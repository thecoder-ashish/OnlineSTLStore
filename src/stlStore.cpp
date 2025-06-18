#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set> 
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <ctime>

using namespace std;

// Custom datatypes

struct Product{
    int productID;
    string name;
    string category;
};
struct Order{
    int orderID;
    int productID;
    string customerID;
    int quantity;
    time_t orderDate;
};

// struct Customer{
//     string customerID;
//     string name;
//     int mobNum;
// };

// repeteadly used variables
int pID;
string cID;
int quant;
char ans = 'y';
int currOrderNum = 2025001;

// All the needed storage variables

// Listing some products
vector<Product> products = {
    {201, "Mobile", "Electronics"},
    {202, "Laptop", "Electronics"},
    {203, "Studs", "Sports"},
    {204, "Blender", "Kitchen"},
    {205, "Coffee Maker", "Kitchen"}
};

// Open queue 
deque<string> recentCustomers = {"C001", "C003"};

// Order history as a list (closed end queue)
list<Order> orderHistory;

// Set of unique categories
set<string> categories;
// Map for stock of products
map<int, int> productStocks = {
    {201, 50},
    {202, 45},
    {203, 25},
    {204, 10},
    {205, 8}
};
// One customer can have multiple orders
multimap<string, Order> customerOrders;
unordered_map<string, string> customerData = {
    {"C001", "Dhoni"},
    {"C002", "Messi"},
    {"C003", "Ronaldo"},
    {"C004", "Yamal"},
    {"C005", "Bruno"},
};
unordered_set<int> uniqueProductIDs;


// All the functions to make int main clutter free

// format date n time
string formatTime(time_t rawTime) {
    struct tm *timeinfo = localtime(&rawTime);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y - %H:%M", timeinfo);
    return string(buffer);
}

// Utility functions

// function to add new order
void placeOrder(string name){
    int* stocks = &productStocks[pID];
    if (*stocks>=quant){
        Order order = {currOrderNum, pID, cID, quant, time(0)};
        orderHistory.push_back(order);
        currOrderNum++;
        recentCustomers.push_front(cID);
        *stocks-=quant;
        customerOrders.insert({cID, order});

        cout << "Thank you for using our store " << name <<endl;
    } else {
        cout << "Sorry " << name << " but we only have " << *stocks << " left in stock\n";
    }
}

// Basic inpputs
void productInput(){
    cout << endl;
    cout << "Enter product id:";
    cin >> pID;

    cout << "Enter product quantity: ";
    cin >> quant;
}
void customerInput(){
    cout << "Enter customer id:";
    cin >> cID;
}
void again(){
    cout << "Do you want to run the code again? (y/n): ";
    cin >> ans;
}


// Customer interfaces
void ui();
void custUI(); 
void adminUI();

// Functions required in UIs
// function if customer wants to buy more items
void buyMore(string name){
    cout << "Do you want to purchare more items? (y/n)";
    cin >> ans;

    if (ans=='Y' || ans=='y'){
        custUI();
    } else if (ans=='N' || ans=='n'){
        cout << "Hope to see you again " << name << "! Have a nice day." << endl<<endl;
        ui();
    } else {
        cout << "\tInvalid input!!!";
        buyMore(name);
    }
}

// displays all available products
void listAllProducts(){
    cout<<"\tHere are all of the products:-\n";
    for (const auto &p : products){
        cout<< p.productID << " - " << p.name << " (" << productStocks[p.productID] << ")" << " - "<< p.category<<endl;
    }
}

// add a new customer
void addNewCust(){
    string name;
    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, name);

    customerData[cID] = name;
}

// view the order history
void ordHist(){

    for (const auto &order : orderHistory){
        cout << "Order ID: " << order.orderID <<endl;
        cout << "Product ID: " << order.productID <<endl;
        cout << "Quantity: " << order.quantity <<endl;
        cout << "Customer ID: " << order.customerID <<endl;
        cout << "Order date: " << formatTime(order.orderDate)  <<endl<<endl;
    }
}

// view recent customers
void recCust(){
    cout << "Our Recent Customers: ";
    for (const string &cust : recentCustomers){
        cout << customerData[cust] << " ";
    }
    cout << endl;
}

