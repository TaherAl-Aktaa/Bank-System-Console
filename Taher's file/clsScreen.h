#pragma once
#include<iostream>
#include"Global.h"
#include"clsDate.h"

using namespace std;

class clsScreen
{
private:

	static string CurrentDate;

protected:

	static void _drawScreenHeader(string Title, string SubTitile = "")
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t" << Title;

		if (!SubTitile.empty())
			cout << "\n\t\t\t\t\t" << SubTitile;

		cout << "\n\t\t\t\t\t______________________________________\n\n";

		cout << "\t\t\t\t\t\t   User : " << CurrentUser.Username << '\n';
		cout << "\t\t\t\t\t\t   Date : " << CurrentDate << "\n\n";
	}

	static bool _checkAccessRights(clsUser::enPermission Permission)
	{
		if (CurrentUser.checkAccessPermission(Permission))
			return true;
		else
		{
			_drawScreenHeader("\t   Access denied", "\t Contact your admin.");
			return false;
		}
	}
};

string clsScreen::CurrentDate = clsDate::formatDate(clsDate());