#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include"clsString.h"


using namespace std;

class clsDate
{
	short _Year;
	short _Month;
	short _Day;

public:

	clsDate()
	{
		*this = getSystemDate();
	}

	clsDate(string strDate)
	{
		vector<string> vecDates = clsString::splitString(strDate, "/");

		_Day = stoi(vecDates[0]);
		_Month = stoi(vecDates[1]);
		_Year = stoi(vecDates[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrder, short Year)
	{
		*this = getDayOrderInYear(Year, DayOrder);
	}

	void setYear(short Year)
	{
		_Year = Year;
	}

	short getYear()
	{
		return _Year;
	}

	__declspec(property(get = getYear, put = setYear)) short Year;

	void setMonth(short Month)
	{
		_Month = Month;
	}

	short getMonth()
	{
		return _Month;
	}

	__declspec(property(get = getMonth, put = setMonth)) short Month;

	void setDay(short Day)
	{
		_Day = Day;
	}

	short getDay()
	{
		return _Day;
	}

	__declspec(property(get = getDay, put = setDay)) short Day;

	static string formatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		DateFormat.replace(DateFormat.find("yyyy"), 4, to_string(Date.Year));

		DateFormat.replace(DateFormat.find("mm"), 2, to_string(Date.Month));

		DateFormat.replace(DateFormat.find("dd"), 2, to_string(Date.Day));

		return DateFormat;
	}

	string formatDate(string DateFormat = "dd/mm/yyyy")
	{
		return formatDate(*this);
	}

	void Print()
	{
		cout << formatDate() << '\n';
	}

	static clsDate getSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;

		return clsDate(Day, Month, Year);
	}

	static bool isLeapYear(short Year)
	{
		return (!(Year % 400) || (!(Year % 4) && (Year % 100)));
	}

	bool isLeapYear()
	{
		return isLeapYear(_Year);
	}

	static clsDate getDayOrderInYear(short Year, short Days)
	{
		short Month = 1;
		short NumberOfDays;

		while (Days > (NumberOfDays = getNumberOfDaysInMonth(Year, Month)))
		{
			Days -= NumberOfDays;
			Month++;

			if (Month == 13)
			{
				Month = 1;
				Year++;
			}
		}

		return { Days, Month, Year };
	}

