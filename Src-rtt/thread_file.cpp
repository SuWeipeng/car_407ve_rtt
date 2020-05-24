#if defined(USE_RTTHREAD)
#include <entry.h>
#include <dfs_posix.h>
#include "AP_Buffer.h"
extern "C"{
#include "drv_spi.h"
#include "spi_msd.h"
}

#define LOG_FILE_NAME "/log.bin"

extern "C" int rt_hw_sdio_init(void);
extern AP_Buffer *buffer;

uint8_t     mount_success = 0;
rt_thread_t file_thread = RT_NULL;

static int rt_hw_sd1_init(void)
{
    rt_hw_spi_device_attach("spi2", "spi20", GPIOB, GPIO_PIN_12);
    msd_init("sd1", "spi20");
    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_hw_sd1_init);

extern "C"
void file_log_entry (void* parameter){
  int fd, mout_result = -1;
  uint16_t read_size;
  uint8_t* pos;
  
  while(1){
    /* Open file to write */
    if (mount_success == 1) {
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
    } else {
      do{
        if(rt_device_find("sd1") != RT_NULL){
          mout_result = dfs_mount("sd1", "/", "elm", 0, 0);
          if(mout_result != RT_EOK && rt_device_find("sd0") != RT_NULL){
            mout_result = dfs_mount("sd0", "/", "elm", 0, 0);
            if(mout_result != RT_EOK){
              rt_thread_delay(300);
              rt_hw_sdio_init();
            }
          }
        }
      } while(mout_result != RT_EOK);
      
      mount_success = 1;
        
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
    }
    rt_thread_delay(1000);
  }

}

#endif
