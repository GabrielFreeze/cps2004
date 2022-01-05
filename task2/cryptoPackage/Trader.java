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
    private MatchingEngine matchingEngine;
    private OrderBook orderBook;

    public Trader(String username, String password) {
        super(username, password);
        registered = false;
        approved = false;
        matchingEngine = MatchingEngine.getInstance();
        orderBook = OrderBook.getInstance();
    }

    private static double round(double x, double d) {
        double y = Math.pow(10,d);
        return (double) Math.round(x*y)/y;
    }
    public void addFiat(double amount, Fiat fiatToAdd) throws java.lang.Error {
        //In a real world application, a bank's API will handle the transferring of cash.
        //However, just as a proof of concept, fiat currencies can simply be added regardless.
        //Checks with the bank can be made in this function.
    
        int fiatIndex = -1;

        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i) == fiatToAdd) {
                fiatIndex = i;
                break;
            }
        }

        if (fiatIndex < 0) { //Create new fiat and set its balance to amount.      
            if (amount <= 0) throw new java.lang.Error("Cannot add a negative amount of " + fiatToAdd.getSymbol() + " to Trader " + this.username);
            fiats.add(fiatToAdd);
            fiatsBalance.add(round(amount, fiatToAdd.getDecimals()));
            
        } else { //Increment balance by amount.
            if (amount < 0 && -amount > fiatsBalance.get(fiatIndex)) throw new java.lang.Error("Trader " + this.username + " does not have " + fiatToAdd.getSymbol() + -amount + " in their wallet.");
            fiatsBalance.set(fiatIndex,fiatsBalance.get(fiatIndex) + round(amount, fiatToAdd.getDecimals())); 
        }

    }

    protected void addCrypto(double amount, Crypto cryptoToAdd) throws java.lang.Error {
        //Assume that when a trader addsCrypto he is merely transfering the crypto coins from another wallet into the current one.
        //A real world application can handle the transfer in this function. 
        
        int cryptoIndex = -1;

        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i) == cryptoToAdd) {
                cryptoIndex = i;
                break;
            }
        }

        if (cryptoIndex < 0) { //Create new crypto and set its balance to amount.      
            if (amount <= 0) throw new java.lang.Error("Cannot add a negative amount of " + cryptoToAdd.getSymbol() + " to Trader " + this.username);
            cryptos.add(cryptoToAdd);
            cryptosBalance.add(round(amount, cryptoToAdd.getDecimals()));
        } else { //Increment balance by amount. 
            if (amount < 0 && amount > cryptosBalance.get(cryptoIndex)) throw new java.lang.Error("Trader " + this.username + " does not have " + cryptoToAdd.getSymbol() + -amount + " in their wallet.");
            cryptosBalance.set(cryptoIndex,cryptosBalance.get(cryptoIndex) + round(amount, cryptoToAdd.getDecimals())); 
        }

    }
    protected int existsFiat(Coin coin) {
        //Check for the coin in fiats
        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i) == coin) return i;
        }

        return -1;
    }
    protected int existsCrypto(Coin coin) {

        //Check for the coin in cryptos
        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i) == coin) return i;
        }

        return -1;

    }
    
    //Temporary Dummy Method
    public void _addCrypto(double amount, Crypto cryptoToAdd) throws java.lang.Error {
        addCrypto(amount,cryptoToAdd);
    }

    public double getBalance(Coin coin) throws java.lang.Error{
        
        int indexFiat = existsFiat(coin);
        int indexCrypto = existsCrypto(coin);

        if (indexFiat >= 0)        return fiatsBalance.get(indexFiat);
        else if (indexCrypto >= 0) return cryptosBalance.get(indexCrypto);
        else                       throw new java.lang.Error("Coin " + coin.getSymbol() +" does not exist in Trader's account.");


    }

    protected void pushActiveOrder(Order order) {
        activeOrders.add(order);
    }
    protected void removeActiveOrder(Order order) {
        activeOrders.remove(order);
    }


    public Boolean transfer(double amount, Fiat fiat, int bankId) throws Exception{
        /*In a real world application, a Bank's API can be used to actually transfer funds
        from a bank account into a trader's profile. However for the scope of this unit, the
        funds are transfered from nowehere. */
        assertLogin();

        addFiat(amount,fiat);

        return true;

    }

    public int sell(double amount, Crypto crypto, Fiat fiat, double limit) throws Exception {
        assertLogin();
        assertApproved();
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //coinIndex: What currency will he use to buy crypto.
        //limit: What should be the price of crypto before the order is available for execution.

        if (existsCrypto(crypto) < 0) throw new Exception("Trader is attempting to buy with a crypto currency he does not own.");
        if (amount < 0) throw new Exception("Trader "+this+" put negative quanatity for an order.");

        LimitOrder order = new LimitOrder(this, OrderType.SELL, round(amount, crypto.getDecimals()), crypto, fiat, limit);
        
        orderBook.pushOrder(order);
        matchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();
    }
    public int sell(double amount, Crypto crypto, Fiat fiat) throws Exception {
        assertLogin();
        assertApproved();
        //amount: How much will the user sell of crypto
        //crypto: The coin which the user will be selling
        //fiat: What fiat currency will he get.

        if (existsCrypto(crypto) < 0) throw new Exception("Trader is attempting to sell with a fiat currency he does not own.");
        if (amount < 0) throw new Exception("Trader "+this+" put negative quanatity for an order.");
        
        MarketOrder order = new MarketOrder(this, OrderType.SELL, round(amount, crypto.getDecimals()), crypto, fiat);
        
        orderBook.pushOrder(order);
        matchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();
    }

    //MarketOrder Buy.
    public int buy(double amount, Crypto crypto, Fiat fiat) throws Exception {
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //fiat: What fiat currency will he use to buy crypto.

        assertLogin();
        assertApproved();

        //Check that fiat is valid
        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        if (amount < 0) throw new Exception("Trader "+this+" put negative quanatity for an order.");
        
        MarketOrder order = new MarketOrder(this, OrderType.BUY, round(amount, crypto.getDecimals()), crypto, fiat);
        
        orderBook.pushOrder(order);
        matchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();

    }
    
    //LimitOrder Buy.
    public int buy(double amount, Crypto crypto, Fiat fiat, double limit) throws Exception{
        assertLogin();
        assertApproved();
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //coinIndex: What currency will he use to buy crypto.
        //limit: What should be the price of crypto before the order is available for execution.

        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        if (amount < 0) throw new Exception("Trader "+this+" put negative quanatity for an order.");

        LimitOrder order = new LimitOrder(this, OrderType.BUY, round(amount, crypto.getDecimals()), crypto, fiat, limit);
        
        orderBook.pushOrder(order);
        matchingEngine.add(order);
        pushActiveOrder(order);

        return order.getId();

    }


    public void cancel(int id) throws Exception{
        
        assertLogin();
        assertApproved();

        for (Order order: activeOrders) {
            if (order.getId() == id) {
                removeActiveOrder(order);
                matchingEngine.remove(order);
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
        return orderBook.copyOrderBook();
    }

    public Boolean getRegistered() {
        return registered;
    }
    public void setRegistered(Boolean registered) {
        this.registered = registered;
    }
    
    public Boolean getApproved() {
        return approved;
    }
    public Boolean setApproved(Boolean approved, Admin admin) throws Exception{

        if (!registered)
            throw new Exception("Trader " + this + " cannot be approved by " + admin + " because Trader is not registered.");

        if (admin.getTraderToApprove() != this)
            throw new Exception("Trader " + this + " cannot be approved by " + admin + " because admin did not approve Trader.");
        
        this.approved = approved;
        return true;

    }
    public void assertApproved() throws IllegalAccessException {
        if (this.approved == false) throw new IllegalAccessException("Trader "+this+" must be approved to perform this action.");
    }
}
