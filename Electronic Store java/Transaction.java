import java.util.Date;

public class Transaction {
    private int id;
    private String date;
    private double totalAmount;
    private String paymentType;
    private static int counter = 1;

    public Transaction(String paymentType, double amount) {
        this.id = counter++;
        this.paymentType = paymentType;
        this.totalAmount = amount;
        this.date = new Date().toString();
    }
}