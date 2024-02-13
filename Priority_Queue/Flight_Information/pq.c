// Typedef and function definitions for PQ
#include <stdio.h>
#include <stdlib.h>

typedef struct flightinfo 
{
	char airline; 		// use U for United, D for Delta, A for American, S for Southwest
	int flightnumber;
	int time;
} Flightinfo;

typedef struct item 
{
	Flightinfo flight;
	int* priority; // priority is a pointer to an int, will point to flighttime
	struct item * next;
} Item;

Item* Initialize()
{
	Item * dummy = (Item*) malloc(sizeof(Item));
	dummy->flight.airline = ' ';
	dummy->flight.flightnumber = -1;
	dummy->flight.time = -1;
	dummy->priority = &dummy->flight.time;
	dummy->next = NULL;
	return dummy;
}

int Add(Item* mypq, char itemAirline, int itemFlightnumber, int itemTime)
{
	// This Add() function will do the priority first, so other functions don't need arrange the priority order again.
	// check whether flight number and flight time is positive
	if (itemFlightnumber >= 0 && itemTime >= 0)
	{
		// Add new flight information
		Item * insertNode = (Item*) malloc(sizeof(Item));
		insertNode->flight.airline = itemAirline;
		insertNode->flight.flightnumber = itemFlightnumber;
		insertNode->flight.time = itemTime;
		insertNode->priority = &insertNode->flight.time;
		insertNode->next = NULL;

		Item * currentNode = mypq;

		// In if-statement, it will check whether the head node's priority is bigger than insertNode.
		if (*(currentNode->priority) > *(insertNode->priority))
		{
			insertNode->next = currentNode;
			currentNode = insertNode;
		}
		else
		{
			// In else-statement, it checks whether the next node of currentNode is null and check the priority between insertNode and currentNode
			while(currentNode->next !=NULL && *(currentNode->next->priority) < *(insertNode->priority))
			{
				// if condition is true, means insertNode’s priority is bigger, then currentNode will move to the next node.
				// do the comparison until insertNode’s is smaller.
				currentNode = currentNode->next;
			}
			insertNode->next = currentNode->next;
			currentNode->next = insertNode;
			//when the insertNode’s priority is smaller, it will insert the insertNode before currentNode.
		}

		return 0;	
	}
	else
	{
		return 1;
	}
}

void Remove(Item* mypq)
{
	Item * tempNode;
	tempNode = mypq->next;
	if (tempNode != NULL)
	{
		// Because the priority order is arranged at Add(), so just remove the first node after the head node.
		mypq->next = tempNode->next;
		free(tempNode);	
	}	
}

void Print(Item* mypq)
{
	// Use the pointer to keep pointing to the next node, and print all informaiton.
	printf("Priority Queue contents:\n");
	Item * temp = mypq->next;
	while (temp != NULL)
	{
		printf("%c %d %d\n",temp->flight.airline, temp->flight.flightnumber, temp->flight.time);
		temp = temp->next;
	}
}

int Count(Item* mypq)
{
	// Use the pointer to keep pointing to the next node, and add 1 to cnt until the next node is null.
	Item * temp = mypq->next;
	int cnt = 0;
	while (temp != NULL)
	{
		cnt++;
		temp = temp->next;
	}
	return cnt;
}

int CountAirline(Item* mypq, char myairline)
{
	// Use the pointer to keep pointing to the next node. When the specific airline name is matched, 
	// cnt will add 1, and it will keep going until the next node is null.
	int cnt = 0;
	Item * currentNode = mypq->next;
	while (currentNode != NULL)
	{
		if (currentNode->flight.airline == myairline)
		{
			cnt++;
		}
		currentNode = currentNode->next;
	}	
	return cnt;
}

int CountSmaller(Item* mypq, int itemflightnumber)
{
	// Use the pointer to keep pointing to the next node. When the flight number is smaller than the specific number, 
	// cnt will add 1, and it will keep going until the next node is null.
	int cnt = 0;
	Item * currentNode = mypq->next;
	while (currentNode != NULL)
	{
		if (currentNode->flight.flightnumber < itemflightnumber)
		{
			cnt++;
		}
		currentNode = currentNode->next;		
	}	

	return cnt;
}

int CountLarger(Item* mypq, int itemflightnumber)
{
	// Use the pointer to keep pointing to the next node. When the flight number is bigger than the specific number, 
	// cnt will add 1, and it will keep going until the next node is null.
	int cnt = 0;
	Item * currentNode = mypq->next;
	while (currentNode != NULL)
	{
		if (currentNode->flight.flightnumber > itemflightnumber)
		{
			cnt++;
		}
		currentNode = currentNode->next;		
	}	

	return cnt;
}

int CountEarlier(Item* mypq, int mypriority)
{
	// Use the pointer to keep pointing to the next node. When the flight's priority is smaller than the specific priority, 
	// cnt will add 1, and it will keep going until the next node is null.
	int cnt = 0;
	Item * currentNode = mypq->next;
	while (currentNode != NULL)
	{
		if (currentNode->flight.time < mypriority)
		{
			cnt++;
		}
		currentNode = currentNode->next;		
	}	

	return cnt;
}

int CountLater(Item* mypq, int mypriority)
{
	// Use the pointer to keep pointing to the next node. When the flight's priority is bigger than the specific priority, 
	// cnt will add 1, and it will keep going until the next node is null.
	int cnt = 0;
	Item * currentNode = mypq->next;
	while (currentNode != NULL)
	{
		if (currentNode->flight.time > mypriority)
		{
			cnt++;
		}
		currentNode = currentNode->next;		
	}	

	return cnt;
}

void Finalize(Item* mypq)
{
	// Use the pointer to keep pointing to the next node to free the memory until the current node is null.
	Item * currentNode = mypq->next;
    while(currentNode != NULL)
    {
        Item * temp = currentNode;
        currentNode = currentNode->next;
        free(temp);
    }
}
