Read in graph information from a file and output information about the graph to the screen.

Calculate the in-degree and out-degree of each vertex, 
taking as arguments an integer pointer to the array representing the graph as well as the number of vertices. 
Loop over all vertices and output to the screen the in-degree and out-degree of each vertex on the same line. 
There should be one line for the in-degree and out-degree of vertex 0, another line for the in-degree and out-degree of vertex 1, etc.

Find all 2-hop paths with distinct vertices contained in the graph. 
If we designate an edge as an ordered pair of vertices (𝑢,𝑣) such that the edge goes from 𝑢 to 𝑣, 
a 2-hop path can be thought of as an ordered pair of edges = (𝑢,𝑣),(𝑣,𝑤). 
In other words, the “to” or “destination” vertex of the first edge serves as the “from” or “source” vertex of the second edge, 
such that the path proceeds from vertex 𝑢 to vertex 𝑤 by way of vertex 𝑣. 
In this case, we add a further restriction that the vertices must be distinct.