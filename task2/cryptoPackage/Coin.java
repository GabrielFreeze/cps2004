package cryptoPackage;

public abstract class Coin {
    private String symbol;
    private int decimals;
    private double exchangeRate;
    private double totalSupply;
    private static int count = 0;
    private int id;

    protected Coin(String symbol, int decimals, double exchangeRate, double totalSupply) {
        id = count++; //Increments the current number of coins, and sets an id to the instance of this coin.
        this.symbol = symbol;
        this.decimals = decimals >= 0? decimals:0;
        this.exchangeRate = exchangeRate >= 0? exchangeRate:0;
        if (totalSupply > 0) this.totalSupply = (double) Math.round(totalSupply*Math.pow(10,this.decimals))/Math.pow(10,this.decimals);
        else                 this.totalSupply = -1;
    }

    public void setExchangeRate(double exchangeRate) {
        this.exchangeRate = exchangeRate;
    }
    public double getExchangeRate() {
        return exchangeRate;
    }

    public void setTotalSupply(double totalSupply) {
        this.totalSupply = totalSupply;
    }
    public double getTotalSupply() {
        return totalSupply;
    }

    public String getSymbol(){
        return symbol;
    }
    public int getId() {
        return id;
    }
    public int getDecimals() {
        return decimals;
    }


}
