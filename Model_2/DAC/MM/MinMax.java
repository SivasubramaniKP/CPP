package Model_2.DAC.MM;


class MinMax {
    int Min;
    int Max;

    MinMax(int min, int max) {
        this.Min = min;
        this.Max = max;
    }

    static MinMax solveMinMax(int a[], int low, int high) {
            if ( high - low == 1 ) {
                if ( a[low] > a[high] ) return new MinMax(a[high], a[low]);
                else return new MinMax(a[low], a[high]);
            } 
            if ( high - low == 0 ) {
                return new MinMax(a[low],a[low]);
            } 
            int mid = (low + high) / 2;
            MinMax left = solveMinMax(a, low, mid) ;
            MinMax right = solveMinMax(a, mid + 1, high);

            int realMin, realMax;
            if(left.Max > right.Max) realMax = left.Max;
            else realMax = right.Max;
            if ( left.Min < right.Min ) realMin = left.Min;
            else realMin = right.Min;

            return new MinMax(realMin, realMax);
    } 

    public static void main(String[] args) {
        int a[] = {100,5,2,7,3,1,-3,5,30};
        System.out.println(solveMinMax(a, 0, a.length - 1).Min + " " + solveMinMax(a, 0, a.length - 1).Max);
    }
}

