// school information system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <regex>

using namespace std;

struct students {
    string Name;
    string Password;
    int ID;
};
struct parents {
    string Name;
    string Password;
    int ID;
};
struct teachers {
    string Name;
    string Password;
    int ID;
};
struct admins {
    string Name;
    string Password;
    int ID;
};
enum class AccountType
{
    STUDENT,
    TEACHER,
    PARENT
};

void login();
void sLogin(int x) {}
void pLogin(int x) {}
void tLogin(int x) {}
void aLogin(int x) {}
void registerAccount();
void registerNewAccount(const AccountType);
void registerTeacherAccount() {}
void registerParentAccount() {}
bool isAlphabet(const std::string&);
bool containsNumber(const std::string&);
bool onlyNumbers(const std::string&);
int generateID(const std::vector<int>&, const AccountType);
std::vector<int> readExistingIDs(const std::string&);
void news();
void placeCursor(HANDLE, int, int);









































































































































































































































































































































































































































































































































































































































































































































































int main()
{
    string school = "Regular High School";
    int choice;

    do {
        cout << "\t" << school << endl;
        for (int i = 0; i < school.length() + 16; i++) {
            cout << "*";
        }
        cout << endl << endl;
        cout << "1. Log In" << endl << "2. Register New Account" << endl << "3. Events & News" << endl << "4. Exit" << endl << endl;
        cout << "Make your choice : ";

        // Perform numeric range check
        while (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(1, '\n');
            std::cout << "Invalid choice. Please enter a number (1 - 4): ";
        }

        switch (choice) {
        case 1: {
            login();
            break;
        }
        case 2: {
            registerAccount();
            break;
        }
        case 3: {
            news();
            break;
        }
        }
    } while (choice != 4);
}

