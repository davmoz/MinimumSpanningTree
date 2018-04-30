//
// Created by quartie on 2018-04-26.
//

#include "Graph.h"
#include <limits>

Graph::Graph(GraphType graphType, int nrOfVert)
{
    this->graphType = graphType;
    numOfVertices = nrOfVert;
    list = new List<AdjacencyInfo>[nrOfVert];
}


Graph::~Graph()
{
    delete[] list;
    numOfVertices = 0;
}


bool Graph::isDirected() const
{
    return graphType == DIRECTED;
}


int Graph::getNrOfVertices() const
{
    return numOfVertices;
}

bool Graph::addArc(int sourceVertex, int destinationVertex, int arcWeight)
{
    bool exists = true;

    if(sourceVertex < 0 || sourceVertex > numOfVertices ||
       destinationVertex < 0 || destinationVertex > numOfVertices)
    {
        exists = false;
    }
    if(exists)
    {
        AdjacencyInfo temp(destinationVertex, arcWeight);

        if(list[sourceVertex].length() > 0)
        {
            list[sourceVertex].insertAt(1, temp);
        }
        else
        {
            list[sourceVertex].insertAt(0, temp);
        }
    }
    else
    {
        cout << "Does not exist" << endl;
    }
    return exists;
}

void Graph::printGraph() const
{
    string type = "";
    if(graphType == 0)
    {
        type = "Directed";
    }
    else if(graphType == 1)
    {
        type = "Undirected";
    }
    cout << endl << "#################################" << endl;
    cout << "Vertices: " << numOfVertices << endl;
    cout << "Type: " << type << endl;
    for (int i = 0; i < numOfVertices; i++)
    {
        cout << "V " << i << ":";
        for (int j = 0; j < list[i].length(); j++)
        {
            cout << " [" << list[i].getAt(j).getNeighbourVertex();
            cout << ", " << list[i].getAt(j).getArcWeight() << "]";
        }
        cout << endl;
    }
    cout << "#################################" << endl;
}

int Graph::outDegreeOfVertex(int theVertex) const
{
    return list[theVertex].length();
}

int Graph::inDegreeOfVertex(int theVertex) const
{
    int inDegree = 0;
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < list[i].length(); j++)
        {
            if(list[i].getAt(j).getNeighbourVertex() == theVertex)
                inDegree++;
        }
    }
    return inDegree;
}

void Graph::reset(int nrOfVert, GraphType graphType)
{
    delete[] list;
    numOfVertices = nrOfVert;
    this->graphType = graphType;
    list = new List<AdjacencyInfo>[nrOfVert];
}

bool Graph::hasArc(int sourceVertex, int destinationVertex) const
{
    // Quadratic
    bool arcExists = false;
    for (int i = 0; i < list[sourceVertex].length() && !arcExists; i++)
    {
        if(list[sourceVertex].getAt(i).getNeighbourVertex() == destinationVertex)
            arcExists = true;
    }
    return arcExists;
}

bool Graph::removeArc(int sourceVertex, int destinationVertex, int arcWeight)
{
    // Need error handling for vertex ranges
    bool removed = false;
    AdjacencyInfo temp = AdjacencyInfo(destinationVertex, arcWeight);
    removed = list[sourceVertex].removeElement(temp);
    return removed;
}

List<int> Graph::getAllVerticesAdjacentTo(int theVertex) const
{
    List<int> temp;
    for (int i = 0; i < list[theVertex].length(); i++)
    {
        temp.insertAt(i, list[theVertex].getAt(i).getNeighbourVertex());
    }
    return temp;
}

void Graph::minSpanTree(List<AdjacencyInfo> *minSpanTree, int cap, int &totalCost) const
{
    if(cap < numOfVertices - 1)
    {
        cout << "Cap is to short" << endl;
    }
    else
    {
        bool known[cap] {false};
        int cost[cap] {numeric_limits<int>::max()};
        int pV[cap] {-1};

        string nodeKnown;
        int startNode = 0;
        int arcWeight = 0;
        int counter = 0;
        int smallest = cost[0];
        int destinationNode = 0;

        // Start with Node 0
        known[startNode] = true;
        cost[startNode] = 0;

        List<int> tempList;

        int tempNode = 0;

        AdjacencyInfo nodeDone = AdjacencyInfo(destinationNode, arcWeight);
        minSpanTree[counter].insertAt(0, nodeDone);

        while(counter < numOfVertices - 1)
        {
            for (int k = 0; k < list[startNode].length(); k++)
            {
                arcWeight = list[startNode].getAt(k).getArcWeight();
                cost[list[startNode].getAt(k).getNeighbourVertex()] = arcWeight;
            }

            tempList = getAllVerticesAdjacentTo(startNode);
            cout << "#################################" << endl;
            cout << "[Neighbours or node " << startNode << "]" << endl;
            for (int i = 1; i < tempList.length(); i++)
            {
                tempNode = tempList.getAt(i);
                cout << "temp: " << tempNode << " Cost: " << cost[tempNode];
                if(cost[tempNode] < smallest && !known[tempNode])
                {
                    smallest = cost[tempNode];
                    destinationNode = tempNode;
                }
                cout << endl;
            }

            cout << endl;
            cout << "From: " << startNode << endl;
            cout << "Dest: " << destinationNode << endl;
            cout << "Cost: " << smallest << endl;
            cout << "#################################" << endl;

            counter++;
            AdjacencyInfo nodeDone = AdjacencyInfo(destinationNode, smallest);
            minSpanTree[counter].insertAt(0, nodeDone);

            pV[destinationNode] = startNode;
            startNode = destinationNode;
            totalCost += smallest;
            known[startNode] = true;
            smallest = numeric_limits<int>::max();




            for (int j = 0; j < cap; j++)
            {
                if (known[j])
                    nodeKnown = "T";
                else
                    nodeKnown = "F";
                cout << "V: " << j << " Known: " << nodeKnown << " Weight: " << cost[j] << " pV: " << pV[j] << endl;
            }
        }
    }
}


