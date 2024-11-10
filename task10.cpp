// task10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <random>

using namespace std;

vector<vector<pair<int, int>>> adjacent;

int shortest_path(int start, int end) {
    int n = adjacent.size();
    vector<int> distance(n + 1);
    vector<bool> procesed(n + 1);
    for (int i = 1; i <= n; i++) {
        distance[i] = int(1e9);
    }
    distance[start] = 0;

    priority_queue<pair<int, int>> q;
    q.push({ 0, start });
    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (procesed[a]) {
            continue;
        }
        procesed[a] = true;
        for (auto u : adjacent[a]) {
            int b = u.first, w = u.second;
            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({ -distance[b], b });
            }
        }
    }
    return distance[end];
}

void print_map() {
    for (int i = 0; i < adjacent.size(); i++) {
        for (int j = 0; j < adjacent[i].size(); j++) {
            cout << i << " -> " << adjacent[i][j].first << " length: " << adjacent[i][j].second << "\n";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(0));
    cout << "Enter the map of the game world\n";
    cout << "Enter the amount of locations: \n";
    int locations; cin >> locations;
    
    adjacent.resize(locations+1);

    for (int i = 0; i < locations; i++) {
        vector<pair<int, int>> pathes(locations, pair<int,int>{0,0});
        while (true) {
            cout << "Enter number of location which can be reached from " << (i + 1) << "(number from 1 to " << locations << ")\n";
            cout << "Enter 0 to enter next location\n";

            int num; cin >> num;

            if (num == (i + 1)) {
                cout << "You are already in " << num << " choose other location\n";
                continue;
            }
            else if (num > locations || num < 0) {
                cout << "Invalid location.\n";
                continue;
            }
            else if (num == 0) {
                break;
            }
            else {
                int len_of_path;
                while (true) {
                    cout << "What will be on the path to the location " << num <<"\n";
                    cout << "1.Straight road\n2.City\n3.Lake\n4.Mountain\n";

                    int choice; cin >> choice;
                    if (choice == 1) {
                        len_of_path = rand() % 2 + 1;
                        break;
                    }
                    else if (choice == 2) {
                        len_of_path = 3 + rand() % 3;
                        break;
                    }
                    else if (choice == 3) {
                        len_of_path = 6 + rand() % 2;
                        break;
                    }
                    else if (choice == 4) {
                        len_of_path = 8 + rand() % 3;
                        break;
                    }
                    else {
                        cout << "Incorrect input. Try again\n";
                        continue;
                    }
                }
                pathes[num-1] = { num, len_of_path };
            }
        }
        for (int j = 0; j < locations; j++) {
            if (pathes[j].first != 0) {
                adjacent[i+1].push_back(pathes[j]);
                adjacent[pathes[j].first].push_back({ i + 1, pathes[j].second }); //both ways
            }
        }
        for (int j = 0; j < locations; j++) {
            pathes[j] = { 0,0 };
        }
    }

    while (true) {
        print_map();
        cout << "Enter two locations to find shortest path between them\n";
        int start, end;
        cout << "Enter start point:\n";
        cin >> start;
        cout << "Enter end point:\n";
        cin >> end;
        cout << "\nThe shortest path is: " << shortest_path(start, end) << "\n";
    }
}