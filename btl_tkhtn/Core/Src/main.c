/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RTC.h"
#include "LiquidCrystal_I2C.h"
#include "Button.h"
#include "set_alarm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */
RTC_Typedef hrtc1;
RTC_Typedef hrtc2;
LiquidCrystal_I2C hlcd;
Button_Typdef button1;   // A6
Button_Typdef button2;   // A5
Button_Typdef button3;   // A4
Button_Typdef button4;   // A3
uint8_t check = 0;
uint8_t checkhand;
int8_t hour2 = 0;
int8_t min2 = 0;
int8_t second2 = 0;
uint8_t increHour; uint8_t decreHour;
uint8_t increMin;	 uint8_t decreMin;
uint8_t increSec;  uint8_t decreSec;
uint8_t pin = 0;
char checkMinHour = 0; // cho ra ngoai tum lum de debug :v
uint32_t value;
uint8_t data_Uart;
int8_t onHour; int8_t offHour;
int8_t onMin; int8_t offMin;
int8_t onSec; int8_t offSec;
char setOFFHour = 0;  char setOFFMin = 0; char setOFFSec = 0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void But2()
//{
////		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
//		lcd_clear_display(&hlcd);
//		lcd_set_cursor(&hlcd, 0,0);
//		lcd_printf(&hlcd, "Mode 2:Hand");
////		button_handle(&button2);
//		{
//			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//		}
//}
void btn_pressing_callback(Button_Typdef *ButtonX)
{
	if(check == 6)
	{
		check = 0;
	}
	if(ButtonX == &button1)
	{
		check++;
	}
//	
//	if(ButtonX == &button2)
//	{
//		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//	}
	
}
void lcd_DateMonthYear()
{
//	lcd_clear_display(&hlcd);
//		lcd_set_cursor(&hlcd, 0,0);
//		lcd_printf(&hlcd, "M1:");
//		lcd_set_cursor(&hlcd, 0,4);
//		lcd_printf(&hlcd, "%02d:%02d:%02d",hrtc1.date_time.hour,
//								hrtc1.date_time.min, hrtc1.date_time.second);
		lcd_set_cursor(&hlcd, 1,6);
		lcd_printf(&hlcd, "%02d/%02d/%02d",hrtc1.date_time.date,
						hrtc1.date_time.month,hrtc1.date_time.year);
////		lcd_set_cursor(&hlcd,1,2);
////		lcd_printf(&hlcd, "%s,",(Convert2Day)hrtc1.date_time.day);
		switch(hrtc1.date_time.day)
			{
			case 1:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Mon,");
			break;
			case 2:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Tue,");
			break;
			case 3:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Wed,");
			break;
			case 4:
				lcd_set_cursor(&hlcd,1,1);
			lcd_printf(&hlcd, "Thur,");
			break;
			case 5:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Fri,");
			break;
			case 6:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Sat,");
			break;
			case 7:
				lcd_set_cursor(&hlcd,1,2);
			lcd_printf(&hlcd, "Sun,");
			break;
			default:
				break;
			}
}

