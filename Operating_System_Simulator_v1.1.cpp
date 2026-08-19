#include<iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <utility>
#include <chrono>
#include <thread>
using std::cout,std::cin,std::endl,std::string,std::vector,std::sort,std::pair,std::swap;
using namespace std::literals::chrono_literals;
int Simulation_UI(){
    cout<<"============================================================\n"
          "================ OPERATING SYSTEM SIMULATOR ================\n"
          "================ Process & Memory Management ===============\n"
          "============================================================\n\n"
          "1. Create Simulation\n"
          "0. Exit\n\n";
    int selection = 0;
    do {
        if (selection == 0) {
            cout<<"Enter your choice: ";
            cin>>selection;
        }
        else {
            cout<<"Invalid Input! Please Try Again.";
            cin>>selection;
        }
        cout<<endl;
    }while (selection != 1 && selection != 0);
    return selection;
}

struct Operating_System {

    // Process Manager
    struct Process_Manager {

        // Process Static Information
        struct Static_Information {
            int PID;
            int Arrival_Time;
            int Burst_Time;
            int Memory_Requirement;
        };

        // Process Control Block
        struct PCB {
            string state;
            int Completion_Time;
            int Waiting_Time;
            int Turnaround_Time;
            int Response_Time;
        };

        // Process Page Table
        struct Page_Table {
            struct Page_Table_Entries {
            int Page_Number;
            int Frame_Number;
            char Protection;
            int Accessed;
            int Valid;
            int Dirty;
        };
            int Number_of_Pages;
            int Page_Size;
            int Process_Size;
            Page_Table_Entries *page_table_entries = nullptr;
        };

        // Process Collective Information
        struct Individual_Process_Information {
            Static_Information Process_Stats;
            PCB Process_Control_Block;
            Page_Table Process_Page_Table;
        };

        // Number of Process
        int Number_of_Process;

        // Completion Time Array
        int *Completion_Time = nullptr;

        // Process Collective Information Array
        Individual_Process_Information *Process_Information = nullptr;

    //repeat function
        static bool repeat_check(const int &temp_value,const Individual_Process_Information *store,const int &length) {
            for (int i=0;i<length;i++) {
                if (temp_value == store[i].Process_Stats.PID) {
                    return true;
                }
            }
            return false;
        }
};

    // Memory Management
    struct Memory_Management {

        // Memory Management Unit
        struct MMU {
            int Process_Size;
            int Process_ID;
            int Logical_Address;
            int Frame_Number;
            pair<int,int>Address_Translation;
            int Physical_Address;
        };

        //Frame Manager
        struct Frame_Manager {
            int Frame_Number;
            string Frame_Status;
            pair<int,int>Occupancy;
            Frame_Manager() {
                Frame_Number = -1;
                Frame_Status = "Free";
                Occupancy.first = -1;
                Occupancy.second = -1;
            }
        };

        // Frame Information
        struct Frame_Information {
            int Total_Frames;
            int Free_Frames;
            int Allocated_Frames;
            Frame_Information() {
                Total_Frames = 0;
                Free_Frames = 0;
                Allocated_Frames = 0;
            }
        };

