#include <iostream>
#include "clsUtility.h"
#include "clsBankClient.h"
#include "MyInputLibrary.h"
#include "clsMainScreen.h"

using namespace std;




//static void DeleteClient()
//{
//    string AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
//    clsBankClient client = clsBankClient::FindClient(AccountNumber);
//    while(client.IsEmpty())
//    {
//        cout << "Client with Account Number " << AccountNumber << " not found.\n";
//        AccountNumber = MyInputLibrary::ReadLine("Enter Account Number of the client to delete: ");
//        client = clsBankClient::FindClient(AccountNumber);
//    }
//
//    cout << "\nClient Data:\n";
//    client.Print();
//
//    if (! MyInputLibrary::YesNo("Are you sure you want to delete this client? (Y/N): "))
//        return;
//
//    if (client.Delete())
//        cout << "Client deleted successfully.\n";
//    else 
//        cout << "Failed to delete client.\n";
//    
//}



int main()
{
    clsMainScreen::ShowMainMenue();
    return 0;
}