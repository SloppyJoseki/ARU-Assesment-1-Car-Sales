#define _CRT_SECURE_NO_WARNINGS
// Prices based on googling for random cars these brands sell
#define TOYOTA_PRICE 21460.60f
#define KIA_PRICE 14900.00f
#define HYUNDAI_PRICE 19035.20f

#include <stdio.h>  // Used for input and output 
#include <string.h> // Used to make interacting with strings easier in partiular strcpy
#include <stdlib.h> // Used for malloc to help control memory

typedef enum { false = 0, true = 1 } bool; // Creating a new variable type bool that just assigns true and false values to improve readability

struct carsData // The basic way to store simple information about the cars this program interacts with
{
	char carName[15];
	float carPrice;
	int amountOfCar;
};

struct purchaseData // When interacting with the data from the file its easy to store it all in an array of these structs
{
	float totalPrice;
	float pricePaid;
	char customerName[200];
	int customerAge;
	char ifDiscountWasGiven;
	int percentageDiscount;
	int numberOfCarsPurchased;
	int numberOfToyotaPurchased;
	int numberOfKiaPurchased;
	int numberOfHyundaiPurchased;
};

struct totalCarSalesData
{
	char carBrand[15];
	float totalCarSales;
};

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

void Bubble_sort(struct totalCarSalesData arr[], int size)
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
	struct purchaseData* purchases = malloc(sizeof(struct purchaseData) * numberOfLinesInFile);
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

struct carsData* calculateCarsInStock()
{
	// Sets up the array of purchases and the variables used to store how many cars of each type have been sold
	int sizeOfArrayOfPurchases = countLinesInFile(); // Again used to help know how many sales have been made so a loop can run through it
	
	struct purchaseData* purchases = readPurchaseDataFromFileIntoArray();

	int numberOfToyotaSold = 0;
	int numberOfKiaSold = 0;
	int numberOfHyundaiSold = 0;

	// For loop goes through the array of purchases and increments the counters acording to the number of cars sold in each sale
	for (int i = 0; i < sizeOfArrayOfPurchases; i++)
	{
		if (purchases[i].numberOfToyotaPurchased != 0)
		{
			numberOfToyotaSold += purchases[i].numberOfToyotaPurchased;
		}

		if (purchases[i].numberOfKiaPurchased != 0)
		{
			numberOfKiaSold += purchases[i].numberOfKiaPurchased;
		}

		if (purchases[i].numberOfHyundaiPurchased != 0)
		{
			numberOfHyundaiSold += purchases[i].numberOfHyundaiPurchased;
		}

	}

	free(purchases); // free the memory

	struct carsData* cars = malloc(sizeof(struct carsData) * 3); // Makes an array of the cars struct only 3 types of cars in the shop so its size 3

	if (cars == NULL)
	{
		return;
	}

	// Sets up all the information about cars in the array the max stock for each is 20 so subtract the number sold to get amount left
	strcpy(cars[0].carName, "Toyota");
	cars[0].carPrice = TOYOTA_PRICE;
	cars[0].amountOfCar = 20 - numberOfToyotaSold;


	strcpy(cars[1].carName, "KIA");
	cars[1].carPrice = KIA_PRICE;
	cars[1].amountOfCar = 20 - numberOfKiaSold;


	strcpy(cars[2].carName, "Hyundai");
	cars[2].carPrice = HYUNDAI_PRICE;
	cars[2].amountOfCar = 20 - numberOfHyundaiSold;

	return cars; // Returns the array of cars for use in other functions
}

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

struct purchaseData establishCarsUserWishesToPurchase(struct carsData* carsList)
{
	struct purchaseData saleToProcess;
	saleToProcess.totalPrice = 0;
	saleToProcess.pricePaid = 0;
	strcpy(saleToProcess.customerName, " ");
	saleToProcess.customerAge = 0;
	saleToProcess.ifDiscountWasGiven = 'Y';
	saleToProcess.percentageDiscount = 0;
	saleToProcess.numberOfCarsPurchased = 0;
	saleToProcess.numberOfToyotaPurchased = 0;
	saleToProcess.numberOfKiaPurchased = 0;
	saleToProcess.numberOfHyundaiPurchased = 0;

	bool desireToContinue1 = true;

