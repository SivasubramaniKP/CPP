package Final.CAT_2;

public class Knuth2 {
    static void KnuthMorrisPratt(String Haystack, String needle) {
        if ( needle.equals("") ) {
           System.out.println("There is no needle");
           return;
        }
        int [] LPS = new int[needle.length()];

        int i = 1;
        int prevLPS = 0;
        while ( i < needle.length() ) {
            if ( needle.charAt(i) == needle.charAt(prevLPS) ) {
                LPS[i] = prevLPS + 1;
                prevLPS += 1;
                i += 1;
            } else if ( prevLPS == 0 ) {
                LPS[i] = 0;
                i += 1;
            } else {
                prevLPS = LPS[prevLPS - 1];
            } 
        }
        printLPS(LPS);

        i = 0;
        int j = 0;
        while ( i < Haystack.length() ) {
            if ( needle.charAt(j) == Haystack.charAt(i) ) {
                i += 1; j += 1;
            } else {
                if ( j == 0 ) {
                    i += 1;
                } else {
                    j = LPS[j-1];
                }
            }
            if ( j == needle.length() ) {
                System.out.println("String found at " + ( i - needle.length() ) + "\n");
                j = LPS[j-1];
            }
        }
    } 
    static void printLPS(int [] a) {
        for ( int i : a ) {
            System.out.print(i + " ");
        }
    }
    public static void main(String[] args) {
        KnuthMorrisPratt("ABBABABABAABABAAB", "ABABA");
    }
}
