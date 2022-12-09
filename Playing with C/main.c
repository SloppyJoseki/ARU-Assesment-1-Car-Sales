#define _CRT_SECURE_NO_WARNINGS

#include "generalFunctions.h"
#include "stockFunctions.h"
#include "purchaseFunctions.h"
#include "salesDataFunctions.h"

/* This program uses the file to run pretty much all of its functionality the rationale behind this is that it should save on memory when the
as when the program does not have to do something it won't use any extra memory. Additionally it makes the program quite resilient to suddenly
being stopped as data is saved in the file at almost every step. */ 

int main()
{
	// The control variable for the main do while loop that keeps the program running until the user wants to exit
	bool desireToContinue = true;
	
	createFileIfNeeded(); // Checks if the text file exists and if not creates it

	// Program greets the user upon first running
	printGreeting();

	do
	{
		printMainMenu();

		// Takes the users input for the switch statement will ensure the user only enters something valid
		char selectedChoice = validateInputForFirstMenu();

		switch (selectedChoice)
		{
		case '1':

			// Clears the screen of all previous output then runs the view stock function
			clearTheScreen();
			// Runs the function to display the name, price and number remaining for each type of car sorted in descending order
			 viewStockOfCars();
			 
			break;

		case '2':
			clearTheScreen();

			// Runs all the relevant car purchase functions 
			purchaseACar();
			break;

		case '3':
			clearTheScreen();

			// Prints all the previous sales data
			viewAllSalesData();
			break;

		case '4':
			// Simple exit option alters the control variable for the main loop allowing it to end
			desireToContinue = false;
			break;
		}

	} while (desireToContinue == true);

	// Program thanks the user upon exit
	printGoodbye();


	return 0;
}

