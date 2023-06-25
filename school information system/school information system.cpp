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
#include <set>
#include <algorithm>

HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;

struct Students {
    int ID;
    string Name;
    string Password;
    string Address;
    int Class;
    int Grade1;
    int Grade2;
    int Grade3;
    int Grade4;
    int Grade5;
};
struct Parents {
    int ID;
    string Name;
    string Password;
    string Address;
    int cNumber;
    int childID;
    int childID2;
    int childID3;
    int childID4;
};
struct Teachers {
    int ID;
    string Name;
    string Password;
    string Address;
    int cNumber;
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
    PARENT,
    ADMIN
};
enum class informationType
{
    ID,
    NAME,
    PASSWORD,
    ADDRESS,
    CONTACTNUMBER,
    CLASS,
    GRADE1,
    GRADE2,
    GRADE3,
    GRADE4,
    GRADE5,
    CHILDID,
    CHILDID2,
    CHILDID3,
    CHILDID4
};

// Function declarations
void mainMenu();
void pressEnter();
void sSLogin(int p);
int choiceCheck(int);
void registerAccount();
void sTLogin(int, vector<Teachers>&);
void viewSentMessages(vector<Messages>&, int, int, vector<Parents>&, vector<Teachers>&);
void registerNewAccount(const AccountType);
bool isAlphabet(const std::string&);
bool containsNumber(const std::string&);
bool onlyNumbers(const std::string&);
int generateID(const std::vector<int>&, const AccountType);
std::vector<int> readExistingIDs(const std::string&);
std::vector<Students> createStudentsVector();
std::vector<Parents> createParentsVector();
std::vector<Teachers> createTeachersVector();
void updatePersonalInformation(int, int, const AccountType, bool admin = false);
void news();
void placeCursor(HANDLE, int, int);
void login(int, static int, int);
void viewUnreadMessages(vector<Messages>&, int, int, int, vector<Parents>&, vector<Teachers>&);
void viewReceivedMessages(vector<Messages>&, int, int, vector<Parents>&, vector<Teachers>&);
void sPLogin(int p, vector<Parents>&);
void sendMessages(int, int, vector<Parents>&, vector<Teachers>&);
void sALogin();
void viewClass(int num, int ID, vector<Teachers>& vT, vector<Students>& vS);

// Main


// Function definitions