// show all stocks
void showStocks(){
    cout << "Stocks:-\n";
    for (const auto &item : productStocks){
        cout << item.first << " - " << item.second <<" pieces\n";
    }
}

// add a new product
void addNewProduct(){
    productInput();
    string pName;
    string pCat;
    
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, pName);
    cout << "Enter product category: ";
    getline(cin, pCat);
    
    Product newProduct = {pID, pName, pCat};
    products.push_back(newProduct);
    productStocks.insert({pID, quant});
    uniqueProductIDs.insert(pID);
    categories.insert(pCat);
}

// view all orders of a customer
void custAllOrders(){
    customerInput();
    cout << "All the orders of customer " << customerData[cID] << " are:\n";
    // auto range = customerOrders.equal_range(cID);
    for (auto [itr, rangeEnd] = customerOrders.equal_range(cID); itr != rangeEnd; ++itr){
        cout << "\nOrder ID: " << itr->second.orderID << endl;
        cout << "Product: " << itr->second.productID << " (" << itr->second.quantity << ")\n";
        cout << "Date: " << formatTime(itr->second.orderDate)<<endl;
    }
}

// check if user exists
void checkExistence(){
    customerInput();
    if (customerData.find(cID) == customerData.end()){
        addNewCust();
    }
}

// dislay all of the registered customers
void listCustomers(){
    cout << "Here is the list of all customers:-\n";
    for (const auto cust : customerData ){
        cout << cust.first <<" - "<<cust.second<<endl;
    }
    cout<<endl;
}

// All the interfaces
// main ui
void ui(){
    int userType;
    cout << "\t\tWelcome to the store!!!\nPlease tell if you're a/an:\n1 - Admin\n2 - Customer\n0 - Exit\n: ";
    cin >> userType;
    cin.ignore();

    if (userType == 1) {
        adminUI();
    } else if (userType == 2) {
        custUI();
    } else if ( userType == 0) {
        cout << "\t\tExiting the store!!!";
        // return;
    } else {
        cout << "\t!!!Invalid input!!!\n";
        ui();
    }
}

// ui for customers
void custUI(){
    listAllProducts();

    productInput();
    checkExistence();
    string name = customerData[cID];
    placeOrder(name);
    buyMore(name);
}


// ui for the admin
void adminUI() {
    while (true) {
        int choice;
        cout << "\nHello admin!! What would you like to do?\n"
             << "1 - Order history\n"
             << "2 - Recent Customers\n"
             << "3 - List of products\n"
             << "4 - Products stock\n"
             << "5 - Add order history\n"
             << "6 - Add/Modify customer Data\n"
             << "7 - Add new product\n"
             << "8 - Add/Update product stock\n"
             << "9 - Track customer\n"
             << "10 - List all customers\n"
             << "0 - Exit\n:";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 0:
                ui();
            case 1:
                ordHist();
                break;
            case 2:
                recCust();
                break;
            case 3:
                listAllProducts();
                break;
            case 4:
                showStocks();
                break;
            case 5:
                productInput();
                checkExistence();
                placeOrder("admin");
                break;
            case 6:
                addNewCust();
                break;
            case 7:
                addNewProduct();
                break;
            case 8:
                productInput();
                productStocks[pID] = quant;
                break;
            case 9:
                custAllOrders();
                break;
            case 10:
                listCustomers();
                break;
            default:
                cout << "\t!!!Invalid input!!!\n";
        }
    }
}


int main() {
    // Adding rough data

    orderHistory.push_back({currOrderNum, 202, "C003", 1, time(0)});
    currOrderNum++;
    orderHistory.push_back({currOrderNum, 205, "C001", 1, time(0)});
    currOrderNum++;
    // If new customer, adding to front of recent customers
    orderHistory.push_back({currOrderNum, 201, "C002", 2, time(0)});
    currOrderNum++;
    recentCustomers.push_front("C002");
    
    // used &product instead of product as using product would make a copy and as it is expensive to copy from class/struct we have given reference using &
    for (const auto &product : products){
        categories.insert(product.category);
    }

    for (const auto &order : orderHistory){
        customerOrders.insert({order.customerID, order});
    }

    for (const auto &product : products){
        uniqueProductIDs.insert(product.productID);
    }


    // Interface for user
    ui();

    return 0;
}