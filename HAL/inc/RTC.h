/*
 * RTC.h
 *
 * Created: 6/8/2020 3:23:43 PM
 *  Author: H
 */ 


#ifndef RTC_H_
#define RTC_H_

#include "TWI.h"

#define RTC_SLA_W	0B11010000
#define RTC_SLA_R	0B11010001

typedef struct
{
	U_8 rtc_reg_val[7];
	U_8 rtc_time[9];		/*10:20:23 (\n)*/
	U_8 rtc_date[11];		 /*10/11/2020*/
}RTC_STRUCT;

void rtc_init(void);
RTC_STRUCT* rtc_update(void);



#endif /* RTC_H_ */