#include <iostream>
#include <list>
#include <stack>

using namespace std;

int task1();
void task2();
void showList(list<int> &ls);


int main()
{
	setlocale(LC_ALL, "Russian");
	task1();
	cout << "\n";
	task2();
}

void showList(list<int>& ls) {
	for  (int v : ls) {
		cout << v << " -> ";
	}
	cout << "None\n";
}

int task1() {
    string s, w;
    cout << "\nВведите первую строку: ";
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
            cout << "\nСтрока s не обратна строке w";
            return 0;
        }
        i++;
        st.pop();
    }
    cout << "\nСтрока s обратна строке w";
}

void task2() {
	cout << "Введите количество чисел\n";
	int n; cin >> n;
	cout << "Введите числа\n";
	list<int> ls1, ls2;
	for (int i = 0; i < n; i++) {
		int elem; cin >> elem;
		ls1.push_back(elem);}
	

	list<int>::iterator it = ls1.begin();
	for (int i = 0; i < n; i++) {
		if (i % 5 == 0) {
			advance(it, i);
			ls2.push_back(*it);
			it = ls1.begin();
		}
	}
	cout << "Исходный список:\n";
	showList(ls1);
	cout << "Полученный список:\n";
	showList(ls2);
}