void set_alarm1()
{
	//Set Gio ON
	// ------------------------------------------------------------------------------------------------------------------
	while(checkMinHour == 1)
	{
	button_handle(&button1);
			if(check == 3)
			{
//				lcd_clear_display(&hlcd);
//				lcd_set_cursor(&hlcd, 1,2);
//				lcd_printf(&hlcd, "OUT SETTING");
				break;
			}
	lcd_set_cursor(&hlcd, 1,10);
	lcd_printf(&hlcd, "Hr");
	increHour = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
	button_delay(&button3, increHour);
	if(increHour == 0)
	{
		if(hour2 >= 23)
		{
			hour2 = -1;
		}
		hour2++;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:00:00",hour2);
	}
			// nut giam
	decreHour = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
	button_delay(&button2, increHour);
	if(decreHour == 0)
	{
		if(hour2 <= 0)
		{
			hour2 = 24;
		}
		hour2--;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:00:00",hour2);	
	}
	//
	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
	button_delay(&button4, checkkk);
		if(checkkk == 0)
		{
			checkMinHour = 2;
			HAL_Delay(350);
			break;
		}
	}
	//Set Phut ON
	// ------------------------------------------------------------------------------------------------------------------
	while(checkMinHour == 2)
	{
	button_handle(&button1);
			if(check == 3)
			{
//				lcd_clear_display(&hlcd);
//				lcd_set_cursor(&hlcd, 1,2);
//				lcd_printf(&hlcd, "OUT SETTING");
				break;
			}	
	lcd_set_cursor(&hlcd, 1,10);
	lcd_printf(&hlcd, "Min");
	increMin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
	button_delay(&button3, increMin);
		if(increMin == 0)
		{	
			if(min2 >= 59)
			{
				min2 = -1;
			}
		min2++;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:00",hour2,
								min2);
		}
		// nut giam
		decreMin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
	button_delay(&button2, increHour);
	if(decreMin == 0)
	{
		if(min2 <= 0)
		{
			min2 = 60;
		}
		min2--;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:00",hour2,
								min2);
	}
		//
	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
	button_delay(&button4, checkkk);
		if(checkkk == 0)
		{
			checkMinHour = 3;
			HAL_Delay(350);
			break;
		}	
	}
	//Set Giay ON
	// ------------------------------------------------------------------------------------------------------------------
	while(checkMinHour == 3)
	{
	button_handle(&button1);
			if(check == 3)
			{
//				lcd_clear_display(&hlcd);
//				lcd_set_cursor(&hlcd, 1,2);
//				lcd_printf(&hlcd, "OUT SETTING");
				break;
			}
	lcd_set_cursor(&hlcd, 1,10);
	lcd_printf(&hlcd, "Sec");
	increSec = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
	button_delay(&button3, increSec);
		if(increSec == 0)
		{	
			if(second2 >= 59)
			{
				second2 = -1;
			}
		second2++;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,
								min2,second2);
		}
		// nut giam
		decreSec = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
	button_delay(&button2, increHour);
	if(decreSec == 0)
	{
		if(second2 <= 0)
		{
			second2 = 60;
		}
		second2--;
		HAL_Delay(200);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,
								min2,second2);
	}
	//
	uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     // cung ten voi checkkk o duoi nhung 2 then la khac nhau mac du cung chuc nang :)))
	button_delay(&button4, checkkk);    // button4 de chuyen trang thai chinh gio phut giay 
		if(checkkk == 0)
		{
//			checkMinHour = 4;
			HAL_Delay(350);
			break;
		}
	}		
		onHour = hour2;
		onMin = min2;
		onSec = second2;
		lcd_set_cursor(&hlcd, 1,10);
		lcd_printf(&hlcd, "   ");
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:%02d",onHour,
								onMin,onSec);
		lcd_set_cursor(&hlcd, 1,4);
		lcd_printf(&hlcd, "ON DONE!");
		while(1)
		{	
			uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);   
			button_delay(&button4, checkkk);
			if(checkkk == 0)
			{
				setOFFHour = 1;
				HAL_Delay(500);
				break;			
			}
			button_handle(&button1);
			if(check == 3)
			{
		    // cai nay lam choi
				break;
			}
		}
		lcd_clear_display(&hlcd);
		//Set Gio OFF
	// ------------------------------------------------------------------------------------------------------------------
		if(setOFFHour)
		{
			button_handle(&button1);
//			if(check == 3)
//			{
//				break;
//			}
			lcd_set_cursor(&hlcd, 0,0);
			lcd_printf(&hlcd, "M2:");
			lcd_set_cursor(&hlcd, 1,0);
			lcd_printf(&hlcd, "           ");
			lcd_set_cursor(&hlcd, 1,0);
			lcd_printf(&hlcd, "SET OFF  ");
			lcd_set_cursor(&hlcd, 1,10);
			lcd_printf(&hlcd, "Hr ");	
			while(1)                         // khong hieu sao ko dung while(1) ma dung chinh bien thoi gian giong nhu o tren checkMinHour = 1 2 3 thi no ko chay :))))
			{
				increHour = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
				button_delay(&button3, increHour);
				if(increHour == 0)
				{
					if(hour2 >= 23)
					{
						hour2 = -1;
					}
				hour2++;
				HAL_Delay(200);
				lcd_set_cursor(&hlcd, 0,4);
				lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,min2,second2);
	//			lcd_printf(&hlcd,"hihi");
				}
				// nut giam
				decreHour = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
				button_delay(&button2, increHour);
				if(decreHour == 0)
				{
					if(hour2 <= 0)
					{
						hour2 = 24;
					}
					hour2--;
					HAL_Delay(200);
					lcd_set_cursor(&hlcd, 0,4);
					lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,min2,second2);	
				}
				//
				button_handle(&button1);
					if(check == 3)
					{
						break;
					}	
			uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);   
			button_delay(&button4, checkkk);
			if(checkkk == 0)
				{
					setOFFHour = 0;
					setOFFMin = 1;
					HAL_Delay(500);
					break;
				}
			}
