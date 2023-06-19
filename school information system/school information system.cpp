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

using namespace std;
struct Students {
    int ID;
    string Name;
    string Password;
};
struct Parents {
    int ID;
    string Name;
    string Password;
};
struct Teachers {
    int ID;
    string Name;
    string Password;
};
struct Admins {
    int ID;
    string Name;
    string Password;
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


void registerAccount();
void viewSentMessages(vector<Messages>& vM, int ID, int p);
void registerNewAccount(const AccountType);
bool isAlphabet(const std::string&);
bool containsNumber(const std::string&);
bool onlyNumbers(const std::string&);
int generateID(const std::vector<int>&, const AccountType);
std::vector<int> readExistingIDs(const std::string&);
void news();
void placeCursor(HANDLE, int, int);
void login();
void viewUnreadMessages(vector<Messages>&, int, int, int);
void viewReceivedMessages(vector<Messages>& vM, int ID, int);
void sPLogin(int p);
void sendMessages(int ID, int);
void viewReport(int p) {}
void viewClass(int p) {}
void updatePersonalInformation(int p) {}
void sSLogin(int p) {
    int choice;
    vector<Students> vS;
    ifstream sInputFile("students.txt");
    if (sInputFile.is_open()) {
        string line;
        while (getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Students s;

            getline(iss, value, ',');
            s.ID = stoi(value);

            getline(iss, s.Name, ',');


            getline(iss, s.Password, ',');

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

void viewChildReport() {}
void viewMessages(int ID, int p){
    vector<Messages> vM;
    int unreadMessages = 0;
    int choice;
    string input;
    ifstream mInputFile("messages.txt");
    if (mInputFile.is_open()) {
        string line;
        while (getline(mInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Messages m;
            getline(iss, value, ',');
            m.sentID = stoi(value);

            getline(iss, value, ',');
            m.recipientID = stoi(value);

            getline(iss, value, ',');
            m.isRead = (value == "1");


            getline(iss, m.message, ',');

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
                    getline(cin, input);
                    viewMessages(ID, p);
                }
                else {
                    viewUnreadMessages(vM, unreadMessages, ID, p);
                }
                break;
            }
            case 2: {
                viewReceivedMessages(vM, ID, p);
                break;
            }
            case 3: {
                system("cls");
                sendMessages(ID, p);
                break;
            }
            case 4: {
                viewSentMessages(vM, ID, p);
                break;
            }

            } while (choice != 5)
                sPLogin(p);
    }
}
void viewReceivedMessages(vector<Messages>& vM, int ID, int p){
    int t = 1;
    string input;
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
    if (t = 0) {
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
    getline(cin, input);
    viewMessages(ID, p);
}
void viewUnreadMessages(vector<Messages>& vM, int unreadMessages, int ID, int p) {
    int t = 1;
    string input;
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
    getline(cin, input);
    viewMessages(ID, p);
    

}
void sendMessages(int ID, int num) {
    
    int pID;
    int t = 0;
    int r = 0;
    int length = to_string(ID).length();
    string message;
    vector<Parents> vP;
    vector<Teachers> vT;
    cout << "\tSend Messages" << endl;
    cout << "************************" << endl << endl;
    if (length == 5) {
        cout << "Enter a message you want to send to (\\n) for new line): ";
        cin.ignore();
        getline(cin, message);
        ifstream pInputFile("parents.txt");
        if (pInputFile.is_open()) {
            string line;
            while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                Parents p;
                getline(iss, value, ',');
                p.ID = stoi(value);

                getline(iss, p.Name, ',');

                getline(iss, p.Password, ',');

                vP.push_back(p);
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << "1234" << ',' << 1 << ',' << message << std::endl;
                    outputFile.close();
                    viewMessages(ID, num);
                }

            }
        }
    }
    else if (length == 4) {
        int choice;

        cout << "1. Admin" << endl << "2. Teacher" << endl;
        cout << "Make your pick : ";
        cin >> choice;
        while (!(std::cin >> choice) || choice < 1 || choice > 2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number (1 - 2): ";
        }
        if (choice == 1) {
            cout << "Enter a message you want to send to (\\n) for new line): ";
            getline(cin, message);
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                outputFile << ID << ',' << "adminID" << ',' << 1 << ',' << message << std::endl;
                outputFile.close();
                viewMessages(ID, num);
            }
        }
        else {

            cout << "enter ID for parent (eg.01042) : ";
            cin >> pID;
            ifstream pInputFile("parents.txt");
            vector<Parents> vP;
            if (pInputFile.is_open()) {
                string line;
                while (t == 0) {
                    while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                        istringstream iss(line);
                        string value;

                        Parents p;
                        r++;
                        getline(iss, value, ',');
                        p.ID = stoi(value);
                        if (pID == p.ID) {
                            t++;
                            getline(iss, p.Name, ',');

                            getline(iss, p.Password, ',');
                        }
                        vP.push_back(p);
                    }
                    r = 0;
                    system("cls");
                    cout << "Number not found. " << endl << "Please enter another ID  or type '0' to return: ";
                    cin >> pID;
                    if (pID == 0) {
                        viewMessages(ID, num);
                    }
                }
            }
            if (t > 0) {
                cout << "Enter a message you want to send to" << vP[r].Name << " (\\n) for new line): ";
                getline(cin, message);
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << std::endl;
                    outputFile.close();
                    viewMessages(ID, num);
                }
            }
        }
    }
    else {

        cout << "Enter ID for parent or teacher you want to talk to: ";
        cin >> pID;
        length = to_string(pID).length();
        while (!(std::cin >> pID) || length < 4 || length > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid ID. Please enter another ID: ";
        }
        do {
            if (length == 5) {
                ifstream pInputFile("parents.txt");
                
                if (pInputFile.is_open()) {
                    string line;
                    while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                        istringstream iss(line);
                        string value;

                        Parents p;
                        r++;
                        getline(iss, value, ',');
                        p.ID = stoi(value);
                        if (pID == p.ID) {
                            t++;
                            getline(iss, p.Name, ',');

                            getline(iss, p.Password, ',');
                        }
                        vP.push_back(p);
                    }
                }
                r = 0;
                system("cls");
                cout << "Number not found. " << endl << "Please enter another ID  or type '0' to return: ";
                cin >> pID;
                length = to_string(pID).length();
                if (pID == 0) {
                    viewMessages(ID, num);
                }
            }
            else if (length == 6){
                ifstream tInputFile("teachers.txt");
                if (tInputFile.is_open()) {
                    string line;
                    while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
                        istringstream iss(line);
                        string value;

                        Teachers te;
                        r++;
                        if (pID == te.ID) {
                            getline(iss, value, ',');
                            te.ID = stoi(value);

                            getline(iss, te.Name, ',');
                            t++;

                            getline(iss, te.Password, ',');

                            vT.push_back(te);
                        }
                    }
                }
            r = 0;
            system("cls");
            cout << "Number not found. " << endl << "Please enter another ID  or type '0' to return: ";
            cin >> pID;
            if (pID == 0) {
                viewMessages(ID, num);
            }
            length = to_string(pID).length();
        }
    } while (t != 1);
    if (length == 5) {
        cout << "Enter a message you want to send to" << vP[r].Name<< "(\\n) for new line): ";
    }
    else {
        cout << "Enter a message you want to send to" << vT[r].Name << "(\\n) for new line): ";
    }
    getline(cin, message);
    ofstream outputFile("messages.txt", ios_base::app);
        if (outputFile.is_open()) {
            outputFile << ID << ',' << "pID" << ',' << 1 << ',' << message << std::endl;
            outputFile.close();
            viewMessages(ID, num);
        }
    }
}
void viewSentMessages(vector<Messages>& vM, int ID, int p) {
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
    getline(cin, input);
    viewMessages(ID, p);
}
void pUpdatePersonalInformation(int ID, int p, vector<Parents>& vP) {

}
void sPLogin(int p, vector<Parents>& vP) {
    int choice;
    vector<Parents> vP;
    ifstream pInputFile("parents.txt");
    if (pInputFile.is_open()) {
        string line;
        while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Parents pa;

            getline(iss, value, ',');
            pa.ID = stoi(value);

            getline(iss, pa.Name, ',');


            getline(iss, pa.Password, ',');

            vP.push_back(pa);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vP[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Your Child's Report" << endl << "2. View your Child's Class" << endl << "3. Messages " << endl <<"4. Update Personal Information" << endl << "5. Logout" << endl << "6. Exit" << endl << endl;
            cout << "Make your choice : ";

            // Perform numeric range check
            while (!(std::cin >> choice) || choice < 1 || choice > 6) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 6): ";
            }

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
        while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Teachers t;

            getline(iss, value, ',');
            t.ID = stoi(value);

            getline(iss, t.Name, ',');


            getline(iss, t.Password, ',');

            vT.push_back(t);
        }
        do {
            system("cls");
            cout << "\t" << "Welcome " << vT[p].Name << "!";
            cout << endl << endl;
            cout << "1. View Class" << endl << "2. Add/Update Reports" << endl << "3. View Reports " << endl << "4. Update Personal Information " << endl << "5. View Messages " << endl << "6. Send Messages " << endl << "7. Logout" << endl << "8. Exit" << endl << endl;
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

void manageSchool() {}
void manageStudents() {}
void manageTeachers() {}
void manageParents() {}
void adminViewMessages() {}
void aSendMessages() {}
void viewReport() {}
void updateEvents() {}
void aUpdatePersonalInformation() {}
void sALogin(int p) {
    int choice = 0;
    vector<Admins> vA;
    ifstream aInputFile("admins.txt");
    if (aInputFile.is_open()) {
        string line;
        while (getline(aInputFile, line)) { //Gathers all of the admins names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Admins a;

            getline(iss, value, ',');
            a.ID = stoi(value);

            getline(iss, a.Name, ',');


            getline(iss, a.Password, ',');

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
    vector<Students> vS;
    ifstream sInputFile("students.txt");
    if (sInputFile.is_open()) {
        string line;
        while (getline(sInputFile, line)) { //Gathers all of the students names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Students s;

            getline(iss, value, ',');
            s.ID = stoi(value);

            getline(iss, s.Name, ',');

            getline(iss, s.Password, ',');

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
    vector<Parents> vP;
    ifstream pInputFile("parents.txt");
    if (pInputFile.is_open()) {
        string line;
        while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Parents p;

            getline(iss, value, ',');
            p.ID = stoi(value);

            getline(iss, p.Name, ',');


            getline(iss, p.Password, ',');

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
    int tt = 0;
    vector<Teachers> vT;
    ifstream tInputFile("teachers.txt");
    if (tInputFile.is_open()) {
        string line;
        while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Teachers t;

            getline(iss, value, ',');
            t.ID = stoi(value);

            getline(iss, t.Name, ',');


            getline(iss, t.Password, ',');

            vT.push_back(t);
        }
        for (int i = 0; i < vT.size(); i++) {
            if (vT[i].ID == ID && vT[i].Password == password) {
                sTLogin(i);
                tt++;
                system("cls");
            }
        }
        if (tt == 0) {
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
    vector<Admins> vA;
    ifstream aInputFile("admins.txt");
    if (aInputFile.is_open()) {
        string line;
        while (getline(aInputFile, line)) { //Gathers all of the admins names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Admins a;

            getline(iss, value, ',');
            a.ID = stoi(value);

            getline(iss, a.Name, ',');


            getline(iss, a.Password, ',');

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
        system("cls");
        cout << "Failed to login" << endl << endl;
    }

    }
}


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
