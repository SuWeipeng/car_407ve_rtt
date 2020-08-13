#include <nrf24l01.h>
#include <rtconfig.h>
#include <entry.h>
#include <rtt_interface.h>
#include <mavlink.h>
#include <stm32f4xx_hal.h>

#define NRF24_DEMO_ROLE                 ROLE_PTX
#define NRF24_DEMO_SEND_INTERVAL        10
#define NRF24_DEMO_SPI_DEV_NAME         "spi10"
#define NRF24_DEMO_CE_PIN               GET_PIN(B, 6)
#define NRF24_DEMO_IRQ_PIN              GET_PIN(B, 8)

static uint32_t last_timestamp;
static uint32_t timestamp;

extern UART_HandleTypeDef huart1;

ap_t       mav_data;
vel_target vel={.vel_x = 0.0f, .vel_y = 0.0f, .rad_z = 0.0f};
uint8_t    mode_mav;

static void rx_ind(nrf24_t nrf24, uint8_t *data, uint8_t len, int pipe)
{    
  /*! Don't need to care the pipe if the role is ROLE_PTX */
  if (len > 0) {         // sent successfully and received data
    uint8_t i;
    mavlink_message_t msg_receive;
    mavlink_status_t mav_status;
    for(i=0; i<32; i++) {
      if(mavlink_parse_char(0, data[i], &msg_receive, &mav_status)) {
        last_timestamp = timestamp;
        switch (msg_receive.msgid) {
        case MAVLINK_MSG_ID_VELOCITY: {
          mavlink_velocity_t packet;
          mavlink_msg_velocity_decode(&msg_receive, &packet);
          
          vel.vel_x = packet.vel_x;
          vel.vel_y = packet.vel_y;
          vel.rad_z = packet.rad_z;

          break;
        }
        case MAVLINK_MSG_ID_CMD: {
          uint8_t myTxData[32];
          uint8_t len = mavlink_msg_to_send_buffer( myTxData, &msg_receive );
          HAL_UART_Transmit(&huart1,myTxData,len,10);
          break;
        }
        case MAVLINK_MSG_ID_MODE: {
          mavlink_mode_t packet;
          mavlink_msg_mode_decode(&msg_receive, &packet);
          
          uint8_t mode_msg[2];
          mode_msg[0] = packet.mode;
          mode_msg[1] = packet.reason;
          
          rt_err_t uwRet = RT_EOK;
          
          uwRet = rt_mq_send(mode_mq,
                             mode_msg,
                             sizeof(mode_msg));
          
          if(RT_EOK != uwRet) {
            rt_kprintf("data can not send to message queue, code: %lx\n", uwRet);
          }
          
          rt_sem_release(mode_sem);
          break;
        }
        }
      }
    }
  }
}

static void tx_done(nrf24_t nrf24, int pipe)
{
  mavlink_message_t msg;
  char tbuf[32];
  
  mav_data.mode = mode_mav;
  timestamp = HAL_GetTick();
  if(abs(timestamp - last_timestamp) > 1000){
    memset(&vel, 0, sizeof(vel_target));
    mav_data.com = 1;
  } else {
    mav_data.com = 0;
  }
  mavlink_msg_simple_pack(0,0,&msg,mav_data.value);
  mavlink_msg_to_send_buffer((uint8_t *)tbuf, &msg);
  
  nrf24_send_data(nrf24, (uint8_t *)tbuf, sizeof(tbuf), pipe);
  
  rt_thread_mdelay(NRF24_DEMO_SEND_INTERVAL);
}

const static struct nrf24_callback _cb = {
    .rx_ind = rx_ind,
    .tx_done = tx_done,
};

static void thread_entry(void *param)
{
    nrf24_t nrf24;

    rt_kprintf("[nrf24/demo] Version:%s\n", PKG_NRF24L01_VERSION);

    nrf24 = nrf24_default_create(NRF24_DEMO_SPI_DEV_NAME, NRF24_DEMO_CE_PIN, NRF24_DEMO_IRQ_PIN, &_cb, NRF24_DEMO_ROLE);

    if (nrf24 == RT_NULL)
    {
        rt_kprintf("\n[nrf24/demo] Failed to create nrf24. stop!\n");
        for(;;) rt_thread_mdelay(10000);
    }
    else
    {
        rt_kprintf("[nrf24/demo] running.");
    }

    nrf24_send_data(nrf24, "Hi\n", 3, NRF24_DEFAULT_PIPE);

    while (1)
    {
        nrf24_run(nrf24);

        if(!nrf24->flags.using_irq)
            rt_thread_mdelay(10);
    }
    
}

static int nrf24l01_sample_init(void)
{
    rt_thread_t thread;

    thread = rt_thread_create("nrf_mav", thread_entry, RT_NULL, 1024, RT_THREAD_PRIORITY_MAX/2, 20);
    rt_thread_startup(thread);

    return RT_EOK;
}

INIT_APP_EXPORT(nrf24l01_sample_init);