//			break;
		}
		//Set Phut OFF
	// ------------------------------------------------------------------------------------------------------------------
		if(setOFFMin)
		{
			button_handle(&button1);
			lcd_set_cursor(&hlcd, 1,0);
			lcd_printf(&hlcd, "SET OFF  ");
			lcd_set_cursor(&hlcd, 1,9);
			lcd_printf(&hlcd, " Min");
		while(1)                         
		{
		increMin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
		button_delay(&button3, increHour);
		if(increMin == 0)
		{
			if(min2 >= 59)
			{
				min2 = -1;
			}
			min2++;
			HAL_Delay(200);
			lcd_set_cursor(&hlcd, 0,4);
			lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,min2,second2);
		}
			// nut giam
			decreMin = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
		button_delay(&button2, increHour);
		if(decreMin == 0)
		{
			if(min2 <= 0)
			{
				min2 = 60;
			}
			min2--;
			HAL_Delay(200);
			lcd_set_cursor(&hlcd, 0,4);
			lcd_printf(&hlcd, "%02d:%02d:00",hour2,
									min2);
		}
			//
		button_handle(&button1);
			if(check == 3)
			{
				break;
			}
		uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     
		button_delay(&button4, checkkk);
			if(checkkk == 0)
			{
				setOFFMin = 0;
				setOFFSec = 1;
				HAL_Delay(350);
				break;
			}
		}
	}
		if(setOFFSec)
		{
			button_handle(&button1);
			lcd_set_cursor(&hlcd, 1,0);
			lcd_printf(&hlcd, "SET OFF  ");
			lcd_set_cursor(&hlcd, 1,9);
			lcd_printf(&hlcd, " Sec");
		while(1)                         
		{
		increSec = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4);    
		button_delay(&button3, increHour);
		if(increSec == 0)
		{
			if(second2 >= 59)
			{
				second2 = -1;
			}
			second2++;
			HAL_Delay(200);
			lcd_set_cursor(&hlcd, 0,4);
			lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,min2,second2);
		}
			// nut giam
			decreSec = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);    
		button_delay(&button2, increHour);
		if(decreSec == 0)
		{
			if(second2 <= 0)
			{
				second2 = 60;
			}
			second2--;
			HAL_Delay(200);
			lcd_set_cursor(&hlcd, 0,4);
			lcd_printf(&hlcd, "%02d:%02d:%02d",hour2,
									min2,second2);
		}
		//
		button_handle(&button1);
			if(check == 3)
			{
				break;
			}
		uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     
		button_delay(&button4, checkkk);
			if(checkkk == 0)
			{
				setOFFSec = 0;
				HAL_Delay(350);
				break;
			}
		}
	}
		offHour = hour2;
		offMin = min2;
		offSec = second2;
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd,0,0);
		lcd_printf(&hlcd,"  Done_SetUp!");
		lcd_set_cursor(&hlcd,1,0);
		lcd_printf(&hlcd,"BTN1_To_Continue");
		while(1)
		{
			button_handle(&button1);
			if(check == 3)
			{
		    // cai nay lam choi
				break;
			}
		}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	//	button_handle(&button1);
	if(check == 6)
	{
		if(data_Uart == '0')   //  Y = yes
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
			lcd_set_cursor( &hlcd, 1,3);
			lcd_printf(&hlcd, "LED OFF");
		}
		else if(data_Uart == '1')   // N = no
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,1);
			lcd_set_cursor(&hlcd, 1,3);
			lcd_printf(&hlcd, "LED ON ");
		}		
	
	HAL_UART_Receive_IT(&huart1,&data_Uart,1);    // gap Receive_IT thi quay lai Callback
	}
