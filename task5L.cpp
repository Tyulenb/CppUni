#include <list>
#include <iostream>

using namespace std;

class Deq {
private:
        list<char> data;
public:
    void push_front(char elem) {
        data.push_front(elem);
    }

    void push_back(char elem) {
        data.push_back(elem);
    }

    void pop_front() {
        data.pop_front();
    }
    void pop_back() {
        data.pop_back();
    }

    char back() {
        if (!data.empty()) {
            return data.back();
        }
    }
    char front() {
        if (!data.empty()) {
            return data.front();
        }
    }
    void print_deq() {
        for (char v : data) {
            cout << v;
        }
        cout << "\n";
    }
};

int main()
{
    cout << "\nEnter your string: ";
    string str; cin >> str;
    size_t n = str.size();
    Deq deq;

    for (int i = 0; i < n; i++) {
        deq.push_back(str[i]);
    }

    cout << "\nYour string is: ";
    deq.print_deq();
    for (int i = 0; i < n / 2; i++) {
        char elem = deq.back();
        deq.pop_back();
        deq.push_front(elem);
    }
    cout << "\nString after swapping: ";
    deq.print_deq();
}


