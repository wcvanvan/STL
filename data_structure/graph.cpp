#include <iostream>
#include <vector>
#include <algorithm>
#include "priority_queue.hpp"

#define MAX_VALUE 1000000000

using std::vector;

using namespace std;

class Graph {
public:
    int V, E;

    class Pair;

    class Vertex;

    std::vector<Pair *> *adjacency_list;
    Vertex *vertices{};

    Graph(int V_, int E_) : V(V_), E(E_) {
        adjacency_list = new std::vector<Pair *>[V];
    };

    ~Graph() = default;

    void add_edge(int from, int to, int weight, bool is_directed) const;

    int shortest_path(int from, int to);

    int minimum_spanning_tree();
};

class Graph::Pair {
public:
    int to{};
    int weight = 1;

    bool operator<(Pair &p) const {
        if (this->weight < p.weight) { return true; }
        else { return false; }
    }

    friend std::ostream& operator << (std::ostream& os, Graph::Pair& pair) {
        os << pair.weight;
        return os;
    }

    Pair(int _to, int _weight) : to(_to), weight(_weight) {}
};


class Graph::Vertex {
public:
    int key{};
    int distance{};
    int best_extension{MAX_VALUE};
    int parent_path{};

    Vertex() = default;

    bool operator<(Graph::Vertex &v) {
        if (this->distance < v.distance) { return true; }
        else { return false; }
    }

    explicit Vertex(int _key, int _distance) : key(_key), distance(_distance) {}
};

/*
 * returns the length of the shortest path from "from" to "to"
 * using Dijkstra's Algorithm
 */
int Graph::shortest_path(int from, int to) {
    auto *priority_queue = new PriorityQueue<Vertex>();
    vertices = new Vertex[V];
    auto *ghost_vertices = new Vertex[V];
    bool *ghost_out = new bool[V]{false};
    for (int vertex_idx = 0; vertex_idx < V; ++vertex_idx) {
        if (vertex_idx == from) {
            vertices[vertex_idx].distance = 0;
        } else {
            vertices[vertex_idx].distance = MAX_VALUE;
        }
        vertices[vertex_idx].key = vertex_idx;
        priority_queue->insert(&vertices[vertex_idx]);
    }
    for (int vertex_idx = 0; vertex_idx < V; ++vertex_idx) {
        while (ghost_out[priority_queue->top()->key]) {
            priority_queue->delete_top();
        }
        int shortest_vertex = priority_queue->top()->key;
        for (Pair *pair: adjacency_list[shortest_vertex]) {
            if (vertices[pair->to].distance > vertices[shortest_vertex].distance + pair->weight) {
                vertices[pair->to].distance = vertices[shortest_vertex].distance + pair->weight;
                vertices[pair->to].parent_path = shortest_vertex;
                ghost_vertices[pair->to].key = pair->to;
                priority_queue->insert(&ghost_vertices[pair->to]);
            }
        }
        priority_queue->delete_top();
    }
    int answer = vertices[to].distance;
    if (answer == MAX_VALUE) { answer = -1; }
    delete[] vertices;
    delete[] ghost_vertices;
    delete priority_queue;
    vertices = nullptr, priority_queue = nullptr;
    return answer;
}

void Graph::add_edge(int from, int to, int weight, bool is_directed) const {
    if (!is_directed) {
        adjacency_list[to].push_back(new Pair(from, weight));
    }
    adjacency_list[from].push_back(new Pair(to, weight));
}

int Graph::minimum_spanning_tree() {
    int total_length{};
    vertices = new Vertex[V];
    // find the shortest edge
    int vertex_a{0}, vertex_b{1};
    int weight = adjacency_list[0][1]->weight;
    for (int from_vertex = 0; from_vertex < V; ++from_vertex) {
        for (int to_vertex = 0; to_vertex < adjacency_list[from_vertex].size(); to_vertex++) {
            if (from_vertex == to_vertex) {
                continue;
            }
            if (adjacency_list[from_vertex][to_vertex]->weight < weight) {
                weight = adjacency_list[from_vertex][to_vertex]->weight;
                vertex_a = from_vertex;
                vertex_b = to_vertex;
            }
        }
    }
    vertices[vertex_b].best_extension = adjacency_list[vertex_a][vertex_b]->weight;
    vertices[vertex_a].best_extension = vertices[vertex_b].best_extension;
    total_length += vertices[vertex_b].best_extension;
    vertices[vertex_b].parent_path = vertex_a;
    vector<int> S;
    S.push_back(vertex_a);
    S.push_back(vertex_b);
    auto *priority_queue = new PriorityQueue<Pair>;
    for (auto &pair: adjacency_list[vertex_a]) {
        if (vertices[pair->to].best_extension == MAX_VALUE) {
            vertices[pair->to].best_extension = pair->weight;
            priority_queue->insert(pair);
            vertices[pair->to].parent_path = vertex_a;
        } else if (pair->weight < vertices[pair->to].best_extension) {
            vertices[pair->to].parent_path = vertex_a;
            vertices[pair->to].best_extension = pair->weight;
        }
    }
    for (auto &pair: adjacency_list[vertex_b]) {
        if (vertices[pair->to].best_extension == MAX_VALUE) {
            vertices[pair->to].best_extension = pair->weight;
            priority_queue->insert(pair);
            vertices[pair->to].parent_path = vertex_b;
        } else if (pair->weight < vertices[pair->to].best_extension) {
            vertices[pair->to].parent_path = vertex_b;
            vertices[pair->to].best_extension = pair->weight;
        }
    }
    for (int idx = 2; idx < V; ++idx) {
        while (std::find(S.begin(), S.end(), priority_queue->top()->to) != S.end()) {
            priority_queue->delete_top();
        }
        int top_idx = priority_queue->top()->to;
        //cout << top_idx << " " << priority_queue->top()->weight << endl;
        total_length += priority_queue->top()->weight;
        priority_queue->delete_top();
        S.push_back(top_idx);
        for (auto &pair: adjacency_list[top_idx]) {
            if (pair->weight < vertices[pair->to].best_extension) {
                vertices[pair->to].best_extension = pair->weight;
                vertices[pair->to].parent_path = top_idx;
            }
            priority_queue->insert(pair);
        }
    }
    return total_length;
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;
    Graph graph(vertices, edges);
    for (int i = 0; i < edges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.add_edge(from, to, weight, false);
    }
    cout << graph.minimum_spanning_tree() << endl;
}