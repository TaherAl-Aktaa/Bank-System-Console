#pragma once
#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"

class clsFindCurrencyScreen : protected clsScreen
{
private:

	enum enFindCurrencyOption { ByCode, ByCountry };

	static enFindCurrencyOption _readFindOption()
	{
		short Option = clsInputValidate<short>::readNumberBetween(1, 2, "\nFind by, [1] Code or [2] Country : ");;

		return enFindCurrencyOption(Option - 1);
	}

	static void _printCurrency(clsCurrency Currency)
	{
		cout << "Currency card : \n\n";
		cout << "------------------------------------------\n";
		cout << setw(10) << left << "Country" << ": " << Currency.Country() << '\n';
		cout << setw(10) << left << "Code" << ": " << Currency.Code() << '\n';
		cout << setw(10) << left << "Name" << ": " << Currency.Name() << '\n';
		cout << setw(10) << left << "Rate (1$)" << ": " << Currency.Rate() << '\n';
		cout << "------------------------------------------\n" << endl;
	}

	static void _printResult(clsCurrency Currency)
	{
		if (Currency.empty())
			cout << "\n\nCurrency was NOT found.\n" << endl;
		else
		{
			cout << "\nCurrency was found.\n\n";
			_printCurrency(Currency);
		}
	}

public:

	static void showFindCurrencyScreen()
	{
		_drawScreenHeader("\t     Find Currency");

		enFindCurrencyOption Option = _readFindOption();

		switch (Option)
		{
		case clsFindCurrencyScreen::ByCode:
		{
			cout << "\nCurrency code : ";
			string CurrencyCode = clsInputValidate<string>::readString();

			clsCurrency Currency = clsCurrency::findByCode(CurrencyCode);

			_printResult(Currency);

			break;
		}
		case clsFindCurrencyScreen::ByCountry:
		{
			cout << "\nCurrency Country : ";
			string CurrencyCountry = clsInputValidate<string>::readString();

			clsCurrency Currency = clsCurrency::findByCountry(CurrencyCountry);

			_printResult(Currency);

			break;
		}
		default:
			break;
		}
	}
};

