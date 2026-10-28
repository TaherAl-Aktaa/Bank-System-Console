#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:

	static void _printCurrency(clsCurrency Currency)
	{
		cout << setw(4) << "";
		cout << "| " << setw(35) << left << Currency.Country();
		cout << "| " << setw(10) << left << Currency.Code();
		cout << "| " << setw(44) << left << Currency.Name();
		cout << "| " << setw(15) << left << Currency.Rate() << "|\n";
	}

public:

	static void showCurrenciesList()
	{
		vector<clsCurrency> vCurrencies = clsCurrency::getCurrenciesList();

		string SubTitle = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

		_drawScreenHeader("\t    Currencies List", SubTitle);

		cout << '\n';
		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
		cout << setw(4) << "";
		cout << "| " << setw(35) << left << "Country";
		cout << "| " << setw(10) << left << "Code";
		cout << "| " << setw(44) << left << "Name";
		cout << "| " << setw(15) << left << "Rate / (1$)" << "|\n";
		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";

		if (vCurrencies.empty())
			cout << "\t\t\t\t\tNo currencies avaliable in th system.\n";
		else
		{
			for (clsCurrency& C : vCurrencies)
				_printCurrency(C);
		}

		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
	}

};

