#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  
#include <string.h>
#include <malloc.h>
#include "functions.h"

int main()
{
	// The control variable for the main do while loop that keeps the program running until the user wants to exit
	bool desireToContinue = true;

	// Program greets the user upon first running
	printf("Welcome to Otto's Automobiles!\n");

	do
	{
		printf("\n\n\n");
		printf("Please enter the number of the menu item you wish to select!\n");
		printf("1. View stock of cars\n");
		printf("2. Purchase a car\n");
		printf("3. View sales figures\n");
		printf("4. Exit\n");
		printf("\n");

		// Takes the users input for the switch statement as mentioned previously will ensure the user only enters something valid
		char selectedChoice = reciveCheckedInput();

		switch (selectedChoice)
		{
		case '1':

			// Clears the screen of all previous output then runs the view stock function
			system("cls");
			// Runs the function to display the name, price and number remaning for each type of car sorted in decending order
			 viewStockOfCars();
			 
			break;

		case '2':
			system("cls");
			purchaseACar();
			break;

		case '3':
			system("cls");
			viewAllSalesData();
			break;

		case '4':
			// Simple exit option alters the control variable for the main loop allowing it to end
			desireToContinue = false;
			break;
		}

	} while (desireToContinue == true);

	// Program thanks the user upon exit
	printf("\n");
	printf("Thanks for using Otto's Automobiles!\n");

	return 0;
}

