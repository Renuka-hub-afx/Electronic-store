public class Review {
    private int id;
    private int rating;
    private String comments;
    private String serviceFeedback;
    private static int counter = 1;

    public Review(int rating, String comments) {
        this.id = counter++;
        this.rating = rating;
        this.comments = comments;
    }
}