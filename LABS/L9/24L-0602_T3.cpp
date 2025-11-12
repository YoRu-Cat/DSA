#include <iostream>
using namespace std;

const int MAX = 10;
const int MAX_EDGES = 20;

class Stack {
    int items[MAX];
    int topIndex;
public:
    Stack() {
        topIndex = -1;
    }

    bool isEmpty() {
        return topIndex == -1;
    }

    bool isFull() {
        return topIndex == MAX - 1;
    }

    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow" << endl;
            return;
        }
        items[++topIndex] = x;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return items[topIndex--];
    }

    int top() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return items[topIndex];
    }
};

struct Edge {
    int to;
    int next;
};

class DFSsta {
    int head[MAX];
    Edge edges[MAX_EDGES];
    int edgeCount;
    int vertexCount;

public:
    DFSsta(int v) : vertexCount(v), edgeCount(0) {
        for (int i = 0; i < MAX; i++)
            head[i] = -1;
    }

    void addEdge(int u, int v) {
        edges[edgeCount].to = v;
        edges[edgeCount].next = head[u];
        head[u] = edgeCount++;
    }

    void DFS(int start) {
        bool visited[MAX] = { false };
        Stack stack;
        stack.push(start);

        while (!stack.isEmpty()) {
            int u = stack.pop();
            if (!visited[u]) {
                visited[u] = true;
                cout << u << " ";

                int neighbors[MAX];
                int count = 0;
                for (int i = head[u]; i != -1; i = edges[i].next) {
                    if (!visited[edges[i].to]) {
                        neighbors[count++] = edges[i].to;
                    }
                }
                for (int i = count - 1; i >= 0; i--) {
                    stack.push(neighbors[i]);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    DFSsta dfs(5);

    dfs.addEdge(0, 1);
    dfs.addEdge(1, 0);

    dfs.addEdge(0, 2);
    dfs.addEdge(2, 0);

    dfs.addEdge(1, 3);
    dfs.addEdge(3, 1);

    dfs.addEdge(1, 4);
    dfs.addEdge(4, 1);

    cout << "DFS traversal starting from vertex 0: ";
    dfs.DFS(0);

    return 0;
}
