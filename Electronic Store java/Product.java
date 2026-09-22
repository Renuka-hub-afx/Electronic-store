import java.util.ArrayList;
import java.util.List;

public class Product {
    private int id;
    private String name;
    private double price;
    private double discount;
    private String warrantyPeriod;
    private List<Review> reviews;

    // Constructor
    public Product(int id, String name, double price, String warrantyPeriod) {
        this.id = id;
        this.name = name;
        this.price = price;
        this.warrantyPeriod = warrantyPeriod;
        this.reviews = new ArrayList<>();
    }
    //encapsulation is used for the detail of the product data
    public String getName() 
    { return name; }
    public double getPrice() 
    { return price - discount; }

    public void setDiscount(double discount) 
    { this.discount = discount; }

    public void addReview(Review r) {
        reviews.add(r);
    }
}