#include <iostream>
#include <string>
#include <utility>
#include <ctime>

// Simulation Configuration
int Simulation_UI(){

    // Choice Section
    std::cout<<"============================================================\n"
    "================ OPERATING SYSTEM SIMULATOR ================\n"
    "================ Process & Memory Management ===============\n"
    "============================================================\n\n"
    "1. Create Simulation\n"
    "0. Exit\n\n";

    int selection = 0;
    do {
        if (selection == 0) {
            std::cout<<"Enter your choice: ";
            std::cin>>selection;
        }
        else {
            std::cout<<"Invalid Input! Please Try Again.";
            std::cin>>selection;
        }
        std::cout<<"\n";
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
            int Remaining_Time;
            Static_Information() {
                PID = -1;
                Arrival_Time = -1;
                Burst_Time = -1;
                Memory_Requirement = -1;
                Remaining_Time = -1;
            }
        };

        // Process Control Block
        struct Process_Control_Block {
            std::string state;
            int Completion_Time;
            int Waiting_Time;
            int Turnaround_Time;
            int Response_Time;
            Process_Control_Block() {
                state = "-1";
                Completion_Time = -1;
                Waiting_Time = -1;
                Turnaround_Time = -1;
                Response_Time = -1;
            }
        };

        // Process Page Table
        struct Page_Table {

            // Page Table Entries
            struct Page_Table_Entries {
                int Page_Number;
                int Frame_Number;
                char Protection;
                int Accessed;
                int Valid;
                int Dirty;
                Page_Table_Entries() {
                    Page_Number = -1;
                    Frame_Number = -1;
                    Protection = -1;
                    Accessed = -1;
                    Valid = -1;
                    Dirty = -1;
                }
            };
            int Number_of_Pages;
            int Page_Size;
            int Process_Size;
            Page_Table_Entries *page_table_entries = nullptr;
            Page_Table() {
                Number_of_Pages = -1;
                Page_Size = -1;
                Process_Size = -1;
            }
        };

        // Process Collective Information
        struct Individual_Process_Information {
            Static_Information Process_Stats;
            Process_Control_Block PCB;
            Page_Table Process_Page_Table;
        };

        // Number of Process
        int Number_of_Process = -1;

        // Completion Time
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

        // Memory_Management_Unit
        struct Memory_Management_Unit {
            int Process_Size;
            int Page_Size;
            int Process_ID;
            int Logical_Address;
            int Frame_Number;
            std::pair<int,int>Address_Translation;
            int Physical_Address;
            int Demand_Bit;
            Memory_Management_Unit() {
                Process_Size = -1;
                Page_Size = -1;
                Process_ID = -1;
                Logical_Address = -1;
                Frame_Number = -1;
                Address_Translation = {-1,-1};
                Physical_Address = -1;
                Demand_Bit = -1;
            }
        };

        // Frame_Manager
        struct Frame_Manager {
            int Frame_Number;
            std::string Frame_Status;
            std::pair<int,int>Occupancy;
            Frame_Manager() {
                Frame_Number = -1;
                Frame_Status = "Free";
                Occupancy = {-1,-1};
            }
        };

        // Frame_Information
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

        // Physical_Memory
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
                RAM_Size = 0;
                Page_Size = 0;
                Frame_Size = 0;
                Number_of_Frames = 0;
                total_used_memory = 0;
            }
        };
    };

    // CPU_Management
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

        // CPU Information
        struct CPU {
            int Core_ID;
            std::string Status;
            std::string Running_Process;
            CPU() {
                Core_ID = 0;
                Running_Process = "NONE";
                Status = "IDLE";
            }
        };

        // Ready_Queue
        struct Ready_Queue {
            Memory_Management::Physical_Memory Physical_Memory;
            Node *Head = nullptr;
            Node *Tail = nullptr;
        };

        // Round_Robin
        struct Round_Robin {
            CPU CPU;
            std::string Next_Process;
            int time_quantum = 1;
            std::string Ghant_Chart;
        };

        // First_Come_First_Serve
        struct FCFS {
            CPU CPU;
            std::string Next_Process;
        };

        Round_Robin RoundRobin;
        FCFS FCFS;
        Ready_Queue ReadyQueue;
    };

    // CPU-Management_Object
    CPU_Management C;
    Operating_System() {

        // Argument for selecting Algorithm
        int argument = 0;
        do {
            if (argument == 0) {
                std::cout<<"============================================================\n"
                "=================== CPU SCHEDULER ==========================\n"
                "============================================================\n"
                "Available Scheduling Algorithms\n"
                "------------------------------------------------------------\n"
                "1. Round Robin\n"
                "0. First Come First Serve (FCFS)\n"
                "------------------------------------------------------------\n\n"
                "Enter Your Choice: \n\n";
            }
            else {
                std::cout<<"Invalid Input! Please Try Again:\n";
            }
            std::cin>>argument;
        }while (argument<0 || argument>1);

        if (argument == 1) {
            std::cout<<"================= You Selected Round Robin =================\n\n";
        }
        else {
            std::cout<<"======== You Selected First Come First Serve (FCFS) ========\n\n";
        }

        //RAM_Size
        C.ReadyQueue.Physical_Memory.RAM_Size = ram_size_validation();

        //Frame_Size
        C.ReadyQueue.Physical_Memory.Frame_Size = frame_size_validation(C.ReadyQueue.Physical_Memory.RAM_Size);

        // Number_of_Process
        C.ReadyQueue.Physical_Memory.Process.Number_of_Process = process_number_validation();

        // Page_Size
        C.ReadyQueue.Physical_Memory.Page_Size = C.ReadyQueue.Physical_Memory.Frame_Size;

        // Number of Frame
        C.ReadyQueue.Physical_Memory.Number_of_Frames = C.ReadyQueue.Physical_Memory.RAM_Size/C.ReadyQueue.Physical_Memory.Frame_Size;

        // Total_Frame
        C.ReadyQueue.Physical_Memory.Frame_information.Total_Frames = C.ReadyQueue.Physical_Memory.Number_of_Frames;

        // Frame_Check_Resize
        C.ReadyQueue.Physical_Memory.Frame_Check = new bool[C.ReadyQueue.Physical_Memory.Number_of_Frames]();

        // Frame Resize
        C.ReadyQueue.Physical_Memory.Frame = new Memory_Management::Frame_Manager[C.ReadyQueue.Physical_Memory.Number_of_Frames]();

        //Completion Time resize
        C.ReadyQueue.Physical_Memory.Process.Completion_Time = new int[C.ReadyQueue.Physical_Memory.Process.Number_of_Process];

        // Process_Information resize
        C.ReadyQueue.Physical_Memory.Process.Process_Information = new Process_Manager::Individual_Process_Information[C.ReadyQueue.Physical_Memory.Process.Number_of_Process];

        // Process Information Assign
        for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {
            int temp_value = rand()+1;
            bool repeated = false;
            do {
                repeated = false;
                temp_value = rand()+1;
                repeated = C.ReadyQueue.Physical_Memory.Process.repeat_check(temp_value,C.ReadyQueue.Physical_Memory.Process.Process_Information,C.ReadyQueue.Physical_Memory.Process.Number_of_Process);
            }while (repeated == true);

            // PID
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID = temp_value;

            // Process Creation Output
            std::cout<<"Process PID "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<" is created\n";

            // Arrival Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time = rand()%10;

            // Burst Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time = (rand()%10)+1;

            // Remaining_Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Remaining_Time = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time;

            // Completion Time
            C.ReadyQueue.Physical_Memory.Process.Completion_Time[i] = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time+C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time;

            // Individual Memory Assign
            bool check = false;
            temp_value = 0;
            do {
                check = false;
                temp_value = rand()%10;
                if (temp_value%C.ReadyQueue.Physical_Memory.Page_Size != 0 || temp_value == 0) {
                    check = true;
                }
            }while (check == true);
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Memory_Requirement = temp_value;

            // Total Memory use Calculation
            C.ReadyQueue.Physical_Memory.total_used_memory+=temp_value;
        }

        // Arrival Time sorting
        for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {
            for (int j=i;j<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;j++) {
                // Condition Check
                if (C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time>C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.Arrival_Time){

                    // swap Arrival Time
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time,C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.Arrival_Time);

                    // swap PID
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID,C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.PID);

                    // swap Completion Time
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Completion_Time[i],C.ReadyQueue.Physical_Memory.Process.Completion_Time[j]);

                    // swap Remaining Burst Time
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Remaining_Time,C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.Remaining_Time);

                    // swap Burst Time
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time,C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.Burst_Time);

                    // swap Memory Requirement
                    std::swap(C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Memory_Requirement,C.ReadyQueue.Physical_Memory.Process.Process_Information[j].Process_Stats.Memory_Requirement);
                }
            }
        }

        // Completion Time Calculation
        for (int i=1;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {
            if (C.ReadyQueue.Physical_Memory.Process.Process_Information[i-1].Process_Stats.Arrival_Time == C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time) {
                C.ReadyQueue.Physical_Memory.Process.Completion_Time[i]+=C.ReadyQueue.Physical_Memory.Process.Completion_Time[i-1];
            }
            else if (C.ReadyQueue.Physical_Memory.Process.Completion_Time[i-1]>C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time) {
                int remain_time = 0;
                remain_time = C.ReadyQueue.Physical_Memory.Process.Completion_Time[i-1] - C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time;
                C.ReadyQueue.Physical_Memory.Process.Completion_Time[i]+=remain_time;
            }
        }


        // Process Control Block Information
        for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {

            // Process State
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.state = "NEW";

            // Completion Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Completion_Time = C.ReadyQueue.Physical_Memory.Process.Completion_Time[i];

            // Turnaround Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Turnaround_Time = C.ReadyQueue.Physical_Memory.Process.Completion_Time[i] - C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time;

            // Waiting Time
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Waiting_Time = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Turnaround_Time - C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time;

            // Response Time
            int first_CPU = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time;

            if (i != 0) {
                first_CPU = C.ReadyQueue.Physical_Memory.Process.Completion_Time[i-1];
            }
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Response_Time = first_CPU;
        }

        // Frame Number Assign
        int frame_number_count = 0;

        // Process Page Table
        for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {

            // Process Size
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Process_Size = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Memory_Requirement;

            // Page Size
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Page_Size = C.ReadyQueue.Physical_Memory.Page_Size;

            // Number of Pages
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Number_of_Pages = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Process_Size/C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Page_Size;

            // Page Table Entries resize
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries = new Process_Manager::Page_Table::Page_Table_Entries[C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Number_of_Pages];

            for (int j=0;j<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {

                // For Random Permission Assignment
                char Protection_Value[3] = {'R','W','X'};

                // Protection Value
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Protection = Protection_Value[rand()%3];

                // Page Number
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number = j;

                // Accessed Bit
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed = 0;

                // Valid Bit
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Valid = 1;

                // Dirty Bit
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Dirty = 0;

                // Validate Frame is free
                int temp_value = rand()%C.ReadyQueue.Physical_Memory.Number_of_Frames;
                bool check = false;
                do {
                    check = false;
                    temp_value = rand()%C.ReadyQueue.Physical_Memory.Number_of_Frames;
                    if (C.ReadyQueue.Physical_Memory.Frame_Check[temp_value] == true) {
                        check = true;
                    }
                }while (check == true);

                // Change Frame Status in record
                C.ReadyQueue.Physical_Memory.Frame_Check[temp_value] = true;

                // Assign Frame Number
                C.ReadyQueue.Physical_Memory.Frame[frame_number_count].Frame_Number = temp_value;

                // Frame Status
                C.ReadyQueue.Physical_Memory.Frame[frame_number_count].Frame_Status = "Occupied";

                // Frame Owner
                C.ReadyQueue.Physical_Memory.Frame[frame_number_count].Occupancy.first = C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID;

                // Page Number
                C.ReadyQueue.Physical_Memory.Frame[frame_number_count].Occupancy.second = j;

                // Frame Number record in Page Table
                C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number = C.ReadyQueue.Physical_Memory.Frame[frame_number_count].Frame_Number;

                // Frame Information Allocated Frames
                C.ReadyQueue.Physical_Memory.Frame_information.Allocated_Frames++;

                // Frame Count
                frame_number_count++;
            }
        }

        // Frame Information Free Frames
        C.ReadyQueue.Physical_Memory.Frame_information.Free_Frames = C.ReadyQueue.Physical_Memory.Frame_information.Total_Frames - C.ReadyQueue.Physical_Memory.Frame_information.Allocated_Frames;

        int Frame_Index = 0;
        for (int i=frame_number_count;i<C.ReadyQueue.Physical_Memory.Number_of_Frames;) {
            if (C.ReadyQueue.Physical_Memory.Frame_Check[Frame_Index] == false) {
                C.ReadyQueue.Physical_Memory.Frame[i].Frame_Number = Frame_Index;
                i++;
            }
            Frame_Index++;
        }

        // Fill Ready Queue with first process
        std::cout<<"*************************************************************\n";
        std::cout<<"Process PID "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[0].Process_Stats.PID<<" enter ready Queue\n";
        std::cout<<"*************************************************************\n\n";

        // first node insertion
        node_insertion(C.ReadyQueue.Head,C.ReadyQueue.Tail,&C.ReadyQueue.Physical_Memory.Process.Process_Information[0].Process_Stats.PID);

        if (argument == 1) {

            // process count in Ready Queue
            int proces_count = 1;

            // Current Time start from 0
            int current_time = 0;

            while (C.ReadyQueue.Head != nullptr) {

                // Running process index
                int current_process_index = -1;

                // Check the Current Running Process index
                for (int m = 0; m < C.ReadyQueue.Physical_Memory.Process.Number_of_Process; m++) {
                    if (*C.ReadyQueue.Head->Process_ID == C.ReadyQueue.Physical_Memory.Process.Process_Information[m].Process_Stats.PID) {
                        current_process_index = m;
                        break;
                    }
                }

                // if not in our memory then skip
                if (current_process_index == -1) {
                    node_deletion(C.ReadyQueue.Head, C.ReadyQueue.Tail);
                    continue;
                }

                // Current Time increase
                current_time += C.RoundRobin.time_quantum;

                // Remaining Time Decrease
                C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].Process_Stats.Remaining_Time -= C.RoundRobin.time_quantum;

                std::cout<<"*************************************************************\n";
                std::cout<<"Round-Robin select Process PID "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].Process_Stats.PID<<"\n";
                std::cout<<"*************************************************************\n\n";

                // Running Process Assignment to CPU
                C.RoundRobin.CPU.Running_Process = std::to_string(C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].Process_Stats.PID);

                // CPU State Change
                C.RoundRobin.CPU.Status = "BUSY";

                // Ghant-Chart
                if (!C.RoundRobin.Ghant_Chart.empty()) {
                    C.RoundRobin.Ghant_Chart+=" -> ";
                }

                // Ghant-Chart update
                C.RoundRobin.Ghant_Chart += std::to_string(C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].Process_Stats.PID);

                // How many Process arrives at time
                while (proces_count < C.ReadyQueue.Physical_Memory.Process.Number_of_Process && C.ReadyQueue.Physical_Memory.Process.Process_Information[proces_count].Process_Stats.Arrival_Time <= current_time) {
                    std::cout<<"*************************************************************\n";
                    std::cout<<"Process PID "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[proces_count].Process_Stats.PID<<" enter ready Queue\n";
                    std::cout<<"*************************************************************\n\n";
                    node_insertion(C.ReadyQueue.Head, C.ReadyQueue.Tail, &C.ReadyQueue.Physical_Memory.Process.Process_Information[proces_count++].Process_Stats.PID);
                }

                // Queue Head next Check
                if (C.ReadyQueue.Head->next) {
                    C.RoundRobin.Next_Process = std::to_string(*C.ReadyQueue.Head->next->Process_ID);
                }
                else {
                    C.RoundRobin.Next_Process = "NONE";
                }

                // Display Output
                display(C.RoundRobin.CPU,C.ReadyQueue,C.RoundRobin.time_quantum,C.RoundRobin.Next_Process,C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].Process_Stats.Remaining_Time,C.ReadyQueue.Physical_Memory.Process.Process_Information[current_process_index].PCB.state);

                // if future process enter ready queue
                if (C.ReadyQueue.Head == nullptr && proces_count<C.ReadyQueue.Physical_Memory.Process.Number_of_Process) {
                    // Increase Current time
                    current_time = C.ReadyQueue.Physical_Memory.Process.Process_Information[proces_count].Process_Stats.Arrival_Time;
                    // Add that process at last of Queue
                    node_insertion(C.ReadyQueue.Head,C.ReadyQueue.Tail,&C.ReadyQueue.Physical_Memory.Process.Process_Information[proces_count++].Process_Stats.PID);
                }
            }

            // display process information
            display(C.ReadyQueue.Physical_Memory.RAM_Size,C.ReadyQueue.Physical_Memory.Page_Size,C.ReadyQueue.Physical_Memory.Frame_Size,C.ReadyQueue.Physical_Memory.Number_of_Frames,C.ReadyQueue.Physical_Memory.Process);

            // Display Physical Memory
            display(C.ReadyQueue.Physical_Memory);

            // Display Ghant-Chart
            std::cout<<"*************************************************************\n";
            std::cout<<"Ghant-Chart: "<<C.RoundRobin.Ghant_Chart<<"\n";
            std::cout<<"*************************************************************\n\n";
        }
        else {

            // Queue Head Check
            if (C.ReadyQueue.Head) {
                C.FCFS.Next_Process = std::to_string(*C.ReadyQueue.Head->Process_ID);
            }
            else {
                C.FCFS.Next_Process = "NONE";
            }

            // Queue Copy
            CPU_Management::Node *curr = nullptr;

            // Display Initials
            display(curr,C.FCFS.CPU,C.FCFS.Next_Process,C.ReadyQueue,0);

            // Pointer to PID
            for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {

                // PID insertion to Ready Queue
                std::cout<<"PID "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<" enter Ready Queue.\n";

                // node insertion in Ready Queue
                node_insertion(C.ReadyQueue.Head,C.ReadyQueue.Tail,&C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID);

                // Queue Copy Assign
                curr = C.ReadyQueue.Head;

                // Queue Copy Traverse
                while (curr) {

                    // CPU Running Process Assign
                    C.FCFS.CPU.Running_Process = std::to_string(*(C.ReadyQueue.Head->Process_ID));

                    // CPU Status Change
                    C.FCFS.CPU.Status = "BUSY";

                    // Queue Head next Check
                    if (C.ReadyQueue.Head->next) {
                        C.FCFS.Next_Process = std::to_string(*C.ReadyQueue.Head->next->Process_ID);
                    }
                    else {
                        C.FCFS.Next_Process = "NONE";
                    }

                    // Display Current
                    display(curr,C.FCFS.CPU,C.FCFS.Next_Process,C.ReadyQueue,i);

                    // Reassign Queue Copy
                    curr = C.ReadyQueue.Head;
                }

                std::cout<<"------------------------------------------------------------\n"
                "PID: "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<"\n"
                "------------------------------------------------------------\n"
                "Process Information\n"
                "\tPID                  : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.PID<<"\n"
                "\tArrival Time         : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Arrival_Time<<"\n"
                "\tBurst Time           : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time<<"\n"
                "\tProcess Size         : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB\n"
                "\tState                : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.state<<"\n\n"
                "PCB\n"
                "\tCompletion Time      : "<<C.ReadyQueue.Physical_Memory.Process.Completion_Time[i]<<"\n"
                "\tWaiting Time         : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Waiting_Time<<"\n"
                "\tTurnaround Time      : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Turnaround_Time<<"\n"
                "\tResponse Time        : "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.Response_Time<<"\n\n"
                "PAGE TABLE\n"
                "\tPage    Frame    Valid    Dirty    Accessed    Protection\n"
                "\t----------------------------------------------------------\n";
                for (int n=0;n<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.Number_of_Pages;n++) {
                    std::cout<<"\t"<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Page_Number<<"       "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Frame_Number<<"        "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Valid<<"      "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Dirty<<"       "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Accessed<<"          "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries[n].Protection<<"\n";
                }
            }

            // Display Physical Memory Function
            display(C.ReadyQueue.Physical_Memory);

            // display process information
            display(C.ReadyQueue.Physical_Memory.RAM_Size,C.ReadyQueue.Physical_Memory.Page_Size,C.ReadyQueue.Physical_Memory.Frame_Size,C.ReadyQueue.Physical_Memory.Number_of_Frames,C.ReadyQueue.Physical_Memory.Process);
        }
    }

    // FCFS Display initials Function
    void display(CPU_Management::Node *&Curr,const CPU_Management::CPU &cpu,const std::string &Next_process,const CPU_Management::Ready_Queue &Q,int i) {
        
        // For Initial State
        if (Curr != nullptr) {
            std::cout<<"CURRENT ACTION\n"
            "------------------------------------------------------------\n"
            "FCFS selected PID "<<*Curr->Process_ID<<".\n"
            "PID "<<*Curr->Process_ID<<" dispatched to CPU Core 0.\n\n"
            "PID "<<*Curr->Process_ID<<" is now RUNNING.\n"
            "------------------------------------------------------------\n\n";
            // Executing Process Output
            std::cout<<"Process PID "<<*Curr->Process_ID<<" is executing CPU for "<<C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Stats.Burst_Time<<"sec\n";

        }
        
        // Node Deletion Based on Curr
        if (Curr) {
            // Node Deletion Function
            C.ReadyQueue.Physical_Memory.Process.Process_Information[i].PCB.state = "Terminated";
            node_deletion(C.ReadyQueue.Head,C.ReadyQueue.Tail,Curr);
        }
        
        // Output
        std::cout<<"============================================================\n"
        "====================== CPU MANAGEMENT ======================\n"
        "============================================================\n\n"
        "CPU\n"
        "------------------------------------------------------------\n"
        "Core ID              : "<<cpu.Core_ID<<"\n"
        "Status               : "<<cpu.Status<<"\n"
        "Running Process      : "<<cpu.Running_Process<<"\n\n"
        "READY QUEUE\n"
        "------------------------------------------------------------\n\n";
        std::cout<<"Front -> [";
        // Queue all Process Output
        if (Q.Head) {
            CPU_Management::Node *travrse = Q.Head;
            while (travrse) {
                std::cout<<*travrse->Process_ID;
                if (travrse->next) {
                            std::cout<<"] -> [";
                }
                else {
                    std::cout<<"] ";
                }
                travrse = travrse->next;
            }
        }
        else {
            std::cout<<"Empty] ";
        }
        std::cout<<"<- Back \n\n"
        "SCHEDULER\n"
        "------------------------------------------------------------\n"
        "Algorithm            : FCFS \n"
        "Next Process         : "<<Next_process<<"\n"
        "============================================================\n\n";
    }

    // FCFS Display Physical Memory Function
    static void display(const Memory_Management::Physical_Memory &P1) {
        std::cout<<"============================================================\n"
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
            std::cout<<P1.Frame[i].Frame_Number<<"                "<<P1.Frame[i].Frame_Status<<"            ";
            if (P1.Frame[i].Occupancy.first == -1) {
                std::cout<<"NONE\n";
            }
            else {
                std::cout<<"PID "<<P1.Frame[i].Occupancy.first<<" - "<<"Page "<<P1.Frame[i].Occupancy.second<<"\n";
            }
        }
        std::cout<<"------------------------------------------------------------\n"
        "Memory Usage       : "<<P1.total_used_memory<<" KB / "<<P1.RAM_Size<<" KB \n"
        "Free Memory        : "<<P1.RAM_Size-P1.total_used_memory<<" KB \n"
        "Occupied Frames    : "<<P1.Frame_information.Allocated_Frames<<" \n"
        "Free Frames        : "<<P1.Frame_information.Free_Frames<<" \n"
        "============================================================\n\n";
    }

    // Round-Robin Display Functions
    static void display(const CPU_Management::CPU &CPU,CPU_Management::Ready_Queue &Queue,int Time_Quanta,const std::string &Next_Process,const int &remian_time,std::string &state) {
        
        // Checking whether process will Execute or not
        if (remian_time>0) {
            
            // insert at end of Queue
            node_insertion(Queue.Head,Queue.Tail,Queue.Head->Process_ID);
            
            // Remove from front of Queue
            node_deletion(Queue.Head,Queue.Tail);
        }
        else {
            state = "Terminated";
            
            // If time completed then remove from Queue
            node_deletion(Queue.Head,Queue.Tail);
        }
        
        // Output
        std::cout<<"=============================================================\n"
        "===================== CPU MANAGEMENT ========================\n"
        "=============================================================\n\n"
        "CPU\n"
        "------------------------------------------------------------\n"
        "Core ID              : "<<CPU.Core_ID<<"\n"
        "Status               : "<<CPU.Status<<"\n"
        "Running Process      : "<<CPU.Running_Process<<"\n\n"
        "READY QUEUE\n"
        "------------------------------------------------------------\n";
        std::cout<<"Front -> [";
        // Queue all Process Output
        if (Queue.Head) {
            CPU_Management::Node *travrse = Queue.Head;
            while (travrse) {
                std::cout<<*travrse->Process_ID;
                if (travrse->next) {
                    std::cout<<"] -> [";
                }
                else {
                    std::cout<<"] ";
                }
                travrse = travrse->next;
            }
        }
        else {
            std::cout<<"Empty] ";
        }
        std::cout<<"<- Back \n\n"
        "SCHEDULER\n"
        "------------------------------------------------------------\n"
        "Algorithm            : ROUND ROBIN\n"
        "Time Quantum         : "<<Time_Quanta<<"\n"
        "Current Process      : "<<CPU.Running_Process<<"\n"
        "Remaining Burst Time : "<<remian_time<<"\n"
        "Next Process         : "<<Next_Process<<"\n"
        "============================================================\n\n";
        std::cout<<"CURRENT ACTION\n"
        "------------------------------------------------------------\n";
        
        if (remian_time>0) {
            std::cout<<"PID "<<CPU.Running_Process<<" time quantum expired.\n";
            std::cout<<"PID "<<CPU.Running_Process<<" moved to the back of the Ready Queue.\n\n";
            std::cout<<"Round Robin selected "<<*Queue.Head->Process_ID<<".\n"
            "PID "<<*Queue.Head->Process_ID<<" dispatched to CPU Core 0.\n"
            "------------------------------------------------------------\n\n";
        }
        else {
            std::cout<<"PID "<<CPU.Running_Process<<" is successfully terminated\n"
            "------------------------------------------------------------\n\n";
        }
    }


    // Display function Process Information
    static void display(const int &RAM_size,const int &Page_size,const int &Frame_size,const int &Number_of_frames,const Process_Manager &process) {
        std::cout<<"============================================================\n"
        "================ OPERATING SYSTEM SIMULATOR ================\n"
        "=============== PROCESS & MEMORY MANAGEMENT ================\n"
        "============================================================\n\n"
        "SIMULATION CONFIGURATION\n"
        "------------------------------------------------------------\n"
        "CPU Cores            : 1 \n"
        "Scheduler            : ROUND ROBIN \n"
        "RAM Size             : "<<RAM_size<<" KB \n"
        "Page Size            : "<<Page_size<<" KB \n"
        "Frame Size           : "<<Frame_size<<" KB \n"
        "Number of Frames     : "<<Number_of_frames<<"\n"
        "------------------------------------------------------------\n\n"
        "PROCESS TABLE\n"
        "------------------------------------------------------------\n"
        "PID       AT       BT       Process Size       State\n"
        "------------------------------------------------------------\n";
        for (int i=0;i<process.Number_of_Process;i++) {
            std::cout<<process.Process_Information[i].Process_Stats.PID<<"      "<<process.Process_Information[i].Process_Stats.Arrival_Time<<"        "<<process.Process_Information[i].Process_Stats.Burst_Time<<"     "<<process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB               "<<process.Process_Information[i].PCB.state<<"\n";
        }
        std::cout<<"------------------------------------------------------------\n\n";

        std::cout<<"PROCESS MANAGEMENT\n";
        for (int i=0;i<process.Number_of_Process;i++) {
            std::cout<<"------------------------------------------------------------\n"
            "PID: "<<process.Process_Information[i].Process_Stats.PID<<"\n"
            "------------------------------------------------------------\n"
            "Process Information\n"
            "\tPID                  : "<<process.Process_Information[i].Process_Stats.PID<<"\n"
            "\tArrival Time         : "<<process.Process_Information[i].Process_Stats.Arrival_Time<<"\n"
            "\tBurst Time           : "<<process.Process_Information[i].Process_Stats.Burst_Time<<"\n"
            "\tProcess Size         : "<<process.Process_Information[i].Process_Stats.Memory_Requirement<<" KB\n"
            "\tState                : "<<process.Process_Information[i].PCB.state<<"\n\n"
            "PCB\n"
            "\tCompletion Time      : "<<process.Completion_Time[i]<<"\n"
            "\tWaiting Time         : "<<process.Process_Information[i].PCB.Waiting_Time<<"\n"
            "\tTurnaround Time      : "<<process.Process_Information[i].PCB.Turnaround_Time<<"\n"
            "\tResponse Time        : "<<process.Process_Information[i].PCB.Response_Time<<"\n\n"
            "PAGE TABLE\n"
            "\t---------------------------------------------------------\n"
            "\tPage    Frame    Valid    Dirty    Accessed    Protection\n"
            "\t---------------------------------------------------------\n";
            for (int j=0;j<process.Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {
                std::cout<<"\t"<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number<<"       "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number<<"        "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Valid<<"      "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Dirty<<"       "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed<<"          "<<process.Process_Information[i].Process_Page_Table.page_table_entries[j].Protection<<"\n";
            }
            std::cout<<"\t---------------------------------------------------------\n\n";
        }

    }

    // Node Insertion
    static void node_insertion(CPU_Management::Node *&Head,CPU_Management::Node *&Tail,int *process_ID) {
        if (Head == nullptr) {
            Head = new CPU_Management::Node(process_ID);
            Tail = Head;
        }
        else {
            Tail->next = new CPU_Management::Node(process_ID);
            Tail =Tail->next;
        }
    }

    // Node Deletion for Round Robin
    static void node_deletion(CPU_Management::Node *&Head,CPU_Management::Node *&Tail) {
        CPU_Management::Node *node = Head->next;
        if (node == nullptr) {
            Tail = nullptr;
        }
        delete Head;
        Head = node;
    }
    // Node Deletion
    static void node_deletion(CPU_Management::Node *&Head,CPU_Management::Node *&Tail,CPU_Management::Node *&curr) {
        if (Head == nullptr || curr == nullptr) {
            return;
        }
        CPU_Management::Node *node = Head->next;
        if (node == nullptr) {
            Tail = nullptr;
        }
        delete Head;
        Head = node;
        curr = Head;
    }

    // RAM Size Validation
    static int ram_size_validation() {
        int RAM_Size = 0;
        do {
            if (RAM_Size == 0) {
                std::cout<<"Enter RAM Size: ";
                std::cin>>RAM_Size;
            }
            else {
                std::cout<<"Invalid Input. Please Try Again. ";
                std::cin>>RAM_Size;
            }
            std::cout<<std::endl;
        }while (RAM_Size<1 || RAM_Size%2 != 0);
        return RAM_Size;
    }

    // Frame Size Validation
    static int frame_size_validation(int RAM_Size) {
        int Frame_Size = 0;
        do {
            if (Frame_Size == 0) {
                std::cout<<"Enter Frame size: ";
                std::cin>>Frame_Size;
            }
            else {
                std::cout<<"Invalid Input. Please Try Again. ";
                std::cin>>Frame_Size;
            }
            std::cout<<std::endl;
        }while (Frame_Size<1 || RAM_Size%Frame_Size != 0);
        return Frame_Size;
    }

    //Process_Size_Validation
    static int process_number_validation() {
        int Number = 0;
        do {
            if (Number == 0) {
                std::cout<<"Enter the Number of Processes: ";
            }
            else {
                std::cout<<"Invalid Input! Please Try Again. ";
            }
            std::cin>>Number;
        }while (Number<0);
        return Number;
    }
    
    ~Operating_System() {
        for (int i=0;i<C.ReadyQueue.Physical_Memory.Process.Number_of_Process;i++) {
            delete []C.ReadyQueue.Physical_Memory.Process.Process_Information[i].Process_Page_Table.page_table_entries;
        }
        delete []C.ReadyQueue.Physical_Memory.Process.Completion_Time;
        delete []C.ReadyQueue.Physical_Memory.Process.Process_Information;
        delete []C.ReadyQueue.Physical_Memory.Frame_Check;
        delete []C.ReadyQueue.Physical_Memory.Frame;
    }

};

int main() {
    srand(time(nullptr));
    while (true) {
        if (Simulation_UI()) {
            Operating_System OS;
        }
        else {
            std::cout<<"You decided to Exit the Simulator.\n";
            break;
        }
    }
    return 0;
}