        // Physical Memory
        struct Physical_Memory {
            int RAM_Size;
            int Page_Size;
            int Frame_Size;
            int Number_of_Frames;
            int total_used_memory;
            Process_Manager Process;
            Frame_Information Frame_information;
            Frame_Manager *Frame = nullptr;
            bool *Frame_Check = nullptr;
            Physical_Memory() {
                total_used_memory = 0;

                // RAM Size
                RAM_Size = ram_size_validation();

                // Frame Size
                Frame_Size = frame_size_validation(RAM_Size);

                // Page Size
                Page_Size = Frame_Size;

                // Number of Frames
                Number_of_Frames = RAM_Size/Frame_Size;

                // Frame Information Total Frame
                Frame_information.Total_Frames = Number_of_Frames;

                // Frame Check resize
                Frame_Check = new bool[Number_of_Frames]();

                // Frame Resize
                Frame = new Frame_Manager[Number_of_Frames]();

                // Process Information
                int Number_of_Process = 0;
                do {
                    if (Number_of_Process == 0) {
                        cout<<"Enter Number of Process: ";
                    }
                    else {
                        cout<<"Invalid Input. Please Try Again:";
                    }
                    cin>>Number_of_Process;
                }while (Number_of_Process<1);
                Process.Number_of_Process = Number_of_Process;

                //Completion Time resize
                Process.Completion_Time = new int[Process.Number_of_Process];

                // Process_Information resize
                Process.Process_Information = new Process_Manager::Individual_Process_Information[Process.Number_of_Process];

                // Process Information Assign
                for (int i=0;i<Process.Number_of_Process;i++) {
                    int temp_value = rand()+1;
                    bool repeated = false;
                    do {
                        repeated = false;
                        temp_value = rand()+1;
                        repeated = Process.repeat_check(temp_value,Process.Process_Information,Process.Number_of_Process);
                    }while (repeated == true);

                    // PID
                    Process.Process_Information[i].Process_Stats.PID = temp_value;
                    std::this_thread::sleep_for(100ms);
                    cout<<"Process PID "<<Process.Process_Information[i].Process_Stats.PID<<" is created\n";

                    // Arrival Time
                    Process.Process_Information[i].Process_Stats.Arrival_Time = rand()%10;
                    // Burst Time
                    Process.Process_Information[i].Process_Stats.Burst_Time = (rand()%10)+1;
                    // Completion Time
                    Process.Completion_Time[i] = Process.Process_Information[i].Process_Stats.Burst_Time+Process.Process_Information[i].Process_Stats.Arrival_Time;
                    // Individual Memory Assign
                    bool check = false;
                    temp_value = 0;
                    do {
                        check = false;
                        temp_value = rand()%10;
                        if (temp_value%Page_Size != 0 || temp_value == 0) {
                            check = true;
                        }
                    }while (check == true);
                    Process.Process_Information[i].Process_Stats.Memory_Requirement = temp_value;
                    // Total Memory use Calculation
                    total_used_memory+=temp_value;
                }

                // Arrival Time sorting
                for (int i=0;i<Process.Number_of_Process;i++) {
                    for (int j=i;j<Process.Number_of_Process;j++) {
                        // Condition Check
                        if (Process.Process_Information[i].Process_Stats.Arrival_Time>Process.Process_Information[j].Process_Stats.Arrival_Time){
                            // swap Arrival Time
                            swap(Process.Process_Information[i].Process_Stats.Arrival_Time,Process.Process_Information[j].Process_Stats.Arrival_Time);
                            // swap PID
                            swap(Process.Process_Information[i].Process_Stats.PID,Process.Process_Information[j].Process_Stats.PID);
                            // swap Completion Time
                            swap(Process.Completion_Time[i],Process.Completion_Time[j]);
                            // swap Burst Time
                            swap(Process.Process_Information[i].Process_Stats.Burst_Time,Process.Process_Information[j].Process_Stats.Burst_Time);
                            // swap Memory Requirement
                            swap(Process.Process_Information[i].Process_Stats.Memory_Requirement,Process.Process_Information[j].Process_Stats.Memory_Requirement);
                        }
                    }
                }

                // Completion Time Calculation
                for (int i=1;i<Process.Number_of_Process;i++) {
                    if (Process.Process_Information[i-1].Process_Stats.Arrival_Time == Process.Process_Information[i].Process_Stats.Arrival_Time) {
                        Process.Completion_Time[i]+=Process.Completion_Time[i-1];
                    }
                    else if (Process.Completion_Time[i-1]>Process.Process_Information[i].Process_Stats.Arrival_Time) {
                        int remain_time = 0;
                        remain_time = Process.Completion_Time[i-1] - Process.Process_Information[i].Process_Stats.Arrival_Time;
                        Process.Completion_Time[i]+=remain_time;
                    }
                }


                // Process Control Block Information
                for (int i=0;i<Process.Number_of_Process;i++) {
                    // Process State
                    Process.Process_Information[i].Process_Control_Block.state = "NEW";
                    // Completion Time
                    Process.Process_Information[i].Process_Control_Block.Completion_Time = Process.Completion_Time[i];
                    // Turnaround Time
                    Process.Process_Information[i].Process_Control_Block.Turnaround_Time = Process.Completion_Time[i] - Process.Process_Information[i].Process_Stats.Arrival_Time;
                    // Waiting Time
                    Process.Process_Information[i].Process_Control_Block.Waiting_Time = Process.Process_Information[i].Process_Control_Block.Turnaround_Time - Process.Process_Information[i].Process_Stats.Burst_Time;
                    // Response Time
                    int first_CPU = Process.Process_Information[i].Process_Stats.Arrival_Time;
                    if (i != 0) {
                        first_CPU = Process.Completion_Time[i-1];
                    }
                    Process.Process_Information[i].Process_Control_Block.Response_Time = first_CPU;
                }

                // Frame Number Assign
                int frame_number_count = 0;

                // Process Page Table
                for (int i=0;i<Process.Number_of_Process;i++) {
                    // Process Size
                    Process.Process_Information[i].Process_Page_Table.Process_Size = Process.Process_Information[i].Process_Stats.Memory_Requirement;
                    // Page Size
                    Process.Process_Information[i].Process_Page_Table.Page_Size = Page_Size;
                    // Number of Pages
                    Process.Process_Information[i].Process_Page_Table.Number_of_Pages = Process.Process_Information[i].Process_Page_Table.Process_Size/Process.Process_Information[i].Process_Page_Table.Page_Size;
                    // Page Table Entries resize
                    Process.Process_Information[i].Process_Page_Table.page_table_entries = new Process_Manager::Page_Table::Page_Table_Entries[Process.Process_Information[i].Process_Page_Table.Number_of_Pages];

                    for (int j=0;j<Process.Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {
                        char Protection_Value[3] = {'R','W','X'};
                        // Protection Value
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Protection = Protection_Value[rand()%3];
                        // Page Number
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number = j;
                        // Accessed Bit
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed = 0;
                        // Valid Bit
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Valid = 1;
                        // Dirty Bit
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Dirty = 0;

                        // Validate Frame is free
                        int temp_value = rand()%Number_of_Frames;
                        bool check = false;
                        do {
                            check = false;
                            temp_value = rand()%Number_of_Frames;
                            if (Frame_Check[temp_value] == true) {
                                check = true;
                            }
                        }while (check == true);

                        // Change Frame Status in record
                        Frame_Check[temp_value] = true;
                        // Assign Frame Number
                        Frame[frame_number_count].Frame_Number = temp_value;
                        // Frame Status
                        Frame[frame_number_count].Frame_Status = "Occupied";
                        // Frame Owner
                        Frame[frame_number_count].Occupancy.first = Process.Process_Information[i].Process_Stats.PID;
                        // Page Number
                        Frame[frame_number_count].Occupancy.second = j;

                        // Frame Number record in Page Table
                        Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number = Frame[frame_number_count].Frame_Number;
                        // Frame Information Allocated Frames
                        Frame_information.Allocated_Frames++;

                        frame_number_count++;
                    }
                }

                // Frame Information Free Frames
                Frame_information.Free_Frames = Frame_information.Total_Frames - Frame_information.Allocated_Frames;


                int j = 0;
                for (int i=frame_number_count;i<Number_of_Frames;) {
                    if (Frame_Check[j] == false) {
                        Frame[i].Frame_Number = j;
                        i++;
                    }
                    j++;
                }

            }


            // RAM Size Validation
            static int ram_size_validation() {
                int RAM_Size = 0;
                do {
                    if (RAM_Size == 0) {
                        cout<<"Enter RAM Size: ";
                        cin>>RAM_Size;
                    }
                    else {
                        cout<<"Invalid Input. Please Try Again. ";
                        cin>>RAM_Size;
                    }
                    cout<<endl;
                }while (RAM_Size<1 || RAM_Size%2 != 0);
                return RAM_Size;
            }

            // Frame Size Validation
            static int frame_size_validation(int RAM_Size) {
                int Frame_Size = 0;
                do {
                    if (Frame_Size == 0) {
                        cout<<"Enter Frame size: ";
                        cin>>Frame_Size;
                    }
                    else {
                        cout<<"Invalid Input. Please Try Again. ";
                        cin>>Frame_Size;
                    }
                    cout<<endl;
                }while (Frame_Size<1 || RAM_Size%Frame_Size != 0);
                return Frame_Size;
            }
        };
    };

