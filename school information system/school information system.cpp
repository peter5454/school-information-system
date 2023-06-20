// school information system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <regex>

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
struct Students {
    int ID;
    string Name;
    string Password;
    string Address;
    int Class;
};
struct Parents {
    int ID;
    string Name;
    string Password;
    string Address;
    int cNumber;
    int childID;
};
struct Teachers {
    int ID;
    string Name;
    string Password;
    int Class;
};
struct Admins {
    int ID;
    string Name;
    string Password;
    string SchoolName;
};
struct Messages {
    int sentID;
    int recipientID;
    bool isRead;
    string message;
};
enum class AccountType
{
    STUDENT,
    TEACHER,
    PARENT
};
enum class informationType
{
    PASSWORD,
    ADDRESS,
    CONTACTNUMBER
};
void mainMenu();
void pressEnter();
int choiceCheck(int);
void registerAccount();
void pViewSentMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP);
void registerNewAccount(const AccountType);
bool isAlphabet(const std::string&);
bool containsNumber(const std::string&);
bool onlyNumbers(const std::string&);
int generateID(const std::vector<int>&, const AccountType);
std::vector<int> readExistingIDs(const std::string&);
void news();
void placeCursor(HANDLE, int, int);
void login(int, static int, int);
void pViewUnreadMessages(vector<Messages>&, int, int, int, vector<Parents>& vP);
void pViewReceivedMessages(vector<Messages>& vM, int ID, int, vector<Parents>& vP);
void sPLogin(int p, vector<Parents>& vP);
void pSendMessages(int ID, int, vector<Parents>& vP);
void viewReport(int p) {}
void viewClass(int p) {}
void updatePersonalInformation(int p) {}
void sSLogin(int p) {
    int choice;
    vector<Students> vS;
    ifstream sInputFile("students.txt");
    if (sInputFile.is_open()) {
        string line;
        while (std::getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Students s;

            std::getline(iss, value, ',');
            s.ID = stoi(value);

            std::getline(iss, s.Name, ',');


            std::getline(iss, s.Password, ',');

            vS.push_back(s);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vS[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Report" << endl << "2. View Class" << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
            cout << "Make your choice : ";
 
            choice = choiceCheck(5);

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
            system("cls");
            mainMenu();
        }
        else {
            exit(0);
        }
    }
}

void viewChildReport() {}
void pViewMessages(int ID, int p, vector<Parents>& vP){
    vector<Messages> vM;
    int unreadMessages = 0;
    int choice;
    string input;
    ifstream mInputFile("messages.txt");
    if (mInputFile.is_open()) {
        string line;
        while (std::getline(mInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Messages m;
            std::getline(iss, value, ',');
            m.sentID = stoi(value);

            std::getline(iss, value, ',');
            m.recipientID = stoi(value);

            std::getline(iss, value, ',');
            m.isRead = (value == "1");


            std::getline(iss, m.message, ',');

            vM.push_back(m);
        }
        for (int i = 0; i < vM.size(); i++) {
            if (ID == vM[i].recipientID && vM[i].isRead != 1) {
                unreadMessages++;
            }
        }
        system("cls");
        cout << "You have " << unreadMessages << " messages" << endl;
            cout << "1. View Unread messages " << endl << "2. View all recieved Messages" << endl << "3. Send Messages" << endl << "4. View all sent messages " << endl << "5. Go back " << endl << endl;
            cout << "Make your choice : ";
            cin >> choice;
            switch (choice) {
            case 1: {
                if (unreadMessages == 0) {
                    system("cls");
                    cout << "You have no unread Messages!" << endl;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
                    cout << "type anything to go back to messages : ";
                    std::getline(cin, input);
                    pViewMessages(ID, p, vP);
                }
                else {
                    pViewUnreadMessages(vM, unreadMessages, ID, p, vP);
                }
                break;
            }
            case 2: {
                pViewReceivedMessages(vM, ID, p, vP);
                break;
            }
            case 3: {
                system("cls");
                pSendMessages(ID, p, vP);
                break;
            }
            case 4: {
                pViewSentMessages(vM, ID, p, vP);
                break;
            }

            } while (choice != 5)
                sPLogin(p, vP);
    }
}
void pViewReceivedMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP){
    int t = 1;
    string input;
    system("cls");
    cout << "\tUnread Messages" << endl;
    cout << "************************" << endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].recipientID == ID && vM[i].isRead != 1) {
            cout << "Message " << t << ": " << vM[i].message << endl;
            t++;
            vM[i].isRead = 0;
        }
        else if ((vM[i].recipientID == ID)) {
            cout << "Message " << t << ": " << vM[i].message << endl;
            t++;
        }
    }
    if (t == 0) {
        cout << "No messages" << endl;
    }
    ofstream file("messages.txt");
    if (file.is_open()) {
        for (int i = 0; i < vM.size(); i++) {
            file << vM[i].sentID << ',' << vM[i].recipientID << ',' << vM[i].isRead << ',' << vM[i].message << std::endl;
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
    cout << "type anything to go back to messages : ";
    std::getline(cin, input);
    pViewMessages(ID, p, vP);
}
void pViewUnreadMessages(vector<Messages>& vM, int unreadMessages, int ID, int p, vector<Parents>& vP) {
    int t = 1;
    string input;
    system("cls");
    cout << "\tUnread Messages" << endl ;
    cout << "************************" <<endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].recipientID == ID && vM[i].isRead != 1) {
            cout << "Message " << t << ": " << vM[i].message <<endl;
            t++;
            vM[i].isRead = 0;
        }
    }
    ofstream file("messages.txt");
    if (file.is_open()) {
        for (int i = 0; i < vM.size(); i++) {
            file << vM[i].sentID << ',' << vM[i].recipientID << ',' << vM[i].isRead << ',' << vM[i].message << std::endl;
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
    cout << "type anything to go back to messages : ";
    std::getline(cin, input);
    pViewMessages(ID, p, vP);
    

}
void pSendMessages(int ID, int num, vector<Parents>& vP) {

    int pID;
    int t = 0;
    int r = 0;
    int length = to_string(ID).length();
    string message;
    vector<Teachers> vT;
    cout << "\tSend Messages" << endl;
    cout << "************************" << endl << endl;
    if (length == 5) {
        cout << "Enter a message you want to send (\\n for new line): ";
        cin.ignore();
        std::getline(cin, message);
        ofstream outputFile("messages.txt", ios_base::app);
        if (outputFile.is_open()) {
            outputFile << ID << ',' << "1234" << ',' << 1 << ',' << message << endl;
            outputFile.close();
            pViewMessages(ID, num, vP);
        }
    }
    else if (length == 4) {
        int choice;
        cout << "1. Admin" << endl << "2. Teacher" << endl;
        cout << "Make your pick: ";
        while (!(cin >> choice) || choice < 1 || choice > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number (1 - 2): ";
        }
        if (choice == 1) {
            cout << "Enter a message you want to send (\\n) for new line): ";
            cin.ignore();
            std::getline(cin, message);
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << "adminID" << ',' << 1 << ',' << message << endl;
                outputFile.close();
                pViewMessages(ID, num, vP);
            }
        }
        else {
            while (t == 0) {
                cout << "Enter ID for parent (e.g., 01042): ";
                cin >> pID;
                for (int i = 0; i < vP.size(); i++) {
                    if (vP[i].ID == pID) {
                        r = i;
                        t++;
                        break;
                    }
                }
                if (t == 0) {
                    system("cls");
                    cout << "Number not found." << endl << "Please enter another ID or type '0' to return: ";
                    cin >> pID;
                    if (pID == 0) {
                        pViewMessages(ID, num, vP);
                        return;
                    }
                }
            }
            cout << "Enter a message you want to send to " << vP[r].Name << " (\\n for new line): ";
            cin.ignore();
            std::getline(cin, message);
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl;
                outputFile.close();
                pViewMessages(ID, num, vP);
            }
        }
    }
    else {
        cout << "Enter ID for parent or teacher you want to talk to: ";
        cin >> pID;
        length = to_string(pID).length();
        while (!(cin >> pID) || length < 4 || length > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Please enter another ID: ";
        }
        do {
            if (length == 5) {
                for (int i = 0; i < vP.size(); i++) {
                    if (vP[i].ID == pID) {
                        t++;
                        r = i;
                        break;
                    }
                }
                if (t == 0) {
                    system("cls");
                    cout << "Number not found." << endl << "Please enter another ID or type '0' to return: ";
                    cin >> pID;
                    length = to_string(pID).length();
                    if (pID == 0) {
                        pViewMessages(ID, num, vP);
                        return;
                    }
                }
            }
            else if (length == 6) {
                ifstream tInputFile("teachers.txt");
                if (tInputFile.is_open()) {
                    string line;
                    while (std::getline(tInputFile, line)) {
                        istringstream iss(line);
                        string value;
                        Teachers te;
                        r++;
                        std::getline(iss, value, ',');
                        te.ID = stoi(value);
                        if (pID == te.ID) {
                            t++;
                            std::getline(iss, te.Name, ',');
                            std::getline(iss, te.Password, ',');
                        }
                        vT.push_back(te);
                    }
                    tInputFile.close();
                }
                if (t == 0) {
                    system("cls");
                    cout << "Number not found." << endl << "Please enter another ID or type '0' to return: ";
                    cin >> pID;
                    length = to_string(pID).length();
                    if (pID == 0) {
                        pViewMessages(ID, num, vP);
                        return;
                    }
                }
            }
        } while (t != 1);
        if (length == 5) {
            cout << "Enter a message you want to send to " << vP[r].Name << " (\\n for new line): ";
        }
        else {
            cout << "Enter a message you want to send to " << vT[r].Name << " (\\n for new line): ";
        }
        cin.ignore();
        std::getline(cin, message);
        ofstream outputFile("messages.txt", ios_base::app);
        if (outputFile.is_open()) {
            if (length == 5) {
                outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl;
            }
            else {
                outputFile << ID << ',' << vT[r].ID << ',' << 1 << ',' << message << endl;
            }
            outputFile.close();
            pViewMessages(ID, num, vP);
        }
    }
}
void pViewSentMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP) {
    int t = 1;
    string input;
    system("cls");
    cout << "\tAll Sent Messages" << endl;
    cout << "************************" << endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].sentID == ID) {
            cout << "Message " << t << ": " << vM[i].message << endl;
            t++;
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
    cout << "type anything to go back to messages : ";
    std::getline(cin, input);
    pViewMessages(ID, p, vP);
}
void pChangeInformation(const informationType informationType, int ID, int p, vector<Parents>& vP, string output) {
    ofstream outputFile("parents.txt");
    system("cls");
    for (int i = 0; i < vP.size(); i++) {
        if (vP[i].ID == ID) {
            if (informationType == informationType::PASSWORD) {
                outputFile << vP[i].ID << "," << vP[i].Name << "," << output << "," << vP[i].Address << "," << vP[i].cNumber << "," << vP[i].childID << endl;
            }
            else if (informationType == informationType::ADDRESS) {
                outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << output << "," << vP[i].cNumber << "," << vP[i].childID << endl;
            }
            else if (informationType == informationType::CONTACTNUMBER) {
                outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << vP[i].Address << "," << output << "," << vP[i].childID << endl;
            }
        }
        else { 
            outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << vP[i].Address << "," << vP[i].cNumber << "," << vP[i].childID << endl; 
        }
    }
    cout << "Done" << endl << endl;
    pressEnter();
    sPLogin(p, vP);
}
void pUpdatePersonalInformation(int ID, int p, vector<Parents>& vP) {
    int choice;
    string str;
    string stri;
    do {
        system("cls");
        cout << "\t" << "Which information do you want to change" << "?";
        cout << endl << endl;
        cout << "1. Password" << endl << "2. Address" << endl << "3. Phone Number" << endl << "4. Go Back" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(4);
        system("cls");
        switch (choice) {
        case 1: {
            placeCursor(screen, 0, 0);
            cout << "Enter a new password must be more than 8 digits or write ""NULL"" to cancel";
            placeCursor(screen, 2, 0);
            cout << "Password: ";
            std::getline(cin >> ws, str);
            
                if (str == "NULL") {
                    sPLogin(p, vP);
                }

            while (str.length() < 8) {
                system("cls");
                placeCursor(screen, 0, 0);
                cout << "Password needs to be at least 8 characters or enter ""NULL"" to cancel. ";
                placeCursor(screen, 2, 0);
                cout << "Password: ";
                placeCursor(screen, 2, 10);
                std::getline(std::cin >> std::ws, str);
                if (str == "NULL") {
                     sPLogin(p, vP);
                }    
            }
            pChangeInformation(informationType::PASSWORD, ID, p, vP, str);
            break;
        }
        case 2: {
            placeCursor(screen, 0, 0);
            cout << "Enter a new address ""NULL"" to cancel";
            placeCursor(screen, 2, 0);
            cout << "Street Number : ";
            std::getline(std::cin >> std::ws, str);
            if (str == "NULL") {
                sPLogin(p, vP);
            }
            while (!containsNumber(str)) {
                placeCursor(screen, 0, 0);
                cout << "Invalid input. Must contain at least one number.";
                placeCursor(screen, 2, 0);
                cout << "Street Number:          ";
                placeCursor(screen, 2, 15);
                std::getline(std::cin >> std::ws, str);
                if (str == "NULL") {
                    sPLogin(p, vP);
                }
            }
            placeCursor(screen, 13, 0);
            std::cout << "                                                   ";

            // Address name input
            placeCursor(screen, 3, 0);
            cout << "Street Name: ";
            std::getline(std::cin >> std::ws, stri);
            if (stri == "NULL") {
                sPLogin(p, vP);
            }
            while (!isAlphabet(stri)) {
                placeCursor(screen, 0, 0);
                std::cout << "Invalid name. Please only use alphabet characters. ";
                placeCursor(screen, 3, 0);
                std::cout << "Street Name:                                       ";
                placeCursor(screen, 3, 12);
                std::getline(std::cin >> std::ws, stri);
                if (stri == "NULL") {
                    sPLogin(p, vP);
                }
            }
            str = str + " " + stri;
            pChangeInformation(informationType::ADDRESS, ID, p, vP, str);
            break;
        }
        case 3: {
            placeCursor(screen, 0, 0);
            cout << "Enter a new Contact Number minimum length of 7 digits or write ""NULL"" to cancel";
            placeCursor(screen, 2, 0);
            cout << "Contact Number: ";
            std::getline(cin >> ws, str);
            if (str == "NULL") {
                sPLogin(p, vP);
            }
            while (!onlyNumbers(str) || str.length() < 7) {
                placeCursor(screen, 0, 0);
                cout << "Invalid input. The input should consist of only numbers with a minimum length of 7 digits.";
                placeCursor(screen, 2, 0);
                cout << "Contact Number:                                 ";
                placeCursor(screen, 2, 16);
                std::getline(std::cin >> std::ws, str);
                if (str == "NULL") {
                    sPLogin(p, vP);
                }
            }
            pChangeInformation(informationType::CONTACTNUMBER, ID, p, vP, str);
            break;
        }
        }
    } while (choice < 4);
        sPLogin(p, vP);

}

