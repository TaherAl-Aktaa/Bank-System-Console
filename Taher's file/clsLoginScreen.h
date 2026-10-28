#pragma once
#include<iostream>
#include"clsMainMenue.h"
#include"Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	
	static void _login()
	{
		string Username, Password;

		for (short i = 0; i < 3; i++)
		{
			cout << "Username : ";
			cin >> Username;

			cout << "\nPassword : ";
			cin >> Password;

			CurrentUser = clsUser::find(Username, Password);

			if (!CurrentUser.isEmpty())
			{
				LoggedIn = true;
				break;
			}

			LoggedIn = false;
			cout << "\nInvalid password / username\n";
			cout << 2 - i << " Trail(s) left.\n\n";
		}

		if (LoggedIn)
		{
			CurrentUser.saveLogIn();
			clsMainMenue::showMainMenue();
		}
		else
			cout << "you are locked after 3 faild trails." << endl;
	}

public:

	static void showLoginScreen()
	{
		_drawScreenHeader("\t     Login screen");
		_login();
	}

	
};

