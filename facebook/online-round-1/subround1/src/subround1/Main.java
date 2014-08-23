/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package subround1;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author gabriel
 */
public class Main {

    static Scanner input;

    static boolean debug = false;

    public static void main(String[] args) throws IOException {
        input = new Scanner(new File(args[0]));
        int tests = input.nextInt();

        for(int j = 0; j < tests; ++j) {
          int G = input.nextInt();
          int W = input.nextInt();
          double M = input.nextLong();
          
          long maxG = (long) Math.floor(M/G);
          long medium = (long) Math.floor(maxG/2);
          long bound = (long) Math.floor(maxG * 0.3);
          long min = medium - bound;
          if(min < 0) min = 0;
          long max = medium + bound;

          double maxDamage = -1;
          double maxI = 0;
          double i = 0;

          if(debug) System.out.print(min + ":" + max + " ");
          for(i = 1; i <= maxG; i++) {
              double moneyLeft = M - G * i;
              double damage = Math.floor(moneyLeft / W) * i;
              if(maxDamage < damage) {
                  maxDamage = damage;
                  maxI = i;
              } /*else {
                  break;
              }*/
              //System.out.println((long) damage);
          }
          System.out.print((long) maxDamage);
          if(!debug) System.out.println("");
          if(debug) System.out.print("\t" + (long) maxI + "/" + (long) maxG);
          if(debug) System.out.println("\t" +  Math.round(maxI / maxG*100));
        }
        return;
    }

}
