// Lab 1 Stahl, Daniel T TH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class InventoryItems {
public:
    vector<InventoryItems>unsortedInventory;
    vector<InventoryItems*>sortedInventory;
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    
    InventoryItems(){};
    InventoryItems(string itemID, string itemName, int itemQuantity, double itemPrice) {
        this->itemID = itemID;
        this->itemName = itemName;
        this->itemQuantity = itemQuantity;
        this->itemPrice = itemPrice;
    };
    
    void PrintUnsortedInventory() {
        cout << "Unsorted inventory:" << endl;
        for (int x = 0; x < unsortedInventory.size(); x++) {
            cout << "Item ID: " << unsortedInventory.at(x).itemID << "\n"
            << "Product Name: " << unsortedInventory.at(x).itemName << "\n"
            << "Quantity: " << unsortedInventory.at(x).itemQuantity << "\n"
            << "Price: " << "$" << unsortedInventory.at(x).itemPrice << endl;
            cout << "\n";
        }
    };
    
    // Better parameter place holder
    void Swap(InventoryItems*& itemA, InventoryItems*& itemB) {
        InventoryItems* temp = itemA;
        itemA = itemB;
        itemB = temp;
    }
    
    void Sort(int sortChoice) {
        bool sortInventory = true;
        
        while (sortInventory) {
            sortInventory = false;
            
            for (int x = 0; x < sortedInventory.size()-1; x++) {
            
                switch (sortChoice) {
                    case 1:
                        // Item ID
                        if (sortedInventory.at(x)->itemID > sortedInventory.at(x+1)->itemID) {
                            Swap(sortedInventory.at(x), sortedInventory.at(x+1));
                            sortInventory = true;
                        }
                        break;
                    case 2:
                        // Product Name
                        if (sortedInventory.at(x)->itemName > sortedInventory.at(x+1)->itemName) {
                            Swap(sortedInventory.at(x), sortedInventory.at(x+1));
                            sortInventory = true;
                        }
                        break;
                    case 3:
                        // QTY
                        if (sortedInventory.at(x)->itemQuantity > sortedInventory.at(x+1)->itemQuantity) {
                            Swap(sortedInventory.at(x), sortedInventory.at(x+1));
                            sortInventory = true;
                        }
                        break;
                    case 4:
                        // Price
                        if (sortedInventory.at(x)->itemPrice > sortedInventory.at(x+1)->itemPrice) {
                            Swap(sortedInventory.at(x), sortedInventory.at(x+1));
                            sortInventory = true;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
        }
        
        for (int x = 0; x < sortedInventory.size(); x++) {
            cout << "Item ID: " << sortedInventory.at(x)->itemID << endl;
            cout << "Product Name: " << sortedInventory.at(x)->itemName << endl;
            cout << "Quantity: " << sortedInventory.at(x)->itemQuantity << endl;
            cout << "Price: " << "$" << sortedInventory.at(x)->itemPrice << endl;
            cout << endl;
        }
    }
    
    void SearchInventory(string userSearch) {
        for (int x = 0; x < userSearch.size(); x++) {
            userSearch[x] = tolower(userSearch[x]);
        }
        
        bool searchFound = false;
        
        for (int y = 0; y < unsortedInventory.size(); y++) {
            if (userSearch == unsortedInventory.at(y).itemID) {
                cout << "Found a match in item ID\n"
                << "Item ID: " << unsortedInventory.at(y).itemID << "\n"
                << "Product Name: " << unsortedInventory.at(y).itemName << "\n"
                << "Quantity: " << unsortedInventory.at(y).itemQuantity << "\n"
                << "Price: " << "$" << unsortedInventory.at(y).itemPrice << endl;
                searchFound = true;
            } else if (userSearch == unsortedInventory.at(y).itemName) {
                cout << "Found a match in product name\n"
                << "Item ID: " << unsortedInventory.at(y).itemID << "\n"
                << "Product Name: " << unsortedInventory.at(y).itemName << "\n"
                << "Quantity: " << unsortedInventory.at(y).itemQuantity << "\n"
                << "Price: " << "$" << unsortedInventory.at(y).itemPrice << endl;
                searchFound = true;
            }
        }
        
        if (searchFound == false) {
            cout << "No match found, returning to main menu." << endl;
        }
    }
    
    void PrintInventoryReport() {
        int sumItems = 0;
        double sumPrice = 0;
        int sumQuantity = 0;
        
        for (int x = 0; x < unsortedInventory.size(); x++) {
            sumItems = x+1;
            sumPrice = (unsortedInventory.at(x).itemPrice * unsortedInventory.at(x).itemQuantity) + sumPrice;
            sumQuantity = unsortedInventory.at(x).itemQuantity + sumQuantity;
        }

        cout << "Number of unique items: " << sumItems << "\n"
        << "Total quantity in stock: " << sumQuantity << "\n"
        << "Total worth of inventory: $" << sumPrice << endl;
    }
};

int main() {
    InventoryItems inventoryItems;
    ifstream inFile;
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    int userSelection;
    int userSortSelection;
    string searchInventory;
    
    
    inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/lab 1 refresher/data.txt");
    
    if(!inFile) {
        cout << "No file exists" << endl;
        exit(1);
    } else {
        cout << "File ready!" << endl;
    }
    
    while(!inFile.eof() && inventoryItems.unsortedInventory.size() != 10) {
        // while infile end of file and array is not larger than 10. Spit out cant take more data.
        inFile >> itemID >> itemName >> itemQuantity >> itemPrice;
        
        for (int x = 0; x < itemName.size(); x++) {
            itemName[x] = tolower(itemName[x]);
        }
        
        inventoryItems.unsortedInventory.push_back(InventoryItems(itemID, itemName, itemQuantity, itemPrice));
        
        if (inventoryItems.unsortedInventory.size() == 10) {
            cout << "This program can only process 10 items at a time" << endl;
        }
    }
    
    inFile.close();
    
    for (int x = 0; x < inventoryItems.unsortedInventory.size(); x++) {
        inventoryItems.sortedInventory.push_back(&inventoryItems.unsortedInventory.at(x));
    }
    
    // Menu
    
    cout << "Hello, please choose from the menu below" << endl;
    
    do {
        cout << "1) Print unsorted inventory\n"
        << "2) Print inventory sorted\n"
        << "3) Look up item by ID or name\n"
        << "4) Print report of inventory\n"
        << "5) Quit program" << endl;
        cout << "Enter a number: ";
        cin >> userSelection;
        cout << "\n";
        
        if (!cin || userSelection > 5) {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "Sorry that is not one of the selections from the menu, please try again.\n" << endl;
        } else {
        
        // Switch menu
            switch (userSelection) {
                case 1:
                    // Print unsorted inventory
                    inventoryItems.PrintUnsortedInventory();
                    break;
                case 2:
                    // Print inventory sorted by user choice
                    // Check user input if bad then repeat this menu
                    cout << "How would you like to sort the inventory?\n"
                    << "1) item ID\n"
                    << "2) item name\n"
                    << "3) quantity on hand\n"
                    << "4) price" << endl;
                    cout << "Enter a number: ";
                    cin >> userSortSelection;
                    cout << "\n";
                    
                    if (!cin || userSortSelection > 4) {
                        cin.clear();
                        cin.ignore(10, '\n');
                        cout << "Sorry that is not one of the selections from the menu, please try again.\n" << endl;
                    } else {
                        inventoryItems.Sort(userSortSelection);
                    }
                    
                    break;
                case 3:
                    //Search product by ID or name
                    cout << "Please type the product you want to search?" << endl;
                    cin >> searchInventory;
                    inventoryItems.SearchInventory(searchInventory);
                    break;
                case 4:
                    // Print inventory details
                    inventoryItems.PrintInventoryReport();
                    break;
                default:
                    break;
            }
        }
        
    } while (userSelection != 5);
}

/*
 
 Testing:
 check user input
 check if file is too big
 check if no data in file
 
 Write a modularized, menu-driven program to read a file with the unknown number of records.
 
 * [done] The input file has an unknown number of records of inventory items (may be empty); one record per line in the following  order: item ID, item  name (one word), quantity on hand, and a price
 * [done] All fields in the input file are separated by a tab (‘\t’) or a blank (up to you)
 * All items are unique
 * Item Id and name do not require error checking
 * [done] Create a menu (use a switch statement) which allows to
 * [done] print the inventory unsorted
 * [done] print the inventory sorted in ascending order; you should allow a user sort by any field: item ID, item name (one word), quantity on hand, or price. Write one function, that can sort by any field using array of pointers. Do not copy and paste sort code five times into the same function. Bubble sort is the easiest to modify.
 * [done] search for an item by ID or name; a user should be able to enter the name of the item using any case, (for example, sTRolleR). You may wish to store items in all lower/upper case to expedite the search.
 * [done] print a report with the following details
    - number of unique items in the inventory
    - the total worth of the inventory and the total count of all items in the inventory
 * [done] quit the program
 A user should be able to run many as many times as a user wants
 Use array of structs if you do not know how to write classes yet
 Thoroughly test your program. Your grade partially depends on the quality of your test data.
 This a and all other  programs in this course must comply with the Guidelines and Standards posted under Resources
 Clearly label the output
 Record sample: 997196478 StroLLer 25 134.78
 
 */


