package crytpoPackage;

public abstract class User {
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

    protected void assertLogin() throws Exception{
        if (!login) throw new Exception("User must be logged in to perform this action.");
    }

    
//     ____ _____ _____ _____ _____ ____  ____       _    _   _ ____     ____  _____ _____ _____ _____ ____  ____     
//     / ___| ____|_   _|_   _| ____|  _ \/ ___|     / \  | \ | |  _ \  / ___|| ____|_   _|_   _| ____|  _ \/ ___|
//    | |  _|  _|   | |   | | |  _| | |_) \___ \    / _ \ |  \| | | | | \___ \|  _|   | |   | | |  _| | |_) \___ \ 
//    | |_| | |___  | |   | | | |___|  _ < ___) |  / ___ \| |\  | |_| |  ___) | |___  | |   | | | |___|  _ < ___) | 
//     \____|_____| |_|   |_| |_____|_| \_\____/  /_/   \_\_| \_|____/  |____/|_____| |_|   |_| |_____|_| \_\____/


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
