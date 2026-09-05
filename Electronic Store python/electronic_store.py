"""
Electronic Store - Python version
Converted from the Java "Electronic Store" project.

Python has real classes + inheritance, like Java, so the structure maps
closely:
    User (abstract base class, via the abc module) -> Customer, Owner,
    Staff, Supplier, Investor (all inherit from User)
    Product, Store, Review, Transaction -> plain classes, same as Java
"""

from abc import ABC, abstractmethod
from datetime import datetime


# ---------------------------- Review ----------------------------
class Review:
    counter = 1  # static counter, like Java's `static int counter`

    def __init__(self, rating, comments):
        self.id = Review.counter
        Review.counter += 1
        self.rating = rating
        self.comments = comments


# ---------------------------- Transaction ----------------------------
class Transaction:
    counter = 1  # static counter, like Java's `static int counter`

    def __init__(self, payment_type, amount):
        self.id = Transaction.counter
        Transaction.counter += 1
        self.payment_type = payment_type
        self.total_amount = amount
        self.date = str(datetime.now())


# ---------------------------- Product ----------------------------
class Product:
    def __init__(self, id, name, price, warranty_period):
        self.id = id
        self.name = name
        self.price = price
        self.discount = 0
        self.warranty_period = warranty_period
        self.reviews = []

    # encapsulation is used for the detail of the product data
    def get_name(self):
        return self.name

    def get_price(self):
        return self.price - self.discount

    def set_discount(self, discount):
        self.discount = discount

    def add_review(self, review):
        self.reviews.append(review)


# ---------------------------- Store ----------------------------
class Store:
    def __init__(self, id, name, location):
        self.id = id
        self.name = name
        self.location = location
        self.products = []

    def get_name(self):
        return self.name

    def stock_product(self, product):
        self.products.append(product)
        print(f"{product.get_name()} stocked in {self.name}")


# ---------------------------- User (abstract base class) ----------------------------
# so this is the parent class and it is an abstract class because it has an
# abstract method display_role() which will be implemented by the child classes
class User(ABC):
    def __init__(self, id, name, email, phone, age, address):
        self.id = id
        self.name = name
        self.email = email
        self.phone = phone
        self.age = age
        self.address = address

    # encapsulation is used for the detail of the users data
    def get_id(self):
        return self.id

    def get_name(self):
        return self.name

    def set_name(self, name):
        self.name = name

    def get_email(self):
        return self.email

    def set_email(self, email):
        self.email = email

    # Abstraction
    @abstractmethod
    def display_role(self):
        pass


# ---------------------------- Customer ----------------------------
class Customer(User):
    def __init__(self, id, name, email, phone, age, address):
        super().__init__(id, name, email, phone, age, address)
        self.transactions = []
        self.reviews = []

    def display_role(self):
        print("Role: Customer")

    def buy_product(self, product, store, payment_type):
        t = Transaction(payment_type, product.get_price())
        self.transactions.append(t)
        print(f"{self.get_name()} bought {product.get_name()} from {store.get_name()}")

    def write_review(self, product, rating, comment):
        r = Review(rating, comment)
        self.reviews.append(r)
        product.add_review(r)
        print(f"{self.get_name()} wrote a review for {product.get_name()}")


# ---------------------------- Owner ----------------------------
# so here we have created a child class of the User class
class Owner(User):
    def __init__(self, id, name, email, phone, age, address, equity):
        super().__init__(id, name, email, phone, age, address)
        self.equity = equity
        self.managed_stores = []

    # Implement the abstract method from the User class
    def display_role(self):
        print(f"Role: Owner with {self.equity} equity")

    # Method to add a store to the list of managed stores
    def add_store(self, store):
        self.managed_stores.append(store)
        print(f"{self.get_name()} now manages {store.get_name()}")


# ---------------------------- Supplier ----------------------------
class Supplier(User):
    def __init__(self, id, name, email, phone, age, address, company_name, price_value):
        super().__init__(id, name, email, phone, age, address)
        self.company_name = company_name
        self.supplied_products = []
        self.price_value = price_value

    def display_role(self):
        print(f"Role: Supplier from {self.company_name}")

    def supply_product(self, product):
        self.supplied_products.append(product)
        print(f"{self.company_name} supplied {product.get_name()} at ${self.price_value}")


# ---------------------------- Staff ----------------------------
class Staff(User):
    def __init__(self, id, name, email, phone, age, address, role, salary):
        super().__init__(id, name, email, phone, age, address)
        self.role = role
        self.salary = salary

    def display_role(self):
        print(f"Role: Staff - {self.role}")

    def sell_product(self, product):
        print(f"{self.get_name()} sold {product.get_name()}")


# ---------------------------- Investor ----------------------------
class Investor(User):
    def __init__(self, id, name, email, phone, age, address, amount, percentage):
        super().__init__(id, name, email, phone, age, address)
        self.invested_amount = amount
        self.invested_percentage = percentage

    def display_role(self):
        print(f"Role: Investor with ${self.invested_amount} - {self.invested_percentage}")


# ---------------------------- main ----------------------------
def main():
    # creating objects
    owner = Owner(1, "Rahul", "rahul@mail.com", 12345678, 35, "Panjim, Goa", "50%")
    customer = Customer(2, "Asha", "asha@mail.com", 12345678, 35, "Panjim, Goa")
    supplier = Supplier(3, "Vikram", "vikram@mail.com", 123456789, 35, "Panjim, Goa", "ABC Supplies", 1000)
    staff = Staff(4, "Priya", "priya@mail.com", 12345678, 45, "quepem goa", "technician", 10000)
    investor = Investor(5, "Mr. Sharma", "sharma@mail.com", 500000, 20, "savordem goa", 40000, "10%")

    store = Store(101, "TechZone", "Panjim, Goa")
    product = Product(501, "Laptop", 50000, "2 years")

    running = True

    while running:
        print("\n=== ELECTRONIC STORE SYSTEM ===")
        print("1. Customer Actions (Buy Product & Write Review)")
        print("2. Owner Actions (View Equity & Manage Store)")
        print("3. Supplier Actions (Supply Product)")
        print("4. Staff Actions (Sell Product)")
        print("5. Investor Actions (View Investment Details)")
        print("6. Exit")

        choice = input("Select an option (1-6): ")

        try:
            choice = int(choice)
        except ValueError:
            print("\nInvalid option! Please try again.")
            continue

        if choice == 1:
            print("\n--- Customer Portal ---")
            customer.display_role()
            print(f"Available Product: {product.get_name()} | Price: ${product.get_price()}")

            payment = input("Enter payment method (e.g., Cash, Card, UPI): ")

            # Buy product
            customer.buy_product(product, store, payment)

            # Review product
            rating = int(input(f"Enter rating for {product.get_name()} (1-5): "))
            comment = input("Enter review comment: ")

            customer.write_review(product, rating, comment)

        elif choice == 2:
            print("\n--- Owner Portal ---")
            owner.display_role()
            owner.add_store(store)

        elif choice == 3:
            print("\n--- Supplier Portal ---")
            supplier.display_role()
            supplier.supply_product(product)

        elif choice == 4:
            print("\n--- Staff Portal ---")
            staff.display_role()
            staff.sell_product(product)

        elif choice == 5:
            print("\n--- Investor Portal ---")
            investor.display_role()

        elif choice == 6:
            print("\nExiting system... Goodbye!")
            running = False

        else:
            print("\nInvalid option! Please try again.")


if __name__ == "__main__":
    main()
