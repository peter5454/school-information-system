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
void login();
void sLogin(int x) {}
void pLogin(int x) {}
void tLogin(int x) {}
void aLogin(int x) {}
void registerAccount();
void registerStudentAccount();
void registerTeacherAccount() {}
void registerParentAccount() {}
int generateStudentID(const std::vector<int>&);
std::vector<int> readExistingStudentIDs();
void news();
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

// Menu to register accounts
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
        outputFile << studentID << "," << fname << " " << lname << "," << password <<   std::endl;

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
    std::system("cls");
    std::cout << "\tEVENTS & NEWS" << std::endl << std::endl;
    std::cout << "There's nothing here yet. Check back later." << std::endl << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    std::system("cls");
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
