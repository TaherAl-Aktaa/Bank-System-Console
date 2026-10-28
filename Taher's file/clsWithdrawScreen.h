#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static void showWithdrawScreen()
	{
		_drawScreenHeader("\t    Withdraw screen");

		string AccountNumber = _readAccountNumber();
		clsBankClient Client = clsBankClient::find(AccountNumber);

		_printClint(Client);

		cout << "\nEnter amount to withdraw.\nAmount : ";
		double Amount = clsInputValidate<double>::readNumber();

		char Check;
		cout << "\nAre your sure you want to withdraw this amount ? ( y / n ) : ";
		cin >> Check;

		if (!(tolower(Check) == 'y'))
			cout << "\nOperation was cancelled.";
		else
		{
			if (Client.withdraw(Amount))
			{
				cout << "\nAmount was wtihdrawn successfully.\n";
				cout << "\nNew balance : " << Client.AccountBalance;
			}
			else
			{
				cout << "\nCannot withdraw, not enough balance\n";
				cout << "\nAmount to withdraw : " << Amount;
				cout << "\nYour balance : " << Client.AccountBalance;
			}
		}

		cout << endl;
	}
};

