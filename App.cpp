#include "Graph.cpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>


std::vector<std::string> splitAndTrim(const std::string &line) {
    std::vector<std::string> tokens;
    std::istringstream stream(line);
    std::string token;

    // Split the string based on commas
    while (std::getline(stream, token, ',')) {
        // Remove whitespaces
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
        tokens.push_back(token);
    }
    
    return tokens;
}

void readInput(Graph &graph, const std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    std::string line;
    
    // Reading graph's weighted property
    std::getline(file, line);
    graph.setWeightedOption(line == "weighted");

    // Reading graph's directedness property
    std::getline(file, line);
    graph.setDirectedOption(line == "directed");

    // Reading vertices
    std::getline(file, line);
    graph.setVertices(splitAndTrim(line));

    // Reading edges
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string src, dest;
        int weight = 1; // Default weight

        iss >> src >> dest;
        
        if (graph.isWeighted()) {
            if (iss >> weight) {
                // successfully extracted weight
            } else {
                std::cerr << "Error reading weight for edge: " << src << " - " << dest << std::endl;
                continue; // Skip this line/edge
            }
        }
        
        graph.setEdge(src, dest, weight);
    }


    file.close();

}


int main() {

    std::string filename;

    // Prompt the user for input
    std::cout << "Please enter the complete filename: ";
    std::getline(std::cin, filename);  // Use getline to read an entire line (including spaces)

    Graph g;
    readInput(g, filename);


    // Print the graph to verify
    g.printGraph();

    return 0;
}
