/*
 * RTC.c
 *
 * Created: 6/8/2020 3:23:57 PM
 *  Author: H
 */ 
#include "RTC.h"

static RTC_STRUCT rtc  = {{0},"hh:mm:ss","dd/mm/20yy"} ;
U_8 rtc_registers[7] = {0};

void rtc_init(void)
{
	twi_init();
	/*WRITE : , / IN time and data*/
	//rtc->rtc_date[2] = ':';
	//rtc->rtc_date[5] = ':';
}

RTC_STRUCT* rtc_update(void)
{
	U_8 ind = 0;
	U_8 data = 0;
	
	twi_start();
	twi_write_byte(RTC_SLA_W,SC_MT_SLA_ACK);
	twi_write_byte(0X00,SC_MT_DATA_ACK);
	twi_restart();
	twi_write_byte(RTC_SLA_R,SC_MR_SLA_ACK);
	for(ind = 0;ind < 6; ind ++)
	{
		twi_read_byte(&data,SC_MR_DATA_ACK);
		rtc_registers[ind] = data;
	}
	twi_read_byte(&data,SC_MR_DATA_NOTACK);
	twi_stop();
	rtc_registers[ind] = data;
	/*Convert*/
	/*Seconds*/
	rtc.rtc_reg_val[0] =    rtc_registers[0]&0X0F;
	rtc.rtc_reg_val[0] +=  ((rtc_registers[0]&0X70)>>4)*10;
	rtc.rtc_time[7]	= (rtc_registers[0] & 0x0F) + '0';			/*"hh:mm:ss"*/
	rtc.rtc_time[6] = (((rtc_registers[0] & 0x70)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Minutes*/
	rtc.rtc_reg_val[1] =	rtc_registers[1]&0X0F;
	rtc.rtc_reg_val[1] += ((rtc_registers[1]&0X70)>>4)*10;
	rtc.rtc_time[4]	= (rtc_registers[1] & 0x0F) + '0';			/*"hh:mm:ss"*/
	rtc.rtc_time[3] = (((rtc_registers[1] & 0x70)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Hours*/
	rtc.rtc_reg_val[2] =	rtc_registers[2]&0X0F;
	rtc.rtc_reg_val[2] += ((rtc_registers[2]&0X70)>>4)*10;
	rtc.rtc_time[1]	= (rtc_registers[2] & 0x0F) + '0';			/*"hh:mm:ss"*/
	rtc.rtc_time[0] = (((rtc_registers[2] & 0x30)>>4)) + '0';	/*"hh:mm:ss"*/
	/*Nth day in a week, starting by 1 = Sunday and So on i.e 1-7*/
	rtc.rtc_reg_val[3] = rtc_registers[3] & 0x07;
	/*Day in a month from 1-31 */
	rtc.rtc_reg_val[4] = rtc_registers[4] & 0x0F;
	rtc.rtc_reg_val[4] += ((rtc_registers[4] & 0x30)>>4)*10;
	rtc.rtc_date[1] = (rtc_registers[4] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	rtc.rtc_date[0] = ((rtc_registers[4] & 0x30)>>4) + '0';			/*"dd/mm/20yy"*/
	/*month in a year from 1-12 */
	rtc.rtc_reg_val[5] = rtc_registers[5] & 0x0F;
	rtc.rtc_reg_val[5] += ((rtc_registers[5] & 0x10)>>4)*10;
	rtc.rtc_date[4] = (rtc_registers[5] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	rtc.rtc_date[3] = ((rtc_registers[5] & 0x10)>>4) + '0';			/*"dd/mm/20yy"*/
	/*least two digits in a 20xx years  00-99, ex: the year 2023 is just 23*/
	rtc.rtc_reg_val[6] = rtc_registers[6] & 0x0F;
	rtc.rtc_reg_val[6] += ((rtc_registers[6] & 0xF0)>>4)*10;
	rtc.rtc_date[9] = (rtc_registers[6] & 0x0F) + '0';				/*"dd/mm/20yy"*/
	rtc.rtc_date[8] = ((rtc_registers[6] & 0xF0)>>4) + '0';			/*"dd/mm/20yy"*/
	
	/*Return the add*/
	return	&rtc;
}