    // CPU Management
    struct CPU_Management {

        // Node Design
        struct Node {
            int *Process_ID;
            Node *next;
            Node(int *Process_ID) {
                this->Process_ID = Process_ID;
                next = nullptr;
            }
        };

        // Node Insertion
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

        // Node Deletion
        static void node_deletion(Node *&Head,Node *&Tail,Node *&curr) {
            if (Head == nullptr || curr == nullptr) {
                return;
            }
            Node *node = Head->next;
            if (node == nullptr) {
                Tail = nullptr;
            }
            delete Head;
            Head = node;
            curr = Head;
        }

        // CPU Information
        struct CPU {
            int Core_ID;
            string Status;
            string Running_Process;
            CPU() {
                Core_ID = 0;
                Running_Process = "NONE";
                Status = "IDLE";
            }
        };

        // Ready Queue
        struct Ready_Queue {
            Memory_Management::Physical_Memory Physical_Memory;
            int Number_of_Process;
            Node *Head = nullptr;
            Node *Tail = nullptr;
            Ready_Queue() {
                // Number of Process
                Number_of_Process = Physical_Memory.Process.Number_of_Process;
            }
        };

        // FCFS Scheduler
        struct  FCFS{
            CPU CPU;
            Ready_Queue Queue;
            string Next_Process;
            FCFS() {
                // Queue Head Check
                if (Queue.Head) {
                    Next_Process = std::to_string(*Queue.Head->Process_ID);
                }
                else {
                    Next_Process = "NONE";
                }
                // Queue Copy
                Node *curr = nullptr;
                // Display Initials
                display(curr,CPU,Next_Process,Queue,0);

                // Pointer to PID
                for (int i=0;i<Queue.Number_of_Process;i++) {
                    // PID insertion to Ready Queue
                    auto start = std::chrono::steady_clock::now();

                    while (true) {
                        auto current = std::chrono::steady_clock::now();

                        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current-start).count();

                        if (elapsed>=Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time) {
                            cout<<"PID "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<" enter Ready Queue.\n";
                            node_insertion(Queue.Head,Queue.Tail,&Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID);

                            // Queue Copy Assign
                            curr = Queue.Head;
                            // Queue Copy Traverse
                            while (curr) {
                                // CPU Running Process Assign
                                CPU.Running_Process = std::to_string(*(Queue.Head->Process_ID));
                                // CPU Status Change
                                CPU.Status = "BUSY";
                                // Queue Head next Check
                                if (Queue.Head->next) {
                                    Next_Process = std::to_string(*Queue.Head->next->Process_ID);
                                }
                                else {
                                    Next_Process = "NONE";
                                }
                                // Display Current
                                display(curr,CPU,Next_Process,Queue,i);
                                // Reassign Queue Copy
                                curr = Queue.Head;
                            }

                            cout<<"------------------------------------------------------------\n"
                            "PID: "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<"\n"
                            "------------------------------------------------------------\n"
                            "Process Information\n"
                            "\tPID                  : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<"\n"
                            "\tArrival Time         : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time<<"\n"
                            "\tBurst Time           : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time<<"\n"
                            "\tProcess Size         : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB\n"
                            "\tState                : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Control_Block.state<<"\n\n"
                            "PCB\n"
                            "\tCompletion Time      : "<<Queue.Physical_Memory.Process.Completion_Time[i]<<"\n"
                            "\tWaiting Time         : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Control_Block.Waiting_Time<<"\n"
                            "\tTurnaround Time      : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Control_Block.Turnaround_Time<<"\n"
                            "\tResponse Time        : "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Control_Block.Response_Time<<"\n\n"
                            "PAGE TABLE\n"
                            "\tPage    Frame    Valid    Dirty    Accessed    Protection\n"
                            "\t----------------------------------------------------------"<<endl;
                            for (int j=0;j<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {
                                cout<<"\t"<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number<<"       "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number<<"        "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Valid<<"      "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Dirty<<"       "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed<<"          "<<Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Protection<<endl;
                            }


                            break;
                        }
                        std::this_thread::sleep_for(100ms);
                    }
                }

                display(Queue.Physical_Memory);
                // display process information
                display(Queue.Physical_Memory.RAM_Size,Queue.Physical_Memory.Page_Size,Queue.Physical_Memory.Frame_Size,Queue.Physical_Memory.Number_of_Frames,Queue.Physical_Memory.Process);
            }

