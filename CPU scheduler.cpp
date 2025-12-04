#include<iostream>
using namespace std;
// cpu schedular 
const int numOfProcess = 6; // number of processes that the user can enter 

struct Algo {   
    int processNo;
    int arrival; 
    int burstTime; 
    int priority;
    int waitTime;
    int turnAroundTime;
    int remainBurstTime; // this is for preemptive priority and round robin 
    
} ;

void AlgoTable(Algo Process[], int user ) { // this function is for printing table content of the algorithm
    cout<<"process: "; 
    for (int i=0; i<user; i++) 
    cout<<Process[i].processNo<<"    ";cout<<endl;
    
    cout<<"arrival: "; 
    for (int i=0; i<user; i++) 
    cout<<Process[i].arrival<<"    ";cout<<endl;
    
    cout<<"burst time: "; 
    for (int i=0; i<user; i++) 
    cout<<Process[i].burstTime<<"    ";cout<<endl;
    
    cout<<"priority: "; 
    for (int i=0; i<user; i++) 
    cout<<Process[i].priority<<"    ";cout<<endl;
    
    cout<<"turn around time: "; 
    for (int i=0; i<user; i++) 
    cout<<Process[i].turnAroundTime<<"    ";cout<<endl;
    
    
    // this part for calculating avg wait time & turn around time 
     cout<<"wait time: ";
  double wait_time=0 ;
  double turn_around_time=0;  
  for (int i=0; i<user; i++){
      cout<< Process[i].waitTime << "  ";
      wait_time= wait_time +Process[i].waitTime;
      turn_around_time=turn_around_time+ Process[i].turnAroundTime;
      
  }
   cout<<"average waiting time: "<< wait_time / user << endl;
  cout<<"average turn around time: " <<turn_around_time / user << endl;
  
} 

 
  
 
   
   // first come first serve 
   
   void FCFS (Algo Process[], int user){ // by using bubble sort  to arrange processes based on 'arrival' time
       for (int i=0;i<user-1; i++  ) {
        for(int j=0; j<user-i-1; j++){
        if (Process[j].arrival > Process[j+1].arrival) {
            Algo str = Process[j];   // swap processes if the current one arrived later than the next one
            Process[j]=Process[j+1];
            Process[j+1] = str;
            }
        }
   }  
       
          int time = 0;  //this is for tracks the current CPU time (Completion Time)
     for(int i=0; i<user; i++) {
        if(time < Process[i].arrival) time = Process[i].arrival;
        time = time + Process[i].burstTime;
        Process[i].turnAroundTime = time - Process[i].arrival;
        Process[i].waitTime = Process[i].turnAroundTime - Process[i].burstTime;
        } 
        cout<<endl;
     cout << " results for FCFS:\n";
     AlgoTable(Process, user);
} 
   
   // shortest job first 
   void SJF(Algo Process[], int user){
       int time =0;//current simulation time
       int com =0; // Counter for completed processes
       bool finish[numOfProcess] = {false};
       
       while(com <user){
           int pointer= -1;// To store the index of the selected process
           int no=999;  //value to find the minimum burst time
           
           for(int i=0; i<user; i++){ // Find the process with the shortest burst time
               if (Process[i].arrival <= time && !finish[i]){
                   if (Process[i].burstTime<no){
                       no=Process[i].burstTime;
                       pointer = i;
                   }
                   
               else if (Process[i].burstTime==no){ 
                   if(Process[i].arrival<Process[pointer].arrival) 
                   pointer =i;
                }
       }
    }
   // if process found execute it 
            // advance time by the full burst duration of the process
     if (pointer != -1){ 
                    time =time + Process[pointer].burstTime;
            Process[pointer].turnAroundTime = time - Process[pointer].arrival;
            Process[pointer].waitTime = Process[pointer].turnAroundTime - Process[pointer].burstTime;
            finish[pointer] = true;
            com++;
        } else {
            time++;
        } 
       }
         cout << "\n results for SJF (Non-Preemptive):\n";
    AlgoTable(Process, user);
    
   }
        

   // priority - non preemptive
   
   void Priority(Algo Process[], int user) {
    int time = 0;
    int com = 0;
    bool finish[numOfProcess] = {false};

    while(com < user) {
        int pointer = -1;
        int prio = 999; 

        for(int i=0; i<user; i++) {
            if(Process[i].arrival <= time && !finish[i]) {
                if(Process[i].priority < prio) { // 
                    prio = Process[i].priority;
                    pointer = i;
                }
                else if(Process[i].priority == prio) {
                    if(Process[i].arrival < Process[pointer].arrival)
                    pointer = i;
                }
            }
        }

        if(pointer != -1) {
            time = time + Process[pointer].burstTime;
            Process[pointer].turnAroundTime = time - Process[pointer].arrival;
            Process[pointer].waitTime = Process[pointer].turnAroundTime - Process[pointer].burstTime;
            finish[pointer] = true;
            com++;
        } else {
            time++;
        }
    }
    cout << "\n results for Priority (Non-Preemptive):\n";
    AlgoTable(Process, user);
}

