import java.util.ArrayList;
import java.util.List;

public class Store {
    private int id;
    private String name;
    private String location;
    private List<Product> products;

    public Store(int id, String name, String location) {
        this.id = id;
        this.name = name;
        this.location = location;
        this.products = new ArrayList<>();
    }

    public String getName() { return name; }

    public void stockProduct(Product p) {
        products.add(p);
        System.out.println(p.getName() + " stocked in " + name);
    }
}