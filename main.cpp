#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to split a string by a delimiter
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Union-Find (Disjoint Set Union) structure to manage connected components
class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Helper function to convert letter to cost
int letterToCost(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A';  // 'A' -> 0, 'B' -> 1, ..., 'Z' -> 25
    } else if ('a' <= c && c <= 'z') {
        return c - 'a' + 26;  // 'a' -> 26, 'b' -> 27, ..., 'z' -> 51
    }
    return 0;  // Default case
}

// Function to calculate minimum reconstruction cost
int minimumReconstructionCost(int n, const vector<vector<char>>& country, const vector<vector<char>>& build, const vector<vector<char>>& destroy) {
    vector<tuple<int, int, int, string>> edges;  // {cost, u, v, action}
    
    // Convert input matrices to edges
 for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        if (country[i][j] == '1') {
            // Compare destruction cost with keeping the road for free (0 cost)
            int destroyCost = letterToCost(destroy[i][j]);
            edges.push_back({min(destroyCost, 0), i, j, "keep"}); // Consider keeping it
        } else {
            // Consider building the road
            int buildCost = letterToCost(build[i][j]);
            edges.push_back({buildCost, i, j, "build"});
        }
    }
}


    // Sort edges by cost
    sort(edges.begin(), edges.end());

    // Kruskal's algorithm to find the minimum spanning tree
    UnionFind uf(n);
    int totalCost = 0;
    int roadsUsed = 0;

   for (const auto& edge : edges) {
    int cost = get<0>(edge);
    int u = get<1>(edge);
    int v = get<2>(edge);
    string action = get<3>(edge);

    if (uf.find(u) != uf.find(v)) {
        uf.unionSets(u, v);
        totalCost += cost;
        roadsUsed++;
    }
    if (roadsUsed == n-1) break;
}

    return totalCost;
}

int main() {
    string countryStr, buildStr, destroyStr;
    cin >> countryStr >> buildStr >> destroyStr;

    // Split the input strings by commas
    vector<string> countryRows = split(countryStr, ',');
    vector<string> buildRows = split(buildStr, ',');
    vector<string> destroyRows = split(destroyStr, ',');

    int N = countryRows.size();  // Determine the number of cities (N x N matrix)

    vector<vector<char>> country(N, vector<char>(N));
    vector<vector<char>> build(N, vector<char>(N));
    vector<vector<char>> destroy(N, vector<char>(N));

    // Fill matrices from the input strings
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            country[i][j] = countryRows[i][j];
            build[i][j] = buildRows[i][j];
            destroy[i][j] = destroyRows[i][j];
        }
    }

    // Calculate the minimum reconstruction cost
    int result = minimumReconstructionCost(N, country, build, destroy);

    // Output the result
    cout << result << endl;

    return 0;
}
