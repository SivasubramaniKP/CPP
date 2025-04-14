package Model_2.DAC.Karatsuba;
public class KaratMult {
    
    static long Karatsuba(long x, long y) {
        if ( x < 10 || y < 10 ) {
            return x * y;
        }

        int size = Math.max(Long.toString(x).length(), Long.toString(y).length());
        int m = size/2;

        long a = x / (long)Math.pow(10, m);
        long b = x % (long)Math.pow(10, m);

        long c = y /  (long)Math.pow(10, m);
        long d = y %  (long)Math.pow(10, m);

        long ac = Karatsuba(a,c);
        long db = Karatsuba(b, d);
        long sumTerm = Karatsuba((a+b), (c+d));

        return ac * (long)Math.pow(10, 2 * m) + (sumTerm - ac - db) * (long)Math.pow(10,m) + db;
    }

    public static void main(String[] args) {
        long a = 130323;
        long b = 23195;
        System.out.println(Karatsuba(a, b));
    }
}
