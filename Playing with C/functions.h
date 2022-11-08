#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"  
#include "string.h"


typedef enum  { false = 0, true = 1 } bool;

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


/* Creates a large array of purchase data structsand goes through the file reading all the info into that array once the file data is read a loop runs
through the array and checks the number of each type of car sold using 3 counter variables then writes the appropriate info to the relevant car and sorts
then prints the data */

void viewStockOfCars()
{
	FILE* fileSalesData;
	struct purchaseData purchases[60];

	fileSalesData = fopen("C:\\Users\\Harry\\source\\repos\\Car Sales Database\\Car Sales Database\\testData.txt", "r");

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

		int numberOfToyotaSold = 0;
		int numberOfKiaSold = 0;
		int numberOfHyundaiSold = 0;

		for (int i = 0; i < valuesRecorded; i++)
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

		// Saftey check to ensure we can't have a negative number in stock

		if (numberOfToyotaSold > 20)
		{
			numberOfToyotaSold = 20;
		}

		if (numberOfKiaSold > 20)
		{
			numberOfKiaSold = 20;
		}

		if (numberOfHyundaiSold > 20)
		{
			numberOfHyundaiSold = 20;
		}

		struct carsData toyota;
		strcpy(toyota.carName, "Toyota");
		toyota.carPrice = 21460.60f;
		toyota.amountOfCar = 20 - numberOfToyotaSold;

		struct carsData kia;
		strcpy(kia.carName, "KIA");
		kia.carPrice = 14900.00f;
		kia.amountOfCar = 20 - numberOfKiaSold;

		struct carsData hyundai;
		strcpy(hyundai.carName, "Hyundai");
		hyundai.carPrice = 19035.20f;
		hyundai.amountOfCar = 20 - numberOfHyundaiSold;

		struct carsData cars[] = { toyota, kia, hyundai };
		insertionSort(cars, 3);

		printf("Here is a list of our stock of cars!\n");
		for (int i = 0; i < 3; i++)
		{
			// The £ sign is a pain to use so just write GBP instead 
			printf("We have %d %s's in stock and they cost %.2f GBP each\n", cars[i].amountOfCar, cars[i].carName, cars[i].carPrice);
		}
		printf("\n");
	}
}


void purchaseACar()
/* First thing the function does is read the file in order to figure out how many cars are in stock then it goes through the process of allowing the
user to select how many cars they would like to buy */
{

	struct purchaseData saleToProcess;
	saleToProcess.totalPrice = 0;
	saleToProcess.pricePaid = 0;
	strcpy(saleToProcess.customerName, "Harry");
	saleToProcess.customerAge = 0;
	saleToProcess.ifDiscountWasGiven = 'Y';
	saleToProcess.percentageDiscount = 0;
	saleToProcess.numberOfCarsPurchased = 0;
	saleToProcess.numberOfToyotaPurchased = 0;
	saleToProcess.numberOfKiaPurchased = 0;
	saleToProcess.numberOfHyundaiPurchased = 0;

	bool desireToContinue1 = true;
	bool checkIfNeedToPurchaseCar = true;
	float currentPurchaseTotal = 0;
	int carsPurchased = 0;
	char fullName[200];

	FILE* fileSalesData;
	struct purchaseData purchases[60];

	fileSalesData = fopen("C:\\Users\\Harry\\source\\repos\\Car Sales Database\\Car Sales Database\\testData.txt", "r");

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

		int numberOfToyotaSold = 0;
		int numberOfKiaSold = 0;
		int numberOfHyundaiSold = 0;

		for (int i = 0; i < valuesRecorded; i++)
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

		// Saftey check to ensure we can't have a negative number in stock

		if (numberOfToyotaSold > 20)
		{
			numberOfToyotaSold = 20;
		}

		if (numberOfKiaSold > 20)
		{
			numberOfKiaSold = 20;
		}

		if (numberOfHyundaiSold > 20)
		{
			numberOfHyundaiSold = 20;
		}

		struct carsData toyota;
		strcpy(toyota.carName, "Toyota");
		toyota.carPrice = 21460.60f;
		toyota.amountOfCar = 20 - numberOfToyotaSold;

		struct carsData kia;
		strcpy(kia.carName, "KIA");
		kia.carPrice = 14900.00f;
		kia.amountOfCar = 20 - numberOfKiaSold;

		struct carsData hyundai;
		strcpy(hyundai.carName, "Hyundai");
		hyundai.carPrice = 19035.20f;
		hyundai.amountOfCar = 20 - numberOfHyundaiSold;




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
				numberOfToyotaSold += 1;
				if (numberOfToyotaSold <= 20)
				{
					currentPurchaseTotal = currentPurchaseTotal + toyota.carPrice;
					carsPurchased++;
					saleToProcess.numberOfToyotaPurchased++;
					break;
				}

				else
				{
					printf("I'm sorry but we have no Toyota's left in stock please select another option\n");
					break;
				}

			case '6':
				numberOfKiaSold += 1;
				if (numberOfKiaSold <= 20)
				{
					currentPurchaseTotal = currentPurchaseTotal + kia.carPrice;
					carsPurchased++;
					saleToProcess.numberOfKiaPurchased++;
					break;
				}

				else
				{
					printf("I'm sorry but we have no Kia's left in stock please select another option\n");
					break;
				}


			case '7':
				numberOfHyundaiSold += 1;
				if (numberOfHyundaiSold <= 20)
				{
					currentPurchaseTotal = currentPurchaseTotal + hyundai.carPrice;
					carsPurchased++;
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
				checkIfNeedToPurchaseCar = false; // Used to skip all of the car purchase code and writing to a file
				desireToContinue1 = false; // Allows us to escape this loop
				break;
			}

		} while (desireToContinue1 == true);

		if (checkIfNeedToPurchaseCar == true)
		{
			printf("The total price of your purchase is: %.2f GBP\n", currentPurchaseTotal);
			saleToProcess.totalPrice = currentPurchaseTotal;
			printf("The total number of cars you purchased is %d\n", carsPurchased);
			saleToProcess.numberOfCarsPurchased = carsPurchased;
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

			// Now it's time to open the file so we can write to it
			// https://www.youtube.com/watch?v=7ZFgphYJvUA&ab_channel=PortfolioCourses Used this video as a source
			fileSalesData = fopen("C:\\Users\\Harry\\source\\repos\\Car Sales Database\\Car Sales Database\\testData.txt", "a");
			if (fileSalesData == NULL)
			{
				printf("ERROR opening file please\n");
				return;

			}

			fprintf(fileSalesData, "%.2f,%.2f,%d,%c,%d,%d,%d,%d,%d,%s\n",
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

			fclose(fileSalesData);
		}
	}
}