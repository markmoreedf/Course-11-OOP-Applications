#pragma once

#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "MyInputLibrary.h"

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
            return _GetEmptyUserObj();

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
    static clsUser _GetEmptyUserObj()
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

    clsUser (enMode mode, string username, string password, string firstName, string lastName, string email, string phone, unsigned int permissions)
        : clsPerson(firstName, lastName, email, phone),
        _Mode(mode),
        _Username(username),
        _Password(password),
        _Permissions(permissions),
        _MarkForDelete(false)  { }

    
    void SetPassword(string Password) { _Password = Password; }
    string GetPassword() const { return _Password; }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    string GetUsername() const { return _Username; }
    __declspec(property(get = GetUsername)) string Username;   // read only property. no setter function. username is unique and should not be changed after creation

    void SetPermissions(unsigned int Permissions) { _Permissions = Permissions; }
    unsigned int GetPermissions() const { return _Permissions; }
    __declspec(property(get = GetPermissions, put = SetPermissions)) unsigned int Permissions;

    void MarkForDelete() { _MarkForDelete = true; }
    void UnMarkForDelete() { _MarkForDelete = false; }
    bool IsMarkedForDelete() const { return _MarkForDelete; }

    // Static Methods:
    static clsUser FindUser(const string& username)
    {
        vector<clsUser> vUsers = _LoadUsersFileToVecObjects();
        for (const clsUser& user : vUsers) {
            if (user.Username == username)
                return user;
        }
        return _GetEmptyUserObj();

    }
    static clsUser FindUser(const string& username, const string& password)
    {
        clsUser user = FindUser(username);

        if (user.Password == password)
            return user;

        return _GetEmptyUserObj();
    }

    static bool IsUserExist(const string& AccNo)
    {
        clsUser client = clsUser::FindUser(AccNo);
        return (!client.IsEmpty());
    }

    static clsUser GetAddNewUserObject(const string& username)
    {
        return clsUser(enMode::AddNewMode, username, "", "", "", "", "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersFileToVecObjects();
    }

  /*  static void SetUserPermissions(clsUser& user)
    {
        if (MyInputLibrary::ReadYesNo("Do you want to give full acess ? [y/n]"))
        {
            user.Permissions = 127;
        }
        else {
            if (MyInputLibrary::ReadYesNo("Give access to View Clients? [y/n]"))
                user.Permissions |= enUserPermissions::showClientList;
            else
                user.Permissions &= ~enUserPermissions::showClientList;

            if (MyInputLibrary::ReadYesNo("Give access to Find Clients? [y/n]"))
                user.Permissions |= enUserPermissions::findClient;
            else
                user.Permissions &= ~enUserPermissions::findClient;

            if (MyInputLibrary::ReadYesNo("Give access to Add Clients? [y/n]"))
                user.Permissions |= enUserPermissions::addClient;
            else
                user.Permissions &= ~enUserPermissions::addClient;

            if (MyInputLibrary::ReadYesNo("Give access to Delete Clients? [y/n]"))
                user.Permissions |= enUserPermissions::deleteClient;
            else
                user.Permissions &= ~enUserPermissions::deleteClient;

            if (MyInputLibrary::ReadYesNo("Give access to Update Clients? [y/n]"))
                user.Permissions |= enUserPermissions::updateClient;
            else
                user.Permissions &= ~enUserPermissions::updateClient;

            if (MyInputLibrary::ReadYesNo("Give access to Transactions? [y/n]"))
                user.Permissions |= enUserPermissions::transactions;
            else
                user.Permissions &= ~enUserPermissions::transactions;

            if (MyInputLibrary::ReadYesNo("Give access to Manage Users? [y/n]"))
                user.Permissions |= enUserPermissions::manageUsers;
            else
                user.Permissions &= ~enUserPermissions::manageUsers;

            user.Save();
        }
    }*/

    // Non Static Methods:

    bool IsEmpty() const { return _Mode == enMode::EmptyMode; }

    enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svUserNameExists = 2 };
    enSaveResults Save()
    {
        switch (_Mode)
        {
            case clsUser::EmptyMode:
            {
                return svFailedEmptyObject;
            }

            case clsUser::UpdateMode:
            {
                if (_Update())
                    return svSucceeded;
                else
                    return svFailedEmptyObject;
            }

            case clsUser::AddNewMode:
            {
                if (IsUserExist(this->_Username))
                    return svUserNameExists;
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return svSucceeded;
                }
            }

            default:
            {
                return svFailedEmptyObject;
            }

        }

    }

    enum enDeleteResults { dlSucceeded = 0, dlNotFound = 1, dlAdminDeleteAttempt = 2 };
    enDeleteResults Delete()
    {
        if (this->_Username == "admin") // prevent deleting admin users
            return dlAdminDeleteAttempt;

        vector <clsUser> vAllUsers = _LoadUsersFileToVecObjects();

        for (clsUser& user : vAllUsers) {
            if (user.Username == this->_Username)
            {
                    user.MarkForDelete();
                    _SaveVecClientsToFile(vAllUsers, false);
                    *this = _GetEmptyUserObj(); // reset the current object to empty state after deletion
                    return dlSucceeded;
            }
        }

        return dlNotFound;
    }


};

