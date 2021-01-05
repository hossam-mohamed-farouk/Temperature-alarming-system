/*
 * temp_alarm_sys_with_RTOS.h
 *
 * Created: 7/11/2020 1:27:10 PM
 *  Author: H
 */ 


#ifndef TEMP_ALARM_SYS_WITH_RTOS_H_
#define TEMP_ALARM_SYS_WITH_RTOS_H_

/*FreeRTOS files*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
/*include our drivers*/
#include "stdio.h"
#include <avr/io.h>
#include "board.h"
#include "key_pad.h"
#include "lcd.h"
#include "adc_bitfield.h"
#include "lm_35_temp_sens.h"
#include "uart.h"
#include "internal_eeprom.h"
#include "RTC.h"

typedef enum
{
	YES = 'Y',NO = 'N'
}alarm_act_t;

typedef struct
{
	//system_state_t	system_state;		/*SS*/
	alarm_act_t		alarm_act;			/*AA*/
	U_8				current_temp;		/*C*/
	U_8				thresh_temp;		/*T*/
	
	U_8				alarms_number;		/*NA*/
	U_8				la_time[9];			/*10:20:23 (\n)*/
	U_8				la_date[11];		 /*10/11/2020*/
}tas_struct;

#define		DISP_MAIN_S_L1					"C:    T:    AA: "
#define		DISP_MAIN_S_L2					"K15 T:G AC13 H14"

#define		DISP_ALARM_S_L1					"    ALARMING    "
#define		DISP_ALARM_S_L2					"  KAD:12 TAD:S  "

#define		DISP_KEY_CFG_S_L1				"      T:        "
#define		DISP_KEY_CFG_S_L2				"  OK:15 CN:12   "

#define		DISP_TER_CFG_S_L1				"      T:        "
#define		DISP_TER_CFG_S_L2				"   OK:O CN:C    "

#define		DISP_ALARM_HISTORY_S_L1			"   -  -     :   "
#define		DISP_ALARM_HISTORY_S_L2			"AN:  AC:14 OK:15"

#define     DISP_LINE				1
#define     DISP_IND_C				3
#define     DISP_IND_T				9
#define     DISP_IND_AA				16

#define     DISP_IND_NA				4
#define     DISP_IND_D				2
#define     DISP_IND_M				5
#define     DISP_IND_Y				8
#define     DISP_IND_H				11
#define     DISP_IND_MIN			14

/*tasks prototypes*/
void system_init(void);

void T_display(void *pvData);
void T_get_temp(void *pvData);
void T_check(void *pvData);
void T_key_handler(void *pvData);
void T_threshold_t_config(void *pvData);
void T_alarming(void *pvData);

/*TAS prototypes*/
Bool tas_update_C(void);
void tas_toggle_AA(void);

/* Displaying */
void tas_disp_AA(void);
void tas_disp_C(void);
void tas_disp_TH(void);
void tas_disp_M(void);
void tas_disp_K_C(void);
void tas_disp_T_C(void);
void tas_disp_A(void);





#endif /* TEMP_ALARM_SYS_WITH_RTOS_H_ */