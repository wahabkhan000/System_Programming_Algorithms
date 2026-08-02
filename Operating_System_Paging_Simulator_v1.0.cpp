#include <iostream>
#include <cmath>
using std::cout,std::cin,std::endl,std::string;
int ram_size_validation(int ram) {
    ram = 0;
    do {
        if (ram == 0) {
            cout<<"Enter RAM Space above '0 byte' and less then equal to '16 byte' :"<<endl;
        }
        else {
            cout<<"You enter wrong size. Please try again."<<endl;
        }
        cin>>ram;
    }while (ram<1 || ram>16);
    return ram;
}
int process_size_validation(int process_size) {
    process_size = 0;
    do {
        if (process_size == 0) {
            cout<<"Enter Process size above '0 byte' and less then equal to '16 byte' :"<<endl;
        }
        else {
            cout<<"You enter wrong size. Please try again."<<endl;
        }
        cin>>process_size;
    }while (process_size<1 || process_size>16);
    return process_size;
}
int frame_number_validation(int total_frame_number,int ram_size) {
    total_frame_number = 0;
    do {
        if (total_frame_number == 0) {
            cout<<"Enter number of Frames above '0' and less then equal to '"<<ram_size<<"' :"<<endl;
        }
        else {
            cout<<"You enter wrong number. Please try again."<<endl;
        }
        cin>>total_frame_number;
    }while (ram_size%total_frame_number != 0);
    return total_frame_number;
}
void logical_address_bit(int cpu_demand,string &logical_address_bits,int total_bits) {
    logical_address_bits.clear();
    for (int i=total_bits-1;i>=0;i--) {
        logical_address_bits+=std::to_string((cpu_demand>>i)&1);
    }
}
void physical_address_bit(int frame_number,string &physical_address,int frame_offset_value,int number_bit,int offset_bit) {
    physical_address.clear();
    for (int i=number_bit-1;i>=0;i--) {
        physical_address+=std::to_string((frame_number>>i)&1);
    }
    for (int i=offset_bit-1;i>=0;i--) {
        physical_address+=std::to_string((frame_offset_value>>i)&1);
    }
}
int validate_cpu_demands(int cpu_demand,int process_size) {
    cpu_demand = 0;
    do {
        if (cpu_demand == 0) {
            cout<<"Enter Byte CPU is demanding less then '"<<process_size<<" byte':"<<endl;
        }
        else {
            cout<<"You enter wrong size. Please try again."<<endl;
        }
        cin>>cpu_demand;
    }while (cpu_demand<0 || cpu_demand>process_size-1);
    return cpu_demand;
}
int bit_value_offset(int count,const string &address) {
    int value = 0;
    for (int i=(int)address.length()-count;i<address.length();i++) {
        value = (value*2+(address[i]-48));
    }
    return value;
}
int bit_value_number(int count,const string &address) {
    int value = 0;
    for (int i=0;i<count;i++) {
        value = (value*2+(address[i]-48));
    }
    return value;
}
int main() {
    srand(time(NULL));
    int RAM_size = 0, process_size = 0;
    int page_size = 0, frame_size = 0;
    int total_page_numbers = 0, total_frame_numbers = 0;
    int cpu_demand = 0;
    int page_number_bits = 0, frame_number_bits = 0;
    int page_offset_bits = 0, frame_offset_bits = 0;
    int page_offset_value = 0, frame_offset_value = 0;
    int page_number_value = 0, frame_number_value = 0;

    RAM_size = ram_size_validation(RAM_size);
    total_frame_numbers = frame_number_validation(total_frame_numbers,RAM_size);
    process_size = process_size_validation(process_size);

    string physical_address_bits;
    string logical_address_bits;

    frame_size = RAM_size/total_frame_numbers;
    page_size = frame_size;
    total_page_numbers = process_size/page_size;
    if (total_page_numbers == 0) {
        total_page_numbers++;
    }

    cout<<"====================== Main Memory Data ======================"<<endl;
    int arr[total_frame_numbers][page_size];
    for (int i=0;i<total_frame_numbers;i++) {
        cout<<"Frame number "<<i<<": ";
        for (int j=0;j<page_size;j++) {
            arr[i][j] = rand()%10;
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"========================================================"<<endl;

    cout<<"====================== Page Table ======================"<<endl;
    int page_table[total_page_numbers];
    for (int i=0;i<total_page_numbers;i++) {
        int frame = 0;
        bool flag = false;
        do {
            flag = false;
            frame = rand()%total_frame_numbers;
            for (int j=0;j<i;j++) {
                if (frame == page_table[j]) {
                    flag = true;
                    break;
                }
            }
        }while (flag == true);
        page_table[i] = frame;
        cout<<"Page number "<<i<<" is present in frame: "<<page_table[i]<<endl;
    }
    cout<<"========================================================"<<endl;


    page_number_bits = (int)std::log2(total_page_numbers);
    page_offset_bits = (int)std::log2(page_size);
    frame_offset_bits = page_offset_bits;

    cpu_demand = validate_cpu_demands(cpu_demand,process_size);
    logical_address_bit(cpu_demand,logical_address_bits,page_number_bits+page_offset_bits);

    page_offset_value = bit_value_offset(page_offset_bits,logical_address_bits);
    frame_offset_value = page_offset_value;

    page_number_value = bit_value_number(page_number_bits,logical_address_bits);


    frame_number_value = page_table[page_number_value];
    frame_number_bits = (int)std::log2(total_frame_numbers);


    physical_address_bit(frame_number_value,physical_address_bits,frame_offset_value,frame_number_bits,frame_offset_bits);



    frame_number_value = bit_value_number(frame_number_bits,physical_address_bits);
    frame_offset_value = page_offset_value;


    cout<<"Total frame are: "<<total_frame_numbers<<endl;
    cout<<"Total page are: "<<total_page_numbers<<endl;
    cout<<"Logical address: "<<logical_address_bits<<endl;
    cout<<"Physical address: "<<physical_address_bits<<endl;
    cout<<"Original value is: "<<arr[frame_number_value][frame_offset_value]<<endl;
  
}
