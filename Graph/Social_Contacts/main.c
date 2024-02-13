/*
Last Date Modified: 1/9/2024

Description:

Quantify an aspect of disease transmissibility by calculating the number of connected components of a graph.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct toVertex
{
    // The data of the vertex that connect to the adjList[i].
    int vertex; // the vertex here means that it connects to the i-th node in the adjList.
    int weight;
    struct toVertex * next;
}ToVertex;

typedef struct graph 
{
    int numVertices; // number of vertices.
    ToVertex ** adjList; //adjList is an array of pointers where adjList[i] points to the head of the linked list for the i-th node in the graph. 
}Graph;

ToVertex* createToVertex(int v, int w) 
{
    // Create a new vertex that connect to the adjList[i].
    ToVertex* newNode = (ToVertex*) malloc(sizeof(ToVertex));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) 
{
    // Create a graph and initialize the value in adjList.
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices * sizeof(ToVertex*));

    for (int i = 0; i < vertices; i++)
    {
        graph->adjList[i] = NULL;
    }
    
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) 
{
    // This function will create the vertex and add the vertex to the assigned adjList[i].
    ToVertex* newNode = createToVertex(dest, weight);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}


void DFS(Graph* graph, int node, int visited[]) 
{
    visited[node] = 1; // Mark the current node as visited.
    ToVertex* temp = graph->adjList[node]; // Create a temp for pointing the vertex at adjList[node]
    while (temp != NULL) 
    {
        int neighbor = temp->vertex; // Define neighbor as the vertex connected to the adjList[node].
        if (!visited[neighbor]) 
        {
            // If the neighbor is not visited, then we do the recursive DFS to visit it's neighbor.
            // DFS will finished when all neighbors are visited.
            DFS(graph, neighbor, visited);
        }
        temp = temp->next;
    }
}

int countConnectedComponents(Graph* graph) 
{
    int numComponents = 0;
    int visited[graph->numVertices];

    for (int i = 0; i < graph->numVertices; i++) 
    {
        visited[i] = 0; // Initialize all nodes as not visited.
    }

    for (int i = 0; i < graph->numVertices; i++) 
    {
        // Start the DFS from adjList[0] (vertex 0). If this vertex is not visited, then the program will do DFS. 
        if (!visited[i]) 
        {
            DFS(graph, i, visited);
            numComponents++; // After DFS, it means all vertices they connect together is a connected component.
        }
    }

    return numComponents;
}

void freeGraph(Graph* graph) 
{
    if (graph == NULL) 
    {
        return;
    }

    // Remove memory of all vertices that are pointed by the adjList.
    for (int i = 0; i < graph->numVertices; i++) 
    {
        ToVertex* current = graph->adjList[i];
        while (current != NULL) 
        {
            ToVertex* temp = current;
            current = current->next;
            free(temp);
        }
    }

    // Remove memory of all adjList and graph.
    free(graph->adjList);
    free(graph);
}


int main(int argc, char *argv[])
{
    FILE *file;
    char *filename;
    int num_elements = 0;
    int size;
    int totalElements;
    int targetLabel;
    int source, dest, weight;

    filename = argv[1];
    targetLabel = atoi(argv[2]);

    // Open the file for reading
    file = fopen(filename, "r");

    // Read the number of the vertex
    if (fscanf(file, "%d", &size) != 1) 
    {
        printf("Error reading size from the file.\n");
        fclose(file);
        return 1;
    }

    // Initialize the graph.
    Graph* graph = createGraph(size);

    // Read the txt file. While reading it, the program will check the weight of the edge when the user enter "1" at the second command-line argument.
    // Thus, the graph will do the classification here to make sure only edges with weight of 2 will be kept.
    while (fscanf(file, "%d %d %d", &source, &dest, &weight) != EOF)
    {
        if (targetLabel <= 1)
        {
            if (weight == 1)
            {
                addEdge(graph, source, dest, weight);
            }
        }
        else
        {
            addEdge(graph, source, dest, weight);
        }
        
    }
    fclose(file);

    int numComponents = countConnectedComponents(graph);
    printf("%d\n", numComponents);
    
    // Release the memory.
    freeGraph(graph);

    return 0;

}