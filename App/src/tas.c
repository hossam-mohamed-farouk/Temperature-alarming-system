/*
 * temp_alarm_sys_n.c
 *
 * Created: 6/9/2020 11:33:58 AM
 *  Author: H
 */ 
#define  tas_f	0
#if		 tas_f

#include "temp_alarm_sys_with_RTOS.h"

tas_struct tas = {SS_MAIN,YES,0,100,0,{0},{0}};  /*initials*/

void tas_init(void)
{
	lcd_init();
	buz_init();
	led_init();			 /*pB 4*/
	//leds_init(0xff);	/*port A*/
	key_pad_init();
	adc_b_init();
	uart_init(UART_0,9600);
	rtc_init();
}

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

void tas_disp_T(void)
{
	U_8 temp_str[4];
	sprintf(temp_str,"%3d",tas.thresh_temp);
	lcd_disp_strXY(DISP_LINE,DISP_IND_T,temp_str);
}

void tas_disp_NA(void)
{
	lcd_disp_intXY(2,DISP_IND_NA,tas.alarms_number);
}

void tas_disp_date(void)
{
	lcd_disp_charXY(DISP_LINE,DISP_IND_D,tas.la_date[0]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_D+1,tas.la_date[1]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_M,tas.la_date[3]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_M+1,tas.la_date[4]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_Y,tas.la_date[8]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_Y+1,tas.la_date[9]);
}

void tas_disp_time(void)
{
	lcd_disp_charXY(DISP_LINE,DISP_IND_H,tas.la_time[0]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_H+1,tas.la_time[1]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_MIN,tas.la_time[3]);
	lcd_disp_charXY(DISP_LINE,DISP_IND_MIN+1,tas.la_time[4]);
}

void tas_disp_state(void)
{
	switch (tas.system_state)
	{
		case SS_MAIN:
		lcd_disp_strXY(1,1,DISP_MAIN_S_L1);
		lcd_disp_strXY(2,1,DISP_MAIN_S_L2);
		break;
		case SS_KEY_CFG:
		lcd_disp_strXY(1,1,DISP_KEY_CFG_S_L1);
		lcd_disp_strXY(2,1,DISP_KEY_CFG_S_L2);
		break;
		case SS_TERM_CFG:
		lcd_disp_strXY(1,1,DISP_TER_CFG_S_L1);
		lcd_disp_strXY(2,1,DISP_TER_CFG_S_L2);
		break;
		case SS_ALARM:
		lcd_disp_strXY(1,1,DISP_ALARM_S_L1);
		lcd_disp_strXY(2,1,DISP_ALARM_S_L2);
		break;
		case SS_ALARM_HIS:
		lcd_disp_strXY(1,1,DISP_ALARM_HISTORY_S_L1);
		lcd_disp_strXY(2,1,DISP_ALARM_HISTORY_S_L2);
		break;
	}
}

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

void tas_update_date(void)
{
	RTC_STRUCT* my_rtc = NULL;
	my_rtc = rtc_update();
	//memcpy(tas.la_date,my_rtc->rtc_date,11);
	tas.la_date[0] = my_rtc->rtc_date[0];
	tas.la_date[1] = my_rtc->rtc_date[1];
	tas.la_date[3] = my_rtc->rtc_date[3];
	tas.la_date[4] = my_rtc->rtc_date[4];
	tas.la_date[8] = my_rtc->rtc_date[8];
	tas.la_date[9] = my_rtc->rtc_date[9];
	//memcpy(tas.la_time,my_rtc->rtc_time,9);
	tas.la_time[0] = my_rtc->rtc_time[0];
	tas.la_time[1] = my_rtc->rtc_time[1];
	tas.la_time[3] = my_rtc->rtc_time[3];
	tas.la_time[4] = my_rtc->rtc_time[4];
}

void eeprom_update_data(void)
{
	int_eeprom_write_byte(0x01,tas.alarms_number);
	
	int_eeprom_write_byte(0x02,tas.la_date[0]);
	int_eeprom_write_byte(0x03,tas.la_date[1]);
	int_eeprom_write_byte(0x04,tas.la_date[3]);
	int_eeprom_write_byte(0x05,tas.la_date[4]);
	int_eeprom_write_byte(0x06,tas.la_date[8]);
	int_eeprom_write_byte(0x07,tas.la_date[9]);
	
	int_eeprom_write_byte(0x08,tas.la_time[0]);
	int_eeprom_write_byte(0x09,tas.la_time[1]);
	int_eeprom_write_byte(0x0A,tas.la_time[3]);
	int_eeprom_write_byte(0x0B,tas.la_time[4]);
}

void eeprom_data_backup(void)
{
	tas.thresh_temp = int_eeprom_read_byte(0x00);
	
	tas.alarms_number = int_eeprom_read_byte(0x01);
	
	tas.la_date[0] = int_eeprom_read_byte(0x02);
	tas.la_date[1] = int_eeprom_read_byte(0x03);
	tas.la_date[3] = int_eeprom_read_byte(0x04);
	tas.la_date[4] = int_eeprom_read_byte(0x05);
	tas.la_date[8] = int_eeprom_read_byte(0x06);
	tas.la_date[9] = int_eeprom_read_byte(0x07);
	
	tas.la_time[0] = int_eeprom_read_byte(0x08);
	tas.la_time[1] = int_eeprom_read_byte(0x09);
	tas.la_time[3] = int_eeprom_read_byte(0x0A);
	tas.la_time[4] = int_eeprom_read_byte(0x0B);
}

#endif