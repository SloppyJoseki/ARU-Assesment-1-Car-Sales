#define _CRT_SECURE_NO_WARNINGS
#define TOYOTA_PRICE 21460.60f
#define KIA_PRICE 14900.00f
#define HYUNDAI_PRICE 19035.20f

#include "stdio.h"  
#include "string.h"
#include "malloc.h"


typedef enum { false = 0, true = 1 } bool;

struct carsData
{
	char carName[15];
	float carPrice;
	int amountOfCar;
};

struct purchaseData
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


/* Function checks the users input by taking the scanf result and then if it matches an expected input the program is allowed to proceed however if the user
fails to input correctly they will get stuck in a loop until the do so additionally it clears the buffer after each itteration so the user is unable to
mess with subsequent inputs */

char reciveCheckedInput()
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


char reciveCheckedInput1()
{
	char menuOption1;
	do
	{
		scanf("\n%c", &menuOption1);
		if (menuOption1 == '5' || menuOption1 == '6' || menuOption1 == '7' || menuOption1 == '8' || menuOption1 == '9')
		{
			return menuOption1;
		}
		else
		{
			printf("Please enter a valid input\n");
		}
		while (getchar() != '\n');
	} while (true);

}

int countLinesInFile()
{
	FILE* fp;
	int count = 0;
	char c;

	fp = fopen("C:\\Users\\Harry\\source\\repos\\Playing with C\\Playing with C\\testData.txt", "r");

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n') // Increment count if this character is newline
			count = count + 1;

	fclose(fp);
	return count;
}

/* Simple insertion sort https://www.youtube.com/watch?v=Tz7vBodZqo8&ab_channel=PortfolioCourses based on this code. A temporary struct is created in order
to allow the swapping of structs inside an array and then the algorithm goes through and divides the array into a sorted subarray and then the larger array
itself. This particular method of sorting is very efficient when there are not many things to sort so its perfect for the small number of cars */

void insertionSort(struct carsData a[], int lengthOfArray)
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

struct purchaseData* readPurchaseDataFromFile()
{
	FILE* fileSalesData;
	int numberOfLinesInFile = countLinesInFile();
	struct purchaseData* purchases = malloc(sizeof(struct purchaseData) * numberOfLinesInFile);
	if (purchases == NULL)
	{
		return;
	}
	fileSalesData = fopen("C:\\Users\\Harry\\source\\repos\\Playing with C\\Playing with C\\testData.txt", "r");

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

		fclose(fileSalesData);

		return purchases;
	}
}

struct carsData* calculateCarsInStock()
{
	struct purchaseData* purchases = readPurchaseDataFromFile();

	int sizeOfArrayOfPurchases = countLinesInFile();

	int numberOfToyotaSold = 0;
	int numberOfKiaSold = 0;
	int numberOfHyundaiSold = 0;

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

	free(purchases);

	struct carsData* cars = malloc(sizeof(struct carsData) * 3);

	if (cars == NULL)
	{
		return;
	}

	strcpy(cars[0].carName, "Toyota");
	cars[0].carPrice = TOYOTA_PRICE;
	cars[0].amountOfCar = 20 - numberOfToyotaSold;


	strcpy(cars[1].carName, "KIA");
	cars[1].carPrice = KIA_PRICE;
	cars[1].amountOfCar = 20 - numberOfKiaSold;


	strcpy(cars[2].carName, "Hyundai");
	cars[2].carPrice = HYUNDAI_PRICE;
	cars[2].amountOfCar = 20 - numberOfHyundaiSold;

	return cars;
}

void viewStockOfCars()
{
	struct carsData* carsList = calculateCarsInStock();
	insertionSort(carsList, 3);

	printf("Here is a list of our stock of cars!\n");
	for (int i = 0; i < 3; i++)
	{
		// The £ sign is a pain to use so just write GBP instead 
		printf("We have %d %s's in stock and they cost %.2f GBP each\n", carsList[i].amountOfCar, carsList[i].carName, carsList[i].carPrice);
	}
	printf("\n");
	free(carsList);
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

		char menuOption1 = reciveCheckedInput1();

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
	return saleToProcess;
}

struct purchaseData reciveNameAgeAndCalculateDiscount(struct purchaseData saleToProcess)
{
	char fullName[200];

	printf("The total price of your purchase is: %.2f GBP\n", saleToProcess.totalPrice);
	printf("The total number of cars you purchased is %d\n", saleToProcess.numberOfCarsPurchased);
	printf("The number of Toyota you bought is: %d\n", saleToProcess.numberOfToyotaPurchased);
	printf("The number of Kia you bought is: %d\n", saleToProcess.numberOfKiaPurchased);
	printf("The number of Hyundai you bought is: %d\n", saleToProcess.numberOfHyundaiPurchased);
	printf("Please enter your full name\n");
	scanf(" %[^\n]s", fullName); // Again the holy white space comes to the rescue scans until it hits new line
	fullName[strlen(fullName) + 1] = '\0'; // Just to ensure the string is null terminated
	strcpy(saleToProcess.customerName, fullName);
	printf("Please enter your age\n");
	scanf("%d", &saleToProcess.customerAge);

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
	// Now it's time to open the file so we can write to it
	// https://www.youtube.com/watch?v=7ZFgphYJvUA&ab_channel=PortfolioCourses Used this video as a source
	FILE* fileData = fopen("C:\\Users\\Harry\\source\\repos\\Playing with C\\Playing with C\\testData.txt", "a");
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
	struct purchaseData* purchases = readPurchaseDataFromFile();

	printAllSalesMade(purchases);
	printSortedProfitForEachBrand(purchases);

}
