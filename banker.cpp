#include <iostream>
using namespace std;

// Manal Ali 
// Banker's algorithm 
const int maximumProcesses = 7; 
const int maximumResources = 5; 

int main() {
    int numProcesses;
    int numResources; 

         // 2D array to map each process to every resource type
  int allocation[maximumProcesses][maximumResources];  // this is for currently allocated resources
  int maxRequirement[maximumProcesses][maximumResources];  // maximum need for each process
  int need[maximumProcesses][maximumResources];  // remaining need (will calculated later)
  int available[maximumResources]; // available resources in system
    

    int work[maximumResources];    // Work of available resources
    bool finish[maximumProcesses];    // to track which processes are done
    int path[maximumProcesses];      // to store the safe execution path

    // ask the user to enter number of processes and resources
    cout << "Please, enter number of  processes:(max number is 7) "<<endl;
    cin >> numProcesses;
    cout << "enter number of resources types:(max number is 5) " <<endl;
    cin >> numResources;
    cout << endl;
    
    cout << "allocation part (write numbers with spaces)\n";  //allocation matrix input 
    for (int i = 0; i < numProcesses; i++) {
 cout << "process P" << i << " allocation: ";
 
     for (int j = 0; j < numResources; j++) {
     cin >> allocation[i][j];
     }
 finish[i] = false;  //no process is finished
    }
    
cout<<endl;

    //maximum requirement matrix 
    cout << " max requirement part \n";
for (int i= 0; i< numProcesses; i++) {
cout << "Process P" << i << " max need: " <<endl;
for (int j=0; j< numResources; j++) {
            cin >> maxRequirement[i][j];
 }
    }

    // here is to calculate need matrix 
    for (int i = 0; i< numProcesses; i++) {
     for (int j = 0; j< numResources; j++) {
     need[i][j] = maxRequirement[i][j]-allocation[i][j];
    }
    }
cout<< endl;

    // Input available resources
    
    cout<<"enter available resources: ";
    for (int j = 0; j < numResources; j++){
        cin >> available[j];
        work[j] = available[j]; // Make a working copy
    }
// here is Banker algorithm implementaion 
    
    int compProcesses = 0;  // this is a  for completed processes
    
    
 // continues until success or detect deadlock
while (compProcesses < numProcesses) {
    bool foundSafeProcess = false; 

       
   
    for (int i = 0; i < numProcesses; i++) {
    if (! finish[i]) {  // just for check unfinished processes
                
// see if current available resources can satisfy this process's need
    bool canExecute = true;
    for (int j=0; j< numResources; j++) {
         if (need[i][j]> work[j]) {
        canExecute = false;
    break;  // not enough resources (try next process)
         }
          }

if (canExecute) {
 // Add its allocated resources back to available pool
  for (int j = 0; j < numResources; j++) {
  work[j] = work[j] + allocation[i][j];
                    }
                    
// Mark process as finished
path[compProcesses] =i;
finish[i]=true;
compProcesses++;
foundSafeProcess =true;
                    
 break;  // to start over with updated available resources
     }
      }
    }

// If no progress was made in this round the system is unsafe State
 if (!foundSafeProcess) {
     cout <<" un safe state(deadlock)"<<endl;
    cout << "no process can proceed with current available resources"<<endl;
     return -1;  // exit with error code 
        }
    }

    // system is in safe state
cout << " safe state\n";
    cout << "safe state: ";
for (int i = 0; i < numProcesses; i++) {
        cout << "P" << path[i];
        if (i < numProcesses - 1) {
            cout << " - "; // to represnt the path
        }
    }
    cout<<endl;
    cout <<" safe path exists";

    return 0;
}
