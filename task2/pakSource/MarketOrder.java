package pakSource;

class MarketOrder extends Order {
    protected MarketOrder(Trader trader, OrderType type, double quantity, Coin from, Coin to) {
        super(trader, type, quantity, from, to);
    }
}
