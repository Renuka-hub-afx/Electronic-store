/*
 * Electronic Store - C++ version
 * Converted from the Java "Electronic Store" project.
 *
 * This mirrors the Java structure closely since C++ (unlike C) supports
 * classes, inheritance, and virtual functions directly:
 *   - User        -> abstract base class (pure virtual displayRole())
 *   - Customer, Owner, Staff, Supplier, Investor -> derived classes (public User)
 *   - Product, Store, Review, Transaction -> plain classes, same as Java
 */

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

/* ---------------------------- Review ---------------------------- */
class Review {
private:
    int id;
    int rating;
    string comments;
    static int counter;

public:
    Review(int rating, const string &comments) {
        this->id = counter++;
        this->rating = rating;
        this->comments = comments;
    }
};
int Review::counter = 1;

/* ---------------------------- Transaction ---------------------------- */
class Transaction {
private:
    int id;
    string date;
    double totalAmount;
    string paymentType;
    static int counter;

public:
    Transaction(const string &paymentType, double amount) {
        this->id = counter++;
        this->paymentType = paymentType;
        this->totalAmount = amount;
        time_t now = time(nullptr);
        this->date = ctime(&now);
        if (!this->date.empty() && this->date.back() == '\n') {
            this->date.pop_back();
        }
    }
};
int Transaction::counter = 1;

/* ---------------------------- Product ---------------------------- */
class Product {
private:
    int id;
    string name;
    double price;
    double discount;
    string warrantyPeriod;
    vector<Review> reviews;

public:
    Product(int id, const string &name, double price, const string &warrantyPeriod) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->discount = 0;
        this->warrantyPeriod = warrantyPeriod;
    }

    // encapsulation is used for the detail of the product data
    string getName() const { return name; }
    double getPrice() const { return price - discount; }
    void setDiscount(double discount) { this->discount = discount; }

    void addReview(const Review &r) {
        reviews.push_back(r);
    }
};

/* ---------------------------- Store ---------------------------- */
class Store {
private:
    int id;
    string name;
    string location;
    vector<Product *> products;

public:
    Store(int id, const string &name, const string &location) {
        this->id = id;
        this->name = name;
        this->location = location;
    }

    string getName() const { return name; }

    void stockProduct(Product *p) {
        products.push_back(p);
        cout << p->getName() << " stocked in " << name << endl;
    }
};

/* ---------------------------- User (abstract base class) ---------------------------- */
// this is the parent class and it is an abstract class because it has a pure
// virtual method displayRole() which will be implemented by the child classes
class User {
private:
    int id;
    string name;
    string email;
    int phone;
    int age;
    string address;

public:
    User(int id, const string &name, const string &email, int phone, int age, const string &address) {
        this->id = id;
        this->name = name;
        this->email = email;
        this->phone = phone;
        this->age = age;
        this->address = address;
    }

    virtual ~User() {}

    // encapsulation is used for the detail of the users data
    int getId() const { return id; }
    string getName() const { return name; }
    void setName(const string &name) { this->name = name; }
    string getEmail() const { return email; }
    void setEmail(const string &email) { this->email = email; }

    // Abstraction
    virtual void displayRole() const = 0;
};

/* ---------------------------- Customer ---------------------------- */
class Customer : public User {
private:
    vector<Transaction> transactions;
    vector<Review> reviews;

public:
    Customer(int id, const string &name, const string &email, int phone, int age, const string &address)
        : User(id, name, email, phone, age, address) {}

    void displayRole() const override {
        cout << "Role: Customer" << endl;
    }

    void buyProduct(Product &p, Store &store, const string &paymentType) {
        Transaction t(paymentType, p.getPrice());
        transactions.push_back(t);
        cout << getName() << " bought " << p.getName() << " from " << store.getName() << endl;
    }

    void writeReview(Product &p, int rating, const string &comment) {
        Review r(rating, comment);
        reviews.push_back(r);
        p.addReview(r);
        cout << getName() << " wrote a review for " << p.getName() << endl;
    }
};

/* ---------------------------- Owner ---------------------------- */
// so here we have created a child class of the User class
class Owner : public User {
private:
    string equity;
    vector<Store *> managedStores;

public:
    Owner(int id, const string &name, const string &email, int phone, int age, const string &address, const string &equity)
        : User(id, name, email, phone, age, address), equity(equity) {}

    // Implement the pure virtual method from the User class
    void displayRole() const override {
        cout << "Role: Owner with " << equity << " equity" << endl;
    }

    // Method to add a store to the list of managed stores
    void addStore(Store &store) {
        managedStores.push_back(&store);
        cout << getName() << " now manages " << store.getName() << endl;
    }
};

/* ---------------------------- Supplier ---------------------------- */
class Supplier : public User {
private:
    string companyName;
    vector<Product *> suppliedProducts;
    int price_value;

public:
    Supplier(int id, const string &name, const string &email, int phone, int age, const string &address,
              const string &companyName, int price_value)
        : User(id, name, email, phone, age, address), companyName(companyName), price_value(price_value) {}

    void displayRole() const override {
        cout << "Role: Supplier from " << companyName << endl;
    }

    void supplyProduct(Product &p) {
        suppliedProducts.push_back(&p);
        cout << companyName << " supplied " << p.getName() << " at $" << price_value << endl;
    }
};

/* ---------------------------- Staff ---------------------------- */
class Staff : public User {
private:
    string role;
    double salary;

public:
    Staff(int id, const string &name, const string &email, int phone, int age, const string &address,
           const string &role, double salary)
        : User(id, name, email, phone, age, address), role(role), salary(salary) {}

    void displayRole() const override {
        cout << "Role: Staff - " << role << endl;
    }

    void sellProduct(Product &p) {
        cout << getName() << " sold " << p.getName() << endl;
    }
};

/* ---------------------------- Investor ---------------------------- */
class Investor : public User {
private:
    double investedAmount;
    string investedPercentage;

public:
    Investor(int id, const string &name, const string &email, int phone, int age, const string &address,
              double amount, const string &percentage)
        : User(id, name, email, phone, age, address), investedAmount(amount), investedPercentage(percentage) {}

    void displayRole() const override {
        cout << "Role: Investor with $" << investedAmount << " - " << investedPercentage << endl;
    }
};

/* ---------------------------- main ---------------------------- */
int main() {
    // creating objects
    Owner owner(1, "Rahul", "rahul@mail.com", 12345678, 35, "Panjim, Goa", "50%");
    Customer customer(2, "Asha", "asha@mail.com", 12345678, 35, "Panjim, Goa");
    Supplier supplier(3, "Vikram", "vikram@mail.com", 123456789, 35, "Panjim, Goa", "ABC Supplies", 1000);
    Staff staff(4, "Priya", "priya@mail.com", 12345678, 45, "quepem goa", "technician", 10000);
    Investor investor(5, "Mr. Sharma", "sharma@mail.com", 500000, 20, "savordem goa", 40000, "10%");

    Store store(101, "TechZone", "Panjim, Goa");
    Product product(501, "Laptop", 50000, "2 years");

    bool running = true;

    while (running) {
        cout << "\n=== ELECTRONIC STORE SYSTEM ===" << endl;
        cout << "1. Customer Actions (Buy Product & Write Review)" << endl;
        cout << "2. Owner Actions (View Equity & Manage Store)" << endl;
        cout << "3. Supplier Actions (Supply Product)" << endl;
        cout << "4. Staff Actions (Sell Product)" << endl;
        cout << "5. Investor Actions (View Investment Details)" << endl;
        cout << "6. Exit" << endl;
        cout << "Select an option (1-6): ";

        int choice;
        cin >> choice;
        cin.ignore(); // Clear newline buffer, same purpose as scanner.nextLine() in Java

        switch (choice) {
            case 1: {
                cout << "\n--- Customer Portal ---" << endl;
                customer.displayRole();
                cout << "Available Product: " << product.getName() << " | Price: $" << product.getPrice() << endl;

                cout << "Enter payment method (e.g., Cash, Card, UPI): ";
                string payment;
                getline(cin, payment);

                // Buy product
                customer.buyProduct(product, store, payment);

                // Review product
                cout << "Enter rating for " << product.getName() << " (1-5): ";
                int rating;
                cin >> rating;
                cin.ignore(); // Clear buffer

                cout << "Enter review comment: ";
                string comment;
                getline(cin, comment);

                customer.writeReview(product, rating, comment);
                break;
            }

            case 2:
                cout << "\n--- Owner Portal ---" << endl;
                owner.displayRole();
                owner.addStore(store);
                break;

            case 3:
                cout << "\n--- Supplier Portal ---" << endl;
                supplier.displayRole();
                supplier.supplyProduct(product);
                break;

            case 4:
                cout << "\n--- Staff Portal ---" << endl;
                staff.displayRole();
                staff.sellProduct(product);
                break;

            case 5:
                cout << "\n--- Investor Portal ---" << endl;
                investor.displayRole();
                break;

            case 6:
                cout << "\nExiting system... Goodbye!" << endl;
                running = false;
                break;

            default:
                cout << "\nInvalid option! Please try again." << endl;
        }
    }

    return 0;
}
