#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsClientListScreen.h"
#include"clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindCientScreen.h"
#include"clsTransactionsMenue.h"
#include"clsManageUsersMenue.h"
#include"clsLoginHistoryScreen.h"
#include"Global.h"
#include"clsCurrencyExchangeMenue.h"

using namespace std;

class clsMainMenue : protected clsScreen
{
	
private:
	enum enMainMenueOptions { ListClients, AddNewClient, DeleteClient, UpdateClient, FindClient, TransactionsMenue, ManageUsers, LoginHistory, CurrencyExchange, Exist };

    static void _goBackToHomeScreen()
    {
        cout << "\n\t\t\t\tPress any key to go back to main menue...\n";
        system("pause > 0");
        showMainMenue();
    }

    static void _showAllClientsScreen()
    {
        clsClientListScreen::showClientsList();
    }

    static void _showAddNewClientScreen()
    {
        clsAddNewClientScreen::showAddNewClientScreen();
    }

    static void _showDeleteClientScreen()
    {
        clsDeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen()
    {
        clsUpdateClientScreen::showUpdateClientScreen();
    }

    static void _showFindClientScreen()
    {
        clsFindCientScreen::showFindClientScreen();
    }

    static void _showTransactionMenue()
    {
        clsTransactionsScreen::showTransactionsMenue();
    }

    static void _showManageUsersMenue()
    {
        clsManageUsersMenue::showManageUsersMenue();
    }

    static void _showLoginHistory()
    {
        clsLoginHistoryScreen::showLoginHistory();
    }

    static void _showCurrencyExchangeMenue()
    {
        clsCurrencyExchangeMenue::showCurrencyExchangeMenue();
    }

    static void _logout()
    {
        CurrentUser = clsUser::find("");
    }

    static void _peformMainMenue(enMainMenueOptions Option)
    {
        switch (Option)
        {
        case clsMainMenue::ListClients:
        {
            system("cls");
            _showAllClientsScreen();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::AddNewClient:
        {
            system("cls");
            _showAddNewClientScreen();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::DeleteClient:
        {
            system("cls");
            _showDeleteClientScreen();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::UpdateClient:
        {
            system("cls");
            _showUpdateClientScreen();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::FindClient:
        {
            system("cls");
            _showFindClientScreen();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::TransactionsMenue:
        {
            _showTransactionMenue();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::ManageUsers:
        {
            _showManageUsersMenue();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::LoginHistory:
        {
            system("cls");
            _showLoginHistory();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::CurrencyExchange:
        {
            _showCurrencyExchangeMenue();
            _goBackToHomeScreen();
            break;
        }
        case clsMainMenue::Exist:
        {
            system("cls");
            _logout();
            break;
        }
        }
    }

public :

	static void showMainMenue()
	{
		system("cls");
		_drawScreenHeader("\t     Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login History.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _peformMainMenue((enMainMenueOptions)(clsInputValidate<short>::readNumberBetween(1, 10, "\t\t\t\t\tChoose what you want to do, [ 1 - 10 ] : ") - 1));
	}
};

