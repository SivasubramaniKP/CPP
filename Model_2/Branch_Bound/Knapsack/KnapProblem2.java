package Model_2.Branch_Bound.Knapsack;
import java.util.*;

class Item {
    int weight;
    int value;
    double ratio;

    Item(int weight, int value ) {
        this.weight = weight;
        this.value = value; 
        this.ratio = (double) value/weight; 
    }
}


class Node {
    int curWeight;
    int curProfit;
    double upperBound;
    
    Node (int curWeight, int curProfit) {
        this.curWeight = curWeight; 
        this.curProfit = curProfit;
    }
}
public class KnapProblem2 {
    
    ArrayList<Item> List;
    int nItems;
    int sackSize;
    Scanner sc = new Scanner(System.in);
    KnapProblem2(int nItems, int sackSize) {
        this.nItems = nItems;
        this.sackSize = sackSize;
        List = new ArrayList<>();
        List.add(new Item(0, 0));
        List.get(0).ratio = 0;
        for( int i = 0; i < nItems; i++ ) {
            int value = sc.nextInt();
            int weight = sc.nextInt();
            List.add(new Item(weight, value));
        }
        List.sort((a, b) -> Double.compare(b.ratio, a.ratio));
    }

    void calcUpperBound(int level, Node node) {
        node.upperBound =  node.curProfit + ( sackSize - node.curWeight ) * List.get(level).ratio;
    } 


    void solveKnapsack() {
        Node batman = new Node(0, 0);
        calcUpperBound(0, batman);
        int curLevel = 0;
        while ( curLevel < nItems ) {
            // Now we have to select the item at curLevel index
            // or leave it
            Item curItem = List.get(curLevel);
            Node accept, refuse;
            if(batman.curWeight + curItem.weight < sackSize) {
                accept = new Node(batman.curWeight + curItem.weight, batman.curProfit + curItem.value);
                refuse = new Node(batman.curWeight, batman.curProfit);
                calcUpperBound(curLevel + 1, accept); calcUpperBound(curLevel + 1, refuse);
                if ( accept.upperBound > refuse.upperBound ) {batman = accept;
                    System.out.println("Selected item " + curItem.ratio);
                }
                else batman = refuse;
            } else {
                calcUpperBound(curLevel + 1, batman);
            }
            curLevel += 1; 
        }
        System.out.println(batman.curProfit);
    }

    public static void main(String[] args) {
        KnapProblem2 kp = new KnapProblem2(4, 10);
        kp.solveKnapsack();
    }
}
