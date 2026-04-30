#include<iostream>
using namespace std;
int main() {
    int loop_variable=3;
    int Arrival_Time[3];
    int Burst_Time[3];
    int Completion_Time[3];
    int Turn_Around_Time[3];
    int Waiting_Time[3];
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
        Turn_Around_Time[i]=Completion_Time[i]-Arrival_Time[i];
        Waiting_Time[i]=Turn_Around_Time[i]-Burst_Time[i];
    }
  //for non-preemptive processes responce time ~ waiting time. So i, use waiting time twice.
  //A-time == Arival-Time
  //B-Time == Brust -Time
  //C-Time == Completion-Time
  //T-Time == Turn-Around-Time
  //W-Time == Waiting-Time
  //R-Time == Responce-Time
    cout<<"--------------------------------------------------------------"<<endl;
    cout<<"| PSID | A-Time | B-Time | C-Time | T-Time | W-Time | R-Time |"<<endl;
    for (int i=0;i<loop_variable;i++) {
        cout<<"|  P"<<i+1<<"  |    "<<Arrival_Time[i]<<"   |    "<<Burst_Time[i]<<"   |    "<<Completion_Time[i]<<"   |    "<<Turn_Around_Time[i]<<"   |    "<<Waiting_Time[i]<<"   |    "<<Waiting_Time[i]<<"   |"<<endl;
    }
    cout<<"--------------------------------------------------------------";
}
