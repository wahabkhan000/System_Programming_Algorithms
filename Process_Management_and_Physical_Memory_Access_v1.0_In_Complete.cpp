#include<iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <utility>
using std::cout,std::cin,std::endl,std::string,std::vector,std::sort,std::pair,std::swap;

void Simulation_UI(){
    cout<<"============================================================"
          "================ OPERATING SYSTEM SIMULATOR ================"
          "================ Process & Memory Management ==============="
          "============================================================"
          "1. Create Simulation"
          "0. Exit"
          "Select option:"<<endl;
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
}
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

// Process Manager
struct Process_Manager {
    struct Static_Information {
        int PID;
        int Arrival_Time;
        int Burst_Time;
        int Memory_Requirement;
    };
    struct PCB {
        string state;
        int Completion_Time;
        int Waiting_Time;
        int Turnaround_Time;
        int Response_Time;
    };
    struct Page_Table {
        struct Page_Table_Entries {
            int Page_Number;
            int Frame_Number;
            char Protection;
            int Accessed;
        };
        int Number_of_Pages;
        int Page_Size;
        int Process_Size;
        Page_Table_Entries *page_table_entries = nullptr;
    };

    struct Individual_Process_Information {
        Static_Information Process_Stats;
        PCB Process_Control_Block;
        Page_Table Process_Page_Table;
    };
    int Number_of_Process;
    int *Completion_Time = nullptr;
    Individual_Process_Information *Process_Information = nullptr;

    // int *PID_check = nullptr;
    // int **Arrival_Time_sort = nullptr;
    // Static_Information *Process_Stats = nullptr;
    // PCB *Process_Control_Block = nullptr;
    // Page_Table *Process_Page_Table = nullptr;


