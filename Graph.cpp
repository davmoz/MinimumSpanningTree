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
    string type;
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
    if(cap < numOfVertices)
    {
        cout << "Cap is to short" << endl;
    }
    else
    {
        bool known[cap];
        int cost[cap];
        int pV[cap];
        AdjacencyInfo temp;

        for (int k = 0; k < cap; k++)
        {
            cost[k] = numeric_limits<int>::max();
            pV[k] = -1;
            known[k] = false;
        }

        string vertexState;

        int indexOfLowestCost = 0;
        int lowestCost = 0;
        known[0] = true;
        totalCost = 0;

        int currentVertex = 0;

        List<int> vertexNeighbours;
        int vertex = 0;
        int arcWeight = 0;

        int counter = 0;
        while(counter < numOfVertices - 1)
        {
            cout << endl;

            lowestCost = numeric_limits<int>::max();

            vertexNeighbours = getAllVerticesAdjacentTo(currentVertex);

            for (int i = 0; i < vertexNeighbours.length(); i++)
            {
                vertex = vertexNeighbours.getAt(i);
                arcWeight = list[currentVertex].getAt(i).getArcWeight();
                cost[vertex] = arcWeight;
            }
            cout << "###################################################" << endl;
            for (int k = 0; k < cap; k++)
            {
                if(known[k])
                {

                    vertexNeighbours = getAllVerticesAdjacentTo(k);
                    cout << "At: " << k << endl;
                    for (int i = 0; i < vertexNeighbours.length(); i++)
                    {
                        vertex = vertexNeighbours.getAt(i); // Gets the node (ex 1, 2, 3)
                        arcWeight = list[k].getAt(i).getArcWeight();

                        if(arcWeight < lowestCost && !known[vertex])
                        {
                            cout << i << ") Cost From: " << k << " To: " << vertex << " -> " << arcWeight << endl;
                            lowestCost = arcWeight;
                            indexOfLowestCost = vertex;
                            currentVertex = k;
                        }
                        else if(known[vertex])
                        {
                            cout << i << ") Cost From: " << k << " To: " << vertex << " -> " << arcWeight << " [Path taken]" << endl;
                        }
                        else
                        {
                            cout << i << ") Cost From: " << k << " To: " << vertex << " -> " << arcWeight << endl;
                        }
                    }

                    cout << "[LOWEST: " << currentVertex << "->" << indexOfLowestCost << "] Cost: " << lowestCost << endl;
                    cout << "--" << endl;
                }
            }
            cout << "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤" << endl;
            cout << "[FINAL] From: " << currentVertex << " To: " << indexOfLowestCost << " Lowest Cost: " << lowestCost << endl;
            cout << to_string(totalCost) << " + " << to_string(lowestCost) << " = " << to_string(totalCost + lowestCost) << endl;
            cout << "¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤" << endl;

            temp = AdjacencyInfo(indexOfLowestCost, lowestCost);
            minSpanTree[currentVertex].insertAt(0, temp);

            known[indexOfLowestCost] = true;
            pV[indexOfLowestCost] = currentVertex;
            currentVertex = indexOfLowestCost;
            totalCost += lowestCost;


            for (int j = 0; j < cap; j++)
            {
                if (known[j])
                    vertexState = "T";
                else
                    vertexState = "F";
                cout << "V: " << j << " Known: " << vertexState << " Weight: " << cost[j] << " pV: " << pV[j] << endl;
            }
            cout << "###################################################" << endl;
            counter++;
        }
    }
}