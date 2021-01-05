/*
 * temp_alarm_sys_n.h
 *
 * Created: 6/9/2020 11:33:44 AM
 *  Author: H
 */ 


#ifndef TAS_H_
#define TAS_H_

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
	SS_NONE,SS_MAIN,SS_KEY_CFG,SS_TERM_CFG,SS_ALARM,SS_ALARM_HIS
}system_state_t;

typedef enum
{
	YES = 'Y',NO = 'N'
}alarm_act_t;

typedef struct
{
	system_state_t	system_state;		/*SS*/
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

void tas_init(void);
/* Displaying */
void tas_disp_AA(void);
void tas_disp_C(void);
void tas_disp_T(void);
void tas_disp_state(void);
void tas_disp_NA(void);
void tas_disp_date(void);
void tas_disp_time(void);
/* TAS Structure Manipulation */
Bool tas_update_C(void);
void tas_toggle_AA(void);
void tas_update_date(void);
void eeprom_update_data(void);
void eeprom_data_backup(void);



//void tas_disp_param(void);
#endif /* TAS_H_ */