//	}
}
void lcd_handle()
{
	if(check == 1)
	{	
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd, 0,0);
		lcd_printf(&hlcd, "M1:");
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:%02d",hrtc1.date_time.hour,
								hrtc1.date_time.min, hrtc1.date_time.second);
		lcd_DateMonthYear();
	}
	else if(check == 2)
	{
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd, 0,0);
		lcd_printf(&hlcd, "Btn4(Continue)");  
		lcd_set_cursor(&hlcd, 1,0);
		lcd_printf(&hlcd, "Btn3(+) Btn2(-)");
		while(1)
		{
			uint8_t checkkk = HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3);     
			button_delay(&button4, checkkk);
			if(checkkk == 0)
			{
				lcd_clear_display(&hlcd);
				HAL_Delay(350);
				break;
			}
		}
		lcd_printf(&hlcd, "M2:");
		lcd_set_cursor(&hlcd, 1,0);
		lcd_printf(&hlcd, "SET ON");
		checkMinHour = 1;
		set_alarm1();
		lcd_clear_display(&hlcd); 
		while(1)
		{
		RTC_ReadTime(&hrtc1,&hrtc1.date_time);
		lcd_set_cursor(&hlcd, 0,4);
		lcd_printf(&hlcd, "%02d:%02d:%02d",hrtc1.date_time.hour,
								hrtc1.date_time.min, hrtc1.date_time.second);
		lcd_set_cursor(&hlcd, 1,3);
		lcd_printf(&hlcd, "REAL__TIME");
			if(onHour == hrtc1.date_time.hour &&  onMin == hrtc1.date_time.min && onSec == hrtc1.date_time.second)
			{
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,1);
				uint32_t b = HAL_GetTick();
				while(HAL_GetTick() - b < 1000)
				{
					if(offHour == hrtc1.date_time.hour &&  offMin == hrtc1.date_time.min && offSec == hrtc1.date_time.second)
					{
					HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
					}
					button_handle(&button1);
					if(check == 4)
						{break;}
				}
			}
			if(offHour == hrtc1.date_time.hour &&  offMin == hrtc1.date_time.min && offSec == hrtc1.date_time.second)
			{
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
				uint32_t b = HAL_GetTick();
				while(HAL_GetTick() - b < 1000)
				{
					button_handle(&button1);
					if(check == 4)
						{break;}
				}
			}
			button_handle(&button1);
			if(check == 4)
			{
////				lcd_clear_display(&hlcd);
////				lcd_set_cursor(&hlcd, 1,2);
////				lcd_printf(&hlcd, "OUT SETTING");
				break;
//			}
			}
		}
	}
	else if(check == 4)
	{
		
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd, 0,0);
		lcd_printf(&hlcd, "Mode 3:Manual");
		if(pin == 0)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
		}
		if(pin % 2 == 1)
			{
				lcd_set_cursor(&hlcd, 1,3);
				lcd_printf(&hlcd, "LED ON ");
			}
		else if(pin % 2 == 0)
			{
				lcd_set_cursor(&hlcd, 1,3);
				lcd_printf(&hlcd, "LED OFF");
			}
		checkhand =  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5);
		button_delay(&button2,checkhand);		
		if(checkhand == 0)
		{
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
			pin++;
			if(pin % 2 == 1)
				{
					lcd_set_cursor( &hlcd, 1,3);
					lcd_printf(&hlcd, "LED ON ");
				}
			else if(pin % 2 == 0)
				{
					lcd_set_cursor(&hlcd, 1,3);
					lcd_printf(&hlcd, "LED OFF");
				}
			uint32_t a = HAL_GetTick();
			while(HAL_GetTick() - a < 500)
			{
				button_handle(&button1);
				if(check == 5)
				{ break; }
			}
			
//				button_handle(&button2);
//				if(checkhand == 0)
//				{
//					HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
//				}
			
			
//				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
		
//			HAL_Delay(150);
		}
	}
	else if(check == 5)
	{ 
		pin = 0;
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd, 0,0);
		lcd_printf(&hlcd, "Mode 4: ADC");
		uint32_t time = HAL_GetTick();
		HAL_ADCEx_Calibration_Start(&hadc1);  // tu dong can chinh ADC, neu su dung ham phai duoc goi truoc khi Start ADC   
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,100);  // Wait for ADC conversion completion, cho ADC doc xong, 100ms chua doc dc thi out chu ko thi no dung mai trong do 
		value = HAL_ADC_GetValue(&hadc1);
		if(value > 3800U)    // U la unsigned int
		{ 
//			uint32_t time11 = HAL_GetTick();	
//			if((HAL_GetTick() - time11) < 1000)    
//			{ 
//			}
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,1);    
			lcd_set_cursor( &hlcd, 1,3);
			lcd_printf(&hlcd, "LED ON ");
		}
		else
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
			lcd_set_cursor( &hlcd, 1,3);
			lcd_printf(&hlcd, "LED OFF");
		}
		HAL_ADC_Stop(&hadc1);    // stop de su dung lai ham Calibration duoc
		while(HAL_GetTick() - time < 5000)
		{ 
			button_handle(&button1);
			if(check == 6)
			{
				break;
			}
		}
		button_handle(&button1);        

	}
	else if(check == 6)
	{
		lcd_clear_display(&hlcd);
		lcd_set_cursor(&hlcd, 0,0);
		lcd_printf(&hlcd, "Mode 5:Bluetooth");
//		HAL_UART_Receive_IT(&huart1,&data_Uart,1);
		while(check == 6)
		{
			button_handle(&button1);
			if(check != 6)
			{
				break;                               
			}
			HAL_UART_RxCpltCallback(&huart1);
		}
//		HAL_UART_RxCpltCallback(&huart1);
			
	}
}

