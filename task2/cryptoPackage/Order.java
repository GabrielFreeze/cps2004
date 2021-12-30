package cryptoPackage;
import java.util.ArrayList;
import java.util.Collections;

public class Order {

    private double quantity;      //The amount the trader is buying/selling.
    private double quantityRemaining;
    private Trader trader;        //Trader who created the order.
    private Crypto from;            //The coin the trader is selling / The coin the trader is buying.
    private Fiat to;              //The coin the trader will get paid in / The coin the trader will use to buy.

    private double volumeExecuted;
    private ArrayList<Trader> matchedTraders = new ArrayList<Trader>();         //The Trader that completed the order.
    private ArrayList<Double> matchedTradersBalance = new ArrayList<Double>();   //The Balance corresponding to the trader with the sae index in matchedTraders
    private static int count = 0;
    private int id;
    private OrderType type;     
    private OrderStatus status = OrderStatus.UNFILLED;

    protected Order(Trader trader, OrderType type, double quantity, Crypto from, Fiat to){
        this.quantity = quantity >= 0? quantity:0;
        this.quantityRemaining = quantity;
        this.trader = trader;
        this.type = type;
        this.id = count++;
        this.from = from;
        this.to = to;
        this.volumeExecuted = 0;
    }

    protected double getQuantity() {
        return quantity;
    }
    protected double getQuantityRemaining() {
        return quantityRemaining;
    }
    public Trader getTrader() {
        return trader;
    }
    public ArrayList<Trader> getMatchedTraders() {
        
        ArrayList<Trader> copy = new ArrayList<Trader>();
        Collections.copy(copy, matchedTraders);
        
        return copy;
    }
    public ArrayList<Double> getMatchedTradersBalance() {
        
        ArrayList<Double> copy = new ArrayList<Double>();
        Collections.copy(copy, matchedTradersBalance);
        
        return copy;
    }
    public void addMatchedTrader(Trader trader, double amount) {
        
        //Find if trader is already in list

        int index = -1;

        for (int i = 0; i < matchedTraders.size(); i++) {
            if (matchedTraders.get(i) == trader) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            index = matchedTraders.size();
            matchedTraders.add(trader);
            matchedTradersBalance.add(0.0);
        }

        //Update quantity for found matched trader.
        matchedTradersBalance.set(index,amount);
        
        
        
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
        return status;
    }
    protected int getId() {
        return id;
    }
    protected double getVolumeExecuted() {
        return volumeExecuted;
    }

    protected void setStatus(OrderStatus status) {
        this.status = status;
    }
    protected void setQuantityRemaining(double quantityRemaining) {
        this.quantityRemaining = Math.max(0, Math.min(quantity, quantityRemaining));
        volumeExecuted = (double) Math.round((1 - this.quantityRemaining/quantity)*10000.0)/100.0;

    }
    

}
