package pakSource;
import java.util.ArrayList;
public class Trader extends User{


    protected Boolean registered;
    protected Boolean approved;

    
    protected ArrayList<Crypto> cryptos = new ArrayList<Crypto>();        //The cryptos the trader has.
    protected ArrayList<Double> cryptosBalance = new ArrayList<Double>(); //The amounts the trader has relating to a crypto.

    protected ArrayList<Fiat> fiats = new ArrayList<Fiat>();              //The fiat the trader has.
    protected ArrayList<Double> fiatsBalance = new ArrayList<Double>();   //The amounts the trader has relating to a fiat.


    public Trader(String username, String password) {
        super(username, password);
        registered = false;
    }


    //Returns 1 if fiat already exists, 0 otherwise.
    public int addFiat(Fiat fiat) throws Exception { 
        
        assertLogin();

        for (Fiat fiat2: fiats) {
            if (fiat2 == fiat) return 1;  
        }
        
        fiats.add(fiat);
        //Initially the user has no balance with respect to the new fiat currency just added.
        fiatsBalance.add((double) 0); 
        return 0;
    }
    public void addFiat(double amount, int fiatId) throws Exception {
        //In a real world application, a bank's API will handle the transferring of cash.
        //However, just as a proof of concept, fiat currencies can simply be added regardless.
        //Checks with the bank can be made in this function.
        assertLogin();

        if (amount <= 0)
            throw new Exception("Amount given must be non-negative");
        
        //Throw exception if fiat currency relating to fiatId is not in user's fiat currencies.
        int index = -1;
        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i).id == fiatId) {
                index = i;
                break;
            }
        }
        if (index < 0)
            throw new Exception("Fiat Id relating to a fiat currency is not present in user's fiat currencies");
        
        //Increase the balance of the fiat.
        fiatsBalance.set(index, fiatsBalance.get(index)+amount);

    

    }

    public double getBalance(int coinId) throws Exception{
        
        assertLogin();

        //Check for the id in fiats
        for (int i = 0; i < fiats.size(); i++) {
            if (fiats.get(i).getId() == coinId) return fiatsBalance.get(i);
        }
        
        //Check for the id in cryptos
        for (int i = 0; i < cryptos.size(); i++) {
            if (cryptos.get(i).getId() == coinId) return cryptosBalance.get(i);
        }

        //If the id is not found in either than the user did not add that coin.
        return -1;

    }

    public void buy(double amount, Crypto crpto, int coinIndex) throws Exception {
        assertLogin();
        //amount: How much will the user buy of crypto
        //crypto: The coin which the user will be buying
        //coinIndex: What currency will he use to buy crypto.

    }

    public Boolean getRegistered() throws Exception {
        assertLogin();
        return registered;
    }
    public void setRegistered(Boolean registered) throws Exception {
        assertLogin();
        this.registered = registered;
    }
    
    public Boolean getApproved() throws Exception {
        assertLogin();
        return approved;
    }
    public void setApproved(Boolean approved, Admin admin) throws Exception {
        assertLogin();

        if (!registered)
            throw new Exception("Trader is not registered");
        if (admin.getTraderToApprove() != this)
            throw new Exception("Admin passed to setApproved must reference Trader to approve in traderToApprove in Admin");
        
        this.approved = approved;
        

    }

}
