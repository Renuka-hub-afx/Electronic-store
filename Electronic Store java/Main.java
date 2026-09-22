import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        //creating objects
        Owner owner = new Owner(1, "Rahul", "rahul@mail.com", 12345678, 35, "Panjim, Goa", "50%");
        Customer customer = new Customer(2, "Asha", "asha@mail.com",12345678, 35, "Panjim, Goa");
        Supplier supplier = new Supplier(3, "Vikram", "vikram@mail.com", 123456789, 35 ,"Panjim, Goa", "ABC Supplies",1000);
        Staff staff = new Staff(4, "Priya", "priya@mail.com", 12345678, 45, "quepem goa","technician",10000);
        Investor investor = new Investor(5, "Mr. Sharma", "sharma@mail.com", 500000, 20, "savordem goa", 40000, "10%");

        Store store = new Store(101, "TechZone", "Panjim, Goa");
        Product product = new Product(501, "Laptop", 50000, "2 years");

        boolean running = true;

        while (running) {
            System.out.println("\n=== ELECTRONIC STORE SYSTEM ===");
            System.out.println("1. Customer Actions (Buy Product & Write Review)");
            System.out.println("2. Owner Actions (View Equity & Manage Store)");
            System.out.println("3. Supplier Actions (Supply Product)");
            System.out.println("4. Staff Actions (Sell Product)");
            System.out.println("5. Investor Actions (View Investment Details)");
            System.out.println("6. Exit");
            System.out.print("Select an option (1-6): ");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Clear newline buffer

            switch (choice) {
                case 1:
                    System.out.println("\n--- Customer Portal ---");
                    customer.displayRole();
                    System.out.println("Available Product: " + product.getName() + " | Price: $" + product.getPrice());
                    
                    System.out.print("Enter payment method (e.g., Cash, Card, UPI): ");
                    String payment = scanner.nextLine();
                    
                    // Buy product
                    customer.buyProduct(product, store, payment);

                    // Review product
                    System.out.print("Enter rating for " + product.getName() + " (1-5): ");
                    int rating = scanner.nextInt();
                    scanner.nextLine(); // Clear buffer
                    
                    System.out.print("Enter review comment: ");
                    String comment = scanner.nextLine();
                    
                    customer.writeReview(product, rating, comment);
                    break;

                case 2:
                    System.out.println("\n--- Owner Portal ---");
                    owner.displayRole();
                    owner.addStore(store);
                    break;

                case 3:
                    System.out.println("\n--- Supplier Portal ---");
                    supplier.displayRole();
                    supplier.supplyProduct(product);
                    break;

                case 4:
                    System.out.println("\n--- Staff Portal ---");
                    staff.displayRole();
                    staff.sellProduct(product);
                    break;

                case 5:
                    System.out.println("\n--- Investor Portal ---");
                    investor.displayRole();
                    break;

                case 6:
                    System.out.println("\nExiting system... Goodbye!");
                    running = false;
                    break;

                default:
                    System.out.println("\nInvalid option! Please try again.");
            }
        }

        scanner.close();
    }
}