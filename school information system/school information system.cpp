// school information system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;
int main()
{
    string school = "Regular high school";
    int choice;
    do {
        cout << "\t" << school << endl;
        cout << "************" << endl << endl;
        cout << "1. Log In/Register" << endl << "2. Events & News" << endl << "3. Exit" << endl << endl;
        cout << "Make your choice : ";
        cin >> choice;
    } while(choice != 3);
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
