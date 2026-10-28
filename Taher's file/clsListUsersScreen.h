#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
#include"clsScreen.h"
#include"clsUser.h"
using namespace std;

class clsListUsersScreen : protected clsScreen
{
private:

	static void _printUser(clsUser& User)
	{
		cout << setw(4) << "" << "| " << setw(13) << left << User.Username;
		cout << "| " << setw(23) << left << User.FullName();
		cout << "| " <<  setw(18) << left << User.Phone;
		cout << "| " << setw(23) << left << User.Email;
		cout << "| " << setw(11) << left << User.Password;
		cout << "| " << setw(11) << left << User.Permissions << " |\n";
	}


public:

	static void showUsersList()
	{
		vector<clsUser> vUsers = clsUser::getUsersList();

		string Title = "\t   Users list screen";
		string SubTitle = "\t      " + to_string(vUsers.size()) + " User(s).";

		_drawScreenHeader(Title, SubTitle);

		cout << '\n';
		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
		cout << setw(4) << "" << setw(15) << left << "| Username";
		cout << setw(25) << left << "| Full name";
		cout << setw(20) << left << "| Phone";
		cout << setw(25) << left << "| Email";
		cout << setw(13) << left << "| Password";
		cout << setw(15) << left << "| Permissions |\n";
		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";

		if (vUsers.empty())
			cout << "\t\t\t\t\t    No users avaliable in the system.\n";
		else
		{
			for (clsUser& User : vUsers)
				_printUser(User);
		
		}

		cout << setw(4) << "" << "-----------------------------------------------------------------------------------------------------------------\n";
		cout << endl;
	}
};

