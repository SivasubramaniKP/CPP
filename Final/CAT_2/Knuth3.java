package Final.CAT_2;

public class Knuth3 {
    static void KnuthMorrisPratt(String T, String P) {
        if ( P.length() == 0 ) {
            System.out.println("No needle");
            return;
        }
        int [] LPS = new int[P.length()];
        int prevLPS =0 ;   
        int i = 1;
        while ( i < P.length() ) {
            if ( P.charAt(i) == P.charAt(prevLPS) ) {
                LPS[i] = prevLPS + 1;
                prevLPS += 1;
                i ++;
            } else if ( prevLPS == 0 ) {
                LPS[i] = 0;
                i += 1;
            } else {
                prevLPS = LPS[prevLPS - 1];
            }
        }
        i = 0;
        int j = 0;
        while ( i < T.length() ) {
            if ( P.charAt(j) == T.charAt(i) ) {
                i += 1; j += 1;
            } else {
                if ( j == 0 ) {
                    i += 1;
                } else {
                    j = LPS[j - 1];
                }
            }
            if ( j == P.length() ) {
                System.out.println("String found at pos  : " +  ( i - P.length()));
                j = LPS[j-1];
            }
        }
    } 
    public static void main(String[] args) {
        KnuthMorrisPratt("Sivasu", "vasu");
    }
}
