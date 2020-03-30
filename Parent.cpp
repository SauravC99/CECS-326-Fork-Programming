#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

void printMenu();

void printMenu() {
    cout << "What would you like to do?" << endl;
    cout << "1) Run the program" << endl;
    cout << "2) Exit the program" << endl;
}

int main() {
    printMenu();

    int choice, size, count;
    char letter;
    long childPID;
    count = 0;
    
    
    cin >> choice;

    if (choice == 1) {
        cout << "How big is the array?" << endl;
        cin >> size;
        
        cout << "what letter?" << endl;
        cin >> letter;

        //spawn child
        childPID = fork();
        if (childPID > 0) {
            cout << "Parent process: pid " << getpid() << ", ppid " 
            << getppid() << ", child " << childPID << "\n" << endl;

            wait(NULL);

            cout << "here" << endl;
        }
        else if (childPID == 0) {
            cout << "Child process: pid " << getpid() << ", ppid "
            << getppid() << ", child " << childPID << "\n" << endl;
            
            char* array;
            array = new char[size];

            cout << size << endl;

            //fill array with random letters
            for (int i = 0; i < size; i++) {
                array[i] = (rand() % 26) + 'A';
                cout << array[i] << endl;
            }

            //look for letter and count
            for (int i = 0; i < size; i++) {
                if (array[i] == letter) {
                    count++;
                }
            }
            cout << "count is " << count << endl;
        }
        else {
            cout << "error" << endl;
        }

    }
    if (choice == 2) {
        exit(0);
    }
}