package pakSource;

class LimitOrder extends Order{

    protected LimitOrder(Trader trader, OrderType type, double quantity, Coin from, Coin to) {
        super(trader, type, quantity, from, to);
    }
    
}
