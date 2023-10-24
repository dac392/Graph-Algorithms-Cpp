#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>

class Graph {
public:
    // Constructor
    Graph() = default;


    // Setters
    void setVertices(const std::vector<std::string>& v) {
        vertices = v;

        for(std::string vertex : v){
            addVertex(vertex);
        }
    }

    void setEdge(const std::string& vertex1, const std::string& vertex2, int weight) {
        if (!hasVertex(vertex1)) {
            addVertex(vertex1);
        }
        if (!hasVertex(vertex2)) {
            addVertex(vertex2);
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
    const std::vector<std::string>& getVertices() const {
        return vertices;
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
    bool directed;
    bool weighted;
};
