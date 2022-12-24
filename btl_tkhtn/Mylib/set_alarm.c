//#include "set_alarm.h"


//void set_alarm()
//{
//	while(checkMinHour == 1)
//	{
//	button_handle(&button1);
//			if(check == 3)
//			{
////				lcd_clear_display(&hlcd);
////				lcd_set_cursor(&hlcd, 1,2);
////				lcd_printf(&hlcd, "OUT SETTING");
//				break;
//			}
//	lcd_set_cursor(&hlcd, 1,10);
//	lcd_printf(&hlcd, "Hr");
//	HourMin.sethour = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
//	button_delay(&button3, sethour);
//	if(sethour == 0)
//	{
//		if(hour2 >= 23)
//		{
//			hour2 = -1;
//		}
//		hour2++;
//		HAL_Delay(200);
//		lcd_set_cursor(&hlcd, 0,4);
//		lcd_printf(&hlcd, "%02d:00:00",hour2);
//	}
//	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
//	button_delay(&button4, checkkk);
//		if(checkkk == 0)
//		{
//			checkMinHour = 2;
//			HAL_Delay(250);
//			break;
//		}
//	}
//	while(checkMinHour == 2)
//	{
//	button_handle(&button1);
//			if(check == 3)
//			{
////				lcd_clear_display(&hlcd);
////				lcd_set_cursor(&hlcd, 1,2);
////				lcd_printf(&hlcd, "OUT SETTING");
//				break;
//			}	
//	lcd_set_cursor(&hlcd, 1,10);
//	lcd_printf(&hlcd, "Min");
//	HourMin.setmin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
//	button_delay(&button3, setmin);
//		if(setmin == 0)
//		{	
//			if(min2 >= 59)
//			{
//				min2 = -1;
//			}
//		min2++;
//		HAL_Delay(200);
//		lcd_set_cursor(&hlcd, 0,4);
//		lcd_printf(&hlcd, "%02d:%02d:00",hour2,
//								min2);
//		}
//	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
//	button_delay(&button4, checkkk);
//		if(checkkk == 0)
//		{
//			checkMinHour = 3;
//			HAL_Delay(250);
//			break;
//		}	
//	}
//	while(checkMinHour == 3)
//	{
//	button_handle(&button1);
//			if(check == 3)
//			{
////				lcd_clear_display(&hlcd);
////				lcd_set_cursor(&hlcd, 1,2);
////				lcd_printf(&hlcd, "OUT SETTING");
//				break;
//			}
//	lcd_set_cursor(&hlcd, 1,10);
//	lcd_printf(&hlcd, "Sec");
//	setsecond = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
//	button_delay(&button3, setsecond);
//		if(setsecond == 0)
//		{	
//			if(second2 >= 59)
//			{
//				second2 = -1;
//			}
//		second2++;
//		HAL_Delay(200);
//		lcd_set_cursor(&hlcd, 0,4);
//		lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,
//								min2,second2);
//		}
//	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
//	button_delay(&button4, checkkk);
//		if(checkkk == 0)
//		{
//			checkMinHour = 4;         // cai nay de debug coi choi thoi
//			HAL_Delay(250);
//			break;
//		}	
//	}
//		lcd_set_cursor(&hlcd, 1,10);
//		lcd_printf(&hlcd, "   ");
//		lcd_set_cursor(&hlcd, 0,4);
//		lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,
//								min2,second2);
//		lcd_set_cursor(&hlcd, 1,7);
//		lcd_printf(&hlcd, "DONE!");
//		while(1)
//		{
//			button_handle(&button1);
//			if(check == 3)
//			{
//				lcd_clear_display(&hlcd);
//				lcd_set_cursor(&hlcd, 1,2);
//				lcd_printf(&hlcd, "OUT SETTING");    // cai nay lam choi
//				break;
//			}
//		}
//}