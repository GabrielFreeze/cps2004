package cryptoPackage;

class MarketOrder extends Order {
    protected MarketOrder(Trader trader, OrderType type, double quantity, Crypto from, Fiat to) {
        super(trader, type, quantity, from, to);
    }
}