            ~FCFS() {
                for (int i=0;i<Queue.Number_of_Process;i++) {
                    delete []Queue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries;
                }
                delete []Queue.Physical_Memory.Process.Completion_Time;
                delete []Queue.Physical_Memory.Process.Process_Information;
                delete []Queue.Physical_Memory.Frame_Check;
                delete []Queue.Physical_Memory.Frame;

            }

            // Display function Process Information
            static void display(const int &RAM_size,const int &Page_size,const int &Frame_size,const int &Number_of_frames,const Process_Manager &process) {
                cout<<"============================================================\n"
                    "================ OPERATING SYSTEM SIMULATOR ================\n"
                    "=============== PROCESS & MEMORY MANAGEMENT ================\n"
                    "============================================================\n\n"
                    "SIMULATION CONFIGURATION\n"
                    "------------------------------------------------------------\n"
                    "CPU Cores            : 1 \n"
                    "Scheduler            : FCFS \n"
                    "RAM Size             : "<<RAM_size<<" KB \n"
                    "Page Size            : "<<Page_size<<" KB \n"
                    "Frame Size           : "<<Frame_size<<" KB \n"
                    "Number of Frames     : "<<Number_of_frames<<"\n"
                    "------------------------------------------------------------\n\n"
                    "PROCESS TABLE\n"
                    "------------------------------------------------------------\n"
                    "PID       AT       BT       Process Size       State\n"
                    "------------------------------------------------------------"<<endl;
                for (int i=0;i<process.Number_of_Process;i++) {
                    cout<<process.Process_Information[i].Process_Stats.PID<<"      "<<process.Process_Information[i].Process_Stats.Arrival_Time<<"        "<<process.Process_Information[i].Process_Stats.Burst_Time<<"     "<<process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB               "<<process.Process_Information[i].Process_Control_Block.state<<endl;
                }
                cout<<"------------------------------------------------------------\n"<<endl;

                cout<<"PROCESS MANAGEMENT"<<endl;
                for (int i=0;i<process.Number_of_Process;i++) {
                    cout<<"------------------------------------------------------------\n"
                            "PID: "<<process.Process_Information[i].Process_Stats.PID<<"\n"
                            "------------------------------------------------------------\n"
                            "Process Information\n"
                            "\tPID                  : "<<process.Process_Information[i].Process_Stats.PID<<"\n"
                            "\tArrival Time         : "<<process.Process_Information[i].Process_Stats.Arrival_Time<<"\n"
                            "\tBurst Time           : "<<process.Process_Information[i].Process_Stats.Burst_Time<<"\n"
                            "\tProcess Size         : "<<process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB\n"
                            "\tState                : "<<process.Process_Information[i].Process_Control_Block.state<<"\n\n"
                            "PCB\n"
                            "\tCompletion Time      : "<<process.Completion_Time[i]<<"\n"
                            "\tWaiting Time         : "<<process.Process_Information[i].Process_Control_Block.Waiting_Time<<"\n"
                            "\tTurnaround Time      : "<<process.Process_Information[i].Process_Control_Block.Turnaround_Time<<"\n"
                            "\tResponse Time        : "<<process.Process_Information[i].Process_Control_Block.Response_Time<<"\n\n"
                            "PAGE TABLE\n"
                            "\tPage    Frame    Valid    Dirty    Accessed    Protection\n"
                            "\t----------------------------------------------------------"<<endl;
                    for (int j=0;j<process.Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {
                        cout<<"\t"<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number<<"       "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number<<"        "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Valid<<"      "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Dirty<<"       "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed<<"          "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Protection<<endl;
                    }
                    cout<<endl;
                }

            }

            // Display Function
            void display(Node *&Curr,const struct CPU &cpu,const string &Next_process,const Ready_Queue &Q,int i) {
                // For Initial State
                if (Curr != nullptr) {
                    cout<<"CURRENT ACTION\n"
                        "------------------------------------------------------------\n"
                        "FCFS selected PID "<<*Curr->Process_ID<<".\n"
                        "PID "<<*Curr->Process_ID<<" dispatched to CPU Core 0.\n"
                        "\n"
                        "PID "<<*Curr->Process_ID<<" is now RUNNING.\n"
                        "------------------------------------------------------------\n"<<endl;
                    auto start = std::chrono::steady_clock::now();
                    cout<<"Process PID "<<*Curr->Process_ID<<" is executing CPU.\n";
                    while (true) {
                        auto current = std::chrono::steady_clock::now();

                        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current-start).count();
                        if (elapsed >= Queue.Physical_Memory.Process.Completion_Time[i]) {
                            break;
                        }
                        std::this_thread::sleep_for(100ms);
                    }
                }
                // Node Deletion Based on Curr
                if (Curr) {
                    // Node Deletion Function
                    node_deletion(Queue.Head,Queue.Tail,Curr);
                }
                // Output
                cout<<"============================================================\n"
                    "====================== CPU MANAGEMENT ======================\n"
                    "============================================================\n\n"
                    "CPU\n"
                    "------------------------------------------------------------\n"
                    "Core ID              : "<<cpu.Core_ID<<"\n"
                    "Status               : "<<cpu.Status<<"\n"
                    "Running Process      : "<<cpu.Running_Process<<"\n\n"
                    "READY QUEUE\n"
                    "------------------------------------------------------------\n"<<endl;
                cout<<"Front -> [";
                // Queue all Process Output
                if (Q.Head) {
                    Node *travrse = Q.Head;
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
                }
                else {
                    cout<<"Empty] ";
                }
                cout<<"<- Back \n\n"
                    "SCHEDULER\n"
                    "------------------------------------------------------------\n"
                    "Algorithm            : FCFS \n"
                    "Next Process         : "<<Next_process<<"\n"
                    "============================================================\n"<<endl;
            }

