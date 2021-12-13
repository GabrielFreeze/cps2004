package pakSource;
import java.util.ArrayList;
import java.util.Collections;

public class OrderBook {
    protected static ArrayList<Order> orderBook = new ArrayList<Order>();

    protected static int pushOrder(Order order) {
        orderBook.add(order);
        return orderBook.size()-1; //Returns the index of the newly added element
    }

    protected static int getOrderIndex(Order order) throws Exception{
        
        for (int i = 0; i < orderBook.size(); i++) {
            if (orderBook.get(i) == order) return i;
        }

        throw new Exception("Order " + order + " does not exist in order book.");
    }

    protected static ArrayList<Order> copyOrderBook() {
        
        ArrayList<Order> copy = new ArrayList<Order>();
        Collections.copy(copy,orderBook);

        return copy;
    }

    public static void printOrderBook() {

        System.out.println("\n\nID\tTRADER\tTYPE\tPAIR\tQUANTITY\tSTATUS");
        System.out.println("------------------------------------------------------");
        
        for (int i = orderBook.size()-1 ; i >= 0; i--) {
            Order o = orderBook.get(i);
            System.out.println(
                o.getId()+"\t"+
                o.getTrader().getUsername()+"\t"+
                o.getType()+"\t"+
                o.getFrom().getSymbol()+"/"+o.getTo().getSymbol()+"\t"+
                o.getQuantity()+"\t\t"+
                o.getStatus());
        }
    }
}
