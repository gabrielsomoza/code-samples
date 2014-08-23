/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package peggame;

import java.io.File;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author gabriel
 */
class Peggle {

    public int _x, _y;
    public int _state;
    boolean _exists;
    public static int goRight = 0;
    public static int goLeft = -2;
    
    public boolean _left, _right, _down;
    public double _probability = 0;

    Peggle(int x, int y) {
        this._x = x;
        this._y = y;
        this._state = 0;
        this._exists = !Main.peggles[x][y];

        if(!this.canLeadToGoal()) {
            this._state = 2;
            return;
        }

        if(this.goDown() <= Main.r - 1) {
            if(this.canGoLeft() && Peggle.canLeadToGoal(this.goLeft(), this.goDown(), this._exists))
                this._left = true;
            else
                this._state = 1;
            if(this.canGoRight() && Peggle.canLeadToGoal(this.goRight(), this.goDown(), this._exists))
                this._right = true;
        }
    }

    public Peggle getNext() {
        int x = 0, y = 0;
        if (!this._exists) {
            if(this._state == 2) return null;
            this._state = 2; //traversed completely.
            y = this._y + 2; //fall _down two levels
            x = this._x;     //to the same x position
        } else {
            y = this._y + 1;
            switch(this._state) {
                case 0:
                    this._state = 1;
                    if(this._left && this.canGoLeft())
                        x = this.goLeft();
                    else
                        return this.getNext();
                    break;
                case 1:
                    this._state = 2;
                    if(this.canGoRight() && this._right)
                        x = this.goRight();
                    else
                        return null;
                    break;
                case 2:
                    return null;
            }
        }
        if(y > Main.r - 1) return null;
        if(x > rowLength(y) - 1 || x < 0) return null;
        Peggle next = new Peggle(x, y);
        if(next.canLeadToGoal())
            return next;
        else
            return this.getNext();
    }

    public final int goLeft() {
        return this._x + (this._y % 2 == 0 ? -1 : 0);
    }

    public final int goRight() {
        return this._x + (this._y % 2 == 0 ? 0 : 1);
    }

    public final int goDown() {
        return this._y + (this._exists ? 1 : 2);
    }

    public static int rowLength(int y) {
        return y % 2 == 0 ? Main.c : Main.c - 1;
    }

    public int rowLength() {
        return rowLength(this._y);
    }

    public double value() {
        double value = 0;
        if(!this._exists || !this.canGoLeft() || !this.canGoRight())
            value = 1;
        else
            value = 0.5;
        return value;
    }

    public final boolean canGoLeft() {
        return this._exists && (this._y % 2 == 1 || this._x > 0);
    }

    public final boolean canGoRight() {
        return this._exists && (this._y % 2 == 1 || this._x < this.rowLength() - 1);
    }

    /**
     * Checks if the peggle is immediately at reach of the goal. Also covers
     * all cases of non-existent ("virtual") peggles as last nodes before the
     * goal.
     * 
     * @return
     */
    public boolean goalAtReach() {
        boolean columnAtReach = this._exists ? (this._x == Main.k || this._x - 1 == Main.k) : this._x == Main.k;
        boolean rowAtReach = (this._exists && this._y == Main.r - 1) || (!this._exists && this._y + 2 > Main.r - 1);
        return columnAtReach && rowAtReach;
    }

    public boolean canLeadToGoal() {
        return Peggle.canLeadToGoal(this);
    }

    public static boolean canLeadToGoal(Peggle peggle) {
        return Peggle.canLeadToGoal(peggle._x, peggle._y, peggle._exists);
    }

    public static boolean canLeadToGoal(int x, int y, boolean exists) {
        int new_y = exists ? y : y + 2;
        int distanceToBottom = Main.r - new_y;
        return Math.abs(x - Main.k) <= distanceToBottom;
    }
}

public class Main {

    static Scanner in;
    static boolean debug = true;
    public static int r, c, k, m;
    public static boolean[][] peggles;
    static double[] routes;
    static DecimalFormat df = new DecimalFormat("0.000000");

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        in = new Scanner(new File(args[0]));
        int tests = in.nextInt();
        for (int i = 0; i < tests; ++i) {
            predict();
        }
        return;
    }

    private static void predict() {
        int ri, ci;

        r = in.nextInt();
        c = in.nextInt();
        k = in.nextInt();
        m = in.nextInt();

        peggles = new boolean[c][r];
        routes = new double[c - 1];

        if (debug) {
            System.out.print("************************************\n");
            System.out.print("Rows: " + r + "\tColumns: " + c + "\n");
        }

        for (int i = 0; i < m; ++i) {
            ri = in.nextInt();
            ci = in.nextInt();
            peggles[ci][ri] = true;
        }
        if (debug) {
            draw();
        }

        /* Calculate */
        Peggle current, next;
        int last = 0;
        ArrayList<Peggle> queue = new ArrayList<Peggle>(); //for traversal
        for (int route = 0; route < c - 1; ++route) {
            if(Math.abs(route - Main.k) <= Main.r) {
                if(Main.debug) System.out.print(route + "-");
                Peggle new_node = new Peggle(route, 1);
                new_node._probability = new_node.value();
                queue.add(new_node);
                while (!queue.isEmpty()) {
                    last = queue.size() - 1;
                    current = queue.get(last); //get last node from queue
                    next = current.getNext();
                    if(next == null) {
                        if(current.goalAtReach())
                            //routes[route] += calculateProbability(queue);
                            routes[route] += current._probability;
                        queue.remove(last);
                    } else {
                        next._probability = current._probability * current.value();
                        queue.add(next);
                    }
                }
            }
        }

        int route = 0;
        double best = 0;
        for(int i = 0; i < routes.length; ++i) {
            if(best < routes[i]) {
                best = routes[i];
                route = i;
            }
            if(best == 1) break;
        }
        System.out.print(route + " " + df.format(best) + "\n");
    }

    /*private static double calculateProbability(ArrayList<Peggle> queue) {
        double product = 1;
        for (Peggle peggle : queue) {
            product *= peggle.value();
        }
        return product;
    }*/

    private static void draw() {
        int rowlength;

        for (int i = 0; i < r; ++i) {
            if (i % 2 == 0) {
                rowlength = c;
            } else {
                rowlength = c - 1;
                System.out.print(" ");
            }
            for (int j = 0; j < rowlength; ++j) {
                System.out.print(peggles[j][i] ? "o" : "x");
                if (j != rowlength - 1) {
                    System.out.print(".");
                }
            }
            System.out.print("\n");
        }
        System.out.print(" ");
        for (int i = 0; i < k; ++i)
            System.out.print("  ");
        System.out.print("G\n");
    }
}
