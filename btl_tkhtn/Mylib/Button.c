#include "Button.h"
//---------------var button------------

__weak void	btn_pressing_callback(Button_Typdef *ButtonX)
{
}
__weak void btn_press_short_callback(Button_Typdef *ButtonX )
{
	
}
__weak void btn_release_callback(Button_Typdef *ButtonX)
{

}
__weak void btn_press_timeout_callback(Button_Typdef *ButtonX)
{

}
//void button_handle2(Button_Typdef *ButtonX)
//{
//	int a;
//	uint8_t sta = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
//	if(sta == 0)
//	{
//		HAL_Delay(50);
//		if(sta == 0)
//			{
//				btn_pressing_callback(ButtonX);
//			}
//	}
//	if(HAL_GetTick() - a >= 50)
//	{
//			btn_pressing_callback(ButtonX);
//	}
//}
void button_handle(Button_Typdef *ButtonX)
{
	//------------------ Loc nhieu ------------------------
	uint8_t sta = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
	if(sta != ButtonX->btn_filter)
	{
		ButtonX->btn_filter = sta;
		ButtonX->is_debouncing = 1;
		ButtonX->time_deboune = HAL_GetTick();
	}
	//------------------ Tin hieu da xac lap------------------------
	if(ButtonX->is_debouncing && (HAL_GetTick() - ButtonX->time_deboune >= 15))
	{
		ButtonX->btn_current = ButtonX->btn_filter;
		ButtonX->is_debouncing =0;
	}
	//---------------------Xu li nhan nha------------------------
	if(ButtonX->btn_current != ButtonX->btn_last)
	{
		if(ButtonX->btn_current == 0)//nhan xuong
		{
			ButtonX->is_press_timeout = 1;
			btn_pressing_callback(ButtonX);
			ButtonX->time_start_press = HAL_GetTick();
		}
		else //nha nut
		{
//			if(HAL_GetTick() - ButtonX->time_start_press <= 1000)
//			{
//				btn_press_short_callback(ButtonX);
//			}
			btn_release_callback(ButtonX);
			ButtonX->is_press_timeout = 0;
		}
		ButtonX->btn_last = ButtonX->btn_current;
	}
	//-------------Xu li nhan giu----------------
//	if(ButtonX->is_press_timeout && (HAL_GetTick() - ButtonX->time_start_press >= 3000))
//	{
//		btn_press_timeout_callback(ButtonX);
//		ButtonX->is_press_timeout =0;
//	}
}
void button_delay(Button_Typdef *ButtonX, uint8_t check2)
{
	//check2 = HAL_GPIO_ReadPin(ButtonX->GPIOx, ButtonX->GPIO_Pin);
//	if(check2 != ButtonX->btn_filter)
//	{
//		ButtonX->btn_filter = check2;
//		ButtonX->is_debouncing = 1;
//		ButtonX->time_deboune = HAL_GetTick();
//	}
//	//------------------ Tin hieu da xac lap------------------------
//	if(ButtonX->is_debouncing && (HAL_GetTick() - ButtonX->time_deboune >= 15))
//	{
//		ButtonX->btn_current = ButtonX->btn_filter;
//		ButtonX->is_debouncing =0;
//	}
	uint32_t relax;
	if(check2 != ButtonX->btn_filter)
	{
		relax = HAL_GetTick();
		if(HAL_GetTick() - relax < 60)
		{
				
		}
		ButtonX->btn_filter = check2;
	}
}
void button_init(Button_Typdef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	ButtonX->GPIOx = GPIOx;
	ButtonX->GPIO_Pin = GPIO_Pin;
}
