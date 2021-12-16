package cryptoPackage;
import java.util.ArrayList;
import java.util.Collections;
public class Trader extends User{


    protected Boolean registered;
    protected Boolean approved;

    
    private ArrayList<Crypto> cryptos = new ArrayList<Crypto>();        //The cryptos the trader has.
    private ArrayList<Double> cryptosBalance = new ArrayList<Double>(); //The amounts the trader has relating to a crypto.

    private ArrayList<Fiat> fiats = new ArrayList<Fiat>();              //The fiat the trader has.
    private ArrayList<Double> fiatsBalance = new ArrayList<Double>();   //The amounts the trader has relating to a fiat.


    private ArrayList<Order> activeOrders = new ArrayList<Order>();


    public Trader(String username, String password) {
        super(username, password);
        registered = false;
    }

    private static double round(double x, double d) {
        double y = Math.pow(10,d);
        return (double) Math.round(x*y)/y;
    }
    public void addFiat(double amount, Fiat fiatToAdd) throws Exception {
        //In a real world application, a bank's API will handle the transferring of cash.
        //However, just as a proof of concept, fiat currencies can simply be added regardless.
        //Checks with the bank can be made in this function.
        assertLogin();
    
        int fiatIndex = -1;

        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i) == fiatToAdd) {
                fiatIndex = i;
                break;
            }
        }

        if (fiatIndex < 0) { //Create new fiat and set its balance to amount.      
            if (amount <= 0) throw new Exception("Cannot add a negative amount of " + fiatToAdd.getSymbol() + " to Trader " + this.username);
            fiats.add(fiatToAdd);
            fiatsBalance.add(round(amount, fiatToAdd.getDecimals()));
            
        } else { //Increment balance by amount.
            if (amount < 0 && -amount > fiatsBalance.get(fiatIndex)) throw new Exception("Trader " + this.username + " does not have " + fiatToAdd.getSymbol() + -amount + " in their wallet.");
            fiatsBalance.set(fiatIndex,fiatsBalance.get(fiatIndex) + round(amount, fiatToAdd.getDecimals())); 
        }

    }

    public void addCrypto(double amount, Crypto cryptoToAdd) throws Exception {
        //Assume that when a trader addsCrypto he is merely transfering the crypto coins from another wallet into the current one.
        //A real world application can handle the transfer in this function. 
        assertLogin();
        
        int cryptoIndex = -1;

        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i) == cryptoToAdd) {
                cryptoIndex = i;
                break;
            }
        }

        if (cryptoIndex < 0) { //Create new crypto and set its balance to amount.      
            if (amount <= 0) throw new Exception("Cannot add a negative amount of " + cryptoToAdd.getSymbol() + " to Trader " + this.username);
            cryptos.add(cryptoToAdd);
            cryptosBalance.add(round(amount, cryptoToAdd.getDecimals()));
        } else { //Increment balance by amount. 
            if (amount < 0 && amount > cryptosBalance.get(cryptoIndex)) throw new Exception("Trader " + this.username + " does not have " + cryptoToAdd.getSymbol() + -amount + " in their wallet.");
            cryptosBalance.set(cryptoIndex,cryptosBalance.get(cryptoIndex) + round(amount, cryptoToAdd.getDecimals())); 
        }

    }
    public int existsFiat(Coin coin) {
        //Check for the coin in fiats
        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i) == coin) return i;
        }

        return -1;
    }
    public int existsCrypto(Coin coin) {

        //Check for the coin in cryptos
        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i) == coin) return i;
        }

        return -1;

    }
    
    public double getBalance(Coin coin) throws Exception{
        
        assertLogin();

        int indexFiat = existsFiat(coin);
        int indexCrypto = existsCrypto(coin);

        if (indexFiat >= 0)        return fiatsBalance.get(indexFiat);
        else if (indexCrypto >= 0) return cryptosBalance.get(indexCrypto);
        else                       throw new Exception("Coin " + coin.getSymbol() +" does not exist in Trader's account.");


    }


    private void pushActiveOrder(Order order) {
        activeOrders.add(order);
    }
    protected void removeActiveOrder(Order order) {
        activeOrders.remove(order);
    }


    public int sell(double amount, Crypto crypto, Fiat fiat) throws Exception {
        assertLogin();
        //amount: How much will the user sell of crypto
        //crypto: The coin which the user will be selling
        //fiat: What fiat currency will he get.

        if (existsCrypto(crypto) < 0) throw new Exception("Trader is attempting to sell with a fiat currency he does not own.");

        MarketOrder order = new MarketOrder(this, OrderType.SELL, round(amount, crypto.getDecimals()), crypto, fiat);
        
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();
    }

    //MarketOrder Buy.
    public int buy(double amount, Crypto crypto, Fiat fiat) throws Exception {
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //fiat: What fiat currency will he use to buy crypto.

        assertLogin();

        //Check that fiat is valid
        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        
        MarketOrder order = new MarketOrder(this, OrderType.BUY, round(amount, crypto.getDecimals()), crypto, fiat);
        
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();

    }
    
    //LimitOrder Buy.
    public int buy(double amount, Crypto crypto, Fiat fiat, double limit) throws Exception{
        assertLogin();
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //coinIndex: What currency will he use to buy crypto.
        //limit: What should be the price of crypto before the order is available for execution.

        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        
        LimitOrder order = new LimitOrder(this, OrderType.BUY, round(amount, crypto.getDecimals()), crypto, fiat, limit);
        
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();

    }


    public void cancel(int id) throws Exception{
        
        for (Order order: activeOrders) {
            if (order.getId() == id) {
                removeActiveOrder(order);
                MatchingEngine.remove(order);
                order.setStatus(OrderStatus.CANCELLED);
                return;
            }
        }
        throw new Exception("No Order with ID "+ id +" was found in Trader "+ username);
    }

    public ArrayList<Order> getActiveOrdersCopy() {
        ArrayList<Order> copy = new ArrayList<Order>();
        Collections.copy(copy,activeOrders);
        
        return copy;
    }
    public void printActiveOrders() {
        System.out.println("\n\n"+username+"'S ACTIVE ORDERS    :");
        System.out.println("\n\nID\tTRADER\tTYPE\tPAIR\tQUANTITY\tVOL EXEC'D\tSTATUS");
        System.out.println("--------------------------------------------------------------------------------");
        
        for (int i = activeOrders.size()-1 ; i >= 0; i--) {
            Order o = activeOrders.get(i);
            System.out.println(
                o.getId()+"\t"                                         +
                o.getTrader().getUsername()+"\t"                       +
                o.getType()+"\t"                                       +
                o.getFrom().getSymbol()+"/"+o.getTo().getSymbol()+"\t" +
                o.getQuantity()+"\t\t"                                 +
                o.getVolumeExecuted()+"%\t\t"                          +
                o.getStatus());
        }
        System.out.println();
    }
    public ArrayList<Order> getOrderBookCopy() {
        return OrderBook.copyOrderBook();
    }

    public Boolean getRegistered() throws Exception {
        assertLogin();
        return registered;
    }
    public void setRegistered(Boolean registered) throws Exception {
        assertLogin();
        this.registered = registered;
    }
    
    public Boolean getApproved() throws Exception {
        assertLogin();
        return approved;
    }
    public void setApproved(Boolean approved, Admin admin) throws Exception {
        assertLogin();

        if (!registered)
            throw new Exception("Trader is not registered");
        if (admin.getTraderToApprove() != this)
            throw new Exception("Admin passed to setApproved must reference Trader to approve in traderToApprove in Admin");
        
        this.approved = approved;
        

    }

}
