#if defined(USE_RTTHREAD)
#include <entry.h>
#include <dfs_posix.h>
#include "AP_Buffer.h"

#define LOG_FILE_NAME "/log.bin"

extern AP_Buffer *buffer;

rt_thread_t file_thread = RT_NULL;

void file_log_entry (void* parameter);

extern "C"
int file_start(void)
{
  int     fd;
 
  rt_thread_mdelay(300);
  if (dfs_mount("sd0", "/", "elm", 0, 0) != RT_EOK)
  {
    return 1;
  }
  
  fd = open(LOG_FILE_NAME, O_RDONLY | O_BINARY);
  if (fd>=0)
  {
    close(fd);
    unlink(LOG_FILE_NAME);
  }
  
  fd = open(LOG_FILE_NAME, O_WRONLY | O_BINARY | O_CREAT);
  
  if (fd>= 0)
  {
    close(fd);
  }
  
  RTT_CREATE(file,file_log_entry,RT_NULL,4096,RT_THREAD_PRIORITY_MAX-2,20);
  return 0;
}

void file_log_entry (void* parameter){
  int fd;
  uint16_t read_size;
  uint8_t* pos;
  while(1){
    /* Open file to write */
    fd = open(LOG_FILE_NAME, O_WRONLY | O_APPEND | O_BINARY);
    if (fd>= 0)
    {
      read_size = buffer->read();
      if(read_size>0){
        if(read_size <= RT_DFS_ELM_MAX_SECTOR_SIZE){
          write(fd, buffer->read_buf_addr(), read_size);
        } else {
          pos = (uint8_t*)buffer->read_buf_addr();
          do{
            write(fd, pos, RT_DFS_ELM_MAX_SECTOR_SIZE);
            pos += RT_DFS_ELM_MAX_SECTOR_SIZE;
            read_size -= RT_DFS_ELM_MAX_SECTOR_SIZE;
            if(read_size < RT_DFS_ELM_MAX_SECTOR_SIZE){
              write(fd, pos, read_size);
              break;
            }
          }while(1);
        }
      }
      close(fd);
    }
    rt_thread_delay(1000);
  }
}

#endif
