package Final;

import java.io.File;
import java.io.PrintWriter;
import java.util.*;

class generateRandom {
    public static void main(String[] args) throws Exception {
        PrintWriter pw = new PrintWriter(new File("./number.txt"));
        Random random = new Random();
        for( int i = 0; i < 100; i++ ) {
            int x = random.nextInt(); 
            pw.println(Integer.toString(x));
        }
        pw.close();
    }
}