/*
 * CDateTimeEx.h
 *
 *  Created on: 2017年4月9日
 *      Author: aaaa
 */

#ifndef CDATETIMEEX_H_
#define CDATETIMEEX_H_

#include "time.h"
#include <string>
using namespace std;

typedef struct {

	int wMilliseconds;
	int wSecond; /* Seconds.	 [0-60] (1 leap second) */
	int wMinute; /* Minutes.	 [0-59] */
	int wHour; /* Hours.	 [0-23] */
	int wDay; /* Day.		 [1-31] */
	int wMonth; /* Month.	 [0-11] */
	int wYear; /* Year	 - 1900.  */
	int wDayOfWeek; /* Day of week.	 [0-6] */
	int tm_yday; /* Days in year.[0-365]	 */
	int tm_isdst; /* DST.		 [-1/0/1]*/
#ifdef	 __USE_BSD
	long int tm_gmtoff; /* Seconds east of UTC.  */
	__const char *tm_zone; /* Timezone abbreviation.  */
#else
	long int __tm_gmtoff; /* Seconds east of UTC.  */
	__const char *__tm_zone; /* Timezone abbreviation.  */
#endif
} SYSTEMTIME;

class CDateTimeEx: public SYSTEMTIME {
public:
	CDateTimeEx(void);
	~CDateTimeEx(void);

	void GetDateTime();

	char * ToStringEx();

	void AddSecond(int n = 1);
	void AddMinute(int n = 1);
	void AddHour(int n = 1);
	void AddDays(int n = 1);
	void AddMonth(int n = 1);
	void AddYear(int n = 1);
	int GetDaysOfMonth(CDateTimeEx * datetime, int n);

	bool operator >(CDateTimeEx &times);
	void operator =(CDateTimeEx &times);
	bool operator <(CDateTimeEx & time);
	int CompareTime(CDateTimeEx * time);

	void SetSecond(int n);
	void SetMinute(int n);
	void SetHour(int n);
	void SetDays(int n);
	void SetMonth(int n);
	void SetYear(int n);
	void SetDayOfWeek(int n);

	int GetSecond();
	int GetMinute();
	int GetHour();
	int GetDays();
	int GetMonth();
	int GetYear();
	int GetDayOfWeek();

	void GetLocalTimeEx(SYSTEMTIME *st);
private:
	SYSTEMTIME m_DateTime;

	char szTimebuf[256];

	void AddDayOfWeek(int n);
};

#endif /* CDATETIMEEX_H_ */
