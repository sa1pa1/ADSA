#include <iostream> 
#include <vector> 
#include <algorithm>
#include <string> 
#include <unordered_set>

using namespace std;

//translating character to cost 
int ChartoNum (char c){
     if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    return -1; 
}

//Disjoint Set (Union Find structure)
struct UnionFind {
    vector<int> parent;
    vector<int> rank;

    UnionFind(int n){
        parent.resize(n);
        rank.resize(n,0);
        for (int i =0; i < n; i++){
            parent[i] = i;
        }
    }

    int find (int u){
        if (parent[u] != u){ //if u is not its own parent
            parent[u] = find(parent[u]);
            } //recursively find root path. 
            return parent[u];
    }

    bool unite(int u, int v){
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

//edge structure to represent roads 
struct Edge {
    int u, v, cost, type;
    Edge(int u, int v, int cost, int type) : u(u), v(v), cost(cost), type(type) {}
};

//comparison for sorting edges in ascending order 
bool compareEdgeCostAscending(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
};
//comparison for sorting edges in descending order 
bool compareEdgeCostDescending(const Edge& a, const Edge& b) {
    return a.cost > b.cost;
};

//Calculate minimum cost to reconstruct road system

int ReconstructRoad(int N, const vector<string> &country, const vector<string> &build, const vector<string>& destroy){
    vector<Edge> buildEdges, destroyEdges;
    UnionFind uf_initial(N);

    for (int i=0;i<N;i++){
        for (int j = i +1; j <N; j++){
            if (country[i][j] == '1') {
                destroyEdges.push_back(Edge(i, j, ChartoNum(destroy[i][j]), 1));
                uf_initial.unite(i, j);  // Union endpoints of existing roads
            } else {
                buildEdges.push_back(Edge(i, j, ChartoNum(build[i][j]), 2));
            }
        }
    }
    

// Use them in the sort calls
sort(buildEdges.begin(), buildEdges.end(), compareEdgeCostAscending);
sort(destroyEdges.begin(), destroyEdges.end(), compareEdgeCostDescending);


 int totalCost = 0;
UnionFind uf_final(N);

for (const auto& edge : destroyEdges) {
        if (!uf_final.unite(edge.u, edge.v)) {
            totalCost += edge.cost;  
        }
    }

     for (const auto& edge : buildEdges) {
        if (uf_final.unite(edge.u, edge.v)) {
            totalCost += edge.cost;  
        }
    }

    return totalCost;
}

//Parsing input into main, splitting of comma and space
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
    result.push_back(temp); 
    return result;
}


int main() {
    string input1, input2, input3;

    cin >> input1 >> input2 >> input3;

    vector<string> country = split(input1, ',');
    vector<string> build = split(input2, ',');
    vector<string> destroy = split(input3, ',');

    int N = country.size();

    int result = ReconstructRoad(N, country, build, destroy);
    cout << result << endl;

    return 0;
}