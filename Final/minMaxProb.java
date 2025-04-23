package Final;

class MinMax {
    int min;
    int max;
    MinMax(int min, int max) {
        this.min = min;
        this.max = max;
    }
}

public class minMaxProb {
    static MinMax solveMinMax(int a[], int low, int high) {
        if ( low == high ) {
            return new MinMax(a[low], a[low]);
        }
        if ( high - low == 1 ) {
            if ( a[low] > a[high] ) return new MinMax(a[high], a[low]);
            else return new MinMax(a[low], a[high]);
        }
        int mid = (low + high)/2;
        MinMax left = solveMinMax(a, low, mid);
        MinMax right = solveMinMax(a, mid + 1, high);
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        if ( left.max > right.max ) max = left.max;
        else max = right.max;
        if ( left.min < right.min ) min = left.min;
        else min = right.min;
        return new MinMax(min, max);
    }
    public static void main(String[] args) {
        int a[] = {5,3,2,6,2,103,5,3,6, -354,2,4,-3414,3};
        System.out.println(solveMinMax(a, 0, a.length-1).min + " " +solveMinMax(a, 0, a.length - 1).max);
    }
}
