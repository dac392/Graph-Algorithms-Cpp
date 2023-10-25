#include "UnionFind.cpp"

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>

class Graph {
public:
    // Constructor
    Graph() = default;

    // Algorithms
    Graph boruvka_mst(){
        UnionFind uf;
        Graph F;
        F.setDirectedOption(false);
        F.setWeightedOption(true);


        int components = getSize();

        uf.init(getVertices());

        while (components > 1){
            std::map<std::string, std::pair<int, std::pair<std::string, std::string>>> safe;
            for (const auto& u : getVertices()){
                for (const auto& edge : getEdges(u)){
                    const std::string& v = edge.first;
                    int weight = edge.second;

                    std::string root1 = uf.findSet(u);
                    std::string root2 = uf.findSet(v);

                    if ( root1 != root2){
                        if(safe[root1].first == 0 || safe[root1].first > weight){
                            safe[root1] = {weight, {u, v}};

                        }
                    }
                }
            }

            for (const auto& pair : safe){
                int weight = pair.second.first;
                const std::string& u = pair.second.second.first;
                const std::string& v = pair.second.second.second;

                std::string set1 = uf.findSet(u);
                std::string set2 = uf.findSet(v);

                if (set1 != set2){
                    F.setEdge(u, v, weight);
                    uf.unionSets(set1, set2);
                    components--;
                }

            }
        }

        return F;
    }


    // Setters
    void setVertices(const std::vector<std::string>& v) {
        vertices = v;

        for(std::string vertex : v){
            addVertex(vertex);
            size++;
        }
    }

    void setEdge(const std::string& vertex1, const std::string& vertex2, int weight) {
        if (!hasVertex(vertex1)) {
            addVertex(vertex1);
            size++;
        }
        if (!hasVertex(vertex2)) {
            addVertex(vertex2);
            size++;
        }

        adjList[vertex1].push_back({vertex2, weight});
        if (!directed) {
            adjList[vertex2].push_back({vertex1, weight});
        }
    }

    void setDirectedOption(bool val) {
        directed = val;
    }
    void setWeightedOption(bool val) {
        weighted = val;
    }

    // Getters
    std::vector<std::string>& getVertices() {
        return vertices;
    }

    std::list<std::pair<std::string, int>>& getEdges(const std::string& vertex){
        return adjList[vertex];

    }

    int getEdgeWeight(const std::string& vertex1, const std::string& vertex2) const {
        if (hasEdge(vertex1, vertex2)) {
            for (const auto& edge : adjList.at(vertex1)) {
                if (edge.first == vertex2) {
                    return edge.second;
                }
            }
        }
        return -1; // Return -1 or some other value to indicate no such edge exists
    }

    int getSize(){
        return size;
    }

    Graph getMST(const std::string& algo_name){
        if (algo_name.find("boruvka") != std::string::npos) {
            return boruvka_mst();
        }else {
            std::cout << "no valid algorithm options were found. Available MST options [ boruvka's, prim's, kruskal's ]" << std::endl;
            return Graph();
        }
    }

    // Utility
    bool hasEdge(const std::string& vertex1, const std::string& vertex2) const {
        if (!hasVertex(vertex1) || !hasVertex(vertex2)) {
            return false;
        }
        for (const auto& pair : adjList.at(vertex1)) {
            if (pair.first == vertex2) {
                return true;
            }
        }
        return false;
    }


    void printGraph() const {
        for (const auto& pair : adjList) {
            std::cout << pair.first << ": ";
            for (const auto& edge : pair.second) {
                std::cout << "(" << edge.first << ", " << edge.second << ") "; // Showing vertex and weight
            }
            std::cout << std::endl;
        }
    }

    bool hasVertex(const std::string& vertex) const {
        return adjList.find(vertex) != adjList.end();
    }

    void addVertex(const std::string& vertex) {
        adjList[vertex] = std::list<std::pair<std::string, int>>();
    }

    bool isWeighted() const {
        return weighted;
    }

    bool isDirected() const {
        return directed;
    }




private:
    std::vector<std::string> vertices;
    std::map<std::string, std::list<std::pair<std::string, int>>> adjList;
    int size = {};
    bool directed = {};
    bool weighted = {};
};
