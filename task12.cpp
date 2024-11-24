#include <iostream>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

mutex mute;
vector<int> found;
vector<int> big_data;

void number_search(int start, int end, int num) {
	for (int i = start; i < end; i++) {
		if (big_data[i] == num) {
			mute.lock();
			found.push_back(i);
			mute.unlock();
		}
	}
}

int main()
{
	srand(123213);
	int size = 100000000;
	for (long long i = 0; i < size; i++) {
		big_data.push_back(rand()% 2147483647 +1);
	}

	cout << "Enter the number you want to find in the BIG DATA\n";
	int num; cin >> num;

	thread t1(number_search, 0, size/4, num);
	thread t2(number_search, size/4, size/2, num);
	thread t3(number_search, size / 2, size/4*3, num);
	thread t4(number_search, size / 4 * 3, size, num);
	auto st = chrono::high_resolution_clock::now();
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	cout << found.size() << "\n";
	auto en = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = en - st;
	cout << "It took " << duration.count() << " seconds\n";
}
