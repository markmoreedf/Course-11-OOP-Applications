#include <iostream>
#include "clsUtility.h";
#include "clsBankClient.h";
#include "MyInputLibrary.h";

using namespace std;

static void ReadClientData(clsBankClient& client)
{
    cout << "Please enter the following client data:\n";
    client.FirstName = MyInputLibrary::ReadLine("First Name: ");
    client.LastName = MyInputLibrary::ReadLine("Last Name: ");
    client.Email = MyInputLibrary::ReadLine("Email: ");
    client.Phone = MyInputLibrary::ReadLine("Phone: ");
    client.Pincode = MyInputLibrary::ReadLine("Pin Code: ");
    client.Balance = MyInputLibrary::ReadPositiveDouble("Balance: ");
}
static void UpdateClientData()
{
    string AccountNumber; 
     
    AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
    clsBankClient client = clsBankClient::FindClient(AccountNumber);

    while (client.IsEmpty()) {
        cout << "Client with Account Number " << AccountNumber << " not found.\n";
        AccountNumber = MyInputLibrary::ReadLine("Enter Account number of the client to update: ");
        client = clsBankClient::FindClient(AccountNumber);
    }
    cout << "\nCurrent Client Data:\n";
    client.Print();

    cout << "Please enter new data for the client:\n";
    ReadClientData(client);

    clsBankClient::enSaveResults saveResult = client.Save();
    if (saveResult == clsBankClient::svSucceeded)
    {
        cout << "\nClient data updated successfully.\n";
        client.Print();
    }
    else
    {
        cout << "\nFailed to update client data.\n";
    }

}
static void AddNewClient()
{
    string AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
    while (clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "Account Number already exists. Please enter a different one.\n";
        AccountNumber = MyInputLibrary::ReadLine("Enter New Account Number: ");
    }
    clsBankClient newClient = clsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientData(newClient);

    clsBankClient::enSaveResults saveResult = newClient.Save();
    switch (saveResult)
    {
    case clsBankClient::svFailedEmptyObject:
        cout << "Failed to add new client. Empty object.\n";
        break;
    case clsBankClient::svSucceeded:
        cout << "New client added successfully.\n";
        break;
    case clsBankClient::svAccountNumberExists:
        cout << "Account Number already exists. Cannot add new client.\n";
        break;
    }


}

int main()
{
    UpdateClientData();
    return 0;
}