package Final.CAT_1;

class interpolation {
    static int Search(int a[], int target) {
        int low = 0;
        int high = a.length - 1;
        while ( low <= high && target >= a[low] && target <= a[high] ) {
            if ( low == high ) {
                return ( a[low] == target ) ? low : -1;
            }
            int pos = low + ( (target - a[low])* ( ( high - low )/( a[high] - a[low] ) ) );
            if ( a[pos] == target ) return pos;
            if ( a[pos] < target ) low = pos + 1;
            else high = pos - 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        System.out.println(" \n\n\n"+Search(new int[]{1,4,6,7,10, 12}, 12
        ));
    }
}