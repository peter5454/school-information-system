// school information system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
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


void login();

void viewReport(int p) {}
void viewClass(int p) {}
void updatePersonalInformation(int p) {}
void sSLogin(int p) {
    int choice;
    vector<students> vS;
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
        do {
            system("cls");
            cout << "\t" << "Welcome " << vS[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Report" << endl << "2. View Class" << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
            cout << "Make your choice : ";

            // Perform numeric range check
            while (!(std::cin >> choice) || choice < 1 || choice > 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 5): ";
            }

            switch (choice) {
            case 1: {
                viewReport(p);
                break;
            }
            case 2: {
                viewClass(p);
                break;
            }
            case 3: {
                updatePersonalInformation(p);
                break;
            }
            }
        } while (choice <= 3);
        if (choice == 4) {

        }
        else {
            exit(0);
        }
    }
}

void sPLogin(int p) {
    int choice;
    vector<parents> vP;
    ifstream pInputFile("parents.txt");
    if (pInputFile.is_open()) {
        string line;
        while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            parents p;
            getline(iss, p.Name, ',');


            getline(iss, p.Password, ',');

            getline(iss, value, ',');
            p.ID = stoi(value);

            vP.push_back(p);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vP[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Your Child's Report" << endl << "2. View your Child's Class" << endl << "3. View Messages " << endl << "4. Message Your Child's Teacher " << endl <<"5. Update Personal Information" << endl << "6. Logout" << endl << "7. Exit" << endl << endl;
            cout << "Make your choice : ";

            // Perform numeric range check
            while (!(std::cin >> choice) || choice < 1 || choice > 7) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 7): ";
            }

            switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            }
        } while (choice <= 5);
        if (choice == 6) {

        }
        else {
            exit(0);
        }
    }
}

void sTLogin(int p) {
    int choice = 0;
    vector<teachers> vT;
    ifstream tInputFile("teachers.txt");
    if (tInputFile.is_open()) {
        string line;
        while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            teachers t;
            getline(iss, t.Name, ',');


            getline(iss, t.Password, ',');

            getline(iss, value, ',');
            t.ID = stoi(value);

            vT.push_back(t);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vT[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Class/Students" << endl << "2. Add/Update Reports" << endl << "3. View Reports " << endl << "4. Update Personal Information " << endl << "5. View Messages " << endl << "6. Send Messages " << endl << "7. Logout" << endl << "8. Exit" << endl << endl;
            cout << "Make your choice : ";

            // Perform numeric range check
            while (!(std::cin >> choice) || choice < 1 || choice > 8) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 8): ";
            }

            switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            }
        } while (choice <= 6);
        if (choice == 7) {

        }
        else {
            exit(0);
        }
    }
}

void sALogin(int p) {
    int choice = 0;
    vector<admins> vA;
    ifstream aInputFile("admins.txt");
    if (aInputFile.is_open()) {
        string line;
        while (getline(aInputFile, line)) { //Gathers all of the admins names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            admins a;
            getline(iss, a.Name, ',');


            getline(iss, a.Password, ',');

            getline(iss, value, ',');
            a.ID = stoi(value);

            vA.push_back(a);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome Admin!";
            cout << endl << endl;
            cout << "1. Manage School Information" << endl << "2. Manage Students" << endl << "3. Manage Teachers " << endl << "4. Manage Parents " << endl << "5. Manage classes " << endl <<"6. View Messages " << endl << "7. Send Messages " << endl << "8. View Reports" << endl << "9. Update News/Events" << endl << "10. Update Personal Information " << endl << "11. Logout" << endl << "12. Exit" << endl << endl;
            cout << "Make your choice : ";

            // Perform numeric range check
            while (!(std::cin >> choice) || choice < 1 || choice > 12) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 12): ";
            }

            switch (choice) {
            case 1: {
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                break;
            }
            case 6: {
                break;
            }
            case 7: {
                break;
            }
            case 8: {
                break;
            }
            case 9: {
                break;
            }
            case 10: {
                break;
            }

            }
        } while (choice <= 10);
        if (choice == 11) {

        }
        else {
            exit(0);
        }
    }
}

