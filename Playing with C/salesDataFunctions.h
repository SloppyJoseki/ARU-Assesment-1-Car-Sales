#include <stdio.h>  // Used for input and output 
#include <string.h> // Used to make interacting with strings easier in partiular strcpy
#include <stdlib.h> // Used for malloc to help control memory


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

	bubble_sort(carSalesList, 3);

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

