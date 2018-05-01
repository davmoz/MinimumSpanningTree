#include "Graph.h"
#include <iostream>
#include <fstream>

using namespace std;


void importGraph(const string fileLocation, Graph *&graph);


int main()
{
    Graph *graph = nullptr;

    importGraph("text.txt", graph);

    graph->printGraph();
    /*
    graph->reset(5, DIRECTED);

    graph->printGraph();

    importGraph("text.txt", graph);

    graph->printGraph();

    cout << "Node 2 InDregree: " << graph->inDegreeOfVertex(2) << endl;

    cout << "Node 2 OutDegree: " << graph->outDegreeOfVertex(2) << endl;

    if(graph->hasArc(3, 2))
    {
        cout << "Has Arc" << endl;
    }
    else
    {
        cout << "No Arc" << endl;
    }

    *//*if(graph->removeArc(0, 2, 40))
    {
        cout << "Arc found and removed" << endl;
    }
    else
    {
        cout << "Arc does not exist and cannot remove" << endl;
    }

    graph->printGraph();*//*

    List<int> temp = graph->getAllVerticesAdjacentTo(1);

    for (int i = 0; i < temp.length(); i++)
    {
        cout << temp.getAt(i) << endl;
    }*/


    int totalCost = 0, length = 7;

    List<AdjacencyInfo> *mst = new List<AdjacencyInfo>[length];
    graph->minSpanTree(mst, length, totalCost);
    cout << endl << "###################" << endl;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < mst[i].length(); j++)
        {
            cout << "[" << i << "]" << "->[" << mst[i].getAt(j).getNeighbourVertex();
            cout << "] Weight: " << mst[i].getAt(j).getArcWeight() << endl;
        }
    }
    cout << "###################" << endl;
    cout << "Total: " << totalCost << endl;
    cout << "###################" << endl;

    delete[] mst;
    delete graph;
    return 0;
}


void importGraph(const string fileLocation, Graph *&graph)
{
    ifstream import;
    import.open(fileLocation);
    if(import.is_open())
    {
        delete graph;
        int nrOfVertices = 0;
        string direction;
        int start = 0, end = 0, weight = 0;

        import >> nrOfVertices;
        import >> direction;

        if(direction == "U")
        {
            graph = new Graph(UNDIRECTED, nrOfVertices);
            while(!import.eof())
            {
                import >> start >> end >> weight;

                graph->addArc(start, end, weight);
                graph->addArc(end, start, weight);
            }
        }
        else if(direction == "D")
        {
            graph = new Graph(DIRECTED, nrOfVertices);
            while(!import.eof())
            {
                import >> start >> end >> weight;

                graph->addArc(start, end, weight);
            }
        }
    }
    else
    {
        cout << "Could not open file" << endl;
    }


    import.close();
}