    // Process_Manager() {
    //     cout<<"Enter Number of Process: ";
    //     cin>>Number_of_Process;
    //
    //     //PID check Resize
    //     // PID_check = new int[Number_of_Process];
    //
    //     //Arrival Time Sort Resize
    //     // Arrival_Time_sort = new int*[Number_of_Process];
    //
    //     //Completion Time resize
    //     Completion_Time = new int[Number_of_Process];
    //
    //     // Process_Information resize
    //     Process_Information = new Individual_Process_Information[Number_of_Process];
    //     // Process Information Assign
    //     for (int i=0;i<Number_of_Process;i++) {
    //         int temp_value = rand()+1;
    //         bool repeated = false;
    //         do {
    //             repeated = false;
    //             temp_value = rand()+1;
    //             repeated = repeat_check(temp_value,Process_Information,Number_of_Process);
    //         }while (repeated == true);
    //         // PID global Entry
    //         // PID_check[i] = temp_value;
    //
    //         // PID
    //         Process_Information[i].Process_Stats.PID = temp_value;
    //         // Arrival Time
    //         Process_Information[i].Process_Stats.Arrival_Time = rand()%10;
    //         // Arrival Time Sort Global
    //         // Arrival_Time_sort[i] = &Process_Information[i].Process_Stats.Arrival_Time;
    //
    //         // Burst Time
    //         Process_Information[i].Process_Stats.Burst_Time = rand()%11;
    //         Completion_Time[i] = Process_Information[i].Process_Stats.Burst_Time+Process_Information[i].Process_Stats.Arrival_Time;
    //         // Individual Memory Assign
    //         bool check = false;
    //         temp_value = 0;
    //         do {
    //             check = false;
    //             temp_value = rand()%10;
    //             if (temp_value%2 != 0 || temp_value == 0) {
    //                 check = true;
    //             }
    //         }while (check == true);
    //         Process_Information[i].Process_Stats.Memory_Requirement = temp_value;
    //
    //     }
    //
    //     // Arrival Time Sort sorting
    //     for (int i=0;i<Number_of_Process;i++) {
    //         for (int j=i;j<Number_of_Process;j++) {
    //             if (Process_Information[i].Process_Stats.Arrival_Time>Process_Information[j].Process_Stats.Arrival_Time){
    //             // if (*Arrival_Time_sort[i]>*Arrival_Time_sort[j]) {
    //                 swap(Process_Information[i].Process_Stats.Arrival_Time,Process_Information[j].Process_Stats.Arrival_Time);
    //                 // swap(*Arrival_Time_sort[i],*Arrival_Time_sort[j]);
    //                 swap(Process_Information[i].Process_Stats.PID,Process_Information[j].Process_Stats.PID);
    //                 swap(Completion_Time[i],Completion_Time[j]);
    //                 swap(Process_Information[i].Process_Stats.Burst_Time,Process_Information[j].Process_Stats.Burst_Time);
    //                 swap(Process_Information[i].Process_Stats.Memory_Requirement,Process_Information[j].Process_Stats.Memory_Requirement);
    //             }
    //         }
    //     }
    //
    //     // Completion Time Calculation
    //     for (int i=1;i<Number_of_Process;i++) {
    //         if (Process_Information[i-1].Process_Stats.Arrival_Time == Process_Information[i].Process_Stats.Arrival_Time) {
    //             Completion_Time[i]+=Completion_Time[i-1];
    //         }
    //         else if (Completion_Time[i-1]>Process_Information[i].Process_Stats.Arrival_Time) {
    //             int rem_time = 0;
    //             rem_time = Completion_Time[i-1]-Process_Information[i].Process_Stats.Arrival_Time;
    //             Completion_Time[i]+=rem_time;
    //         }
    //     }
    //
    //     cout<<"After swap: "<<endl;
    //     for (int i=0;i<Number_of_Process;i++) {
    //         cout<<"PID "<<Process_Information[i].Process_Stats.PID<<" "<<"Arrival Time "<<Process_Information[i].Process_Stats.Arrival_Time<<" "<<"Burst Time "<<Process_Information[i].Process_Stats.Burst_Time<<" "<<"Completion Time "<<Completion_Time[i]<<" "<<"Memory Requirement "<<Process_Information[i].Process_Stats.Memory_Requirement<<endl;
    //     }
    //
    //     // Process Control Block Information
    //     for (int i=0;i<Number_of_Process;i++) {
    //         Process_Information[i].Process_Control_Block.state = "NEW";
    //         Process_Information[i].Process_Control_Block.Completion_Time = Completion_Time[i];
    //         Process_Information[i].Process_Control_Block.Turnaround_Time = Completion_Time[i]-Process_Information[i].Process_Stats.Arrival_Time;
    //         Process_Information[i].Process_Control_Block.Waiting_Time = Process_Information[i].Process_Control_Block.Turnaround_Time - Process_Information[i].Process_Stats.Burst_Time;
    //         int first_CPU = Process_Information[i].Process_Stats.Arrival_Time;
    //         if (i != 0) {
    //             first_CPU = Completion_Time[i-1];
    //         }
    //         Process_Information[i].Process_Control_Block.Response_Time = first_CPU;
    //     }
    //
    //     // Process Page Table
    //     for (int i=0;i<Number_of_Process;i++) {
    //         // Process Size
    //         Process_Information[i].Process_Page_Table.Process_Size = Process_Information[i].Process_Stats.Memory_Requirement;
    //         // Page Size
    //         Process_Information[i].Process_Page_Table.Page_Size = 2;
    //         // Number of Pages
    //         Process_Information[i].Process_Page_Table.Number_of_Pages = Process_Information[i].Process_Page_Table.Process_Size/Process_Information[i].Process_Page_Table.Page_Size;
    //         // Page Table Entries resize
    //         Process_Information[i].Process_Page_Table.page_table_entries = new Page_Table::Page_Table_Entries[Process_Information[i].Process_Page_Table.Number_of_Pages];
    //         for (int j=0;j<Process_Information[i].Process_Page_Table.Number_of_Pages;j++) {
    //             char Protection_Value[3] = {'R','W','X'};
    //             Process_Information[i].Process_Page_Table.page_table_entries[j].Protection = Protection_Value[rand()%3];
    //             Process_Information[i].Process_Page_Table.page_table_entries[j].Page_Number = j;
    //             Process_Information[i].Process_Page_Table.page_table_entries[j].Accessed = 0;
    //             Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number = 0;
    //         }
    //     }
    //
    // }

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

// CPU Information
struct CPU {
    int Core_ID;
    string Status;
    string Running_Process;
    CPU(const string &PID) {
        Core_ID = 0;
        if (PID != "NONE") {
            Running_Process = PID;
            Status = "BUSY";
        }
        else {
            Running_Process = "NONE";
            Status = "IDLE";
        }
    }
};

// Ready Queue
struct Ready_Queue {
    Node *Head = nullptr;
    Node *Tail = nullptr;
    Ready_Queue() {
        // Temporary PID
        int PID = 0;
        Node *curr;
        node_insertion(Head,Tail,&PID);
        node_deletion(Head,Tail,curr);
    }
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
    int total_pages;
    int Number_of_Frames;
    int total_used_memory;
    Process_Manager Process;
    Frame_Information Frame_information;
    Frame_Manager *Frame = nullptr;
    bool *Frame_Check = nullptr;
    Physical_Memory() {

        // RAM Size
        RAM_Size = ram_size_validation();

        // Frame Size
        Frame_Size = frame_size_validation(RAM_Size);

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
        cout<<"Enter Number of Process: ";
        cin>>Process.Number_of_Process;

        //PID check Resize
        // Process.PID_check = new int[Process.Number_of_Process];

        //Arrival Time Sort Resize
        // Process.Arrival_Time_sort = new int*[Process.Number_of_Process];

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
            // PID global Entry
            // PID_check[i] = temp_value;

            // PID
            Process.Process_Information[i].Process_Stats.PID = temp_value;
            // Arrival Time
            Process.Process_Information[i].Process_Stats.Arrival_Time = rand()%10;
            // Arrival Time Sort Global
            // Arrival_Time_sort[i] = &Process_Information[i].Process_Stats.Arrival_Time;

            // Burst Time
            Process.Process_Information[i].Process_Stats.Burst_Time = rand()%11;
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
            cout<<temp_value<<endl;
            Process.Process_Information[i].Process_Stats.Memory_Requirement = temp_value;
            // Total Memory use Calculation
            total_used_memory+=temp_value;

        }

