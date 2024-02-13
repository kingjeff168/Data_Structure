// Find diameter using All-pairs shortest paths
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "graph.h"

// #define DEBUG

//===================== Function Prototypes ===========================
void PrepareGraph(int* mygraph);
int calcIterations();
void CalcShortestPaths(int* mygraph);
int CalcDiameter(int* mygraph);
void PrintGraph(int* mygraph);

//========================= Main Function ===========================
int main() 
{
// initialize the graph here; note it is a 1-dimensional array	
	int* mygraph = (int *) malloc(sizeof(int) * NVERT * NVERT);
	getGraph(mygraph);

	int i, j, k;

#ifdef DEBUG
	printf("\nThe adjacency matrix is\n");
	PrintGraph(mygraph);
#endif

// prepare the graph/array for the all-pairs algorithm
	PrepareGraph(mygraph);

#ifdef DEBUG
	printf("\nThe matrix for calculating all-pairs shortest paths is\n");
	PrintGraph(mygraph);
#endif
	
// set up outer iteration
	int niterations = calcIterations();
#ifdef DEBUG
	printf("number of iterations = %d\n",niterations);
#endif

// calculate shortest paths	
	for(int iiteration = 0; iiteration < niterations; iiteration++) 
	{
#ifdef DEBUG
		printf("\nouter iteration %d:\n",iiteration);
#endif
		CalcShortestPaths(mygraph);
	} 
	
#ifdef DEBUG
	printf("\nThe graph diameter is ");
#endif
	printf("%d\n",CalcDiameter(mygraph));

	free(mygraph);
	return 0;
}

//===================== Function Definitions ===========================

// store "Infinity" values (INT_MAX) where there are no edges, other than from each edge to itself
void PrepareGraph(int* mygraph) 
{
	for (int i = 0; i < NVERT; i++) 
	{
        for (int j = 0; j < NVERT; j++) 
		{
            if (i == j) 
			{
				// while initializing the graph, the elements at the diagonal should be 0.
                mygraph[i * NVERT + j] = 0;
            } 
			else if (mygraph[i * NVERT + j] == 0) 
			{
				// If the value of the element is 0, it will be changed to INT_MAX.
                mygraph[i * NVERT + j] = INT_MAX;
            }
        }
    }
}

// This function is to calculate the number of iterations. The formula is from Workshop3's instruction. 
int calcIterations() 
{
	double result = log(NVERT - 1) / log(2);
    int iterations = (int)ceil(result);
	return iterations;
}

// calculate the lengths of all shortest paths using the "matrix multiplication" method
void CalcShortestPaths(int* mygraph) 
{
	int tempGraph[NVERT*NVERT];
	int temp;
	int min;

	for (int i = 0; i < NVERT; i++)
	{
		for(int j = 0; j < NVERT; j++) 
		{		
			// Assign a minimum	value of the matrix multiplication for multiplying one row and one column.
			// If 2 values are added, the result value will overflow, so min would be assigned with INT_MAX directly.
			if ((mygraph[i * NVERT + j] == INT_MAX) || (mygraph[j * NVERT + i] == INT_MAX))
			{
				min = INT_MAX;
			}
			else
			{
				min = mygraph[i * NVERT + j] + mygraph[j * NVERT + i];
			}

			// This for-loop do the matrix multiplication for shortest paths.
			for (int k = 0; k < NVERT; k++)
			{
				// If any value is INT_MAX, after adding two values, it will overflow, so the value will be assigned INT_MAX directly.
				if ((mygraph[i * NVERT + k] == INT_MAX) || (mygraph[k * NVERT + j] == INT_MAX))
				{
					temp = INT_MAX;
				}
				else
				{
					temp = mygraph[i * NVERT + k] + mygraph[k * NVERT + j];
				}
				
				// If the temp value is smaller the minimum value, it will replace the minimum value.
				if (temp < min)
				{
					min = temp;
				}				
			}
			tempGraph[i * NVERT + j] = min; // after the k-for-loop, the minimum value will be updated in the tempGraph. 		
		}
	}

	// After the matrix multiplication is finished, update all values of mygraph from tempGraph.
	for(int i = 0; i < NVERT; i++)
	{
		for(int j = 0; j < NVERT; j++) 
		{
			mygraph[i * NVERT + j] = tempGraph[i * NVERT + j];
		}
	}

}

// calculate the diameter of the graph as the maximum of the minimum distances
int CalcDiameter(int* mygraph) 
{
	int diameter = 0;
    for (int i = 0; i < NVERT; i++) 
	{
        for (int j = 0; j < NVERT; j++) 
		{
            if ((mygraph[i * NVERT + j] > diameter) && (mygraph[i * NVERT + j] != INT_MAX))
			{
                diameter = mygraph[i * NVERT + j];
            }
        }
    }
	return diameter;
}

// print all array entries as an adjacency matrix
void PrintGraph(int* mygraph) 
{
	for (int i=0; i<NVERT; i++) 
	{
		for (int j=0; j<NVERT; j++) 
		{
			printf("%d ", mygraph[i*NVERT+j]);
		}
		printf("\n");
	}
}