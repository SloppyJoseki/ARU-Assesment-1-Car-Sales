#include <stdio.h>  // Used for input and output 
#include <string.h> // Used to make interacting with strings easier in partiular strcpy
#include <stdlib.h> // Used for malloc to help control memory


void viewStockOfCars()
{
	struct carsData* carsList = calculateCarsInStock(); // Calculates the number of cars in stock with previous function
	insertionSort(carsList, 3); // Sorts that array with the insertion sort

	// Prints all cars in stock
	printf("Here is a list of our stock of cars!\n");
	for (int i = 0; i < 3; i++)
	{
		// The £ sign is a pain to use so just write GBP instead 
		printf("We have %d %s's in stock and they cost %.2f GBP each\n", carsList[i].amountOfCar, carsList[i].carName, carsList[i].carPrice);
	}
	printf("\n");
	free(carsList); // Free the momory taken up by carsList to prevent any memory issues
}