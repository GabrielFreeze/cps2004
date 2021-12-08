package pakSource;

class Order {

    double quantity;    //The amount the trader is buying/selling.
    Trader trader;      //Trader who created the order.
    Coin from;          //The coin the trader is selling / The coin the trader is buying.
    Coin to;            //The coin the trader will get paid in / The coin the trader will use to buy.
    
    OrderType type;     //Buy or Ask
    OrderStatus orderStatus = OrderStatus.UNFILLED;

    protected Order(Trader trader, OrderType type, double quantity, Coin from, Coin to){
        this.quantity = quantity;
        this.trader = trader;
        this.type = type;

        this.from = from;
        this.to = to;
    }

}
