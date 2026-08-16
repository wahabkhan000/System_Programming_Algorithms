#include <iostream>
#include <utility>
using std::cout,std::cin,std::endl,std::string,std::pair;

struct Memory_Management_Unit {
    int Process_Size;
    int Process_ID;
    int Logical_Address;
    int Frame_Number;
    pair<int,int>Address_Translation;
    int Physical_Address;
};

struct Frame_Manager {
    int Frame_Number;
    string Frame_Status;
    pair<int,int>Occupancy;
};

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
struct Physical_Memory {
    //temporary
    int Number_of_Process;
    int *PID = nullptr;
    int *Process_Size = nullptr;
    Memory_Management_Unit MMU;

    //Actual Members
    int RAM_Size;
    int Page_Size;
    int Frame_Size;
    int Number_of_Frames;
    Frame_Manager *Frame = nullptr;
    //Check which Frame is free or not
    bool *Frame_check = nullptr;
    Frame_Information Frame_Information;
    Physical_Memory() {

        // RAM Size
        RAM_Size = 0;
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

        //Frame Size
        Frame_Size = 0;
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

        //Page Size
        Page_Size = Frame_Size;

        //Number of Frames
        Number_of_Frames = RAM_Size/Frame_Size;

        //Frame Check Resize
        Frame_check = new bool[Number_of_Frames]();

        //Number of Process
        cout<<"Enter Number of Process: ";
        cin>>Number_of_Process;
        cout<<endl;

        //Process_Size resize
        Process_Size = new int[Number_of_Process]();
        //Process size
        for (int i=0;i<Number_of_Process;i++) {
            Process_Size[i] = 2*Page_Size;
        }

        //PID resize
        PID = new int[Number_of_Process]();
        //PID rand Value
        for (int i=0;i<Number_of_Process;i++) {
            int temp_value = rand()+1;
            bool repeated = false;
            do {
                repeated = false;
                temp_value = rand()+1;
                repeated = repeat_check(temp_value,PID,Number_of_Process);
            }while (repeated == true);
            PID[i] = temp_value;
        }

        //Frame Information
        Frame_Information.Total_Frames = Number_of_Frames;

        //Frame Array Resize
        Frame = new Frame_Manager[Number_of_Frames]();
        //Page Number Temporary
        int k = 0;
        int l = 0;
        for (int i=0;i<Number_of_Frames;i++) {
            if (i<Number_of_Process*2) {

                //repeated Frame Check
                int temp_value = rand()%Number_of_Frames;
                bool repeated = false;
                do {
                    repeated = false;
                    temp_value = rand()%Number_of_Frames;
                    for (int j=0;j<Number_of_Process;j++) {
                        if (temp_value == Frame[j].Frame_Number) {
                            repeated = true;
                            break;
                        }
                    }
                }while (repeated == true);

                //Frame Values
                Frame_Information.Allocated_Frames++;
                Frame[i].Frame_Number = temp_value;
                Frame[i].Frame_Status = "Occupied";
                Frame[i].Occupancy.first = PID[l];
                if (k == 0 || k == 1) {
                    Frame[i].Occupancy.second = k++;
                }
                if (k == 2) {
                    k = 0;l = i;
                }
            }
            else {
                Frame_Information.Free_Frames++;
                Frame[i].Frame_Number = i;
                Frame[i].Frame_Status = "Free";
                Frame[i].Occupancy.first = -1;
                Frame[i].Occupancy.second = -1;
            }
        }

        //output
        cout<<"============================================================\n"
              "==================== PHYSICAL MEMORY ======================\n"
              "============================================================\n"
              "MEMORY CONFIGURATION\n"
              "------------------------------------------------------------\n"
              "RAM Size             : "<<RAM_Size<<" KB\n"
              "Page Size            : "<<Page_Size<<" KB\n"
              "Frame Size           : "<<Frame_Size<<" KB\n"
              "Number of Frames     : "<<Number_of_Frames<<"\n"
              "FRAME TABLE\n"
              "------------------------------------------------------------\n"
              "Frame No.       Status          Occupancy\n"
              "------------------------------------------------------------\n";
        for (int i=0;i<Number_of_Frames;i++) {
            cout<<Frame[i].Frame_Number<<"                "<<Frame[i].Frame_Status<<"            ";
            if (Frame[i].Occupancy.first == -1) {
                cout<<"NONE"<<endl;
            }
            else {
                cout<<"PID "<<Frame[i].Occupancy.first<<" - "<<"Page "<<Frame[i].Occupancy.second<<endl;
            }
        }
              cout<<"------------------------------------------------------------\n"
              "Memory Usage       : "<<Number_of_Process*Process_Size[0]<<" KB / "<<RAM_Size<<" KB \n"
              "Free Memory        : "<<RAM_Size-(Number_of_Process*Process_Size[0])<<" KB \n"
              "Occupied Frames    : "<<Frame_Information.Allocated_Frames<<" \n"
              "Free Frames        : "<<Frame_Information.Free_Frames<<" \n"
              "============================================================"<<endl;
    }

    //repeat function
    bool repeat_check(int temp_value,const int *store,int length) {
        for (int i=0;i<length;i++) {
            if (temp_value == store[i]) {
                return true;
            }
        }
        return false;
    }
};


int main() {
    srand(time(NULL));
    Physical_Memory P1;
}
