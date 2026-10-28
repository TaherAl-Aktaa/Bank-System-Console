#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	static void _readClientInfo(clsBankClient& Client)
	{
		cout << "First name : ";
		Client.FirstName = clsInputValidate<string>::readString();

		cout << "Last name : ";
		Client.LastName = clsInputValidate<string>::readString();

		cout << "Email : ";
		Client.Email = clsInputValidate<string>::readString();

		cout << "Phone : ";
		Client.Phone = clsInputValidate<string>::readString();

		cout << "Password : ";
		Client.PINCode = clsInputValidate<string>::readString();

		cout << "Account balance : ";
		Client.AccountBalance = clsInputValidate<double>::readNumber();
	}

public:

	static void showUpdateClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermission::UpdateClient))
			return;

		_drawScreenHeader("\t Update client screen");

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
		cout << "\nAre you sure you want to update this client ? ( y / n ): ";
		cin >> Check;

		if (towlower(Check) == 'y')
		{
			cout << "\n\nUpdate client info : ";
			cout << "\n____________________\n";

			_readClientInfo(Client);

			clsBankClient::enSaveResult SaveResult = Client.save();

			switch (SaveResult)
			{
			case clsBankClient::Succeeded:
			{
				cout << "\nAccount was updated successfully.\n";
				_printClint(Client);
				break;
			}
			case clsBankClient::Faild_EmptyObj:
			{
				cout << "\nError account was not saved because it's Empty";
				break;
			}
			default:
				break;
			}
		}
	}
};

