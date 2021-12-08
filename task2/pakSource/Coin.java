package pakSource;
import java.util.ArrayList;

public abstract class Coin {
    protected String symbol;
    protected int decimals;
    protected double exchangeRate;
    protected double totalSupply;
    protected static int count = 0;
    protected int id;

    protected Coin(String symbol, int decimals, double exchangeRate, double totalSupply) {
        id = count++; //Increments the current number of coins, and sets an id to the instance of this coin.
        this.symbol = symbol;
        this.decimals = decimals;
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

    public int getId() {
        return id;
    }


}
