#include <car_def.h>
#include "drv_gpio.h"

#if CAR_TYPE == 0 || CAR_TYPE == 1
#define NRF24L01_CE_PIN         GET_PIN(B, 6)
#define NRF24L01_SPI_DEVICE     "spi10"

// if you don't use the interrupt of nrf24l01, ignore the following macro
#define NRF24_IRQ_PIN           GET_PIN(B, 8)

#elif CAR_TYPE == 5

#define NRF24L01_CE_PIN         GET_PIN(B, 0)
#define NRF24L01_SPI_DEVICE     "spi20"

// if you don't use the interrupt of nrf24l01, ignore the following macro
#define NRF24_IRQ_PIN           GET_PIN(B, 1)
#endif