	/* Using another looping menu to see how many cars the user wishes to purchase since cars are not something one generaly buys a lot of at once it 
	seems easier to do it in this simple way rather than have the user enter a number for each and every car type */
	do
	{
		printf("Please select the car model you wish to buy!\n");
		printf("5. Toyota\n");
		printf("6. KIA\n");
		printf("7. Hyundai\n");
		printf("8. I have selected all the cars I wish to purchase\n");
		printf("9. I do not want to purchase any cars\n");

		/*Using the code from DealingWithUserInput to ensure that the character input is properly validatedand no matter what is typed
		  everything will work out all good same as above */

		char menuOption1 = validateInputForSecondMenu();

		switch (menuOption1)
		{
		case '5':
			// carsList[0] is Toyota
			carsList[0].amountOfCar -= 1;
			if (carsList[0].amountOfCar >= 0)
			{
				saleToProcess.totalPrice = saleToProcess.totalPrice + carsList[0].carPrice;
				saleToProcess.numberOfCarsPurchased++;
				saleToProcess.numberOfToyotaPurchased++;
				break;
			}

			else
			{
				printf("I'm sorry but we have no Toyota's left in stock please select another option\n");
				break;
			}

		case '6':
			// carsList[1] is Kia
			carsList[1].amountOfCar -= 1;
			if (carsList[1].amountOfCar >= 0)
			{
				saleToProcess.totalPrice = saleToProcess.totalPrice + carsList[1].carPrice;
				saleToProcess.numberOfCarsPurchased++;
				saleToProcess.numberOfKiaPurchased++;
				break;
			}

			else
			{
				printf("I'm sorry but we have no Kia's left in stock please select another option\n");
				break;
			}


		case '7':
			// carsList[2] is Hyundai
			carsList[2].amountOfCar -= 1;
			if (carsList[2].amountOfCar >= 0)
			{
				saleToProcess.totalPrice = saleToProcess.totalPrice + carsList[2].carPrice;
				saleToProcess.numberOfCarsPurchased++;
				saleToProcess.numberOfHyundaiPurchased++;
				break;
			}

			else
			{
				printf("I'm sorry but we have no Hyundai left in stock please select another option\n");
				break;
			}


		case '8':
			desireToContinue1 = false;
			break;

		case '9':
			saleToProcess.numberOfCarsPurchased = 0; // Used to skip all of the car purchase code and writing to a file
			desireToContinue1 = false; // Allows us to escape this loop
			break;
		}

	} while (desireToContinue1 == true);

	free(carsList);
	return saleToProcess; // Returns the struct set up with all the cars related information 
}

struct purchaseData reciveNameAgeAndCalculateDiscount(struct purchaseData saleToProcess)
{
	// This function sets up all the rest of the data for a sale such as user name ect
	char fullName[200];

	printf("The total undiscounted price of your purchase is: %.2f GBP\n", saleToProcess.totalPrice);
	printf("The total number of cars you purchased is %d\n", saleToProcess.numberOfCarsPurchased);
	printf("The number of Toyota you bought is: %d\n", saleToProcess.numberOfToyotaPurchased);
	printf("The number of Kia you bought is: %d\n", saleToProcess.numberOfKiaPurchased);
	printf("The number of Hyundai you bought is: %d\n", saleToProcess.numberOfHyundaiPurchased);
	printf("Please enter your full name\n");
	scanf(" %[^\n]s", fullName); // Again the holy white space comes to the rescue scans until it hits new line
	fullName[strlen(fullName) + 1] = '\0'; // Just to ensure the string is null terminated
	strcpy(saleToProcess.customerName, fullName);
	printf("Please enter your age\n");
	saleToProcess.customerAge = validateUserAge();

	if (saleToProcess.customerAge > 60)
	{
		saleToProcess.ifDiscountWasGiven = 'Y';
		saleToProcess.percentageDiscount = 10;
		saleToProcess.pricePaid = saleToProcess.totalPrice - (saleToProcess.totalPrice / 10);
		printf("Due to your age you have been given a 10 percent discount\n");
		printf("Your new total is %f", saleToProcess.totalPrice);
	}
	else
	{
		saleToProcess.ifDiscountWasGiven = 'N';
		saleToProcess.percentageDiscount = 0;
		saleToProcess.pricePaid = saleToProcess.totalPrice;
	}
	return saleToProcess;
}

void writeSaleDataToFile(struct purchaseData saleToProcess)
{
	// Simply writes all the data from the given sale into the file to save it
	// https://www.youtube.com/watch?v=7ZFgphYJvUA&ab_channel=PortfolioCourses Used this video as a source
	FILE* fileData = fopen("carSaleData.txt", "a");
	if (fileData == NULL)
	{
		printf("ERROR opening file please\n");
		return;

	}

	fprintf(fileData, "%.2f,%.2f,%d,%c,%d,%d,%d,%d,%d,%s\n",
		saleToProcess.totalPrice,
		saleToProcess.pricePaid,
		saleToProcess.customerAge,
		saleToProcess.ifDiscountWasGiven,
		saleToProcess.percentageDiscount,
		saleToProcess.numberOfCarsPurchased,
		saleToProcess.numberOfToyotaPurchased,
		saleToProcess.numberOfKiaPurchased,
		saleToProcess.numberOfHyundaiPurchased,
		saleToProcess.customerName);

	fclose(fileData);
}

