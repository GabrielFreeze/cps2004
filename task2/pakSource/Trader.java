package pakSource;
public class Trader extends User{


    protected Boolean registered;
    protected Boolean approved;

    public Trader(String username, String password) {
        super(username, password);
        registered = false;
    }


    



//     ____ _____ _____ _____ _____ ____  ____       _    _   _ ____     ____  _____ _____ _____ _____ ____  ____     
//     / ___| ____|_   _|_   _| ____|  _ \/ ___|     / \  | \ | |  _ \  / ___|| ____|_   _|_   _| ____|  _ \/ ___|
//    | |  _|  _|   | |   | | |  _| | |_) \___ \    / _ \ |  \| | | | | \___ \|  _|   | |   | | |  _| | |_) \___ \ 
//    | |_| | |___  | |   | | | |___|  _ < ___) |  / ___ \| |\  | |_| |  ___) | |___  | |   | | | |___|  _ < ___) | 
//     \____|_____| |_|   |_| |_____|_| \_\____/  /_/   \_\_| \_|____/  |____/|_____| |_|   |_| |_____|_| \_\____/
   

    public Boolean getRegistered() {
        return registered;
    }
    public void setRegistered(Boolean registered) {
        this.registered = registered;
    }
    
    public Boolean getApproved() {
        return approved;
    }
    public void setApproved(Boolean approved, Admin admin) throws Exception {

        if (admin.getTraderToApprove() != this)
            throw new Exception("Admin passed to setApproved must reference Trader to approve in traderToApprove in Admin");
        
        this.approved = approved;
        

    }

    
}
