
void printAllSalesMade(purchaseData* purchases)
{
	// Feed in the array of all purchases and loop through to print out all the details
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

float checkPurchaseForToyota(purchaseData* purchases, int purchaseNumber)
{
	// Checks the current purchase and returns the total amount spent on Toyota cars
	totalCarSalesData toyotaSalesData;
	toyotaSalesData.totalCarSales = 0;

	if (purchases[purchaseNumber].numberOfToyotaPurchased > 0)
	{
		if (purchases[purchaseNumber].percentageDiscount != 10)
		{
			toyotaSalesData.totalCarSales += (TOYOTA_PRICE * purchases[purchaseNumber].numberOfToyotaPurchased);
		}
		else if (purchases[purchaseNumber].percentageDiscount == 10)
		{
			toyotaSalesData.totalCarSales += ((TOYOTA_PRICE - (TOYOTA_PRICE / 10)) * purchases[purchaseNumber].numberOfToyotaPurchased);
		}
	}
	return toyotaSalesData.totalCarSales;
}

float checkPurchaseForKia(purchaseData* purchases, int purchaseNumber)
{
	// Checks the current purchase and returns the total amount spent on Kia cars
	totalCarSalesData kiaSalesData;
	kiaSalesData.totalCarSales = 0;
	if (purchases[purchaseNumber].numberOfKiaPurchased > 0)
	{
		if (purchases[purchaseNumber].percentageDiscount != 10)
		{
			kiaSalesData.totalCarSales += (KIA_PRICE * purchases[purchaseNumber].numberOfKiaPurchased);
		}
		else if (purchases[purchaseNumber].percentageDiscount == 10)
		{
			kiaSalesData.totalCarSales += ((KIA_PRICE - (KIA_PRICE / 10)) * purchases[purchaseNumber].numberOfKiaPurchased);
		}
	}
	return kiaSalesData.totalCarSales;
}

float checkPurchaseForHyundai(purchaseData* purchases, int purchaseNumber)
{
	// Checks the current purchase and returns the total amount spent on Hyundai cars
	totalCarSalesData hyundaiSalesData;
	hyundaiSalesData.totalCarSales = 0;

	if (purchases[purchaseNumber].numberOfHyundaiPurchased > 0)
	{
		if (purchases[purchaseNumber].percentageDiscount != 10)
		{
			hyundaiSalesData.totalCarSales += (HYUNDAI_PRICE * purchases[purchaseNumber].numberOfHyundaiPurchased);
		}
		else if (purchases[purchaseNumber].percentageDiscount == 10)
		{
			hyundaiSalesData.totalCarSales += ((HYUNDAI_PRICE - (HYUNDAI_PRICE / 10)) * purchases[purchaseNumber].numberOfHyundaiPurchased);
		}
	}
	return hyundaiSalesData.totalCarSales;
}

void printProfitForEachBrand(totalCarSalesData carSalesList[NUMBER_OF_CARS])
{
	// Takes in an array of the total sales from each brand and then prints it in order
	for (int i = 0; i < NUMBER_OF_CARS; i++)
	{
		printf("We have made %.2f GBP from %s\n", carSalesList[i].totalCarSales, carSalesList[i].carBrand);
	}
}

void printSortedProfitForEachBrand(purchaseData* purchases)
{
	totalCarSalesData toyotaSalesData;
	strcpy(toyotaSalesData.carBrand, "Toyota");
	toyotaSalesData.totalCarSales = 0;

	totalCarSalesData kiaSalesData;
	strcpy(kiaSalesData.carBrand, "Kia");
	kiaSalesData.totalCarSales = 0;

	totalCarSalesData hyundaiSalesData;
	strcpy(hyundaiSalesData.carBrand, "Hyundai");
	hyundaiSalesData.totalCarSales = 0;

	int numberOfSales = countLinesInFile();

	// The loop goes through and checks each sale for what cars have been purchased with what discounts and adds them up for each type of car

	for (int i = 0; i < numberOfSales; i++)
	{
		toyotaSalesData.totalCarSales += checkPurchaseForToyota(purchases, i);
		kiaSalesData.totalCarSales += checkPurchaseForKia(purchases, i);
		hyundaiSalesData.totalCarSales += checkPurchaseForHyundai(purchases, i);
	}
	totalCarSalesData carSalesList[NUMBER_OF_CARS] = { toyotaSalesData, kiaSalesData, hyundaiSalesData };
	bubble_sort(carSalesList, NUMBER_OF_CARS);
	printProfitForEachBrand(carSalesList);
}

void viewAllSalesData()
{
	// Runs the two previous functions to print all the data and print the sorted cars sales data
	purchaseData* purchases = readPurchaseDataFromFileIntoArray();

	printAllSalesMade(purchases);
	printSortedProfitForEachBrand(purchases);

	free(purchases);

}

