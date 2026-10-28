#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"

using namespace std;

class clsTransferHistoryScreen : protected clsScreen
{
private:

	static void _printTransferRecord(clsBankClient::stTransferRecord Record)
	{
		cout << setw(3) << "";
		cout << "| " << setw(21) << left << Record.Date_Time;
		cout << "| " << setw(15) << left << Record.SourceAccountNumber;
		cout << "| " << setw(15) << left << Record.DesAccountNumber;
		cout << "| " << setw(10) << left << Record.TransferAmount;
		cout << "| " << setw(15) << left << Record.SourceBalance;
		cout << "| " << setw(15) << left << Record.DesBalance;
		cout << "| " << setw(10) << left << Record.User << "|\n";
	}

public:

	static void showTransferHistoryScreen()
	{
		vector<clsBankClient::stTransferRecord> vTransferRecords = clsBankClient::loadTransferRecord();

		string SubTitle = "\t    (" + to_string(vTransferRecords.size()) + ") Record(s).";
		_drawScreenHeader("\t   Transfer History", SubTitle);

		cout << setw(3) << "" << "--------------------------------------------------------------------------------------------------------------------\n";
		cout << setw(3) << "";
		cout << "| " << setw(21) << left << "Date / Time";
		cout << "| " << setw(15) << left << "Source Account";
		cout << "| " << setw(15) << left << "Des Account";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(15) << left << "Source Balance";
		cout << "| " << setw(15) << left << "Des Balance";
		cout << "| " << setw(10) << left << "User" << "|\n";
		cout << setw(3) << "" << "--------------------------------------------------------------------------------------------------------------------\n";

		if (vTransferRecords.empty())
			cout << "\t\t\t\t\t     No transfers have been made.\n";
		else
		{
			for (clsBankClient::stTransferRecord& Record : vTransferRecords)
				_printTransferRecord(Record);
		}


		cout << setw(3) << "" << "--------------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
	}
};

