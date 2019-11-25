#include <rtthread.h>
#include "nrf24l01.h"
#include "mavlink.h"
#include "sample.h"
#include <stdio.h>

static rt_sem_t nrfirq_sem;

static void _irq_init(void);
static void _waitirq(void);

void sample_nrf24l01_task(void *param)
{
  struct hal_nrf24l01_port_cfg halcfg;
  nrf24_cfg_t cfg;
  int rlen;
  uint8_t rbuf[32];
  uint8_t tbuf[32] = "first\r\n";
  uint32_t cnt = 0;

  mavlink_message_t msg;

  mavlink_msg_simple_pack(0,0,&msg,1);
  int len = mavlink_msg_to_send_buffer(tbuf, &msg);

  _irq_init();

  nrf24_default_param(&cfg);
  halcfg.ce_pin = NRF24L01_CE_PIN;
  halcfg.spi_device_name = NRF24L01_SPI_DEVICE;
  cfg.role = ROLE_PTX;    // PTX
  cfg.ud = &halcfg;
  cfg.use_irq = 1;        // True
  nrf24_init(&cfg);

  while (1) {
    rlen = nrf24_irq_ptx_run(rbuf, tbuf, 32, _waitirq);
    if (rlen > 0) {         // sent successfully and received data
      uint8_t i;
      mavlink_message_t msg_receive;
      mavlink_status_t mav_status;
      for(i=0; i<32; i++) {
        if(mavlink_parse_char(0, rbuf[i], &msg_receive, &mav_status)) {
          switch (msg_receive.msgid) {
          case MAVLINK_MSG_ID_VELOCITY: {
            mavlink_velocity_t packet;
            mavlink_msg_velocity_decode(&msg_receive, &packet);

            sprintf((char *)rbuf, "vel_x=%.2f, vel_y=%.2f, rad_z=%.2f\r\n", packet.vel_x, packet.vel_y, packet.rad_z);
            rt_kputs((char *)rbuf);
            break;
          }
          }
        }
      }
    } else if (rlen == 0) { // sent successfully but no data received
      cnt++;
    } else { // sent failed
      rt_kputs("send failed\r\n");
    }
  }
}

static void _irq_cb(void *param)
{
  rt_sem_release(nrfirq_sem);
}

static void _irq_init(void)
{
  nrfirq_sem = rt_sem_create("nrfIRQ", 0, RT_IPC_FLAG_FIFO);

  rt_pin_attach_irq(NRF24_IRQ_PIN, PIN_IRQ_MODE_FALLING, _irq_cb, 0);
  rt_pin_irq_enable(NRF24_IRQ_PIN, PIN_IRQ_ENABLE);
}

static void _waitirq(void)
{
  rt_sem_take(nrfirq_sem, RT_WAITING_FOREVER);
}

static int nrf24l01_sample_init(void)
{
  rt_thread_t thread;

  thread = rt_thread_create("samNrfPTX", sample_nrf24l01_task, RT_NULL, 2048, RT_THREAD_PRIORITY_MAX/2, 20);
  rt_thread_startup(thread);

  return RT_EOK;
}

INIT_APP_EXPORT(nrf24l01_sample_init);
