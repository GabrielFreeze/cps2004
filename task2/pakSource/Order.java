package pakSource;
import java.util.ArrayList;
import java.util.Collections;

class Order {

    private double quantity;      //The amount the trader is buying/selling.
    private Trader trader;        //Trader who created the order.
    private Crypto from;            //The coin the trader is selling / The coin the trader is buying.
    private Fiat to;              //The coin the trader will get paid in / The coin the trader will use to buy.

    private ArrayList<Trader> matchedTraders = new ArrayList<Trader>(); //The Trader that completed the order.
    
    private OrderType type;     //Buy or Ask
    private OrderStatus orderStatus = OrderStatus.UNFILLED;

    protected Order(Trader trader, OrderType type, double quantity, Crypto from, Fiat to){
        this.quantity = quantity;
        this.trader = trader;
        this.type = type;

        this.from = from;
        this.to = to;
    }

    protected double getQuantity() {
        return quantity;
    }
    protected Trader getTrader() {
        return trader;
    }
    protected ArrayList<Trader> getMatchedTraders() {
        
        ArrayList<Trader> copy = new ArrayList<Trader>();
        Collections.copy(copy, matchedTraders);
        
        return copy;
    }
    protected void addMatchedTrader(Trader trader) {
        matchedTraders.add(trader);
    }


    protected Crypto getFrom() {
        return from;
    }
    protected Fiat getTo() {
        return to;
    }
    protected OrderType getType() {
        return type;
    }
    protected OrderStatus getStatus() {
        return orderStatus;
    }
}
