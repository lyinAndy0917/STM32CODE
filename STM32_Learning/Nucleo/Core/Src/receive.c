#include "receive.h"
#include "USART.h"
#include "stdio.h"
#include "string.h"

uint8_t rx_counter;//�ۻ��������ݵĳ���
uint8_t rx_buff[20];
uint32_t rx_tick;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //���ﲻ��Ҫ��h������
{

	rx_counter++;
	rx_tick = uwTick;
	HAL_UART_Receive_IT(&huart2,&rx_buff[rx_counter],1);

}


void uart_task()
{
	if(rx_counter != 0)
	{
		if((uwTick - rx_tick)>5)
		{
			printf("Received %d\r\n",rx_counter);
			printf("%s\n",rx_buff);
			rx_counter = 0; //��� �˴�buff���������
			memset(rx_buff,0,sizeof(rx_buff));
			huart2.pRxBuffPtr = rx_buff;
		}
	}


}


