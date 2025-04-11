import java.util.ArrayList;
import java.util.Scanner;

class DPTable {
    ArrayList<Integer> DP;
    ArrayList<Integer> CoinUsed;

    DPTable(int cols) {
        this.DP = new ArrayList<>(cols + 1);
        this.CoinUsed = new ArrayList<>(cols + 1);
        for ( int i = 0; i <= cols; i++ ) {
            DP.add(Integer.MAX_VALUE);
            CoinUsed.add(-1);
        }
        DP.set(0, 0);
    }
    void printTable() {
        for ( int i = 0 ; i < DP.size(); i++ ) {
            System.out.print(DP.get(i) + "  ");
        }
        System.out.println("\n");
    }    
     void printCoinsUsed(int target) {
        if (DP.get(target) == Integer.MAX_VALUE) {
            System.out.println("No solution possible");
            return;
        }

        System.out.print("Coins used: ");
        while (target > 0) {
            int coin = CoinUsed.get(target);
            System.out.print(coin + " ");
            target -= coin;
        }
        System.out.println();
    }
}
public class coinChange {
    ArrayList<Integer> Denomination;
    int targetAmount;
    Scanner sc;
   coinChange(int nD, int targetAmount) {
        Denomination = new ArrayList<>(nD);
        sc = new Scanner(System.in);
        for ( int i = 0 ; i < nD; i++ ) {
            int temp = sc.nextInt();
            Denomination.add(temp);
        }
        this.targetAmount = targetAmount;
        sc.close();
   } 

   void SolveCoinChange() { 
        DPTable dptable = new DPTable(targetAmount);
        for ( int i = 0; i < Denomination.size(); i++ ) {
            int curDenomination = Denomination.get(i);
            for ( int j = 1 ; j <= targetAmount; j++ ) {
                if ( j - curDenomination >= 0 ) {
                    int currentValue = Math.min(dptable.DP.get(j), 1 + dptable.DP.get(j - curDenomination));
                    dptable.DP.set(j, currentValue);
                    dptable.CoinUsed.set(j, curDenomination);
                }
            }
        }
        dptable.printTable();
        dptable.printCoinsUsed(targetAmount);
    }

    public static void main(String[] args) {
        coinChange temp = new coinChange(5, 16);
        temp.SolveCoinChange();
    }
}
