package Model_2.Branch_Bound.Knapsack;

import java.util.ArrayList;

class Item {
    int id;
    int weight;
    int value;
    double ratio;

    Item( int weight, int value ) {
        this.weight = weight;
        this.value = value;
        this.ratio = (double) value/ weight;
    }
}

class Node {
    int curSackWeight;
    int curProfit;
    double upperBound;

    Node(int curSackWeight, int curProfit ) {
        this.curSackWeight = curSackWeight;
        this.curProfit = curProfit;
        // this.upperBound = upperBound;
    }
}

class KnapProblem {
       static double solveKnapsack(ArrayList<Item> items, int sack) {
            double res = 0;
            items.sort((a, b) -> Double.compare(b.ratio , a.ratio) );
            int level = 0;
            Node batman = new Node( 0, 0);
            while ( level < items.size() ) {
                Item currentItem = items.get(level);
                int currentWeight = batman.curSackWeight + currentItem.weight;
                
                Node accept, refuse;
                if ( currentWeight <= sack ) {
                    accept = new Node(currentWeight, batman.curProfit + currentItem.value);
                } else {
                    accept = new Node(batman.curSackWeight , batman.curProfit);
                }   

                if( level + 1 < items.size() ) {
                    Item nexItem = items.get(level + 1);
                    double remainingCapacity = sack - accept.curSackWeight;
                    accept.upperBound = accept.curProfit + ( remainingCapacity * nexItem.ratio );

                    refuse = new Node(batman.curSackWeight,batman.curProfit);
                    remainingCapacity = sack - refuse.curSackWeight;
                    refuse.upperBound = refuse.curProfit + remainingCapacity * nexItem.ratio;
                } else {
                    accept.upperBound = accept.curProfit;
                    refuse = new Node(batman.curSackWeight , batman.curProfit);
                    refuse.upperBound = refuse.curProfit;
                }
                if ( accept.upperBound > refuse.upperBound ) batman = accept;
                else batman = refuse;

                level += 1;
            }
            return batman.curProfit;
       } 
    public static void main(String[] args) {
            ArrayList<Item> items = new ArrayList<>();
            items.add(new Item(10, 60));
            items.add(new Item(20, 100));
            items.add(new Item(30, 120));


            int capacity = 50;
            double maxProfit = solveKnapsack(items, capacity);
            System.out.println("Maximum Profit = " + maxProfit);
    }

}
