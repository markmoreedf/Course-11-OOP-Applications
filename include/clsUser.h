#pragma once
#include "clsPerson.h"
class clsUser :public clsPerson
{
private:
    string _Username;
    string _Password;

    void _SetUsername(string Username) { _Username = Username; }

public:
    clsUser(string FirstName, string LastName, string Email, string Phone, string Username, string Password) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Username = Username;
        _Password = Password;
    }
    void SetPassword(string Password) { _Password = Password; }
    string GetUsername() const { return _Username; }
    string GetPassword() const { return _Password; }
     __declspec(property(get= GetUsername) ) string Username;
     __declspec(property(get = GetPassword, put = SetPassword)) string Password;

};

