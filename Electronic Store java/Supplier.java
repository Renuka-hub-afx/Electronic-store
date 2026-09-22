import java.util.ArrayList;
import java.util.List;

public class Supplier extends User {
    private String companyName;
    private List<Product> suppliedProducts;
    private int price_value;

    public Supplier(int id, String name, String email,int phone, int age, String address, String companyName,int price_value) {
        // Call the constructor of the parent class (User)
        super(id, name, email, phone, age, address);
        this.companyName = companyName;
        this.suppliedProducts = new ArrayList<>();
        this.price_value = price_value;
    }

    @Override
    // Implement the abstract method from User class
    public void displayRole() {
        System.out.println("Role: Supplier from " + companyName);
    }

    public void supplyProduct(Product p) {
        suppliedProducts.add(p);
        System.out.println(companyName + " supplied " + p.getName() + " at $" + price_value);
    }
}