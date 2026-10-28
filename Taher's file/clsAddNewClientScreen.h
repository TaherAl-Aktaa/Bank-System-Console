#pragma once
#include<iostream>
#include"clsBankClient.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static clsBankClient _readClientInfo()
	{
		string AccountNumber;

		while (true)
		{
			cout << "Enter account number : ";
			AccountNumber = clsInputValidate<string>::readString();

			if (!clsBankClient::doesClientExist(AccountNumber))
				break;

			cout << "\nAccount number [" << AccountNumber << "] is used\n\n";
		}


		clsBankClient Client = clsBankClient::getNewClientObj(AccountNumber);

		cout << "Enter first name : ";
		Client.FirstName = clsInputValidate<string>::readString();

		cout << "Enter last name : ";
		Client.LastName = clsInputValidate<string>::readString();

		cout << "Enter email : ";
		Client.Email = clsInputValidate<string>::readString();

		cout << "Enter phone : ";
		Client.Phone = clsInputValidate<string>::readString();

		cout << "Enter Password : ";
		Client.PINCode = clsInputValidate<string>::readString();

		cout << "Enter account balance : ";
		Client.AccountBalance = clsInputValidate<double>::readNumber();

		return Client;
	}

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
	static void showAddNewClientScreen()
	{
		if (!_checkAccessRights(clsUser::enPermission::AddNewClient))
			return;

		_drawScreenHeader("\t  Add new client screen");

		clsBankClient NewClient = _readClientInfo();

		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.save();

		switch (SaveResult)
		{
		case clsBankClient::Succeeded:
		{
			cout << "\nClient was added successfully.\n\n";
			_printClint(NewClient);
			break;
		}
		case clsBankClient::Faild_EmptyObj:
		{
			cout << "\nFaild because object is empty.\n\n";
			break;
		}
		case clsBankClient::Faild_AccountNumberIsUsed:
		{
			cout << "\nFaild account number is used.\n\n";
			break;
		}
		}

	}
};

