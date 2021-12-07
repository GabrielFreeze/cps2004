package pakSource;

public abstract class Crypto {
    String symbol;
    int totalSupply;
    int decimals;
    double exchangeRate;

    public Crypto(String symbol, int totalSupply, int decimals, double exchangeRate) {
        this.symbol = symbol;
        this.totalSupply = totalSupply;
        this.decimals = decimals;
        this.exchangeRate = exchangeRate;
    }
}
