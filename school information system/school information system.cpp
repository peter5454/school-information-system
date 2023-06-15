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
struct messages {
    int sentID;
    int recipientID;
    bool isRead;
    string message;
};


void login();
void viewUnreadMessages(vector<messages>&, int, int);
void viewReceivedMessages(vector<messages>& vM, int ID);
void sPLogin(int p);
void sendMessages(int ID);
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

void viewChildReport() {}
void viewMessages(int ID){
    vector<messages> vM;
    int unreadMessages = 0;
    int choice;
    ifstream mInputFile("messages.txt");
    if (mInputFile.is_open()) {
        string line;
        while (getline(mInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            messages m;
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
        cout << "You have " << unreadMessages << endl;
            cout << "1. View Unread messages " << endl << "2. View all recieved Messages" << endl << "3. Send Messages" << endl << "4. View all sent messages " << endl << "5. Go back " << endl << endl;
            cout << "Make your choice : ";
            cin >> choice;
            while (!(std::cin >> choice) || choice < 1 || choice > 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please enter a number (1 - 5): ";
            }
            switch (choice) {
            case 1: {
                if (unreadMessages == 0) {
                    system("cls");
                    cout << "You have no unread Messages!";
                }
                else {
                    viewUnreadMessages(vM, unreadMessages, ID);
                }
                break;
            }
            case 2: {
                viewReceivedMessages(vM, ID);
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                sendMessages(ID);
                break;
            }

            } while (choice != 5)
                sPLogin(ID);
    }
}
void viewReceivedMessages(vector<messages>& vM, int ID){
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
    ofstream file("messages.txt");
    if (file.is_open()) {
        for (int i = 0; i < vM.size(); i++) {
            file << vM[i].sentID << ',' << vM[i].recipientID << ',' << vM[i].isRead << ',' << vM[i].message << std::endl;
        }
    }
    cout << "type anything to go back to messages : ";
    getline(cin, input);
    viewMessages(ID);
}
void viewUnreadMessages(vector<messages>& vM, int unreadMessages, int ID) {
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
    cout << "type anything to go back to messages : ";
    getline(cin, input);
    viewMessages(ID);
    

}
void sendMessages(int ID) {
    int pID;
    int t = 0;
    int r = 0;
    int length = to_string(ID).length();
    string message;
    vector<parents> vP;
    vector<teachers> vT;
    cout << "\tSend Messages" << endl;
    cout << "************************" << endl << endl;
    if (length == 5) {
        cout << "Enter a message you want to send to (\\n) for new line): ";
        getline(cin, message);
        ifstream pInputFile("parents.txt");
        if (pInputFile.is_open()) {
            string line;
            while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                parents p;
                getline(iss, value, ',');
                p.ID = stoi(value);

                getline(iss, p.Name, ',');

                getline(iss, p.Password, ',');

                vP.push_back(p);
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << "TeacherID" << ',' << 1 << ',' << message << std::endl;
                    outputFile.close();
                    viewMessages(ID);
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
                viewMessages(ID);
            }
        }
        else {

            cout << "enter ID for parent (eg.01042) : ";
            cin >> pID;
            ifstream pInputFile("parents.txt");
            vector<parents> vP;
            if (pInputFile.is_open()) {
                string line;
                while (t = 0) {
                    while (getline(pInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                        istringstream iss(line);
                        string value;

                        parents p;
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
                        viewMessages(ID);
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
                    viewMessages(ID);
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

                        parents p;
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
                    viewMessages(ID);
                }
            }
            else if (length == 6){
                ifstream tInputFile("teachers.txt");
                if (tInputFile.is_open()) {
                    string line;
                    while (getline(tInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
                        istringstream iss(line);
                        string value;

                        teachers te;
                        r++;
                        if (pID == te.ID) {
                            getline(iss, te.Name, ',');
                            t++;

                            getline(iss, te.Password, ',');

                            getline(iss, value, ',');
                            te.ID = stoi(value);

                            vT.push_back(te);
                        }
                    }
                }
            r = 0;
            system("cls");
            cout << "Number not found. " << endl << "Please enter another ID  or type '0' to return: ";
            cin >> pID;
            if (pID == 0) {
                viewMessages(ID);
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
            viewMessages(ID);
        }
    }
}
void messageTeacher(){}
void pUpdatePersonalInformation() {}
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
                viewMessages(vP[p].ID);
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

void viewClass() {}
void updateReports(){}
void tUpdatePersonalInformation() {}
void tViewMessages() {}

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
        system("cls");
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
