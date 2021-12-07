package pakSource;
public class Admin extends User{
    
    private Trader traderToApprove = null;

    public Admin(String username, String password) {
        super(username, password);
    }


    public void setTraderToApprove(Trader traderToApprove) throws Exception {
        if (!login) throw new Exception("Login to admin");
        if (!traderToApprove.registered) throw new Exception("Trader did not register to be approved");
        this.traderToApprove = traderToApprove;
    }

    public Trader getTraderToApprove() {
        return this.traderToApprove;
    }


}
