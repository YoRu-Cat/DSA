#include <iostream>
using namespace std;

const int MAX = 10;

void bfs(int v, int edges[][2], int edgeCount, int src) {
    int adj[MAX][MAX] = { 0 };

    for (int i = 0; i < edgeCount; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        adj[a][b] = 1;
        adj[b][a] = 1;
    }

    bool visited[MAX] = { false };
    int queue[MAX];
    int front = 0, rear = 0;

    visited[src] = true;
    queue[rear++] = src;

    while (front < rear) {
        int curr = queue[front++];
        cout << curr << " ";

        for (int i = 0; i < v; i++) {
            if (adj[curr][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    cout << endl;
}

int main() {
    int v = 4;
    int edges[][2] = { {0,1}, {0,2}, {1,3} };
    int edgeCount = sizeof(edges) / sizeof(edges[0]);
    int src = 0;

    cout << "BFS traversal starting from vertex " << src << ": ";
    bfs(v, edges, edgeCount, src);

    return 0;
}
