// Lab 1 Stahl, Daniel T TH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

void MakeLowercase(string& testString);

class Item {
private:
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    
public:
    Item(){};
    Item(string newItemID, string newItemName, int newItemQty, double newItemPrice) {
        SetItemID(newItemID); SetItemName(newItemName); SetItemQty(newItemQty); SetItemPrice(newItemPrice);
    };
    
    string GetItemID();
    string GetItemName();
    int GetItemQty();
    double GetItemPrice();
    
    void SetItemID(string newItemID);
    void SetItemName(string newItemName);
    void SetItemQty(int newItemQty);
    void SetItemPrice(double newItemPrice);

    void PrintItem();
};

class Inventory {
private:
    vector<Item>unsortedInventory;
    vector<Item*>sortedInventory;
    
public:
    void ProcessFile();
    void SortMenu();
    void Sort(int userChoice);
    void SearchItem();
    void PrintReport();
    void PrintUnsorted();
    void PrintSort();
};

void MainMenu(Inventory inventory);

int main() {
    Inventory inventory;
    inventory.ProcessFile();
    MainMenu(inventory);
}

void MainMenu(Inventory inventory) { // Promts menus for user
    int userSelection;
    string searchInventory;
    
    cout << "Hello, please choose from the menu below\n" << endl;
    
    do {
        cout << "Main Menu\n" << "1) Print unsorted inventory\n" << "2) Print inventory sorted\n" << "3) Look up item by ID or name\n" << "4) Print report of inventory\n" << "5) Quit program" << endl;
        cout << "Enter a number: ";
        cin >> userSelection;
        cout << "\n";
        
        if (!cin || userSelection > 5) { // Checks if user input is valid
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
                    inventory.SortMenu();
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

void MakeLowercase(string& testString) { // Makes strings lowercase
    for (int x = 0; x < testString.size(); x++) {
        testString[x] = tolower(testString[x]);
    }
}

void Inventory::ProcessFile() { // Fills inventory with items from file
    ifstream inFile;
    ofstream errorFile;
    string itemID;
    string itemName;
    int itemQuantity;
    double itemPrice;
    
    inFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/lab 1 refresher/data.txt");
    errorFile.open("/Users/stahl/Desktop/Pierce College/COSCI 136/lab 1 refresher/Error Log.txt");
    
    if(!inFile) {
        cout << "No file exists" << endl;
        exit(1);
    } else {
        cout << "File ready!" << endl;
    }
    
    if(!errorFile) {
        cout << "No file exists" << endl;
        exit(2);
    } else {
        cout << "Error File ready!" << endl;
    }
    
    while(!inFile.eof()) {
        inFile >> itemID >> itemName >> itemQuantity >> itemPrice;
        if (itemQuantity < 0 || itemPrice < 0) {
            errorFile << itemID << " " << itemName << " " << itemQuantity << " " << itemPrice << "\n";
        } else {
            MakeLowercase(itemName);
            MakeLowercase(itemID);
            unsortedInventory.push_back(Item(itemID, itemName, itemQuantity, itemPrice));
        }
    }
    
    inFile.close();
    errorFile.close();
    
    for (int x = 0; x < unsortedInventory.size(); x++) {
        sortedInventory.push_back(&unsortedInventory.at(x));
    }
}

void Inventory::SortMenu() { // Prompts the sort menu to user
    int userSortSelection;
    do {
        cout << "How would you like to sort the inventory? (enter 6 to go back to the main menu)\n" << "1) item ID\n" << "2) item name\n" << "3) quantity on hand\n" << "4) price\n" << "5) Main Menu" << endl;
        cout << "Enter a number: ";
        cin >> userSortSelection;
        cout << "\n";
        
        if (!cin || userSortSelection > 5) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Sorry that is not one of the selections from the menu, please try again.\n";
        } else {
            // Sort here
            Sort(userSortSelection);
            PrintSort();
        }
    } while (userSortSelection < 5);
}

void Inventory::Sort(int userChoice) { // Sorts inventory by user choice
    bool sorting = true;
    bool toSwap = false;
    
    while (sorting) {
        sorting = false;
        
        for (int x = 0; x < sortedInventory.size()-1; x++) {
            switch (userChoice) {
                case 1:
                    // Item ID
                    toSwap = sortedInventory.at(x)->GetItemID() > sortedInventory.at(x+1)->GetItemID();
                    break;
                case 2:
                    // Product Name
                    toSwap = sortedInventory.at(x)->GetItemName() > sortedInventory.at(x+1)->GetItemName();
                    break;
                case 3:
                    // QTY
                    toSwap = sortedInventory.at(x)->GetItemQty() > sortedInventory.at(x+1)->GetItemQty();
                    break;
                case 4:
                    // Price
                    toSwap = sortedInventory.at(x)->GetItemPrice() > sortedInventory.at(x+1)->GetItemPrice();
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
    
    if (!sorting && userChoice < 5) {
        cout << "Sort complete\n";
    }
}

void Inventory::SearchItem() { // Searches array for matching item ID or item name
    string userSearch;
    bool searchFound = false;
    Item* item = nullptr;
    
    while (userSearch != "main") {
        cout << "Please type the ID or product name you want to search for\n" << "(type main to return to the main menu)\n" << "Search: ";
        cin >> userSearch;
        
        MakeLowercase(userSearch);
        
        searchFound = false;
        
        if (userSearch != "main") {
            for (int y = 0; y < unsortedInventory.size() && !searchFound; y++) {
                if (userSearch == unsortedInventory.at(y).GetItemID() || userSearch == unsortedInventory.at(y).GetItemName()) {
                    item = &unsortedInventory.at(y);
                    item->PrintItem();
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

void Inventory::PrintReport() { // Prints a report of the entire inventory
    int sumItems = 0;
    double sumPrice = 0.0;
    int sumQuantity = 0;
    
    for (int x = 0; x < unsortedInventory.size(); x++) {
        sumItems = x+1;
        sumPrice = (unsortedInventory.at(x).GetItemPrice() * unsortedInventory.at(x).GetItemQty()) + sumPrice;
        sumQuantity = unsortedInventory.at(x).GetItemQty() + sumQuantity;
    }
    
    cout << "Number of unique items: " << sumItems << "\n" << "Total quantity in stock: " << sumQuantity << "\n" << "Total worth of inventory: $" << setprecision (2) << fixed << sumPrice << "\n" << endl;
}

void Inventory::PrintUnsorted() { // Prints unsorted inventory
    cout << "Unsorted inventory:\n" << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << setw(8) << right <<"Price\n";
    
    for (int x = 0; x < unsortedInventory.size(); x++) {
        cout << left << setw(10)<< unsortedInventory.at(x).GetItemID() << setw(13) << unsortedInventory.at(x).GetItemName() << setw(8) << right << unsortedInventory.at(x).GetItemQty() << setw(10) << right << unsortedInventory.at(x).GetItemPrice() << "\n";
    }
    cout << "\n";
}

void Inventory::PrintSort() { // Prints sorted inventory
    cout << "Sorted inventory:\n" << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << setw(8) << right << "Price\n";
    
    for (int x = 0; x < sortedInventory.size(); x++) {
        cout << left << setw(10)<< sortedInventory.at(x)->GetItemID() << setw(13) << sortedInventory.at(x)->GetItemName() << setw(8) << right << sortedInventory.at(x)->GetItemQty() << setw(10) << right << sortedInventory.at(x)->GetItemPrice() << "\n";
    }
    cout << "\n";
}

string Item::GetItemID() { return itemID; };

string Item::GetItemName() { return itemName; };

int Item::GetItemQty() { return itemQuantity; };

double Item::GetItemPrice() { return itemPrice; };

void Item::SetItemID(string newItemID) { itemID = newItemID; };

void Item::SetItemName(string newItemName) { itemName = newItemName; };

void Item::SetItemQty(int newItemQty) { itemQuantity = newItemQty; };

void Item::SetItemPrice(double newItemPrice) { itemPrice = newItemPrice; };

void Item::PrintItem() { // Prints a single item from inventory
    cout << left << setw(10)<< "Item ID" << setw(13) << "Item Name" << setw(10) << "Quantity" << "Price\n" << left << setw(10) << this->GetItemID() << setw(13) << this->GetItemName() << setw(10) << this->GetItemQty() << "$" << this->GetItemPrice() << "\n" << endl;
}

/*

 File ready!
 Error File ready!
 Hello, please choose from the menu below
 
 Main Menu
 1) Print unsorted inventory
 2) Print inventory sorted
 3) Look up item by ID or name
 4) Print report of inventory
 5) Quit program
 Enter a number: 1
 
 Unsorted inventory:
 Item ID   Item Name    Quantity    Price
 992837    computer            4    299.99
 236627    ipad                7    399.99
 463526    iphone              3    999.99
 987737    keyboard           10     19.99
 236684    laptop              4    199.99
 123987    notebook           10     19.99
 674344    mouse               9     12.99
 544532    calculator          5     34.99
 456553    headphones         14     59.99
 847332    monitor             2    109.99
 992537    bag                 7    219.99
 343526    iphonex             3    999.99
 236784    imac                7   2199.99
 345834    yoyo                5     11.99
 123457    necklace           10    459.99
 744344    ps4                 9    479.99
 554532    socks               5     34.99
 656553    sunglasses         14     59.99
 848132    fork                2      9.99
 
 Main Menu
 1) Print unsorted inventory
 2) Print inventory sorted
 3) Look up item by ID or name
 4) Print report of inventory
 5) Quit program
 Enter a number: 2
 
 How would you like to sort the inventory? (enter 6 to go back to the main menu)
 1) item ID
 2) item name
 3) quantity on hand
 4) price
 5) Main Menu
 Enter a number: 1
 
 Sort complete
 Sorted inventory:
 Item ID   Item Name    Quantity    Price
 123457    necklace           10    459.99
 123987    notebook           10     19.99
 236627    ipad                7    399.99
 236684    laptop              4    199.99
 236784    imac                7   2199.99
 343526    iphonex             3    999.99
 345834    yoyo                5     11.99
 456553    headphones         14     59.99
 463526    iphone              3    999.99
 544532    calculator          5     34.99
 554532    socks               5     34.99
 656553    sunglasses         14     59.99
 674344    mouse               9     12.99
 744344    ps4                 9    479.99
 847332    monitor             2    109.99
 848132    fork                2      9.99
 987737    keyboard           10     19.99
 992537    bag                 7    219.99
 992837    computer            4    299.99
 
 How would you like to sort the inventory? (enter 6 to go back to the main menu)
 1) item ID
 2) item name
 3) quantity on hand
 4) price
 5) Main Menu
 Enter a number: 2
 
 Sort complete
 Sorted inventory:
 Item ID   Item Name    Quantity    Price
 992537    bag                 7    219.99
 544532    calculator          5     34.99
 992837    computer            4    299.99
 848132    fork                2      9.99
 456553    headphones         14     59.99
 236784    imac                7   2199.99
 236627    ipad                7    399.99
 463526    iphone              3    999.99
 343526    iphonex             3    999.99
 987737    keyboard           10     19.99
 236684    laptop              4    199.99
 847332    monitor             2    109.99
 674344    mouse               9     12.99
 123457    necklace           10    459.99
 123987    notebook           10     19.99
 744344    ps4                 9    479.99
 554532    socks               5     34.99
 656553    sunglasses         14     59.99
 345834    yoyo                5     11.99
 
 How would you like to sort the inventory? (enter 6 to go back to the main menu)
 1) item ID
 2) item name
 3) quantity on hand
 4) price
 5) Main Menu
 Enter a number: 3
 
 Sort complete
 Sorted inventory:
 Item ID   Item Name    Quantity    Price
 848132    fork                2      9.99
 847332    monitor             2    109.99
 463526    iphone              3    999.99
 343526    iphonex             3    999.99
 992837    computer            4    299.99
 236684    laptop              4    199.99
 544532    calculator          5     34.99
 554532    socks               5     34.99
 345834    yoyo                5     11.99
 992537    bag                 7    219.99
 236784    imac                7   2199.99
 236627    ipad                7    399.99
 674344    mouse               9     12.99
 744344    ps4                 9    479.99
 987737    keyboard           10     19.99
 123457    necklace           10    459.99
 123987    notebook           10     19.99
 456553    headphones         14     59.99
 656553    sunglasses         14     59.99
 
 How would you like to sort the inventory? (enter 6 to go back to the main menu)
 1) item ID
 2) item name
 3) quantity on hand
 4) price
 5) Main Menu
 Enter a number: 4
 
 Sort complete
 Sorted inventory:
 Item ID   Item Name    Quantity    Price
 848132    fork                2      9.99
 345834    yoyo                5     11.99
 674344    mouse               9     12.99
 987737    keyboard           10     19.99
 123987    notebook           10     19.99
 544532    calculator          5     34.99
 554532    socks               5     34.99
 456553    headphones         14     59.99
 656553    sunglasses         14     59.99
 847332    monitor             2    109.99
 236684    laptop              4    199.99
 992537    bag                 7    219.99
 992837    computer            4    299.99
 236627    ipad                7    399.99
 123457    necklace           10    459.99
 744344    ps4                 9    479.99
 463526    iphone              3    999.99
 343526    iphonex             3    999.99
 236784    imac                7   2199.99
 
 How would you like to sort the inventory? (enter 6 to go back to the main menu)
 1) item ID
 2) item name
 3) quantity on hand
 4) price
 5) Main Menu
 Enter a number: 5
 
 Sorted inventory:
 Item ID   Item Name    Quantity    Price
 848132    fork                2      9.99
 345834    yoyo                5     11.99
 674344    mouse               9     12.99
 987737    keyboard           10     19.99
 123987    notebook           10     19.99
 544532    calculator          5     34.99
 554532    socks               5     34.99
 456553    headphones         14     59.99
 656553    sunglasses         14     59.99
 847332    monitor             2    109.99
 236684    laptop              4    199.99
 992537    bag                 7    219.99
 992837    computer            4    299.99
 236627    ipad                7    399.99
 123457    necklace           10    459.99
 744344    ps4                 9    479.99
 463526    iphone              3    999.99
 343526    iphonex             3    999.99
 236784    imac                7   2199.99
 
 Main Menu
 1) Print unsorted inventory
 2) Print inventory sorted
 3) Look up item by ID or name
 4) Print report of inventory
 5) Quit program
 Enter a number: 3
 
 Please type the ID or product name you want to search for
 (type main to return to the main menu)
 Search: iPAD
 Item ID   Item Name    Quantity  Price
 236627    ipad         7         $399.99
 
 Please type the ID or product name you want to search for
 (type main to return to the main menu)
 Search: 123457
 Item ID   Item Name    Quantity  Price
 123457    necklace     10        $459.99
 
 Please type the ID or product name you want to search for
 (type main to return to the main menu)
 Search: SOcKS
 Item ID   Item Name    Quantity  Price
 554532    socks        5         $34.99
 
 Please type the ID or product name you want to search for
 (type main to return to the main menu)
 Search: main
 
 Returning to main menu
 Main Menu
 1) Print unsorted inventory
 2) Print inventory sorted
 3) Look up item by ID or name
 4) Print report of inventory
 5) Quit program
 Enter a number: 4
 
 Number of unique items: 19
 Total quantity in stock: 130
 Total worth of inventory: $39505.70
 
 Main Menu
 1) Print unsorted inventory
 2) Print inventory sorted
 3) Look up item by ID or name
 4) Print report of inventory
 5) Quit program
 Enter a number: 5
 
 Program ended with exit code: 0
*/

