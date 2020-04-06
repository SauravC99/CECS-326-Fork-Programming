#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

void printMenu();

int main() {
    int choice, size, count;
    char letter;
    char* array;
    long childPID;
    count = 0;
    
    printMenu();
    cin >> choice;
    do {
        if (choice == 1) {
            cout << "How big is the array?" << endl;
            cin >> size;
            
            cout << "what letter?" << endl;
            cin >> letter;

            //spawn child
            childPID = fork();

            if (childPID > 0) { //parent
                cout << "Parent process: pid " << getpid() << ", ppid " 
                << getppid() << ", child " << childPID << "\n" << endl;
                
                wait(NULL);

                if (choice == 2) {
                    break;
                }
                else {
                    cout << "here" << endl;
                    printMenu();
                    cin >> choice;
                    cout << endl;
                    delete array; //free up memory
                    continue;
                }
            }
            else if (childPID == 0) { //child
                cout << "Child process: pid " << getpid() << ", ppid "
                << getppid() << ", child " << childPID << "\n" << endl;

                array = new char[size]; //allocate memory for array

                if (choice == 2) {
                    break;
                }

                cout << size << endl;

                //fill array with random letters
                for (int i = 0; i < size; i++) {
                    array[i] = (rand() % 26) + 'A';
                    //cout << array[i] << endl;
                }

                int i = 0;
                //look for letter and count
                for (i = 0; i < size; i++) {
                    there:
                    if (array[i] == letter) {
                        count++;
                        //spawn child
                        childPID = fork();
                        if (childPID > 0) { //parent
                            wait(NULL);
                        }
                        if (childPID == 0) { //child
                            //cout << "child made" << endl;
                            if (array[i] == letter) {
                                count++;
                                //cout << "exit child" << endl;
                                exit(1);
                            }
                        }
                    }
                }
                if (count == 0) { //injected bug, restart search
                    cout << "Not found, restarting" << endl;
                    cout << "Run kill command on: " << getpid() << endl;
                    i = 0;
                    sleep(1); //sleep for a second to see the PID in console
                    goto there;
                }
                cout << "HERE" << endl;
                cin >> size;
                cout << "count is " << count << endl;
                cout << "exit last child" << endl;
                exit(1);
            }
            else {
                cout << "fork() error" << endl;
            }
        }
    } while (choice != 2);
    delete array; //free up memory
    return 0;
}

void printMenu() {
    cout << "What would you like to do?" << endl;
    cout << "1) Run the program" << endl;
    cout << "2) Exit the program" << endl;
}