#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <chrono>
#include <thread>

using namespace std;

int dijkstra(vector <vector<pair<int, int>>> &adj, int start, int end, int n) {
    vector<int> distance(n + 1);
    vector<bool> processed(n + 1);
    for (int i = 1; i <= n; i++) {
        distance[i] = int(1e9);
    }
    distance[start] = 0;

    priority_queue<pair<int, int>> q;
    q.push({ 0, start });

    while (!q.empty()) {
        int a = q.top().second;
        q.pop();
        if (processed[a]) {
            continue;
        }
        
        processed[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (distance[a] + w < distance[b]) {
                distance[b] = distance[a] + w;
                q.push({ -distance[b],b });
            }
        }
    }
    return distance[end];
}

int bellmanFord(vector<tuple<int, int, int>> &edges, int start, int end, int n) {
    vector<int> distance(n + 1);
    for (int i = 1; i <= n; i++) {
        distance[i] = int(1e9);
    }

    distance[start] = 0;
    for (int i = 1; i < n; i++) {
        for (auto e : edges) {
            int st, en, len;
            tie(st, en, len) = e;
            distance[en] = min(distance[en], distance[st] + len);
        }
    }

    return distance[end];
}

int main()
{
    vector<tuple<int, int, int>> edges; // For Bellman-Ford
    vector <vector<pair<int, int>>> adj; // For Dijkstra

    cout << "Enter amount of vertexes: ";
    int n; cin >> n;
    
    adj.resize(n+1);
    cout << "Enter start vertex, end vertex and length in format: start end length (All vertexes are values from 1 to " << n << ") length can be only positive\nEnter -1 to continue\n";
    while (true) {
        int start, end, len;
        cin >> start;
        if (start == -1) {
            break;
        }
        if (start <= 0 || start >= n + 1) {
            cout << "Value of start is incorrect.\n";
            continue;
        }
        cin >> end >> len;
        if (start <= 0 || start >= n + 1) {
            cout << "Value of endpoint is incorrect.\n";
            continue;
        }
        if (len <= 0) {
            cout << "Value of length is incorrect.\n";
            continue;
        }
        adj[start].push_back({end, len});
        adj[end].push_back({start, len});

        edges.push_back({start, end, len});
        edges.push_back({end, start, len});
    }

    while (true) {
        cout << "\nEnter two vertex to find shortest path between them: \n";
        int first, second; cin >> first >> second;

        auto st = chrono::high_resolution_clock::now();
        cout << "Dikstra shortest path is: " << dijkstra(adj, first, second, n) << "\n";
        auto en = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = en - st;
        cout << "Dijkstra time is: " << duration.count() << "\n";

        double time1 = duration.count();
        this_thread::sleep_for(chrono::seconds(1));

        st = chrono::high_resolution_clock::now();
        cout << "Bellman-Ford shortest path: " << bellmanFord(edges, first, second, n) << "\n";
        en = chrono::high_resolution_clock::now();
        duration = en - st;
        cout << "Bellman-Ford time is: " << duration.count() << "\n";
        double time2 = duration.count();

        cout << "Bellman-Ford time to Dijkstra time = " << time2 / time1 << "\n";
    }

}

