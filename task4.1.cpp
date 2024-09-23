#include <iostream>
#include <stack>

using namespace std;

int main()
{
    string s, w;
    cout << "Введите первую строку: ";
    cin >> s;
    cout << "\nВведите вторую строку: ";
    cin >> w;
    string sw = s+"*"+w;
    
    stack<char> st;
    int i = 0;
    while (sw[i]!='*'){
        st.push(sw[i]);
        ++i;
    }
    i = 0;
    while(!st.empty()){
        if (st.top()!=w[i]){
            cout << "\nОтвет отрицательный";
            return 0;
        }
        i++;
        st.pop();
    }
    cout << "\nОтвет положительный";
}
