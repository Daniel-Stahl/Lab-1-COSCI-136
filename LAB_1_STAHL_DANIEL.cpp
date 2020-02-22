// Lab 1 Stahl, Daniel T TH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

class Item {
public:
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    
    Item(){};
    Item(string itemID, string itemName, int itemQuantity, double itemPrice) {
        //One liners
        this->itemID = itemID;
        this->itemName = itemName;
        this->itemQuantity = itemQuantity;
        this->itemPrice = itemPrice;
    };
};

class Inventory {
public:
    vector<Item>unsortedInventory;
    vector<Item*>sortedInventory;
    
    // File intake function
    
    
    
    void PrintUnsortedInventory() {
        cout << "Unsorted inventory:\n";
        cout << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << "Price\n";
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            cout << left << setw(10)<< unsortedInventory.at(x).itemID << setw(13) << unsortedInventory.at(x).itemName << setw(10) << unsortedInventory.at(x).itemQuantity << "$" << unsortedInventory.at(x).itemPrice << "\n";
        }
        cout << "\n";
    };
    
    void Sort(int sortChoice) { // Sorts array of addresses by user input
        bool sortInventory = true;
        bool toSwap = false;
        
        while (sortInventory) {
            sortInventory = false;
            
            for (int x = 0; x < sortedInventory.size()-1; x++) {
                switch (sortChoice) {
                    case 1:
                        // Item ID
                        toSwap = sortedInventory.at(x)->itemID > sortedInventory.at(x+1)->itemID;
                        break;
                    case 2:
                        // Product Name
                        toSwap = sortedInventory.at(x)->itemName > sortedInventory.at(x+1)->itemName;
                        break;
                    case 3:
                        // QTY
                        toSwap = sortedInventory.at(x)->itemQuantity > sortedInventory.at(x+1)->itemQuantity;
                        break;
                    case 4:
                        // Price
                        toSwap = sortedInventory.at(x)->itemPrice > sortedInventory.at(x+1)->itemPrice;
                        break;
                }
                
                if(toSwap) {
                    Item* temp = sortedInventory.at(x);
                    sortedInventory.at(x) = sortedInventory.at(x+1);
                    sortedInventory.at(x+1) = temp;
                    sortInventory = true;
                }
            }
        }

        PrintSortOutput();
    }
    
    void SearchInventory(string userSearch) { // Searches array for matching item ID or item name
        for (int x = 0; x < userSearch.size(); x++) {
            userSearch[x] = tolower(userSearch[x]);
        }
        
        bool searchFound = false;
        
        for (int y = 0; y < unsortedInventory.size(); y++) {
            if (userSearch == unsortedInventory.at(y).itemID) {
                cout << "\nFound a match in item ID\n";
                PrintSearchOutput(y);
                searchFound = true;
            } else if (userSearch == unsortedInventory.at(y).itemName) {
                cout << "\nFound a match in product name\n";
                PrintSearchOutput(y);
                searchFound = true;
            }
        }
        
        if (searchFound == false) {
            cout << "\nNo match found, returning to main menu.\n" << endl;
        }
    }
    
    void PrintSearchOutput(int subscript) {
        cout << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << "Price\n" << left << setw(10) << unsortedInventory.at(subscript).itemID << setw(13) << unsortedInventory.at(subscript).itemName << setw(10) << unsortedInventory.at(subscript).itemQuantity << "$" << unsortedInventory.at(subscript).itemPrice << "\n" << endl;
    }
    
    void PrintInventoryReport() { // Prints a report of the entire inventory
        int sumItems = 0;
        double sumPrice = 0;
        int sumQuantity = 0;
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            sumItems = x+1;
            sumPrice = (unsortedInventory.at(x).itemPrice * unsortedInventory.at(x).itemQuantity) + sumPrice;
            sumQuantity = unsortedInventory.at(x).itemQuantity + sumQuantity;
        }

        cout << "\nNumber of unique items: " << sumItems << "\n"
        << "Total quantity in stock: " << sumQuantity << "\n"
        << "Total worth of inventory: $" << sumPrice << "\n" << endl;
    }
    
    void PrintSortOutput() { // Prints the output for sorted inventory
        cout << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << "Price\n";
        
        for (int x = 0; x < sortedInventory.size(); x++) {
            cout << left << setw(10)<< sortedInventory.at(x)->itemID << setw(13) << sortedInventory.at(x)->itemName << setw(10) << sortedInventory.at(x)->itemQuantity << "$" << sortedInventory.at(x)->itemPrice << "\n";
        }
        cout << "\n";
    }
};

int main() {
    Inventory inventory;
    ifstream inFile;
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    int userSelection;
    int userSortSelection;
    string searchInventory;
    
    
    // File stuff goes in Inventory with a function
    
    inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/lab 1 refresher/data.txt");
    
    if(!inFile) {
        cout << "No file exists" << endl;
        exit(1);
    } else {
        cout << "File ready!" << endl;
    }
    
    while(!inFile.eof() && inventory.unsortedInventory.size() != 10) { // Check if vector is full
        inFile >> itemID >> itemName >> itemQuantity >> itemPrice;
        
        for (int x = 0; x < itemName.size(); x++) {
            itemName[x] = tolower(itemName[x]);
        }
        
        inventory.unsortedInventory.push_back(Item(itemID, itemName, itemQuantity, itemPrice));
        
        if (inventory.unsortedInventory.size() == 10) {
            cout << "This program can only process 10 items at a time" << endl;
        }
    }
    
    inFile.close();
    
    // try putting this after push_back unsorted
    for (int x = 0; x < inventory.unsortedInventory.size(); x++) {
        inventory.sortedInventory.push_back(&inventory.unsortedInventory.at(x));
    }
    
    // put menu in Inventory via function
    cout << "Hello, please choose from the menu below\n" << endl;
    
    do {
        cout << "1) Print unsorted inventory\n"
        << "2) Print inventory sorted\n"
        << "3) Look up item by ID or name\n"
        << "4) Print report of inventory\n"
        << "5) Quit program" << endl;
        cout << "Enter a number: ";
        cin >> userSelection;
        
        if (!cin || userSelection > 5) { // Checks if user inout is valid
            cin.clear();
            cin.ignore(100, '\n');
            cout << "\nSorry that is not one of the selections from the menu, please try again.\n" << endl;
        } else {
        
        // Switch menu
            switch (userSelection) {
                case 1:
                    // Print unsorted inventory
                    inventory.PrintUnsortedInventory();
                    break;
                case 2:
                    // Print inventory sorted by user choice
                    // Get user to go back to menu
                    cout << "\nHow would you like to sort the inventory?\n"
                    << "1) item ID\n"
                    << "2) item name\n"
                    << "3) quantity on hand\n"
                    << "4) price" << endl;
                    cout << "Enter a number: ";
                    cin >> userSortSelection;
                    
                    if (!cin || userSortSelection > 4) { // Checks if user input is valid
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "\nSorry that is not one of the selections from the menu, please try again.\n" << endl;
                    } else {
                        inventory.Sort(userSortSelection);
                    }
                    
                    break;
                case 3:
                    // Search product by ID or name
                    cout << "\nPlease type the product you want to search?" << endl;
                    cin >> searchInventory;
                    inventory.SearchInventory(searchInventory);
                    break;
                case 4:
                    // Print inventory details
                    inventory.PrintInventoryReport();
                    break;
                default:
                    cout << "\nSorry that is not one of the selections from the menu, please try again.\n" << endl;
                    break;
            }
        }
        
    } while (userSelection != 5);
}
