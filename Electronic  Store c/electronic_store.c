/*
 * Electronic Store - C version
 * Converted from the Java "Electronic Store" project.
 *
 * Java used classes + inheritance (User -> Customer/Owner/Staff/Supplier/Investor).
 * C has no classes/inheritance, so each "class" becomes a struct, and each
 * "role" struct starts with a User field to mimic inheritance (the common
 * fields id/name/email/phone/age/address live inside `User base;`).
 * displayRole() (was polymorphic/abstract in Java) becomes one plain
 * function per role in C: displayRoleOwner(), displayRoleCustomer(), etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- static "counters" (like Java's static int counter) ---------- */
static int reviewCounter = 1;
static int transactionCounter = 1;

/* ---------------------------- Review ---------------------------- */
typedef struct {
    int id;
    int rating;
    char comments[200];
} Review;

Review createReview(int rating, const char *comments) {
    Review r;
    r.id = reviewCounter++;
    r.rating = rating;
    strncpy(r.comments, comments, sizeof(r.comments) - 1);
    r.comments[sizeof(r.comments) - 1] = '\0';
    return r;
}

/* ---------------------------- Transaction ---------------------------- */
typedef struct {
    int id;
    char date[64];
    double totalAmount;
    char paymentType[32];
} Transaction;

Transaction createTransaction(const char *paymentType, double amount) {
    Transaction t;
    time_t now = time(NULL);
    t.id = transactionCounter++;
    strncpy(t.paymentType, paymentType, sizeof(t.paymentType) - 1);
    t.paymentType[sizeof(t.paymentType) - 1] = '\0';
    t.totalAmount = amount;
    strncpy(t.date, ctime(&now), sizeof(t.date) - 1);
    t.date[sizeof(t.date) - 1] = '\0';
    return t;
}

/* ---------------------------- Product ---------------------------- */
#define MAX_REVIEWS 50

typedef struct {
    int id;
    char name[50];
    double price;
    double discount;
    char warrantyPeriod[20];
    Review reviews[MAX_REVIEWS];
    int reviewCount;
} Product;

Product createProduct(int id, const char *name, double price, const char *warrantyPeriod) {
    Product p;
    p.id = id;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.price = price;
    p.discount = 0;
    strncpy(p.warrantyPeriod, warrantyPeriod, sizeof(p.warrantyPeriod) - 1);
    p.warrantyPeriod[sizeof(p.warrantyPeriod) - 1] = '\0';
    p.reviewCount = 0;
    return p;
}

const char *productGetName(const Product *p) { return p->name; }
double productGetPrice(const Product *p) { return p->price - p->discount; }
void productSetDiscount(Product *p, double discount) { p->discount = discount; }

void productAddReview(Product *p, Review r) {
    if (p->reviewCount < MAX_REVIEWS) {
        p->reviews[p->reviewCount++] = r;
    }
}

/* ---------------------------- Store ---------------------------- */
#define MAX_PRODUCTS 50

typedef struct {
    int id;
    char name[50];
    char location[100];
    Product *products[MAX_PRODUCTS];
    int productCount;
} Store;

