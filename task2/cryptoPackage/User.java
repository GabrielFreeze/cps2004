package cryptoPackage;

public abstract class User implements java.io.Serializable{
    protected String username;
    protected String password;
    protected Boolean login;


    public User(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public void login(String username, String password) throws Exception {
        if (this.username == username && this.password == password)
            login = true;
        else throw new Exception("Invalid Username and Password");
    }

    public void logout(){
        login = false;
    }

    public void assertLogin() throws IllegalAccessException {
        if (!login) throw new IllegalAccessException("User "+this+" must be logged in to perform this action.");
    }

    public String getUsername() {
        return username;
    }
    public String getPassword() {
        return password;
    }
    public Boolean getLoginStatus() {
        return login;
    }
    public void setUsername(String username) {
        this.username = username;
    }
    public void setPassword(String password) {
        this.password = password;
    }


}