	static short getNumberOfDaysInYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}

	short getNumberOfDaysInYear()
	{
		return getNumberOfDaysInYear(_Year);
	}

	static short getNumberOfHoursInYear(short Year)
	{
		const short HourInDay = 24;

		return getNumberOfDaysInYear(Year) * HourInDay;
	}

	short getNumberOfHoursInYear()
	{
		return getNumberOfHoursInYear(_Year);
	}

	static int getNumberOfMinutesInYear(short Year)
	{
		const short MinutesInDay = 60;

		return getNumberOfHoursInYear(Year) * MinutesInDay;
	}

	int getNumberOfMinutesInYear()
	{
		return getNumberOfMinutesInYear(_Year);
	}

	static int getNumberOfSecondsInYear(short Year)
	{
		const short SecondsInMinute = 60;

		return getNumberOfMinutesInYear(Year) * SecondsInMinute;
	}

	int getNumberOfSecondsInYear()
	{
		return getNumberOfSecondsInYear(_Year);
	}

	static short getNumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month > 12)
			return 0;

		short NumberOfDays[] = { 0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return Month == 2 ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month];
	}

	short getNumberOfDaysInMonth()
	{
		return getNumberOfDaysInMonth(_Year, _Month);
	}

	static short getDayOrder(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
	}

	static short getDayOrder(clsDate Date)
	{
		return getDayOrder(Date.Day, Date.Month, Date.Year);
	}

	short getDayOrder()
	{
		return getDayOrder(_Day, _Month, _Year);
	}

	static string getDayText(short DayOrder)
	{
		string Days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

		return Days[DayOrder];
	}

	string getDayText()
	{
		return getDayText(getDayOrder());
	}

	static short getNumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short Sum = 0;

		for (short i = 1; i <= Month - 1; i++)
			Sum += getNumberOfDaysInMonth(Year, i);

		return Sum + Day;
	}

	short getNumberOfDaysFromTheBeginingOfTheYear()
	{
		return getNumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	static bool isDateBeforeDate2(clsDate Date1, clsDate Date2)
	{
		if (Date1.Year < Date2.Year)
			return true;
		else if (Date1.Year > Date2.Year)
			return false;
		else
		{
			if (Date1.Month < Date2.Month)
				return true;
			else if (Date1.Month > Date2.Month)
				return false;
			else
				return Date1.Day < Date2.Day;
		}
	}

	bool isDateBeforeDate2(clsDate Date2)
	{
		return isDateBeforeDate2(*this, Date2);
	}

	static bool isDateEqualToDate2(clsDate Date1, clsDate Date2)
	{
		return Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day;
	}

	bool isDateEqualToDate2(clsDate Date2)
	{
		return isDateEqualToDate2(*this, Date2);
	}

	static bool isDateAfterDate2(clsDate Date1, clsDate Date2)
	{
		return !isDateBeforeDate2(Date1, Date2) && !isDateEqualToDate2(Date1, Date2);
	}

	bool isDateAfterDate2(clsDate Date2)
	{
		return isDateAfterDate2(*this, Date2);
	}

	static bool isLastDayInMonth(clsDate Date)
	{
		return Date.Day == getNumberOfDaysInMonth(Date.Year, Date.Month);
	}

	bool isLastDayInMonth()
	{
		return isLastDayInMonth(*this);
	}

	static bool isLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	bool isLastMonthInYear()
	{
		return isLastMonthInYear(_Month);
	}

	static bool isValidDate(clsDate Date)
	{
		return (Date.Month > 0 && Date.Month < 13) && (Date.Day > 0 && Date.Day <= getNumberOfDaysInMonth(Date.Year, Date.Month)) && Date.Year > 0;
	}

	bool isValid()
	{
		return isValidDate(*this);
	}

	static bool isEndOfTheWeek(clsDate Date)
	{
		return getDayOrder(Date) == 6;
	}

	static bool isWeekend(clsDate Date)
	{
		short DayOrder = getDayOrder(Date);
		return DayOrder == 5 || DayOrder == 6;
	}

	bool isWeekend()
	{
		short DayOrder = getDayOrder();
		return DayOrder == 5 || DayOrder == 6;
	}

	static bool isBusinessDay(clsDate Date)
	{
		return !isWeekend(Date);
	}

	bool isBusinessDay()
	{
		return !isWeekend();
	}

	static clsDate addOneDay(clsDate Date)
	{
		if (isLastDayInMonth(Date))
		{
			Date.Day = 1;

			if (isLastMonthInYear(Date.Month))
			{
				Date.Year++;
				Date.Month = 1;
			}
			else
				Date.Month++;
		}
		else
			Date.Day++;

		return Date;
	}

	void addOneDay()
	{
		*this = addOneDay(*this);
	}

	static int calculateDiffrenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Counter = 0;

		while (isDateBeforeDate2(Date1, Date2))
		{
			Date1 = addOneDay(Date1);
			Counter++;
		}

		return IncludeEndDay ? ++Counter : Counter;
	}

	int calculateDiffrenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return calculateDiffrenceInDays(*this, Date2, IncludeEndDay);
	}

	static string getMonthText(short MonthOrder)
	{
		string Months[] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		return Months[MonthOrder];
	}

	static void printMonthCalendar(short Month, short Year)
	{
		short StartOfMonth = getDayOrder(1, Month, Year);
		short DaysOfMonth = getNumberOfDaysInMonth(Year, Month);

		cout << "\n\n_______________" << getMonthText(Month) << "_______________\n\n";
		cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		int j = StartOfMonth;

		for (short i = 0; i < StartOfMonth; i++)
			cout << "     ";

		for (int i = 1; i <= DaysOfMonth; i++)
		{
			printf("%3d  ", i);
			j++;

			if (j % 7 == 0 && i < DaysOfMonth)
				printf("\n");
		}

		cout << "\n_________________________________" << endl;
	}

	void printMonthCalendar()
	{
		printMonthCalendar(_Month, _Year);
	}

	static int calculateMyAgeInDays(clsDate DateOfBirth)
	{
		return calculateDiffrenceInDays(DateOfBirth, getSystemDate());
	}

	static clsDate increaseDateByXDays(clsDate Date, int Days)
	{
		for (int i = 0; i < Days; i++)
			Date = addOneDay(Date);

		return Date;
	}

	void addXDays(int Days)
	{
		*this = increaseDateByXDays(*this, Days);
	}

	static clsDate increaseDateByOneWeek(clsDate Date)
	{
		return increaseDateByXDays(Date, 7);
	}

	void addOneWeek()
	{
		*this = increaseDateByOneWeek(*this);
	}

	static clsDate increaseDateByXWeeks(clsDate Date, int Week)
	{
		for (int i = 0; i < Week; i++)
			Date = increaseDateByOneWeek(Date);

		return Date;
	}

	void addXWeeks(int Week)
	{
		*this = increaseDateByXWeeks(*this, Week);
	}

	static clsDate increaseDateByOneMonth(clsDate Date)
	{
		if (isLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;

		short NumberOfDaysInMonth = getNumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInMonth)
			Date.Day = NumberOfDaysInMonth;

		return Date;
	}

	void addOneMonth()
	{
		*this = increaseDateByOneMonth(*this);
	}

	static clsDate increaseDateByXMonths(clsDate Date, int NumberOfMonths)
	{
		for (int i = 0; i < NumberOfMonths; i++)
			Date = increaseDateByOneMonth(Date);

		return Date;
	}

	void addXMonths(int Months)
	{
		*this = increaseDateByXMonths(*this, Months);
	}

	static clsDate increaseDateByOneYear(clsDate Date)
	{
		Date.Year++;
		return Date;
	}

	void addOneYear()
	{
		*this = increaseDateByOneYear(*this);
	}

	static clsDate increaseDateByXYears(clsDate Date, int NumberOfYears)
	{
		Date.Year += NumberOfYears;
		return Date;
	}

	void addXYears(int Years)
	{
		*this = increaseDateByXYears(*this, Years);
	}

	static clsDate increaseDateByOneDecade(clsDate Date)
	{
		Date.Year += 10;
		return Date;
	}

	void addOneDecade()
	{
		*this = increaseDateByOneDecade(*this);
	}

	static clsDate increaseDateByXDecades(clsDate Date, int NumberOfDecades)
	{
		Date.Year += NumberOfDecades * 10;

		return Date;
	}

	void addXDecades(int Decades)
	{
		*this = increaseDateByXDecades(*this, Decades);
	}

	static clsDate increaseDateByOneCentury(clsDate Date)
	{
		Date.Year += 100;
		return Date;
	}

	void addOneCentury()
	{
		*this = increaseDateByOneCentury(*this);
	}

	static clsDate increaseDateByOneMillennium(clsDate Date)
	{
		Date.Year += 1000;
		return Date;
	}

	void addOneMillennium()
	{
		*this = increaseDateByOneMillennium(*this);
	}

	static clsDate decreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day > 1)
			Date.Day--;
		else
		{
			if (Date.Month > 1)
				Date.Month--;
			else
			{
				Date.Year--;
				Date.Month = 12;
			}

			Date.Day = getNumberOfDaysInMonth(Date.Year, Date.Month);
		}

		return Date;
	}

	void subtractOneDay()
	{
		*this = decreaseDateByOneDay(*this);
	}

	static clsDate decreaseDateByXDays(clsDate Date, int Days)
	{
		for (int i = 0; i < Days; i++)
			Date = decreaseDateByOneDay(Date);

		return Date;
	}

	void subtractXDays(int Days)
	{
		*this = increaseDateByXDays(*this, Days);
	}

	static clsDate decreaseDateByOneWeek(clsDate Date)
	{
		return decreaseDateByXDays(Date, 7);
	}

	void subtractOneWeek()
	{
		*this = decreaseDateByOneWeek(*this);
	}

	static clsDate decreaseDateByXWeeks(clsDate Date, int Week)
	{
		for (int i = 0; i < Week; i++)
			Date = decreaseDateByOneWeek(Date);

		return Date;
	}

	void subtractXWeeks(int Weeks)
	{
		*this = decreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate decreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month > 1)
			Date.Month--;
		else
		{
			Date.Month = 12;
			Date.Year--;
		}

		short NumberOfDaysInMonth = getNumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInMonth)
			Date.Day = NumberOfDaysInMonth;

		return Date;
	}

	void subtractOneMonth()
	{
		*this = decreaseDateByOneMonth(*this);
	}

	static clsDate decreaseDateByXMonths(clsDate Date, int NumberOfMonths)
	{
		for (int i = 0; i < NumberOfMonths; i++)
			Date = decreaseDateByOneMonth(Date);

		return Date;
	}

	void subtractXMonths(int Months)
	{
		*this = decreaseDateByXMonths(*this, Months);
	}

	static clsDate decreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;
		return Date;
	}

	void subtractOneYear()
	{
		*this = decreaseDateByOneYear(*this);
	}

	static clsDate decreaseDateByXYears(clsDate Date, int NumberOfYears)
	{
		Date.Year -= NumberOfYears;
		return Date;
	}

	void subtractXYears(int Years)
	{
		*this = decreaseDateByXYears(*this, Years);
	}

	static clsDate decreaseDateByOneDecade(clsDate Date)
	{
		Date.Year -= 10;
		return Date;
	}

	void subtractOneDecade()
	{
		*this = decreaseDateByOneDecade(*this);
	}

	static clsDate decreasDateByXDecades(clsDate Date, int NumberOfDecades)
	{
		Date.Year -= NumberOfDecades * 10;
		return Date;
	}

	void subtractXDecades(int Decades)
	{
		*this = decreasDateByXDecades(*this, Decades);
	}

	static clsDate decreaseDateByOneCentury(clsDate Date)
	{
		Date.Year -= 100;
		return Date;
	}

	void subtractOneCentury()
	{
		*this = decreaseDateByOneCentury(*this);
	}

	static clsDate decreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;
		return Date;
	}

	void subtractOneMillennium()
	{
		*this = decreaseDateByOneMillennium(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - getDayOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return getNumberOfDaysInMonth(Date.Year, Date.Month) - Date.Day;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		short Sum = DaysUntilTheEndOfMonth(Date);

		for (short i = Date.Month + 1; i <= 12; i++)
			Sum += getNumberOfDaysInMonth(Date.Year, Date.Month);

		return Sum;
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static string getSystemTime()
	{
		time_t t = time(0); 
		tm* now = localtime(&t);

		return to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":"
			+ to_string(now->tm_sec);
	}

	static string getSystemDateAndTime()
	{
		return formatDate(clsDate()) + " - " + getSystemTime();
	}
};