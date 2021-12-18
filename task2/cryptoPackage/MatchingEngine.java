package cryptoPackage;
import java.util.Comparator;
import java.util.PriorityQueue;

//MatchingEngine is a singleton class.
public class MatchingEngine {

    private static Comparator<Order> orderComparator = new Comparator<Order>() {
        public int compare(Order a, Order b) {
            return (int) (a.getQuantity() - b.getQuantity());
        }
    };

    private static MatchingEngine matchingEngine = null;
    private PriorityQueue<Order> queue = new PriorityQueue<Order>(orderComparator);


    public static MatchingEngine getInstance() {
        if (matchingEngine == null) matchingEngine = new MatchingEngine();
        return matchingEngine;
    }

    protected void add(Order order) {
        queue.add(order);
    }
    protected void remove(Order order) {
        queue.remove(order);
    }

    public void printQueue() {
        System.out.println("Matching Engine Order Queue: " + queue);
    }

    public Boolean limitOrderReady(LimitOrder order) {
       
        if (order.getType() == OrderType.BUY) //Returns true if the price of FROM is less than the bid price. 
            return order.getFrom().getExchangeRate() <= order.getBidask();

        else                                  //Returns true if the price of FROM is more than the ask price. 
            return order.getFrom().getExchangeRate() >= order.getBidask();
    }


    public int update() {
        //For every order, traverse down the queue and find any matching order

        for (Order o : queue) {

            for (Order p : queue) {
                
                //Preliminary plumbing
                if (o instanceof LimitOrder && !limitOrderReady((LimitOrder) o)  ||
                    p instanceof LimitOrder && !limitOrderReady((LimitOrder) p)) continue;

                if (o == p                          ||
                    p.getType() == o.getType()      ||
                    p.getTrader() == o.getTrader()  ||
                    p.getFrom() != o.getFrom()      ||
                    p.getTo() != o.getTo())         continue;

                    
                
                //Check that o and p have enough crypto/fiat to make the trade.
                
                double buyBal = 0;
                double sellBal = 0;
                double amount = o.getQuantityRemaining() > p.getQuantityRemaining()? p.getQuantityRemaining() : o.getQuantityRemaining();
                
                Order buy;
                Order sell;

                if (o.getType() == OrderType.BUY) {
                    buy = o;
                    sell = p;
                } else {
                    buy = p;
                    sell = o;
                }


                try {
                    buyBal = buy.getTrader().getBalance(buy.getTo());
                    sellBal = sell.getTrader().getBalance(sell.getFrom());
                } catch (Exception e) {Error.handleError(e);}
                
                    
                /*If buyer doesn't have enough fiat to pay the seller,
                or the seller doesn't have enough crypto to give to the buyer. */
                if (buyBal < amount * p.getFrom().getExchangeRate() * p.getTo().getExchangeRate() ||
                    sellBal < amount)                                                             continue;

                //Handle the transfer of coins.
                matchOrders(buy, sell);
                
            }
        }
        
        return 0;
    }


    private void matchOrders(Order buy, Order sell) {
        
        //Mention which traders fulfilled orders buy and sell.
        buy.addMatchedTrader(sell.getTrader());
        sell.addMatchedTrader(buy.getTrader());
        

        
        try {
            //The amount which should be subtracted from each order
            double amount = sell.getQuantityRemaining() > buy.getQuantityRemaining()? buy.getQuantityRemaining() : sell.getQuantityRemaining();

            //The price in Fiat which the seller will recieve from the buyer.
            double amountInFiat = amount * sell.getFrom().getExchangeRate() * sell.getTo().getExchangeRate();

            //Transfer the crypto which the buyer bought from the seller.
            sell.getTrader().addCrypto(-amount, sell.getFrom());
            buy.getTrader().addCrypto(amount, sell.getFrom());
            
            //Update the order's remaining quantity
            double buyQuantity = buy.getQuantityRemaining();
            double sellQuantity = sell.getQuantityRemaining();
            
            buy.setQuantityRemaining(buyQuantity-sellQuantity);
            sell.setQuantityRemaining(sellQuantity-buyQuantity);

            //Add the fiat to Order sell's Trader
            sell.getTrader().addFiat(amountInFiat, sell.getTo());
            
            //Remove the fiat from Order buy's Trader
            buy.getTrader().addFiat(-amountInFiat, buy.getTo());
            
            
        } catch (Exception e) {Error.handleError(e);}

        //Update orders' status

        if (sell.getQuantityRemaining() <= 0) {
            sell.setStatus(OrderStatus.FILLED);
            queue.remove(sell);
            sell.getTrader().removeActiveOrder(sell);
        } else sell.setStatus(OrderStatus.PARTIALLY_FILLED);

        if (buy.getQuantityRemaining() <= 0) {
            buy.setStatus(OrderStatus.FILLED);
            queue.remove(buy);
            buy.getTrader().removeActiveOrder(buy);
        } else buy.setStatus(OrderStatus.PARTIALLY_FILLED);

        

        
    }


}
