#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"

class clsUpdateRateScreen : protected clsScreen
{
private:

	static void _printCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency card : \n\n";
		cout << "------------------------------------------\n";
		cout << setw(10) << left << "Country" << ": " << Currency.Country() << '\n';
		cout << setw(10) << left << "Code" << ": " << Currency.Code() << '\n';
		cout << setw(10) << left << "Name" << ": " << Currency.Name() << '\n';
		cout << setw(10) << left << "Rate (1$)" << ": " << Currency.Rate() << '\n';
		cout << "------------------------------------------\n" << endl;
	}

public:

	static void showUpdateRateScreen()
	{
		_drawScreenHeader("\t      Update Rate");

		cout << "\nEnter the currency code you want to update\n\n";
		string CurrencyCode;

		while (true)
		{
			cout << "Currency code : ";
			CurrencyCode = clsInputValidate<string>::readString();

			if (clsCurrency::doesCurrencyExist(CurrencyCode))
				break;

			cout << "\nCurrency with code [" + CurrencyCode + "] does NOT exist.\n\n";
		}
		
		clsCurrency Currency = clsCurrency::findByCode(CurrencyCode);
		_printCurrency(Currency);

		cout << "\nAre you sure you want to update the rate of this currency ?, [ y - n ] : ";
		char Check;
		cin >> Check;

		if (tolower(Check) != 'y')
			return;

		cout << "\n\nEnter the new rate\n";
		cout << "New rate : ";
		float NewRate = clsInputValidate<double>::readNumber();

		Currency.updateRate(NewRate);

		if (Currency.Rate() != NewRate)
			cout << "\nRate was NOT updated successfully.\n" << endl;
		else
		{
			cout << "\nRate was updated successfully.\n";
			_printCurrency(Currency);
			cout << endl;
		}
	}
};

