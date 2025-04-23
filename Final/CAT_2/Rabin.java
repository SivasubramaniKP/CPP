package Final.CAT_2;

public class Rabin {
        static void search(String text, String pattern) {
        int m = pattern.length();
        int n = text.length();
        int d = 256; // base for ASCII

        if (m > n) {
            System.out.println("Pattern is longer than text.");
            return;
        }

        // Calculate initial hash for pattern and first window
        int patternHash = 0;
        int windowHash = 0;

        for (int i = 0; i < m; i++) {
            patternHash = patternHash * d + pattern.charAt(i);
            windowHash = windowHash * d + text.charAt(i);
        }

        // Check first window
        if (patternHash == windowHash && text.substring(0, m).equals(pattern)) {
            System.out.println("Pattern found at index 0");
        }

        // Slide the window
        for (int i = 1; i <= n - m; i++) {
            // Remove leading character and add new trailing character
            windowHash = windowHash - text.charAt(i - 1) * (int)Math.pow(d, m - 1);
            windowHash = windowHash * d + text.charAt(i + m - 1);

            // Compare hash and then verify characters
            if (windowHash == patternHash && text.substring(i, i + m).equals(pattern)) {
                System.out.println("Pattern found at index " + i);
            }
        }
    }

    public static void main(String[] args) {
        search("ABCCDDAEFG", "CDD");
    }
}
