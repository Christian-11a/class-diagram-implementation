#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// Constants for stock limits
const int MAX_EXCLUSIVE_STOCK = 20;
const int MAX_HUGE_STOCK = 10;
const int MAX_TITANIC_STOCK = 3;

// Product class
class Product {
public:
    string id;
    string name;
    float price;
    int stock; 

    Product() : stock(0) {}

    Product(string pid, string pname, float pprice, int pstock) : id(pid), name(pname), price(pprice), stock(pstock) {}

    void displayProduct() const {
        cout << setw(10) << id << setw(20) << name << setw(10) << price << setw(10) << stock << endl;
    }
};

// Shopping Cart class
class ShoppingCart {
private:
    Product* cartItems[10];  // Pointer array for cart items
    int quantities[10];
    int itemCount;

public:
    ShoppingCart() : itemCount(0) {}

    Product** getCartItems() {
        return cartItems;
    }

    int* getQuantities() {
        return quantities;
    }

    int getItemCount() const {
        return itemCount;
    }

    void addProduct(Product* product, int quantity) {
        if (product->stock >= quantity) {
            cartItems[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
            product->stock -= quantity; // Deduct the quantity from stock
            cout << "Product added successfully!" << endl;
            system("pause");
        } else {
            cout << "Insufficient stock to fulfill your request." << endl;
        }
    }

    void viewCart() const {
        if (itemCount == 0) {
            cout << "Shopping cart is empty." << endl;
        } else {
            cout << left << setw(10) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
            for (int i = 0; i < itemCount; i++) {
                cout << left << setw(10) << cartItems[i]->id << setw(15) << cartItems[i]->name << setw(10) << cartItems[i]->price << setw(10) << quantities[i] << endl;
            }
        }
    }

    bool isEmpty() const {
        return itemCount == 0;
    }

    float checkout() {
        float totalAmount = 0;
        cout << "\nChecking out the following items:\n";
        cout << left << setw(10) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(10) << cartItems[i]->id << setw(15) << cartItems[i]->name << setw(10) << cartItems[i]->price << setw(10) << quantities[i] << endl;
            totalAmount += cartItems[i]->price * quantities[i];
        }
        cout << "Total Amount: " << totalAmount << endl;
        return totalAmount;
    }

    void clearCart() {
        itemCount = 0;
    }
};

// OrderManager class
class OrderManager {
private:
    struct Order {
        int orderId;
        Product* products[10]; // Pointer array for products
        int quantities[10];
        int itemCount;
        float totalAmount;
    };

    Order orders[100];
    int orderCount;

public:
    OrderManager() : orderCount(0) {}

    void placeOrder(Product* products[], int quantities[], int itemCount, float totalAmount) {
        Order newOrder;
        newOrder.orderId = orderCount + 1;
        newOrder.itemCount = itemCount;
        newOrder.totalAmount = totalAmount;

        for (int i = 0; i < itemCount; i++) {
            newOrder.products[i] = products[i];
            newOrder.quantities[i] = quantities[i];
        }

        orders[orderCount] = newOrder;
        orderCount++;
        cout << "Order placed successfully!" << endl;
    }

    void viewOrders() const {
        if (orderCount == 0) {
            cout << "No orders have been placed." << endl;
        } else {
            for (int i = 0; i < orderCount; i++) {
                cout << "\nOrder ID: " << orders[i].orderId << endl;
                cout << "Total Amount: " << orders[i].totalAmount << endl;
                cout << "Order Details:\n";
                cout << left << setw(10) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
                for (int j = 0; j < orders[i].itemCount; j++) {
                    cout << left << setw(10) << orders[i].products[j]->id << setw(15) << orders[i].products[j]->name << setw(10) << orders[i].products[j]->price << setw(10) << orders[i].quantities[j] << endl;
                }
            }
        }
    }
};

// Function to display all products
void viewProducts(Product productList[], int size) {
    cout << left << setw(10) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Stock" << endl;
    for (int i = 0; i < size; i++) {
        productList[i].displayProduct();
    }
}