void btn_release_callback(Button_Typdef *ButtonX)
{
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	button_init(&button1,GPIOA,GPIO_PIN_6);
	button_init(&button2,GPIOA,GPIO_PIN_5);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	
	lcd_init(&hlcd, &hi2c1, LCD_ADDR_DEFAULT);
	RTC_Init(&hrtc1,&hi2c1);
//	HAL_UART_Receive_IT(&huart1,&data_Uart,1);    // cua Uart
//	hrtc1.date_time.hour = 14;
//	hrtc1.date_time.min = 25;
//	hrtc1.date_time.second = 10;
//		hrtc1.date_time.day = 6;
//	hrtc1.date_time.date = 17;
//	hrtc1.date_time.month = 12;
//	hrtc1.date_time.year = 22;
//	RTC_WriteTime(&hrtc1,&hrtc1.date_time);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		uint32_t wait = HAL_GetTick();
		while(HAL_GetTick() - wait < 20)
		{}
		button_handle(&button1);
//		button_handle(&button2);
    RTC_ReadTime(&hrtc1,&hrtc1.date_time);
		lcd_handle();
//	lcd_set_cursor(&hlcd, 0,0);
//	lcd_printf(&hlcd, "M1:");
//	lcd_set_cursor(&hlcd, 0,4);
//	lcd_printf(&hlcd, "%02d:%02d:%02d",hrtc1.date_time.hour,
//								hrtc1.date_time.min, hrtc1.date_time.second);
//	lcd_set_cursor(&hlcd, 1,4);
//	lcd_printf(&hlcd, "%02d/%02d/%02d",hrtc1.date_time.date,
//	hrtc1.date_time.month,hrtc1.date_time.year);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