void viewReport(int p, vector<Students>& vS) {
    system("cls");
    cout << vS[p].Name << "'s report :" << endl << endl;
    cout << "(G1)  (G2)  (G3)  (G4)  (G5)" << endl;
    for (int grade : {vS[p].Grade1, vS[p].Grade2, vS[p].Grade3, vS[p].Grade4, vS[p].Grade5}) {
        if (grade > -1) {
            std::cout << grade << " ";
        }
        else {
            std::cout << "none ";
        }
    }
    cout << endl << endl;
    pressEnter();
    sSLogin(p);
}
void sSLogin(int p) {
    int choice;

    try {
        vector<Students> vS = createStudentsVector();
        vector<Teachers> vT = createTeachersVector();
        do {
            system("cls");
            cout << "\t" << "Welcome " << vS[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Report" << endl << "2. View Class" << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
            cout << "Make your choice : ";

            choice = choiceCheck(5);

            switch (choice) {
            case 1: {
                viewReport(p, vS);
                break;
            }
            case 2: {
                viewClass(p, vS[p].ID, vT, vS);
                break;
            }
            case 3: {
                updatePersonalInformation(vS[p].ID, p, AccountType::STUDENT);
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
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void viewChildReport(int ID, int num, vector<Parents>& vP) {
    system("cls");
    int c2;
    int c3;
    int c4;
    int c1;
    int child = 0;
    try {
        std::vector<Students> vS = createStudentsVector();
        if (vP[num].childID2 != 0) {
            for (int i = 0; i < vS.size(); i++) {
                if (vP[num].childID2 == vS[i].ID) {
                    c2 = i;
                    child++;
                }
            }
        }
        if (vP[num].childID3 != 0) {
            for (int i = 0; i < vS.size(); i++) {
                if (vP[num].childID3 == vS[i].ID) {
                    c3 = i;
                    child++;
                }
            }
        }
        if (vP[num].childID4 != 0) {
            for (int i = 0; i < vS.size(); i++) {
                if (vP[num].childID4 == vS[i].ID) {
                    c4 = i;
                    child++;
                }
            }
        }
        for (int i = 0; i < vS.size(); i++) {
            if (vP[num].childID == vS[i].ID) {
                c1 = i;
                child++;
            }
        }
        if (child == 0) {
            cout << "No children linked to your account";
            pressEnter();
            sPLogin(num, vP);
        }
        cout << "Your children reports" << endl;
        cout << "grades: \t\t\t(G1)  (G2)  (G3)  (G4)  (G5)" << endl;
        for (int i = 0; i < child; i++) {
            int currentChild = c1;
            if (i == 1) {
                currentChild = c2;
            }
            else if (i == 2) {
                currentChild = c3;
            }
            else if (i == 3) {
                currentChild = c4;
            }
            cout << vS[currentChild].Name;
            if (vS[currentChild].Name.length() < 15) {
                std::cout << "\t\t";
            }
            else {
                std::cout << "\t";
            }
            for (int grade : {vS[currentChild].Grade1, vS[currentChild].Grade2, vS[currentChild].Grade3, vS[currentChild].Grade4, vS[currentChild].Grade5}) {
                if (grade > -1) {
                    std::cout << grade << " ";
                }
                else {
                    std::cout << "none ";
                }
            }
            cout << endl;
        }
       
        cout << endl << endl;
        pressEnter();
        sPLogin(num,vP);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void viewMessages(int ID, int p, vector<Parents>& vP, vector<Teachers>& vT) {
    vector<Messages> vM;
    int unreadMessages = 0;
    int choice;
    int length = to_string(ID).length();
    string input;
    ifstream mInputFile("messages.txt");
    if (mInputFile.is_open()) {
        string line;
        while (std::getline(mInputFile, line)) { //Gathers all of the messages and gives the respected message their variables.
            istringstream iss(line);
            string value;

            Messages m;
            std::getline(iss, value, ',');
            m.sentID = stoi(value);

            std::getline(iss, value, ',');
            m.recipientID = stoi(value);

            std::getline(iss, value, ',');
            m.isRead = stoi(value);


            std::getline(iss, m.message, ',');

            vM.push_back(m);
        }
        for (int i = 0; i < vM.size(); i++) {
            if (ID == vM[i].recipientID && vM[i].isRead == 1) {
                unreadMessages++;
            }
        }
        system("cls");
        cout << "You have " << unreadMessages << " new messages" << endl;
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
                viewMessages(ID, p, vP, vT);
            }
            else {
                viewUnreadMessages(vM, unreadMessages, ID, p, vP, vT);
            }
            break;
        }
        case 2: {
            viewReceivedMessages(vM, ID, p, vP, vT);
            break;
        }
        case 3: {
            system("cls");
            sendMessages(ID, p, vP, vT);
            break;
        }
        case 4: {
            viewSentMessages(vM, ID, p, vP, vT);
            break;
        }

        } while (choice != 5)

            if (length == 5) {
                sPLogin(p, vP);
            }
            else if (length == 4) {
                sTLogin(p, vT);
            }
            else {
                sALogin();
            }
    }
}
void viewReceivedMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP, vector <Teachers>& vT) {
    int t = 1;
    string name = "hi";
    string input;
    system("cls");
    int length;

    cout << "\tUnread Messages" << endl;
    cout << "*******************************" << endl;

    cout << "New messages : " << endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].recipientID == ID && vM[i].isRead == 1) {
            length = to_string(vM[i].sentID).length();
            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].sentID) {
                        name = vT[j].Name;
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].sentID) {
                        name = vP[j].Name;
                    }
                }
            }
            else {
                name = "Admin";
            }
            cout << "Message " << t << " from " << name << ": " << vM[i].message << endl;
            t++;
            vM[i].isRead = 0;
        }
    }
    cout << "\nOld Messages : " << endl << endl;
    for (int i = vM.size() - 1; i > 0; i--) {
        if (vM[i].recipientID == ID) {
            length = to_string(vM[i].sentID).length();
            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].sentID) {
                        name = vT[j].Name;
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].sentID) {
                        name = vP[j].Name;
                        break;
                    }
                }
            }
            else {
                name = "Admin";
            }
            cout << "Message " << t << " from " << name << ": " << vM[i].message << endl;
            t++;
            vM[i].isRead = 0;
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
    pressEnter();
    viewMessages(ID, p, vP, vT);
}
void viewUnreadMessages(vector<Messages>& vM, int unreadMessages, int ID, int p, vector<Parents>& vP, vector<Teachers>& vT) {
    int t = 1;
    string input;
    string name;
    int length;
    system("cls");
    cout << "\tUnread Messages" << endl;
    cout << "************************" << endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].recipientID == ID && vM[i].isRead == 1) {
            length = to_string(vM[i].sentID).length();
            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].sentID) {
                        name = vT[j].Name;
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].sentID) {
                        name = vP[j].Name;
                    }
                }
            }
            else {
                name = "Admin";
            }
            cout << "Message " << t << " from " << name << ": " << vM[i].message << endl;
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
    viewMessages(ID, p, vP, vT);


}
void sendMessages(int ID, int num, vector<Parents>& vP, vector<Teachers>& vT) {

    int pID;
    int t = 0;
    int r = 0;
    int child = 0;
    int length = to_string(ID).length();
    string message;
    std::vector<Students> sVec;
    int locationOfTeacher = 9999;
    int locationOfTeacher2;
    int locationOfTeacher3;
    int locationOfTeacher4;
    int c1;
    int c2;
    int c3;
    int c4;
    int choice = 0;
    int choice1 = 0;
    ifstream sInputFile("students.txt");
    if (!sInputFile.is_open()) {
        cout << "Failed to open students.txt" << std::endl;
        pressEnter();
        sALogin();
    }
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

        std::getline(iss, value, ',');
        s.Class = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade1 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade2 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade3 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade4 = std::stoi(value);

        std::getline(iss, value, 'n');
        s.Grade5 = std::stoi(value);

        sVec.push_back(s);
    }
    cout << "\tSend Messages" << endl;
    cout << "*****************************" << endl;
    if (length == 5) {
        cout << "1. Admin" << endl << "2. Teacher" << endl <<endl;
        cout << "Make your pick: ";
        choice1 = choiceCheck(2);
        if (choice1 == 1) {
            system("cls");
            cout << "Enter a message you want to send to the admin (or leave it blank to cancel): ";
            cin.ignore();
            std::getline(cin, message);
            length = message.length();
            if (length == 0) {
                viewMessages(ID, num, vP, vT);
            }
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << "123" << ',' << 1 << ',' << message << endl;
                outputFile.close();
                viewMessages(ID, num, vP, vT);
            }
        }
        else {
            if (vP[num].childID2 != 0) {
                for (int i = 0; i < sVec.size(); i++) {
                    if (vP[num].childID2 == sVec[i].ID) {
                        c2 = i;
                        for (int j = 0; j < vT.size(); j++) {
                            if (sVec[i].Class == vT[j].Class) {
                                locationOfTeacher2 = j;
                                child++;
                            }
                        }
                    }
                }
            }
            if (vP[num].childID3 != 0) {
                for (int i = 0; i < sVec.size(); i++) {
                    if (vP[num].childID3 == sVec[i].ID) {
                        c3 = i;
                        for (int j = 0; j < vT.size(); j++) {
                            if (sVec[i].Class == vT[j].Class) {
                                locationOfTeacher3 = j;
                                child++;
                            }
                        }
                    }
                }
            }
            if (vP[num].childID4 != 0) {
                for (int i = 0; i < sVec.size(); i++) {
                    if (vP[num].childID4 == sVec[i].ID) {
                        c4 = i;
                        for (int j = 0; j < vT.size(); j++) {
                            if (sVec[i].Class == vT[j].Class) {
                                locationOfTeacher4 = j;
                                child++;
                            }
                        }
                    }
                }
            }
            for (int i = 0; i < sVec.size(); i++) {
                if (vP[num].childID == sVec[i].ID) {
                    c1 = i;
                    for (int j = 0; j < vT.size(); j++) {
                        if (sVec[i].Class == vT[j].Class) {
                            locationOfTeacher = j;
                            child++;
                        }
                    }
                }
            }
            system("cls");
            if (child == 2) {
                cout << "which teacher do you want to message" << endl;
                cout << "1. " << vT[locationOfTeacher].Name << ", teacher of child " << sVec[c1].Name << endl;
                cout << "2. " << vT[locationOfTeacher2].Name << ", teacher of child " << sVec[c2].Name << endl;
                cout << "which ne do you pick : ";
                choice = choiceCheck(2);
            }
            else if (child == 3) {
                cout << "which teacher do you want to message" << endl;
                cout << "1. " << vT[locationOfTeacher].Name << ", teacher of child " << sVec[c1].Name << endl;
                cout << "2. " << vT[locationOfTeacher2].Name << ", teacher of child " << sVec[c2].Name << endl;
                cout << "3. " << vT[locationOfTeacher3].Name << ", teacher of child " << sVec[c3].Name << endl;
                cout << "which ne do you pick : ";
                choice = choiceCheck(3);
            }
            else if (child == 4) {
                cout << "which teacher do you want to message" << endl;
                cout << "1. " << vT[locationOfTeacher].Name << ", teacher of child " << sVec[c1].Name << endl;
                cout << "2. " << vT[locationOfTeacher2].Name << ", teacher of child " << sVec[c2].Name << endl;
                cout << "3. " << vT[locationOfTeacher3].Name << ", teacher of child " << sVec[c3].Name << endl;
                cout << "4. " << vT[locationOfTeacher4].Name << ", teacher of child " << sVec[c4].Name << endl;
                cout << "which ne do you pick : ";
                choice = choiceCheck(4);
            }
            if (choice == 2) {
                locationOfTeacher = locationOfTeacher2;
            }
            else if (choice == 3) {
                locationOfTeacher = locationOfTeacher3;
            }
            else if (choice == 4) {
                locationOfTeacher = locationOfTeacher4;
            }
            if (locationOfTeacher == 9999) {
                cout << "No children are matched to your account" << endl;
                pressEnter();
                viewMessages(ID, num, vP, vT);
            }
            system("cls");
            cout << "Enter a message you want to " << vT[locationOfTeacher].Name << "send (or leave it blank to cancel) : "; //still need to get teacher id in order to get name for this ouput message
            cin.ignore();
            std::getline(cin, message);
            length = message.length();
            if (length == 0) {
                viewMessages(ID, num, vP, vT);
            }
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << vT[locationOfTeacher].ID << ',' << 1 << ',' << message << endl;
                outputFile.close();
                viewMessages(ID, num, vP, vT);
            }
        }
    }
    else if (length == 4) {
        int choice;
        cout << "1. Admin" << endl << "2. Parent" << endl;
        cout << "Make your pick: ";
        while (!(cin >> choice) || choice < 1 || choice > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number (1 - 2): ";
        }
        if (choice == 1) {
            system("cls");
            cout << "Enter a message you want to send the admin (or leave it blank to cancel): ";
            cin.ignore();
            std::getline(cin, message);
            length = message.length();
            if (length == 0) {
                viewMessages(ID, num, vP, vT);
            }
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << "123" << ',' << 1 << ',' << message << endl;
                outputFile.close();
                viewMessages(ID, num, vP, vT);
            }
        }
        else {
            system("cls");
            cout << "Send message to parents of your students" << endl;
            cout << "Enter ID for parent (e.g., 01042) or enter '0' return: ";
            cin >> pID;
            if (pID == 0) {
                viewMessages(ID, num, vP, vT);
            }
            while (t == 0) {
                int temp;
                int temp2;
                for (int i = 0; i < vP.size(); i++) {
                    if (vP[i].ID == pID) {
                        temp = i;
                        for (int k = 0; k < sVec.size(); k++) {
                            if (vP[temp].childID == sVec[k].ID) {
                                temp2 = k;
                                for (int j = 0; j < vT.size(); j++) {
                                    if (sVec[temp2].Class == vT[j].Class)
                                        r = temp;
                                    t = 1;
                                    break;
                                }
                            }
                        }
                    }
                }




                if (t == 0) {
                    system("cls");
                    cout << "Send message to parents of your students" << endl;
                    cout << "Number not found." << endl << "Please enter another ID or type '0' to return: ";
                    cin >> pID;
                    if (pID == 0) {
                        viewMessages(ID, num, vP, vT);
                    }
                }
            }
            system("cls");
            cout << "Enter a message you want to send to " << vP[r].Name << "(or leave it blank to cancel): ";
            cin.ignore();
            std::getline(cin, message);
            length = message.length();
            if (length == 0) {
                viewMessages(ID, num, vP, vT);
            }
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl;
                outputFile.close();
                viewMessages(ID, num, vP, vT);
            }
        }
    }
    else {
        cout << "Enter ID for parent or teacher you want to talk to: ";
        cin >> pID;
        length = to_string(pID).length();
        if (pID == 0) {
            viewMessages(ID, num, vP, vT);
            return;
        }
        while (length != 4 && length != 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid ID. Please enter another ID: ";
            cin >> pID;
            length = to_string(pID).length();
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
                        viewMessages(ID, num, vP, vT);
                        return;
                    }
                }
            }
            else if (length == 4) {
                for (int i = 0; i < vT.size(); i++) {
                    if (pID == vT[i].ID) {
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
                        viewMessages(ID, num, vP, vT);
                        return;
                    }
                }
            }
        } while (t != 1);
        system("cls");
        if (length == 5) {
            cout << "Enter a message you want to send to " << vP[r].Name << "(or leave it blank to cancel): ";
        }
        else {
            cout << "Enter a message you want to send to " << vT[r].Name << " (or leave it blank to cancel): ";
        }
        cin.ignore();
        std::getline(cin, message);
        length = message.length();
        if (length == 0) {
            viewMessages(ID, num, vP, vT);
        }
        ofstream outputFile("messages.txt", ios_base::app);
        if (outputFile.is_open()) {
            if (length == 5) {
                outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl;
            }
            else {
                outputFile << ID << ',' << vT[r].ID << ',' << 1 << ',' << message << endl;
            }
            outputFile.close();
            viewMessages(ID, num, vP, vT);
        }
    }
}
void viewSentMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP, vector<Teachers>& vT) {
    int t = 1;
    string name = "hi";
    string input;
    system("cls");
    int length;

    cout << "\tAll sent messages" << endl;
    cout << "*******************************" << endl;

    cout << "Sent messages : " << endl;
    for (int i = 0; i < vM.size(); i++) {
        if (vM[i].sentID == ID && vM[i].isRead == 1) {
            length = to_string(vM[i].recipientID).length();
            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].recipientID) {
                        name = vT[j].Name;
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].recipientID) {
                        name = vP[j].Name;
                    }
                }
            }
            else {
                name = "Admin";
            }
            cout << "Message " << t << " to " << name << ": " << vM[i].message << endl;
            t++;
        }
    }

    if (t == 0) {
        cout << "No messages" << endl;
    }
    pressEnter();
    viewMessages(ID, p, vP, vT);
}
void sChangeInformation(const informationType informationType, int ID, int p, vector<Students>& vS, string output, bool admin = false) {
    ofstream outputFile("students.txt");
    system("cls");
    for (int i = 0; i < vS.size(); i++) {
        if (vS[i].ID == ID) {
            if (informationType == informationType::ID) {
                vS[i].ID = std::stoi(output);
            }
            else if (informationType == informationType::NAME) {
                vS[i].Name = output;
            }
            else if (informationType == informationType::PASSWORD) {
                vS[i].Password = output;
            }
            else if (informationType == informationType::ADDRESS) {
                vS[i].Address = output;
            }
            else if (informationType == informationType::CLASS) {
                vS[i].Class = std::stoi(output);
            }
            else if (informationType == informationType::GRADE1) {
                vS[i].Grade1 = std::stoi(output);
            }
            else if (informationType == informationType::GRADE2) {
                vS[i].Grade2 = std::stoi(output);
            }
            else if (informationType == informationType::GRADE3) {
                vS[i].Grade3 = std::stoi(output);
            }
            else if (informationType == informationType::GRADE4) {
                vS[i].Grade4 = std::stoi(output);
            }
            else if (informationType == informationType::GRADE5) {
                vS[i].Grade5 = std::stoi(output);
            }
        }
        outputFile << vS[i].ID << "," << vS[i].Name << "," << vS[i].Password << "," << vS[i].Address << "," << vS[i].Class << "," << vS[i].Grade1 << "," << vS[i].Grade2 << "," << vS[i].Grade3 << "," << vS[i].Grade4 << "," << vS[i].Grade5 << endl;
    }
    outputFile.close();
    cout << "Update Saved!" << endl << endl;
    pressEnter();
    if (admin) {
        sALogin();
    }
    else {
        sSLogin(p);
    }
}
void pChangeInformation(const informationType informationType, int ID, int p, vector<Parents>& vP, string output, bool admin = false) {
    ofstream outputFile("parents.txt");
    system("cls");
    for (int i = 0; i < vP.size(); i++) {
        if (vP[i].ID == ID) {
            if (informationType == informationType::ID) {
                vP[i].ID = std::stoi(output);
            }
            else if (informationType == informationType::NAME) {
                vP[i].Name = output;
            }
            else if (informationType == informationType::PASSWORD) {
                vP[i].Password = output;
            }
            else if (informationType == informationType::NAME) {
                vP[i].Name = output;
            }
            else if (informationType == informationType::PASSWORD) {
                vP[i].Password = output;
            }
            else if (informationType == informationType::ADDRESS) {
                vP[i].Address = output;
            }
            else if (informationType == informationType::CONTACTNUMBER) {
                vP[i].cNumber = std::stoi(output);
            }
            else if (informationType == informationType::CHILDID) {
                vP[i].childID = std::stoi(output);
            }
            else if (informationType == informationType::CHILDID2) {
                vP[i].childID2 = std::stoi(output);
            }
            else if (informationType == informationType::CHILDID3) {
                vP[i].childID3 = std::stoi(output);
            }
            else if (informationType == informationType::CHILDID4) {
                vP[i].childID4 = std::stoi(output);
            }
        }
        outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << vP[i].Address << "," << vP[i].cNumber << "," << vP[i].childID << "," << vP[i].childID2 << "," << vP[i].childID3 << "," << vP[i].childID4 << endl;
    }
    outputFile.close();
    cout << "Done" << endl << endl;
    pressEnter();
    if (admin) {
        sALogin();
    }
    else {
        sPLogin(p, vP);
    }
}
void tChangeInformation(const informationType informationType, int ID, int p, vector<Teachers>& vT, string output, bool admin = false) {
    ofstream outputFile("teachers.txt");
    system("cls");
    for (int i = 0; i < vT.size(); i++) {
        if (vT[i].ID == ID) {
            if (informationType == informationType::ID) {
                vT[i].ID = std::stoi(output);
            }
            else if (informationType == informationType::NAME) {
                vT[i].Name = output;
            }
            else if (informationType == informationType::PASSWORD) {
                vT[i].Password = output;
            }
            else if (informationType == informationType::NAME) {
                vT[i].Name = output;
            }
            else if (informationType == informationType::PASSWORD) {
                vT[i].Password = output;
            }
            else if (informationType == informationType::ADDRESS) {
                vT[i].Address = output;
            }
            else if (informationType == informationType::CONTACTNUMBER) {
                vT[i].cNumber = std::stoi(output);
            }
            else if (informationType == informationType::CLASS) {
                vT[i].Class = std::stoi(output);
            }
        }
        outputFile << vT[i].ID << "," << vT[i].Name << "," << vT[i].Password << "," << vT[i].Address << "," << vT[i].cNumber << "," << vT[i].Class << endl;
    }
    outputFile.close();
    std::cout << "Done" << std::endl << std::endl;
    pressEnter();
    if (admin) {
        sALogin();
    }
    else {
        sTLogin(p, vT);
    }
}
void updateName(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string fname;
    std::string lname;
    std::cout << "\tUpdating Name or write ""NULL"" to cancel" << std::endl << std::endl;

    std::cout << "First Name:                    Last Name:" << std::endl;
    placeCursor(screen, 2, 12);
    std::getline(std::cin >> std::ws, fname);
    if (fname == "NULL") {

        placeCursor(screen, 6, 0);
        std::cout << "Name Change Cancelled." << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::system("cls");
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }
    while (!isAlphabet(fname)) {
        placeCursor(screen, 4, 0);
        std::cout << "Invalid name. Please only use alphabet characters.";
        placeCursor(screen, 2, 0);
        std::cout << "First Name:                    Last Name:";
        placeCursor(screen, 2, 12);
        std::getline(std::cin >> std::ws, fname);
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' ');

    // Last name input
    placeCursor(screen, 2, 42);
    std::getline(std::cin >> std::ws, lname);
    if (lname == "NULL") {
        placeCursor(screen, 6, 0);
        std::cout << "Name Change Cancelled." << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::system("cls");
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }

    while (!isAlphabet(lname)) {
        placeCursor(screen, 4, 0);
        std::cout << "Invalid name. Please only use alphabet characters.";
        placeCursor(screen, 2, 30);
        std::cout << " Last Name:                                       ";
        placeCursor(screen, 2, 42);
        std::getline(std::cin >> std::ws, lname);
    }
    std::string str = fname + ' ' + lname;
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' ');
    if (admin) {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::NAME, ID, p, vS, str, true);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::NAME, ID, p, vT, str, true);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::NAME, ID, p, vP, str, true);
        }
    }
    else {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::NAME, ID, p, vS, str);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::NAME, ID, p, vT, str);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::NAME, ID, p, vP, str);
        }
    }
}
void updatePassword(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    string str;
    placeCursor(screen, 0, 0);
    cout << "Enter a new password must be more than 8 characters or write ""NULL"" to cancel";
    placeCursor(screen, 2, 0);
    cout << "Password: ";
    std::getline(cin >> ws, str);

    if (str == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
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
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::STUDENT) {
                sSLogin(p);
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
            else if (accountType == AccountType::PARENT) {
                sPLogin(p, vP);
            }
        }
    }
    if (admin) {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::PASSWORD, ID, p, vS, str, true);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::PASSWORD, ID, p, vT, str, true);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::PASSWORD, ID, p, vP, str, true);
        }
    }
    else {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::PASSWORD, ID, p, vS, str);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::PASSWORD, ID, p, vT, str);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::PASSWORD, ID, p, vP, str);
        }
    }
}
void updateAddress(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string address;
    std::string adNum;
    std::string adName;
    placeCursor(screen, 0, 0);
    cout << "Enter a new address ""NULL"" to cancel";
    placeCursor(screen, 2, 0);
    cout << "Street Number : ";
    std::getline(std::cin >> std::ws, adNum);
    if (adNum == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }
    while (!containsNumber(adNum)) {
        placeCursor(screen, 0, 0);
        cout << "Invalid input. Must contain at least one number.";
        placeCursor(screen, 2, 0);
        cout << "Street Number:          ";
        placeCursor(screen, 2, 15);
        std::getline(std::cin >> std::ws, adNum);
        if (adNum == "NULL") {
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::STUDENT) {
                sSLogin(p);
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
            else if (accountType == AccountType::PARENT) {
                sPLogin(p, vP);
            }
        }
    }
    placeCursor(screen, 13, 0);
    std::cout << "                                                   ";

    // Address name input
    placeCursor(screen, 3, 0);
    cout << "Street Name: ";
    std::getline(std::cin >> std::ws, adName);
    if (adName == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }

    }
    while (!isAlphabet(adName)) {
        placeCursor(screen, 0, 0);
        std::cout << "Invalid name. Please only use alphabet characters. ";
        placeCursor(screen, 3, 0);
        std::cout << "Street Name:                                       ";
        placeCursor(screen, 3, 12);
        std::getline(std::cin >> std::ws, adName);
        if (adName == "NULL") {
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::STUDENT) {
                sSLogin(p);
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
            else if (accountType == AccountType::PARENT) {
                sPLogin(p, vP);
            }
        }
    }
    address = adNum + " " + adName;
    if (admin) {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::ADDRESS, ID, p, vS, address, true);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::ADDRESS, ID, p, vT, address, true);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::ADDRESS, ID, p, vP, address, true);
        }
    }
    else {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::ADDRESS, ID, p, vS, address);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::ADDRESS, ID, p, vT, address);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::ADDRESS, ID, p, vP, address);
        }
    }
}
void updateContactNumber(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string str;
    placeCursor(screen, 0, 0);
    cout << "Enter a new Contact Number minimum length of 7 digits or write ""NULL"" to cancel";
    placeCursor(screen, 2, 0);
    cout << "Contact Number: ";
    std::getline(cin >> ws, str);
    if (str == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }
    while (!onlyNumbers(str) || str.length() < 7) {
        placeCursor(screen, 0, 0);
        cout << "Invalid input. The input should consist of only numbers with a minimum length of 7 digits.";
        placeCursor(screen, 2, 0);
        cout << "Contact Number:                                 ";
        placeCursor(screen, 2, 16);
        std::getline(std::cin >> std::ws, str);
        if (str == "NULL") {
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
            else if (accountType == AccountType::PARENT) {
                sPLogin(p, vP);
            }
        }
    }
    if (accountType == AccountType::TEACHER) {
        tChangeInformation(informationType::CONTACTNUMBER, ID, p, vT, str, false);
    }
    else {
        pChangeInformation(informationType::CONTACTNUMBER, ID, p, vP, str, false);
    }
}
void updateClass(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string str;
    int t = 0;
    std::cout << "\tUpdating Class" << std::endl;
    placeCursor(screen, 2, 0);
    std::cout << "Class (1-9): ";
    std::getline(std::cin >> std::ws, str);
    while (true) {
        if (str == "NULL") {
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::STUDENT) {
                sSLogin(p);
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
        }

        while (!onlyNumbers(str)) {
            placeCursor(screen, 4, 0);
            std::cout << "Invalid class. Please only use a single digit.";
            placeCursor(screen, 2, 0);
            std::cout << "Class (1-9):                          ";
            placeCursor(screen, 2, 12);
            std::getline(std::cin >> std::ws, str);

            if (str == "NULL") {
                if (admin) {
                    sALogin();
                }
                else if (accountType == AccountType::STUDENT) {
                    sSLogin(p);
                }
                else if (accountType == AccountType::TEACHER) {
                    sTLogin(p, vT);
                }
            }
        }

        if (accountType == AccountType::TEACHER) {
            bool validClass = true;
            for (int i = 0; i < vT.size(); i++) {
                if (vT[i].Class == stoi(str) && i != p) {
                    validClass = false;
                    break;
                }
            }

            if (validClass) {
                break; // Exit the while loop if the class is valid
            }

            // Show error message and prompt for class input again
            placeCursor(screen, 4, 0);
            std::cout << "Invalid class. Another teacher already has this class.";
            placeCursor(screen, 2, 0);
            std::cout << "Class (1-9):                          ";
            placeCursor(screen, 2, 12);
            std::getline(std::cin >> std::ws, str);
        }
        else {
            break; // Exit the while loop for non-teacher account types
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' ');

    if (admin) {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::CLASS, ID, p, vS, str, true);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::CLASS, ID, p, vT, str, true);
        }
    }
    else {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::CLASS, ID, p, vS, str);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::CLASS, ID, p, vT, str);
        }
    }
}
void updateGrade(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string newGrade;

    std::cout << "\tUpdating Grade or write ""NULL"" to cancel" << std::endl;
    placeCursor(screen, 2, 0);
    std::cout << "Grade (0 - 100): ";
    placeCursor(screen, 2, 18);
    std::getline(std::cin >> std::ws, newGrade);
    if (newGrade == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
    }
    // Validation check (number: 0 - 100)
    while (!onlyNumbers(newGrade) || std::stoi(newGrade) <= 100 || std::stoi(newGrade) >= 0) {
        placeCursor(screen, 4, 0);
        std::cout << "Invalid input. Grade must be a number (0 - 100).";
        placeCursor(screen, 2, 0);
        std::cout << "Grade (0 - 100):                                 ";
        placeCursor(screen, 2, 18);
        std::getline(std::cin >> std::ws, newGrade);
        if (newGrade == "NULL") {
            if (admin) {
                sALogin();
            }
            else if (accountType == AccountType::STUDENT) {
                sSLogin(p);
            }
            else if (accountType == AccountType::TEACHER) {
                sTLogin(p, vT);
            }
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' ');

    if (admin) {
            sChangeInformation(informationType::CLASS, ID, p, vS, newGrade, true);
    }
    else {
            sChangeInformation(informationType::CLASS, ID, p, vS, newGrade);
    }
}
void updateChildID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false){}
// Function to collect new user ID
void updateID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, bool admin = false)
{
    std::string newID;
    std::cout << "\tUpdating Name or write ""NULL"" to cancel" << std::endl;
    
    if (accountType == AccountType::STUDENT) {
        std::cout << "Current ID: " << vS[p].ID << std::endl;
    }
    else if (accountType == AccountType::TEACHER) {
        std::cout << "Current ID: " << vT[p].ID << std::endl;
    }
    else if (accountType == AccountType::PARENT) {
        std::cout << "Current ID: " << vP[p].ID << std::endl;
    }
            
    std::cout << "\nNew ID: ";
    std::cin >> newID;
    if (newID == "NULL") {
        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }
    // ID number/length validation
    if (accountType == AccountType::STUDENT) {
        while (!onlyNumbers(newID) || newID.length() != 6) {
            std::cout << "Student ID needs to be exactly 6 digits" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                if (admin) {
                    sALogin();
                }
                else if (accountType == AccountType::STUDENT) {
                    sSLogin(p);
                }
                else if (accountType == AccountType::TEACHER) {
                    sTLogin(p, vT);
                }
                else if (accountType == AccountType::PARENT) {
                    sPLogin(p, vP);
                }
            }
        }
        // Check if ID already exists
        bool conflict = true;
        while (conflict) {
            conflict = false;
            for (const Students& student : vS) {
                if (std::stoi(newID) == student.ID) {
                    std::cout << "That ID already exists. Please try again." << std::endl;
                    placeCursor(screen, 3, 0);
                    std::cout << "New ID:                           ";
                    placeCursor(screen, 3, 8);
                    std::cin >> newID;
                    conflict = true;
                }
            }
        }
    }
    // ID number/length validation
    else if (accountType == AccountType::TEACHER) {
        while (!onlyNumbers(newID) || newID.length() != 4) {
            std::cout << "Teacher ID needs to be exactly 4 digits" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                if (admin) {
                    sALogin();
                }
                else if (accountType == AccountType::STUDENT) {
                    sSLogin(p);
                }
                else if (accountType == AccountType::TEACHER) {
                    sTLogin(p, vT);
                }
                else if (accountType == AccountType::PARENT) {
                    sPLogin(p, vP);
                }
            }
        }
        // Check if ID already exists
        bool conflict = true;
        while (conflict) {
            conflict = false;
            for (const Teachers& teacher : vT) {
                if (std::stoi(newID) == teacher.ID) {
                    std::cout << "That ID already exists. Please try again." << std::endl;
                    placeCursor(screen, 3, 0);
                    std::cout << "New ID:                           ";
                    placeCursor(screen, 3, 8);
                    std::cin >> newID;
                    conflict = true;
                }
            }
        }
    }
    // ID number/length validation
    else if (accountType == AccountType::PARENT) {
        while (!onlyNumbers(newID) || newID.length() != 5) {
            std::cout << "Parent ID needs to be exactly 5 digits" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                if (admin) {
                    sALogin();
                }
                else if (accountType == AccountType::STUDENT) {
                    sSLogin(p);
                }
                else if (accountType == AccountType::TEACHER) {
                    sTLogin(p, vT);
                }
                else if (accountType == AccountType::PARENT) {
                    sPLogin(p, vP);
                }
            }
        }
        // Check if ID already exists
        bool conflict = true;
        while (conflict) {
            conflict = false;
            for (const Parents& parent : vP) {
                if (std::stoi(newID) == parent.ID) {
                    std::cout << "That ID already exists. Please try again." << std::endl;
                    placeCursor(screen, 3, 0);
                    std::cout << "New ID:                           ";
                    placeCursor(screen, 3, 8);
                    std::cin >> newID;
                    conflict = true;
                }
            }
        }
    }
 
    if (admin) {
        if (accountType == AccountType::STUDENT) {
            sChangeInformation(informationType::ID, ID, p, vS, newID, true);
        }
        else if (accountType == AccountType::TEACHER) {
            tChangeInformation(informationType::ID, ID, p, vT, newID, true);
        }
        else if (accountType == AccountType::PARENT) {
            pChangeInformation(informationType::ID, ID, p, vP, newID, true);
        }
    }

}
void updatePersonalInformation(int ID, int p, const AccountType accountType, bool admin) {
    int choice;
    int n;
    try {
        std::vector<Students> vS = createStudentsVector();
        std::vector<Parents> vP = createParentsVector();
        std::vector<Teachers> vT = createTeachersVector();
        do {
            system("cls");
            std::cout << "\t" << "Which information do you want to change?";
            std::cout << std::endl << std::endl;
            std::cout << "Option" << std::endl;

            n = 1;

            std::cout << n++ << ". Name" << std::endl;
            std::cout << n++ << ". Password" << std::endl;
            std::cout << n++ << ". Address" << std::endl;
            if (accountType == AccountType::PARENT || accountType == AccountType::TEACHER) {
                std::cout << n++ << ". Phone Number" << std::endl;
            }
            if (admin) {
                std::cout << n++ << ". ID" << std::endl;
                if (accountType == AccountType::STUDENT) {
                    std::cout << n++ << ". Class" << std::endl;
                    std::cout << n++ << ". Grade 1" << std::endl;
                    std::cout << n++ << ". Grade 2" << std::endl;
                    std::cout << n++ << ". Grade 3" << std::endl;
                    std::cout << n++ << ". Grade 4" << std::endl;
                    std::cout << n++ << ". Grade 5" << std::endl;
                }
                else if (accountType == AccountType::PARENT) {
                    std::cout << n++ << ". Child ID" << std::endl;
                    std::cout << n++ << ". Child ID 2" << std::endl;
                    std::cout << n++ << ". Child ID 3" << std::endl;
                    std::cout << n++ << ". Child ID 4" << std::endl;
                }
                else if (accountType == AccountType::TEACHER) {

                    std::cout << n++ << ". Class" << std::endl;
                }
            }
            std::cout << n << ". Cancel" << std::endl << std::endl;
            std::cout << "Choice: ";

            choice = choiceCheck(n);
            system("cls");
            switch (choice) {
            case 1: {
                updateName(ID, p, vS, vP, vT, accountType);
                break;
            }
            case 2: {
                updatePassword(ID, p, vS, vP, vT, accountType);
                break;
            }
            case 3: {
                updateAddress(ID, p, vS, vP, vT, accountType);
                break;
            }
            case 4: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateID(ID, p, vS, vP, vT, accountType);
                }
                else if (accountType == AccountType::PARENT || accountType == AccountType::TEACHER) {
                    updateContactNumber(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 5: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateClass(ID, p, vS, vP, vT, accountType);
                }
                else if (admin && accountType == AccountType::PARENT || accountType == AccountType::TEACHER) {
                    updateID(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 6: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateGrade(ID, p, vS, vP, vT, accountType);
                }
                else if (admin && accountType == AccountType::PARENT) {
                    updateChildID(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 7: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateGrade(ID, p, vS, vP, vT, accountType);
                }
                else if (admin && accountType == AccountType::PARENT) {
                    updateChildID(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 8: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateGrade(ID, p, vS, vP, vT, accountType);
                }
                else if (admin && accountType == AccountType::PARENT) {
                    updateChildID(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 9: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateGrade(ID, p, vS, vP, vT, accountType);
                }
                else if (admin && accountType == AccountType::PARENT) {
                    updateChildID(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            case 10: {
                if (admin && accountType == AccountType::STUDENT) {
                    updateGrade(ID, p, vS, vP, vT, accountType);
                }
                break;
            }
            }
        } while (choice < n);

        if (admin) {
            sALogin();
        }
        else if (accountType == AccountType::STUDENT) {
            sSLogin(p);
        }
        else if (accountType == AccountType::TEACHER) {
            sTLogin(p, vT);
        }
        else if (accountType == AccountType::PARENT) {
            sPLogin(p, vP);
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void sPLogin(int p, vector<Parents>& vP) {
    int choice;
    try {
        vector<Teachers> vT;
        vector<Students> vS = createStudentsVector();
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

                std::getline(iss, t.Address, ',');


                std::getline(iss, value, ',');
                t.cNumber = stoi(value);

                std::getline(iss, value, ',');
                t.Class = stoi(value);

                vT.push_back(t);
            }
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vP[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Your Child's Report" << endl << "2. Messages " << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
            cout << "Make your choice : ";

            choice = choiceCheck(5);

            switch (choice) {
            case 1: {
                viewChildReport(vP[p].ID, p, vP);
                break;
            }
            case 2: {
                viewMessages(vP[p].ID, p, vP, vT);
                break;
            }
            case 3: {
                updatePersonalInformation(vP[p].ID, p, AccountType::PARENT);
                break;
            }
            }
        } while (choice < 4);
        if (choice == 4) {
            system("cls");
            mainMenu();
        }
        else {
            exit(0);
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void viewClass(int num, int ID, vector<Teachers>& vT, vector<Students>& vS) {
    system("cls");
    int t = 0;
    try {
        if (int length = to_string(ID).length() == 4) {
            cout << "Your class : " << endl;
            for (int i = 0; i < vS.size(); i++) {
                if (vS[i].Class == vT[num].Class) {
                    t++;
                    cout << t << ". " << vS[i].Name << endl;
                }
            }
            if (t == 0) {
                cout << "No one in your class" << endl;

            }
            pressEnter();
            sTLogin(num, vT);
        }
        else {
            cout << "Your classmates : " << endl;
            for (int i = 0; i < vS.size(); i++) {
                if (vS[i].Class == vS[num].Class && num != i) {
                    t++;
                    cout << t << ". " << vS[i].Name << endl;
                }
            }
            if (t == 0) {
                cout << "No one in your class" << endl;

            }
            pressEnter();
            sSLogin(num);
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void viewClassReport(int num, vector<Teachers>& vT, vector<Students>& vS) {
    system("cls");
    int t = 0;
    try {
        cout << "Your class: " << endl;
        cout << "grades: \t\t(G1)  (G2)  (G3)  (G4)  (G5)" << endl;
        for (int i = 0; i < vS.size(); i++) {
            if (vS[i].Class == vT[num].Class) {
                t++;
                cout << t << ". "<<vS[i].Name;
                if (vS[i].Name.length() < 15) {
                    std::cout << "\t\t";
                }
                else {
                    std::cout << "\t";
                }
                for (int grade : {vS[i].Grade1, vS[i].Grade2, vS[i].Grade3, vS[i].Grade4, vS[i].Grade5}) {
                    if (grade > -1) {
                        std::cout << grade << " ";
                    }
                    else {
                        std::cout << "none ";
                    }
                }
                cout << endl;
            }
        }

        cout << endl << endl;
        pressEnter();
        sTLogin(num, vT);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void sTLogin(int p, vector<Teachers>& vT) {
    int choice = 0;
    try {
        vector<Parents> vP;
        vector<Students> vS = createStudentsVector();
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
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vT[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Class" << endl << "2. Add/Update Reports" << endl << "3. View Reports " << endl << "4. Update Personal Information " << endl << "5. Messages" << endl << "6. Logout" << endl << "7. Exit" << endl << endl;
            cout << "Make your choice : ";

            choice = choiceCheck(7);

            switch (choice) {
            case 1: {
                viewClass(p,vT[p].ID, vT, vS);
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                viewClassReport(p, vT, vS);
                break;
            }
            case 4: {
                updatePersonalInformation(vT[p].ID, p, AccountType::TEACHER);
                break;
            }
            case 5: {
                viewMessages(vT[p].ID, p, vP, vT);
                break;
            }
            }
        } while (choice <= 5);
        if (choice == 6) {
            system("cls");
            mainMenu();
        }
        else {
            exit(0);
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
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
void saveToFile(const std::string& filename, const std::vector<std::string>& content)
{
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open file for writing." << std::endl;
        return;
    }

    for (const auto& line : content) {
        outputFile << line << '\n';
    }

    outputFile.close();
    std::cout << "Content saved to file." << std::endl;
}
void appendToFile(const std::string& filename, const std::string& content)
{
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile.is_open()) {
        std::cout << "Failed to open file for writing." << std::endl;
        return;
    }

    outputFile << content << '\n';

    outputFile.close();
    std::cout << "Content appended to file." << std::endl;
}
// Function to read a file (used for News)
std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    std::vector<std::string> content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content.push_back(line);
    }

    inputFile.close();
    return content;
}
// Check if file is empty
bool isFileEmpty(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Failed to open file for reading.";
    }

    std::string line;
    std::getline(inputFile, line);

    bool isEmpty = inputFile.eof();

    inputFile.close();
    return isEmpty;
}
// Manage school name and news/events
void manageSchoolInformation()
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

    do {
        std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl;
        std::cout << "1. Change School Name" << std::endl << "2. Add News & Events" << std::endl << "3. Remove New & Events" << std::endl << "4. Exit" << std::endl;

        choice = choiceCheck(4);

        switch (choice) {
            // Change school name
        case 1: {
            std::system("cls");
            std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl << std::endl;
            std::cout << "New Name: ";
            std::getline(std::cin >> std::ws, admin.SchoolName);

            if (!std::cin.eof()) {
                std::string newLine = std::to_string(admin.ID) + "," + admin.Name + "," + admin.Password + "," + admin.SchoolName;
                lines[0] = newLine;

                std::ofstream outputFile("admins.txt");
                if (!outputFile.is_open()) {
                    std::cout << "Failed to open file for writing." << std::endl;
                    return;
                }
                for (const auto& line : lines) {
                    outputFile << line << std::endl;
                }
                outputFile.close();
                std::cout << "Name changed successfully!" << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
                std::system("cls");
                break;
            }
            else {
                std::cout << "Name not changed.";
                pressEnter();
                break;
            }
        }
              // Add news/events
        case 2: {
            std::string content;
            std::system("cls");
            std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl << std::endl;
            std::cout << "Add News & Events" << std::endl << std::endl << "New/Events item to add: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, content);
            appendToFile("news.txt", content);
            std::cout << "Press Enter to continue...";
            std::cin.get();
            std::system("cls");

            break;
        }
              // Delete news/events
        case 3: {
            std::system("cls");
            std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl << std::endl;
            std::cout << "Remove News & Events" << std::endl << std::endl;;
            try {
                int n = 1;
                int toRemove;
                std::vector<std::string> news = readFile("news.txt");

                for (const auto& line : news) {
                    std::cout << n << ". " << line << std::endl;
                    n++;
                }
                std::cout << news.size() + 1 << ". Cancel" << std::endl;
                std::cout << std::endl << "What item do you want to delete? ";
                toRemove = choiceCheck(news.size() + 1);
                if (toRemove == news.size() + 1) {
                    std::system("cls");
                    break;
                }
                std::vector<std::string> updatedNews;
                for (const auto& line : news) {
                    if (line != news[toRemove - 1]) {
                        updatedNews.push_back(line);
                    }
                }
                saveToFile("news.txt", updatedNews);
                pressEnter();
                break;
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << std::endl;
                pressEnter();
                break;
            }
        }
        }
    } while (choice != 4);
}
// Function to create vector of all students
std::vector<Students> createStudentsVector()
{
    std::vector<Students> vS;
    ifstream sInputFile("students.txt");
    if (!sInputFile.is_open()) {
        throw std::runtime_error("Failed to open students.txt for reading.");
    }
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

        std::getline(iss, value, ',');
        s.Class = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade1 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade2 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade3 = std::stoi(value);

        std::getline(iss, value, ',');
        s.Grade4 = std::stoi(value);

        std::getline(iss, value, 'n');
        s.Grade5 = std::stoi(value);

        vS.push_back(s);
    }
    return vS;
}
// Function to create vector of all parents
std::vector<Parents> createParentsVector()
{
    std::vector<Parents> vP;
    ifstream sInputFile("parents.txt");
    if (!sInputFile.is_open()) {
        throw std::runtime_error("Failed to open parents.txt for reading.");
    }
    else {
        string line;
        while (std::getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Parents p;

            std::getline(iss, value, ',');
            p.ID = stoi(value);

            std::getline(iss, p.Name, ',');

            std::getline(iss, p.Password, ',');

            std::getline(iss, p.Address, ',');

            std::getline(iss, value, ',');
            p.cNumber = std::stoi(value);

            std::getline(iss, value, ',');
            p.childID = std::stoi(value);

            std::getline(iss, value, ',');
            p.childID2 = std::stoi(value);

            std::getline(iss, value, ',');
            p.childID3 = std::stoi(value);

            std::getline(iss, value, ',');
            p.childID4 = std::stoi(value);

            vP.push_back(p);
        }
        return vP;
    }
}
// Function to create vector of all teachers
std::vector<Teachers> createTeachersVector()
{
    std::vector<Teachers> vT;
    ifstream sInputFile("teachers.txt");
    if (!sInputFile.is_open()) {
        throw std::runtime_error("Failed to open teachers.txt for reading.");
    }
    string line;
    while (std::getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
        istringstream iss(line);
        string value;

        Teachers t;

        std::getline(iss, value, ',');
        t.ID = stoi(value);

        std::getline(iss, t.Name, ',');

        std::getline(iss, t.Password, ',');

        std::getline(iss, t.Address, ',');

        std::getline(iss, value, ',');
        t.cNumber = std::stoi(value);

        std::getline(iss, value, ',');
        t.Class = std::stoi(value);

        vT.push_back(t);
    }
    return vT;
}
// Function for sorting students vector by name
bool compareByName(const Students& student1, const Students& student2)
{
    return student1.Name < student2.Name;
}
// Arbitrary function?
void manageStudentInfo(std::vector<Students>& vS, const std::string& sID)
{
    // Find correct student // Manage individual student menu
    for (Students& student : vS) {
        if (std::stoi(sID) == student.ID) {
            std::system("cls");
            std::cout << "\tManaging Students" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;
            std::cout << "Student: " << student.Name << std::endl << std::endl;
            std::cout << "1. Change ID: " << student.ID << std::endl;
            std::cout << "2. Change Name: " << student.Name << std::endl;
            std::cout << "3. Change Password: " << student.Password << std::endl;
            std::cout << "4. Change Address: " << student.Address << std::endl;
            std::cout << "5. Change Class: " << student.Class << std::endl;
            std::cout << "6. Change Grade 1: " << (student.Grade1 >= 0 ? std::to_string(student.Grade1) : "No Grade Added") << std::endl;
            std::cout << "7. Change Grade 2: " << (student.Grade2 >= 0 ? std::to_string(student.Grade2) : "No Grade Added") << std::endl;
            std::cout << "8. Change Grade 3: " << (student.Grade3 >= 0 ? std::to_string(student.Grade3) : "No Grade Added") << std::endl;
            std::cout << "9. Change Grade 4: " << (student.Grade4 >= 0 ? std::to_string(student.Grade4) : "No Grade Added") << std::endl;
            std::cout << "10. Change Grade 5: " << (student.Grade5 >= 0 ? std::to_string(student.Grade5) : "No Grade Added") << std::endl;
            std::cout << "11. Cancel" << std::endl;
            std::cout << "Choice: ";
            int choice2 = choiceCheck(11);

            switch (choice2) {
                std::system("cls");

                break;
            }
            
        }
    }
}
// Manage student menu
void manageStudents()
{
    // Create vector of all students
    try {
        std::vector<Students> vS = createStudentsVector();

        // Menu for searching students
        int choice;
        string sID;
        int sClass;
        do {
            std::cout << "\tManaging Students" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;
            std::cout << "1. Search students by ID" << std::endl << "2. Search students by class" << std::endl << "3. Cancel" << std::endl;
            choice = choiceCheck(3);

            switch (choice) {
            case 1: {
                // Student ID search
                std::system("cls");
                std::cout << "\tManaging Students" << std::endl;
                std::cout << "*********************************" << std::endl << std::endl;
                std::cout << "Enter Student ID (or enter \'0\' to cancel): ";
                std::cin >> sID;
                if (sID == "0") {
                    std::system("cls");
                    break;
                }
                while (!onlyNumbers(sID) || sID.length() != 6) {
                    std::cout << "Not a valid Student ID (must contain 6 numbers only)" << std::endl;
                    std::cout << "Enter Student ID:";
                    std::cin >> sID;
                }
                // // Get student position from vector of all students by matching ID
                int p;
                int counter = 0;
                for (auto& student : vS) {
                    if (student.ID == std::stoi(sID)) {
                        p = counter;
                    }
                    counter++;
                }
                updatePersonalInformation(std::stoi(sID), p, AccountType::STUDENT, true);
                break;
            }
            case 2: {
                // Student class search
                std::system("cls");
                std::cout << "\tManaging Students" << std::endl;
                std::cout << "*********************************" << std::endl << std::endl;
                std::vector<int> classes;
                for (const Students& c : vS) {
                    classes.push_back(c.Class);
                }
                if (classes.empty()) {
                    std::cout << "No Classes Found." << std::endl;
                    pressEnter();
                    break;
                }
                // Get unique class numbers and sort them for display
                std::set<int> uniqueClasses(classes.begin(), classes.end());
                std::sort(classes.begin(), classes.end());
                for (const int& i : uniqueClasses) {
                    if (i == 0) {
                        std::cout << i << ". New Students (Not in a class)" << std::endl;
                    }
                    else if (i > 0) {
                        std::cout << i << ". Class " << i << std::endl;
                    }
                }
                int lastValue = *(--uniqueClasses.end()); // Get last value in unique set
                std::cout << lastValue + 1 << ". Cancel" << std::endl;
                std::cout << std::endl << "Class: ";
                std::cin >> sClass;
                if (sClass == (lastValue + 1)) {
                    std::system("cls");
                    break;
                }
                bool validInput = false;
                do {
                    for (const int& i : uniqueClasses) {
                        if (i == sClass) {
                            validInput = true;
                            break;
                        }
                    }
                    if (!validInput) {
                        std::cout << "Class " << sClass << " not found.\nPlease enter a valid input: ";
                        std::cin >> sClass;
                    }
                } while (!validInput);

                system("cls");
                std::cout << "\tManaging Students" << std::endl;
                std::cout << "*********************************" << std::endl << std::endl;

                int n = 1;
                std::vector<Students> inClass;

                if (sClass == 0) {
                    std::cout << "All Students Not In a Class " << std::endl << std::endl;
                }
                else {
                    std::cout << "Class " << sClass << std::endl << std::endl;
                }

                for (const auto& student : vS) {
                    if (student.Class == sClass) {
                        inClass.push_back(student);
                    }
                }
                std::sort(inClass.begin(), inClass.end(), compareByName);

                // Display student info in class
                std::cout << "Option \t ID \t\t Name \t\t\tClass \t\t Address \t\t (G1) (G2) (G3) (G4) (G5)" << endl;
                for (const auto& student : inClass) {
                    std::cout << n++ << ".\t";
                    if (student.Class == sClass) {
                        std::cout << student.ID << "\t\t " << student.Name;
                        if (student.Name.length() < 15) {
                            std::cout << "\t\t";
                        }
                        else {
                            std::cout << "\t";
                        }

                        std::cout << student.Class << "\t\t " << student.Address;
                        if (student.Address.length() < 15) {
                            std::cout << "\t\t";
                        }
                        else {
                            std::cout << "\t";
                        }
                        // Loop to print grades
                        for (int grade : {student.Grade1, student.Grade2, student.Grade3, student.Grade4, student.Grade5}) {
                            if (grade > -1) {
                                std::cout << grade << " ";
                            }
                            else {
                                std::cout << " none";
                            }
                        }

                        std::cout << std::endl;
                    }
                }
                std::cout << n << ". Cancel" << std::endl;
                std::cout << std::endl << std::endl;

                int sChange;
                std::cout << "Enter student to manage: ";

                sChange = choiceCheck(n);
                if (sChange == n) {
                    std::system("cls");
                    break;
                }
                // Get student position from vector of all students by matching ID
                int ID = inClass[sChange - 1].ID;
                int p;
                int counter = 0;
                for (auto& student : vS) {
                    if (student.ID == ID) {
                        p = counter;
                    }
                    counter++;
                }
                // Pass student to update info function
                updatePersonalInformation(ID, p, AccountType::STUDENT, true);
                break;
            }
            case 3: {
                std::system("cls");
                break;
            }
            }
        } while (choice != 3);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void manageTeachers() {}
void manageParents() {}
void manageClass(vector<Parents>& vP, vector<Teachers>& vT) {
    try {
        int newID;
        int t = 0;
        bool admin;
        int newClass;
        vector<Students> vS = createStudentsVector();
        while (t != 1) {
            cout << "enter the ID of the persons class you want to change (teacher or student) or write 0 to cancel : ";
            cin >> newID;
            int length = to_string(newID).length();
            if (newID == 0) {
                sALogin();
            }
            if (length == 4) {
                for (int i = 0; i < vT.size(); i++) {
                    if (vT[i].ID == newID) {
                        updateClass(newID, i, vS, vP, vT, AccountType::TEACHER, admin = true);
                    }
                }
            }
            else if (length == 6) {
                for (int i = 0; i < vT.size(); i++) {
                    if (vS[i].ID == newID) {
                        updateClass(newID, i, vS, vP, vT, AccountType::STUDENT, admin = true);
                    }
                }
            }
            else {
                system("cls");
                cout << "invalid ";
            }
        }
        
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

}
void manageSchool(int ID, int p, vector<Parents>& vP, vector<Teachers>& vT) {
    int choice;
    do {
        system("cls");
        cout << "\t" << "Manage School ";
        cout << endl << endl;
        cout << "1. Manage School information" << endl << "2. Manage students" << endl << "3. Manage parents" << endl << "4. Manage teachers" << endl << "5. Manage class" << endl << "6. go back" << endl << "7. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(7);

        switch (choice) {
        case 1: {
            std::system("cls");
            manageSchoolInformation();
            break;
        }
        case 2: {
            std::system("cls");
            manageStudents();
            break;
        }
        case 3: {
            std::system("cls");
            manageParents();
            break;
        }
        case 4: {
            std::system("cls");
            manageTeachers();
            break;
        }
        case 5: {
            std::system("cls");
            manageClass(vP, vT);
            break;
        }
        }
    } while (choice <= 5);
    if (choice == 6) {
        system("cls");
        sALogin();
    }
    else {
        exit(0);
    }
}


void sALogin() {
    int choice = 0;
    Admins admin = readAdmin();
    do {
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

                std::getline(iss, t.Address, ',');


                std::getline(iss, value, ',');
                t.cNumber = stoi(value);

                std::getline(iss, value, ',');
                t.Class = stoi(value);

                vT.push_back(t);
            }
        }
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
        }
        system("cls");
        cout << "\t" << "Welcome " << admin.Name << "!";
        cout << endl << endl;
        cout << "1. Manage School (school information, students, parents, teachers and class" << endl << "2. Messages" << endl << "3. View Reports" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(5);

        switch (choice) {
        case 1: {
            std::system("cls");
            manageSchool(admin.ID, 1, vP, vT);
            break;
        }
        case 2: {
            viewMessages(admin.ID, 1, vP, vT);
            break;
        }
        case 3: {
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
void sLogin(string password, int ID, int& tries) {
    int cUser = 0;
    try {
        vector<Students> vS = createStudentsVector();

        for (int i = 0; i < vS.size(); i++) {
            if (vS[i].ID == ID && vS[i].Password == password) {
                sSLogin(i);
            }
            else if (vS[i].ID == ID) {
                cUser = 1;
            }
        }
        tries++;
        login(cUser, tries, ID);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void pLogin(string password, int ID, int& tries) {
    int cUser = 0;
    try {
        vector<Parents> vP = createParentsVector();

        for (int i = 0; i < vP.size(); i++) {
            if (vP[i].ID == ID && vP[i].Password == password) {
                sPLogin(i, vP);

            }
            else if (vP[i].ID == ID) {
                cUser = 1;
            }
        }
        tries++;
        login(cUser, tries, ID);
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void tLogin(string password, int ID, int& tries) {
    int cUser = 0;
    
    try{
        vector<Teachers> vT = createTeachersVector();
        for (int i = 0; i < vT.size(); i++) {
            if (vT[i].ID == ID && vT[i].Password == password) {
                sTLogin(i, vT);
            }
            else if (vT[i].ID == ID) {
                cUser = 1;
            }
        }
        tries++;
        login(cUser, tries, ID);
    }

    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
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
// Function to call Main Menu
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

// Function for 'press enter to continue'
void pressEnter()
{

    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
// Register acount Menu
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
// Function for registering new accounts
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
    std::cout << std::string(60, ' ');

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
    std::cout << std::string(60, ' ');

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
        std::cout << std::string(100, ' ');
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
        std::cout << std::string(100, ' ');
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
    std::cout << std::string(60, ' ');

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
    std::cout << std::string(60, ' ');

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
    std::cout << std::string(60, ' ');

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
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << ",0,-1,-1,-1,-1,-1" << std::endl;
        }
        else if (accountType == AccountType::TEACHER) {
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << "," << contactNum << ",0" << std::endl;
        }
        else if (accountType == AccountType::PARENT) {
            outputFile << userID << "," << fname << " " << lname << "," << password << "," << addressNum << " " << addressName << "," << contactNum << "," << childID << ",0,0,0,0" << std::endl;
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
    int userID = 0;
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
// Function to display News/Events
void news()
{
    std::system("cls");
    std::cout << "\tEVENTS & NEWS" << std::endl << std::endl;
    if (isFileEmpty("news.txt")) {
        std::cout << "There's nothing here yet. Check back later." << std::endl << std::endl;
    }
    try {
        std::vector<std::string> news = readFile("news.txt");
        for (const auto& line : news) {
            std::cout << line << std::endl;
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    pressEnter();
    mainMenu();
}
// Function to place the cursor
void placeCursor(HANDLE screen, int row, int col)
{
    COORD position;
    position.Y = row;
    position.X = col;
    SetConsoleCursorPosition(screen, position);
}

int main()
{
    mainMenu();
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu