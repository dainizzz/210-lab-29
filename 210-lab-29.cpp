// COMSC-210 | Lab 30 | Dainiz Almazan
// IDE used: CLion

// Include necessary headers for file handling, data structures, etc.
#include <map>
#include <array>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
using namespace std;

const int SIZE = 3;
const int NUM_FLOWERS = 15;
const string flowers[NUM_FLOWERS] = {
	"Rose",
	"Tulip",
	"Lily",
	"Carnation",
	"Sunflower",
	"Orchid",
	"Daisy",
	"Chrysanthemum",
	"Peony",
	"Hydrangea",
	"Bluebell",
	"Alstroemeria",
	"Iris",
	"Freesia",
	"Ranunculus",
};

// Define a function to simulate customer orders, store orders to the supplier, and supplier deliveries
// Parameters: map of store data, number of intervals
void runSimulation(map<string, array<list<string>, SIZE> >, int);

// Returns a randomly selected flower from the flowers array.
string getRandomFlower();

// Returns a bool representing whether an event occurs
// Parameters: an int representing the percent chance of an event occurring
bool eventOccurs(int);

// Define main function
int main() {
	srand(time(0));
	// Initialize a map to store the flower shop's data: customers who come in and what they order, flowers currently in
	// the flower shop inventory, and flowers growing in the supplier's greenhouse.
	list<string> shopInventory = {};
	list<string> greenhouseInventory = {};
	list<string> customerQueue = {};
	array<list<string>, SIZE> shop1data = {shopInventory, greenhouseInventory, customerQueue};
	map<string, array<list<string>, SIZE> > shops;

	shops.insert(make_pair("shop1", shop1data));

	// Open an external file to read initial data about flower shop inventory and greenhouse inventory
	ifstream infile("flower inventory.txt");
	string tempLoc, tempFlower;
	if (infile.good()) {
		while (infile >> tempLoc) {
			infile >> tempFlower;
			if (tempLoc == "shop")
				shops.at("shop1")[1].push_back(tempFlower);
			else
				shops.at("shop1")[2].push_back(tempFlower);
		}
		infile.close();
	} else {
		// If file does not open, print an error and exit
		cout << "Error opening file." << endl;
	}

	// Begin a time-based simulation for running the flower shop
	// for 35 time intervals (i.e. hours shop is open during the week)
	runSimulation(shops, 35);

	// Read data from file and populate map
	// For each line, extract the flower's name and whether it goes to the flower shop or the greenhouse
	// Insert flower into the appropriate list in the array for the shop
	// Close the file

	// End of main function
	return 0;
}

// Define simulation function
void runSimulation(map<string, array<list<string>, SIZE> > storeData, int intervals) {
	// TODO: ADD FOR SHOP IN SHOPS
	// For n number of time periods
	for (int i = 0; i < intervals; i++) {
		cout << "Interval #" << i + 1 << ':' << endl;

		// EVENT #1: Randomly decide if a customer will arrive (50% chance)
		if (eventOccurs(50)) {
			// If they arrive, randomly decide what they order
			string order = getRandomFlower();
			bool found = false;
			// If the flowers needed for the customer's order are available, remove the flowers from the shop's
			// inventory
			for (auto it = storeData.at("shop1")[1].begin(); it != storeData.at("shop1")[1].end(); ++it) { // TODO: Fix so it's not hardcoded
				if (*it == order) {
					cout << "\tCustomer ordered " << order << " and " << *it << " was removed from the store's inventory." << endl;
					storeData.at("shop1")[1].erase(it);
					found = true;
					break;
				}
			}
			if (!found) {
				// Otherwise, add the customer to the queue and the flower needed for completing their order to the
				// end of the supplier's greenhouse list
				cout << "\tCustomer ordered " << order << " and it was not in stock. A request has been made to the supplier and the customer has been added to the queue" << endl;
				storeData.at("shop1")[2].push_back(order);
				storeData.at("shop1")[3].push_back(order);
			}
		}

		// EVENT  #2: Randomly decide if a flower in the supplier's greenhouse are ready to deliver (75% chance)
		if (eventOccurs(75)) {
			string delivered = storeData.at("shop1")[2].front();
			storeData.at("shop1")[2].pop_front();
			// If so, add them to the store's inventory
			cout << '\t' << delivered << "was"
		}
		// If there are customers left in the queue, randomly decide to check if their order can now be made. (50%)
		if (eventOccurs(50)) {
			// Give customer their order
		}

		// Print the changes for this interval, e.g., "Customer ordered {order} and 1 {flower} was removed from the shop's inventory"
		// Wait or pause briefly to simulate the passage of time between intervals
	}
}

string getRandomFlower() {
	int index = rand() % 15;
	return flowers[index];
}

bool eventOccurs(int probability) {
	return rand() % 100 + 1 <= probability;
}
