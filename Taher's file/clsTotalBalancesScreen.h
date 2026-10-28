#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include<iomanip>
#include<vector>
#include"clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

	static void _printClientBalanceLine(clsBankClient Client)
	{
		cout << "\t\t\t" << "| " << setw(23) << left << Client.AccountNumber();
		cout << "| " << setw(33) << left << Client.FullName();
		cout << "| " << setw(15) << left << Client.AccountBalance;
		cout << '\n';
	}

public:

	static void showTotalBalancesScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_drawScreenHeader("\t Balnaces list screen", SubTitle);

		cout << "\n\t\t---------------------------------------------------------------------------------------\n";
		cout << "\t\t\t" << setw(25) << left << "| Account number";
		cout << setw(35) << left << "| Client name";
		cout << setw(15) << left << "| Balance";
		cout << "\n\t\t---------------------------------------------------------------------------------------\n";

		if (vClients.empty())
			cout << "\t\t\t\t\t  " << "No clients available in the system.\n";
		else
		{
			for (clsBankClient& Client : vClients)
				_printClientBalanceLine(Client);

			cout << "\t\t---------------------------------------------------------------------------------------\n";

			double TotalBalance = clsBankClient::getTotalBalance();

			cout << "\t\t\t\t\t\t" << "Total balance : " << TotalBalance;
			cout << "\n\t\t\t\t\t    " << clsUtil::NumberToText(int(TotalBalance)) + '.' << endl;
		}
	}

};

