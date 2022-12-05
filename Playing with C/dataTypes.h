// Prices based on googling for random cars these brands sell
#define TOYOTA_PRICE 21460.60f
#define KIA_PRICE 14900.00f
#define HYUNDAI_PRICE 19035.20f

typedef enum { false = 0, true = 1 } bool; // Defining a bool type variable with false and true to improve code readability

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

