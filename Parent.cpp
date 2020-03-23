#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

void printMenu();

void printMenu() {
    cout << "What would you like to do?" << endl;
    cout << "1) Run the program" << endl;
    cout << "2) Exit the program" << endl;
}

int main() {
    long childPID;
    childPID = fork();

    if (childPID > 0) {
        cout << "Parent process: pid " << getpid() << ", ppid " 
        << getppid() << ", child " << childPID << endl;
    }
    else if (childPID == 0) {
        cout << "Child process: pid " << getpid() << ", ppid "
        << getppid() << ", child " << childPID << endl;
    }
    else {
        cout << "error" << endl;
    }

    //printMenu();
    int choice;
    //cin >> choice;

}