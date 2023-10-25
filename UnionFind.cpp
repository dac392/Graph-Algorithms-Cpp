#include <map>
#include <vector>
#include <string>

class UnionFind {
    std::map<std::string, std::string> parent;
    std::map<std::string, int> rank;

public:

    void init(std::vector<std::string>& vertices){
        for(const auto& vertex : vertices){
            makeSet(vertex);
        }
    }

    void makeSet(const std::string& v) {
        parent[v] = v;
        rank[v] = 0;
    }

    std::string findSet(const std::string& v) {
        if (v == parent[v])
            return v;
        return parent[v] = findSet(parent[v]);
    }

    void unionSets(const std::string& a, const std::string& b) {
        std::string rootA = findSet(a);
        std::string rootB = findSet(b);
        if (rootA != rootB) {
            if (rank[rootA] < rank[rootB])
                std::swap(rootA, rootB);
            parent[rootB] = rootA;
            if (rank[rootA] == rank[rootB])
                rank[rootA]++;
        }
    }
};
