#pragma once
#include<iostream>
#include<iomanip>
#include"Global.h"
#include"clsScreen.h"
#include"clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void _printClientDataLine(clsBankClient Client)
	{
		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PINCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void showClientsList()
	{
		if (!_checkAccessRights(clsUser::enPermission::ClientsList))
			return;

		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string Title = "\t  Client list screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

		_drawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n\n";

		cout << setw(8) << left << "" << "| " << setw(15) << left << "Account number";
		cout << "| " << setw(20) << left << "Client name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "PIN code";
		cout << "| " << setw(12) << left << "Balance\n\n";
		cout << setw(5) << left << "" << "------------------------------------------------------------------------------------------------------\n\n";

		if (vClients.empty())
			cout << "\t\t\t\tNo clients available in the system.";
		else
		{
			for (clsBankClient& Client : vClients)
			{
				_printClientDataLine(Client);
				cout << '\n';
			}
		}

		cout << "\n\n" << setw(8) << left << "" << "------------------------------------------------------------------------------------------------------\n\n";
	}

};

