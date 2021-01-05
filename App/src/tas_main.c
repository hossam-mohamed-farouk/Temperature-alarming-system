/*
 * temperature_alarming_system.c
 *
 * Created: 6/6/2020 12:58:28 AM
 * Author : H
 */ 
#define  tasm_f	0
#if		 tasm_f

#include "temp_alarm_sys_with_RTOS.h"


extern tas_struct tas;

int main(void)
{
	system_state_t prev_state = SS_NONE;
	U_8 key = 0;
	U_8 digit_ind = 0;
	U_8 data = 0;
	U_32 delay_count = 0;
	U_8 threshold_temp = 0;
	U_8 digits[3]={0};
	U_8 ind = 0;	
	
	eeprom_data_backup();
	tas_init();
	
    while (1) 
    {
		//start_alarm_temp_sys();
		switch (tas.system_state)
		{
			case SS_MAIN:
					/*For each entry*/
				if (prev_state != SS_MAIN)
				{
					prev_state = SS_MAIN;
					tas_disp_state();
					tas_disp_T();
					tas_disp_AA();
					tas_disp_C();
				}
						/*C*/
				if (tas_update_C())
				{
					tas_disp_C();
					if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
					{
						tas_update_date();
						tas.system_state = SS_ALARM;
						tas.alarms_number ++;
						eeprom_update_data();
					}
				}
						/*Keys*/
				key = key_pad_pressed_key();
				if (key == 15)
				{
					tas.system_state = SS_KEY_CFG;
				}
				else if (key == 13)
				{
					tas_toggle_AA();
					tas_disp_AA();
					if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
					{
						tas_update_date();
						tas.system_state = SS_ALARM;
						tas.alarms_number ++;
						eeprom_update_data();
					}
				}
				else if (key == 14)
				{
					tas.system_state = SS_ALARM_HIS;
				}
						/*Terminal*/
				if (uart_receive_byte_unblock(UART_0,&data))
					{
						if (data == 'G')
						{
							tas.system_state = SS_TERM_CFG;
						}
					}	
			break;
			
			case SS_KEY_CFG:
			/*For each entry*/
			if (prev_state != SS_KEY_CFG)
			{
				prev_state = SS_KEY_CFG;
				tas_disp_state();
				//digit_ind = 0;
			}
			/*Keys*/
				key = key_pad_pressed_key();
				if (key == 12)
				{
					tas.system_state = SS_MAIN;
				}
				else if(key == 15)
				{
					threshold_temp = 0;			 /*remove*/
					for(ind = 0;ind < digit_ind;ind ++)
					{
						threshold_temp = threshold_temp*10 + digits[ind];
					}
					tas.thresh_temp = threshold_temp;
					int_eeprom_write_byte(0x00,tas.thresh_temp);
					
					if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
					{
						tas_update_date();
						tas.system_state = SS_ALARM;
						tas.alarms_number ++;
						eeprom_update_data();
					}
					else
					{
						tas.system_state = SS_MAIN;
					}
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
			break;
			
			case SS_TERM_CFG:
			/*For each entry*/
			if (prev_state != SS_TERM_CFG)
			{
				prev_state = SS_TERM_CFG;
				tas_disp_state();
				digit_ind = 0;
			}
			/*Keys*/
			if (uart_receive_byte_unblock(UART_0,&data))
			{
				if (data == 'C')
				{
					tas.system_state = SS_MAIN;
				}
				else if(data == 'O')
				{
					threshold_temp = 0; //remove
					for(ind = 0;ind < digit_ind;ind ++)
					{
						threshold_temp = threshold_temp*10 + digits[ind];
					}
					tas.thresh_temp = threshold_temp;
					int_eeprom_write_byte(0x00,tas.thresh_temp);
					
					if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
					{
						tas_update_date();
						tas.system_state = SS_ALARM;
						tas.alarms_number ++;
						eeprom_update_data();
					}
					else
					{
						tas.system_state = SS_MAIN;
					}
					
				}				
				else if((data >= '0') && (data <= '9') && (digit_ind < 3))
				{
					lcd_disp_charXY(DISP_LINE,DISP_IND_T+digit_ind,data);
					digits[digit_ind] = data - '0';
					digit_ind ++;
				}
			}
			break;
			
			case SS_ALARM:
			
			/*For each entry*/
			if (prev_state != SS_ALARM)
			{
				prev_state = SS_ALARM;
				delay_count = 0;
				tas_disp_state();
			}
			/*Alarm scenario*/
			if (delay_count >= 500UL)
			{
				delay_count = 0;
				buz_toggle();
				led_toggle();
				leds_toggle(0xff);
			}
			_delay_ms(50);
			delay_count += 50;
			/*C*/
			if (tas_update_C())
			{
				if (tas.current_temp < tas.thresh_temp)
				{
					tas.system_state = SS_MAIN;
				}
			}
			/*Key*/
			key = key_pad_pressed_key();
			if (key == 12)
			{
				tas.system_state = SS_MAIN;
				tas.alarm_act = NO;
			}
			/*Terminal*/
			if (uart_receive_byte_unblock(UART_0,&data))
			{
				if (data == 'S')
				{
					tas.system_state = SS_MAIN;
					tas.alarm_act = NO;
				}
			}
			/*Turn off the buzzer before state transition*/
			if (tas.system_state != SS_ALARM)
			{
				buz_off();
				led_off();
				leds_off(0xff);
				digit_ind = 0;
			}
			
			break;
			
			case SS_ALARM_HIS:
			/*For each entry*/
			if (prev_state != SS_ALARM_HIS)
			{
				prev_state = SS_ALARM_HIS;
				tas_disp_state();
				tas_disp_date();
				tas_disp_time();
				tas_disp_NA();
			}
			/*C*/
			if (tas_update_C())
			{
				if ((tas.current_temp >= tas.thresh_temp) && (tas.alarm_act == YES))
				{
					tas_update_date();
					tas.system_state = SS_ALARM;
					tas.alarms_number ++;
					eeprom_update_data();
				}
			}
			
			key = key_pad_pressed_key();
			if (key == 15)
			{
				tas.system_state = SS_MAIN;
			}
			if (key == 14)
			{
				tas.alarms_number = 0;
				int_eeprom_write_byte(0x01,tas.alarms_number);
				tas_disp_NA();
			}
			break;
		}
    }
}

#endif