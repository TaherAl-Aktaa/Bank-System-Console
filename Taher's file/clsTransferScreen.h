#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:

	static void _printClientCard(clsBankClient Client)
	{
		cout << "\nClient Card : \n\n";
		cout << "-------------------------\n\n";
		cout << "Full name      : " << Client.FullName() << '\n';
		cout << "Account Number : " << Client.AccountNumber() << '\n';
		cout << "Balance        : " << Client.AccountBalance << "\n\n";
		cout << "-------------------------\n";
	}

	static string _readAccountNumber(string Message)
	{
		string AccountNumber;

		while (true)
		{
			cout << Message;
			cin >> AccountNumber;

			if (clsBankClient::doesClientExist(AccountNumber))
				return AccountNumber;

			cout << "\nAccount [" << AccountNumber << "] does NOT exist.\n\n";
		}
	}

	static double _readTransferAmount(clsBankClient SourceClient)
	{
		double TransferAmount;

		while (true)
		{
			cout << "Transfer amount : ";
			TransferAmount = clsInputValidate<double>::readNumber();

			if (TransferAmount <= SourceClient.AccountBalance)
				return TransferAmount;

			cout << "\nAmount exceeds the avaliable balance.\n\n";
		}
	}

public:

	static void showTranferScreen()
	{
		_drawScreenHeader("\t   Transfer Screen");

		string TransferFrom = _readAccountNumber("Account to transfer from : ");
		clsBankClient ClientFrom = clsBankClient::find(TransferFrom);
		_printClientCard(ClientFrom);
		cout << '\n';

		string TransferTo = _readAccountNumber("Account to transfer to : ");
		clsBankClient ClientTo = clsBankClient::find(TransferTo);
		_printClientCard(ClientTo);
		cout << '\n';

		double TransferAmount = _readTransferAmount(ClientFrom);

		char ch;
		cout << "\nAre you sure to peform this transfer, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) != 'y')
			cout << "\nOperation was canceled.";
		else
		{
			bool OperationStatus = ClientFrom.transferTo(TransferAmount, ClientTo);

			if (OperationStatus)
				cout << "\nOperation was done successfully.";
			else
				cout << "\nOperation failed.";

			cout << endl;

			_printClientCard(ClientFrom);
			cout << '\n';
			_printClientCard(ClientTo);
			cout << "\n\n";
		}

		
	}
};

