import pakSource.*;

class HelloWorld {
    public static void main (String args[]) {
        /*For a trader to be approved, he must login and register.
        An admin must also login, and choose to approve this trader.
        Then the trader must accept the approval by referencing the admin that approved him.*/
        
        //TODO: Create an error system


        //  _   _
        // | | | |___  ___ _ __ ___
        // | | | / __|/ _ \ '__/ __|
        // | |_| \__ \  __/ |  \__ \
        //  \___/|___/\___|_|  |___/


        //Create a trader and an admin account.
        Trader trader = new Trader("trader","123");
        Trader joe = new Trader("joe", "joeyjoe");
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
                joe.login("joe","joeyjoe");
            } catch (Exception e) {
                //The trader did not log in correctly.
                System.out.println("The trader did not log in correctly.");
                System.exit(0);
            }


        // Trader registers for approval
            try {
                trader.setRegistered(true);
                joe.setRegistered(true);
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
            
        //Admin wants to register trader
        try {
            admin.setTraderToApprove(joe);
        } catch (Exception e) {
            //Admin may not be logged in
            //Trader may not have registered to be approved
            System.out.println("Admin could not approve trader");
            System.exit(0);
        }
        
        //Trader can confirm approval request by referencing to the admin that approved him
        try {
            joe.setApproved(true, admin);
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


        

        
        
        Fiat euro = new Fiat("€", 2, 1, 1000.0);            //A new Fiat coin was created
        Fiat dollar = new Fiat("$", 2, 1.12, 1000.0);          //A new Fiat coin was created

        Crypto btc = new Crypto("$BTC", 8, 100, 1000.0);
        Crypto doge = new Crypto("$DOGE", 8, 845, 1000.0);
        
        try {
            trader.addFiat(10000, euro);                       //Trader adds €10 to his account.
            trader.addFiat(20, dollar);                     //Trader adds $10 to his account.
            
            joe.addFiat(200, dollar);
            joe.addCrypto(200, btc);
            joe.addCrypto(100, doge);

            System.out.println("Trader's euro balance: " + trader.getBalance(euro));      //10.00
            System.out.println("Trader's dollar balance: " + trader.getBalance(dollar));  //20.00

            System.out.println("Joe's BTC balance: " + joe.getBalance(btc));           //200.00000000
            System.out.println("Joe's DOGE balance: " + joe.getBalance(doge));         //100.00000000
            

            //The trader wishes to use his EUROS to buy some BTC.
            //This order is added to the orderbook and remains UNFULFILLED.
            trader.buy(2, btc, euro);
            MatchingEngine.printQueue();

            //The Matching Engine attempts to match any orders but does not find any
            MatchingEngine.update();

            //Joe wishes to sell 4 BTC for the equivalent in euros.
            //This order is added to the orderbook and remains UNFULFILLED
            joe.sell(4, btc, euro);
            MatchingEngine.printQueue();

            /* The Matching Engine realises it could match trader's buy order with joe's sell order.
            Since trader only wants 2 btc, his order will be fullfilled. However joe's order still needs to sell
            the remaioning 2 btc. */
            MatchingEngine.update();
            MatchingEngine.printQueue();
            
            //Trader's wallet.
            System.out.println("Trader's BTC wallet:\t" + trader.getBalance(btc));
            System.out.println("Trader's euro wallet:\t" + trader.getBalance(euro));

            //Joe's wallet.
            System.out.println("Joe's BTC wallet:\t" + joe.getBalance(btc));
            System.out.println("Joe's euro wallet:\t" + joe.getBalance(euro));
            
            OrderBook.printOrderBook();

            //Trader will place a buy limit order for when the price of BTC (exchange rate) is 50 or less.
            trader.buy(2, btc, euro, 50);

            /*The new order is not matched with joe's partially filled order as the 
            price of BTC has not met the limit order's condition.*/
            MatchingEngine.update();
            OrderBook.printOrderBook();

            /*In a real world application this function would be applied on the actual value of BTC,
            however in this example let's assume that the price has magically fallen.*/
            btc.setExchangeRate(50);
            
            /*Since the limit order can now be executed, it will be matched with joe's previous order*/
            MatchingEngine.update();
            OrderBook.printOrderBook();
            
            //Trader's wallet.
            System.out.println("Trader's BTC wallet:\t" + trader.getBalance(btc));
            System.out.println("Trader's euro wallet:\t" + trader.getBalance(euro));

            //Joe's wallet.
            System.out.println("Joe's BTC wallet:\t" + joe.getBalance(btc));
            System.out.println("Joe's euro wallet:\t" + joe.getBalance(euro));

                       
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        
        
        trader.logout();
        admin.logout();
    }
}