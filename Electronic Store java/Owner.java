import java.util.ArrayList;
import java.util.List;
//so here we have create a child class of user classs
public class Owner extends User {
    private String equity;
    private List<Store> managedStores;

    public Owner(int id, String name, String email, int phone, int age, String address, String equity) {
        // Call the constructor of the parent class (User)
        super(id, name, email, phone, age, address);
        this.equity = equity;
        this.managedStores = new ArrayList<>();
    }

    @Override
    // Implement the abstract method from User class
    public void displayRole() {
        System.out.println("Role: Owner with " + equity + " equity");
    }

    // Method to add a store to the list of managed stores
    public void addStore(Store store) {
        managedStores.add(store);
        System.out.println(getName() + " now manages " + store.getName());
    }
}