#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:

	static int _readPermissions()
	{
		int Permissions = 0;
		char ch;

		cout << "\n\nDo you want to give full access ? ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			return -1;

		cout << "\nDo you want to give access to : \n";

		cout << "\nShow client list, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::ClientsList;

		cout << "\nAdd new client, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::AddNewClient;

		cout << "\nDelete client, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::DeleteClient;

		cout << "\nUpdate client, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::UpdateClient;

		cout << "\nFind client, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::FindClient;

		cout << "\nTransactions, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::Transactions;

		cout << "\nManage users, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::ManageUsers;

		cout << "\nLogin history, ( y / n ) : ";
		cin >> ch;

		if (tolower(ch) == 'y')
			Permissions |= clsUser::enPermission::LoginHistory;

		return Permissions;
	}

	static clsUser _readUserInfo(string Username)
	{
		clsUser User = clsUser::getNewUserObj(Username);

		cout << "\nEnter user information.\n";

		cout << "\nFirst name : ";
		User.FirstName = clsInputValidate<string>::readString();

		cout << "\nLast name : ";
		User.LastName = clsInputValidate<string>::readString();

		cout << "\nEmail : ";
		User.Email = clsInputValidate<string>::readString();

		cout << "\nPhone : ";
		User.Phone = clsInputValidate<string>::readString();

		cout << "\nPassword : ";
		User.Password = clsInputValidate<string>::readString();

		cout << "\nPermissions : ";
		User.Permissions = _readPermissions();

		return User;
	}

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
	
	static void showAddNewUserScreen()
	{
		_drawScreenHeader("\t  Add new user screen");

		string Username;

		while (true)
		{
			cout << "Enter username : ";
			cin >> Username;

			if (!clsUser::doesUserExist(Username))
				break;

			cout << "\nUsername is already used.\n\n";
		}

		clsUser NewUser = _readUserInfo(Username);

		clsUser::enSaveResult SaveResult = NewUser.save();

		switch (SaveResult)
		{
		case clsUser::Succeeded:
		{
			cout << "\nUser was added successfully.\n";
			_printUser(NewUser);
			break;
		}
		case clsUser::FailedEmptyObj:
		{
			cout << "\nError, User was not saved because it's empty.";
			break;
		}
		case clsUser::FailedUserExists:
		{
			cout << "\nError, User was not saves because username is used.\n";
			break;
		}
		default:
			break;
		}
	}
};

