# include <iostream>
using namespace std;
int main() {
    string s;
    getline(cin,s);
    for (int i=0;i<s.length();i++) {
        int n=s[i];
        int rem=0;
        string c;
        while (n>0)
        {
            rem=n%2;
            n=n/2;
            c=to_string(rem)+c;
        }
        if (c.length()<8) {
            cout<<to_string(0)+c<<" ";
        }
        else {
            cout<<c<<" ";
        }
    }
}
