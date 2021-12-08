import pakSource.*;

class HelloWorld {
    public static void main (String args[]) {
        /*For a trader to be approved, he must login and register.
        An admin must also login, and choose to approve this trader.
        Then the trader must accept the approval by referencing the admin that approved him.*/
    


        // _   _
        // | | | |___  ___ _ __ ___
        // | | | / __|/ _ \ '__/ __|
        // | |_| \__ \  __/ |  \__ \
        //  \___/|___/\___|_|  |___/


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
        


            


        //      ____      _
        //     / ___|___ (_)_ __  ___
        //    | |   / _ \| | '_ \/ __|
        //    | |__| (_) | | | | \__ \
        //     \____\___/|_|_| |_|___/


        
        
        Fiat euro = new Fiat("€",2,1,1000);
        Fiat dollar = new Fiat("$", 2, 1,1000);
        
        try {

            //Trader adds fiat currencies to his account
                trader.addFiat(euro);
                trader.addFiat(dollar); 
                trader.addFiat(10, euro.getId());
                trader.addFiat(20, dollar.getId());
                System.out.println(trader.getBalance(euro.getId()));    //10.00
                System.out.println(trader.getBalance(dollar.getId()));  //20.00
            
            
           
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        
        trader.logout();
        admin.logout();
    }
}