import pakSource.*;

class HelloWorld {
    public static void main (String args[]) {
        /*For a trader to be approved, he must login and register.
        An admin must also login, and choose to approve this trader.
        Then the trader must accept the approval by referencing the admin that approved him.*/
    
        //Create a trader and an admin account.
        Trader trader = new Trader("trader","123");
        Admin admin =  new Admin("admin", "123");
        

        //Admin logs in
            try {      
                admin.login("admin","123");
            } catch (Exception e) {
                System.out.println("The admin did not log in correctly.");
                System.exit(0);
            }


        //Trader logs in
            try {      
                trader.login("trader","123");
            } catch (Exception e) {
                //The trader did not log in correctly.
                System.out.println("The trader did not log in correctly.");
                System.exit(0);
            }


        // Trader registers for approval
            try {
                trader.setRegistered(true);
            } catch (Exception e) {
                //Thr trader is not logged in
                System.out.println("The trader is not logged in");
                System.exit(0);
            }


        //Admin wants to register trader
            try {
                admin.setTraderToApprove(trader);
            } catch (Exception e) {
                //Admin may not be logged in
                //Trader may not have registered to be approved
                System.out.println("Admin could not approve trader");
                System.exit(0);
            }
        
        //Trader can confirm approval request by referencing to the admin that approved him
            try {
                trader.setApproved(true, admin);
            } catch (Exception e) {
                //Reference to admin that does not want trader to be approved
                //Trader may not be registered to be approved.
                System.out.println("Trader could not accept approval request");
                System.exit(0);
            }
        


        //Trader and admin logout
        trader.logout();
        admin.logout();

        System.out.println("!");

        
        Fiat euro = new Fiat("€",2,1,1000);
        
        //Reference to euro added to trader. Trader still hasn't bought any euro
        try {
            trader.addFiat(euro); 
        } catch (Exception e) {
            //trader is not logged in.
        }
            
        
        try {
            trader.addFiat(10, euro.getId());
        } catch (Exception e) {
            //Amount may be non-negative
            //Euro may not have been added to trader's available crypto coins.
        }



    }
}