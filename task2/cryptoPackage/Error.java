package cryptoPackage;

public class Error {
    protected static void handleError(Exception e) {
        System.out.println(e.getMessage());
        System.exit(0);
    }
}
