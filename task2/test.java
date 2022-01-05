import cryptoPackage.*;


public class test {
    public static void main(String[] args) {
        try {
            Trader trader = new Trader("trader","123");
            Admin admin = new Admin("admin","456");

            assert(trader.getLoginStatus() == false);
            trader.login("trader", "123");
            assert(trader.getLoginStatus() == true);
            
            assert(admin.getLoginStatus() == false);
            admin.login("admin", "456");
            assert(admin.getLoginStatus() == true);


            assert(trader.getRegistered() == false);
            trader.setRegistered(true);
            assert(trader.getRegistered() == true);

            assert(admin.getTraderToApprove() == null);
            admin.setTraderToApprove(trader);
            assert(admin.getTraderToApprove() == trader);

            assert(trader.getApproved() == false);
            trader.setApproved(true,admin);
            assert(trader.getApproved() == true);



            Trader joe = new Trader("joe","123");
            joe.login("joe", "123");
            joe.setRegistered(true);
            admin.setTraderToApprove(joe);
            joe.setApproved(true, admin);
            

            Fiat euro = new Fiat("€", 2, 1, 1000.0);
            Crypto btc = new Crypto("$BTC", 8, 100, 1000.0);
            MatchingEngine matchingEngine = MatchingEngine.getInstance();
            OrderBook orderBook = OrderBook.getInstance();


            trader.transfer(10,euro,123);
            assert(trader.getBalance(euro) == 10);

            joe._addCrypto(20, btc);
            assert(joe.getBalance(btc) == 20);

            int id1 = trader.buy(2,btc,euro);
            assert(orderBook.getOrder(id1).getId() == id1); //asserts that the order exists.

            int id2 = joe.sell(2,btc,euro);
            assert(orderBook.getOrder(id2).getId() == id2); //asserts that the order exists.

            assert(orderBook.getOrder(id1).getVolumeExecuted() == 0.0);
            assert(orderBook.getOrder(id2).getVolumeExecuted() == 0.0);


            matchingEngine.update();
            
            assert(orderBook.getOrder(id1).getVolumeExecuted() == 100.0);
            assert(orderBook.getOrder(id2).getVolumeExecuted() == 100.0);



        } catch (Exception e) {System.err.println(e.getMessage());}

        System.out.println("All Unit Tests Worked!");
    }
}
