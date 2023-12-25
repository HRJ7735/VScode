#ifndef     ADS8353_H
#define     ADS8353_H
#include <stdarg.h>
#include "main.h"


#define ADS_CS_PULLDOWN     HAL_GPIO_WritePin(AD_CS_GPIO_Port, AD_CS_Pin, GPIO_PIN_RESET)
#define ADS_CS_PULLUP       HAL_GPIO_WritePin(AD_CS_GPIO_Port, AD_CS_Pin, GPIO_PIN_SET)

typedef enum
{
  REFDAC_A_READ = 0x01,
  READAC_B_READ = 0x02,
  CFR_READ      = 0x03,
  CFR_WRITE     = 0x08,
  REFDAC_A_WRITE= 0x09,
  REFDAC_B_WRITE= 0x0A,
}AD_WRITE_OP_TYPE;



void ads8353_init(void);
uint16_t ads8353_read_value(uint16_t * value_buffer);
void ads8353_write_config(uint16_t reg, uint16_t tx_buffer, uint16_t * rx_buffer);
uint16_t ads8353_read_config(uint16_t reg, uint16_t tx_buffer , uint16_t *rx_buffer);

#endif