            static void display(const Memory_Management::Physical_Memory &P1) {
                cout<<"============================================================\n"
                    "==================== PHYSICAL MEMORY ======================\n"
                    "============================================================\n\n"
                    "MEMORY CONFIGURATION\n"
                    "------------------------------------------------------------\n"
                    "RAM Size             : "<<P1.RAM_Size<<" KB\n"
                    "Page Size            : "<<P1.Page_Size<<" KB\n"
                    "Frame Size           : "<<P1.Frame_Size<<" KB\n"
                    "Number of Frames     : "<<P1.Number_of_Frames<<"\n\n"
                    "FRAME TABLE\n"
                    "------------------------------------------------------------\n"
                    "Frame No.       Status          Occupancy\n"
                    "------------------------------------------------------------\n";
                for (int i=0;i<P1.Number_of_Frames;i++) {
                    cout<<P1.Frame[i].Frame_Number<<"                "<<P1.Frame[i].Frame_Status<<"            ";
                    if (P1.Frame[i].Occupancy.first == -1) {
                        cout<<"NONE"<<endl;
                    }
                    else {
                        cout<<"PID "<<P1.Frame[i].Occupancy.first<<" - "<<"Page "<<P1.Frame[i].Occupancy.second<<endl;
                    }
                }
                cout<<"------------------------------------------------------------\n"
                    "Memory Usage       : "<<P1.total_used_memory<<" KB / "<<P1.RAM_Size<<" KB \n"
                    "Free Memory        : "<<P1.RAM_Size-P1.total_used_memory<<" KB \n"
                    "Occupied Frames    : "<<P1.Frame_information.Allocated_Frames<<" \n"
                    "Free Frames        : "<<P1.Frame_information.Free_Frames<<" \n"
                    "============================================================\n"<<endl;
            }
        };

        FCFS F1;
    };

    CPU_Management C1;
};

int main() {
    // This Version is Still Incomplete For MMU. I am working on MMU
    // In Version 1.1, I will Handle Memory Free
    // In Version 2.0, I will Replace Scheduler FCFS with Round-Robin
    srand(time(nullptr));
    while (true) {
        if (Simulation_UI()) {
            Operating_System OS;
        }
        else {
            cout<<"You decided to Exit the Simulator.\n";
            break;
        }
    }
    return 0;
}