// Menu to register accounts
void registerAccount()
{
    int choice;

    system("cls");
    cout << "\tRegister New Account" << std::endl;
    cout << "\n1. Student\n2. Teacher\n3. Parent\n4. Cancel" << std::endl;
    cout << "Choice: ";

    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cin.clear();
        std::cin.ignore(1, '\n');
        std::cout << "Invalid choice. Please enter a number (1 - 4): ";
    }

    switch (choice) {
    case 1: {
        registerNewAccount(AccountType::STUDENT);
        break;
    }
    case 2: {
        registerNewAccount(AccountType::TEACHER);
        break;
    }
    case 3: {
        registerNewAccount(AccountType::PARENT);
        break;
    }
    case 4: {
        break;
    }
    }
}
void login()
{
    int ID;
    int t = 0;
    vector<students> vS;
    vector<parents> vP;
    vector<teachers> vT;
    vector<admins> vA;
    string password;
    int length;
    ifstream inputFile(" ");
    std::system("cls");
    std::cout << "\tLogin" << std::endl;
    std::cout << "\nEnter your ID" << std::endl;
    cin >> ID;
    std::cout << "\nEnter your Password" << std::endl;
    cin >> password;

    length = to_string(ID).length();
    switch (length) {
    case 6: {
        ifstream sInputFile("students.txt");
        if (sInputFile.is_open()) {
            string line;
            while (getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                students s;
                getline(iss, s.Name, ',');


                getline(iss, s.Password, ',');

                getline(iss, value, ',');
                s.ID = stoi(value);

                vS.push_back(s);
            }
            for (int i = 0; i < vS.size(); i++) {
                cout << vS[i].ID << endl;
                cout << vS[i].Password << endl;
                if (vS[i].ID == ID && vS[i].Password == password) {
                    sLogin(i);
                    t++;
                    system("cls");
                    cout << "Successfully Logged In" << endl;
                }
            }
            if (t == 0) {
                cout << "Failed to Login" << endl << endl;
                break;
            }
        }
        else {
            std::cout << "Failed to open students.txt" << std::endl;
        }
        break;
    }
    case 5: {
        ifstream pInputFile("parents.txt");
        if (pInputFile.is_open()) {
            string line;
            while (getline(pInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                parents p;
                getline(iss, p.Name, ',');


                getline(iss, p.Password, ',');

                getline(iss, value, ',');
                p.ID = stoi(value);

                vP.push_back(p);
            }
            for (int i = 0; i < vP.size(); i++) {
                if (vP[i].ID == ID && vP[i].Password == password) {
                    pLogin(i);
                    t++;
                    system("cls");
                    cout << "Successfully Logged In" << endl;
                }
            }
            if (t == 0) {
                cout << "Failed to Login" << endl << endl;
                break;
            }
        }
        else {
            std::cout << "Failed to open parents.txt" << std::endl;
        }
        break;
    }
    case 4: {
        std::ifstream tInputFile("teachers.txt");
        if (tInputFile.is_open()) {
            string line;
            while (getline(tInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                teachers t;
                getline(iss, t.Name, ',');


                getline(iss, t.Password, ',');

                getline(iss, value, ',');
                t.ID = stoi(value);

                vT.push_back(t);
            }
            for (int i = 0; i < vT.size(); i++) {
                if (vT[i].ID == ID && vT[i].Password == password) {
                    tLogin(i);
                    t++;
                    system("cls");
                    cout << "Successfully Logged In" << endl;
                }
            }
            if (t == 0) {
                cout << "Failed to Login" << endl << endl;
                break;
            }
        }
        else {
            std::cout << "Failed to open teachers.txt" << std::endl;
        }
        break;
    }
    case 3: {
        std::ifstream aInputFile("admins.txt");
        if (aInputFile.is_open()) {
            string line;
            while (getline(aInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                admins a;
                getline(iss, a.Name, ',');


                getline(iss, a.Password, ',');

                getline(iss, value, ',');
                a.ID = stoi(value);

                vA.push_back(a);
            }
            for (int i = 0; i < vA.size(); i++) {
                if (vA[i].ID == ID && vA[i].Password == password) {
                    aLogin(i);
                    t++;
                    system("cls");
                    cout << "Successfully Logged In" << endl;
                }
            }
            if (t == 0) {
                cout << "Failed to Login" << endl << endl;
                break;
            }
        }
        else {

            std::cout << "Failed to open admins.txt" << std::endl;
        }
        break;
    } Default: {
        cout << "Failed to login" << endl << endl;
    }



    }
}

void registerNewAccount(const AccountType accountType)
{
    std::system("cls");
    std::string fname, lname, password, addressNum, addressName, contactNum, childID;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string fileName;

    if (accountType == AccountType::STUDENT) {
        std::cout << "\tStudent Registry" << std::endl;
        fileName = "students.txt";
    }
    else if (accountType == AccountType::TEACHER) {
        std::cout << "\tTeacher Registry" << std::endl;
        fileName = "teachers.txt";
    }
    else if (accountType == AccountType::PARENT) {
        std::cout << "\tParent Registry" << std::endl;
        fileName = "parents.txt";
    }
    std::cout << "********************************" << std::endl << "Please Enter Your Details";

    placeCursor(screen, 4, 0);
    std::cout << "NAME" << std::endl;
    std::cout << "First Name:                    Last Name:" << std::endl;

    if (accountType == AccountType::TEACHER || accountType == AccountType::PARENT) {
        std::cout << "Contact Number:";
    }
    if (accountType == AccountType::PARENT) {
        placeCursor(screen, 7, 0);
        std::cout << "Child's Student ID:";
    }

    placeCursor(screen, 8, 0);
    std::cout << "ADDRESS" << std::endl;
    std::cout << "Street Number:               Street Name:";

    placeCursor(screen, 11, 0);
    std::cout << "Password: ";

    // First name input
    placeCursor(screen, 5, 12);
    std::getline(std::cin >> std::ws, fname);
    while (!isAlphabet(fname)) {
        placeCursor(screen, 13, 0);
        std::cout << "Invalid name. Please only use alphabet characters.";
        placeCursor(screen, 5, 0);
        std::cout << "First Name:                    Last Name:";
        placeCursor(screen, 5, 12);
        std::getline(std::cin >> std::ws, fname);
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    // Last name input
    placeCursor(screen, 5, 42);
    std::getline(std::cin >> std::ws, lname);
    while (!isAlphabet(lname)) {
        placeCursor(screen, 13, 0);
        std::cout << "Invalid name. Please only use alphabet characters.";
        placeCursor(screen, 5, 30);
        std::cout << " Last Name:                                       ";
        placeCursor(screen, 5, 42);
        std::getline(std::cin >> std::ws, lname);
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    // Teacher/Parent contact number input
    if (accountType == AccountType::TEACHER || accountType == AccountType::PARENT) {
        placeCursor(screen, 6, 16);
        std::getline(std::cin >> std::ws, contactNum);
        while (!onlyNumbers(contactNum) || contactNum.length() < 7) {
            placeCursor(screen, 13, 0);
            std::cout << "Invalid input. The input should consist of only numbers with a minimum length of 7 digits.";
            placeCursor(screen, 6, 0);
            std::cout << "Contact Number:                                 ";
            placeCursor(screen, 6, 16);
            std::getline(std::cin >> std::ws, contactNum);
        }
        placeCursor(screen, 13, 0);
        std::cout << "                                                                                                ";
    }

    // Parent: child ID input
    if (accountType == AccountType::PARENT) {
        placeCursor(screen, 7, 20);
        std::getline(std::cin >> std::ws, childID);
        std::vector<int> studentIDs = readExistingIDs("students.txt");
        bool isValid = false;
        int childIDInt;


        while (!isValid) {
            std::istringstream(childID) >> childIDInt;
            for (int i : studentIDs) {
                if (i == childIDInt) {
                    isValid = true;
                    break;
                }
            }
            if (isValid) { break; }
            placeCursor(screen, 13, 0);
            std::cout << "ID does not match any current students. (The input should consist of only numbers with a length of 6 digits)";
            placeCursor(screen, 7, 0);
            std::cout << "Child's Student ID:                ";
            placeCursor(screen, 7, 20);
            std::getline(std::cin >> std::ws, childID);
        }
        placeCursor(screen, 13, 0);
        std::cout << "                                                                                                                   ";
    }

    // Address number input
    placeCursor(screen, 9, 15);
    std::getline(std::cin >> std::ws, addressNum);
    while (!containsNumber(addressNum)) {
        placeCursor(screen, 13, 0);
        std::cout << "Invalid input. Must contain at least one number.";
        placeCursor(screen, 9, 0);
        std::cout << "Street Number:          ";
        placeCursor(screen, 9, 15);
        std::getline(std::cin >> std::ws, addressNum);
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    // Address name input
    placeCursor(screen, 9, 42);
    std::getline(std::cin >> std::ws, addressName);
    while (!isAlphabet(addressName)) {
        placeCursor(screen, 13, 0);
        std::cout << "Invalid name. Please only use alphabet characters. ";
        placeCursor(screen, 9, 28);
        std::cout << " Street Name:                                       ";
        placeCursor(screen, 9, 42);
        std::getline(std::cin >> std::ws, addressName);
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    // Password input
    placeCursor(screen, 11, 10);
    std::getline(std::cin >> std::ws, password);
    while (password.length() < 8) {
        placeCursor(screen, 13, 0);
        std::cout << "Password needs to be at least 8 characters. ";
        placeCursor(screen, 11, 0);
        std::cout << "Password:         ";
        placeCursor(screen, 11, 10);
        std::getline(std::cin >> std::ws, password);
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    int userID;
    std::vector<int> existingIDs;

    existingIDs = readExistingIDs(fileName);
    userID = generateID(existingIDs, accountType);
    
    // Open the file in append mode
    std::ofstream outputFile(fileName, std::ios_base::app);

    // Check if the file was opened successfully
    if (outputFile.is_open())
    {
        // Write the account information to the file
        if (accountType == AccountType::STUDENT) {
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << std::endl;
        }
        else if (accountType == AccountType::TEACHER) {
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << "," << contactNum << std::endl;
        }
        else if (accountType == AccountType::PARENT) {
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << "," << contactNum << "," << childID << std::endl;
        }

        // Close the file
        outputFile.close();

        placeCursor(screen, 13, 0);
        std::cout << "Account registered successfully!\nPlease wait while an administrator verifies your account." << std::endl << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::system("cls");

    }
    else
    {
        std::system("cls");
        std::cout << "Error opening the file." << std::endl << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::system("cls");
        
    }
}

// Function to check if an input is alphabet characters and hyphen only
bool isAlphabet(const std::string& input)
{
    std::regex pattern("^[a-zA-Z -]+$");
    return std::regex_match(input, pattern);
}

// Function to check if input contains at least one number
bool containsNumber(const std::string& input) {
    for (char c : input) {
        if (std::isdigit(c)) {
            return true;
        }
    }
    return false;
}

// Function to check if input contains only numbers
bool onlyNumbers(const std::string& input) {
    for (char c : input) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Function to generate a random 6-digit student ID
int generateID(const std::vector<int>& existingIDs, const AccountType accountType)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int userID;
    bool idExists;

    do {
        if (accountType == AccountType::STUDENT) {
            userID = rand() % 900000 + 100000;
        }
        else if (accountType == AccountType::TEACHER) {
            userID = rand() % 9000 + 1000;
        }
        else if (accountType == AccountType::PARENT) {
            userID = rand() % 90000 + 10000;
        }
        // Check if the generated ID already exists
        idExists = false;
        for (int id : existingIDs) {
            if (id == userID) {
                idExists = true;
                break;
            }
        }
    } while (idExists);

    return userID;
}

// Function to read existing student IDs from the file
std::vector<int> readExistingIDs(const std::string& fileName)
{
    std::vector<int> existingIDs;
    std::ifstream inputFile(fileName);
    std::string line;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string token;

        // Get ID number
        if (std::getline(iss, token, ',')) {
            try {
                // Convert string to int
                int userID = std::stoi(token);
                // Add to ID vector
                existingIDs.push_back(userID);
            }
            catch (const std::exception& e) {
                // Handle the exception (e.g., print an error message)
                std::cerr << "Error converting string to integer: " << e.what() << std::endl;
            }
        }
    }

    inputFile.close();
    return existingIDs;
}

void news()
{
    std::system("cls");
    std::cout << "\tEVENTS & NEWS" << std::endl << std::endl;
    std::cout << "There's nothing here yet. Check back later." << std::endl << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.ignore(1, '\n');
    std::cin.get();
    std::system("cls");
}

// Function to place the cursor
void placeCursor(HANDLE screen, int row, int col)
{
    COORD position;
    position.Y = row;
    position.X = col;
    SetConsoleCursorPosition(screen, position);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
