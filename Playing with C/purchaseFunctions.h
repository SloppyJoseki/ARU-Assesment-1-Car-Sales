
void printCarSaleOptionsMenu()
{
	printf("Please select the car model you wish to buy!\n");
	printf("5. Toyota\n");
	printf("6. KIA\n");
	printf("7. Hyundai\n");
	printf("8. I have selected all the cars I wish to purchase\n");
	printf("9. I do not want to purchase any cars\n");
}

purchaseData establishCarsUserWishesToPurchase(carsData* carsList)
{
	purchaseData saleToProcess;
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

	/* Using another looping menu to see how many cars the user wishes to purchase since cars are not something one generally buys a lot of at once it
	seems easier to do it in this simple way rather than have the user enter a number for each and every car type */
	do
	{
		printCarSaleOptionsMenu();

		/*Using the code from DealingWithUserInput to ensure that the character input is properly validated and no matter what is typed
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

void printSaleInformation(purchaseData saleToProcess)
{
	printf("The total undiscounted price of your purchase is: %.2f GBP\n", saleToProcess.totalPrice);
	printf("The total number of cars you purchased is %d\n", saleToProcess.numberOfCarsPurchased);
	printf("The number of Toyota you bought is: %d\n", saleToProcess.numberOfToyotaPurchased);
	printf("The number of Kia you bought is: %d\n", saleToProcess.numberOfKiaPurchased);
	printf("The number of Hyundai you bought is: %d\n", saleToProcess.numberOfHyundaiPurchased);
}

purchaseData takeUserName(purchaseData saleToProcess)
{
	char fullName[200];
	printf("Please enter your full name\n");
	scanf(" %[^\n]s", fullName); // Again the holy white space comes to the rescue scans until it hits new line
	fullName[strlen(fullName) + 1] = '\0'; // Just to ensure the string is null terminated
	strcpy(saleToProcess.customerName, fullName);
	return saleToProcess;
}

purchaseData takeUserAge(purchaseData saleToProcess)
{
	printf("Please enter your age\n");
	saleToProcess.customerAge = validateUserAge();
	return saleToProcess;
}

purchaseData checkforDiscount(purchaseData saleToProcess)
{
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

void writeSaleDataToFile(purchaseData saleToProcess)
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
	carsData* carsList = calculateCarsInStock();

	purchaseData saleToProcess = establishCarsUserWishesToPurchase(carsList);

	if (saleToProcess.numberOfCarsPurchased > 0)
	{
		printSaleInformation(saleToProcess);
		saleToProcess = takeUserName(saleToProcess);
		saleToProcess = takeUserAge(saleToProcess);
		saleToProcess = checkforDiscount(saleToProcess);

		writeSaleDataToFile(saleToProcess);
	}
}