# 🏦 Simple Bank System (C++)

A comprehensive Banking Management System developed as part of the **Programming Advices** roadmap (Course 11). This project focuses on mastering Object-Oriented Programming (OOP) in C++ by building a real-world application.

## 📌 Project Overview
The goal of this project is to manage bank clients and users through a console interface, using **File Handling** for data persistence and **Inheritance** to structure the domain logic.

---

## 🛠 Features

### ✅ Currently Implemented
* **Client List:** View all clients in a formatted table. 📋
* **Add New Client:** Form-based entry for adding new records. ➕
* **Update Client:** Modify existing client details using their Account Number. ✏️
* **Find Client:** Search for specific clients quickly. 🔍
* **Object-Oriented Design:** * `clsPerson`: Base class for personal data.
    * `clsBankClient`: Derived class for banking-specific logic.
* **Delete Client:** Securely remove records from the system. 🗑️
* **Transactions Menu:**
    * Deposit & Withdraw logic. 💰
    * Total Balances view.

### ⏳ Coming Soon (Roadmap)
* **User Management:** Login system with different permissions/access levels. 🔑
* **Login Register:** Logging every login attempt to a file. 📝
* **Currency Exchange:** A specialized system for handling multiple currencies. 🌍

---

## 💻 Technical Skills Applied
* **File Streams (`fstream`):** Reading and writing data to `.txt` files. 📂
* **String Manipulation:** Using a custom `clsString` library for splitting and joining data. ✂️
* **Encapsulation:** Using private members and public `properties` for data safety. 🛡️
* **Static Members:** Efficiently managing shared file paths and delimiters.

---

## 📂 Project Structure
* `clsPerson.h`: The base class containing shared personal attributes.
* `clsBankClient.h`: The main logic for bank clients and file interactions.
* `clsUser.h`: User class for system administrator.
* `Clients.txt`: The text-based database for the system clients.
* `Users.txt`: The text-based database for the system users.
* Many classes for screen management, all of them inheriting the `ClsScreen.h` class.
* Helper Classes:
   * `MyInputLibrary.h`: Helper library for input validation.
   * `ClsString.h`: Helper library for advanced string operations.
   * `ClsTable.h`: Helper library for printing tables.
   * `ClsUtility.h`: Helper Utility library.

---

### 🎓 Note for Reviewers
I am currently working through the **Programming Advices** curriculum. As I learn new concepts like **Composition** and **Operator Overloading**, I will be updating this repository to reflect more advanced system features.
