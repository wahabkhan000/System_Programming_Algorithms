#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;
int main() {
    int loop_variable=3;
    int Arrival_Time[3];
    int Burst_Time[3];
    int Completion_Time[3];
    int Turn_Around_Time[3];
    int Waiting_Time[3];
    vector<int>Arrival_Copy;
    cout<<"=========== ****************************************************** ============"<<endl;
    cout<<endl;
    cout<<"========== For simplicity We assume the processes are Non-Preemptive =========="<<endl;
    cout<<endl;
    for (int i=0;i<loop_variable;i++) {
        cout<<"Enter the Arrival-Time for Process "<<i+1<<": ";
        cin>>Arrival_Time[i];
    }
    for (int i=0;i<loop_variable;i++) {
        cout<<"Enter the Burst-Time for Process "<<i+1<<": ";
        cin>>Burst_Time[i];
    }
    for (int i=0;i<loop_variable;i++) {
        cout<<"Enter the Completion-Time for Process "<<i+1<<": ";
        cin>>Completion_Time[i];
    }
    for (int i=0;i<loop_variable;i++) {
        if (Completion_Time[i]-Arrival_Time[i]>0) {
            Turn_Around_Time[i]=Completion_Time[i]-Arrival_Time[i];
            Waiting_Time[i]=Turn_Around_Time[i]-Burst_Time[i];
        }
        else {
            Turn_Around_Time[i]=0;
            Waiting_Time[i]=0;
        }
    }
    for (int i=0;i<loop_variable;i++) {
        int internal_element=Arrival_Time[i];
        Arrival_Copy.push_back(internal_element);
    }
    sort(Arrival_Copy.begin(),Arrival_Copy.end());
    cout<<"Processes will execute in this way:"<<endl;
    for (int j=0;j<loop_variable;j++) {
        for (int i=0;i<loop_variable;i++) {
            if (Arrival_Copy[j]==Arrival_Time[i]) {
                cout<<"P"<<i+1<<" ";
            }
        }
    }
    cout<<endl;
    //for non-preemptive processes response time ~ waiting time. So i, use waiting time twice.
    //A-time == Arrival-Time
    //B-Time == Burst -Time
    //C-Time == Completion-Time
    //T-Time == Turn-Around-Time
    //W-Time == Waiting-Time
    //R-Time == Response-Time
    cout<<"--------------------------------------------------------------"<<endl;
    cout<<"| PSID | A-Time | B-Time | C-Time | T-Time | W-Time | R-Time |"<<endl;
    for (int i=0;i<loop_variable;i++) {
        cout<<"|  P"<<i+1<<"  |    "<<Arrival_Time[i]<<"   |    "<<Burst_Time[i]<<"   |    "<<Completion_Time[i]<<"   |    "<<Turn_Around_Time[i]<<"   |    "<<Waiting_Time[i]<<"   |    "<<Waiting_Time[i]<<"   |"<<endl;
    }
    cout<<"--------------------------------------------------------------";
}
