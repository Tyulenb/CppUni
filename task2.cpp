#include <iostream>

using namespace std;

class Graph {
private:
    int n;
    int g[100][100];
public:
    Graph(int x) { //Конструктор
        n = x;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
            }
        }
    }
    void displayAdjacencyMatrix() { //Вывод матрицы смежности
        cout << "\n\n Adjacency Matrix:";

        for (int i = 0; i < n; i++) {
            cout << "\n";
            for (int j = 0; j < n; j++) {
                cout << " " << g[i][j];
            }
        }
        cout << "\n";
    }
    void addEdge(int x, int y) {
        if ((x >= n) || (y >= n)) {
            cout << "Vertex does not exists!";
        }
        if (x == y) {
            cout << "Same Vertex!";
        }
        else {
            g[y][x] = 1;
            g[x][y] = 1;
        }
    }
    void addVertex() {
        n++;
        int i;

        for (int i = 0; i < n; i++) {
            g[i][n - 1] = 0;
            g[n - 1][i] = 0;
        }
    }
    void removeVertex(int x) {
        if (x >= n) {
            cout << "\nVertex is not present!";
            return;
        }
        else {
            int i;
            while (x < n) {
                for (i = 0; i < n; i++) {
                    g[i][x] = g[i][x + 1];
                }
                for (i = 0; i < n; i++) {
                    g[x][i] = g[x + 1][i];
                }
                x++;
            }
            n--;
        }
    }
    void removeEdge(int x, int y) {
        if ((x >= n) || (y >= n)) {
            cout << "Vertex does not exists!";
        }
        if (x == y) {
            cout << "Same Vertex!";
        }
        else {
            g[y][x] = 0;
            g[x][y] = 0;
        }
    }
    Graph UniteGraph(Graph &g2) {
        int mn;
        if (n < g2.n) {
            mn = n;
            for (int i = 0; i < mn; i++) {
                for (int j = 0; j < mn; j++) {
                        g2.g[i][j] |= g[i][j];
                }
            }
            return g2;
        }
        else {
            mn = g2.n;
            for (int i = 0; i < mn; i++) {
                for (int j = 0; j < mn; j++) {
                    if (g2.g[i][j] != 0) {
                        g[i][j] |= g2.g[i][j];
                    }
                }
            }
            return *this;
        }
    }
    Graph IntersectGraph(Graph &g2) {
        int mn;
        if (n < g2.n) {
            mn = n;
            for (int i = 0; i < mn; i++) {
                for (int j = 0; j < mn; j++) {
                    g[i][j] &= g2.g[i][j];
                }
            }
            return *this;
        }
        else {
            mn = g2.n;
            for (int i = 0; i < mn; i++) {
                for (int j = 0; j < mn; j++) {
                    g2.g[i][j] &= g[i][j];
                }
            }
            return g2;
        }
    }
};

void editGraph(Graph& g);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "\nВведите количество вершин графа g1: ";
    int n; cin >> n;
    cout << "\nВведите количество вершин графа g2: ";
    int m; cin >> m;

    Graph g1 = Graph(n);
    Graph g2 = Graph(m);
    Graph g3 = Graph(1);
    while (true) {
        cout << "\n1.Редактировать граф g1\n2.Редактировать граф g2\n3.Пересечение графов\n4.Объединение графов\n0.Завершить\n";
        int switch_on; cin >> switch_on;
        switch (switch_on)
        {
        case 1:
            g1.displayAdjacencyMatrix();
            editGraph(g1);
            break;
        case 2:
            g2.displayAdjacencyMatrix();
            editGraph(g2);
            break;
        case 3:
            g1.displayAdjacencyMatrix();
            g2.displayAdjacencyMatrix();
            g3 = g1.IntersectGraph(g2);
            g3.displayAdjacencyMatrix();
            break;
        case 4:
            g1.displayAdjacencyMatrix();
            g2.displayAdjacencyMatrix();
            g3 = g1.UniteGraph(g2);
            g3.displayAdjacencyMatrix();
            break;
        default:
            return 0;
            break;
        }
    }
}

void editGraph(Graph &g) {
    while (true) {
        cout << "\n1.Добавить ребро\n2.Удалить ребро\n3.Добавить вершину\n4.Удалить вершину\n0.Завершить\n";
        int sw; cin >> sw;
        int v1, v2;
        switch (sw)
        {
        case 1:
            cout << "\nВведите 2 различных вершины от 1 до n: ";
            cin >> v1 >> v2;
            g.addEdge(v1-1, v2-1);
            g.displayAdjacencyMatrix();
            break;
        case 2:
            cout << "\nВведите 2 различных существующих вершины от 1 до n: ";
            cin >> v1 >> v2;
            g.removeEdge(v1-1, v2-1);
            g.displayAdjacencyMatrix();
            break;
        case 3:
            g.addVertex();
            g.displayAdjacencyMatrix();
            break;
        case 4:
            cout << "\nВведите существующую вершину от 1 до n: ";
            cin >> v1;
            g.removeVertex(v1-1);
            g.displayAdjacencyMatrix();
            break;
        default:
            return;
        }
    }
}