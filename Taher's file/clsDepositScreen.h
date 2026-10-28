#pragma once
#include<iostream>
#include"clsBankClient.h"
#include"clsScreen.h"
#include"clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

	static string _readAccountNumber()
	{
		string AccountNumber;

		while (true)
		{
			cout << "Enter account number : ";
			cin >> AccountNumber;

			if (clsBankClient::doesClientExist(AccountNumber))
				return AccountNumber;

			cout << "Account number not found, choose another one\n\n";
		}
	}

public:

	static void showDepositScreen()
	{
		_drawScreenHeader("\t    Deposit screen");

		string AccountNumber = _readAccountNumber();
		clsBankClient Client = clsBankClient::find(AccountNumber);

		_printClint(Client);

		double Amount = 0;
		
		while (true)
		{
			cout << "\nEnter amount to deposit.\nAmount : ";
			Amount = clsInputValidate<double>::readNumber();

			if (Amount >= 0)
				break;

			cout << "\nEnter a POSTIVE number.\n";
		}

		char Check;
		cout << "\nAre you sure you want to peform this deposit ? ( y / n ) : ";
		cin >> Check;

		if (tolower(Check) == 'y')
		{
			Client.deposit(Amount);
			cout << "\n\nAmount was deposited successfully.\n";
			cout << "\nNew balance : " << Client.AccountBalance;
		}
		else
			cout << "\nOperation was cancelled.";

		cout << endl;
	}
};

