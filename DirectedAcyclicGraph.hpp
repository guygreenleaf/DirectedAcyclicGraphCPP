//
// Created by Guy Greenleaf on 3/21/21.
//

#ifndef CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
#define CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP


#include <vector>
#include "adjNode.hpp"
#include <list>
#include "CustomerInfo.hpp"

class DirectedAcyclicGraph{
    public:

        explicit DirectedAcyclicGraph(std::vector<CustomerInfo *> inputVec);

        unsigned long long nodeCount();

        std::vector<int> neighbors(int clientNum);

        std::vector<int> startVec;
        bool getValue(int n);
        void setValue(int n);

        void topSort();
        void topSortUtil(int v);
        std::vector<int> answer;
        std::vector<adjNode *> getAdjList();

        int getNodeType(int v);

    private:
        std::vector<adjNode *> adjList;
        std::vector<std::vector<adjNode>> adjMatrix;
        std::vector<std::vector<int>> edgeMatrix;

    std::vector<bool> visited;


    };


#endif //CS415PROJECT2_DIRECTEDACYCLICGRAPH_HPP
