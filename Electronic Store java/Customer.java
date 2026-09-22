import java.util.ArrayList;
import java.util.List;

public class Customer extends User {
    private List<Transaction> transactions;
    private List<Review> reviews;

    public Customer(int id, String name, String email,int phone, int age, String address) {
        super(id, name, email,phone, age, address);
        this.transactions = new ArrayList<>();
        this.reviews = new ArrayList<>();
    }

    @Override
    public void displayRole() {
        System.out.println("Role: Customer");
    }

    public void buyProduct(Product p, Store store,String paymentType) {
        Transaction t = new Transaction(paymentType, p.getPrice());
        transactions.add(t);
        System.out.println(getName() + " bought " + p.getName() + " from " + store.getName());
    }

    public void writeReview(Product p, int rating, String comment) {
        Review r = new Review(rating, comment);
        reviews.add(r);
        p.addReview(r);
        System.out.println(getName() + " wrote a review for " + p.getName());
    }
}