#include <iostream>
#include <queue>
#include <map>

using namespace std;

class boy {
public:
    string name{};
    queue<int> targets;
    int partner = -1;
};

class girl {
public:
    string name{};
    int *rankings{}; // 越小越优先
    int partner = -1;
};

int main() {
    std::istream::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int N;
    cin >> N;
    boy *boys = new boy[N];
    girl *girls = new girl[N];
    map<string, int> boy_names;
    map<string, int> girl_names;
    string name;
    for (int i = 0; i < N; ++i) {
        cin >> name;
        boys[i].name = name;
        boy_names[name] = i;
    }
    for (int i = 0; i < N; ++i) {
        cin >> name;
        girls[i].name = name;
        girls[i].rankings = new int[N];
        girl_names[name] = i;
    }

    string target_name{};
    int target = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> target_name;
            boys[i].targets.push(girl_names[target_name]);
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> target_name;
            girls[i].rankings[boy_names[target_name]] = j;
        }
    }

    queue<int> boys_queue;
    for (int i = 0; i < N; ++i) {
        boys_queue.push(i);
    }
    while (!boys_queue.empty()) {
        int i = boys_queue.front();
        boys_queue.pop();
        while (!boys[i].targets.empty()) {
            int j = boys[i].targets.front();
            boys[i].targets.pop();
            girl *g = &girls[j];
            if (g->partner == -1) {
                boys[i].partner = j;
                g->partner = i;
                break;
            } else if (g->rankings[i] < g->rankings[g->partner]) {
                boys[g->partner].partner = -1;
                boys_queue.push(g->partner);
                boys[i].partner = j;
                g->partner = i;
                break;
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        cout << boys[i].name << " " << girls[boys[i].partner].name << endl;
    }

    delete[] boys;
    delete[] girls;
    return 0;
}
