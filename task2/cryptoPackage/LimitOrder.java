package cryptoPackage;

class LimitOrder extends Order{


    protected double bidask;

    protected LimitOrder(Trader trader, OrderType type, double quantity, Crypto from, Fiat to, double bidask) {
        super(trader, type, quantity, from, to);
        this.bidask = bidask;
    }
    
    protected double getBidask(){
        return bidask;
    }
    
    




}
