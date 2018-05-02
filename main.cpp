#include "Graph.h"
#include <iostream>
#include <fstream>

using namespace std;


void importGraph(const string fileLocation, Graph *&graph);


int main()
{
    Graph *graph = nullptr;
    int vertexA = 0, vertexB = 0, arcWeight = 0;
    bool graphType;
    const string fileLocation = "text.txt";

    // Read and print!
    cout << endl << "########[Read from file & print]#########" << endl;
    importGraph(fileLocation, graph);
    graph->printGraph();
    cout << "#########################################" << endl;


    // Checking graph type!
    cout << endl << "########[Controlling graph type]#########" << endl;
    graphType = graph->isDirected();
    if(graphType)
        cout << "The graph is Directed!" << endl;
    else
        cout << "The graph is not Directed!" << endl;
    cout << "#########################################" << endl;


    // Check number of vertices in graph
    cout << endl << "#########[Number of Vertices]############" << endl;
    cout << "Number of vertices: " << graph->getNrOfVertices() << endl;
    cout << "#########################################" << endl;


    // Reset graph and print the "empty" graph
    cout << endl << "########[Reset graph & print]############" << endl;
    graph->reset(5, DIRECTED);
    graph->printGraph();
    cout << "#########################################" << endl;


    // Check number of vertices in graph
    cout << endl << "#########[Number of Vertices]############" << endl;
    cout << "Number of vertices: " << graph->getNrOfVertices() << endl;
    cout << "#########################################" << endl;


    // Fill the same graph with arcs!
    cout << endl << "#####[Same graph read again & print]#####" << endl;
    importGraph(fileLocation, graph);
    graph->printGraph();
    cout << "#########################################" << endl;


    // Check in- and out-degree of a vertex!
    cout << endl << "#####[Control indegree & outdegree]######" << endl;
    vertexA = 2;
    cout << "InDregree of vertex ["<< vertexA << "]: " << graph->inDegreeOfVertex(vertexA) << endl;
    cout << "OutDegree of vertex ["<< vertexA << "]: " << graph->outDegreeOfVertex(vertexA) << endl;
    cout << "#########################################" << endl;


    // Control if arcs exist!
    cout << endl << "#########[Control arc existence]#########" << endl;
    vertexA = 4;
    vertexB = 3;

    if(graph->hasArc(vertexA, vertexB))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "] Exist!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "] Does not exist!" << endl;
    }

    vertexA = 9;
    vertexB = 3;
    if(graph->hasArc(vertexA, vertexB))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "] Exist!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "] Does not exist!" << endl;
    }
    cout << "#########################################" << endl;

    // Control remove functionality
    cout << endl << "##########[Control arc removal]##########" << endl;
    vertexA = 0;
    vertexB = 3;
    arcWeight = 10;
    if(graph->removeArc(vertexA, vertexB, arcWeight))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Removed!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Does not exist and can not be removed!" << endl;
    }

    vertexA = 0;
    vertexB = 1;
    arcWeight = 10;
    if(graph->removeArc(vertexA, vertexB, arcWeight))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Removed!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Does not exist and can not be removed!" << endl;
    }
    cout << "#########################################" << endl;


    // Print graph
    cout << endl << "#####[print current graph & state]#######" << endl;
    graph->printGraph();
    cout << "##########################################" << endl;


    // Control add functionality
    cout << endl << "##########[Control arc adding]###########" << endl;
    vertexA = 0;
    vertexB = 3;
    arcWeight = 10;
    if(graph->addArc(vertexA, vertexB, arcWeight))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Added!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Not Added!" << endl;
    }

    vertexA = 8;
    vertexB = 3;
    arcWeight = 10;
    if(graph->addArc(vertexA, vertexB, arcWeight))
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Added!" << endl;
    }
    else
    {
        cout << "Arc [" << vertexA << "]->[" << vertexB << "]" << " Weight: " << arcWeight << " Not Added!" << endl;
    }
    cout << "#########################################" << endl;


    // Print graph
    cout << endl << "#####[print current graph & state]#######" << endl;
    graph->printGraph();
    cout << "##########################################" << endl;


    cout << endl << "########[Viewing vertex neighbours]#######" << endl;
    vertexA = 3;
    List<int> temp = graph->getAllVerticesAdjacentTo(vertexA);
    cout << "Node " << vertexA << " has the following arcs: " << endl;
    for (int i = 0; i < temp.length(); i++)
    {
        cout << "[" << vertexA << "]" << "->" << "[" << temp.getAt(i) << "]" << endl;
    }
    cout << "##########################################" << endl << endl;



    int totalCost = 0, length = 7;
    List<AdjacencyInfo> *mst = new List<AdjacencyInfo>[length];

    try
    {
        cout << "##########################################" << endl;
        cout << "################  M S T  #################" << endl;
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

    }
    catch (const char *e)
    {
        cout << e << endl;
    };


    graph->hasArc(99, 10);

    graph->removeArc(0, 3, 10);

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