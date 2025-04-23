package Final;

import java.util.HashSet;
import java.util.Scanner;

class Node {
    int UpperBound;
    int person;
    int job;
    Node next;
    Node( int person, int job ) {
        this.person = person;
        this.job = job;
        next = null;
    }
    public String toString() {
        return person + " is assigned the job of " + job;
    }
}

public class Assignment {
    int Matrix [][];
    int nPerson;
    int nJob;
    HashSet<Integer> assigned;
    Scanner sc = new Scanner(System.in);
    Assignment(int nPerson, int nJob) {
        Matrix = new int[nPerson][nJob];
        assigned = new HashSet<>();
        this.nPerson = nPerson;
        this.nJob = nJob;
        for ( int i = 0 ; i < nPerson; i++ ) {
            for ( int j = 0 ; j < nJob; j++ ) {
                Matrix[i][j] = sc.nextInt(); 
            }
        }
    }

    
    void calcUpperBound(Node node, int i, int j) {
        int UB = Matrix[i][j];
        assigned.add(j);
        for ( int person = i + 1; person < nPerson; person++ ) {
            int minCost = Integer.MAX_VALUE;
            for ( int job = 0; job < nJob; job++ ) {
                if ( assigned.contains(job)) continue;
                minCost = Math.min(minCost, Matrix[person][job]);
            }
            UB += minCost;
        }
        assigned.remove(j);
        node.UpperBound = UB;
    }

    void SolveAssignment() {
        Node batman = new Node(-1, -1);
        Node cur = batman;
        int level = 0;
        int cost = 0;
        while ( level < nPerson ) {
            int minUpperBound = Integer.MAX_VALUE;
            Node minNode = null;
            for ( int i = 0 ; i < nJob; i++ ) {
                if ( assigned.contains(i) ) continue;
                Node tempAssignment = new Node(level, i);
                calcUpperBound(tempAssignment, level, i);  
                if ( tempAssignment.UpperBound < minUpperBound ) {
                    minUpperBound = tempAssignment.UpperBound;
                    minNode = tempAssignment;
                }
            }
            cur.next = minNode;
            cur = minNode ;
            cost += Matrix[minNode.person][minNode.job];
            assigned.add(minNode.job);
            level += 1;
        }

        System.out.println("COST : " + cost);
        for (Node temp = batman.next; temp != null; temp = temp.next) {
            System.out.println(temp);
        }
    }

    public static void main(String[] args) {
        Assignment as = new Assignment(4,4);
        as.SolveAssignment();
    }
    
}
