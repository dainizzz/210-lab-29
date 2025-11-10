// COMSC-210 | Lab 31 | Dainiz Almazan
// IDE used: CLion

#include <map>
#include <array>
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

const int SIZE = 3;
const int NUM_FLOWERS = 15;
const string flowers[NUM_FLOWERS] = {
	"Rose", "Tulip", "Lily", "Carnation", "Sunflower",
	"Orchid", "Daisy", "Chrysanthemum", "Peony", "Hydrangea",
	"Bluebell", "Alstroemeria", "Iris", "Freesia", "Ranunculus",
};

// runSimulation() simulates three events for a specified number of intervals: 1) a customer makes an order, 2) an item
//		is delivered from the supplier to the shop, 3) a customer in the queue is helped
// arguments: map of store data, number of intervals to run the simulation, probability of event 1 (0-100), probability
//		of event 2 (0-100), probability of event 3 (0-100)
// returns: nothing
void runSimulation(map<string, array<list<string>, SIZE> > &, int, int, int, int);

// getRandomFlower() randomly selects a flower from the flowers array and returns it.
// arguments: none
// returns: a string flower name
string getRandomFlower();

// eventOccurs() determines whether an event with a given probability occurs or not
// arguments: an int value 0-100 representing the percent chance of an event occurring
// returns: a bool value representing whether the event occurs
bool eventOccurs(int);

// testSimulationEvents() performs a unit test of the runSimulation() function
void testSimulationEvents();

// Define main function
int main() {
	srand(time(0));

	// Initialize a map to store the flower shop's data: customers who come in and what they order, flowers currently in
	// the flower shop inventory, and flowers growing in the supplier's greenhouse.
	map<string, array<list<string>, SIZE> > shops;

	array<list<string>, SIZE> shop1data = {};
	shops.insert(make_pair("Shop 1", shop1data));

	array<list<string>, SIZE> shop2data = {};
	shops.insert(make_pair("Shop 2", shop2data));

	// Open an external file to read initial data about flower shop inventory and greenhouse inventory
	ifstream infile("flower inventory.txt");
	string tempLoc, tempFlower;
	if (infile.good()) {
		while (infile >> tempLoc) {
			infile >> tempFlower;
			if (tempLoc == "shop") {
				shops.at("Shop 1")[0].push_back(tempFlower);
				shops.at("Shop 2")[0].push_back(tempFlower);
			}
			else {
				shops.at("Shop 1")[1].push_back(tempFlower);
				shops.at("Shop 2")[1].push_back(tempFlower);
			}
		}
		infile.close();
	} else {
		// If file does not open, print an error and exit
		cout << "Error opening file." << endl;
	}

	// EVENT #1: Randomly decide if a customer will arrive (75% chance)
	// EVENT #2: Randomly decide if a flower in the supplier's greenhouse are ready to deliver (25% chance)
	// EVENT #3: If there are customers in the queue, randomly decide to check if their order is ready (60% chance)
	cout << "Beginning a simulation for 35 intervals (i.e. hours shop is open during a week):" << endl;
	runSimulation(shops, 35, 75, 25, 60);

	return 0;
}

void runSimulation(map<string, array<list<string>, SIZE> > &shops, int intervals, int event1Probability, int event2Probability, int event3Probability) {
	for (auto &shop: shops) {
		cout << shop.first << " simulation:" << endl;
		for (int i = 0; i < intervals; i++) {
			cout << "Interval #" << i + 1 << ':' << endl;
			bool anyEventOccurred = false;

			// EVENT #1: Randomly decide if a customer will arrive
			if (eventOccurs(event1Probability)) {
				anyEventOccurred = true;
				string order = getRandomFlower();
				bool found = false;
				auto it = shop.second[0].begin();
				while (!found && it != shop.second[0].end()) {
					if (*it == order) {
						cout << "\tCustomer ordered 1 " << order << " and 1 " << *it <<
								" was removed from the store's inventory." << endl;
						shop.second[0].erase(it);
						found = true;
						break;
					}
					++it;
				}

				if (!found) {
					cout << "\tCustomer ordered 1 " << order <<
							" and it was not in stock. A request has been made to the supplier "
							<< "and the customer has been added to the queue" << endl;
					shop.second[1].push_back(order);
					shop.second[2].push_back(order);
				}
			}

			// EVENT #2: Randomly decide if a flower in the supplier's greenhouse are ready to deliver
			if (eventOccurs(event2Probability) && !shop.second[1].empty()) {
				anyEventOccurred = true;
				string delivered = shop.second[1].front();
				shop.second[0].push_back(delivered);
				shop.second[1].pop_front();
				// If so, add them to the store's inventory
				cout << "\t1 " << delivered << " was added to the store inventory from the greenhouse." << endl;
			}

			// EVENT #3: If there are customers in the queue, randomly decide to check if their order is ready
			if (eventOccurs(event3Probability)) {
				if (!shop.second[2].empty()) {
					anyEventOccurred = true;
					// Give customer their order if it's available
					for (auto it = shop.second[0].begin(); it != shop.second[0].end(); ++it) {
						if (*it == shop.second[2].front()) {
							// If the first customer in the queue's order is in stock
							cout << "\tCustomer's " << *it << " order was ready and 1 " << *it <<
									" was removed from the store's inventory." << endl;
							shop.second[0].erase(it);
							shop.second[2].pop_front();
							break;
						}
					}
				}
			}

			if (!anyEventOccurred)
				cout << "\tNothing happened." << endl;

			// Wait or pause briefly to simulate the passage of time between intervals
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
}

string getRandomFlower() {
	int index = rand() % 15;
	return flowers[index];
}

bool eventOccurs(int probability) {
	return rand() % 100 + 1 <= probability;
}

void testSimulationEvents() {
	list<string> shopInventory = {"Rose", "Tulip", "Lily",};
	list<string> greenhouseInventory = {"Chrysanthemum", "Peony", "Hydrangea"};
	list<string> customerOrderQueue = {"Rose"};
	array<list<string>, SIZE> testShopData = {shopInventory, greenhouseInventory, customerOrderQueue};
	map<string, array<list<string>, SIZE> > shops;
	shops.insert(make_pair("Test Shop", testShopData));

	// PRINT DATA BEFORE
	cout << "Test Shop data before simulation:" << endl;
	cout << "\t Shop inventory: ";
	for (string flower : shops.at("Test Shop")[0])
		cout << flower << " ";
	cout << "\n\t Greenhouse inventory: ";
	for (string flower : shops.at("Test Shop")[1])
		cout << flower << " ";
	cout << "\n\t Customer order queue: ";
	for (string flower : shops.at("Test Shop")[2])
		cout << flower << " ";
	cout << endl << endl;

	// Testing each event occurring in an interval to make sure all events work correctly
	runSimulation(shops, 1, 100, 100, 100);

	// PRINT DATA AFTER
	cout << "\n\nTest Shop data after simulation:" << endl;
	cout << "\n\t Shop inventory: ";
	for (string flower : shops.at("Test Shop")[0])
		cout << flower << " ";
	cout << "\n\t Greenhouse inventory: ";
	for (string flower : shops.at("Test Shop")[1])
		cout << flower << " ";
	cout << "\n\t Customer order queue: ";
	for (string flower : shops.at("Test Shop")[2])
		cout << flower << " ";
	cout << endl;
}