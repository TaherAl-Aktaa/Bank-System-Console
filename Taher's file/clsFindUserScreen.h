#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:

	static void _printUser(clsUser User)
	{
		cout << "\nUser Card : ";
		cout << "\n___________________________\n\n";
		cout << setw(15) << left << "Username" << " : " << User.Username << '\n';
		cout << setw(15) << left << "First name" << " : " << User.FirstName << '\n';
		cout << setw(15) << left << "Last name" << " : " << User.LastName << '\n';
		cout << setw(15) << left << "Full name" << " : " << User.FullName() << '\n';
		cout << setw(15) << left << "Email" << " : " << User.Email << '\n';
		cout << setw(15) << left << "Phone" << " : " << User.Phone << '\n';
		cout << setw(15) << left << "Password" << " : " << User.Password << '\n';
		cout << setw(15) << left << "Permissions" << " : " << User.Permissions << '\n';
		cout << "\n___________________________\n";
	}


public:

	static void showFindUserScreen()
	{
		_drawScreenHeader("\t    Find user screen");

		string Username;

		while (true)
		{
			cout << "Enter username : ";
			cin >> Username;

			if (clsUser::doesUserExist(Username))
				break;

			cout << "\nUsername was NOT found.\n\n";
		}

		cout << "\nUser was found.\n";

		clsUser User = clsUser::find(Username);
		_printUser(User);
	}
};

