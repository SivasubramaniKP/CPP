package Final.CAT_2;

public class Rabin2 {
    static void RabinKarp(String Haystack, String needle) {
        int m = needle.length();
        int n = Haystack.length();
        int d = 256;
        
        long patternHash = 0;
        long windowHash = 0;

        for ( int i =0 ; i < m; i++ ) {
            patternHash = patternHash * d + needle.charAt(i);
            windowHash = windowHash * d + Haystack.charAt(i);
        }

        if ( patternHash == windowHash ) {
            System.out.println("String found at index 0");
        }
        for ( int i = 1; i <= n - m; i++ ) {
            windowHash = windowHash - Haystack.charAt(i-1) * (int)Math.pow(d, m - 1);
            windowHash = windowHash * d + Haystack.charAt(i + m - 1);

            if ( windowHash == patternHash ) {
                System.out.println("String found at index : " + i);
            }
        }

    } 
    public static void main(String[] args) {
        RabinKarp("Sivasu", "vasu");
    }
}
