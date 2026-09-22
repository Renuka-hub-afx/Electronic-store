// so this is the parent class and it is an abstract class because it has an abstract method displayRole() which will be implemented by the child classes
public abstract class User {
    private int id;
    private String name;
    private String email;
    private int phone;
    private int age;
    private String address;

    public User(int id, String name, String email, int phone, int age, String address) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.phone = phone;
        this.age = age;
        this.address = address;
    }

    // encapsilation is used for the detail of the users data
    public int getId() 
    { return id; }
    public String getName() 
    { return name; }
    public void setName(String name) 
    { this.name = name; }
    public String getEmail() 
    { return email; }
    public void setEmail(String email) { this.email = email; }

    // Abstraction
    public abstract void displayRole();
}