void purchaseACar()
{
	// The culmination of many functions simply executes them all in order to perform the entire buy a car and write to file process
	struct carsData* carsList = calculateCarsInStock();

	struct purchaseData saleToProcess = establishCarsUserWishesToPurchase(carsList);

	if (saleToProcess.numberOfCarsPurchased > 0)
	{
		saleToProcess = reciveNameAgeAndCalculateDiscount(saleToProcess);

		writeSaleDataToFile(saleToProcess);
	}
}

void printAllSalesMade(struct purchaseData* purchases)
{
	// Feed in teh array of all purchases and loop through to print out all the details
	int numberOfSales = countLinesInFile();

	for (int i = 0; i < numberOfSales; i++)
	{
		printf("total price: %.2f GBP\n price paid: %.2f GBP\n customers name: %s\n customers age: %d\n if discount was given: %c\n percentage discount: %d\n number of "
			"cars purchased: %d\n number of Toyota purchased: %d\n number of Kia purchased: %d\n number of Hyundai purchased %d\n",
			purchases[i].totalPrice,
			purchases[i].pricePaid,
			purchases[i].customerName,
			purchases[i].customerAge,
			purchases[i].ifDiscountWasGiven,
			purchases[i].percentageDiscount,
			purchases[i].numberOfCarsPurchased,
			purchases[i].numberOfToyotaPurchased,
			purchases[i].numberOfKiaPurchased,
			purchases[i].numberOfHyundaiPurchased);
		printf("\n");
	}

}

void printSortedProfitForEachBrand(struct purchaseData* purchases)
{
	struct totalCarSalesData toyotaSalesData;
	strcpy(toyotaSalesData.carBrand, "Toyota");
	toyotaSalesData.totalCarSales = 0;

	struct totalCarSalesData kiaSalesData;
	strcpy(kiaSalesData.carBrand, "Kia");
	kiaSalesData.totalCarSales = 0;

	struct totalCarSalesData hyundaiSalesData;
	strcpy(hyundaiSalesData.carBrand, "Hyundai");
	hyundaiSalesData.totalCarSales = 0;

	int numberOfSales = countLinesInFile();

	// The loop goes through and checks each sale for what cars have been purchased with what discounts and adds them up for each type of car

	for (int i = 0; i < numberOfSales; i++)
	{
		if (purchases[i].numberOfToyotaPurchased > 0)
		{
			if (purchases[i].percentageDiscount != 10)
			{
				toyotaSalesData.totalCarSales += (TOYOTA_PRICE * purchases[i].numberOfToyotaPurchased);
			}
			else if (purchases[i].percentageDiscount == 10)
			{
				toyotaSalesData.totalCarSales += ((TOYOTA_PRICE - (TOYOTA_PRICE / 10)) * purchases[i].numberOfToyotaPurchased);
			}
		}

		if (purchases[i].numberOfKiaPurchased > 0)
		{
			if (purchases[i].percentageDiscount != 10)
			{
				kiaSalesData.totalCarSales += (KIA_PRICE * purchases[i].numberOfKiaPurchased);
			}
			else if (purchases[i].percentageDiscount == 10)
			{
				kiaSalesData.totalCarSales += ((KIA_PRICE - (KIA_PRICE / 10)) * purchases[i].numberOfKiaPurchased);
			}
		}

		if (purchases[i].numberOfHyundaiPurchased > 0)
		{
			if (purchases[i].percentageDiscount != 10)
			{
				hyundaiSalesData.totalCarSales += (HYUNDAI_PRICE * purchases[i].numberOfHyundaiPurchased);
			}
			else if (purchases[i].percentageDiscount == 10)
			{
				hyundaiSalesData.totalCarSales += ((HYUNDAI_PRICE - (HYUNDAI_PRICE / 10)) * purchases[i].numberOfHyundaiPurchased);
			}
		}
	}


	/* Using an array of structs because it makes the sorting and printing easier when two of them happen to have the same value such as
	£0 as just using if statements can lead to the program printing the same name for multiple of the cars*/
	struct totalCarSalesData carSalesList[] = { toyotaSalesData, kiaSalesData, hyundaiSalesData };

	Bubble_sort(carSalesList, 3);

	printf("We have made %.2f GBP from %s\n", carSalesList[0].totalCarSales, carSalesList[0].carBrand);
	printf("We have made %.2f GBP from %s\n", carSalesList[1].totalCarSales, carSalesList[1].carBrand);
	printf("We have made %.2f GBP from %s\n", carSalesList[2].totalCarSales, carSalesList[2].carBrand);


}

void viewAllSalesData()
{
	// Runs the two previous functions to print all the data and print the sorted cars sales data
	struct purchaseData* purchases = readPurchaseDataFromFileIntoArray();

	printAllSalesMade(purchases);
	printSortedProfitForEachBrand(purchases);
	free(purchases);

}
