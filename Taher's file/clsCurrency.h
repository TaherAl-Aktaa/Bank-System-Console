#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include"clsString.h"
#include<string>

using namespace std;

class clsCurrency
{
private:

	enum enMode { Empty, Update };

	enMode _Mode;
	string _Country;
	string _Code;
	string _Name;
	float _Rate;

	static clsCurrency _convertDataLineToCurrency(string DataLine)
	{
		vector<string> vData = clsString::splitString(DataLine, "#//#");

		return clsCurrency(enMode::Update, vData[0], vData[1], vData[2], stof(vData[3]));
	}

	string _convertCurrencyToDataLine(clsCurrency Currency, string Sperator = "#//#")
	{
		string DataLine;

		DataLine += Currency.Country() + Sperator;
		DataLine += Currency.Code() + Sperator;
		DataLine += Currency.Name() + Sperator;
		DataLine += to_string(Currency.Rate()) + Sperator;

		return DataLine;
	}

	static vector<clsCurrency> _loadCurrenciesDataFromFile()
	{
		vector<clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
				vCurrencies.push_back(_convertDataLineToCurrency(DataLine));
			
			MyFile.close();
		}

		return vCurrencies;
	}

	void _saveCurrenciesDataToFile(vector <clsCurrency>& vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency& C : vCurrencies)
				MyFile << _convertCurrencyToDataLine(C) << '\n';
			

			MyFile.close();
		}
	}

	void _update()
	{
		vector <clsCurrency> vCurrencies = _loadCurrenciesDataFromFile();

		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.Code() == Code())
			{
				Currency = *this;
				break;
			}
		}

		_saveCurrenciesDataToFile(vCurrencies);
	}

	static clsCurrency _getEmptyObj()
	{
		return clsCurrency(enMode::Empty, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode,
		string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_Code = CurrencyCode;
		_Name = CurrencyName;
		_Rate = Rate;
	}

	bool empty()
	{
		return _Mode == enMode::Empty;
	}

	string Country()
	{
		return _Country;
	}

	string Code()
	{
		return _Code;
	}

	string Name()
	{
		return _Name;
	}

	float Rate()
	{
		return _Rate;
	}

	void updateRate(float Rate)
	{
		_Rate = Rate;
		_update();
	}

	static clsCurrency findByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::upperString(CurrencyCode);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsCurrency Currency = _convertDataLineToCurrency(DataLine);

				if (Currency.Code() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

		return _getEmptyObj();
	}

	static clsCurrency findByCountry(string Country)
	{
		Country = clsString::lowerString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsCurrency Currency = _convertDataLineToCurrency(DataLine);

				if (clsString::lowerString(Currency.Country()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
		}

		return _getEmptyObj();
	}

	static bool doesCurrencyExist(string CurrencyCode)
	{
		return !findByCode(CurrencyCode).empty();
	}

	static vector <clsCurrency> getCurrenciesList()
	{
		return _loadCurrenciesDataFromFile();
	}

	double convertToUSD(float Amount)
	{
		return Amount / Rate();
	}

	double convertToCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = convertToUSD(Amount);

		if (Currency2.Code() == "USD")
			return AmountInUSD;

		return AmountInUSD * Currency2.Rate();
	}
};

