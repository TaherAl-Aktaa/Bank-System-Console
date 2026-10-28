#pragma once
#include<iostream>
#include"clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _printClint(clsBankClient Client)
	{
		cout << "\nClient Card : ";
		cout << "\n___________________________\n\n";
		cout << setw(15) << left << "First name" << " : " << Client.FirstName << '\n';
		cout << setw(15) << left << "Last name" << " : " << Client.LastName << '\n';
		cout << setw(15) << left << "Full name" << " : " << Client.FullName() << '\n';
		cout << setw(15) << left << "Email" << " : " << Client.Email << '\n';
		cout << setw(15) << left << "Phone" << " : " << Client.Phone << '\n';
		cout << setw(15) << left << "Account Number" << " : " << Client.AccountNumber() << '\n';
		cout << setw(15) << left << "Password" << " : " << Client.PINCode << '\n';
		cout << setw(15) << left << "Balance" << " : " << Client.AccountBalance << '\n';
		cout << "\n___________________________\n";
	}

public:

	static void showDeleteClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermission::DeleteClient))
			return;

		_drawScreenHeader("\t Delete client screen");

		string AccountNumber;

		while (true)
		{
			cout << "Enter account number : ";
			cin >> AccountNumber;

			if (clsBankClient::doesClientExist(AccountNumber))
				break;

			cout << "Account number not found, choose another one\n\n";
		}

		clsBankClient Client = clsBankClient::find(AccountNumber);
		_printClint(Client);

		char Check;
		cout << "\nAre you sure you want to delete this client ? ( y / n) : ";
		cin >> Check;

		if (tolower(Check) == 'y')
		{
			if (!Client.Delete())
				cout << "\nError, Client was NOT deleted successfully.\n";
			else
			{
				cout << "\nClient was deleted successfully.\n";
				_printClint(Client);
			}
		}
	}
};

