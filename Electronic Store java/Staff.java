public class Staff extends User {
    private String role;
    private double salary;

    public Staff(int id, String name, String email, int phone, int age, String address,String role, double salary) {
        // Call the constructor of the parent class (User)
        super(id, name, email, phone, age, address);
        this.role = role;
        this.salary = salary;
    }

    @Override
    // Implement the abstract method from User class
    public void displayRole() {
        System.out.println("Role: Staff - " + role);
    }

    public void sellProduct(Product p) {
        System.out.println(getName() + " sold " + p.getName());
    }
}