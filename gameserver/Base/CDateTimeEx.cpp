/*
 * CDateTimeEx.cpp
 *
 *  Created on: 2017年4月9日
 *      Author: aaaa
 */

#include "CDateTimeEx.h"


#include "string.h"
#include "stdio.h"

CDateTimeEx::CDateTimeEx(void)
{
}

CDateTimeEx::~CDateTimeEx(void)
{
}

void CDateTimeEx::GetLocalTimeEx(SYSTEMTIME *st)
{
    if(st)
    {
        struct tm *pst = NULL;
        time_t t = time(NULL);
        pst = localtime(&t);
        memcpy(st,pst,sizeof(SYSTEMTIME));
        st->wYear += 1900;
    }
}
void CDateTimeEx::GetDateTime()
{
	szTimebuf[0] = 0;
	GetLocalTimeEx( &m_DateTime );
	this->wDay = m_DateTime.wDay;
	this->wDayOfWeek = m_DateTime.wDayOfWeek;
	this->wHour = m_DateTime.wHour;
	this->wMilliseconds = m_DateTime.wMilliseconds;
	this->wMinute = m_DateTime.wMinute;
	this->wMonth = m_DateTime.wMonth;
	this->wSecond = m_DateTime.wSecond;
	this->wYear = m_DateTime.wYear;
}

void CDateTimeEx::AddSecond( int n )
{
	int iSecond = wSecond;
	wSecond = ( iSecond + n ) % 60;
	AddMinute( (iSecond + n) / 60 );
}
void CDateTimeEx::AddMinute( int n )
{
	int iMinute = wMinute;
	wMinute = ( iMinute + n ) % 60;
	AddHour( ( iMinute + n ) / 60 );

}
void CDateTimeEx::AddHour( int n )
{
	int iHour = wHour;
	wHour = ( iHour + n ) % 24;
	AddDays( ( iHour + n ) / 24 );

}
void CDateTimeEx::AddDays( int n )
{
	for( int i = 0; i < n; i++ )
	{
		if( wDay + 1 > GetDaysOfMonth( this, wMonth ))
		{
			wDay = 1;
			AddMonth( );
		}
		else
		{
			wDay = wDay + 1;
		}

	}

	AddDayOfWeek( n );

}
void CDateTimeEx::AddDayOfWeek( int n )
{
	int wDayOfWeeks = wDayOfWeek;
	wDayOfWeek = ( wDayOfWeeks + n ) % 7;
}
void CDateTimeEx::AddMonth( int n )
{
	int iMonth = wMonth;
	wMonth = ( iMonth - 1 + n ) % 12 + 1;
	AddYear( ( iMonth - 1 + n ) / 12 );
}
void CDateTimeEx::AddYear( int n )
{
	wYear += n;
}
//比较两个日期的时间部分（小时，分，秒）（返回0,1,2分别为相等，大于，小于）
int CDateTimeEx::CompareTime( CDateTimeEx * time )
{
	if( this->wHour > time->wHour )
		return 1;
	else if( this->wHour == time->wHour && this->wMinute > time->wMinute )
		return 1;
	else if( this->wHour == time->wHour && this->wMinute == time->wMinute && this->wSecond > time->wSecond )
		return 1;
	else if( this->wHour == time->wHour && this->wMinute == time->wMinute && this->wSecond == time->wSecond )
		return 0;
	else
		return 2;
}
bool CDateTimeEx::operator > ( CDateTimeEx & time)
{
	if( this->wYear > time.wYear )
		return true;
	else if( this->wYear == time.wYear && this->wMonth > time.wMonth )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay > time.wDay )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour > time.wHour )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour == time.wHour && this->wMinute > time.wMinute )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour == time.wHour && this->wMinute == time.wMinute && this->wSecond > time.wSecond )
		return true;
	else
		return false;
}
bool CDateTimeEx::operator < ( CDateTimeEx & time)
{
	if( this->wYear < time.wYear )
		return true;
	else if( this->wYear == time.wYear && this->wMonth < time.wMonth )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay < time.wDay )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour < time.wHour )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour == time.wHour && this->wMinute < time.wMinute )
		return true;
	else if( this->wYear == time.wYear && this->wMonth == time.wMonth && this->wDay == time.wDay && this->wHour == time.wHour && this->wMinute == time.wMinute && this->wSecond < time.wSecond )
		return true;
	else
		return false;
}
void CDateTimeEx::operator = ( CDateTimeEx &times )
{
	this->wYear = times.wYear;
	this->wMonth = times.wMonth;
	this->wDay = times.wDay;
	this->wHour = times.wHour;
	this->wMinute = times.wMinute;
	this->wSecond = times.wSecond;
}

void CDateTimeEx::SetSecond( int n )
{
	this->wSecond = n;
}
void CDateTimeEx::SetMinute( int n )
{
	this->wMinute = n;
}
void CDateTimeEx::SetHour( int n )
{
	this->wHour = n;
}
void CDateTimeEx::SetDayOfWeek( int n )
{
	this->wDayOfWeek = n;
}
void CDateTimeEx::SetDays( int n )
{
	this->wDay = n;
}
void CDateTimeEx::SetMonth( int n )
{
	this->wMonth = n;
}
void CDateTimeEx::SetYear( int n )
{
	this->wYear = n;
}
char * CDateTimeEx::ToStringEx()
{
	sprintf(szTimebuf, "%4d-%02d-%02d %02d:%02d", wYear, wMonth, wDay, wHour, wMinute);

	return szTimebuf;
}

int CDateTimeEx::GetSecond(  )
{
	return wSecond;
}
int CDateTimeEx::GetMinute(  )
{
	return wMinute;
}
int CDateTimeEx::GetHour(  )
{
	return wHour;
}
int CDateTimeEx::GetDays(  )
{
	return wDay;
}
int CDateTimeEx::GetMonth(  )
{
	return wMonth;
}
int CDateTimeEx::GetYear(  )
{
	return wYear;
}
int CDateTimeEx::GetDayOfWeek()
{
	return wDayOfWeek;
}

//获取这个月有几天
int	CDateTimeEx::GetDaysOfMonth( CDateTimeEx * datetime, int iMonth )
{
	CDateTimeEx * time = datetime;

	int idays = 0;
	switch( iMonth )
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		{
			idays = 31;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		{
			idays = 30;
		}
		break;
	case 2:
		{
			if( time->wYear % 4 == 0 && time->wYear % 100 != 0 || time->wYear % 400 == 0 )
				idays = 29;
			else
				idays = 28;
		}
		break;
	}
	return idays;
}
