#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsListUsersScreen.h"
#include"clsUser.h"
#include"clsAddNewUserScreen.h"
#include"clsDeleteUserScreen.h"
#include"clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"

using namespace std;

class clsManageUsersMenue : protected clsScreen
{
private:
	
	enum enManageUsersMenueOptions
	{
		ListUsers, AddNewUser, DeleteUser, UpdateUser, FindUser, MainMenue
	};

	static enManageUsersMenueOptions _readManageUsersOption()
	{
		short Option;

		while (true)
		{
			cout << setw(40) << "" << "Choose an option to do, [ 1 - 6 ] : ";
			Option = clsInputValidate<short>::readNumber();

			if (clsInputValidate<short>::isNumberBetween(Option, 1, 6))
				break;
		}

		return enManageUsersMenueOptions(Option - 1);
	}

	static void _goBackToManageUsersMenue()
	{
		cout << endl;
		cout << "Press any key to go back to mange users screen...\n";
		system("pause > 0");

		showManageUsersMenue();
	}

	static void _listUsers()
	{
		clsListUsersScreen::showUsersList();
	}

	static void _addNewUser()
	{
		clsAddNewUserScreen::showAddNewUserScreen();
	}

	static void _deleteUser()
	{
		clsDeleteUserScreen::showDeleteUserScreen();
	}

	static void _updateUser()
	{
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _findUser()
	{
		clsFindUserScreen::showFindUserScreen();
	}

	static void _peformManageUsersMenue(enManageUsersMenueOptions Option)
	{
		switch (Option)
		{
		case clsManageUsersMenue::ListUsers:
		{
			system("cls");
			_listUsers();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::AddNewUser:
		{
			system("cls");
			_addNewUser();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::DeleteUser:
		{
			system("cls");
			_deleteUser();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::UpdateUser:
		{
			system("cls");
			_updateUser();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::FindUser:
		{
			system("cls");
			_findUser();
			_goBackToManageUsersMenue();
			break;
		}
		case clsManageUsersMenue::MainMenue:
			break;
		default:
			break;
		}
	}

public:

	static void showManageUsersMenue()
	{
		system("cls");

		if (!_checkAccessRights(clsUser::enPermission::ManageUsers))
			return;

		_drawScreenHeader("\t  Mange users screen");

		cout << setw(40) << "" << "======================================\n";
		cout << setw(50) << "" << "[1] List users.\n";
		cout << setw(50) << "" << "[2] Add new user.\n";
		cout << setw(50) << "" << "[3] Delete user.\n";
		cout << setw(50) << "" << "[4] Update user.\n";
		cout << setw(50) << "" << "[5] Find user.\n";
		cout << setw(50) << "" << "[6] Main menue.\n";
		cout << setw(40) << "" << "======================================\n";

		_peformManageUsersMenue(_readManageUsersOption());
	}
};

