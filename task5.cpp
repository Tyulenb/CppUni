#include <iostream>
#include <deque>

using namespace std;

class Deq {
private:
    char* arr;
    int front = -1;
    int back = 0;
    int capacity;
    int size = 0;
public:
    Deq(int capacity) {
        this->capacity = capacity;
        arr = new char[capacity];
    }
    ~Deq() {
        delete[] arr;
    }

    void push_front(char elem) {
        if (size == capacity) {
            return;
        }
        front = (front + 1) % capacity;
        arr[front] = elem;
        size++;
        if (back == 0) {
            back = front;
        }
    }

    void push_back(char elem) {
        if (size == capacity) {
            return;
        }
        back = (back - 1 + capacity) % capacity;
        arr[back] = elem;
        size++;
        if (front == -1) {
            front = back;
        }
    }

    void pop_front() {
        if (size == 0) {
            return;
        }
        front = (front - 1 + capacity) % capacity;
        size--;
        if (size == 0) { // Сброс
            front = -1;
            back = 0;
        }
    }

    void pop_back() {
        if (size == 0) {
            return;
        }
        back = (back + 1) % capacity;
        size--;
        if (size == 0) {
            front = -1;
            back = 0;
        }
    }

    char get_back() {
        if (size == 0) {
            return '=';
        }
        return arr[back];
    }

    char get_front() {
        if (size == 0) {
            return '=';
        }
        return arr[front];
    }

    void print_deq() {
        for (int i = 0; i < size; i++) {
            int ind = (front - i + capacity) % capacity;
            cout << arr[ind];
        }
        cout << "\n";
    }
};

int main()
{
    for (int i = 0; i < 2; i++) {
        cout << "\nEnter your string: ";
        string str; cin >> str;
        size_t n = str.size();
        Deq deq(n);
        for (int i = 0; i < n; i++) {
            deq.push_back(str[i]);
        }
        cout << "\nYour string is: ";
        deq.print_deq();
        for (int i = 0; i < n / 2; i++) {
            char elem = deq.get_back();
            deq.pop_back();
            deq.push_front(elem);
        }
        cout << "\nYour string after swapping: ";
        deq.print_deq();
    }
}