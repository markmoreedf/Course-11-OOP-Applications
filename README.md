# Simple Bank System (C++)

This is a **console-based bank system** implemented in C++ for **learning purposes**.  
It focuses on practicing **object-oriented programming (OOP)** concepts such as classes, encapsulation, and basic file handling.

---

## Features

- Create a new bank client
- Update client information (balance, pin)
- Find clients by account number and/or pin
- Store client data in a file (`Clients.txt`)
- Simple, clean console output
- Defensive programming: ignores empty or corrupted lines in the data file

---

## Learning Goals

This project is designed to help understand:

- Classes and inheritance
- Constructors and member functions
- Access modifiers (`private`, `public`)
- Reference vs value parameters
- File I/O with `ifstream` and `ofstream`
- Encapsulation of data and behavior

---

## How to Use

1. Clone the repository
2. Open the solution in **Visual Studio**
3. Build and run the console application
4. Interact with the menu to add/update/find clients

---

## Project Structure

- `clsPerson.h` – Base class for personal information  
- `clsBankClient.h` – Main class for bank clients, inherits from `clsPerson`  
- `clsString.h` – Helper class for string operations  
- `Clients.txt` – Stores client data (generated automatically)  

---

## Notes

- This project is **not a real banking system**. It is purely for learning C++ and OOP.  
- The system does **not implement security measures** (e.g., hashing PINs).  
- Currently, negative balances are allowed; this can be improved in future versions.

---

## Future Improvements

- Deposit and withdraw methods with balance checks
- Transaction history logging
- PIN validation and encryption
- Console menu interface for better user interaction
