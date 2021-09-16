#ifndef HC05_H
#define HC05_H
#include <usart.h>
#include <retarget.h>

void HC05_init(UART_HandleTypeDef* hc_05);
void HC05_print();
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef* huart, uint8_t *pData, uint16_t Size);








#endif /*HC05_H */
