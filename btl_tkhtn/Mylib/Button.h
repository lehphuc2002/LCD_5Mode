#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"
#include "stdint.h"
#include "stdlib.h"
typedef struct
{                         // tao bien struct thi ko dc khoi tao gia tri!
	uint8_t btn_current;
	uint8_t btn_last;
	uint8_t btn_filter;
	uint8_t is_debouncing;
	uint32_t time_deboune;
	uint32_t time_start_press;
	uint8_t is_press_timeout;
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;
}Button_Typdef;
	// muon dung ham cho file khac thi phai copy ham do vao file .h
void button_handle(Button_Typdef *ButtonX);
//void button_handle2(Button_Typdef *ButtonX);
void button_init(Button_Typdef *ButtonX,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin); // button cho GPIO nao, PIN nao
void button_delay(Button_Typdef *ButtonX, uint8_t check2);
#endif