void sPLogin(int p, vector<Parents>& vP) {
    int choice;
    do {
        system("cls");
        cout << "\t" << "Welcome " << vP[p].Name << "!";
        cout << endl << endl;
        cout << "1. View Your Child's Report" << endl << "2. View your Child's Class" << endl << "3. Messages " << endl << "4. Update Personal Information" << endl << "5. Logout" << endl << "6. Exit" << endl << endl;
        cout << "Make your choice : ";
        
        choice = choiceCheck(6);

        switch (choice) {
        case 1: {
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            pViewMessages(vP[p].ID, p, vP);
            break;
        }
        case 4: {
            pUpdatePersonalInformation(vP[p].ID, p, vP);
            break;
        }
        }
    } while (choice < 5);
    if (choice == 5) {
        system("cls");
        mainMenu();
    }
    else {
        exit(0);
    }
}

void viewClass() {}
void updateReports(){}
void tUpdatePersonalInformation() {}
void tViewMessages() {}

void sTLogin(int p) {
    int choice = 0;
    vector<Teachers> vT;
    ifstream tInputFile("teachers.txt");
    if (tInputFile.is_open()) {
        string line;
        while (std::getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Teachers t;

            std::getline(iss, value, ',');
            t.ID = stoi(value);

            std::getline(iss, t.Name, ',');


            std::getline(iss, t.Password, ',');

            vT.push_back(t);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vT[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Class" << endl << "2. Add/Update Reports" << endl << "3. View Reports " << endl << "4. Update Personal Information " << endl << "5. View Messages " << endl << "6. Send Messages " << endl << "7. Logout" << endl << "8. Exit" << endl << endl;
            cout << "Make your choice : ";

            choice = choiceCheck(8);

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
            system("cls");
            mainMenu();
        }
        else {
            exit(0);
        }
    }
}

Admins readAdmin()
{
    std::ifstream adminFile("admins.txt");
    if (adminFile.is_open()) {
        string line;
        Admins admin;

        if (std::getline(adminFile, line)) {
            istringstream iss(line);
            string value;

            std::getline(iss, value, ',');
            admin.ID = std::stoi(value);

            std::getline(iss, admin.Name, ',');

            std::getline(iss, admin.Password, ',');

            std::getline(iss, admin.SchoolName, ',');
        }
        adminFile.close();

        return admin;
    }
    else {
        std::cout << "Failed to open admins.txt" << std::endl;
    }
    

}

void manageSchool() 
{
    Admins admin = readAdmin();
    int choice;

    std::ifstream inputFile("admins.txt");
    if (!inputFile.is_open()) {
        std::cout << "Failed to open admins.txt" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();

    if (lines.empty()) {
        std::cout << "File is empty." << std::endl;
        return;
    }

    std::ofstream outputFile("admins.txt");
    if (!outputFile.is_open()) {
        std::cout << "Failed to open file for writing." << std::endl;
        return;
    }



    do {
        std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl;
        std::cout << "1. Change School Name" << std::endl << "2. Add News & Events" << std::endl << "3. Remove New & Events" << std::endl << "4. Exit" << std::endl;

        choice = choiceCheck(4);

        switch (choice) {
        case 1:
            std::cout << "New Name: ";
            std::getline(std::cin >> std::ws, admin.SchoolName);

            std::string newLine = std::to_string(admin.ID) + "," + admin.Name + "," + admin.Password + "," + admin.SchoolName;
            lines[0] = newLine;
            for (const auto& line : lines) {
                outputFile << line << std::endl;
            }
            outputFile.close();
            std::cout << "Name changed successfully!" << std::endl;
            pressEnter();
            break;
        }

    } while (choice != 4);
}
void manageStudents() {}
void manageTeachers() {}
void manageParents() {}
void adminViewMessages() {}
void aSendMessages() {}
void viewReport() {}
void updateEvents() {}
void aUpdatePersonalInformation() {}
void sALogin() {
    int choice = 0;
    Admins admin = readAdmin();
    do {
        cout << "\t" << "Welcome " << admin.Name << "!";
        cout << endl << endl;
        cout << "1. Manage School Information" << endl << "2. Manage Students" << endl << "3. Manage Teachers " << endl << "4. Manage Parents " << endl << "5. Manage classes " << endl <<"6. View Messages " << endl << "7. Send Messages " << endl << "8. View Reports" << endl << "9. Update News/Events" << endl << "10. Update Personal Information " << endl << "11. Logout" << endl << "12. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(11);

        switch (choice) {
        case 1: {
            std::system("cls");
            manageSchool();
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
            system("cls");
            mainMenu();
        }
        else {
            exit(0);
        }
}


void sLogin(string password, int ID, int& tries) {
    int cUser = 0;
    vector<Students> vS;
    ifstream sInputFile("students.txt");
    if (sInputFile.is_open()) {
        string line;
        while (std::getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Students s;

            std::getline(iss, value, ',');
            s.ID = stoi(value);

            std::getline(iss, s.Name, ',');

            std::getline(iss, s.Password, ',');

            std::getline(iss, s.Address, ',');

            vS.push_back(s);
        }
        for (int i = 0; i < vS.size(); i++) {
            if (vS[i].ID == ID && vS[i].Password == password) {
                sSLogin(i);

            }else if (vS[i].ID == ID) {
                cUser = 1;
            }
        }
        tries++;
        login(cUser, tries, ID);
    }
    else {
        cout << "Failed to open students.txt" << std::endl;
    }
}
void pLogin(string password, int ID, int& tries) {
    int cUser = 0;
    vector<Parents> vP;
    ifstream pInputFile("parents.txt");
    if (pInputFile.is_open()) {
        string line;
        while (std::getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Parents p;

            std::getline(iss, value, ',');
            p.ID = stoi(value);

            std::getline(iss, p.Name, ',');


            std::getline(iss, p.Password, ',');

            std::getline(iss, p.Address, ',');
            
           
            std::getline(iss, value, ',');
            p.cNumber = stoi(value);

            std::getline(iss, value, ',');
            p.childID = stoi(value);
            vP.push_back(p);
        }
        for (int i = 0; i < vP.size(); i++) {
            if (vP[i].ID == ID && vP[i].Password == password) {
                sPLogin(i, vP);

            }else if (vP[i].ID == ID) {
                cUser = 1;
            }
        }
        tries++;
        login(cUser, tries, ID);
    }
    else {
        cout << "Failed to open parents.txt" << endl;
    }
}
void tLogin(string password, int ID, int& tries) {
    int cUser = 0;
    vector<Teachers> vT;
    ifstream tInputFile("teachers.txt");
    if (tInputFile.is_open()) {
        string line;
        while (std::getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Teachers t;

            std::getline(iss, value, ',');
            t.ID = stoi(value);

            std::getline(iss, t.Name, ',');


            std::getline(iss, t.Password, ',');

            vT.push_back(t);
        }
        for (int i = 0; i < vT.size(); i++) {
            if (vT[i].ID == ID && vT[i].Password == password) {
                sTLogin(i);
            } else if (vT[i].ID == ID) {
                cUser = 1;
            }
        }
            tries++;
            login(cUser, tries, ID);
    }
    else {
        cout << "Failed to open teachers.txt" << std::endl;
    }
}
void aLogin(string password, int ID, int& tries) {
    int cUser = 0;
    Admins admin = readAdmin();
    if (admin.ID == ID && admin.Password == password) {
        sALogin();
    }
    else if (admin.ID == ID) {
        cUser = 1;
        
    }
    tries++;
    login(cUser, tries, ID);
}
void login(int cUser, static int tries, int correctID)
{
    string password;
    int ID;
    int length;
    system("cls");
    if (tries == 3) {
        cout << "You failed to login 3 times exiting";
        exit(0);
    }
    else if (cUser == 1) {
        cout << "\tincorrect Password! You have " << 3 - tries << " tries left" << endl << endl;
        placeCursor(screen, 2, 23);
        cout << "Login";
        placeCursor(screen, 3, 5);
        std::cout << "********************************************";
        placeCursor(screen, 4, 0);
        cout << "Enter your ID : " << correctID;
        ID = correctID;
        placeCursor(screen, 5, 0);
        cout << "Enter your Password : ";
        cin >> password;
    }
    else if (tries > 0) {
        cout << "\tincorrect ID and Password! You have " << 3 - tries << " tries left" << endl << endl;
        placeCursor(screen, 2, 23);
        cout << "Login";
        placeCursor(screen, 3, 5);
        std::cout << "********************************************";
        placeCursor(screen, 4, 0);
        cout << "Enter your ID : ";
        cin >> ID;
        placeCursor(screen, 5, 0);
        cout << "Enter your Password : ";
        cin >> password;
    }
    else if (tries == 0) {
        placeCursor(screen, 0, 23);
        cout << "Login";
        placeCursor(screen, 1, 5);
        std::cout << "********************************************";
        placeCursor(screen, 2, 0);
        cout << "Enter your ID : ";
        cin >> ID;
        placeCursor(screen, 3, 0);
        cout << "Enter your Password : ";
        cin >> password;
    }
    length = to_string(ID).length();
    switch (length) {
    case 6: {
        sLogin(password, ID, tries);
        break;
    }
    case 5: {
        pLogin(password, ID, tries);
        break;
    }
    case 4: {
        tLogin(password, ID, tries);
        break;
    }
    case 3: {
        aLogin(password, ID, tries);
        break;
    }
    default: {
        tries++;
        break;
    }
    }
}

void mainMenu()
{
    
    int choice;
    do {
        Admins admin = readAdmin();
        string school = admin.SchoolName;
        cout << "\t" << school << endl;
        for (int i = 0; i < school.length() + 16; i++) {
            cout << "*";
        }
        cout << endl << endl;
        cout << "1. Log In" << endl << "2. Register New Account" << endl << "3. Events & News" << endl << "4. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(4);

        switch (choice) {
        case 1: {
            login(0, 0, 0);
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
      exit(0);
    
};
int main()
{
    mainMenu();
}

void pressEnter()
{
    std::cout << "Press Enter to continue...";
    std::cin.get();
    std::system("cls");
}

// Function to perform numeric range check for choices
int choiceCheck(int n)
{
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > n) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number (1 - " << n << "): ";
    }
    return choice;
}

void registerAccount()
{
    int choice;

    system("cls");
    cout << "\tRegister New Account" << std::endl;
    cout << "\n1. Register Student\n2. Register Teacher\n3. Register Parent\n4. Cancel" << std::endl;
    choice = choiceCheck(4);

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
            std::cout << "ID does not match any current students. (The input should consist of 6 numbers only)";
            placeCursor(screen, 7, 0);
            std::cout << "Child's Student ID:                ";
            placeCursor(screen, 7, 20);
            std::getline(std::cin >> std::ws, childID);
        }
        placeCursor(screen, 13, 0);
        std::cout << "                                                                                             ";
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
