#include <iostream>
#include <map>
using namespace std;


int main()
{
    cout << "Enter your string: ";
    string str; cin >> str;
    size_t n = str.length();
    map <char, int> m;
    for (int i = 0; i < n; i++){
        if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z')){
            m[str[i]]++;
        } 
    }
    
    map <char, int> :: iterator it = m.begin();
    
    for (; it != m.end(); it++){
        cout << it-> first << "   " << it->second << "\n";
    }
    
    while(true){
        cout << "Enter 0 to exit";
        cout << "\nEnter letter to find in map: ";
        char c; cin >> c;
        if(c=='0'){
            return 0;
        }else{
            it = m.find(c);
            cout << "Amount of " << c << ": " << it->second << "\n";
        }
    }
    
}
