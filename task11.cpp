#include <iostream>
#include <queue>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

int vertexes_bfs = 0;
void bfs(vector<vector<int>>& adj, int s) {
    queue<int> q;
    vector<bool> visited(adj.size(), false);
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                vertexes_bfs++;
                q.push(x);
            }
        }
    }
}

int vertexes_dfs = 0;
void dfs(vector<vector<int>>& adj, vector<bool>& visited, int s) {
    visited[s] = true;

    cout << s << " ";
    vertexes_dfs++;

    for (int i : adj[s]) {
        if (visited[i] == false) {
            dfs(adj, visited, i);
        }
    }
}

int main() {
    vector <vector<int>> adj;
    vector<bool> visited;
    cout << "Enter amount of vertexes: ";
    int n; cin >> n;
    adj.resize(n + 1);
    visited.resize(n + 1);
    cout << "Enter start vertex, end vertex in format: start end (All vertexes are values from 1 to " << n << ")\nEnter -1 to continue\n";
    while (true) {
        int start, end;
        cin >> start;
        if (start == -1) {
            break;
        }
        if (start <= 0 || start >= n + 1) {
            cout << "Value of start is incorrect.\n";
            continue;
        }
        cin >> end;
        if (end <= 0 || end >= n + 1) {
            cout << "Value of endpoint is incorrect.\n";
            continue;
        }

        adj[start].push_back(end);
        adj[end].push_back(start);
    }

    int entryPoint;
    cin >> entryPoint;
    cout << "BFS\nVisited vertexes: ";
    auto st = chrono::high_resolution_clock::now();

    bfs(adj, entryPoint);

    auto en = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = en - st;
    cout << "\nAmount of visited vertexes: " << vertexes_bfs << "\n";
    cout << "time: " << duration.count() << "\n";

    double time1 = duration.count();
    this_thread::sleep_for(chrono::seconds(1));

    cout << "\nDFS\nVisited vertexes: ";
    st = chrono::high_resolution_clock::now();

    dfs(adj, visited, entryPoint);

    en = chrono::high_resolution_clock::now();
    duration = en - st;
    cout << "\nAmount of visited vertexes: " << vertexes_bfs << "\n";
    cout << "time: " << duration.count() << "\n";
    double time2 = duration.count();

    cout << "BFS time to DFS = " << time1 / time2 << "\n";

}