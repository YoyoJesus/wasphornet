#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <ctime>
#include "process.hpp"

using std::cout; using std::endl;
using std::vector; using std::queue; 

int main() {
    srand(time(nullptr)); // seed the random number generator
    const int numProcesses = 4;
    queue<Process *> ready;
    queue<Process *> blocked;

    // create and initialize processes with unique IDs
    for(int i = 0; i < numProcesses; i++) {
        Process *p = new Process();
        cout << p->report(); // report the creation of the process
        p->create();
        ready.push(p);
    }

    cout << endl;
    cout << "-------- scheduler running ---------" << endl;

    while(!ready.empty() || !blocked.empty()) { // if either queue is not empty, proceed
        int choice;

        if(!ready.empty()) {
            choice = rand() % 3; // set a 1/3 chance to suspend, block, or exit a process

            Process *p = ready.front();
            ready.pop();
            cout << "Dispatching..." << endl;
            p->dispatch();
            
            switch(choice) {
                case 1:
                    cout << "Blocking..." << endl;
                    p->block();
                    blocked.push(p);
                    break;
                case 2:
                    cout << "Exiting..." << endl;
                    p->exit();
                    break;
                default: // case 0 essentially
                    cout << "Suspending..." << endl;
                    p->suspend();
                    ready.push(p);
                    break;
            }

            //check if ready queue is empty
            if(ready.empty() && !blocked.empty()) {
                cout << endl;
                cout << "ready queue is empty" << endl;
            }

            cout << endl;
        }

        if(!blocked.empty()) {
            choice = rand() % 3; // set a 1/3 chance to unblock a process

            if(choice == 0) {
                cout << "Unblocking..." << endl;
                Process *p = blocked.front();
                blocked.pop();
                p->unblock();
                ready.push(p);
                cout << endl;
            }
        }
    }

    cout << "all processes exited." << endl;
    cout << "--------- scheduler done ---------" << endl;
}