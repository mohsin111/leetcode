public class Sqrt {
    
    //O(logx) time and O(1) space
    public int mySqrt(int x) {
        if (x < 0) {
            throw new RuntimeException("The integer can't be negative!");
        }
        int low = 0;
        int high = x;
        while (low < high) {
            int mid = high - (high - low) / 2;
            int quotient = x / mid; //mid * mid could result in overflow!
            if (mid > quotient) {
                high = mid - 1;
            } else if (mid < quotient) {
                low = mid;
            } else {
                return mid;
            }
        }
        return high;
    }
}