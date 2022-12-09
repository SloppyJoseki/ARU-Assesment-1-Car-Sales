#include <stdio.h>  // Used for input and output 
#include <string.h> // Used to make interacting with strings easier in particular strcpy
#include <stdlib.h> // Used for malloc to help control memory
#include <ctype.h>
#include "dataTypes.h"

void clearTheScreen() // Makes it a bit tidier and also would allow an easy change for other systems where this might not work
{
	system("cls");
}

void systemSleep()
{
	// Causes the system to make a brief pause to help smooth out the car animation
	system("ping -c 1 localhost > nul");
}

void printLine(char* line, int no)
{
	// A loop that adds spaces continuously to the start of a line to give the illusion of movement when repeated
	int i;
	for (i = 0; i < no; i++)
		printf(" ");
	printf("%s\n", line);
}

void drawCar(int no_of_spaces)
{
	// Makes use of the printline function to  move the car when repeated
	char* line1 = "       .--------.";
	char* line2 = " ____/_____|___ \\___";
	char* line3 = " O    _   - |   _   ,*";
	char* line4 = " '--(_)-------(_)--'";
	printLine(line1, no_of_spaces);
	printLine(line2, no_of_spaces);
	printLine(line3, no_of_spaces);
	printLine(line4, no_of_spaces);
}

void printGreeting()
{
	// https://www.youtube.com/watch?v=qOam8Veyw10&ab_channel=SaifurRahmanMohsin Car drawing code taken from this video
	// Prints and moves the car across the screen then prints the greeting. The screen is cleared each time the car is printed so it "moves"
	for (int i = 0; i < 50; i++)
	{
		systemSleep();
		clearTheScreen();
		drawCar(i);
	}
	printf("\n-----------------------------------------\n");
	printf("Welcome to Otto's Automobiles!\n");
}

void printGoodbye()
{
	// Program thanks the user upon exit
	for (int i = 0; i < 50; i++)
	{
		systemSleep();
		clearTheScreen();
		drawCar(i);
	}
	printf("\n-----------------------------------------\n");
	printf("Thanks for using Otto's Automobiles!\n");
	printf("We hope to see you again soon!\n");
}

