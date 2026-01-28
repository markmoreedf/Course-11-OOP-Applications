#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

class clsBankClient : public clsPerson
{
    // an info you will thank me later for it
    // firstName _Delimiter lastname _Delimiter email _Delimiter phone _Delimiter accountnumber _Delimiter pincode _Delimiter balance

private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _Pincode;
    double _Balance;

    inline static const string _ClientsFileName = "Clients.txt";
    inline static const string _Delimiter = "#//#";

    static vector<string>  _LoadFileDataToVecString(const string& dataFileName)
    {
        vector<string> clients;
        string dataLine = "";

        ifstream dataFile;
        dataFile.open(dataFileName);
        if (dataFile.is_open())
        {
            while (getline(dataFile, dataLine))
            {
                // never trust external data:    Files,    User input,    Network,    Sensors,    Even our own previous versions
                if (dataLine.empty())
                    continue; // skip empty lines. a data file after all

                // validate data line
                if (clsString::Split(dataLine, _Delimiter).size() != 7)
                    continue; // skip invalid data lines

                clients.push_back(dataLine);
            }
            dataFile.close();
        }

        // its better to seperarte object from UI responsibilities
        //else {
        //    cout << "Couldn't open the file (_LoadDataFileToVecString)\n";
        //}

        return clients;
    }
    static void _SaveDataLineToFile(const string& dataLine, const string& dataFileName, const bool& appendMode)
    {
        ofstream dataFile;
        if (appendMode)
            dataFile.open(dataFileName, ios::out | ios::app); // keep the old data and append new data
        else
            dataFile.open(dataFileName, ios::trunc); // overwrite the file

        if (dataFile.is_open())
        {
            dataFile << dataLine << endl;
            dataFile.close();
        }
        else {
            // cout << "Error occured while trying to open the output file\n";
        }
    }

    static clsBankClient _ConvertLineToBankClientObject(const string& Line)
    {
        vector <string> vClientData = clsString::Split(Line, _Delimiter);

        // Expected Data Members Count = 7
        if (vClientData.size() != 7)
            return _GetEmptyClientObj();

        return (clsBankClient(enMode::UpdateMode,
            vClientData[0],
            vClientData[1],
            vClientData[2],
            vClientData[3],
            vClientData[4],
            vClientData[5],
            stod(vClientData[6])));
    }
    static string _ConvertBankClientObjectToLine(const clsBankClient& cl)
    {
        string lineOfData = "";
        lineOfData += cl.FirstName + _Delimiter;
        lineOfData += cl.LastName + _Delimiter;
        lineOfData += cl.Email + _Delimiter;
        lineOfData += cl.Phone + _Delimiter;
        lineOfData += cl.AccountNumber + _Delimiter;
        lineOfData += cl.Pincode + _Delimiter;
        lineOfData += to_string(cl.Balance);
        return lineOfData;
    }
    static clsBankClient _GetEmptyClientObj()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static vector<clsBankClient> _LoadClientsFileToVecObjects() 
    {
        vector<string> dataLines = _LoadFileDataToVecString(_ClientsFileName);

        vector<clsBankClient> clients;

        for (const string& line : dataLines) {
            clients.push_back(_ConvertLineToBankClientObject(line));
        }
        return clients;
    }
    void _SaveVecClientsToFile(const vector<clsBankClient>& clients, bool appendMode) const
    {
        ofstream dataFile;
        if (appendMode)
            dataFile.open(_ClientsFileName, ios::out | ios::app); // keep the old data and append new data
        else
            dataFile.open(_ClientsFileName, ios::trunc); // overwrite the file
        if (dataFile.is_open())
        {
            for (const clsBankClient & cl : clients) {

                dataFile << _ConvertBankClientObjectToLine(cl) << endl;
            }
            dataFile.close();

        }
    }
    bool _Update()
    {
        vector<clsBankClient> clients = _LoadClientsFileToVecObjects();

        for (clsBankClient& cl : clients) {
            if (cl.AccountNumber == this->AccountNumber) {
                cl = *this;
                _SaveVecClientsToFile(clients, false);
                return true;
            }
        }
        return false;
    }
    void _AddNew() const
    {
        _SaveDataLineToFile(_ConvertBankClientObjectToLine(*this), _ClientsFileName, true);
    }

    public:
        clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string Pincode, double Balance)
            : clsPerson(FirstName, LastName, Email, Phone)
        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _Pincode = Pincode;
            _Balance = Balance;
        }

        void SetPincode(string Pincode) { _Pincode = Pincode; }
        void SetBalance(double Balance) { _Balance = Balance; }

        string GetAccountNumber() const { return _AccountNumber; }
        string GetPincode() const { return _Pincode; }
        double GetBalance() const { return _Balance; }

        __declspec(property(get = GetAccountNumber)) string AccountNumber;
        __declspec(property(get = GetPincode, put = SetPincode)) string Pincode;
        __declspec(property(get = GetBalance, put = SetBalance)) double Balance;

        bool IsEmpty() const { return _Mode == enMode::EmptyMode; }

        void Print() const
        {
            cout << "=============================\n";
            cout << "First Name   : " << FirstName << endl;
            cout << "Last Name    : " << LastName << endl;
            cout << "Email        : " << Email << endl;
            cout << "Phone        : " << Phone << endl;
            cout << "Account No.  : " << AccountNumber << endl;
            cout << "Pincode      : " << Pincode << endl;
            cout << "Balance      : " << Balance << endl;
            cout << "=============================\n";
        }

        static clsBankClient FindClient(const string & AccountNumber)
        {
            vector<clsBankClient> clients = _LoadClientsFileToVecObjects();
            for (const clsBankClient& cl : clients) {
                if (cl.AccountNumber == AccountNumber)
                    return cl;
            }
            return _GetEmptyClientObj();

        }
        static clsBankClient FindClient(const string & AccountNumber, const string & pincode)
        {
            clsBankClient client = FindClient(AccountNumber);

            if (client.Pincode == pincode)
                return client;

            return _GetEmptyClientObj();
        }

        static bool IsClientExist(const string & AccNo)
        {
            clsBankClient client = clsBankClient::FindClient(AccNo);
            return (!client.IsEmpty());
        }

        enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svAccountNumberExists = 2 };
        enSaveResults Save()
        {
            switch (_Mode)
            {
            case clsBankClient::EmptyMode:
                return svFailedEmptyObject;

            case clsBankClient::UpdateMode:
            
                if (_Update())
                    return svSucceeded;
                else
                    return svFailedEmptyObject;
            
                
            case clsBankClient::AddNewMode: 
                if (IsClientExist(this->AccountNumber))
                    return svAccountNumberExists;
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return svSucceeded;
                }

            default:
                return svFailedEmptyObject;
            
            }
            
        }

        static clsBankClient GetAddNewClientObject(const string & AccountNumber)
        {
            return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
        }


};