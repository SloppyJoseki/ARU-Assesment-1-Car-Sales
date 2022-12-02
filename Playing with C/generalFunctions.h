#include <stdio.h>  // Used for input and output 
#include <string.h> // Used to make interacting with strings easier in partiular strcpy
#include <stdlib.h> // Used for malloc to help control memory
#include "dataTypes.h"

void clearTheScreen() // Makes it a bit tidier and also would allow an easy change for other systems where this might not work
{
	system("cls");
}

char validateInputForFirstMenu()
/* Function checks the users input by taking the scanf result and then if it matches an expected input the program is allowed to proceed however if the
user fails to input correctly they will get stuck in a loop until the do so additionally it clears the buffer after each itteration so the user is unable to
mess with subsequent inputs */
{
	char menuOption;
	do
	{
		scanf("\n%c", &menuOption);
		if (menuOption == '1' || menuOption == '2' || menuOption == '3' || menuOption == '4')
		{
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
		// scanf returns a value for everything it scans so if thats 1 it means it read an int correctly 
		int check = scanf("\n%d", &userAge);
		if (check == 1 && userAge < 150 && userAge > 16)
		{
			/* 17 is normal uk driving age but 16 year olds can technically drive with gov permit. The longest documented human life was 126 years
			but the upper check mainly exsists to stop someone inputing something larger than an int can deal with */
			return userAge;
		}
		// Reusing the other validate input code
		else
		{
			printf("Please enter a valid age\n");
		}
		while (getchar() != '\n');
	} while (true);
}

bool checkDataFileExsists()
{
	FILE* fp;
	fp = fopen("carSaleData.txt", "r");
	if (fp == NULL) // If the file does not exsist will be equal to NULL so open it in write mode and it will be created by default
	{
		fp = fopen("carSaleData.txt", "w");
	}
	fclose(fp);
	fp = fopen("carSaleData.txt", "r");

	if (fp == NULL) // Check again to make sure the creation went ok as if it failed so will the whole program
	{
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}

int countLinesInFile()
// Useful for determaning how much sale data is the the file as in the csv format each sale is seperated by a new line
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

void insertionSort(struct carsData a[], int lengthOfArray)
/* Simple insertion sort https://www.youtube.com/watch?v=Tz7vBodZqo8&ab_channel=PortfolioCourses based on this code. A temporary struct is created in
order to allow the swapping of structs inside an array and then the algorithm goes through and divides the array into a sorted subarray and then the
larger array itself. This particular method of sorting is very efficient when there are not many things to sort so its perfect for the small number
of cars */
{
	struct carsData temp;

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

void bubble_sort(struct totalCarSalesData arr[], int size)
// http://www.cprogrammingnotes.com/question/sorting-structure-array.html used to help implement the bubble sort
/* Uses a temporary struct to allow the swaping of cars unfortunetly the previous sorting function can't be resued since a different kind of struct
 is being worked with  */
{
	struct totalCarSalesData temporary;
	int i, j;

	for (i = 0; i < (size - 1); i++)
	{
		for (j = 0; j < (size - 1 - i); j++)
		{
			if (arr[j].totalCarSales < arr[j + 1].totalCarSales)
			{
				temporary = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temporary;
			}
		}
	}
}

struct purchaseData* readPurchaseDataFromFileIntoArray()
{
	FILE* fileSalesData;
	int numberOfLinesInFile = countLinesInFile();
	// Uses the number of lines in the file (aka number of sales) to determine the size of the array
	struct purchaseData* purchases = (struct purchaseData*) malloc(sizeof(struct purchaseData) * numberOfLinesInFile);
	if (purchases == NULL)
	{
		return;
	}
	fileSalesData = fopen("carSaleData.txt", "r");

	if (fileSalesData != NULL)
	{
		int valuesRead = 0;
		int valuesRecorded = 0;

		do
		{
			valuesRead = fscanf(fileSalesData, "%f, %f, %d, %c, %d, %d, %d, %d, %d, %[^\n]s",
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
			if (valuesRead == 10)
			{
				valuesRecorded++;
			}

			if (valuesRead != 10 && !feof(fileSalesData))
			{
				printf("ERROR formatting issue in file please try to fix\n");
			}

			if (ferror(fileSalesData))
			{
				printf("ERROR file error\n");

			}

		} while (!feof(fileSalesData));
		// While its not the end of the file loop through and read all of the sales data into the array of structs

		fclose(fileSalesData);

		return purchases; // Return the array of sales for use by other functions
	}
}


