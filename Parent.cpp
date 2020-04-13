#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

void printMenu();

int choice, sizea, count;
char letter;
char* array;
long childPID;
    
int main() {
    printMenu();
    cin >> choice;
    do {
        if (choice == 1) {
            cout << "\nHow big is the array?" << endl;
            cin >> sizea;
            
            cout << "What letter?" << endl;
            cin >> letter;

            //spawn child
            childPID = fork();

            if (childPID > 0) { //parent
                cout << "" << endl;
                cout << "Parent process: pid " << getpid() << ", ppid " 
                << getppid() << ", child " << childPID << "\n" << endl;
                
                wait(NULL); //wait untill child is finished

                if (choice == 2) {
                    break;
                }
                else {
                    cout << "back to parent" << endl;
                    cout << "" << endl;
                    printMenu();
                    cin >> choice;
                    //cout << endl;
                    delete array; //free up memory
                    continue;
                }
            }
            else if (childPID == 0) { //child
                if (choice == 2) {
                    break;
                }

                cout << "Child process: pid " << getpid() << ", ppid "
                << getppid() << ", child " << childPID << "\n" << endl;

                array = new char[sizea]; //allocate memory for array

                //fill array with random letters
                for (int i = 0; i < sizea; i++) {
                    array[i] = (rand() % 26) + 'A';
                }

                //Search through array and count
                int i;
                for (i = 0; i < sizea; i++) {
                    if (array[i] == letter) {
                        count++;
                    }
                    if (false){ //false gate, only used for injected bug
                        there:
                        i = 0;
                    }
                }

                if (count == 0) { //injected bug, restart search
                    cout << "INJECTED BUG\nNot found, restarting" << endl;
                    cout << "Run kill command" << endl;
                    cout << "kill -9 " << getpid() << endl;
                    sleep(1); //sleep for a second to see the PID in console
                    goto there;
                }
                
                cout << "count is " << count << endl;
                cout << "" << endl;
                cout << "exit child" << endl;
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
    cout << "==========================" << endl;
    cout << "1) Run the program" << endl;
    cout << "2) Exit the program" << endl;
    cout << "==========================" << endl;
}