#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include"clsPerson.h"
#include"clsDate.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	
	enum enMode {EmptyMode, UpdateMode, AddNewMode};
	enMode _Mode;

	string _AccountNumber;
	string _PINCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;
	struct  stTransferRecord;

	static clsBankClient _convertDataLineToClientObj(string LineData, string Sperator = "#//#")
	{
		vector<string> vData = clsString::splitString(LineData, Sperator);
		return clsBankClient(enMode::UpdateMode, vData[0], vData[1], vData[2], vData[3], vData[4], vData[5],
			stof(vData[6]));
	}

	static clsBankClient _getEmptyClientObj()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _loadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("ClientsData.txt", ios::in);

		string DataLine;

		while (getline(MyFile, DataLine))
		{	
			vClients.push_back(_convertDataLineToClientObj(DataLine));
		}

		return vClients;
	}

	string _convertClientObjToDataLine(clsBankClient Client, string Sperator = "#//#")
	{
		string DataLine;

		DataLine.append(Client.FirstName);
		DataLine.append(Sperator);

		DataLine.append(Client.LastName);
		DataLine.append(Sperator);

		DataLine.append(Client.Email);
		DataLine.append(Sperator);

		DataLine.append(Client.Phone);
		DataLine.append(Sperator);

		DataLine.append(Client.AccountNumber());
		DataLine.append(Sperator);

		DataLine.append(Client.PINCode);
		DataLine.append(Sperator);

		DataLine.append(to_string(Client.AccountBalance));

		return DataLine;
	}

	void _saveClientsDataToFile(vector<clsBankClient>& vClients)
	{
		fstream MyFile;
		MyFile.open("ClientsData.txt", ios::out);

		for (clsBankClient& Client : vClients)
			if (!Client._MarkedForDelete)
				MyFile << _convertClientObjToDataLine(Client) << '\n';
	}

	void _update()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client = *this;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
	}

	void _addDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("ClientsData.txt", ios::out | ios::app);

		MyFile << DataLine << '\n';
	}

	void _addNew()
	{
		_addDataLineToFile(_convertClientObjToDataLine(*this));
	}

	string _prepareDataLine(double TranferAmount, clsBankClient ClientTo, string Sperator = "#//#")
	{
		string DataLine;
		DataLine += clsDate::getSystemDateAndTime() + Sperator;
		DataLine += AccountNumber() + Sperator;
		DataLine += ClientTo.AccountNumber() + Sperator;
		DataLine += to_string(TranferAmount) + Sperator;
		DataLine += to_string(AccountBalance) + Sperator;
		DataLine += to_string(ClientTo.AccountBalance) + Sperator;
		DataLine += CurrentUser.Username;

		return DataLine;
	}

	void _saveTransfer(double TranferAmount, clsBankClient ClientTo)
	{
		fstream MyFile;
		MyFile.open("Transfer history.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << _prepareDataLine(TranferAmount, ClientTo) << '\n';
			MyFile.close();
		}
	}

	static stTransferRecord _convertDataLineToTransferRecord(string DataLine)
	{
		vector<string> vData = clsString::splitString(DataLine, "#//#");

		stTransferRecord TransferRecord;
		TransferRecord.Date_Time = vData[0];
		TransferRecord.SourceAccountNumber = vData[1];
		TransferRecord.DesAccountNumber = vData[2];
		TransferRecord.TransferAmount = stod(vData[3]);
		TransferRecord.SourceBalance = stod(vData[4]);
		TransferRecord.DesBalance = stod(vData[5]);
		TransferRecord.User = vData[6];

		return TransferRecord;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PINCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PINCode = PINCode;
		_AccountBalance = AccountBalance;
	}

	struct stTransferRecord
	{
		string Date_Time;
		string SourceAccountNumber;
		string DesAccountNumber;
		string User;
		double TransferAmount;
		double SourceBalance;
		double DesBalance;
	};

	bool isEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void setPINCode(string PINCode)
	{
		_PINCode = PINCode;
	}

	string getPINCode()
	{
		return _PINCode;
	}

	__declspec(property(get = getPINCode, put = setPINCode)) string PINCode;

	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float getAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	static clsBankClient find(string AccountNumber)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("ClientsData.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;
			while (getline(MyFile, DataLine))
			{
				clsBankClient Client = _convertDataLineToClientObj(DataLine);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _getEmptyClientObj();
	}

	static clsBankClient find(string AccountNumber, string PINCode)
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("ClientsData.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;
			while (getline(MyFile, DataLine))
			{
				clsBankClient Client = _convertDataLineToClientObj(DataLine);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();

					if (Client.PINCode == PINCode)
						return Client;
					else
						return _getEmptyClientObj();
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _getEmptyClientObj();
	}

	static bool doesClientExist(string AccountNumber)
	{
		clsBankClient Client = find(AccountNumber);
		return !Client.isEmpty();
	}

	static clsBankClient getNewClientObj(string AccountNumber)
	{
		return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> getClientsList()
	{
		return _loadClientsDataFromFile();
	}

	static double getTotalBalance()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		double TotalBalance = 0;
		for (clsBankClient& Client : vClients)
			TotalBalance += Client.AccountBalance;

		return TotalBalance;
	}

	enum enSaveResult {Succeeded, Faild_EmptyObj, Faild_AccountNumberIsUsed};

	enSaveResult save()
	{
		switch (_Mode)
		{
		case EmptyMode:
			return Faild_EmptyObj;
		case UpdateMode:
		{
			_update();
			return Succeeded;
		}
		case AddNewMode:
		{
			if (doesClientExist(AccountNumber()))
				return Faild_AccountNumberIsUsed;

			_addNew();
			_Mode = enMode::UpdateMode;

			return enSaveResult::Succeeded;
		}
		}
	}

	bool Delete()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkedForDelete = true;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
		*this = _getEmptyClientObj();

		return true;
	}

	void deposit(double Amount)
	{
		_AccountBalance += Amount;
		save();
	}

	bool withdraw(double Amount)
	{
		if (_AccountBalance < Amount)
			return false;
		
		_AccountBalance -= Amount;
		save();
		return true;
	}

	bool transferTo(double TranferAmount, clsBankClient& ClientTo)
	{
		if (TranferAmount > AccountBalance)
			return false;
		else
		{
			withdraw(TranferAmount);
			ClientTo.deposit(TranferAmount);
			_saveTransfer(TranferAmount, ClientTo);
			return true;
		}
	}

	static vector<stTransferRecord> loadTransferRecord()
	{
		vector<stTransferRecord> vTransferRecords;
		fstream MyFile;
		MyFile.open("Transfer history.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
				vTransferRecords.push_back(_convertDataLineToTransferRecord(DataLine));

			MyFile.close();
		}
		
		return vTransferRecords;
	}
};

