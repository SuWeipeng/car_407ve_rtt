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
  
  RTT_CREATE(file,file_log_entry,RT_NULL,1024,1,20);
  return 0;
}

void file_log_entry (void* parameter){
  int fd;
  uint16_t read_size;
  while(1){
    /* Open file to write */
    fd = open(LOG_FILE_NAME, O_WRONLY | O_APPEND | O_BINARY);
    if (fd>= 0)
    {
      read_size = buffer->read();
      if(read_size>0){
        write(fd, buffer->read_buf_addr(), read_size);
      }
      close(fd);
    }
    rt_thread_delay(1);
  }
}

#endif
