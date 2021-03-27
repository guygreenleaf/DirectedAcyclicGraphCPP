//
// Created by Guy Greenleaf on 3/21/21.
//

#include "DirectedAcyclicGraph.hpp"
#include "adjNode.hpp"
#include <iostream>

DirectedAcyclicGraph::DirectedAcyclicGraph(std::vector<CustomerInfo *> inputVec) {
    std::vector<adjNode *> nodeVector;

    // Need to do this and the endNode after list is built
        auto *startNode = new adjNode(0, 0, 0, 0);
        adjList.emplace_back(startNode);

    int place = 1;
    auto *endNode = new adjNode(0,0,0,0);
    //Make a vector of all adjacency nodes
    for (int i = 0; i < inputVec.size(); i++){
        auto *newNode = new adjNode(inputVec.at(i)->custNumber(), inputVec.at(i)->startDate(), inputVec.at(i)->endDate(), inputVec.at(i)->weight());
        adjList.emplace_back(newNode);

    }

    adjList.emplace_back(endNode);

    for(int i = 0; i<inputVec.size(); i++){

        for(int j = 1; j < adjList.size()-1; j++){
            adjNode * currListPlace = adjList.at(j);
            if((currListPlace->getEndDate() <= inputVec.at(i)->startDate()) && (currListPlace->getClientNumber() != inputVec.at(i)->custNumber())){
                auto *newNode = new adjNode(inputVec.at(i)->custNumber(), inputVec.at(i)->startDate(), inputVec.at(i)->endDate(), inputVec.at(i)->weight());
                newNode->next(currListPlace->next());
                currListPlace->next(newNode);
            }
        }
    }
    std::cout << "Initial adjacency list built...\nBuilding End...\n";

    //populate end
    auto *currentPlaceInEndList = adjList.at(adjList.size()-1);

    for(int i = 1; i < adjList.size()-1; i++){
        if(adjList.at(i)->next() == nullptr){
            auto *newNode = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight());
            newNode->next(currentPlaceInEndList->next());
            currentPlaceInEndList->next(newNode);
        }
    }

    std::cout << "End node built..\nBuilding Start node...\n";

    //populate start
    auto *currentStartPlace = adjList.at(0);

    bool isFound = false;

    for(int i = 1; i <adjList.size()-1; i++){
        auto *currPlace = adjList.at(i);

        for(int j = 1; j < adjList.size()-1; j++ ){
//            auto *innerPlace = new adjNode(adjList.at(j)->getClientNumber(), adjList.at(j)->getStartDate(), adjList.at(j)->getEndDate(), adjList.at(j)->getWeight());
            auto *innerPlace = adjList.at(j);
            if(i != j){
                while(innerPlace != nullptr){
                    if(innerPlace->getClientNumber() == currPlace->getClientNumber()){
                        isFound = true;
                        innerPlace = innerPlace->next();
                    }
                    else {
                        innerPlace = innerPlace->next();
                    }
                }
            }
        }

        if(!isFound){
            auto *newNode = new adjNode(adjList.at(i)->getClientNumber(), adjList.at(i)->getStartDate(), adjList.at(i)->getEndDate(), adjList.at(i)->getWeight());
            newNode->next(adjList.at(0)->next());
            adjList.at(0)->next(newNode);
            isFound = false;
        }
        isFound = false;
//        std::cout << i << " scanned out of " << adjList.size() << std::endl;
    }

}

unsigned long long DirectedAcyclicGraph::nodeCount() {return adjList.size()-2;}

std::vector<adjNode *> DirectedAcyclicGraph::neighbors(int clientNum){
    std::vector<adjNode *> neighborVec;

    adjNode *getNeighborsOf = adjList.at(clientNum);

    while(getNeighborsOf != nullptr){
        neighborVec.emplace_back(getNeighborsOf);
        getNeighborsOf = getNeighborsOf->next();
    }
    return neighborVec;
}

std::vector<adjNode *> DirectedAcyclicGraph::getAdjList(){
    return adjList;
}

void DirectedAcyclicGraph::topSort(){
    unsigned long long n = adjList.size()-2;
    visited.assign(n, false);
    for(int i = 0; i < n; i++){
        if(!visited.at(i)){
            topSortUtil(i);
        }
    }

    for(int i : answer){
        std::cout << i << std::endl;
    }

}

void DirectedAcyclicGraph::topSortUtil(int v) {
    visited.at(v) = true;
    int i;
    for( i = 1; i < adjList.size()-2; i++){
        if(!visited[i]){
            topSortUtil(i);
        }
    }
    answer.push_back(adjList.at(i)->getClientNumber());
}