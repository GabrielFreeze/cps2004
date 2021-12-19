package cryptoPackage;
import java.util.ArrayList;
import java.util.Collections;

public class OrderBook {
    protected ArrayList<Order> orderBook = new ArrayList<Order>();
    public static OrderBook instance = null;

    private OrderBook() {}

    public static OrderBook getInstance() {
        if (instance == null) instance = new OrderBook();
        return instance;

    }

    protected int pushOrder(Order order) {
        orderBook.add(order);
        return orderBook.size()-1; //Returns the index of the newly added element
    }

    protected int getOrderIndex(Order order) throws Exception{
        
        for (int i = 0; i < orderBook.size(); i++) {
            if (orderBook.get(i) == order) return i;
        }

        throw new Exception("Order " + order + " does not exist in order book.");
    }

    protected ArrayList<Order> copyOrderBook() {
        
        ArrayList<Order> copy = new ArrayList<Order>();
        Collections.copy(copy,orderBook);

        return copy;
    }

    public void printOrderBook() {

        System.out.println("\n\nORDER BOOK:");

        System.out.println("\n\nID\tTRADER\tTYPE\tPAIR\tQUANTITY\tVOL EXEC'D\tSTATUS");
        System.out.println("--------------------------------------------------------------------------------");
        
        for (int i = orderBook.size()-1 ; i >= 0; i--) {
            Order o = orderBook.get(i);
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

    public Order getOrder(int orderID) {
        for (Order o : orderBook) {
            if (o.getId() == orderID)
                return o;
        }

        return null;
    }

}
