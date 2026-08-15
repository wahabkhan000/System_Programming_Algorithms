#include <iostream>
#include <vector>
using std::cout,std::cin,std::endl,std::string,std::vector;
class CPU_Management {
    struct Node {
    int *Process_ID;
    Node *next;
    Node(int *Process_ID) {
        this->Process_ID = Process_ID;
        next = nullptr;
    }
};
    static void node_insertion(Node *&Head,Node *&Tail,int *process_ID) {
    if (Head == nullptr) {
        Head = new Node(process_ID);
        Tail = Head;
    }
    else {
        Tail->next = new Node(process_ID);
        Tail =Tail->next;
    }
}
    static void node_deletion(Node *&Head,Node *&Tail,Node *&curr) {
    Node *node = Head->next;
    if (node == nullptr) {
        Tail = nullptr;
    }
    delete Head;
    Head = node;
    curr = Head;
}
    struct CPU {
        int Core_ID;
        string status;
        string Running_Process;
        CPU() {
            Core_ID = 0;
            status = "IDLE";
            Running_Process = "NONE";
        }
        CPU(const string &Process_ID) {
            Core_ID = 0;
            status = "BUSY";
            Running_Process = Process_ID;
        }
    };
    struct Ready_Queue {
        Node *Head = nullptr;
        Node *Tail = nullptr;
        vector<int>Arrival_Time;
        vector<int>PID;
        int Number_of_Process;
        Ready_Queue() {
        Number_of_Process = 0;
        do {
            if (Number_of_Process == 0) {
                cout<<"Enter Number_of_Process: "<<endl;
            }
            else {
                cout<<"Invalid Input! Try Again"<<endl;
            }
            cin>>Number_of_Process;
        }while (Number_of_Process<1);

        //PID
        for (int i=0;i<Number_of_Process;i++) {
            int temp_value = rand()+1;
            bool repeated = false;
            do {
                repeated = false;
                temp_value = rand()+1;
                repeated = repeat_check(temp_value,PID);
            }while (repeated == true);
            PID.push_back(temp_value);
        }

        //Arrival_Time
        for (int i=0;i<Number_of_Process;i++) {
            int temp_value = rand()%Number_of_Process+1;
            bool repeated = false;
            do {
                repeated = false;
                temp_value = rand()%Number_of_Process+1;
                repeated = repeat_check(temp_value,Arrival_Time);
            }while (repeated == true);
            Arrival_Time.push_back(temp_value);
        }

        //getting min
        vector<bool>used(Number_of_Process,false);
        for (int i=0;i<Number_of_Process;i++) {

            int min_value = INT_MAX;
            int index = -1;
            for (int j=0;j<Number_of_Process;j++) {
                if (used[j] == false) {
                    if (min_value>Arrival_Time[j]) {
                        min_value = Arrival_Time[j];
                        index = j;
                    }
                }
            }

            if (index != -1) {
                used[index] = true;
                cout<<"Process "<<PID[index]<<" enter Ready_Queue."<<endl;
                node_insertion(Head,Tail,&PID[index]);
            }
        }
    }
        bool repeat_check(int temp_value,const vector<int>&store) {
            for (int x : store) {
                if (x == temp_value) {
                    return true;
                }
            }
            return false;
        }
    };
    struct FCFS {
        Ready_Queue Queue;
        string Next_Process = "NONE";
        FCFS() {
            CPU cpu;
            display(cpu,Queue);
            Node *curr = Queue.Head;
            while (curr) {
                CPU CPU(std::to_string(*curr->Process_ID));
                display(curr,CPU,Next_Process,Queue);
                curr = Queue.Head;
            }
        }
        void display(CPU &cpu,Ready_Queue Q1) {
            cout<<"============================================================\n"
                "====================== CPU MANAGEMENT ======================\n"
                "============================================================\n"
                "CPU\n"
                "------------------------------------------------------------\n"
                "Core ID              : "<<cpu.Core_ID<<"\n"
                "Status               : "<<cpu.status<<"\n"
                "Running Process      : "<<cpu.Running_Process<<"\n"
                "READY QUEUE\n"
                "------------------------------------------------------------"<<endl;
            Node *curr = Q1.Head;
            cout<<"Front -> [";
            while (curr) {
                cout<<*curr->Process_ID;
                if (curr->next) {
                    cout<<"] -> [";
                }
                else {
                    cout<<"] ";
                }
                curr = curr->next;
            }
            cout<<" <- Back \n"
                "SCHEDULER\n"
                "------------------------------------------------------------\n"
                "Algorithm            : FCFS \n"
                "Next Process         : "<<*(Q1.Head->Process_ID)<<"\n"
                "============================================================"<<endl;
        }
        void display(Node *&curr, CPU &cpu,string &Next_Process,Ready_Queue &Q1) {
            cout<<"CURRENT ACTION\n"
                    "------------------------------------------------------------\n"
                    "FCFS selected PID "<<*curr->Process_ID<<".\n"
                    "PID "<<*curr->Process_ID<<" dispatched to CPU Core 0."<<endl;
            cout<<endl;
            node_deletion(Queue.Head,Queue.Tail,curr);
            cout<<"============================================================\n"
                "====================== CPU MANAGEMENT ======================\n"
                "============================================================\n"
                "CPU\n"
                "------------------------------------------------------------\n"
                "Core ID              : "<<cpu.Core_ID<<"\n"
                "Status               : "<<cpu.status<<"\n"
                "Running Process      : "<<cpu.Running_Process<<"\n"
                "READY QUEUE\n"
                "------------------------------------------------------------"<<endl;
            cout<<"Front -> [";
            if (Q1.Head) {
                Node *travrse = Q1.Head;
                while (travrse) {
                    cout<<*travrse->Process_ID;
                    if (travrse->next) {
                        cout<<"] -> [";
                    }
                    else {
                        cout<<"] ";
                    }
                    travrse = travrse->next;
                }
                Next_Process = std::to_string(*(Q1.Head->Process_ID));
            }
            else {
                cout<<"Empty] ";
                Next_Process = "NONE";
            }
            cout<<"<- Back \n"
                "SCHEDULER\n"
                "------------------------------------------------------------\n"
                "Algorithm            : FCFS \n"
                "Next Process         : "<<Next_Process<<"\n"
                "============================================================"<<endl;
        }
    };
    FCFS F;
};
int main() {
    srand(time(NULL));
    CPU_Management C1;
}
