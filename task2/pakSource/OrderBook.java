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

        throw new Exception("Order does not exist in order book");
    }

    protected static ArrayList<Order> copyOrderBook(){
        
        ArrayList<Order> copy = new ArrayList<Order>();
        Collections.copy(copy,orderBook);

        return copy;
    }
}
