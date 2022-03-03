#include <iostream>
#include <vector>
#include <algorithm>
#include "priority_queue.hpp"
#include <stack>

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

    void add_edge(int from, int to, int weight, bool is_directed = false) const;

    int shortest_path(int from, int to);

    int minimum_spanning_tree();

    int strongly_connected_components();

    void dfs(int vertex_idx, bool *visited, stack<int> *s = nullptr, stack<int> *order = nullptr, vector<int> *v = nullptr);
};

class Graph::Pair {
public:
    int to{};
    int weight = 1;

    bool operator<(Pair &p) const {
        if (this->weight < p.weight) { return true; }
        else { return false; }
    }

    friend std::ostream &operator<<(std::ostream &os, Graph::Pair &pair) {
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

    bool operator<(Graph::Vertex &v) const {
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

long long Graph::minimum_spanning_tree() {
    long long total_length{};
    vertices = new Vertex[V];
    // find the shortest edge
    long long vertex_a{0}, vertex_b{};
    long long weight = adjacency_list[0][0]->weight;
    vertex_b = adjacency_list[0][0]->to;
    Edge *shortest_edge = adjacency_list[0][0];
    for (long long from_vertex = 0; from_vertex < V; ++from_vertex) {
        for (Edge *edge: adjacency_list[from_vertex]) {
            if (edge->weight < weight) {
                weight = edge->weight;
                vertex_a = from_vertex;
                vertex_b = edge->to;
                shortest_edge = edge;
            }
        }
    }
    vertices[vertex_b].best_extension = shortest_edge->weight;
    vertices[vertex_a].best_extension = shortest_edge->weight;
    total_length += shortest_edge->weight;
    vertices[vertex_b].parent_path = vertex_a;
    vertices[vertex_a].parent_path = vertex_b;
    vector<long long> S(V);
    bool *in_S = new bool[V]{};
    S.push_back(vertex_a);
    S.push_back(vertex_b);
    in_S[vertex_a] = true, in_S[vertex_b] = true;
    priority_queue<Edge *, vector<Edge *>, edge_cmp> pq;
    for (auto &edge: adjacency_list[vertex_a]) {
        if (edge->weight < vertices[edge->to].best_extension) {
            vertices[edge->to].best_extension = edge->weight;
            pq.push(edge);
            vertices[edge->to].parent_path = vertex_a;
        }
    }
    for (auto &edge: adjacency_list[vertex_b]) {
        if (edge->weight < vertices[edge->to].best_extension) {
            vertices[edge->to].best_extension = edge->weight;
            pq.push(edge);
            vertices[edge->to].parent_path = vertex_b;
        }
    }
    while (!pq.empty()) {
        bool exist{}, empty{};
        long long top_idx = pq.top()->to;
        if (in_S[top_idx]) {
            pq.pop();
            continue;
        }
        long long weight = pq.top()->weight;
        pq.pop();
//        cout << top_idx+1 << " " << priority_queue.front().weight << endl;
        total_length += weight;
        S.push_back(top_idx);
        in_S[top_idx] = true;
        for (auto &edge: adjacency_list[top_idx]) {
            if (edge->weight < vertices[edge->to].best_extension) {
                vertices[edge->to].best_extension = edge->weight;
                vertices[edge->to].parent_path = top_idx;
                pq.push(edge);
            }
        }
    }
    return total_length;
}

/*
 * return the number of SCC
 */
int Graph::strongly_connected_components() {
    int number_scc{};
    vertices = new Vertex[V];
    bool *visited = new bool[V]{};
    Graph graph_reverse(V, E);
    for (int from_vertex_idx = 0; from_vertex_idx < V; ++from_vertex_idx) {
        for (Pair *pair : adjacency_list[from_vertex_idx]) {
            graph_reverse.add_edge(pair->to, from_vertex_idx, pair->weight, true);
        }
    }
    stack<int> s;
    stack<int> order;
    for (int vertex_idx = 0; vertex_idx < V; ++vertex_idx) {
        if (visited[vertex_idx]) { continue; }
        graph_reverse.dfs(vertex_idx, visited, &s, &order);
    }
    fill(visited, visited + V, 0);
    vector<vector<int>> SCCs;
    while (!order.empty()) {
        int start_vertex_idx = order.top();
        order.pop();
        if (visited[start_vertex_idx]) { continue; }
        vector<int> v;
        SCCs.push_back(v);
        dfs(start_vertex_idx, visited, nullptr, nullptr, &v);
        number_scc++;
        //cout << number_scc << ": " << start_vertex_idx+1 << endl;
    }
    auto *degrees = new int[SCCs.size() * 2];
    //for (int vertex_idx = 0; vertex_idx < V; ++vertex_idx) {
    //    for (Pair *pair : adjacency_list[vertex_idx]) {
    //        for (int scc_idx = 0; scc_idx < SCCs.size(); ++scc_idx) {
    //            if (std::find(SCCs[scc_idx].begin(), SCCs[scc_idx].end(), vertex_idx) != SCCs[scc_idx].end() && std::find(SCCs[scc_idx].begin(), SCCs[scc_idx].end(), pair->to) != SCCs[scc_idx].end()) {
    //                degrees[scc_idx*2 + 1]++;
    //            }
    //        }
    //    }
    //}
    delete[] vertices;
    delete[] visited;
    delete[] degrees;
    return number_scc;
}

void Graph::dfs(int vertex_idx, bool *visited, stack<int> *s, stack<int> *order, vector<int> *v) {
    if (s != nullptr) {
        s->push(vertex_idx);
    }
    if (v != nullptr) {
        v->push_back(vertex_idx);
    }
    visited[vertex_idx] = true;
    for (Pair *pair: adjacency_list[vertex_idx]) {
        if (visited[pair->to]) { continue; }
        dfs(pair->to, visited, s, order);
    }
    if (order != nullptr) {
        order->push(s->top());
        s->pop();
    }
}

int main() {
    std::istream::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int cities, roads;
    cin >> cities >> roads;
    Graph graph(cities, roads);
    for (int road = 0; road < roads; ++road) {
        int vertex_a_num, vertex_b_num;
        cin >> vertex_a_num >> vertex_b_num;
        vertex_a_num--, vertex_b_num--;
        graph.add_edge(vertex_a_num, vertex_b_num, 0, true);
    }
    cout << graph.strongly_connected_components() << endl;
}