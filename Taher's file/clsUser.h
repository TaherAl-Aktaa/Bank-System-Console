#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"clsString.h"
#include"clsPerson.h"
#include"clsDate.h"
#include"clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode { Empty, Update, AddNew };

	enMode _Mode;
	string _Username;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;
	struct stLoginRecord;

	static clsUser _convertLineToUserObj(string Line)
	{
		vector<string> vData = clsString::splitString(Line, "#//#");

		return clsUser(Update, vData[0], vData[1], vData[2], vData[3], vData[4], clsUtil::decryptText(vData[5]), stoi(vData[6]));
	}

	static clsUser _getEmptyUser()
	{
		return clsUser(enMode::Empty, "", "", "", "", "", "", 0);
	}

	static vector<clsUser> _loadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open("UsersData.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				vUsers.push_back(_convertLineToUserObj(DataLine));
			}

			MyFile.close();
		}

		return vUsers;
	}

	static string _convertObjToDataLine(clsUser User, string Sperator = "#//#")
	{
		string DataLine;

		DataLine += User.FirstName + Sperator;
		DataLine += User.LastName + Sperator;
		DataLine += User.Email + Sperator;
		DataLine += User.Phone + Sperator;
		DataLine += User.Username + Sperator;
		DataLine += clsUtil::encryptText(User.Password) + Sperator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	static void _saveUsersDataToFile(vector<clsUser>& vUsers)
	{
		fstream MyFile;
		MyFile.open("UsersData.txt", ios::out);

		for (clsUser& User : vUsers)
		{
			if (!User.isMarkedToDelete())
				MyFile << _convertObjToDataLine(User) << '\n';
		}

		MyFile.close();
	}

	void _update()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == Username)
			{
				User = *this;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
	}

	void _addNewUser()
	{
		fstream MyFile;
		MyFile.open("UsersData.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _convertObjToDataLine(*this) << '\n';

			MyFile.close();
		}
	}

	string _prepareLogInRecord(string Sperator = "#//#")
	{
		string str = clsDate::getSystemDateAndTime() + Sperator;
		str += Username + Sperator;
		str += clsUtil::encryptText(Password) + Sperator;
		str += to_string(Permissions);

		return str;
	}

	static stLoginRecord _convertDataLineToLoginRecord(string DataLine, string Delim = "#//#")
	{
		vector<string> vData = clsString::splitString(DataLine, Delim);

		stLoginRecord LoginRecord;
		LoginRecord.Date_Time = vData[0];
		LoginRecord.Username = vData[1];
		LoginRecord.Password = clsUtil::decryptText(vData[2]);
		LoginRecord.Permissions = stoi(vData[3]);

		return LoginRecord;
	}

public:

	enum enPermission
	{
		All = -1, ClientsList = 1, AddNewClient = 1 << 1, DeleteClient = 1 << 2,
		UpdateClient = 1 << 3, FindClient = 1 << 4, Transactions = 1 << 5, ManageUsers = 1 << 6,
		LoginHistory = 1 << 7
	};

	struct stLoginRecord
	{
		string Date_Time;
		string Username;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string Username, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	string getUsername()
	{
		return _Username;
	}

	void setUsername(string Username)
	{
		_Username = Username;
	}

	__declspec(property(get = getUsername, put = setUsername)) string Username;

	string getPassword()
	{
		return _Password;
	}

	void setPassword(string Password)
	{
		_Password = Password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string Password;

	int getPermissions()
	{
		return _Permissions;
	}

	void setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	bool isEmpty()
	{
		return (_Mode == enMode::Empty);
	}

	bool isMarkedToDelete()
	{
		return _MarkedForDelete;
	}

	static clsUser find(string Username)
	{
		fstream MyFile;
		MyFile.open("UsersData.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsUser User = _convertLineToUserObj(DataLine);

				if (User.Username == Username)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _getEmptyUser();
	}

	static clsUser find(string Username, string Password)
	{
		fstream MyFile;
		MyFile.open("UsersData.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsUser User = _convertLineToUserObj(DataLine);

				if (User.Username == Username && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _getEmptyUser();
	}

	static bool doesUserExist(string Username)
	{
		return !find(Username).isEmpty();
	}

	enum enSaveResult { Succeeded, FailedEmptyObj, FailedUserExists };

	enSaveResult save()
	{
		switch (_Mode)
		{
		case clsUser::Empty:
			return enSaveResult::FailedEmptyObj;
		case clsUser::Update:
		{
			_update();
			return enSaveResult::Succeeded;
		}
		case clsUser::AddNew:
		{
			if (doesUserExist(Username))
				return enSaveResult::FailedUserExists;

			_addNewUser();
			_Mode = enMode::Update;
			return enSaveResult::Succeeded;
		}
		default:
			break;
		}
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.Username == Username)
			{
				User._MarkedForDelete = true;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
		*this = _getEmptyUser();

		return true;
	}

	static clsUser getNewUserObj(string Username)
	{
		return clsUser(enMode::AddNew, " ", " ", " ", " ", Username, " ", 0);
	}

	static vector<clsUser> getUsersList()
	{
		return _loadUsersDataFromFile();
	}

	bool checkAccessPermission(enPermission Permission)
	{
		return this->Permissions & Permission;
	}

	void saveLogIn()
	{
		fstream MyFile;
		MyFile.open("LogInHistory.txt", ios::out | ios::app);

		string DataLine = _prepareLogInRecord();

		if (MyFile.is_open())
		{
			MyFile << DataLine << '\n';
			MyFile.close();
		}
	}

	static vector<stLoginRecord> loadLoginRecordsFromFile()
	{
		vector<stLoginRecord> vLoginRecords;

		fstream MyFile;
		MyFile.open("LogInHistory.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				vLoginRecords.push_back(_convertDataLineToLoginRecord(DataLine));
			}

			MyFile.close();
		}

		return vLoginRecords;
	}
};

