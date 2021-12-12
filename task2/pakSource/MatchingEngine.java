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

    public static void printQueue() {
        System.out.println("Matching Engine Order Queue: " + queue);
    }

    public static int update() {
        //For every order, traverse down the queue and find any matching order

        for (Order o : queue) {

            for (Order p : queue) {
                //Preliminary plumbing
                if (o == p                          ||
                    p.getType() == o.getType()      ||
                    p.getTrader() == o.getTrader()  ||
                    p.getFrom() != o.getFrom()      ||
                    p.getTo() != o.getTo())         continue;

                //If p did not go into the if statement, then it is a valid match for o.
                
                //o is Buying
                //p is Selling

                //p can be fulfilled, o can be partially filled
                if (o.getQuantity() > p.getQuantity()) {
                    //Mention which traders fulfilled orders o and p.
                    o.addMatchedTrader(p.getTrader());
                    p.addMatchedTrader(o.getTrader());
                    

                    //Subtract the crypto that just got sold from Order p's trader.
                    try { p.getTrader().addCrypto(-p.getQuantity(), p.getFrom());
                    } catch (Exception e) {Error.handleError(e);}

                    //TODO: COMPLETE THIS
                    //Need to calculate the price in fiat for the crypto that got bought
                    //With exchange values or some bullshit yknow
                    //Then add the calculated amount of fiat into order p's trader
                    //Subtract the calculated amount of fiat from order o's trader
                    //Add p.getQuantity() amount of crpyto into order o's wallet
                    //Set p to be fulfilled and o to eb partially filled
                    //Remove p from the queue

                    
                }
                

            }
        }
        
        return 0;
    }
}
