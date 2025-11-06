// COMSC-210 | Lab 29 | Dainiz Almazan
// IDE used: CLion

// Include necessary headers for file handling, data structures, etc.
#include <map>
#include <array>
#include <list>
using namespace std;

// Define a function to simulate customer orders, store orders to the supplier, and supplier deliveries
	// Parameters: map of store data, number of intervals

// Define main function
int main () {
	// Initialize a map to store the flower shop's data: customers who come in and what they order, flowers currently in
	// the flower shop inventory, and flowers growing in the supplier's greenhouse.

	// Open an external file to read initial data about flower shop inventory and greenhouse inventory
		// If file does not open, print an error and exit

	// Begin a time-based simulation for running the flower shop
	// for 35 time intervals (i.e. hours shop is open during the week)

	// Read data from file and populate map
		// For each line, extract the flower's name and whether it goes to the flower shop or the greenhouse
		// Insert flower into the appropriate list in the array for the shop
	// Close the file

	// End of main function
	return 0;
}

// Define simulation function
	// For n number of time periods
		// Randomly decide if a customer will arrive
			// If they arrive, randomly decide what they order
				// If the flowers needed for the customer's order are available, remove the flowers from the shop's
				// inventory
				// Otherwise, add the customer to the queue and the necessary flowers for completing their order to the
				// end of the supplier's greenhouse list
		// Randomly decide if flowers in the supplier's greenhouse are ready to deliver
			// If so, add them to the store's inventory
		// If there are customers left in the queue, randomly decide if their order can now be made.
	// Print the changes for this interval, e.g., "Customer ordered {order} and {flowers} were removed from the shop's inventory"
	// Wait or pause briefly to simulate the passage of time between intervals