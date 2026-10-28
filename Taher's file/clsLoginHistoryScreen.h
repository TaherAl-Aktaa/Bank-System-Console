#pragma once
#include<iostream>
#include"clsUser.h"
#include"clsScreen.h"
#include"clsString.h"

using namespace std;

class clsLoginHistoryScreen : protected clsScreen
{
private:

	static void _printLoginRecord(clsUser::stLoginRecord LoginRecord)
	{
		cout << setw(5) << "";
		cout << "| " << setw(35) << left << LoginRecord.Date_Time;
		cout << "| " << setw(28) << left << LoginRecord.Username;
		cout << "| " << setw(22) << left << LoginRecord.Password;
		cout << "| " << setw(14) << left << LoginRecord.Permissions << " |\n";
	}

public:

	static void showLoginHistory()
	{
		if (!_checkAccessRights(clsUser::enPermission::LoginHistory))
			return;

		vector<clsUser::stLoginRecord> vLoginRecords = clsUser::loadLoginRecordsFromFile();
		string SubTitle = "\t   (" + to_string(vLoginRecords.size()) + ")" + " Record(s).";

		_drawScreenHeader("\t    Login History", SubTitle);


		cout << '\n';
		cout << setw(5) << "" << "-------------------------------------------------------------------------------------------------------------\n";
		cout << setw(5) << ""; 
		cout << "| " << setw(35) << left << "Date / Time";
		cout << "| " << setw(28) << left << "Username";
		cout << "| " << setw(22) << left << "Password";
		cout << "| " << setw(14) << left << "Permissions" << " |\n";
		cout << setw(5) << "" << "-------------------------------------------------------------------------------------------------------------\n";

		for (clsUser::stLoginRecord& Record : vLoginRecords)
		{
			_printLoginRecord(Record);
		}

		cout << setw(5) << "" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
	}
};

