public class Investor extends User {
    private double investedAmount;
    private String investedPercentage;

    public Investor(int id, String name, String email,int phone, int age, String address, double amount, String percentage) {
        // Call the constructor of the parent class (User)
        super(id, name, email, phone, age, address);
        this.investedAmount = amount;
        this.investedPercentage = percentage;
    }

    @Override
    // Implement the abstract method from User class
    public void displayRole() {
        System.out.println("Role: Investor with $" + investedAmount + " - " + investedPercentage + "%");
    }
}