// 4. Priority (Preemptive)
void PriorityPreemptive(Algo Process[], int user) {
    int time = 0, com = 0;
    for(int i=0; i<user; i++) 
    Process[i].remainBurstTime = Process[i].burstTime; 

    while(com < user) { //to continue until all processes are executed
        int pointer = -1;
        int prio = 999;
  
  
  for(int i=0; i<user; i++) { //scan for the highest priority process available
            if(Process[i].arrival <= time && Process[i].remainBurstTime > 0) {
                if(Process[i].priority < prio) {
                   prio = Process[i].priority;  //// Found a better priority
                    pointer = i; // Update selected index
                }
                else if(Process[i].priority == prio) {
                    if(Process[i].arrival < Process[pointer].arrival) pointer = i;
                }
            }
        }

        if(pointer != -1) { //process found Since it is Non-Preemptive
            Process[pointer].remainBurstTime--;
            time++;
            if(Process[pointer].remainBurstTime == 0) {
                com++;
                Process[pointer].turnAroundTime = time - Process[pointer].arrival;
                Process[pointer].waitTime = Process[pointer].turnAroundTime - Process[pointer].burstTime;
            }
        } else {
            time++; 
        }
    }
    cout << "\n>>> Results for Priority (Preemptive):\n";
    AlgoTable(Process, user);
}

// 5. Round Robin
void roundRobin(Algo Process[], int user, int quantum) {
    int time = 0;
    int com = 0;
    for(int i=0; i<user; i++) // need a copy of burstTime to modify, because we need the original burstTime
    Process[i].remainBurstTime = Process[i].burstTime;

    while(com < user) { 
        bool worked = false; //to check if any process was executed in this cycle
        //Iterate through all processes
        for(int i=0; i<user; i++) {
            
            // to heck if process has arrived and is not yet finished
            if(Process[i].arrival <= time && Process[i].remainBurstTime > 0) {
                worked = true;
                if(Process[i].remainBurstTime > quantum) {
                    time =time + quantum;
                    Process[i].remainBurstTime -= quantum;
                } else {
                    time =time + Process[i].remainBurstTime;
                    Process[i].remainBurstTime = 0;
                    com++;
                    Process[i].turnAroundTime = time - Process[i].arrival;
                    Process[i].waitTime = Process[i].turnAroundTime - Process[i].burstTime;
                }
            } 
        }
        if(!worked) time++;
    }
    cout << "\n>> Round Robin (quantum=" << quantum << "):\n";
   AlgoTable(Process, user);
}

int main() {
    Algo Process[numOfProcess];
    int user;
int choice;

    
    ///////////////////////////////////////////
    cout << "\nChoose Algorithm:\n";
    cout << "1. FCFS\n";
    cout << "2. SJF (Shortest Job First)\n";
    cout << "3. Priority (Non-Preemptive)\n";
    cout << "4. Priority (Preemptive)\n";
    cout << "5. Round Robin\n";
    cout << "Selection: ";
    cin >> choice;

  
    cout << "Enter number of processes: ";
    cin >> user;

    // entering process data
    for(int i=0; i<user; i++) {
        Process[i].processNo = i + 1;
        
        cout << "\nProcess " << i+1 << " details:\n";
        
        
        if (choice == 3 || choice == 4) {
             
             cout << "Enter Arrival, Burst, Priority: ";
             cin >> Process[i].arrival >> Process[i].burstTime >> Process[i].priority;
        } else {
            
             cout << "Enter Arrival, Burst: ";
             cin >> Process[i].arrival >> Process[i].burstTime;
             Process[i].priority = 0; // default value
        }
    }

    
    cout << "\n calculating results \n";
    switch(choice) {
        case 1: FCFS(Process, user); 
        break;
        case 2: SJF(Process, user);
        break;
        case 3: Priority(Process, user); 
        break;
        case 4: PriorityPreemptive(Process, user); 
        break;
        case 5: 
            int quantum;
            cout << "enter time quantum: ";
            cin >> quantum;
            roundRobin(Process, user, quantum); 
            break;
        default: cout << "Invalid choice\n";
    }

    return 0;
}
