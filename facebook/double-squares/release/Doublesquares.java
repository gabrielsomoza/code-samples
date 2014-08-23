package doublesquares;
/**
 * @author gabriel
 */

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class Doublesquares {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(new File(args[0]));
        long count = in.nextLong();
        long n;
        for(int i = 1; i <= count; i++) {
            n = in.nextLong();
            System.out.print(getDoubleSquares(n) + "\n");
        }
        return;
    }

    private static long getDoubleSquares(long number) {
        if(number <= 2) return 1;
        long combinations = 0;

        long hi = closestSquare(number);
        long low;
        long max = (long) Math.sqrt(hi);
        long min = (long) Math.ceil(max / 2);

        ArrayList<Number> used = new ArrayList<Number>();

        if(hi == number) {
            combinations++;
            used.add((long) Math.sqrt(hi));
            used.add(0);
            max--;
        }

        for(long i = max; i >= min; i--) {
            if(!used.contains(i)) {
                hi = i*i;
                low = number - hi;
                if(perfectSquare(low)) {
                    combinations++;
                    used.add(i);
                    used.add((long) Math.sqrt(low));
                }
            }
        }
        return combinations;
    }

    private static boolean perfectSquare(long number) {
        if(number <= 1) return true;
        double d = Math.sqrt(number);
        long p = (long) d;
        return (d*d) == (p*p);
    }

    private static long closestSquare(long number, boolean allowSelf) {
        if(number <= 1)
            return number;

        long cs = (long) Math.pow(Math.floor(Math.sqrt(number)), 2);
        if(!allowSelf && cs == number)
            cs = closestSquare(number - 1);
        return cs;
    }

    private static long closestSquare(long number) {
        return closestSquare(number, true);
    }

}
