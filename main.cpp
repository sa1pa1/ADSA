#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


int charToCost(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' +26 ;
    return -1; // Invalid character 
}

// Disjoint Set
struct UnionFind {
    vector<int> parent, rank;

    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u) parent[u] = find(parent[u]);
        return parent[u];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
            return true;
        }
        return false;
    }
};

// Edge structure (storing informationa bout each road)
struct Edge {
    int u, v, cost, type; 
    Edge(int u, int v, int cost, int type) : u(u), v(v), cost(cost), type(type) {}
};

// Minimum cost to reconstruct
int reconstructRoads(int N, const vector<string>& country, const vector<string>& build, const vector<string>& destroy) {
    vector<Edge> edges;
  UnionFind uf(N);
    
    // Handle existing roads
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (country[i][j] == '1') {
                // Existing road, consider destroying
                int destroyCost = charToCost(destroy[i][j]);
                edges.push_back(Edge(i, j, destroyCost, 1)); // destroy type
                uf.unite(i, j); // Mark these as already connected in the union-find
            }
        }
    }

    // Add roads that can be built
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (country[i][j] == '0') {
                // No road exists, consider building
                int buildCost = charToCost(build[i][j]);
                edges.push_back(Edge(i, j, buildCost, 2)); // build type
            }
        }
    }

    // Sort edges: first by cost, then prioritize build over destroy
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        if (a.cost == b.cost) {
            return a.type < b.type; // Prefer build (2) over destroy (1) if costs are equal
        }
        return a.cost < b.cost;
    });

    int totalCost = 0;

    // Process edges and form the MST
    for (const auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            totalCost += edge.cost;
        }
    }

    return totalCost;
}

vector<string> split(const string &str, char delimiter) {
    vector<string> result;
    string temp;
    for (char ch : str) {
        if (ch == delimiter) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    result.push_back(temp);  // add the last part
    return result;
}

int main() {
    string countryInput, buildInput, destroyInput;

    cin >> countryInput >> buildInput >> destroyInput;

    vector<string> country = split(countryInput, ',');
    vector<string> build = split(buildInput, ',');
    vector<string> destroy = split(destroyInput, ',');

    int N = country.size();

    int result = reconstructRoads(N, country, build, destroy);
    cout << result << endl;

    return 0;
}