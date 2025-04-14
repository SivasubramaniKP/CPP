package Model_2.Branch_Bound.AP;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

class Node {
    int upperBound;
    String mapping;
    int job;
    int person;
    Node next;
    Node( String mapping ) {
        this.mapping = mapping;
    }
    Node ( String mapping, int person, int job ) {
        this.mapping = mapping;
        this.job = job;
        this.person = person;
    }  

}

class Assignment {
    int [][] Matrix;
    int nPerson;
    int nJobs;
    HashSet<Integer> assignedJobs;
    Scanner sc;
    Assignment(int nPerson, int nJobs) {
        sc = new Scanner(System.in);
        this.nJobs = nJobs;
        this.nPerson = nPerson;
        assignedJobs = new HashSet<>();
        Matrix = new int[nPerson][nJobs];
        for ( int i =0 ; i < nPerson; i++) {
            for( int j = 0 ; j < nJobs; j++ ) {
                Matrix[i][j] = sc.nextInt();
            }
        }  
    }

    void updateUpperBound(Node node,int i, int j, int level) {
        int cur = Matrix[i][j];
        for ( int person = i + 1; person < nPerson; person++ ) {
            int rowMin = Integer.MAX_VALUE;
            for( int job = 0 ; job < nJobs; job++ ) {
                if ( assignedJobs.contains(job) ) continue;
                rowMin = Math.min(rowMin, Matrix[i][j]); 
            }
            cur += rowMin;
        } 
        node.upperBound = cur;
    }

    void solveAssignment() {
        Node parent = new Node(null);
        int level = 0;
        ArrayList<String> result = new ArrayList<>();
        int cost = 0;
        Node cur = parent;
        while ( level < nPerson ) {
            // ArrayList<Node> levelList = new ArrayList<>();
            
            int minUpperBound = Integer.MAX_VALUE;
            Node minNode = null;
            for( int i = 0; i < nJobs; i++ ) {
                if ( assignedJobs.contains(i) ) continue;
                String mapping = level + ":" + i;
                Node temp = new Node(mapping, level, i);
                // levelList.add(temp);
                updateUpperBound(temp,level, i, level); 
                if(temp.upperBound < minUpperBound) {
                    minUpperBound = temp.upperBound;
                    minNode = temp;
                }
            }
            if ( minNode != null ) {
                assignedJobs.add(minNode.job);
                cur.next = minNode;
                cur = cur.next;
                result.add(minNode.mapping);
                cost += Matrix[minNode.person][minNode.job];
            } 
            level += 1;
        }  
        System.out.println("\nOptimal Assignment:");
        for (String map : result) {
            System.out.println("Person " + map);
        }
        System.out.println("Total Cost: " + cost);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of persons/jobs: ");
        int n = sc.nextInt();

        Assignment a = new Assignment(n, n);
        a.solveAssignment();
    }
}



