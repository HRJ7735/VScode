#include "ads8353.h"
#include "spi.h"
//#include "echo_uart_handle.h"
extern SPI_HandleTypeDef hspi2;
//下降沿 16bit


/* 配置 ads8353 工作模式 */
void ads8353_init(void)
{
  uint16_t cfg_read = 0;
  ads8353_read_config(CFR_READ, 0x3000, &cfg_read);
  if(cfg_read != 0x400)
  {
    HAL_Delay(10);
    ads8353_write_config(CFR_WRITE, 0x8400, &cfg_read);
    HAL_Delay(10);
    ads8353_read_config(CFR_READ, 0x3000, &cfg_read);
    //echo_usart1_printf("cfg:%#x\n", cfg_read);
  }
}

uint16_t ads8353_read_value(uint16_t * value_buffer)
{
  uint16_t tx_buffer[3] = {0};
  uint16_t rx_buffer[3] = {0};
  ADS_CS_PULLDOWN;
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&tx_buffer,(uint8_t*)rx_buffer, 3, 10);
  ADS_CS_PULLUP;
  *value_buffer = rx_buffer[1];
  return rx_buffer[1];
}

void ads8353_write_config(uint16_t reg, uint16_t data_tx, uint16_t * data_rx)
{
  uint16_t cfg_value[3] = {0};
  cfg_value[0] = ((reg & 0x000f) << 12) | ((data_tx & 0x0fff0) >> 4);

  ADS_CS_PULLDOWN;
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&cfg_value,(uint8_t*)data_rx,3, 10);
  ADS_CS_PULLUP;

}
uint16_t ads8353_read_config(uint16_t reg, uint16_t  data_tx, uint16_t *data_rx)
{
  uint16_t tx_buffer[3] = {0};
  tx_buffer[0] = ((reg & 0x000f) << 12) | ((data_tx & 0x0fff0) >> 4);
  uint16_t rx_buffer[3] = {0};
  ADS_CS_PULLDOWN;
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&tx_buffer,(uint8_t*)rx_buffer, 3, 10);
  ADS_CS_PULLUP;
  HAL_Delay(10);
  ADS_CS_PULLDOWN;
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t*)&tx_buffer,(uint8_t*)rx_buffer, 3, 10);
  ADS_CS_PULLUP;
  *data_rx = rx_buffer[0];
  return rx_buffer[0];
}

