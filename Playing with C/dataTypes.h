// Prices based on googling for random cars these brands sell
#define TOYOTA_PRICE 21460.60f
#define KIA_PRICE 14900.00f
#define HYUNDAI_PRICE 19035.20f

typedef enum { false = 0, true = 1 } bool; // Defining a bool type variable with false and true to improve code readability

// The Pluralsight corse "Using storage classes in C" made me aware I can use typedef in my structs so I don't have to type struct every time I use them
typedef struct carsData  // The basic way to store simple information about the cars this program interacts with
{
	char carName[15];
	float carPrice;
	int amountOfCar;
}carsData;

typedef struct purchaseData // When interacting with the data from the file its easy to store it all in an array of these structs
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
}purchaseData;

typedef struct totalCarSalesData
{
	char carBrand[15];
	float totalCarSales;
}totalCarSalesData;

