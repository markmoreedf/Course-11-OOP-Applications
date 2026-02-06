#pragma once

#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

class clsUser :public clsPerson
{
    // clients data written in the file as follows: 
    // username _Delimiter password _Delimiter firstName _Delimiter lastname _Delimiter email _Delimiter phone _Delimiter permissions

private:
    inline static const string _UsersFileName = "data/Users.txt";
    inline static const string _Delimiter = "#//#";
    static enum enUserPermissions
    {
        showClientList = 0b0000001,
        findClient     = 0b0000010,
        addClient      = 0b0000100,
        updateClient   = 0b0001000,
        deleteClient   = 0b0010000,
        transactions   = 0b0100000,
        manageUsers    = 0b1000000
    };

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _Username;
    string _Password;
    unsigned int _Permissions;
    bool _MarkForDelete = 0;

    static vector<string>  _LoadFileDataToVecString(const string& dataFileName)
    {
        vector<string> vUsers;
        string dataLine = "";

        ifstream dataFile;
        dataFile.open(dataFileName);
        if (dataFile.is_open())
        {
            while (getline(dataFile, dataLine))
            {
                // never trust external data:
                if (dataLine.empty())
                    continue;

                // validate data line
                if (clsString::Split(dataLine, _Delimiter).size() != 7)
                    continue; // skip invalid data lines

                vUsers.push_back(dataLine);
            }
            dataFile.close();
        }
        return vUsers;
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

    }

    static clsUser _ConvertLineToUserObject(const string & dataLine)
    {
        vector <string> vUserData = clsString::Split(dataLine, _Delimiter);

        // Expected Data Members Count = 7
        if (vUserData.size() != 7)
            return _GetEmptyClientObj();

        return clsUser(enMode::UpdateMode,
            vUserData[0],
            vUserData[1],
            vUserData[2],
            vUserData[3],
            vUserData[4],
            vUserData[5],
            (unsigned int) stoi(vUserData[6]));
    }
    static string _ConvertUserObjectToLine(const clsUser & user)
    {
        string lineOfData = "";
        lineOfData += user._Username + _Delimiter;
        lineOfData += user._Password + _Delimiter;
        lineOfData += user.FirstName + _Delimiter;
        lineOfData += user.LastName + _Delimiter;
        lineOfData += user.Email + _Delimiter;
        lineOfData += user.Phone + _Delimiter;
        lineOfData += to_string(user._Permissions);
        return lineOfData;
    }
    static clsUser _GetEmptyClientObj()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static vector<clsUser> _LoadUsersFileToVecObjects()
    {
        vector<string> dataLines = _LoadFileDataToVecString(_UsersFileName);

        vector<clsUser> vUsers;

        for (const string& line : dataLines) {
            vUsers.push_back(_ConvertLineToUserObject(line));
        }
        return vUsers;
    }
    void _SaveVecClientsToFile(const vector<clsUser>& vUsers, bool appendMode) const
    {
        ofstream dataFile;
        if (appendMode)
            dataFile.open(_UsersFileName, ios::out | ios::app); // keep the old data and append new data
        else
            dataFile.open(_UsersFileName, ios::trunc); // overwrite the file
        if (dataFile.is_open())
        {
            for (const clsUser& user : vUsers) {

                if (user._MarkForDelete)
                    continue;

                dataFile << _ConvertUserObjectToLine(user) << endl;
            }
            dataFile.close();

        }
    }

    bool _Update()
    {
        vector<clsUser> vUsers = _LoadUsersFileToVecObjects();

        for (clsUser& user : vUsers) {
            if (user.Username == this->_Username) {
                user = *this;
                _SaveVecClientsToFile(vUsers, false);
                return true;
            }
        }
        return false;
    }
    void _AddNew() const
    {
        _SaveDataLineToFile(_ConvertUserObjectToLine(*this), _UsersFileName, true);
    }

public:

public:
    clsUser (enMode mode, string username, string password, string firstName, string lastName, string email, string phone, unsigned int permissions)
        : clsPerson(firstName, lastName, email, phone),
        _Mode(mode),
        _Username(username),
        _Password(password),
        _Permissions(permissions),
        _MarkForDelete(false)  { }

    
    void SetPassword(string Password) { _Password = Password; }
    string GetPassword() const { return _Password; }
    string GetUsername() const { return _Username; }
    __declspec(property(get = GetUsername)) string Username;   // read only property. no setter function. username is unique and should not be changed after creation
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    bool IsEmpty() const { return _Mode == enMode::EmptyMode; }

};

