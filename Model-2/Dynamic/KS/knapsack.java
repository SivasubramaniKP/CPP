package KS;

import java.util.ArrayList;
import java.util.Scanner;

class Item {
    int weight;
    int value;
    Item(int weight, int value) {
        this.value = value;
        this.weight = weight;
    }
}

public class knapsack {
    int capacity;
    ArrayList<Item> itemList;
    int [][] DP;
    Scanner sc;
    int nItems;
    static void printMatrix(int [][] Matrix, int I, int J) {
        for ( int i = 0; i <= I ; i++ ) {
            for ( int j = 0 ; j <= J; j++ ) {
                System.out.print(Matrix[i][j] + " ");
            }    
            System.out.println();
        }
    }
    knapsack() {
        itemList = new ArrayList<>();
        sc = new Scanner(System.in);
        capacity = sc.nextInt();
        int nItems = sc.nextInt();
        this.nItems = nItems;
        itemList.add(new Item(0, 0));
        for ( int i = 0 ; i < nItems; i++ ) {
            int w = sc.nextInt();
            int v = sc.nextInt();
            itemList.add(new Item(w, v));
        }
        DP = new int[nItems + 1][capacity + 1];
        for( int i = 0 ; i <= capacity; i++ ) {
            DP[0][i] = 0;
        }
        for ( int i = 0; i <= nItems; i++ ) {
            DP[i][0] = 0;
        }
    }

    void SolveKnapsack() {
        for ( int i = 1; i <= nItems; i++) {
            for ( int j = 1; j <= capacity; j++ ) {
                if ( j - itemList.get(i).weight < 0 ) {
                    DP[i][j] = DP[i-1][j];
                } else {
                    DP[i][j] = Math.max(DP[i-1][j], itemList.get(i).value + DP[i-1][j-itemList.get(i).weight]);
                }
            }
        }
        printMatrix(DP, nItems, capacity);

        int i = nItems;
        int j = capacity;
        ArrayList<Item> itemsAdded = new ArrayList<>();
        while ( i > 0 && j > 0 ) {
            if ( DP[i][j] != DP[i-1][j] ) {
                itemsAdded.add(itemList.get(i));
                j -= itemList.get(i).weight;
            }
            i -= 1;
        }

        for ( Item ti : itemsAdded ) {
            System.out.println(ti.value);
        }
    }


    public static void main(String[] args) {
        knapsack kp = new knapsack();
        kp.SolveKnapsack();
    }

}