        // Arrival Time Sort sorting
        for (int i=0;i<Process.Number_of_Process;i++) {
            for (int j=i;j<Process.Number_of_Process;j++) {
                // Condition Check
                if (Process.Process_Information[i].Process_Stats.Arrival_Time>Process.Process_Information[j].Process_Stats.Arrival_Time){
                // if (*Process.Arrival_Time_sort[i]>*Process.Arrival_Time_sort[j]) {
                    // swap Arrival Time
                    swap(Process.Process_Information[i].Process_Stats.Arrival_Time,Process.Process_Information[j].Process_Stats.Arrival_Time);
                    // swap(*Process.Arrival_Time_sort[i],*Process.Arrival_Time_sort[j]);
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

        // cout<<"After swap: "<<endl;
        // for (int i=0;i<Process.Number_of_Process;i++) {
        //     cout<<"PID "<<Process.Process_Information[i].Process_Stats.PID<<" "<<"Arrival Time "<<Process.Process_Information[i].Process_Stats.Arrival_Time<<" "<<"Burst Time "<<Process.Process_Information[i].Process_Stats.Burst_Time<<" "<<"Completion Time "<<Process.Completion_Time[i]<<" "<<"Memory Requirement "<<Process.Process_Information[i].Process_Stats.Memory_Requirement<<endl;
        // }

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
                frame_number_count++;
                // Frame Number record in Page Table
                Process.Process_Information[i].Process_Page_Table.page_table_entries[j].Frame_Number = Frame[frame_number_count].Frame_Number;
                // Frame Information Allocated Frames
                Frame_information.Allocated_Frames++;
            }
        }

        // Frame Information Free Frames
        Frame_information.Free_Frames = Frame_information.Total_Frames - Frame_information.Allocated_Frames;
        cout<<Frame_information.Free_Frames<<endl;
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

int main() {
    srand(time(NULL));
    Physical_Memory P1;
}
