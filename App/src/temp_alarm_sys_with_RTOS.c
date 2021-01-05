/*
* temp_alarm_sys_n.c
*
* Created: 6/9/2020 11:33:58 AM
*  Author: H
*/
#define  tas_f	1
#if		 tas_f

#include "temp_alarm_sys_with_RTOS.h"

tas_struct tas = {YES,0,100,0,{0},{0}};  /*initials*/

/*OS services decl*/
#define  E_TEMP				(1<<0)
#define  E_M_DISP			(1<<1)
#define  E_K_C_DISP			(1<<2)
#define  E_T_C_DISP			(1<<3)
#define  E_A_DISP			(1<<4)
#define  E_C_DISP			(1<<5)
#define  E_TH_DISP			(1<<6)
#define  E_AA_DISP			(1<<7)

EventGroupHandle_t			egTAS;
EventBits_t					ebTAS;

/*Tasks IMP*/
void system_init(void)
{
	lcd_init();
	buz_init();
	led_init();						 /*pB 4*/
	key_pad_init();
	adc_b_init();
	uart_init(UART_0,9600);
	rtc_init();
	tas_disp_M();
	tas_update_C();
	tas_disp_C();
	tas_disp_TH();
	tas_disp_AA();
}

void T_display(void *pvData)
{
	while(1)
	{
		ebTAS = xEventGroupWaitBits(egTAS,(E_M_DISP|E_A_DISP|E_C_DISP|E_TH_DISP|E_AA_DISP|E_K_C_DISP|E_T_C_DISP),1,0,500);
		if (ebTAS & E_M_DISP)
		{
			tas_disp_M();
		}
		if (ebTAS & E_A_DISP)
		{
			tas_disp_A();
		}
		if (ebTAS & E_C_DISP)
		{
			tas_disp_C();
		}
		if (ebTAS & E_TH_DISP)
		{
			tas_disp_TH();
		}
		if (ebTAS & E_AA_DISP)
		{
			tas_disp_AA();
		}
		if (ebTAS & E_K_C_DISP)
		{
			tas_disp_K_C();
		}
		if (ebTAS & E_T_C_DISP)
		{
			tas_disp_T_C();
		}
		//vTaskDelay(50);
	}
}

void T_get_temp(void *pvData)
{
	while(1)
	{
		if (tas_update_C() && (ebTAS & E_M_DISP))
		{
			xEventGroupSetBits(egTAS,E_C_DISP);
		}
		vTaskDelay(100);
	}
}

void T_check(void *pvData)
{
	while(1)
	{
		if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
		{
			//xEventGroupClearBits(egTAS,E_M_DISP);
			xEventGroupSetBits(egTAS,E_TEMP | E_A_DISP);
		}
		else
		{
			//xEventGroupSetBits(egTAS,E_M_DISP|E_C_DISP|E_TH_DISP|E_AA_DISP);  /*Test*/
			xEventGroupClearBits(egTAS,E_TEMP | E_A_DISP);
		}
		vTaskDelay(50);
	}
}

void T_key_handler(void *pvData)
{
	U_8 key = 0;
	U_8 threshold_temp = 0;
	U_8 digits[3]={0};
	U_8 ind = 0;
	U_8 digit_ind = 0;
	U_8 k = 1;
	
	while(1)
	{
		key = key_pad_pressed_key();
		if (key == 13)
		{
			key = 0;
			tas_toggle_AA();
			xEventGroupSetBits(egTAS,E_AA_DISP);
		}
		else if (key == 15)
		{
			key = 0;
			//xEventGroupClearBits(egTAS,E_M_DISP);
			//lcd_clear();
			xEventGroupSetBits(egTAS,E_K_C_DISP);
			while(k)
			{
				key = key_pad_pressed_key();
				if (key == 12)
				{
					k = 0;
					xEventGroupSetBits(egTAS,E_M_DISP);
				}
				else if(key == 15)
				{
					threshold_temp = 0;			 /*remove*/
					for(ind = 0;ind < digit_ind;ind ++)
					{
						threshold_temp = threshold_temp*10 + digits[ind];
					}
					tas.thresh_temp = threshold_temp;
					k = 0;
					xEventGroupSetBits(egTAS,E_M_DISP);
				}
				else if(key >= 1 && key <= 10 && digit_ind < 3)
				{
					if (key == 10)
					{
						key = 0;
					}
					lcd_disp_charXY(DISP_LINE,DISP_IND_T+digit_ind,key+'0');
					digits[digit_ind]=key; //=0
					digit_ind ++;
				}
			}
		}
		
		k = 1;
		threshold_temp = 0;
		ind = 0;
		digit_ind = 0;
		vTaskDelay(50);
	}
}


void T_threshold_t_config(void *pvData)
{
	while(1)
	{
		
	}
}

void T_alarming(void *pvData)
{
	while(1)
	{
		ebTAS = xEventGroupWaitBits(egTAS,E_TEMP,0,0,portMAX_DELAY);
		if ((ebTAS&E_TEMP))
		{
			xEventGroupClearBits(egTAS,E_C_DISP);
			led_on();
			buz_on();
			vTaskDelay(500);
			led_off();
			buz_off();
			vTaskDelay(500);
		}
		/*else
		{
			led_off();
			buz_off();
			xEventGroupSetBits(egTAS,E_M_DISP|E_C_DISP|E_TH_DISP|E_AA_DISP);  / *Test* /
			//vTaskDelay(500); / *Check that's right or not !!! * /
		}*/
	}
}

/*TAS functions IMP*/
Bool tas_update_C(void)
{
	Bool result = FALSE;
	U_16 temp = adc_b_read(0);
	temp = (temp*150UL)/1023;		/*0:1023 to 0:150 C*/
	if (temp != tas.current_temp)
	{
		tas.current_temp = temp;
		result = TRUE;
	}
	return result;
}

void tas_toggle_AA(void)
{
	if (tas.alarm_act == YES)
	{
		tas.alarm_act = NO;
	}
	else
	{
		tas.alarm_act = YES;
	}
}

/*Displaying IMP*/
void tas_disp_AA(void)
{
	lcd_disp_charXY(DISP_LINE,DISP_IND_AA,tas.alarm_act);
}

void tas_disp_C(void)
{
	U_8 temp_str[4];
	sprintf(temp_str,"%3d",tas.current_temp);
	lcd_disp_strXY(DISP_LINE,DISP_IND_C,temp_str);
}

void tas_disp_TH(void)
{
	U_8 temp_str[4];
	sprintf(temp_str,"%3d",tas.thresh_temp);
	lcd_disp_strXY(DISP_LINE,DISP_IND_T,temp_str);
}

void tas_disp_M(void)
{
	lcd_disp_strXY(1,1,DISP_MAIN_S_L1);
	lcd_disp_strXY(2,1,DISP_MAIN_S_L2);
}

void tas_disp_K_C(void)
{
	lcd_disp_strXY(1,1,DISP_KEY_CFG_S_L1);
	lcd_disp_strXY(2,1,DISP_KEY_CFG_S_L2);
}

void tas_disp_T_C(void)
{
	lcd_disp_strXY(1,1,DISP_TER_CFG_S_L1);
	lcd_disp_strXY(2,1,DISP_TER_CFG_S_L2);
}

void tas_disp_A(void)
{
	lcd_disp_strXY(1,1,DISP_ALARM_S_L1);
	lcd_disp_strXY(2,1,DISP_ALARM_S_L2);
}


#endif