char validateInputForFirstMenu()
/* Function checks the users input by taking the scanf result and then if it matches an expected input the program is allowed to proceed however if the
user fails to input correctly they will get stuck in a loop until the do so additionally it clears the buffer after each iteration so the user is unable to
mess with subsequent inputs */
{
	char menuOption;
	do
	{
		scanf("\n%c", &menuOption);
		if (menuOption == '1' || menuOption == '2' || menuOption == '3' || menuOption == '4')
		{
			while (getchar() != '\n');
			return menuOption;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
		while (getchar() != '\n');
	} while (true);
}

char validateInputForSecondMenu()
// Same as above but for the second menu so it requires different inputs
{
	char menuOption2;
	do
	{
		scanf("\n%c", &menuOption2);
		if (menuOption2 == '5' || menuOption2 == '6' || menuOption2 == '7' || menuOption2 == '8' || menuOption2 == '9')
		{
			while (getchar() != '\n');
			return menuOption2;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
		while (getchar() != '\n');
	} while (true);

}

int validateUserAge()
{
	// Inspiration from https://www.youtube.com/watch?v=feUTrLz7l8k&ab_channel=GodfredTech
	int userAge;
	do
	{
		// scanf returns a value for everything it scans so if that's 1 it means it read an int correctly 
		int check = scanf("\n%d", &userAge);
		if (check == 1 && userAge <= 150 && userAge >= 16)
		{
			/* 17 is normal uk driving age but 16 year olds can technically drive with gov permit. The longest documented human life was 126 years
			but the upper check mainly exists to stop someone inputting something larger than an int can deal with */
			return userAge;
		}
		// Reusing the other validate input code
		else
		{
			printf("Please enter a valid age *between 16 and 150*\n");

		}
		while (getchar() != '\n');
	} while (true);
}

bool checkStringForNonLetters(char str[])
{
	// Loop's through the string to check is any characters are not in the alphabet or are not spaces
	for (int i = 0; i < strlen(str); i++)
	{
		if (isalpha(str[i]) || str[i] == ' ')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool checkStringForNewlineCharacter(char str[])
{
	// Loop's through the string to check for a newline character
	int stringLength = strlen(str);
	for (int i = 0; i < stringLength; i++)
	{
		if (str[i] == '\n')
		{
			return true;
		}
	}
	return false;
}

void validateUserName(char fullName[])
{
	// Creates a temp string and checks it if it's good then it sets the given string to be equal to the temp string. If not you must enter a new string
	char tempStr[200];
	printf("Please enter your full name\n");
	do
	{
		fgets(tempStr, 200, stdin); // Using fgets to eliminate the possibility of an input string that is too long
		int stringLength = strlen(tempStr);
		if (checkStringForNewlineCharacter(tempStr) == false) 
		// If tempStr does not contain a \n the input was too large and so the buffer needs to be cleared 
		{
			while (getchar() != '\n');
		}
		tempStr[stringLength - 1] = '\0'; // Ensure the string is null terminated and get rid of a \n character if one does exist

		if (checkStringForNonLetters(tempStr) == true)
		{
			strcpy(fullName, tempStr);
			return;
		}
		else
		{
			printf("Please enter a valid name\n");
		}
	} while (true);
}

bool checkDataFileExists()
{
	FILE* fp;
	fp = fopen("carSaleData.txt", "r");
	if (fp != NULL)
	{
		// The file exists 
		fclose(fp);
		return true;
	}
	else
	{
		return false;
	}
}

void createFileIfNeeded()
{
	bool doesFileExsist = checkDataFileExists();

	if (doesFileExsist == true)
	{
		return;
	}
	else
	{
		FILE* fp;
		fp = fopen("carSaleData.txt", "w");
		fclose(fp);
	}
}

void printMainMenu()
{
	// Prints the main menu 
	printf("\n\n\n");
	printf("Please enter the number of the menu item you wish to select!\n");
	printf("1. View stock of cars\n");
	printf("2. Purchase a car\n");
	printf("3. View sales figures\n");
	printf("4. Exit\n");
	printf("\n");
}

int countLinesInFile()
// Useful for determining how much sale data is the the file as in the csv format each sale is separated by a new line
// https://www.geeksforgeeks.org/c-program-count-number-lines-file/
{
	FILE* fp;
	int count = 0;
	char c;

	fp = fopen("carSaleData.txt", "r");

	for (c = getc(fp); c != EOF; c = getc(fp)) // Goes through each character in the file
		if (c == '\n') // Counts up if this character is newline
			count = count + 1;

	fclose(fp);
	return count; // Returns the count of every newline character in the file
}

void insertionSort(carsData a[], int lengthOfArray)
/* Simple insertion sort https://www.youtube.com/watch?v=Tz7vBodZqo8&ab_channel=PortfolioCourses based on this code. A temporary struct is created in
order to allow the swapping of structs inside an array and then the algorithm goes through and divides the array into a sorted subarray and then the
larger array itself. This particular method of sorting is very efficient when there are not many things to sort so it's perfect for the small number
of cars */
{
	carsData temp;

	for (int i = 1; i < lengthOfArray; i++)
	{
		int lookingAt = a[i].amountOfCar;
		int j = i - 1;

		while (j >= 0 && a[j].amountOfCar < lookingAt)
		{
			temp = a[j + 1];
			a[j + 1] = a[j];
			a[j] = temp;
			j = j--;
		}
		a[j + 1].amountOfCar = lookingAt;
	}
}

void bubble_sort(totalCarSalesData arr[], int size)
// http://www.cprogrammingnotes.com/question/sorting-structure-array.html used to help implement the bubble sort
/* Uses a temporary struct to allow the swapping of cars unfortunately the previous sorting function can't be reused since a different kind of struct
 is being worked with  */
{
	totalCarSalesData temporary;
	int i, j;

	for (i = 0; i < (size - 1); i++)
	{
		for (j = 0; j < (size - 1 - i); j++) 
		{
			/* size - 1 - i acts as an optimisation so that you don't go over elements you have already sorted, as the elements "bubble up" there is
			no need to go over the elements at the end of the array as they are already sorted into place. Therefore for every element you sort you
			can look at one fewer element on the next pass of the array */
			if (arr[j].totalCarSales < arr[j + 1].totalCarSales)
			{
				temporary = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temporary;
			}
		}
	}
}

purchaseData* readPurchaseDataFromFileIntoArray()
{
	FILE* fileSalesData;
	int numberOfLinesInFile = countLinesInFile();
	// Uses the number of lines in the file (aka number of sales) to determine the size of the array
	if (numberOfLinesInFile == 0)
	{
		return NULL;
	}
	purchaseData* purchases = (purchaseData*) malloc(sizeof(purchaseData) * numberOfLinesInFile);
	if (purchases == NULL)
	{
		return NULL;
	}
	fileSalesData = fopen("carSaleData.txt", "r");

	if (fileSalesData != NULL)
	{
		int valuesRecorded = 0;
		do
		{
			fscanf(fileSalesData, "%f, %f, %d, %c, %d, %d, %d, %d, %d, %[^\n]s",
				&purchases[valuesRecorded].totalPrice,
				&purchases[valuesRecorded].pricePaid,
				&purchases[valuesRecorded].customerAge,
				&purchases[valuesRecorded].ifDiscountWasGiven,
				&purchases[valuesRecorded].percentageDiscount,
				&purchases[valuesRecorded].numberOfCarsPurchased,
				&purchases[valuesRecorded].numberOfToyotaPurchased,
				&purchases[valuesRecorded].numberOfKiaPurchased,
				&purchases[valuesRecorded].numberOfHyundaiPurchased,
				&purchases[valuesRecorded].customerName);

			valuesRecorded++;


		} while (!feof(fileSalesData));
		// While it's not the end of the file loop through and read all of the sales data into the array of structs

		fclose(fileSalesData);

		return purchases; // Return the array of sales for use by other functions
	}
}


