#pragma once
#include<iostream>
#include"clsDate.h"

using namespace std;

template <typename Type> class clsInputValidate
{
	
public:

	static bool isNumberBetween(Type Number, Type From, Type To)
	{
		return Number >= From && Number <= To;
	}

	static bool isDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::isDateAfterDate2(From, To))
			swap(From, To);

		// From <= Date && Date <= To
		return (clsDate::isDateBeforeDate2(From, Date) || clsDate::isDateEqualToDate2(From, Date)) && (clsDate::isDateBeforeDate2(Date, To) || clsDate::isDateEqualToDate2(Date, To));
	}

	static string readString()
	{
		string s;
		getline(cin >> ws, s);

		return s;
	}

	static Type readNumber(string Message = "Invalid number, Enter a vaild one : ")
	{
		Type Number;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << Message;
		}

		return Number;
	}

	static Type readNumberBetween(Type From, Type To, string Message)
	{
		Type Number;

		do
		{
			cout << Message;
			Number = readNumber("Invalid number, Enter another one : ");
		} while (!isNumberBetween(Number, From, To));

		return Number;
	}

	static bool isValidDate(clsDate Date)
	{
		return (Date.Month > 0 && Date.Month < 13) && (Date.Day > 0 && Date.Day <= Date.getNumberOfDaysInMonth());
	}
};