#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

	static void showDeleteUserScreen()
	{
		_drawScreenHeader("\t  Delete user screen");

		string Username;

		while (true)
		{
			cout << "Username : ";
			cin >> Username;

			if (clsUser::doesUserExist(Username))
				break;

			cout << "\nUser was not found.\n\n";
		}

		clsUser User = clsUser::find(Username);
		_printUser(User);

		char Check;

		cout << "\nAre you sure to delete this user ? ( y / n ) : ";
		cin >> Check;

		if (tolower(Check) == 'y')
		{
			if (!User.Delete())
				cout << "\nError, user was not deleted.\n";
			else
			{
				cout << "\nUser was deleted successfully.\n";
				_printUser(User);
			}
		}
	}
};

