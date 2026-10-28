#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h";
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMenue : protected clsScreen
{
private:
	
	enum enCurrencyExchangeOption {CurrenciesList, Find, Update, Calculator};

	static void _showCurrenciesList()
	{
		clsCurrenciesListScreen::showCurrenciesList();
	}

	static void _showFindCurrency()
	{
		clsFindCurrencyScreen::showFindCurrencyScreen();
	}

	static void _showUpdateRate()
	{
		clsUpdateRateScreen::showUpdateRateScreen();
	}

	static void _showCurrencyCalculator()
	{
		clsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _goBackToCurrencyExchangeMenue()
	{
		cout << "Press any key to go back to currency exchange menue...";
		system("pause > 0");
		showCurrencyExchangeMenue();
	}

	static void _peformCurrencyExchange(enCurrencyExchangeOption Option)
	{
		switch (Option)
		{
		case clsCurrencyExchangeMenue::CurrenciesList:
		{
			system("cls");
			_showCurrenciesList();
			_goBackToCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeMenue::Find:
		{
			system("cls");
			_showFindCurrency();
			_goBackToCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeMenue::Update:
		{
			system("cls");
			_showUpdateRate();
			_goBackToCurrencyExchangeMenue();
			break;
		}
		case clsCurrencyExchangeMenue::Calculator:
		{
			_showCurrencyCalculator();
			_goBackToCurrencyExchangeMenue();
			break;
		}
		default:
			break;
		}
	}

public:

	static void showCurrencyExchangeMenue()
	{
		system("cls");

		_drawScreenHeader("        Currency Exchange Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t[1] Currencies list.\n";
		cout << setw(37) << left << "" << "\t\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t\t[5] Main menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_peformCurrencyExchange((enCurrencyExchangeOption)(clsInputValidate<short>::readNumberBetween(1, 5, "\t\t\t\t\tChoose an operation to do, [ 1 - 5 ] : ") - 1));
	}
};

