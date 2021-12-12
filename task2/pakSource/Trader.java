package pakSource;
import java.util.ArrayList;
public class Trader extends User{


    protected Boolean registered;
    protected Boolean approved;

    
    protected ArrayList<Crypto> cryptos = new ArrayList<Crypto>();        //The cryptos the trader has.
    protected ArrayList<Double> cryptosBalance = new ArrayList<Double>(); //The amounts the trader has relating to a crypto.

    public ArrayList<Fiat> fiats = new ArrayList<Fiat>();              //The fiat the trader has.
    public ArrayList<Double> fiatsBalance = new ArrayList<Double>();   //The amounts the trader has relating to a fiat.


    public Trader(String username, String password) {
        super(username, password);
        registered = false;
    }


    public void addFiat(double amount, Fiat fiatToAdd) throws Exception {
        //In a real world application, a bank's API will handle the transferring of cash.
        //However, just as a proof of concept, fiat currencies can simply be added regardless.
        //Checks with the bank can be made in this function.
        assertLogin();

        if (amount <= 0)
            throw new Exception("Amount given must be non-negative");
        
        int fiatIndex = -1;

        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i) == fiatToAdd) {
                fiatIndex = i;
                break;
            }
        }

        if (fiatIndex < 0) { //Create new fiat and set its balance to amount.
            fiats.add(fiatToAdd);
            fiatsBalance.add((double) amount);
        } else { //Increment balance by amount.
            fiatsBalance.set(fiatIndex,fiatsBalance.get(fiatIndex) + (double) amount); 
        }

    }

    public void addCrypto(double amount, Crypto cryptoToAdd) throws Exception {
        //Assume that when a trader addsCrypto he is merely transfering the crypto coins from another wallet into the current one.
        //A real world application can handle the transfer in this function. 
        assertLogin();

        if (amount <= 0)
            throw new Exception("Amount given must be non-negative");
        
        int cryptoIndex = -1;

        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i) == cryptoToAdd) {
                cryptoIndex = i;
                break;
            }
        }

        if (cryptoIndex < 0) { //Create new fiat and set its balance to amount.
            cryptos.add(cryptoToAdd);
            cryptosBalance.add((double) amount);
        } else { //Increment balance by amount.
            cryptosBalance.set(cryptoIndex,cryptosBalance.get(cryptoIndex) + (double) amount); 
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
        else                       throw new Exception("Coin " + coin.symbol +" does not exist in Trader's account.");


    }



    public void sell(double amount, Crypto crypto, Fiat fiat) throws Exception {
        assertLogin();
        //amount: How much will the user sell of crypto
        //crypto: The coin which the user will be selling
        //fiat: What fiat currency will he get.

        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");

        MarketOrder order = new MarketOrder(this, OrderType.SELL, amount, crypto, fiat);
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);
    }


    //MarketOrder Buy.
    public void buy(double amount, Crypto crypto, Fiat fiat) throws Exception {
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //fiat: What fiat currency will he use to buy crypto.

        assertLogin();

        //Check that fiat is valid
        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        
        MarketOrder order = new MarketOrder(this, OrderType.BUY, amount, crypto, fiat);
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);

    }
    
    //LimitOrder Buy.
    public void buy(double amount, Crypto crypto, Fiat fiat, double limit) throws Exception{
        assertLogin();
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //coinIndex: What currency will he use to buy crypto.
        //limit: What should be the price of crypto before the order is available for execution.

        if (existsFiat(fiat) < 0) throw new Exception("Trader is attempting to buy with a fiat currency he does not own.");
        
        LimitOrder order = new LimitOrder(this, OrderType.BUY, amount, crypto, fiat, limit);
        OrderBook.pushOrder(order);
        MatchingEngine.add(order);

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