void sLogin(string password, int ID) {
    int t = 0;
    vector<students> vS;
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
            if (vS[i].ID == ID && vS[i].Password == password) {
                sSLogin(i);
                t++;
                system("cls");
            }
        }
        if (t == 0) {
            system("cls");
            cout << "Failed to Login" << endl << endl;
        }
    }
    else {
        cout << "Failed to open students.txt" << std::endl;
    }
}
void pLogin(string password, int ID) {
    int t = 0;
    vector<parents> vP;
    ifstream pInputFile("parents.txt");
    if (pInputFile.is_open()) {
        string line;
        while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
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
                sPLogin(i);
                t++;
                system("cls");
            }
        }
        if (t == 0) {
            system("cls");
            cout << "Failed to Login" << endl << endl;
           
        }
    }
    else {
        cout << "Failed to open parents.txt" << endl;
    }
}
void tLogin(string password, int ID) {
    int t = 0;
    vector<teachers> vT;
    ifstream tInputFile("teachers.txt");
    if (tInputFile.is_open()) {
        string line;
        while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
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
                sTLogin(i);
                t++;
                system("cls");
            }
        }
        if (t == 0) {
            system("cls");
            cout << "Failed to Login" << endl << endl;
        }
    }
    else {
        cout << "Failed to open teachers.txt" << std::endl;
    }
}
void aLogin(string password, int ID) {
    int t = 0;
    vector<admins> vA;
    ifstream aInputFile("admins.txt");
    if (aInputFile.is_open()) {
        string line;
        while (getline(aInputFile, line)) { //Gathers all of the admins names, passwords and IDs then assigns them to their respected variables.
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
                sALogin(i);
                t++;
                system("cls");
            }
        }
        if (t == 0) {
            system("cls");
            cout << "Failed to Login" << endl << endl;
        }
    }
    else {

        cout << "Failed to open admins.txt" << std::endl;
    }
}

void registerAccount();
void registerStudentAccount();
void registerTeacherAccount() {}
void registerParentAccount() {}

int generateStudentID(const std::vector<int>&);
std::vector<int> readExistingStudentIDs();
void news();

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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

void registerAccount()
{
    int choice;

    system("cls");
    cout << "\tRegister New Account" << std::endl;
    cout << "\n1. Register Student\n2. Register Teacher\n3. Register Parent\n4. Cancel" << std::endl;

    while (!(std::cin >> choice) || choice < 1 || choice > 4) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number (1 - 4): ";
    }

    switch (choice) {
    case 1: {
        registerStudentAccount();
        break;
    }
    case 2: {
        registerTeacherAccount();
        break;
    }
    case 3: {
        registerParentAccount();
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
    string password;
    int length;

    system("cls");
    cout << "\tLogin" << endl;
    std::cout << "************************" << std::endl;
    cout << "\nEnter your ID" << endl;
    cin >> ID;
    cout << "\nEnter your Password" << endl;
    cin >> password;

    length = to_string(ID).length();
    switch (length) {
    case 6: {
        sLogin(password, ID);
        break;
    }
    case 5: {
        pLogin(password, ID);
        break;
    }
    case 4: {
        tLogin(password, ID);
        break;
    }
    case 3: {
        aLogin(password, ID);
        break;
    } 
    default: {
        cout << "Failed to login" << endl << endl;
    }

    }
}

void registerStudentAccount()
{
    std::system("cls");
    std::string fname, lname, password;

    std::cout << "\tStudent Registry" << std::endl;
    std::cout << "********************************" << std::endl;
    std::cout << "Enter your first name: ";
    std::getline(std::cin >> std::ws, fname);

    std::cout << "Enter your last name: ";
    std::getline(std::cin >> std::ws, lname);

    std::cout << "Enter your password: ";
    std::getline(std::cin >> std::ws, password);

    std::vector<int> existingIDs = readExistingStudentIDs();
    int studentID = generateStudentID(existingIDs);

    // Open the file in append mode
    std::ofstream outputFile("students.txt", std::ios_base::app);

    // Check if the file was opened successfully
    if (outputFile.is_open())
    {
        // Write the account information to the file
        outputFile << fname << " " << lname << "," << password << "," << studentID << std::endl;

        // Close the file
        outputFile.close();

        std::system("cls");
        std::cout << "Account registered successfully!\nPlease wait while an administrator assigns you to a class." << std::endl << std::endl;
    }
    else
    {
        std::system("cls");
        std::cout << "Error opening the file." << std::endl << std::endl;
    }

}

// Function to generate a random 6-digit student ID
int generateStudentID(const std::vector<int>& existingIDs)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int studentID;
    bool idExists;

    do {
        studentID = rand() % 900000 + 100000;

        // Check if the generated ID already exists
        idExists = false;
        for (int id : existingIDs) {
            if (id == studentID) {
                idExists = true;
                break;
            }
        }
    } while (idExists);

    return studentID;
}

// Function to read existing student IDs from the file
std::vector<int> readExistingStudentIDs()
{
    std::vector<int> existingIDs;
    std::ifstream inputFile("students.txt");
    std::string line;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string token;

        // Skip the first two values on the line
        std::getline(iss, token, ',');
        std::getline(iss, token, ',');

        // Get the third value (studentID)
        std::getline(iss, token, ',');

        try {
            int studentID = std::stoi(token);
            existingIDs.push_back(studentID);
        }
        catch (const std::exception& e) {
            // Handle the exception (e.g., print an error message)
            std::cerr << "Error converting string to integer: " << e.what() << std::endl;
        }
    }

    inputFile.close();
    return existingIDs;
}

void news()
{
    std::cout << "NEWS" << std::endl;
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
