package Final.CAT_2;

public class Naive {
    static void StringCompare(String Haystack, String needle) {
        int n = Haystack.length();
        int m = needle.length();
        for ( int i = 0; i < n - m + 1; i++ ) {
            int j;
            for ( j = 0 ; j < m ; j++ ) {
                if ( Haystack.charAt(i+j) != needle.charAt(j) ) break;
            }
            if ( j == m ) {
                System.out.println("String found at index : " + i);
            }
        }
    } 
    public static void main(String[] args) {
        StringCompare("Sivasubramani", "Sivasu");
    }
}
