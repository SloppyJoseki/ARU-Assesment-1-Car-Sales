
carsData* calculateCarsInStock()
{
	// Sets up the array of purchases and the variables used to store how many cars of each type have been sold
	int sizeOfArrayOfPurchases = countLinesInFile(); // Again used to help know how many sales have been made so a loop can run through it

	purchaseData* purchases = readPurchaseDataFromFileIntoArray();

	int numberOfToyotaSold = 0;
	int numberOfKiaSold = 0;
	int numberOfHyundaiSold = 0;

	// For loop goes through the array of purchases and increments the counters according to the number of cars sold in each sale
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

	carsData* cars = (carsData*)malloc(sizeof(carsData) * 3); // Makes an array of the cars struct only 3 types of cars in the shop so its size 3

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
	carsData* carsList = calculateCarsInStock(); // Calculates the number of cars in stock with previous function
	insertionSort(carsList, 3); // Sorts that array with the insertion sort

	// Prints all cars in stock
	printf("Here is a list of our stock of cars!\n");
	for (int i = 0; i < 3; i++)
	{
		// The £ sign is a pain to use so just write GBP instead 
		printf("We have %d %s's in stock and they cost %.2f GBP each\n", carsList[i].amountOfCar, carsList[i].carName, carsList[i].carPrice);
	}
	printf("\n");
	free(carsList); // Free the memory taken up by carsList to prevent any memory issues
}