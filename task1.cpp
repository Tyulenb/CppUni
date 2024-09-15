#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>

using namespace std;

void merge(vector<set<int>>& Sets);
void unificate(vector<set<int>>& Sets);
void intersect(vector<set<int>>& Sets);

int main() {
	setlocale(LC_ALL, "Russian");
	vector<set<int>> Sets;
	cout << "Введите количество множеств\n";
	int amount_of_sets; cin >> amount_of_sets; 
	for (int i = 0; i < amount_of_sets; i++) {
		set<int> s;
		cout << "Введите количество элементов множества " << i + 1 << "\n";
		int size_of_set; cin >> size_of_set;
		for (int i = 0; i < size_of_set; i++) {
			cout << "Введите элемент множества " << i + 1 << "/" << size_of_set << "\n";
			int elem; cin >> elem;
			s.insert(elem);
		}
		Sets.push_back(s);
	}

	merge(Sets);
	unificate(Sets);
	intersect(Sets);

	system("pause");
}

void merge(vector<set<int>>& Sets) {
	multiset<int> result;
	for (int i = 0; i < Sets.size(); i++) {
		for (int elem : Sets[i]) {
			result.insert(elem);
		}
	}
	cout << "Результат выполнения операции 'слияния' множеств.\n";
	for (int elem : result) {
		cout << elem << " ";
	}
	cout << "\n";
}

void unificate(vector<set<int>>& Sets) {
	set<int> result;
	for (int i = 0; i < Sets.size(); i++) {
		for (int elem : Sets[i]) {
			result.insert(elem);
		}
	}
	cout << "Результат выполнения операции 'объединения' множеств.\n";
	for (int elem : result) {
		cout << elem << " ";
	}
	cout << "\n";
}

void intersect(vector<set<int>>& Sets) {
	set<int> result;
	int max_length = -1;
	int max_length_set_ind = 0;
	for (int i = 0; i < Sets.size(); i++) {
		if (Sets[i].size() > max_length) {
			max_length_set_ind = i;
			max_length = Sets[i].size();
		}
	}
	for (int elem : Sets[max_length_set_ind]) {
		int count = 0;
		for (int i = 0; i < Sets.size(); i++) {
			if (Sets[i].count(elem) != 0) {
				count++;
			}
			else {
				break;
			}
		}
		if (count == Sets.size()) {
			result.insert(elem);
		}
	}
	cout << "Результат выполнения операции 'пересечения' множеств.\n";
	for (int elem : result) {
		cout << elem << " ";
	}
	cout << "\n";
}