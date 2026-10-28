#pragma once
#include"clsScreen.h"
#include"clsCurrency.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:

	static string _readCurrencyCode(string Message)
	{
		string CurrencyCode;

		while (true)
		{
			cout << Message;
			cin >> CurrencyCode;

			if (clsCurrency::doesCurrencyExist(CurrencyCode))
				return CurrencyCode;

			cout << "\nCurrency with code[" + CurrencyCode + "] does NOT exist.\n\n";
		}
	}

	static void _printCurrency(clsCurrency Currency)
	{
		cout << "------------------------------------------\n";
		cout << setw(10) << left << "Country" << ": " << Currency.Country() << '\n';
		cout << setw(10) << left << "Code" << ": " << Currency.Code() << '\n';
		cout << setw(10) << left << "Name" << ": " << Currency.Name() << '\n';
		cout << setw(10) << left << "Rate (1$)" << ": " << Currency.Rate() << '\n';
		cout << "------------------------------------------\n" << endl;
	}

	static void _exchange(clsCurrency From, clsCurrency To, double Amount)
	{
		if (From.Code() != "USD" && To.Code() != "USD")
		{
			clsCurrency USD = clsCurrency::findByCode("USD");

			_exchange(From, USD, Amount);
			_exchange(USD, To, From.convertToUSD(Amount));
			return;
		}

		cout << "\nConvert From\n\n";
		_printCurrency(From);

		cout << "\nConvert To\n\n";
		_printCurrency(To);

		cout << Amount  << ' ' << From.Code() << " = " << From.convertToCurrency(Amount, To) << ' ' << To.Code() << '\n';
	}

public:

	static void showCurrencyCalculatorScreen()
	{
		while (true)
		{
			system("cls");
			_drawScreenHeader("\t  Currency Calculator");

			cout << "\nEnter the code of the currency you want to convert form\n\n";
			clsCurrency CurrencyFrom = clsCurrency::findByCode(_readCurrencyCode("Convert from : "));

			cout << "\nEnter the code of the currency you want to convert to\n\n";
			clsCurrency CurrencyTo = clsCurrency::findByCode(_readCurrencyCode("Convert to : "));

			cout << "\nExchange Amount : ";
			double AmountToExchange = clsInputValidate<double>::readNumber();

			_exchange(CurrencyFrom, CurrencyTo, AmountToExchange);

			char ch;

			cout << "\nDo you want to peform another calculation ? [ y / n ] : ";
			cin >> ch;

			if (tolower(ch) != 'y')
				break;
		}
	}
};

