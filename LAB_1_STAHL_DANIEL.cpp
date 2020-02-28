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
    Item(string newItemID, string newItemName, int newItemQty, double newItemPrice) {
        itemID = newItemID; itemName = newItemName; itemQuantity = newItemQty; itemPrice = newItemPrice;
    };
};

class Inventory {
public:
    vector<Item>unsortedInventory;
    vector<Item*>sortedInventory;
    
    void ProcessFile() {
        ifstream inFile;
        string itemID;
        string itemName;
        int itemQuantity;
        double itemPrice;
        
        inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/lab 1 refresher/data.txt");
        
        if(!inFile) {
            cout << "No file exists" << endl;
            exit(1);
        } else {
            cout << "File ready!" << endl;
        }
        
        while(!inFile.eof()) { // Check if vector is full
            inFile >> itemID >> itemName >> itemQuantity >> itemPrice;
            MakeLowercase(itemName);
            unsortedInventory.push_back(Item(itemID, itemName, itemQuantity, itemPrice));
            
        }
        
        inFile.close();
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            sortedInventory.push_back(&unsortedInventory.at(x));
        }
    }
    
    void MakeLowercase(string& testString) {
        for (int x = 0; x < testString.size(); x++) {
            testString[x] = tolower(testString[x]);
        }
    }
    
    bool Sort() { // Sorts array of addresses by user input
        int userSortSelection;
        do {
            cout << "How would you like to sort the inventory? (enter 5 to go back to the main menu)\n" << "1) item ID\n" << "2) item name\n" << "3) quantity on hand\n" << "4) price\n" << "5) Print\n" << "6) Main Menu" << endl;
            cout << "Enter a number: ";
            cin >> userSortSelection;
            cout << "\n";
            
            if (!cin || userSortSelection > 6) { // Checks if user input is valid
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Sorry that is not one of the selections from the menu, please try again.\n";
            } else {
                // Sort here
                bool sorting = true;
                bool toSwap = false;
                
                while (sorting) {
                    sorting = false;
                    
                    for (int x = 0; x < sortedInventory.size()-1; x++) {
                        switch (userSortSelection) {
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
                            sorting = true;
                        }
                    }
                }
                
                if (!sorting && userSortSelection < 5) {
                    cout << "Sort complete\n";
                }
            }
        } while (userSortSelection < 5);
        
        if (userSortSelection == 5) {
            return true;
        } else {
            return false;
        }
    }
    
    void SearchItem() { // Searches array for matching item ID or item name
        string userSearch;
        bool searchFound = false;
        
        while (userSearch != "main") {
            cout << "Please type the ID or product name you want to search for\n" << "(type main to return to the main menu)\n" << "Search: ";
            cin >> userSearch;
            
            MakeLowercase(userSearch);
            
            searchFound = false;
            
            if (userSearch != "main") {
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
                    cout << "\nNo match found, please search again or type back to go to the main menu\n";
                }
            } else {
                cout << "\nReturning to main menu\n";
            }
        }
    }
    
    void PrintSearchOutput(int subscript) {
        cout << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << "Price\n" << left << setw(10) << unsortedInventory.at(subscript).itemID << setw(13) << unsortedInventory.at(subscript).itemName << setw(10) << unsortedInventory.at(subscript).itemQuantity << "$" << unsortedInventory.at(subscript).itemPrice << "\n" << endl;
    }
    
    void PrintReport() { // Prints a report of the entire inventory
        int sumItems = 0;
        double sumPrice = 0.0;
        int sumQuantity = 0;
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            sumItems = x+1;
            sumPrice = (unsortedInventory.at(x).itemPrice * unsortedInventory.at(x).itemQuantity) + sumPrice;
            sumQuantity = unsortedInventory.at(x).itemQuantity + sumQuantity;
        }

        cout << "\nNumber of unique items: " << sumItems << "\n"
        << "Total quantity in stock: " << sumQuantity << "\n"
        << "Total worth of inventory: $" << setprecision (2) << fixed << sumPrice << "\n" << endl;
    }
    
    void PrintUnsorted() {
        cout << "Unsorted inventory:\n" << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << setw(8) << right <<"Price\n";
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            cout << left << setw(10)<< unsortedInventory.at(x).itemID << setw(13) << unsortedInventory.at(x).itemName << setw(8) << right << unsortedInventory.at(x).itemQuantity << setw(10) << right << unsortedInventory.at(x).itemPrice << "\n";
        }
        cout << "\n";
    };
    
    void PrintSortOutput() { // Prints the output for sorted inventory
        cout << "Sorted inventory:\n" << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << setw(8) << right << "Price\n";
        
        for (int x = 0; x < sortedInventory.size(); x++) {
            cout << left << setw(10)<< sortedInventory.at(x)->itemID << setw(13) << sortedInventory.at(x)->itemName << setw(8) << right << sortedInventory.at(x)->itemQuantity << setw(10) << right << sortedInventory.at(x)->itemPrice << "\n";
        }
        cout << "\n";
    }
};

void MainMenu(Inventory inventory);

int main() {
    Inventory inventory;
    inventory.ProcessFile();
    MainMenu(inventory);
}

void MainMenu(Inventory inventory) {
    int userSelection;
    string searchInventory;
    
    cout << "Hello, please choose from the menu below\n" << endl;
    
    do {
        cout << "Main Menu\n" << "1) Print unsorted inventory\n" << "2) Print inventory sorted\n" << "3) Look up item by ID or name\n" << "4) Print report of inventory\n" << "5) Quit program" << endl;
        cout << "Enter a number: ";
        cin >> userSelection;
        cout << "\n";
        
        if (!cin || userSelection > 5) { // Checks if user inout is valid
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Sorry that is not one of the selections from the menu, please try again." << endl;
        } else {
            // Switch menu
            switch (userSelection) {
                case 1:
                    // Prints unsorted inventory
                    inventory.PrintUnsorted();
                    break;
                case 2:
                    // Prints inventory sorted by user choice
                    if (inventory.Sort()) {
                       inventory.PrintSortOutput();
                    }
                    break;
                case 3:
                    // Searchs product by ID or name
                    inventory.SearchItem();
                    break;
                case 4:
                    // Prints inventory details
                    inventory.PrintReport();
                    break;
            }
        }
    } while (userSelection != 5);
}
