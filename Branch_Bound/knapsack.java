package Branch_Bound;
import java.util.ArrayList;
class Item {
    int weight;
    int value;
    double ratio;

    Item(int weight, int value) {
        this.weight = weight;
        this.value = value;
        this.ratio = (double)value/weight;
    }
}

class Node {
    int curSackWeight;
    int curProfit;
    double upperBound;
    Node ( int curSackWeight, int curProfit ) {
        this.curProfit = curProfit;
        this.curSackWeight = curSackWeight;
        // this.upperBound = upperBound;
    }  
    
}

public class knapsack {

    double solveKnapsack( ArrayList<Item> items, int sack ) {
        items.sort((a, b) -> Double.compare(b.ratio, a.ratio));
        int level = 0;
        Node batman = new Node(0, 0);
        while ( level < items.size() ) {
            Item currentItem = items.get(level);
            int currentWeight = batman.curSackWeight + currentItem.weight;
            // Take item at this level
            Node accept, refuse;
            if ( currentWeight <= sack ) {
                 accept = new Node(currentWeight, batman.curProfit + items.get(level).value );
            } else {
                 accept = new Node(batman.curSackWeight, batman.curProfit);
            }

            if ( level + 1 < items.size() ) {
                Item nextItem = items.get(level + 1);
                double remainingCapacity = sack - accept.curSackWeight;
                accept.upperBound = accept.curProfit + ( remainingCapacity * nextItem.ratio );
                
                refuse = new Node(batman.curSackWeight, batman.curProfit);
                remainingCapacity = sack - refuse.curSackWeight;
                refuse.upperBound = refuse.curProfit + remainingCapacity * nextItem.ratio;
            } else {
                accept.upperBound = accept.curProfit;
                refuse = new Node(batman.curSackWeight, batman.curProfit);
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

            knapsack ks = new knapsack();
            int capacity = 50;
            double maxProfit = ks.solveKnapsack(items, capacity);
            System.out.println("Maximum Profit = " + maxProfit);
    }
}