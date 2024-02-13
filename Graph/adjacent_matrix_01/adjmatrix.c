#include <stdio.h>
#include <stdlib.h>

int in_degree(int * p, int size, int j)
{
    int i1 = 0;
    for (int i = 0; i < size; i++)
    {
        i1 = i1 + p[(i*size) + j];
    }
    return i1;
}

int out_degree(int * p, int size, int i)
{
    int i2 = 0;
    for (int j = 0; j < size; j++)
    {
        i2 = i2 + p[(i*size) + j];
    }
    return i2;
}


int main() 
{
    FILE *file;
    char filename[] = "testgraph.txt";
    int num_elements = 0;
    int size;
    int totalElements;

    // Open the file for reading
    file = fopen(filename, "r");

    // Read the size of the graph first
    if (fscanf(file, "%d", &size) != 1) 
    {
        printf("Error reading size from the file.\n");
        fclose(file);
        return 1;
    }

    totalElements = size * size;

    int * data;
    data = (int *)malloc(totalElements * sizeof(int));

    // Read data from the file and store it in the array
    while (fscanf(file, "%d", &data[num_elements]) != EOF) 
    {
        num_elements++;
    }
    fclose(file);

    int printInDegree, printOutDegree;
    for (int i = 0; i < size; i++)
    {
        printInDegree = in_degree(data, size, i);
        printOutDegree = out_degree(data, size, i);
        printf("%d: %d, %d\n", i, printInDegree, printOutDegree);
    }

    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            if (i != j) 
            {   // make sure the first and second vertex are different
                for (int k = 0; k < size; k++) 
                {
                    if (i != k && j != k) 
                    {   // check the third vertex is different from the first and second vertex.
                        if (data[i * size + j] && data[j * size + k]) 
                        {
                            // if exist a path from i to j and a path from j to k, then the 2-hop exist
                            printf("%d %d %d\n", i, j, k);
                        }
                    }
                }
            }
        }
    }

    free(data);
    return 0;
}
