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
    string cNumber;
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
    string cNumber;
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
    CHILDID1,
    CHILDID2,
    CHILDID3,
    CHILDID4
};

// Function declarations
void mainMenu(int);
Admins readAdmin();
std::vector<Students> createStudentsVector();
std::vector<Parents> createParentsVector();
std::vector<Teachers> createTeachersVector();
void login(int, static int, int);
void sSLogin(int p);
void sPLogin(int p, vector<Parents>&);
void sTLogin(int, vector<Teachers>&);
void sALogin();
void sLogin(string password, int ID, int& tries);
void pLogin(string password, int ID, int& tries);
void tLogin(string password, int ID, int& tries);
void aLogin(string password, int ID, int& tries);
void registerAccount();
void registerNewAccount(const AccountType);
int generateID(const std::vector<int>&, const AccountType);
void news(int);
bool isFileEmpty(const std::string& filename);
std::vector<std::string> readFile(const std::string& filename);
void saveToFile(const std::string& filename, const std::vector<std::string>& content);
void appendToFile(const std::string& filename, const std::string& content);
void sendMessages(int ID, int num, vector<Parents>& vP, vector<Teachers>& vT);
void viewMessages(int ID, int p, vector<Parents>& vP, vector<Teachers>& vT);
void viewUnreadMessages(vector<Messages>& vM, int unreadMessages, int ID, int p, vector<Parents>& vP, vector<Teachers>& vT);
void viewReceivedMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP, vector <Teachers>& vT);
void viewSentMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP, vector<Teachers>& vT);
void viewClass(int num, int ID, vector<Teachers>& vT, vector<Students>& vS);
void viewReport(int p, vector<Students>& vS);
void viewChildReport(int ID, int num, vector<Parents>& vP);
void viewClassReport(int num, vector<Teachers>& vT, vector<Students>& vS);
void updatePersonalInformation(int ID, int p, const AccountType accountType, bool admin = false);
void sChangeInformation(vector<Students>& vS);
void pChangeInformation(vector<Parents>& vP, bool noPrint = false);
void tChangeInformation(vector<Teachers>& vT);
void updateName(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updatePassword(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updateAddress(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updateContactNumber(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updateClass(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updateGrade(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, const int gradeType);
void updateChildID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void updateID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
int deleteUser(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType);
void manageSchool();
void manageSchoolInformation();
void viewReportAdmin();
void manageStudents();
void manageParents();
void manageTeachers();
bool compareByName(const Students& student1, const Students& student2);
void pressEnter(int type = 1);
int choiceCheck(int n);
bool isAlphabet(const std::string& input);
bool containsNumber(const std::string& input);
bool onlyNumbers(const std::string& input);
std::vector<int> readExistingIDs(const std::string& fileName);
void placeCursor(HANDLE screen, int row, int col);

// Main
int main()
{
    mainMenu(0);
}

// Function definitions

// Main Menu
void mainMenu(static int tries)
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
            login(0, tries, 0);
            break;
        }
        case 2: {
            registerAccount();
            break;
        }
        case 3: {
            news(tries);
            break;
        }
        }
    } while (choice != 4);
    exit(0);
}
Admins readAdmin()
{
    std::ifstream adminFile("admins.txt");
    try {
        if (!adminFile.is_open()) {
            throw std::runtime_error("Failed to open admins.txt for reading.");
        }
        else {
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
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Create vector functions
std::vector<Students> createStudentsVector()
{
    std::vector<Students> vS;
    try {
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
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
std::vector<Parents> createParentsVector()
{
    std::vector<Parents> vP;
    try {
        ifstream sInputFile("parents.txt");
        if (!sInputFile.is_open()) {
            throw std::runtime_error("Failed to open parents.txt for reading.");
        }
        else {
            string line;
            while (std::getline(sInputFile, line)) { //Gathers all of the parents names, passwords and IDs then assigns them to their respected variables.
                istringstream iss(line);
                string value;

                Parents p;

                std::getline(iss, value, ',');
                p.ID = stoi(value);

                std::getline(iss, p.Name, ',');

                std::getline(iss, p.Password, ',');

                std::getline(iss, p.Address, ',');

                std::getline(iss, value, ',');
                p.cNumber = value;

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
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
std::vector<Teachers> createTeachersVector()
{
    std::vector<Teachers> vT;
    try {
        ifstream sInputFile("teachers.txt");
        if (!sInputFile.is_open()) {
            throw std::runtime_error("Failed to open teachers.txt for reading.");
        }
        string line;
        while (std::getline(sInputFile, line)) { //Gathers all of the teachers names, passwords and IDs then assigns them to their respected variables.
            istringstream iss(line);
            string value;

            Teachers t;

            std::getline(iss, value, ',');
            t.ID = stoi(value);

            std::getline(iss, t.Name, ',');

            std::getline(iss, t.Password, ',');

            std::getline(iss, t.Address, ',');

            std::getline(iss, value, ',');
            t.cNumber = value;

            std::getline(iss, value, ',');
            t.Class = std::stoi(value);

            vT.push_back(t);
        }
        return vT;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Log in functions
void login(int cUser, static int tries, int correctID)
{
    string password;
    int ID = 0;
    int length;
    system("cls");
    if (tries == 3) { //if the user has tried 3 times to log in they will be exited from the system
        cout << "You failed to login 3 times exiting";
        exit(0);
    }
    else if (cUser == 1) { //if they got the id correct but wrong password
        cout << "\tincorrect Password! You have " << 3 - tries << " tries left" << endl << endl;
        placeCursor(screen, 2, 23);
        cout << "Login";
        placeCursor(screen, 3, 5);
        std::cout << "********************************************";
        placeCursor(screen, 4, 0);
        cout << "Enter your ID : " << correctID;
        ID = correctID;
        placeCursor(screen, 5, 0);
        cout << "Enter your Password or '0' to exit : ";
        cin >> password;
        if (password == "0") {
            system("cls");
            mainMenu(tries);
        }
    }
    else if (tries > 0) { // if the user entered incorrect id and password
        cout << "\tincorrect ID and Password! You have " << 3 - tries << " tries left" << endl << endl;
        placeCursor(screen, 2, 23);
        cout << "Login";
        placeCursor(screen, 3, 5);
        std::cout << "********************************************";
        placeCursor(screen, 4, 0);
        cout << "Enter your ID or 0 to exit: ";
        cin >> ID;
        if (ID == 0) {
            system("cls");
            mainMenu(tries);
        }
        placeCursor(screen, 5, 0);
        cout << "Enter your Password : ";
        cin >> password;
    }
    else if (tries == 0) { //initial login arrempt
        placeCursor(screen, 0, 23);
        cout << "Login";
        placeCursor(screen, 1, 5);
        std::cout << "********************************************";
        placeCursor(screen, 2, 0);
        cout << "Enter your ID or 0 to exit : ";
        cin >> ID;
        if (ID == 0) {
            system("cls");
            mainMenu(tries);
        }
        placeCursor(screen, 3, 0);
        cout << "Enter your Password : ";
        cin >> password;
    }
    length = to_string(ID).length();
    switch (length) { //calls one of the function based the length f the id they inputted 
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
        system("cls");
        mainMenu(tries); //passes back tries
        break;
    }
    }
}
void sSLogin(int p)/*succesful student login*/ {
    int choice;

    vector<Students> vS = createStudentsVector(); //sucessful student login creates 2 vectors in order to pass to the respected function if called
    vector<Teachers> vT = createTeachersVector();
    do {
        system("cls");
        cout << "\t" << "Welcome " << vS[p].Name << "!"; //uses p to indicate the name, the only variable passed
        cout << endl << endl;
        cout << "1. View Report" << endl << "2. View Class" << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(5);

        switch (choice) { //based on choice will call these function which match with the text outputted
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
        mainMenu(0);
    }
    else {
        exit(0);
    }
}
void sPLogin(int p, vector<Parents>& vP)/*succesful parent login*/ {
    int choice;

    vector<Teachers> vT = createTeachersVector();
    vector<Students> vS = createStudentsVector();//sucessful parent login creates 2 vectors in order to pass o the respected function if called
        
    do {
        system("cls");
        cout << "\t" << "Welcome " << vP[p].Name << "!";//uses p to indicate the name, the only variable passed
        cout << endl << endl;
        cout << "1. View Your Child's Report" << endl << "2. Messages " << endl << "3. Update Personal Information" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(5);

        switch (choice) {//based on choice will call these function which match with the text outputted
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
        mainMenu(0);
    }
    else {
        exit(0);
    }
}
void sTLogin(int p, vector<Teachers>& vT)/*succesful teacher login*/ {
    int choice = 0;

    vector<Parents> vP = createParentsVector();
    vector<Students> vS = createStudentsVector(); //creates the other 2 vectors after being passed their own
        
    do {
        system("cls");
        cout << "\t" << "Welcome " << vT[p].Name << "!";
        cout << endl << endl;
        cout << "1. View Class" << endl << "2. Update Student Grades" << endl << "3. View Class Report " << endl << "4. Update Personal Information " << endl << "5. Messages" << endl << "6. Logout" << endl << "7. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(7);

        switch (choice) { //7 switch case option
        case 1: {
            viewClass(p, vT[p].ID, vT, vS);
            break;
        }
        case 2: {
            system("cls");
            std::cout << "\tUpdating Grades" << std::endl;
            std::cout << "*****************************" << std::endl << std::endl;

            if (vT[p].Class == 0) { //if the teacher has no class they need to wait for the admin to assign them to one
                std::cout << "Wait until administrator assigns you to a class (might need to message them)." << std::endl;
                pressEnter();
                break;
            }

            int n = 1;
            std::vector<Students> inClass;

            std::cout << "Class " << vT[p].Class << std::endl << std::endl; //outputs their class number

            for (const auto& student : vS) {
                if (student.Class == vT[p].Class) {
                    inClass.push_back(student);
                }
            }
            std::sort(inClass.begin(), inClass.end(), compareByName); //gets and sorts all the students in their class

            // Display student info in class
            std::cout << "Option \t ID \t\t Name \t\t\t(G1) (G2) (G3) (G4) (G5)" << endl;
            for (const auto& student : inClass) {
                std::cout << n++ << ".\t";
                if (student.Class == vT[p].Class) {
                    std::cout << student.ID << "\t\t " << student.Name;
                    if (student.Name.length() < 15) {
                        std::cout << "\t\t"; //outputs the students
                    }
                    else {
                        std::cout << "\t";
                    }
                    // Loop to print grades
                    for (int grade : {student.Grade1, student.Grade2, student.Grade3, student.Grade4, student.Grade5}) {
                        if (grade > -1) {
                            std::cout << " " << grade << "  ";
                        }
                        else {
                            std::cout << " XX  ";
                        }
                    }

                    std::cout << std::endl;
                }
            }
            std::cout << n << ".\tCancel" << std::endl;
            std::cout << std::endl << std::endl;

            int sChange;
            std::cout << "Option: ";

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
                    break;
                }
                counter++;
            }
            // Print current grades
            int choice2 = 0;
            std::system("cls");
            std::cout << "Student: " << vS[p].Name << std::endl << std::endl;
            int num = 0;
            for (auto grade : { vS[p].Grade1 , vS[p].Grade2, vS[p].Grade3, vS[p].Grade4, vS[p].Grade5 }) {
                std::cout << ++num << ". Grade " << num << ": " << (grade > -1 ? std::to_string(grade) : "XX") << std::endl;
            }
            std::cout << "6. Cancel" << std::endl;
            std::cout << "Choice: ";
            choice2 = choiceCheck(6);
            // Choose grade to update
            switch (choice2) {
            case 1: {
                std::system("cls");
                updateGrade(ID, p, vS, vP, vT, AccountType::TEACHER, 1);
                break;
            }
            case 2: {
                std::system("cls");
                updateGrade(ID, p, vS, vP, vT, AccountType::TEACHER, 2);
                break;
            }
            case 3: {
                std::system("cls");
                updateGrade(ID, p, vS, vP, vT, AccountType::TEACHER, 3);
                break;
            }
            case 4: {
                std::system("cls");
                updateGrade(ID, p, vS, vP, vT, AccountType::TEACHER, 4);
                break;
            }
            case 5: {
                std::system("cls");
                updateGrade(ID, p, vS, vP, vT, AccountType::TEACHER, 5);
                break;
            }
            case 6: {
                break;
            }
            }
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
        mainMenu(0);
    }
    else {
        exit(0);
    }
}
void sALogin()/*succesful admin login*/ {
    int choice = 0;

    do {
        Admins admin = readAdmin();
        vector<Teachers> vT = createTeachersVector(); // Creates all vectors
        vector<Parents> vP = createParentsVector();
        vector<Students> vS = createStudentsVector();
            
        system("cls");
        cout << "\t" << "Welcome " << admin.Name << "!";
        cout << endl << endl;
        cout << "1. Manage School (School Information, Students, Parents & Teachers)" << endl << "2. Messages" << endl << "3. View Class Reports" << endl << "4. Logout" << endl << "5. Exit" << endl << endl;
        cout << "Make your choice : ";

        choice = choiceCheck(5);

        switch (choice) { 
        case 1: {
            std::system("cls");
            manageSchool();
            break;
        }
        case 2: {
            viewMessages(admin.ID, 1, vP, vT);
            break;
        }
        case 3: {
            viewReportAdmin();
            break;
        }
        }
    } while (choice <= 3); //while choice != 4 or choice != 5
    if (choice == 4) {
        system("cls");
        mainMenu(0);
    }
    else { //if choice == 5 (only possible option)
        exit(0);
    }
}
void sLogin(string password, int ID, int& tries) /*student login*/ {
    int cUser = 0;

    vector<Students> vS = createStudentsVector(); //creates the vector

    for (int i = 0; i < vS.size(); i++) { //checks if id and password match from the whole vector
        if (vS[i].ID == ID && vS[i].Password == password) {
            sSLogin(i);
        }
        else if (vS[i].ID == ID) {
            cUser = 1; //if only id matched sets cUser to 1
        }
    }
    tries++;
    login(cUser, tries, ID); // goes back to login

}
void pLogin(string password, int ID, int& tries) /*parent login*/ {
    int cUser = 0;

    vector<Parents> vP = createParentsVector(); //creates the vector

    for (int i = 0; i < vP.size(); i++) {
        if (vP[i].ID == ID && vP[i].Password == password) {//checks if id and password match from the whole vector
            sPLogin(i, vP);

        }
        else if (vP[i].ID == ID) {
            cUser = 1;//if only id matched sets cUser to 1
        }
    }
    tries++;
    login(cUser, tries, ID);// goes back to login
}
void tLogin(string password, int ID, int& tries)/*teacher login*/ {
    int cUser = 0;

    try {
        vector<Teachers> vT = createTeachersVector();//creates the vector
        for (int i = 0; i < vT.size(); i++) {
            if (vT[i].ID == ID && vT[i].Password == password) {//checks if id and password match from the whole vector
                sTLogin(i, vT);
            }
            else if (vT[i].ID == ID) {
                cUser = 1;//if only id matched sets cUser to 1
            }
        }
        tries++;
        login(cUser, tries, ID);// goes back to login
    }

    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void aLogin(string password, int ID, int& tries)/*admin login*/ {
    int cUser = 0;
    Admins admin = readAdmin(); //due to there being 1 admin doesnt need to create a vector
    if (admin.ID == ID && admin.Password == password) { //if admin id an dpasswor dmatch teh id and password which are passed here
        sALogin();
    }
    else if (admin.ID == ID) {
        cUser = 1; //if id matches the admin id

    }
    tries++;
    login(cUser, tries, ID); //goes back to login
}

// Register functions
void registerAccount()
{
    int choice;

    system("cls");
    cout << "\tRegister New Account" << std::endl;
    cout << "\n1. Register Student\n2. Register Teacher\n3. Register Parent\n4. Cancel" << std::endl; 
    choice = choiceCheck(4);

    switch (choice) { //switch case for the new account then assign account type based on their input
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
        std::system("cls");
        return;
    }
    }
}
void registerNewAccount(const AccountType accountType)
{
    std::system("cls");
    std::string fname, lname, password, addressNum, addressName, contactNum, childID;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string fileName;

    if (accountType == AccountType::STUDENT) { //which file to open based on the account type which was passed
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
    //outputs all mthe fields

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

        //checks if childID input matches an already existing student
        while (!isValid) {
            std::istringstream(childID) >> childIDInt;
            for (int i : studentIDs) {
                if (i == childIDInt) {
                    isValid = true;
                    break;
                }
            }
            //if it doesn't match wth any
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
    userID = generateID(existingIDs, accountType); //gives the user a unique id

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
        std::cout <<"Your User ID is: " << userID << std::endl << std::endl <<
            "Write this down! Use this to log in next time you visit." << std::endl << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get();

        std::cout << std::endl << "Account registered successfully!" << std::endl << std::endl;

        if (accountType == AccountType::STUDENT || accountType == AccountType::TEACHER) {
            std::cout << "Please wait while an administrator assigns you to a class." << std::endl;
        }
        else if (accountType == AccountType::PARENT) {
            std::cout << "To link more child ID's to your account, contact the administrator." << std::endl;
        }
        std::cout << "Press Enter to continue...";
        std::cin.get();
        std::system("cls");

    }
    else
    {
        std::system("cls");
        std::cout << "Error opening the file." << std::endl << std::endl;
        pressEnter();
    }
}
int generateID(const std::vector<int>& existingIDs, const AccountType accountType)
{
    srand(static_cast<unsigned int>(time(nullptr))); //intiate random
    int userID = 0;
    bool idExists;

    do {
        if (accountType == AccountType::STUDENT) {
            userID = rand() % 900000 + 100000; //gets a random 6 digit number
        }
        else if (accountType == AccountType::TEACHER) {
            userID = rand() % 9000 + 1000; //gets a random 5 digit number
        }
        else if (accountType == AccountType::PARENT) {
            userID = rand() % 90000 + 10000; //gets a random 4 digit number
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

// Events/News functions
void news(static int tries)
{
    std::system("cls");
    std::cout << "\tEVENTS & NEWS" << std::endl << std::endl;
    if (isFileEmpty("news.txt")) {
        std::cout << "There's nothing here yet. Check back later." << std::endl << std::endl;// incase the file is empty
    }
    try {
        std::vector<std::string> news = readFile("news.txt");
        for (const auto& line : news) {
            std::cout << line << std::endl; //outputs the lines in the file one at a time and ends it after
        }
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    pressEnter();
    mainMenu(tries); // passes tries back to main menu
}
bool isFileEmpty(const std::string& filename) {
    std::ifstream inputFile(filename);
    try {
        if (!inputFile.is_open()) {
            std::cout << "Failed to open file for reading.";
        }

        std::string line;
        std::getline(inputFile, line);

        bool isEmpty = inputFile.eof(); //checks if file is empty and if so returns false

        inputFile.close();
        return isEmpty;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    try {
        if (!inputFile.is_open()) {
            throw std::runtime_error("Failed to open file for reading.");
        }
        std::vector<std::string> content;
        std::string line;
        while (std::getline(inputFile, line)) {
            content.push_back(line); //simply gets the information and applies it to a vector string
        }

        inputFile.close();
        return content;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void saveToFile(const std::string& filename, const std::vector<std::string>& content)
{
    std::ofstream outputFile(filename);
    try {
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing.");
            return;
        }

        for (const auto& line : content) {
            outputFile << line << '\n'; //saves a string to the file
        }

        outputFile.close();
        std::cout << "Content saved to file." << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void appendToFile(const std::string& filename, const std::string& content)
{
    std::ofstream outputFile(filename, std::ios::app);
    try {
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing.");
            return;
        }

        outputFile << content << '\n'; //instead of saving to the file it adds a new line and saves to that

        outputFile.close();
        std::cout << "Content appended to file." << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Messaging functions
void sendMessages(int ID, int num, vector<Parents>& vP, vector<Teachers>& vT) {

    int pID; //potential ID
    int t = 0;
    int r = 0; //t and r are counters
    int child = 0; //how many children the parents have
    int length = to_string(ID).length();
    int length2;
    string message;
    int locationOfTeacher = 9999;  //initiating the fact that a parent might have 4 different teacher they can send to
    int locationOfTeacher2;
    int locationOfTeacher3;
    int locationOfTeacher4;
    int c1;
    int c2;
    int c3;
    int c4; //all 4 children
    int choice = 0;
    int choice1 = 0; //for 2 choices
    try {
        vector<Students> sVec = createStudentsVector();
        cout << "\tSend Messages" << endl;
        cout << "*****************************" << endl;
        if (length == 5) {
            cout << "1. Admin" << endl << "2. Teacher" << endl << endl;
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
                    outputFile << ID << ',' << "123" << ',' << 1 << ',' << message << endl; // append the data to the file in the format sentID, recipiantID, isRead and the message
                    outputFile.close();
                    viewMessages(ID, num, vP, vT);
                }
            }
            else { //if they pick 2 it check how many children they have
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
                } //Above gathers the data and the location of each of their children teachers
                system("cls");
                if (child == 2) { //allows the parents to pick the teacher they want to send the message to
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
                } // finnaly assigns the value of which teacher they want to send it to
                if (locationOfTeacher == 9999) {
                    cout << "No children are matched to your account" << endl;
                    pressEnter();
                    viewMessages(ID, num, vP, vT);
                }
                system("cls");
                cout << "Enter a message you want to " << vT[locationOfTeacher].Name << "send (or leave it blank to cancel) : "; //outputs the name based on which teacher the user choose
                cin.ignore();
                std::getline(cin, message);
                length = message.length();
                if (length == 0) {
                    viewMessages(ID, num, vP, vT); //in case the user change their mind on senddng a message
                }
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << vT[locationOfTeacher].ID << ',' << 1 << ',' << message << endl; // appends the data to the file
                    outputFile.close();
                    viewMessages(ID, num, vP, vT);
                }
            }
        }
        else if (length == 4) { //If their ID is a teacher ID
            int choice;
            cout << "1. Admin" << endl << "2. Parent" << endl;
            cout << "Make your pick: ";
            choice = choiceCheck(2);
            if (choice == 1) {
                system("cls");
                cout << "Enter a message you want to send the admin (or leave it blank to cancel): ";
                cin.ignore();
                std::getline(cin, message);
                length = message.length();
                if (length == 0) {
                    viewMessages(ID, num, vP, vT); //Incase they change their mind
                }
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << "123" << ',' << 1 << ',' << message << endl; // append to fiel using rcipiant ID 123 because it doesn't change
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
                        if (vP[i].ID == pID) { // finding parents of students in the users class then checking i their id matches the submited ID
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




                    if (t == 0) { //if the id doesnt match anybody 
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
                cout << "Enter a message you want to send to " << vP[r].Name << "(or leave it blank to cancel): "; //Incase they dont want to send a message
                cin.ignore();
                std::getline(cin, message);
                length = message.length();
                if (length == 0) {
                    viewMessages(ID, num, vP, vT);
                }
                ofstream outputFile("messages.txt", ios_base::app);
                if (outputFile.is_open()) {
                    outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl; // append to the file
                    outputFile.close();
                    viewMessages(ID, num, vP, vT);
                }
            }
        }
        else {
            cout << "Enter ID for parent or teacher you want to talk to: "; //admin functions, Admin can send a message to anybody (not studetns)
            cin >> pID;
            length = to_string(pID).length();
            if (pID == 0) {
                viewMessages(ID, num, vP, vT);
                return;
            }
            while (length != 4 && length != 5) { // simple check if the id is matching 4 or 5 digits which is parent or teacher
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID. Please enter another ID: ";
                cin >> pID;
                length = to_string(pID).length();
            }

            do {
                if (length == 5) { // if id is a parent id
                    for (int i = 0; i < vP.size(); i++) {
                        if (vP[i].ID == pID) { // read the vector for matching potential id
                            t++;
                            r = i; //place is saved and counter is increased by one to tell the system matching id was found
                            break;
                        }
                    }
                    if (t == 0) {
                        system("cls");
                        cout << "Number not found." << endl << "Please enter another ID or type '0' to return: "; // in case the counter wasn't increased
                        cin >> pID;
                        length = to_string(pID).length();
                        if (pID == 0) {
                            viewMessages(ID, num, vP, vT);
                            return;
                        }
                    }
                }
                else if (length == 4) { //if id is teacher ID
                    for (int i = 0; i < vT.size(); i++) {
                        if (pID == vT[i].ID) { //read the vector for potential ID (pID)
                            t++;
                            r = i; // saves the place and increaes the counter to tell the system that a matching ID has been found
                            break;
                        }
                    }
                    if (t == 0) { //if counter has increased
                        system("cls");
                        cout << "Number not found." << endl << "Please enter another ID or type '0' to return: ";
                        cin >> pID;
                        length = to_string(pID).length();
                        if (pID == 0) {
                            viewMessages(ID, num, vP, vT); // exits
                        }
                    }
                }
            } while (t != 1); // while counter hasn't increased
            system("cls");
            if (length == 5) { // if id is parent
                cout << "Enter a message you want to send to " << vP[r].Name << "(or leave it blank to cancel): "; //output parent name
            }
            else {
                cout << "Enter a message you want to send to " << vT[r].Name << " (or leave it blank to cancel): "; // output teacher name
            }
            cin.ignore();
            std::getline(cin, message);

            length2 = message.length();
            if (length2 == 0) {
                viewMessages(ID, num, vP, vT); //in case the user changes their mind
            }
            ofstream outputFile("messages.txt", ios_base::app);
            if (outputFile.is_open()) {
                if (length == 5) {
                    outputFile << ID << ',' << vP[r].ID << ',' << 1 << ',' << message << endl; //output parent ID to the file
                }
                else {
                    outputFile << ID << ',' << vT[r].ID << ',' << 1 << ',' << message << endl; //append teachere id to the file
                }
                outputFile.close();
                viewMessages(ID, num, vP, vT);
            }
        }
    }
    catch (const std::runtime_error& e) { //if failed to create the student vector
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
                unreadMessages++; //count how many messages that are unread by checking if the unread variable is = to 1 and recipiant id is = to the user id
            }
        }
        system("cls");
        cout << "You have " << unreadMessages << " new messages" << endl; //outputs how many un read messages
        cout << "1. View Unread messages " << endl << "2. View all recieved Messages" << endl << "3. Send Messages" << endl << "4. View all sent messages " << endl << "5. Go back " << endl << endl;
        cout << "Make your choice : ";
        cin >> choice;
        switch (choice) {
        case 1: {
            if (unreadMessages == 0) { //if no unread messages displays it instead of going to function
                system("cls");
                cout << "You have no unread Messages!" << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
                cout << "type anything to go back to messages : ";
                std::getline(cin, input);
                viewMessages(ID, p, vP, vT);
            }
            else { // if there are unread mssage goes to function
                viewUnreadMessages(vM, unreadMessages, ID, p, vP, vT);
            }
            break;
        }
        case 2: {
            viewReceivedMessages(vM, ID, p, vP, vT); //goes to recieve messages function
            break;
        }
        case 3: {
            system("cls");
            sendMessages(ID, p, vP, vT); //goes to send messages function
            break;
        }
        case 4: {
            viewSentMessages(vM, ID, p, vP, vT); //goes to view sent messages function
            break;
        }

        } while (choice != 5) //if choice !=5 it will stay in loop

            if (length == 5) {
                sPLogin(p, vP); // if parent it will go to parent login
            }
            else if (length == 4) { //if teacher it will go to teacher login
                sTLogin(p, vT);
            } 
            else {
                sALogin(); //or it goes to admin login
            }
    }
}
void viewUnreadMessages(vector<Messages>& vM, int unreadMessages, int ID, int p, vector<Parents>& vP, vector<Teachers>& vT) {
    int t = 1;
    string input;
    string name;
    int length;
    system("cls");
    cout << "\tUnread Messages" << endl;
    cout << "************************" << endl;
    for (int i = 0; i < vM.size(); i++) { //for statemet to read all of the messages
        if (vM[i].recipientID == ID && vM[i].isRead == 1) { // if unread and recipiant id and id matches then it will find the length to find out which file to open 
            length = to_string(vM[i].sentID).length();

            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].sentID) {
                        name = vT[j].Name; //opens teacher vector and if the ids match it will save their name and output
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].sentID) {
                        name = vP[j].Name; // same with teacher
                    }
                }
            }
            else { // if length doesnt = any of thoese it must be admin
                name = "Admin";
            }
            cout << "Message " << t << " from " << name << ": " << vM[i].message << endl;
            t++;
            vM[i].isRead = 0; //outputs message and changes the message o read
        }

    }
    ofstream file("messages.txt");
    if (file.is_open()) {
        for (int i = 0; i < vM.size(); i++) {
            file << vM[i].sentID << ',' << vM[i].recipientID << ',' << vM[i].isRead << ',' << vM[i].message << std::endl; //write the vector down to the file.
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the remaining input
    cout << "type anything to go back to messages : ";
    std::getline(cin, input);
    viewMessages(ID, p, vP, vT);


}
void viewReceivedMessages(vector<Messages>& vM, int ID, int p, vector<Parents>& vP, vector <Teachers>& vT) {
    int t = 1;
    string name;
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
                        name = vT[j].Name; //same as unread for new messages
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
    for (int i = vM.size() - 1; i > 0; i--) { //goes backwards from new to old rather than new to old
        if (vM[i].recipientID == ID) {
            length = to_string(vM[i].sentID).length();
            if (length == 4) {
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].sentID) {
                        name = vT[j].Name; //saves name after matching id
                        break;
                    }
                }
            }
            else if (length == 5) {
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].sentID) {
                        name = vP[j].Name; //saves name after matching id
                        break;
                    }
                }
            }
            else {
                name = "Admin";
            }
            cout << "Message " << t << " from " << name << ": " << vM[i].message << endl; //uputs message
            t++;
            vM[i].isRead = 0;
        }
    }
    if (t == 0) {
        cout << "No messages" << endl; //if counter = 0  no messages have been recieved
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
            if (length == 4) { //if id is a teacher id
                for (int j = 0; j < vT.size(); j++) {
                    if (vT[j].ID == vM[i].recipientID) {
                        name = vT[j].Name; //same as view recieved messages except for this matches the users id with sent id and then locates the recipiant id to get the name 
                        break;
                    }
                }
            }
            else if (length == 5) { //if id is a paren id
                for (int j = 0; j < vP.size(); j++) {
                    if (vP[j].ID == vM[i].recipientID) {
                        name = vP[j].Name;
                    }
                }
            }
            else {
                name = "Admin"; //has to be admin if none of the above
            }
            cout << "Message " << t << " to " << name << ": " << vM[i].message << endl; //outputs messages
            t++;
        }
    }

    if (t == 1) {
        cout << "No messages" << endl; //if t = to what it is initialised as then it ouputs no sent messages
    }
    pressEnter();
    viewMessages(ID, p, vP, vT);
}

// Class/report functions
void viewClass(int num, int ID, vector<Teachers>& vT, vector<Students>& vS) {
    system("cls");
    int t = 0; //counter
    try {
        if (int length = to_string(ID).length() == 4) { //since this is used by teachers and students checks if a teacher is using it
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
            cout << "Your classmates : " << endl; //if a student opens the function simply finds other students with same class and outputs them
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
void viewReportAdmin() {
    int sClass;
    int t = 0;
    int average = 0;

    // Create vector of all students
    try {
        std::vector<Students> vS = createStudentsVector();
        std::system("cls");
        std::cout << "\tView reports" << std::endl;
        std::cout << "*********************************" << std::endl << std::endl;
        std::vector<int> classes;
        for (const Students& c : vS) {
            classes.push_back(c.Class);
        }
        if (classes.empty()) {
            std::cout << "No Classes Found." << std::endl;
            pressEnter();
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
        }
        bool validInput = false; //checks for valid input
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
        std::cout << "\tView reports" << std::endl;
        std::cout << "*********************************" << std::endl << std::endl;

        
        std::vector<Students> inClass;

        if (sClass == 0) {
            std::cout << "All Students Not In a Class " << std::endl << std::endl; //if no classes are assigned to students
        }
        else {
            std::cout << "Class " << sClass << std::endl << std::endl;
        }

        for (const auto& student : vS) {
            if (student.Class == sClass) {
                inClass.push_back(student); //assigns the students which are in the already inputed class
            }
        }
        std::sort(inClass.begin(), inClass.end(), compareByName); //sorts them
        cout << "Grades: \t\t\t(G1)  (G2)  (G3)  (G4)  (G5)  (AVG)" << endl;
        for (int i = 0; i < vS.size(); i++) {
            if (vS[i].Class == sClass) {
                int n = 0;
                average = 0;
                t++;
                cout << t << ". " << vS[i].Name;
                placeCursor(screen, t + 5, 31);
                for (int grade : {vS[i].Grade1, vS[i].Grade2, vS[i].Grade3, vS[i].Grade4, vS[i].Grade5}) {
                    if (grade > -1) {
                        std::cout << "  " << grade << "  "; //outputs the grades
                        average += grade; //Then gets the average
                        n++;
                    }
                    else {
                        std::cout << "  XX  ";
                    }
                }
                if (n == 0) {
                    cout << "  XX" << endl;
                }
                else {
                    cout << "  " << average / n << endl;
                }
            }
        }

        cout << endl << endl;

        pressEnter();
    }
        catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    
}
void viewReport(int p, vector<Students>& vS) {
    system("cls");
    int i = 0;
    float average = 0;
    cout << vS[p].Name << "'s report :" << endl << endl;
    cout << " (G1)  (G2)  (G3)  (G4)  (G5)" << endl;
    for (int grade : {vS[p].Grade1, vS[p].Grade2, vS[p].Grade3, vS[p].Grade4, vS[p].Grade5}) {
        if (grade > -1) {
            std::cout << "  " << grade << "  "; //outputs the grades
            i++;
            average += grade; //gets the average
        }
        else {
            std::cout << "  XX  ";
        }
    }
    if (i > 0) {
        cout << "\n\nYour average is : " << average / i; //divides the average by iterations
    }
    else {
        cout << "\n\nNo grades added yet.";
    }
    cout << endl << endl;
    pressEnter();
    return;
}
void viewChildReport(int ID, int num, vector<Parents>& vP) {
    system("cls");
    int c1, c2, c3, c4; //initialize children
    int child = 0;
    int t = 0;
    int average = 0;
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
        }// all of the if statments gathers which children belong to which parents account
        cout << "Your children reports" << endl;
        cout << "grades: \t\t\t(G1)  (G2)  (G3)  (G4)  (G5)  (AVG)" << endl;
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
            t++;
            cout << t << ". " << vS[currentChild].Name;
            average = 0;
            int n = 0;
            placeCursor(screen, t + 1, 31);
            for (int grade : {vS[i].Grade1, vS[i].Grade2, vS[i].Grade3, vS[i].Grade4, vS[i].Grade5}) {
                if (grade > -1) {
                    std::cout << "  " << grade << "  ";
                    average += grade; //adds up all the grades
                    ++n;
                }
                else {
                    std::cout << "  XX  ";
                }
            }
            if (n == 0) {
                cout << "  XX" << endl;
            }
            else {
                cout << "  " << average / n << endl; //outputs the average
            }
        }
       
        cout << endl << endl;
        pressEnter();
        return;
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}
void viewClassReport(int num, vector<Teachers>& vT, vector<Students>& vS) {
    system("cls");
    int t = 0;
    int average = 0;
    cout << "Your class: " << endl;
    cout << "Grades: \t\t\t(G1)  (G2)  (G3)  (G4)  (G5)  (AVG)" << endl;
    for (int i = 0; i < vS.size(); i++) {
        if (vS[i].Class == vT[num].Class) {
            t++;
            int n = 0;
            cout << t << ". " << vS[i].Name;
            placeCursor(screen, t + 1, 31);
            for (int grade : {vS[i].Grade1, vS[i].Grade2, vS[i].Grade3, vS[i].Grade4, vS[i].Grade5}) {
                if (grade > -1) {
                    std::cout << "  " << grade << "  "; //outputs every grade
                    average += grade; //average out the grades
                }
                else {
                    std::cout << "  XX  ";
                }
            }
            if (n > 0) {
                cout << "  " << average / t << endl; //outputs the average
            }
            else {
                cout << "  XX" << endl;
            }
        }
    }

    cout << endl << endl;

    pressEnter();
    return;
}

// Update information functions
void updatePersonalInformation(int ID, int p, const AccountType accountType, bool admin) {
    int choice;
    int n;
    // Refresh all account vectors
    std::vector<Students> vS = createStudentsVector();
    std::vector<Parents> vP = createParentsVector();
    std::vector<Teachers> vT = createTeachersVector(); //initalize the vectors

    do {
        std::system("cls");
        std::cout << "\t" << "Changing Information" << std::endl << std::endl;
        // Display user info depending on selected account type
        if (accountType == AccountType::STUDENT) { //outputs student information
            std::cout << "User: " << vS[p].ID << std::endl << std::endl;
            std::cout << "Name: " << vS[p].Name << std::endl;
            std::cout << "Password: " << vS[p].Password << std::endl;
            std::cout << "Address: " << vS[p].Address << std::endl;
            if (admin) {
                std::cout << "Class: " << vS[p].Class << std::endl;
                n = 1;
                for (int grade : {vS[p].Grade1, vS[p].Grade2, vS[p].Grade3, vS[p].Grade4, vS[p].Grade5 }) {
                    if (grade > -1) {
                        std::cout << "Grade " << n++ << ": " << grade << std::endl;
                    }
                    else {
                        std::cout << "Grade " << n++ << ": " << "XX" << std::endl;
                    }
                }
            }
        }
        else if (accountType == AccountType::PARENT) { //outputs parents information
            std::cout << "User: " << vP[p].ID << std::endl << std::endl;
            std::cout << "Name: " << vP[p].Name << std::endl;
            std::cout << "Password: " << vP[p].Password << std::endl;
            std::cout << "Address: " << vP[p].Address << std::endl;
            std::cout << "Contact Number: " << vP[p].cNumber << std::endl;
            if (admin) {
                n = 1;
                for (int ID : {vP[p].childID, vP[p].childID2, vP[p].childID3, vP[p].childID4 }) {
                    if (ID > 0) {
                        std::cout << "Child ID " << n++ << ": " << ID << std::endl;
                    }
                }
            }
        }
        else if (accountType == AccountType::TEACHER) { //outputs teachers information
            std::cout << "User: " << vT[p].ID << std::endl << std::endl;
            std::cout << "Name: " << vT[p].Name << std::endl;
            std::cout << "Password: " << vT[p].Password << std::endl;
            std::cout << "Address: " << vT[p].Address << std::endl;
            std::cout << "Contact Number: " << vT[p].cNumber << std::endl;
            if (admin) {
                std::cout << "Class: " << vT[p].Class << std::endl;
            }
        }
        // Display numbered options the user can edit
        std::cout << "\nWhich information do you want to change ?" << std::endl << std::endl;
        std::cout << "Option" << std::endl;

        n = 1;

        std::cout << n++ << ". Name" << std::endl;
        std::cout << n++ << ". Password" << std::endl;
        std::cout << n++ << ". Address" << std::endl;
        if (accountType == AccountType::PARENT || accountType == AccountType::TEACHER) {
            std::cout << n++ << ". Contact Number" << std::endl; //because student doesn't have a phone number
        }
        if (admin) {
            std::cout << n++ << ". ID" << std::endl;
            if (accountType == AccountType::STUDENT) {
                std::cout << n++ << ". Class" << std::endl;
                std::cout << n++ << ". Grade 1" << std::endl;
                std::cout << n++ << ". Grade 2" << std::endl;
                std::cout << n++ << ". Grade 3" << std::endl;
                std::cout << n++ << ". Grade 4" << std::endl;
                std::cout << n++ << ". Grade 5" << std::endl; //ony students have grades
            }
            else if (accountType == AccountType::PARENT) {
                std::cout << n++ << ". Child ID's" << std::endl; //only parents have child id's
            }
            else if (accountType == AccountType::TEACHER) {

                std::cout << n++ << ". Class" << std::endl;
            }
            std::cout << n++ << ". Delete User Account" << std::endl; //only admin has delete account
        }
        std::cout << n << ". Cancel" << std::endl << std::endl;
        std::cout << "Choice: ";
        // Switch that performs different actions based on what type of user account
        choice = choiceCheck(n);
        std::system("cls");
        switch (choice) {
        case 1: { //switch casewhich opens the function of he information the user has decided they want to change
            if (admin) {
                updateName(ID, p, vS, vP, vT, accountType);
            }
            else {
                updateName(ID, p, vS, vP, vT, accountType);
            }
            break;
        }
        case 2: {
            if (admin) {
                updatePassword(ID, p, vS, vP, vT, accountType);
            }
            else {
                updatePassword(ID, p, vS, vP, vT, accountType);
            }
            break;
        }
        case 3: {
            if (admin) {
                updateAddress(ID, p, vS, vP, vT, accountType);
            }
            else {
                updateAddress(ID, p, vS, vP, vT, accountType);
            }
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
            else if (admin && accountType == AccountType::PARENT || admin && accountType == AccountType::TEACHER) {
                updateID(ID, p, vS, vP, vT, accountType);
            }
            break;
        }
        case 6: {
            if (admin && accountType == AccountType::STUDENT) {
                updateGrade(ID, p, vS, vP, vT, accountType, 1);
            }
            else if (admin && accountType == AccountType::PARENT) {
                updateChildID(ID, p, vS, vP, vT, accountType);
            }
            else if (admin && accountType == AccountType::TEACHER) {
                updateClass(ID, p, vS, vP, vT, accountType);
            }
            break;
        }
        case 7: {
            if (admin && accountType == AccountType::STUDENT) {
                updateGrade(ID, p, vS, vP, vT, accountType, 2);
            }
            else if (admin && accountType == AccountType::PARENT) {
                if (deleteUser(ID, p, vS, vP, vT, accountType) == 1) {
                    return;
                }
            }
            else if (admin && accountType == AccountType::TEACHER) {
                if (deleteUser(ID, p, vS, vP, vT, accountType) == 1) {
                    return;
                }
            }
            break;
        }
        case 8: {
            if (admin && accountType == AccountType::STUDENT) {
                updateGrade(ID, p, vS, vP, vT, accountType, 3);
            }
            break;
        }
        case 9: {
            if (admin && accountType == AccountType::STUDENT) {
                updateGrade(ID, p, vS, vP, vT, accountType, 4);
            }
            break;
        }
        case 10: {
            if (admin && accountType == AccountType::STUDENT) {
                updateGrade(ID, p, vS, vP, vT, accountType, 5);
            }
            break;
        }
        case 11: {
            if (admin && accountType == AccountType::STUDENT) {
                if (deleteUser(ID, p, vS, vP, vT, accountType) == 1) {
                    return;
                }
            }
            break;
        }
        }
    } while (choice < n);

    return;
}
void sChangeInformation(vector<Students>& vS) {
    // Opens file and overwites entire document according to current student vector
    ofstream outputFile("students.txt");
    try {
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing."); //outputs if file failed to open
            return;
        }
        for (int i = 0; i < vS.size(); i++) {
            outputFile << vS[i].ID << "," << vS[i].Name << "," << vS[i].Password << "," << vS[i].Address << "," << vS[i].Class << "," << vS[i].Grade1 << "," << vS[i].Grade2 << "," << vS[i].Grade3 << "," << vS[i].Grade4 << "," << vS[i].Grade5 << endl; //writes every line to the file to include the updated information form the vector
        }
        outputFile.close();
        std::cout << "\nChanges Saved!" << endl << endl; // outputs changes saved
        pressEnter(0);
        return;
    }
    catch (const std::runtime_error& e) {
        std::cout << "\nError: " << e.what() << std::endl; // if file didnt open
    }
}
void pChangeInformation(vector<Parents>& vP, bool noPrint) {
    // Opens file and overwites entire document according to current parent vector
    ofstream outputFile("parents.txt");
    try {
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing."); //outputs if file failed to open
            return;
        }

        for (int i = 0; i < vP.size(); i++) {
            outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << vP[i].Address << "," << vP[i].cNumber << "," << vP[i].childID << "," << vP[i].childID2 << "," << vP[i].childID3 << "," << vP[i].childID4 << endl;//writes every line to the file to include the updated information form the vector
        }
        outputFile.close();
        if (!noPrint) { // Doesn't print these when prompted
            std::cout << "\nChanges Saved!" << endl << endl;
            pressEnter(0);
        }
        return;
    }
    catch (const std::runtime_error& e) {
        std::cout << "\nError: " << e.what() << std::endl;
    }
}
void tChangeInformation(vector<Teachers>& vT)/*teacher change information*/ {
    ofstream outputFile("teachers.txt");
    try {
        if (!outputFile.is_open()) {
            throw std::runtime_error("Failed to open file for writing."); //if the file couldn't open
            return;
        }

        for (int i = 0; i < vT.size(); i++) {
            outputFile << vT[i].ID << "," << vT[i].Name << "," << vT[i].Password << "," << vT[i].Address << "," << vT[i].cNumber << "," << vT[i].Class << endl;//writes every line to the file to include the updated information form the vector
        }
        outputFile.close();
        std::cout << "\nChanges Saved!" << endl << endl; //svae changes
        pressEnter(0);
        return;
    }
    catch (const std::runtime_error& e) {
        std::cout << "\nError: " << e.what() << std::endl;
    }
}
void updateName(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    std::string fname;
    std::string lname;
    std::cout << "\tUpdating Name or write ""NULL"" to cancel" << std::endl << std::endl;
    // first name input
    std::cout << "First Name:                    Last Name:" << std::endl; //adds a gap in between first and last name so that they both always visable
    placeCursor(screen, 2, 12); //moves cursor
    std::getline(std::cin >> std::ws, fname);
    if (fname == "NULL") {

        placeCursor(screen, 6, 0);
        std::cout << "Name Change Cancelled." << std::endl;
        std::cout << "Press Enter to continue...";
        std::cin.get(); //press enter to return
        std::system("cls");
        return;
    }
    while (!isAlphabet(fname)) { // Validation check
        placeCursor(screen, 4, 0);
        std::cout << "Invalid name. Please only use alphabet characters."; //if not all alphabet
        placeCursor(screen, 2, 0);
        std::cout << "First Name:                    Last Name:";// re writes first and last name in new position
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
        return;
    }

    while (!isAlphabet(lname)) { // Validation check
        placeCursor(screen, 4, 0);
        std::cout << "Invalid name. Please only use alphabet characters."; //if it isn't alphabet
        placeCursor(screen, 2, 30);
        std::cout << " Last Name:                                       "; //saves first name but re outputs last name
        placeCursor(screen, 2, 42);
        std::getline(std::cin >> std::ws, lname);
    }
    std::string str = fname + ' ' + lname;
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' ');
    //sends the str to the correct update inormation based on account types
    if (accountType == AccountType::STUDENT) {
        vS[p].Name = str;
        sChangeInformation(vS);
    }
    else if (accountType == AccountType::TEACHER) {
        vT[p].Name = str;
        tChangeInformation(vT);
    }
    else if (accountType == AccountType::PARENT) {
        vP[p].Name = str;
        pChangeInformation(vP);
    }
}
void updatePassword(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    string newPass;
    placeCursor(screen, 0, 0);
    std::cout << "Enter a new password must be more than 8 characters or write ""NULL"" to cancel";
    placeCursor(screen, 2, 0);
    std::cout << "Password: ";
    std::getline(cin >> ws, newPass);

    if (newPass == "NULL") {
        return;
    }

    while (newPass.length() < 8) { // minimum 8 characters check
        placeCursor(screen, 4, 0);
        std::cout << "Password needs to be at least 8 characters or enter ""NULL"" to cancel. ";
        placeCursor(screen, 2, 0);
        std::cout << "Password:                   ";
        placeCursor(screen, 2, 10);
        std::getline(std::cin >> std::ws, newPass);
        if (newPass == "NULL") {
            return;
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(80, ' ');
    placeCursor(screen, 4, 0);
    // change vector and write change to file
    if (accountType == AccountType::STUDENT) {
        vS[p].Password = newPass;
        sChangeInformation(vS);
    }
    else if (accountType == AccountType::TEACHER) {
        vT[p].Password = newPass;
        tChangeInformation(vT);
    }
    else if (accountType == AccountType::PARENT) {
        vP[p].Password = newPass;
        pChangeInformation(vP);
    }

}
void updateAddress(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    std::string address;
    std::string adNum;
    std::string adName;
    placeCursor(screen, 0, 0);
    cout << "Enter a new address or write ""NULL"" to cancel"; // Prompt user to enter a new address or cancel
    placeCursor(screen, 2, 0);
    cout << "Street Number : "; // Prompt user to enter the street number
    std::getline(std::cin >> std::ws, adNum);
    if (adNum == "NULL") {
        return;
    }
    while (!containsNumber(adNum)) { // Invalid input message when the street number doesn't contain a number
        placeCursor(screen, 4, 0);
        cout << "Invalid input. Must contain at least one number.";
         // Prompt user to enter the street name
        placeCursor(screen, 2, 0);
        std::cout << "Street Number:          ";
        placeCursor(screen, 2, 15);
        std::getline(std::cin >> std::ws, adNum);
        if (adNum == "NULL") {
            return;
        }
        
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(80, ' '); // clear error message

    // Address name input
    placeCursor(screen, 3, 0);
    std::cout << "Street Name: ";
    std::getline(std::cin >> std::ws, adName);
    if (adName == "NULL") {
        return;

    }
    while (!isAlphabet(adName)) {// Invalid name message when the street name contains non-alphabetic characters
        placeCursor(screen, 5, 0);
        std::cout << "Invalid name. Please only use alphabet characters. ";
        placeCursor(screen, 3, 0);
        std::cout << "Street Name:                                       ";
        placeCursor(screen, 3, 12);
        std::getline(std::cin >> std::ws, adName);
        if (adName == "NULL") {
            return;
        }
    }
    placeCursor(screen, 5, 0);
    std::cout << std::string(80, ' '); // clear error message

    address = adNum + " " + adName; // adds the two strings together with a space in the middle
    //sends user to their respected update information based on account types
    if (accountType == AccountType::STUDENT) {
        vS[p].Address = address;
        sChangeInformation(vS);
    }
    else if (accountType == AccountType::TEACHER) {
        vT[p].Address = address;
        tChangeInformation(vT);
    }
    else if (accountType == AccountType::PARENT) {
        vP[p].Address = address;
        pChangeInformation(vP);
    }

}
void updateContactNumber(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    std::string newCNum;
    placeCursor(screen, 0, 0);
    cout << "Enter a new Contact Number minimum length of 7 digits or write ""NULL"" to cancel"; // prompts the user to enter a contact number
    placeCursor(screen, 2, 0);
    cout << "Contact Number: ";
    std::getline(cin >> ws, newCNum); //gets the contact number
    if (newCNum == "NULL") {
        return;
    }
    while (!onlyNumbers(newCNum) || newCNum.length() < 7) { //if they dont input a value which is all numbers or more than 7 charcters
        placeCursor(screen, 4, 0);
        std::cout << "Invalid input. The input should consist of only numbers with a minimum length of 7 digits.";
        placeCursor(screen, 2, 0);
        std::cout << "Contact Number:                                 ";
        placeCursor(screen, 2, 16);
        std::getline(std::cin >> std::ws, newCNum);
        if (newCNum == "NULL") {
            return;
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(80, ' '); // clear error message

    //sends the user to their respected change infomation based on account types
    if (accountType == AccountType::TEACHER) {
        vT[p].cNumber = newCNum;
        tChangeInformation(vT);
    }
    else if (accountType == AccountType::PARENT) {
        vP[p].cNumber = newCNum;
        pChangeInformation(vP);
    }
}
void updateClass(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    std::string newClass;

    std::cout << "\tUpdating Class or write ""NULL"" to cancel" << std::endl;

    placeCursor(screen, 2, 0);
    std::cout << "Class (1-9): "; //prompts user to enter number from 1-9 and if they eneter NULL the program returns
    std::getline(std::cin >> std::ws, newClass);
    while (true) {
        if (newClass == "NULL") {
            return;
        }

        while (!onlyNumbers(newClass)) {
            placeCursor(screen, 4, 0);
            std::cout << "Invalid class. Please only use a single digit.";
            placeCursor(screen, 2, 0);
            std::cout << "Class (1-9):                          "; //asks them for an input again if their first one wasn't only digits
            placeCursor(screen, 2, 12);
            std::getline(std::cin >> std::ws, newClass);

            if (newClass == "NULL") {
                return;
            }
        }

        if (accountType == AccountType::TEACHER) { // 
            bool validClass = true;
            for (int i = 0; i < vT.size(); i++) {
                if (vT[i].Class == stoi(newClass) && i != p) { //checks if there is a matching clsss
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
            std::getline(std::cin >> std::ws, newClass);
        }
        else {
            break; // Exit the while loop for non-teacher account types
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' '); // clear error message

    //send the user to their respective change information based on the users
    if (accountType == AccountType::STUDENT) {
        vS[p].Class = std::stoi(newClass);
        sChangeInformation(vS);
    }
    else if (accountType == AccountType::TEACHER) {
        vT[p].Class = std::stoi(newClass);
        tChangeInformation(vT);
    }
}
void updateGrade(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType, const int gradeType)
{
    std::string newGrade;

    std::cout << "\tUpdating Grade or write ""NULL"" to cancel" << std::endl; //prompts the user to enter a grade
    placeCursor(screen, 2, 0);
    std::cout << "Grade (0 - 100): ";
    placeCursor(screen, 2, 18);
    std::getline(std::cin >> std::ws, newGrade);
    if (newGrade == "NULL") { //if entered text is = to nulll then it will return
        return;
    }
    // Validation check (number: 0 - 100)
    while (!onlyNumbers(newGrade) || std::stoi(newGrade) > 100 || std::stoi(newGrade) < 0) {
        placeCursor(screen, 4, 0);
        std::cout << "Invalid input. Grade must be a number (0 - 100)."; //prompts the user to enter a grade between 0-100
        placeCursor(screen, 2, 0);
        std::cout << "Grade (0 - 100):                                 ";
        placeCursor(screen, 2, 18);
        std::getline(std::cin >> std::ws, newGrade);
        if (newGrade == "NULL") {//if entered text is = to nulll then it will return
            return;
        }
    }
    placeCursor(screen, 4, 0);
    std::cout << std::string(60, ' '); // clear error message

    int counter = 1;
    int* grades[] = { &vS[p].Grade1, &vS[p].Grade2, &vS[p].Grade3, &vS[p].Grade4, &vS[p].Grade5 };

    for (int* grade : grades) {
        if (counter == gradeType) {
            *grade = std::stoi(newGrade); //assigns the entered grade to the place in the vector
            break;
        }
        counter++;
    }
    sChangeInformation(vS); //student change information

}
void updateChildID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    int n = 2;
    std::string newCID;
    vP = createParentsVector();; // refresh parent vector

    std::cout << "\tUpdating Child ID's" << std::endl;
    
    placeCursor(screen, 2, 0);
    
    std::cout << "1. Add New" << std::endl;
    std::cout << "2. Cancel" << std::endl;
    std::cout << "   Or \nDelete:" << std::endl;

    for (int childID : { vP[p].childID, vP[p].childID2, vP[p].childID3, vP[p].childID4 } ) {
        if (std::to_string(childID).length() == 6) {
            for (const auto& student : vS) {
                if (student.ID == childID) {
                    std::cout << ++n << ". Child: " << student.ID << " : " << student.Name << std::endl;
                }
            }
        }
    } //outputs childid 1, 2, 3 and 4
    std::cout << std::endl << "Choice: ";
    int select = choiceCheck(n);
    int counter;
    std::vector<int> studentIDs = readExistingIDs("students.txt");

    switch (select)
    {
    // Add new
    case 1: {
        if (vP[p].childID4 != 0) {
            std::cout << "Sorry, children limit reached." << std::endl;
            pressEnter();
            break;
        }
        std::system("cls");
        std::cout << "\tAdding new child ID or write ""NULL"" to cancel" << std::endl;
        std::cout << "Parent Account: " << vP[p].Name << std::endl;
        std::cout << "\nEnter new ID: ";
        std::cin >> newCID;
        if (newCID == "NULL") {
            return;
        }
        // ID number/length validation
        while (!onlyNumbers(newCID) || newCID.length() != 6) {
            std::cout << "Student ID needs to be exactly 6 digits" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "Enter new ID:                           ";
            placeCursor(screen, 3, 15);
            std::cin >> newCID;
            if (newCID == "NULL") {
                return;
            }
        }
        
        bool isValid = false;
        int childIDInt;


        while (!isValid) {
            std::istringstream(newCID) >> childIDInt; //checks if child id matches current ids
            for (int i : studentIDs) {
                if (i == childIDInt) {
                    isValid = true;
                    break;
                }
            }
            if (isValid) { break; }
            placeCursor(screen, 5, 0);
            std::cout << "ID does not match any current students. (The input should consist of 6 numbers only)";
            placeCursor(screen, 3, 0);
            std::cout << "Enter New ID:                     ";
            placeCursor(screen, 3, 15);
            std::cin >> newCID;
        }
        placeCursor(screen, 5, 0);
        std::cout << std::string(80, ' '); // clear error message
        counter = 1;

        for (int childID : {vP[p].childID, vP[p].childID2, vP[p].childID3, vP[p].childID4}) {
            if (childID == 0 || childID == stoi(newCID)) {
                break;
            }
            counter++;
        }
        if (counter == 1) {
            vP[p].childID = stoi(newCID);
            break;
        }
        else if (counter == 2) {
            vP[p].childID2 = stoi(newCID);
            break;
        }
        else if (counter == 3) {
            vP[p].childID3 = stoi(newCID);
            break;
        }
        else if (counter == 4) {
            vP[p].childID4 = stoi(newCID);
            break;
        }
        break;
    }
    // Cancel
    case 2: {
        return;
        break;
    }
    // delete childID1
    case 3: {
        vP[p].childID = 0;
        if (vP[p].childID2 == 0) {
            break;
        }
        else {
            vP[p].childID = vP[p].childID2;
            vP[p].childID2 = vP[p].childID3;
            vP[p].childID3 = vP[p].childID4;
            vP[p].childID4 = 0; //rearranges the ids to make 2 go to 1.
        }
        break;
    }
    // delete childID2
    case 4: {
        vP[p].childID2 = 0;
        if (vP[p].childID3 == 0) {
            break;
        }
        else {
            vP[p].childID2 = vP[p].childID3;
            vP[p].childID3 = vP[p].childID4; //same with last rearrange but it makes it go from 3 to 2.
            vP[p].childID4 = 0;
        }
        break;
    }
    // delete childID3
    case 5: {
        vP[p].childID3 = 0;
        if (vP[p].childID4 == 0) {
            break;
        }
        else {
            vP[p].childID3 = vP[p].childID4;
            vP[p].childID4 = 0;
        }
        break;
    }
    // delete childID4
    case 6: {
        vP[p].childID4 = 0;
        break;
    }
    }

    pChangeInformation(vP); //goes to this function to output the updated vector in the file
    return;
}
void updateID(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    std::string newID;
    std::cout << "\tUpdating ID or write ""NULL"" to cancel" << std::endl;
    //outputs current ID based on account types
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
        return;
    }
    // ID number/length validation
    if (accountType == AccountType::STUDENT) {
        while (!onlyNumbers(newID) || newID.length() != 6 || newID[0] == '0') {
            std::cout << "Student ID needs to be exactly 6 digits and cannot start with '0'" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                return;
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
        while (!onlyNumbers(newID) || newID.length() != 4 || newID[0] == '0') {
            std::cout << "Teacher ID needs to be exactly 4 digits and cannot start with '0'" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                return;
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
        while (!onlyNumbers(newID) || newID.length() != 5 || newID[0] == '0') {
            std::cout << "Parent ID needs to be exactly 5 digits and cannot start with '0'" << std::endl;
            placeCursor(screen, 3, 0);
            std::cout << "New ID:                           ";
            placeCursor(screen, 3, 8);
            std::cin >> newID;
            if (newID == "NULL") {
                return;
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
 
    if (accountType == AccountType::STUDENT) {
        // Update student vector / file
        vS[p].ID = std::stoi(newID);
        // update child ID from parent vector / file
        for (Parents& parent : vP) {
            Parents modifiedParent = parent;  // Make a copy of the parent object
            if (modifiedParent.childID == ID) {
                modifiedParent.childID = std::stoi(newID);
            }
            if (modifiedParent.childID2 == ID) {
                modifiedParent.childID2 = std::stoi(newID);
            }
            if (modifiedParent.childID3 == ID) {
                modifiedParent.childID3 = std::stoi(newID);
            }
            if (modifiedParent.childID4 == ID) {
                modifiedParent.childID4 = std::stoi(newID);
            }
            parent = modifiedParent;  // Replace the original object with the modified copy
        }
        pChangeInformation(vP, true);
        sChangeInformation(vS);
    }
    //goes into the respected function based on account type
    else if (accountType == AccountType::TEACHER) {
        vT[p].ID = std::stoi(newID);
        tChangeInformation(vT);
    }
    else if (accountType == AccountType::PARENT) {
        vP[p].ID = std::stoi(newID);
        pChangeInformation(vP);
    }
}
int deleteUser(int ID, int p, std::vector<Students>& vS, std::vector<Parents>& vP, std::vector<Teachers>& vT, const AccountType accountType)
{
    int choice;
    std::string fileName;
    if (accountType == AccountType::STUDENT) {
        fileName = "students.txt";
    }
    else if (accountType == AccountType::PARENT) {
        fileName = "parents.txt";
    }
    else if (accountType == AccountType::TEACHER) {
        fileName = "teachers.txt";
    }
    std::system("cls");
    std::cout << "Are you sure you want to delete this account" << std::endl <<
        "This action cannot be undone." << std::endl << std::endl;
    std::cout << "1. Yes - Delete\n2. No - Cancel" << std::endl << std::endl;
    std::cout << "Choice: ";
    choice = choiceCheck(2);

    switch (choice) {
    case 1: {
        ofstream outputFile(fileName);
        try {
            if (!outputFile.is_open()) {
                throw std::runtime_error("Failed to open file for writing.");
                return 0;
            }
            // Overwrites student file from vector, but leaves out the current selected students account
            if (accountType == AccountType::STUDENT) {
                for (int i = 0; i < vS.size(); i++) {
                    if (vS[i].ID != vS[p].ID) {
                        outputFile << vS[i].ID << "," << vS[i].Name << "," << vS[i].Password << "," << vS[i].Address << "," << vS[i].Class << "," << vS[i].Grade1 << "," << vS[i].Grade2 << "," << vS[i].Grade3 << "," << vS[i].Grade4 << "," << vS[i].Grade5 << endl;
                    }
                }
                // update child ID from parent vector / file
                for (Parents& parent : vP) {
                    Parents modifiedParent = parent;  // Make a copy of the parent object
                    if (modifiedParent.childID == ID) {
                        modifiedParent.childID = modifiedParent.childID2;
                        modifiedParent.childID2 = modifiedParent.childID3;
                        modifiedParent.childID3 = modifiedParent.childID4;
                        modifiedParent.childID4 = 0;
                    }
                    if (modifiedParent.childID2 == ID) {
                        modifiedParent.childID2 = modifiedParent.childID3;
                        modifiedParent.childID3 = modifiedParent.childID4;
                        modifiedParent.childID4 = 0;
                    }
                    if (modifiedParent.childID3 == ID) {
                        modifiedParent.childID3 = modifiedParent.childID4;
                        modifiedParent.childID4 = 0;
                    }
                    if (modifiedParent.childID4 == ID) {
                        modifiedParent.childID4 = 0;
                    }
                    parent = modifiedParent;  // Replace the original object with the modified copy
                }
                pChangeInformation(vP, true);
                sChangeInformation(vS);
            }
            // Overwrites file (same as student)
            else if (accountType == AccountType::PARENT) {
                for (int i = 0; i < vP.size(); i++) {
                    if (vP[i].ID != vP[p].ID) {
                        outputFile << vP[i].ID << "," << vP[i].Name << "," << vP[i].Password << "," << vP[i].Address << "," << vP[i].cNumber << "," << vP[i].childID << "," << vP[i].childID2 << "," << vP[i].childID3 << "," << vP[i].childID4 << endl;
                    }
                }
            }
            // Overwrites file (same as student)
            else if (accountType == AccountType::TEACHER) {
                for (int i = 0; i < vT.size(); i++) {
                    if (vT[i].ID != vT[p].ID) {
                        outputFile << vT[i].ID << "," << vT[i].Name << "," << vT[i].Password << "," << vT[i].Address << "," << vT[i].cNumber << "," << vT[i].Class << endl;
                    }
                }
            }

            outputFile.close();

            std::cout << "USER DELETED" << std::endl;
            pressEnter();
            manageSchool();
            return 1;
            break;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        break;
    }
    case 2: {
        return 0;
    }
    }
    return 0;

}
// Admin functions
void manageSchool() {
    int choice;
    do {
        // Menu for admin managing school
        system("cls");
        cout << "\t" << "Manage School ";
        cout << endl << endl;
        cout << "1. Manage School Information" << endl << "2. Manage Students" << endl << "3. Manage Parents" << endl << "4. Manage Teachers" << endl << "5. Cancel" << endl << "6. Exit" << endl << endl; //outputs the 6 options
        cout << "Make your choice : ";

        choice = choiceCheck(7);

        switch (choice) { //switch case for the repected functions
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
        }
    } while (choice <= 4);
    if (choice == 5) {
        system("cls");
        sALogin();
    }
    else {
        exit(0);
    }
}
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
        std::cout << "1. Change School Name" << std::endl << "2. Add News & Events" << std::endl << "3. Remove New & Events" << std::endl << "4. Cancel" << std::endl;
        cout << "Make your pick: ";
        choice = choiceCheck(4);

        switch (choice) {
            // Change school name
        case 1: {
            std::system("cls");
            string schName;
            std::cout << "\tManaging School" << std::endl << "*******************************" << std::endl << std::endl;
            std::cout << "New Name or type 'NULL' to exit: ";
            std::getline(std::cin >> std::ws, schName);
            if (schName == "NULL") {
                manageSchoolInformation();
            } else{
                admin.SchoolName = schName;
            }

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
                pressEnter(0);
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
                std::vector<std::string> updatedNews; // New vector with chosen line deleted
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
void manageStudents()
{
    // Menu for searching students
    int choice;
    string sID;
    int sClass;
    vector<int> studentIDs = readExistingIDs("students.txt");
    vector<Students> vS = createStudentsVector();
    do {
        std::cout << "\tManaging Students" << std::endl;
        std::cout << "*********************************" << std::endl << std::endl;
        std::cout << "1. Search students by ID" << std::endl << "2. Search students by class" << std::endl << "3. Cancel" << std::endl; //prompts the user to enter one of 3 options
        choice = choiceCheck(3);

        switch (choice) {
        case 1: {
            // Student ID search
            std::system("cls");
            std::string sID;
            bool validID = false;
            do {
                std::cout << "Enter Student ID (or enter '0' to cancel): ";
                std::cin >> sID;
                if (sID == "0") {
                    std::system("cls");
                    return;
                }
                if (onlyNumbers(sID) && sID.length() == 6) {
                    for (int i : studentIDs) {
                        if (i == std::stoi(sID)) {
                            validID = true;
                            break;
                        }
                    }
                }
                if (!onlyNumbers(sID) || sID.length() != 6 || !validID) {
                    std::cout << "\nNot a valid Student ID (must contain 6 numbers only)" << std::endl; //checks if it is 6 digits and only numbers
                }
            } while (!onlyNumbers(sID) || sID.length() != 6 || !validID);

            // Get student position from vector of all students by matching ID
            int p;
            int counter = 0;
            for (auto& student : vS) {
                if (student.ID == std::stoi(sID)) {
                    p = counter;
                    break;
                }
                counter++;
            }
            updatePersonalInformation(std::stoi(sID), p, AccountType::STUDENT, true);
            break;
        }
        case 2: {
            vS = createStudentsVector(); // Refresh student vector
            // Student class search
            std::system("cls");
            std::cout << "\tManaging Students" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;
            std::vector<int> classes; // Create vector of classes with students in them
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
                for (const int& i : uniqueClasses) { // Checks if class is valid
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

            std::system("cls");
            std::cout << "\tManaging Students" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;

            int n = 1;
            std::vector<Students> inClass;

            if (sClass == 0) {
                std::cout << "All Students Not In a Class " << std::endl << std::endl; //if no student is in an applicabe class
            }
            else {
                std::cout << "Class " << sClass << std::endl << std::endl; //outputs the sudents class
            }

            for (const auto& student : vS) {
                if (student.Class == sClass) {
                    inClass.push_back(student);
                }
            }
            std::sort(inClass.begin(), inClass.end(), compareByName);

            // Display student info in class
            std::cout << "Option \t ID \t\t Name \t\t\tClass \t\t Address \t\t(G1) (G2) (G3) (G4) (G5)" << endl;
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
                            std::cout << " " << grade << "  ";
                        }
                        else {
                            std::cout << " XX  ";
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
            int p = 0;
            int counter = 0;
            for (auto& student : vS) {
                if (student.ID == ID) {
                    p = counter;
                    break;
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
void manageParents() 
{
    // Menu for searching parents
    int choice;
    int p;
    int counter;
    string pID;
    vector<int> parentIDs = readExistingIDs("parents.txt");
    vector<Parents> vP = createParentsVector();
    do {
        std::cout << "\tManaging Parents" << std::endl;
        std::cout << "*********************************" << std::endl << std::endl;
        std::cout << "1. Search Parents by ID" << std::endl << "2. View All" << std::endl << "3. Cancel" << std::endl;
        std::cout << "Make your choice : ";
        choice = choiceCheck(3);

        switch (choice) {
        case 1: {
            // Parent ID search
            bool validID = false;

            std::system("cls");
            std::cout << "\tManaging Parents" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;
            do {
                std::cout << "Enter Parent ID (or enter \'0\' to cancel): ";
                std::cin >> pID;
                if (pID == "0") {
                    std::system("cls");
                    return;
                }
                if (onlyNumbers(pID) && pID.length() == 5) {
                    for (int i : parentIDs) {
                        if (i == std::stoi(pID)) {
                            validID = true;
                            break;
                        }
                    }
                }
                if (!onlyNumbers(pID) || pID.length() != 5 || !validID) {
                    std::cout << "\nNot a valid Parent ID (must contain 5 numbers only)" << std::endl;
                }
            } while (!onlyNumbers(pID) || pID.length() != 5 || !validID);
            // // Get parent position from vector of all parents by matching ID
            counter = 0;
            for (auto& Parents : vP) {
                if (Parents.ID == std::stoi(pID)) {
                    p = counter;
                    break;
                }
                counter++;
            }
            updatePersonalInformation(std::stoi(pID), p, AccountType::PARENT, true); //sends them to their respected function
            break;
        }

        case 2: {
            std::system("cls");
            p = 0;
            int choice2;
            std::cout << "Viewing All Parents to Manage" << std::endl << std::endl;
            for (Parents& parent : vP) {
                std::cout << p++ + 1 << ". " << parent.Name << std::endl;
            }
            std::cout << "\nChoice: ";
            choice2 = choiceCheck(p);
            updatePersonalInformation(vP[choice2 - 1].ID, choice2 - 1, AccountType::PARENT, true);
            break;
        }
        }
    } while (choice != 3);

}
void manageTeachers()
{
    // Menu for searching teachers
    int choice;
    string tID;
    vector<int> teacherIDs = readExistingIDs("teachers.txt");
    vector<Teachers> vT = createTeachersVector();
    do {
        std::cout << "\tManaging Teachers" << std::endl;
        std::cout << "*********************************" << std::endl << std::endl;
        std::cout << "1. Search Teachers by ID" << std::endl << "2. View All" << std::endl << "3. Cancel" << std::endl;
        std::cout << "Make your choice : ";
        choice = choiceCheck(3);

        switch (choice) {
        case 1: {
            // Teacher ID search
            bool validID = false;

            std::system("cls");
            std::cout << "\tManaging Teachers" << std::endl;
            std::cout << "*********************************" << std::endl << std::endl;
            do {
                std::cout << "Enter Teacher ID (or enter \'0\' to cancel): ";
                std::cin >> tID;
                if (tID == "0") {
                    std::system("cls"); //if 0 return
                    return;
                }
                if (onlyNumbers(tID) && tID.length() == 4) {
                    for (int i : teacherIDs) {
                        if (i == std::stoi(tID)) {
                            validID = true;
                            break;
                        }
                    }
                }
                if (!onlyNumbers(tID) || tID.length() != 4 || !validID) {
                    std::cout << "\nNot a valid Teacher ID (must contain 4 numbers only)" << std::endl;
                }
            } while (!onlyNumbers(tID) || tID.length() != 4 || !validID);
            // // Get teacher position from vector of all teacher by matching ID
            int p;
            int counter = 0;
            for (auto& Teachers : vT) {
                if (Teachers.ID == std::stoi(tID)) {
                    p = counter;
                    break;
                }
                counter++;
            }
            updatePersonalInformation(std::stoi(tID), p, AccountType::TEACHER, true); //update information
            break;
        }

        case 2: {
            std::system("cls");
            int p = 0;
            int choice2;
            std::cout << "Viewing All Teachers to Manage" << std::endl << std::endl;
            for (Teachers& teacher : vT) {
                std::cout << p++ + 1 << ". " << teacher.Name << std::endl;
            }
            std::cout << "\nChoice: ";
            choice2 = choiceCheck(p);
            updatePersonalInformation(vT[choice2 - 1].ID, choice2 - 1, AccountType::TEACHER, true);
            break;
        }
        }
    } while (choice != 3);
}

// General functions
// 
// Function for sorting students vector by name
bool compareByName(const Students& student1, const Students& student2)
{
    return student1.Name < student2.Name;
}
// Function for 'press enter to continue'
void pressEnter(int type)
{
    std::cout << "Press Enter to continue..."; //asks for input
    if (type == 1) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.get(); //gets the input
    std::system("cls"); //clear screen
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
// Function to read existing student IDs from the file
std::vector<int> readExistingIDs(const std::string& fileName)
{
    std::vector<int> existingIDs;
    std::ifstream inputFile(fileName);
    std::string line;

    try {
        if (!inputFile.is_open()) {
            throw std::ios_base::failure("Failed to open file.");
        }

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
                    // Handle the exception
                    std::cerr << "Error converting string to integer: " << e.what() << std::endl;
                }
            }
        }

        inputFile.close();
    }
    catch (const std::ios_base::failure& e) {
        // Handle the exception
        std::cerr << "Error opening file: " << e.what() << std::endl;
    }

    return existingIDs;
}
// Function to place the cursor
void placeCursor(HANDLE screen, int row, int col)
{
    COORD position;
    position.Y = row;
    position.X = col;
    SetConsoleCursorPosition(screen, position);
}