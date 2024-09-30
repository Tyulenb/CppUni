#include <iostream>

using namespace std;

class Deq {
private:
    int front = 0;
    int back = 0;
    int capacity;
    char* arr;
public:
    Deq(int capacity){
        this->capacity = capacity;
        arr = new char[capacity];
        back = capacity-1;
    }
    ~Deq(){
        delete[] arr;
    }
    
    bool push_back(char elem){
        if(back==front){
            return false;
        }
        arr[back] = elem;
        back--;
        return true;
    }
    
    bool push_front(char elem){
        if(front == back){
            return false;
        }
        arr[front] = elem;
        front++;
        return true;
    }
    
    char pop_back(){
        if(back == capacity-1){
            return 0;
        }
        char elem = arr[back];
        arr[back] = 0;
        back++;
        return elem;
    }
    
    char pop_front(){
        if(front == 0){
            return 0;
        }
        char elem = arr[front];
        arr[front] = 0;
        front--;
        return elem;
    }
    
    char get_front(){
        if(front == 0){
            return 0;
        }
        return arr[front];
    }
    
    char get_back(){
        if(back==0){
            return 0;
        }
        return arr[back];
    }
    void print_deq(){
        cout << "WORK!";
        for(int i = 0; i < front; i++){
            cout << arr[i] << " ";
        }
        for(int i = capacity-1; i > back; i--){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
};

int main()
{
    cout << "Enter your string length\n";
    int n; cin >> n;
    Deq deq(n);
    
    for(int i = 0; i < n; i++){
        deq.push_front(char(i));
    }
    deq.print_deq();
}
