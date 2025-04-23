package Final.CAT_2;

class Knuth {
    static void KnuthMorrisPratt(String Haystack, String needle) {
        if ( needle.equals("") ) {
            System.out.println("There is no Needle");
        }
        int[] LPS = new int[needle.length()];

        int prevLPS = 0, i = 1;
        while ( i < needle.length() ) {
            if ( needle.charAt(i) == needle.charAt(prevLPS) ) {
                prevLPS += 1;
                LPS[i] = prevLPS; 
                i += 1;
            } else if ( prevLPS == 0  ){
                LPS[i] = 0;
                i += 1;
            } else {
                prevLPS = LPS[prevLPS - 1];
            } 
        }
        i = 0;
        int j = 0;
        int found = 0;
        while ( i < Haystack.length() ) {
            if ( Haystack.charAt(i) == needle.charAt(j) ) {
                i = i + 1;
                j = j + 1;
            } else {
                if ( j == 0 ) {
                    i += 1;
                } else {
                    j = LPS[j - 1];
                }
            }
            if ( j == needle.length() ) {
                System.out.println("String found at : " + ( i - needle.length()) + "\n");
                found = 1;
            }
        } 
        if ( found == 0 ) System.out.println("String not found");
    }
    public static void main(String[] args) {
        KnuthMorrisPratt("Sivasu", "AABABAABABBBA");        
    }
}