int main() {
    // Define the products for each category
    Product exclusivePets[5] = {
        Product("111", "Forest Wyvern", 35, MAX_EXCLUSIVE_STOCK),
        Product("121", "Balloon Dragon", 40, MAX_EXCLUSIVE_STOCK),
        Product("131", "Keyboard Cat", 40, MAX_EXCLUSIVE_STOCK),
        Product("141", "Lava Scorpion", 45, MAX_EXCLUSIVE_STOCK),
        Product("151", "Otter", 45, MAX_EXCLUSIVE_STOCK)
    };

    Product hugePets[5] = {
        Product("211", "Holographic Cat", 200, MAX_HUGE_STOCK),
        Product("221", "Wizard Westi", 200, MAX_HUGE_STOCK),
        Product("231", "Shuriken Corgi", 200, MAX_HUGE_STOCK),
        Product("241", "Sorcerer Bear", 250, MAX_HUGE_STOCK),
        Product("251", "Happy Rock", 300, MAX_HUGE_STOCK)
    };

    Product titanicPets[5] = {
        Product("311", "Banana Cat", 11000, MAX_TITANIC_STOCK),
        Product("321", "Hubert", 18000, MAX_TITANIC_STOCK),
        Product("331", "Kitsune Fox", 13500, MAX_TITANIC_STOCK),
        Product("341", "Silver Dragon", 14000, MAX_TITANIC_STOCK),
        Product("351", "Bat", 10000, MAX_TITANIC_STOCK)
    };

    ShoppingCart cart;
    OrderManager orderManager;
    char choice;
    bool isRunning = true;  

    while (isRunning) {
        system("cls"); 
        cout << "PetX99 Online Store\n";
        cout << "\nMenu:\n";
        cout << "1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (!isdigit(choice) || choice < '1' || choice > '4') {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            system("pause");
            continue;
        }

        switch (choice) {
            case '1': {
                // Declare addMoreProducts inside case '1'
                bool addMoreProducts = true;
                while (addMoreProducts) {
                    system("cls");
                    cout << "Select Category:\n";
                    cout << "1. Exclusive Pets\n";
                    cout << "2. Huge Pets\n";
                    cout << "3. Titanic Pets\n";
                    cout << "Enter your choice: ";
                    int categoryChoice;
                    cin >> categoryChoice;

                    switch (categoryChoice) {
                        case 1: {
                            // Display Exclusive Pets
                            cout << "\nExclusive Pets:\n";
                            viewProducts(exclusivePets, 5);

                            // Add products to cart
                            string productId;
                            cout << "Enter the ID of the pet to add: ";
                            cin >> productId;
                            bool productFound = false;

                            for (int i = 0; i < 5; i++) {
                                if (exclusivePets[i].id == productId) {
                                    int quantity;
                                    bool validQuantity = false;

                                    while (!validQuantity) {
                                        cout << "Enter quantity: ";
                                        cin >> quantity;

                                        if (quantity > 0 && quantity <= exclusivePets[i].stock) {
                                            cart.addProduct(&exclusivePets[i], quantity); // Pass address of the product
                                            validQuantity = true;
                                            productFound = true;
                                        } else if (quantity <= 0) {
                                            cout << "Invalid quantity! Quantity must be greater than 0." << endl;
                                        } else {
                                            cout << "Insufficient stock! Please enter a smaller quantity." << endl;
                                        }
                                    }
                                    break; 
                                }
                            }

                            if (!productFound) {
                                cout << "Invalid Product ID." << endl;
                                system("pause");
                            }
                            break; // Exit switch (categoryChoice)
                        }
                        case 2: {
                            // Display Huge Pets
                            cout << "\nHuge Pets:\n";
                            viewProducts(hugePets, 5);

                            // Add products to cart
                            string productId;
                            cout << "Enter the ID of the pet to add: ";
                            cin >> productId;
                            bool productFound = false;

                            for (int i = 0; i < 5; i++) {
                                if (hugePets[i].id == productId) {
                                    int quantity;
                                    bool validQuantity = false;

                                    while (!validQuantity) {
                                        cout << "Enter quantity: ";
                                        cin >> quantity;

                                        if (quantity > 0 && quantity <= hugePets[i].stock) {
                                            cart.addProduct(&hugePets[i], quantity); // Pass address of the product
                                            validQuantity = true;
                                            productFound = true;
                                        } else if (quantity <= 0) {
                                            cout << "Invalid quantity! Quantity must be greater than 0." << endl;
                                        } else {
                                            cout << "Insufficient stock! Please enter a smaller quantity." << endl;
                                        }
                                    }
                                    break; 
                                }
                            }

                            if (!productFound) {
                                cout << "Invalid Product ID." << endl;
                                system("pause");
                            }
                            break; 
                        }
                        case 3: {
                            // Display Titanic Pets
                            cout << "\nTitanic Pets:\n";
                            viewProducts(titanicPets, 5);

                            // Add products to cart
                            string productId;
                            cout << "Enter the ID of the pet to add: ";
                            cin >> productId;
                            bool productFound = false;

                            for (int i = 0; i < 5; i++) {
                                if (titanicPets[i].id == productId) {
                                    int quantity;
                                    bool validQuantity = false;

                                    while (!validQuantity) {
                                        cout << "Enter quantity: ";
                                        cin >> quantity;

                                        if (quantity > 0 && quantity <= titanicPets[i].stock) {
                                            cart.addProduct(&titanicPets[i], quantity); // Pass address of the product
                                            validQuantity = true;
                                            productFound = true;
                                        } else if (quantity <= 0) {
                                            cout << "Invalid quantity! Quantity must be greater than 0." << endl;
                                        } else {
                                            cout << "Insufficient stock! Please enter a smaller quantity." << endl;
                                        }
                                    }
                                    break; // Exit for loop
                                }
                            }

                            if (!productFound) {
                                cout << "Invalid Product ID." << endl;
                                system("pause");
                            }
                            break; // Exit switch (categoryChoice)
                        }
                        default:
                            cout << "Invalid category choice." << endl;
                            system("pause");
                            break;
                    }

                    // Ask if the user wants to add another product
                    cout << "\nDo you want to add another product? (y/n): ";
                    char addMoreChoice;
                    cin >> addMoreChoice;
                    addMoreProducts = (toupper(addMoreChoice) == 'Y');
                }
                break; // Exit case '1'
            }
            case '2': {
                system("cls");
                cout << "Shopping Cart:\n";
                cart.viewCart();

                if (!cart.isEmpty()) {
                    cout << "\nDo you want to proceed to checkout? (y/n): ";
                    char checkoutChoice;
                    cin >> checkoutChoice;

                    if (toupper(checkoutChoice) == 'Y') {
                        float totalAmount = cart.checkout();
                        // Place order and reset cart
                        orderManager.placeOrder(cart.getCartItems(), cart.getQuantities(), cart.getItemCount(), totalAmount);
                        cart.clearCart(); 
                    }
                }
                system("pause");
                break;
            }
            case '3': {
                system("cls");
                cout << "Order History:\n";
                orderManager.viewOrders();
                system("pause");
                break;
            }
            case '4': {
                isRunning = false;  
                cout << "Exiting the PetX99 Online Store. Thank you for visiting!" << endl;
                break;
            }
            default:
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                system("pause");
                break;
        }
    }

    return 0;
}