Store createStore(int id, const char *name, const char *location) {
    Store s;
    s.id = id;
    strncpy(s.name, name, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';
    strncpy(s.location, location, sizeof(s.location) - 1);
    s.location[sizeof(s.location) - 1] = '\0';
    s.productCount = 0;
    return s;
}

const char *storeGetName(const Store *s) { return s->name; }

void storeStockProduct(Store *s, Product *p) {
    if (s->productCount < MAX_PRODUCTS) {
        s->products[s->productCount++] = p;
    }
    printf("%s stocked in %s\n", productGetName(p), s->name);
}

/* ---------------------------- User (common fields) ---------------------------- */
typedef struct {
    int id;
    char name[50];
    char email[50];
    int phone;
    int age;
    char address[100];
} User;

User createUser(int id, const char *name, const char *email, int phone, int age, const char *address) {
    User u;
    u.id = id;
    strncpy(u.name, name, sizeof(u.name) - 1);
    u.name[sizeof(u.name) - 1] = '\0';
    strncpy(u.email, email, sizeof(u.email) - 1);
    u.email[sizeof(u.email) - 1] = '\0';
    u.phone = phone;
    u.age = age;
    strncpy(u.address, address, sizeof(u.address) - 1);
    u.address[sizeof(u.address) - 1] = '\0';
    return u;
}

const char *userGetName(const User *u) { return u->name; }

/* ---------------------------- Customer (User + extras) ---------------------------- */
#define MAX_TRANSACTIONS 50

typedef struct {
    User base;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
    Review reviews[MAX_REVIEWS];
    int reviewCount;
} Customer;

Customer createCustomer(int id, const char *name, const char *email, int phone, int age, const char *address) {
    Customer c;
    c.base = createUser(id, name, email, phone, age, address);
    c.transactionCount = 0;
    c.reviewCount = 0;
    return c;
}

void displayRoleCustomer(void) {
    printf("Role: Customer\n");
}

void customerBuyProduct(Customer *c, Product *p, Store *store, const char *paymentType) {
    Transaction t = createTransaction(paymentType, productGetPrice(p));
    if (c->transactionCount < MAX_TRANSACTIONS) {
        c->transactions[c->transactionCount++] = t;
    }
    printf("%s bought %s from %s\n", userGetName(&c->base), productGetName(p), storeGetName(store));
}

void customerWriteReview(Customer *c, Product *p, int rating, const char *comment) {
    Review r = createReview(rating, comment);
    if (c->reviewCount < MAX_REVIEWS) {
        c->reviews[c->reviewCount++] = r;
    }
    productAddReview(p, r);
    printf("%s wrote a review for %s\n", userGetName(&c->base), productGetName(p));
}

/* ---------------------------- Owner (User + extras) ---------------------------- */
#define MAX_STORES 20

typedef struct {
    User base;
    char equity[20];
    Store *managedStores[MAX_STORES];
    int storeCount;
} Owner;

Owner createOwner(int id, const char *name, const char *email, int phone, int age, const char *address, const char *equity) {
    Owner o;
    o.base = createUser(id, name, email, phone, age, address);
    strncpy(o.equity, equity, sizeof(o.equity) - 1);
    o.equity[sizeof(o.equity) - 1] = '\0';
    o.storeCount = 0;
    return o;
}

void displayRoleOwner(const Owner *o) {
    printf("Role: Owner with %s equity\n", o->equity);
}

void ownerAddStore(Owner *o, Store *store) {
    if (o->storeCount < MAX_STORES) {
        o->managedStores[o->storeCount++] = store;
    }
    printf("%s now manages %s\n", userGetName(&o->base), storeGetName(store));
}

/* ---------------------------- Supplier (User + extras) ---------------------------- */
typedef struct {
    User base;
    char companyName[50];
    Product *suppliedProducts[MAX_PRODUCTS];
    int suppliedCount;
    int priceValue;
} Supplier;

Supplier createSupplier(int id, const char *name, const char *email, int phone, int age, const char *address, const char *companyName, int priceValue) {
    Supplier s;
    s.base = createUser(id, name, email, phone, age, address);
    strncpy(s.companyName, companyName, sizeof(s.companyName) - 1);
    s.companyName[sizeof(s.companyName) - 1] = '\0';
    s.suppliedCount = 0;
    s.priceValue = priceValue;
    return s;
}

void displayRoleSupplier(const Supplier *s) {
    printf("Role: Supplier from %s\n", s->companyName);
}

void supplierSupplyProduct(Supplier *s, Product *p) {
    if (s->suppliedCount < MAX_PRODUCTS) {
        s->suppliedProducts[s->suppliedCount++] = p;
    }
    printf("%s supplied %s at $%d\n", s->companyName, productGetName(p), s->priceValue);
}

/* ---------------------------- Staff (User + extras) ---------------------------- */
typedef struct {
    User base;
    char role[30];
    double salary;
} Staff;

Staff createStaff(int id, const char *name, const char *email, int phone, int age, const char *address, const char *role, double salary) {
    Staff st;
    st.base = createUser(id, name, email, phone, age, address);
    strncpy(st.role, role, sizeof(st.role) - 1);
    st.role[sizeof(st.role) - 1] = '\0';
    st.salary = salary;
    return st;
}

void displayRoleStaff(const Staff *s) {
    printf("Role: Staff - %s\n", s->role);
}

void staffSellProduct(const Staff *s, Product *p) {
    printf("%s sold %s\n", userGetName(&s->base), productGetName(p));
}

/* ---------------------------- Investor (User + extras) ---------------------------- */
typedef struct {
    User base;
    double investedAmount;
    char investedPercentage[10];
} Investor;

Investor createInvestor(int id, const char *name, const char *email, int phone, int age, const char *address, double amount, const char *percentage) {
    Investor inv;
    inv.base = createUser(id, name, email, phone, age, address);
    inv.investedAmount = amount;
    strncpy(inv.investedPercentage, percentage, sizeof(inv.investedPercentage) - 1);
    inv.investedPercentage[sizeof(inv.investedPercentage) - 1] = '\0';
    return inv;
}

void displayRoleInvestor(const Investor *inv) {
    printf("Role: Investor with $%.1f - %s\n", inv->investedAmount, inv->investedPercentage);
}

/* ---------------------------- helper: clean line reading ---------------------------- */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

/* ---------------------------- main ---------------------------- */
int main(void) {
    char payment[32];
    char comment[200];
    int choice, rating;

    /* creating objects (same values as Main.java) */
    Owner owner = createOwner(1, "Rahul", "rahul@mail.com", 12345678, 35, "Panjim, Goa", "50%");
    Customer customer = createCustomer(2, "Asha", "asha@mail.com", 12345678, 35, "Panjim, Goa");
    Supplier supplier = createSupplier(3, "Vikram", "vikram@mail.com", 123456789, 35, "Panjim, Goa", "ABC Supplies", 1000);
    Staff staff = createStaff(4, "Priya", "priya@mail.com", 12345678, 45, "quepem goa", "technician", 10000);
    Investor investor = createInvestor(5, "Mr. Sharma", "sharma@mail.com", 500000, 20, "savordem goa", 40000, "10%");

    Store store = createStore(101, "TechZone", "Panjim, Goa");
    Product product = createProduct(501, "Laptop", 50000, "2 years");

    int running = 1;

    while (running) {
        printf("\n=== ELECTRONIC STORE SYSTEM ===\n");
        printf("1. Customer Actions (Buy Product & Write Review)\n");
        printf("2. Owner Actions (View Equity & Manage Store)\n");
        printf("3. Supplier Actions (Supply Product)\n");
        printf("4. Staff Actions (Sell Product)\n");
        printf("5. Investor Actions (View Investment Details)\n");
        printf("6. Exit\n");
        printf("Select an option (1-6): ");

        if (scanf("%d", &choice) != 1) {
            /* clear bad input */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }
        getchar(); /* clear newline buffer, same purpose as scanner.nextLine() in Java */

        switch (choice) {
            case 1:
                printf("\n--- Customer Portal ---\n");
                displayRoleCustomer();
                printf("Available Product: %s | Price: $%.1f\n", productGetName(&product), productGetPrice(&product));

                printf("Enter payment method (e.g., Cash, Card, UPI): ");
                readLine(payment, sizeof(payment));

                customerBuyProduct(&customer, &product, &store, payment);

                printf("Enter rating for %s (1-5): ", productGetName(&product));
                scanf("%d", &rating);
                getchar();

                printf("Enter review comment: ");
                readLine(comment, sizeof(comment));

                customerWriteReview(&customer, &product, rating, comment);
                break;

            case 2:
                printf("\n--- Owner Portal ---\n");
                displayRoleOwner(&owner);
                ownerAddStore(&owner, &store);
                break;

            case 3:
                printf("\n--- Supplier Portal ---\n");
                displayRoleSupplier(&supplier);
                supplierSupplyProduct(&supplier, &product);
                break;

            case 4:
                printf("\n--- Staff Portal ---\n");
                displayRoleStaff(&staff);
                staffSellProduct(&staff, &product);
                break;

            case 5:
                printf("\n--- Investor Portal ---\n");
                displayRoleInvestor(&investor);
                break;

            case 6:
                printf("\nExiting system... Goodbye!\n");
                running = 0;
                break;

            default:
                printf("\nInvalid option! Please try again.\n");
        }
    }

    return 0;
}
