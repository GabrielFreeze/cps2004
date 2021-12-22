import cryptoPackage.*;

import java.util.ArrayList;

class cryptoPackageLauncher {
    public static void main (String args[]) {
        /*For a trader to be approved, he must login and register.
        An admin must also login, and choose to approve this trader.
        Then the trader must accept the approval by referencing the admin that approved him.*/
        

        //  _   _
        // | | | |___  ___ _ __ ___
        // | | | / __|/ _ \ '__/ __|
        // | |_| \__ \  __/ |  \__ \
        //  \___/|___/\___|_|  |___/


        //Create a trader and an admin account.
        Trader trader = new Trader("trader","123");
        Trader joe = new Trader("joe", "joeyjoe");
        Trader baba = new Trader("baba", "isyou");
        Admin admin =  new Admin("admin", "123");
        
        
        try {
            
            //All accounts log in.
            admin.login("admin","123");
            trader.login("trader","123");
            joe.login("joe","joeyjoe");
            baba.login("baba", "isyou");
            
            //Traders register for approval
            trader.setRegistered(true);
            joe.setRegistered(true);
    
            //Admin approved traders.
            admin.setTraderToApprove(trader);
            admin.setTraderToApprove(joe);

            //Traders must accept approval and reference the admin that approved them..
            trader.setApproved(true, admin);
            joe.setApproved(true, admin);

            
        } catch (Exception e) {System.out.println(e.getMessage());}




        //      ____      _
        //     / ___|___ (_)_ __  ___
        //    | |   / _ \| | '_ \/ __|
        //    | |__| (_) | | | | \__ \
        //     \____\___/|_|_| |_|___/


                
        
        Fiat euro = new Fiat("€", 2, 1, 1000.0);            //A new Fiat coin was created
        Fiat dollar = new Fiat("$", 2, 1.12, 1000.0);          //A new Fiat coin was created

        Crypto btc = new Crypto("$BTC", 8, 100, 1000.0);
        Crypto doge = new Crypto("$DOGE", 8, 845, 1000.0);

        MatchingEngine matchingEngine = MatchingEngine.getInstance();
        OrderBook orderBook = OrderBook.getInstance();
        int orderID = -1;
        try {
            trader.transfer(10000, euro, 123);                     //Trader adds €10 to his account.
            trader.transfer(20, dollar, 123);                     //Trader adds $10 to his account.
            
            joe.transfer(200, dollar, 456);
            baba.transfer(100, euro, 789);
            
            /* A user cannot decide to add crypto from thin air, however
            for the sake of the demonstration let's assume that Joe already has
            some crypto in his account.
            
            The method addCrypto would preferably be PROTECTED, like addFiat.
            The launcher file should not have access to add funds to a trader's account
            without the neccessary checks such as being logged in and approved.
            However I created a dummy method for demonstration purposes, as I wanted to show
            trades between 2 traders..*/

            joe._addCrypto(200, btc);
            joe._addCrypto(100, doge);


            System.out.println("Trader's euro balance: " + trader.getBalance(euro));      //10.00
            System.out.println("Trader's dollar balance: " + trader.getBalance(dollar));  //20.00

            System.out.println("Joe's BTC balance: " + joe.getBalance(btc));           //200.00000000
            System.out.println("Joe's DOGE balance: " + joe.getBalance(doge));         //100.00000000
            

            //The trader wishes to use his EUROS to buy some BTC.
            //This order is added to the orderbook and remains UNFULFILLED.
            trader.buy(2, btc, euro);
            matchingEngine.printQueue();

            //The Matching Engine attempts to match any orders but does not find any
            matchingEngine.update();

            //Joe wishes to sell 4 BTC for the equivalent in euros.
            //This order is added to the orderbook and remains UNFULFILLED
            joe.sell(4, btc, euro);
            // matchingEngine.printQueue();

            /* The Matching Engine realises it could match trader's buy order with joe's sell order.
            Since trader only wants 2 btc, his order will be fullfilled. However joe's order still needs to sell
            the remaioning 2 btc. */
            matchingEngine.update();
            // matchingEngine.printQueue();
            
            //Trader's wallet.
            System.out.println("Trader's BTC wallet:\t" + trader.getBalance(btc));
            System.out.println("Trader's euro wallet:\t" + trader.getBalance(euro));

            //Joe's wallet.
            System.out.println("Joe's BTC wallet:\t" + joe.getBalance(btc));
            System.out.println("Joe's euro wallet:\t" + joe.getBalance(euro));
            
            orderBook.printOrderBook();

            //Baba will place a buy limit order for when the price of BTC (exchange rate) is 50 or less.
            orderID = baba.buy(10, btc, euro, 50);

            /*The new order is not matched with joe's partially filled order as the 
            price of BTC has not met the limit order's condition.*/
            matchingEngine.update();
            orderBook.printOrderBook();

            /*In a real world application this function would be applied on the actual value of BTC,
            however in this example let's assume that the price has magically fallen.*/
            btc.setExchangeRate(50);
            
            /*Since the limit order can now be executed, it will be matched with joe's previous order*/
            matchingEngine.update();
            orderBook.printOrderBook();
            
            //Baba's wallet.
            System.out.println("Baba's BTC wallet:\t" + baba.getBalance(btc));
            System.out.println("Baba's euro wallet:\t" + baba.getBalance(euro));

            //Joe's wallet.
            System.out.println("Joe's BTC wallet:\t" + joe.getBalance(btc));
            System.out.println("Joe's euro wallet:\t" + joe.getBalance(euro));


            /*Baba decides to cancel his order of 10 btc, despite already buying 2.
            This will remove the order from the Matching Engine Queue and update it's status on the Order Book.*/
            baba.printActiveOrders();
            baba.cancel(orderID);
            baba.printActiveOrders();


            /*Joe is now selling 4 BTC, however since baba cancelled his buy order, joe's order won't
            be matched by anyone.*/
            joe.sell(4,btc,euro);
            matchingEngine.update();
            orderBook.printOrderBook();

                       
        } catch (Exception e) {
            /* If a trader is not logged in or is not approved by an administrator
            and attempts to place orders, an exception is raised. A real world application
            */

            System.out.println(e.getMessage());
        }
        
        //  __  __                  _____                           _
        // |  \/  | ___  _ __ ___  | ____|_  ____ _ _ __ ___  _ __ | | ___  ___
        // | |\/| |/ _ \| '__/ _ \ |  _| \ \/ / _` | '_ ` _ \| '_ \| |/ _ \/ __|
        // | |  | | (_) | | |  __/ | |___ >  < (_| | | | | | | |_) | |  __/\__ \
        // |_|  |_|\___/|_|  \___| |_____/_/\_\__,_|_| |_| |_| .__/|_|\___||___/  

        /*A trader may view the OrderBook at any given time. A trader may also
        copy the OrderBook. */
        ArrayList<Order> orderBookCopy = trader.getOrderBookCopy();
        System.out.println(orderBookCopy);
        
        /*Quantities in orders are automatically rounded to fit the allowed
        decimal places for any coin.
        Example: Buying €2.567 defaults to €2.58 because euros.decimals = 2
        Example: Buying $BTC 2.567 defaults to $BTC 2.56700000 because btc.decimals = 8
        */
        try {
            trader.buy(2.567, btc, euro);
            orderBook.printOrderBook(); 
        } catch (Exception e) {};

        /*A Trader must be logged in and approved in order to place orders,
        otherwise an exception is raised*/
        try {
            Trader david = new Trader("david", "david");
            david.buy(10, doge, dollar);
            System.out.println("Order confirmed.");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        };


        /*An order also keeps track of which traders executed it. */
        try {
            Order order = orderBook.getOrder(orderID);
            ArrayList<Trader> tradersMatched = order.getTradersMatched();
            ArrayList<Double> tradersMatchedBalance = order.getTradersMatchedBalance();

            for (int i = 0; i < tradersMatched.size(); i++) {
                System.out.println("Trader " + tradersMatched.get(i).getUsername() +
                                   " sold " + tradersMatchedBalance.get(i) + " to Trader " + 
                                   order.getTrader().getUsername());
            }

        } catch (Exception e) {};
        
        trader.logout();
        admin.logout();
    }
}