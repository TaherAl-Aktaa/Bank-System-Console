#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransferScreen.h"
#include"clsTransferHistoryScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{

private:

	enum enTransactionsMenueOptions {Deposit, Withdraw, ShowTotalBalance, Transfer, TransferHistory, ShowMainMenue};

	static enTransactionsMenueOptions _readTransactionsMenueOption()
	{
		return enTransactionsMenueOptions(clsInputValidate<int>::readNumberBetween(1, 6, "\t\t\t\t\tChoose what you want to do, [ 1 - 6 ] : ") - 1);
	}

	static void _showDepositScreen()
	{
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen()
	{
		clsWithdrawScreen::showWithdrawScreen();
	}

	static void _showTotalBalanceScreen()
	{
		clsTotalBalancesScreen::showTotalBalancesScreen();
	}

	static void _showTransferScreen()
	{
		clsTransferScreen::showTranferScreen();
	}

	static void _showTransferHistory()
	{
		clsTransferHistoryScreen::showTransferHistoryScreen();
	}

	static void _goBackToTransactionsScreen()
	{
		cout << "\n\nPress any key to go back to transactions menue...";
		system("pause > 0");
		showTransactionsMenue();
	}

	static void _peformTransactionsMenue(enTransactionsMenueOptions Option)
	{
		switch (Option)
		{
		case clsTransactionsScreen::Deposit:
		{
			system("cls");
			_showDepositScreen();
			_goBackToTransactionsScreen();
			break;
		}
		case clsTransactionsScreen::Withdraw:
		{
			system("cls");
			_showWithdrawScreen();
			_goBackToTransactionsScreen();
			break;
		}
		case clsTransactionsScreen::ShowTotalBalance:
		{
			system("cls");
			_showTotalBalanceScreen();
			_goBackToTransactionsScreen();
			break;
		}
		case clsTransactionsScreen::Transfer:
		{
			system("cls");
			_showTransferScreen();
			_goBackToTransactionsScreen();
			break;
		}
		case clsTransactionsScreen::TransferHistory: 
		{
			system("cls");
			_showTransferHistory();
			_goBackToTransactionsScreen();
			break;
		}
		case clsTransactionsScreen::ShowMainMenue:
			break;
		default:
			break;
		}
	}

public:

	static void showTransactionsMenue()
	{
		system("cls");

		if (!_checkAccessRights(clsUser::enPermission::Transactions))
			return;

		_drawScreenHeader("\t  Transactions Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total balances.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer history.\n";
		cout << setw(37) << left << "" << "\t[6] Main menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_peformTransactionsMenue(_readTransactionsMenueOption());
	}
};

