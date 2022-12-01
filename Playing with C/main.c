#define _CRT_SECURE_NO_WARNINGS

#include "functions.h"

int main()
{
	// Sometime when the data is manualy cleared from the file the program tries to read a blank line as data and it breaks
	// The control variable for the main do while loop that keeps the program running until the user wants to exit
	bool desireToContinue = true;
	bool doesTheFileExsist = checkDataFileExsists(); // Makes sure the file exsists so we can use it for everything else

	if (doesTheFileExsist == false) // If the text file does not exsist then the program can't run so tell the user why and end it
	{
		printf("Your computer has stoped this program from creating the file carSaleData.txt this is needed for the program to run");
		printf(" you can either fix your permissions or manualy create the file\n");
		return 1;
	}

	// Program greets the user upon first running
	printf("Welcome to Otto's Automobiles!\n");

	do
	{
		// Prints the main menu 
		printf("\n\n\n");
		printf("Please enter the number of the menu item you wish to select!\n");
		printf("1. View stock of cars\n");
		printf("2. Purchase a car\n");
		printf("3. View sales figures\n");
		printf("4. Exit\n");
		printf("\n");

		// Takes the users input for the switch statement will ensure the user only enters something valid
		char selectedChoice = validateInputForFirstMenu();

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

			// Runs all the relevant car purchase functions 
			purchaseACar();
			break;

		case '3':
			system("cls");

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
	printf("\n");
	printf("Thanks for using Otto's Automobiles!\n");

	return 0;
}

