package pakSource;
import java.util.Comparator;
import java.util.PriorityQueue;

public class MatchingEngine {

    private static Comparator<Order> orderComparator = new Comparator<Order>() {
        public int compare(Order a, Order b) {
            return (int) (a.getQuantity() - b.getQuantity());
        }
    };


    private static PriorityQueue<Order> queue = new PriorityQueue<Order>(orderComparator);

    protected static void add(Order order) {
        queue.add(order);
    }
    protected static void remove(Order order) {
        queue.remove(order);
    }

    public static void printQueue() {
        System.out.println("Matching Engine Order Queue: " + queue);
    }

    public static Boolean limitOrderReady(LimitOrder order) {
       
        if (order.getType() == OrderType.BUY) //Returns true if the price of FROM is less than the bid price. 
            return order.getFrom().getExchangeRate() <= order.getBidask();

        else                                  //Returns true if the price of FROM is more than the ask price. 
            return order.getFrom().getExchangeRate() >= order.getBidask();
    }


    public static int update() {
        //For every order, traverse down the queue and find any matching order

        for (Order o : queue) {

            for (Order p : queue) {
                
                //Preliminary plumbing
                if (o instanceof LimitOrder && !limitOrderReady((LimitOrder) o) ||
                    p instanceof LimitOrder && !limitOrderReady((LimitOrder) p)) continue;

                if (o == p                          ||
                    p.getType() == o.getType()      ||
                    p.getTrader() == o.getTrader()  ||
                    p.getFrom() != o.getFrom()      ||
                    p.getTo() != o.getTo())         continue;

                    
                //If p did not go into the if statement, then it is a valid match for o.

                if (o.getType() == OrderType.BUY && p.getType() == OrderType.SELL) {
                    matchOrders(o, p);
                }
                else {
                    matchOrders(p, o);
                }
                    
            }
        }
        
        return 0;
    }


    private static void matchOrders(Order buy, Order sell) {
        
        //Mention which traders fulfilled orders buy and sell.
        buy.addMatchedTrader(sell.getTrader());
        sell.addMatchedTrader(buy.getTrader());
        

        //Calculate how much FIAT does the CRYPTO cost.
        //First exchanges it into price in euros, then exchanges it into price in FROM.
        double amountInFiat = buy.getQuantityRemaining() * sell.getFrom().getExchangeRate() * sell.getTo().getExchangeRate();
        
        try {
            
            //Subtract the crypto that just got sold from Order sell's trader.
            sell.getTrader().addCrypto(-buy.getQuantityRemaining(), sell.getFrom());

            //Add the crypto to Order buy's Trader
            buy.getTrader().addCrypto(buy.getQuantityRemaining(), sell.getFrom());

            //Add the fiat to Order sell's Trader
            sell.getTrader().addFiat(amountInFiat, sell.getTo());

            //Remove the fiat from Order buy's Trader
            buy.getTrader().addFiat(-amountInFiat, buy.getTo());
            
            //Update the order's remaining quantity
            double buyQuantity = buy.getQuantityRemaining();
            double sellQuantity = sell.getQuantityRemaining();
            
            buy.setQuantityRemaining(buyQuantity-sellQuantity);
            sell.setQuantityRemaining(sellQuantity-buyQuantity);

        } catch (Exception e) {Error.handleError(e);}

        //Update orders' status

        if (sell.getQuantityRemaining() <= 0) {
            sell.setStatus(OrderStatus.FILLED);
            queue.remove(sell);
        } else sell.setStatus(OrderStatus.PARTIALLY_FILLED);

        if (buy.getQuantityRemaining() <= 0) {
            buy.setStatus(OrderStatus.FILLED);
            queue.remove(buy);
        } else buy.setStatus(OrderStatus.PARTIALLY_FILLED);

        

        
    }


}
