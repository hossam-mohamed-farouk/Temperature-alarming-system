/*
 * temperature_alarming_system.c
 *
 * Created: 6/6/2020 12:58:28 AM
 * Author : H
 */ 
#define  tasm_f	1
#if		 tasm_f

#include "temp_alarm_sys_with_RTOS.h"

/*Var maybe use it*/
/*
	system_state_t prev_state = SS_NONE;
	U_8 key = 0;
	U_8 digit_ind = 0;
	U_8 data = 0;
	U_32 delay_count = 0;
	U_8 threshold_temp = 0;
	U_8 digits[3]={0};
	U_8 ind = 0;	
*/

extern tas_struct tas;
extern EventGroupHandle_t	egTAS;
//extern EventBits_t			ebTAS;

int main(void)
{
	/*init the system*/
	system_init();
	/*OS services create and init*/
	egTAS = xEventGroupCreate();
	
	/*Tasks creation*/
	xTaskCreate(T_display, "T_display", 100, NULL, 3, NULL);
	xTaskCreate(T_get_temp, "T_get_temp", 100, NULL, 4, NULL);
	xTaskCreate(T_check, "T_check", 100, NULL, 5, NULL);
	xTaskCreate(T_key_handler, "T_key_handler", 100, NULL, 2, NULL);
	xTaskCreate(T_threshold_t_config, "T_threshold_t_config", 100, NULL, 1, NULL);
	xTaskCreate(T_alarming, "T_alarming", 100, NULL, 6, NULL);
	/*start os or sched*/	vTaskStartScheduler();
}


#endif