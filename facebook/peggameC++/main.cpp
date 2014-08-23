#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

struct peg {
        vector<peg*> pegs;
        double prob;
        bool done;

        peg() {
                done=false;
                prob=0.0;
        }

        double getProb() {
                if (!done) {
                        for (int i=0; i<(int)pegs.size(); ++i) prob+=pegs[i]->getProb();
                        prob/=pegs.size();
                        done=true;
                }
                return prob;
        }
};

int main() {
        int N; cin >> N;

        for (int I=0; I<N; ++I) {

                int r, c; cin >> r >> c;
                peg pegs[r+2][c];

                /**
                 * Link all pegs to their previous ones
                 * [i>=2] because first two rows are all done
                 */
                for (int i=r+1; i>=2; --i) {
                        if (i%2==1) { //smaller row
                                pegs[i][0].pegs.push_back(&pegs[i-1][1]);
                                pegs[i][c-2].pegs.push_back(&pegs[i-1][c-2]);
                                for (int j=1; j<c-2; ++j) {
                                        pegs[i][j].pegs.push_back(&pegs[i-1][j]);
                                        pegs[i][j].pegs.push_back(&pegs[i-1][j+1]);
                                }
                        } else { //larger row
                                for (int j=1; j<c-1; ++j) {
                                        pegs[i][j].pegs.push_back(&pegs[i-1][j-1]);
                                        pegs[i][j].pegs.push_back(&pegs[i-1][j]);
                                }
                        }
                }

                int k; //target
                cin >> k;
                for (int i=0; i<c; ++i)
                        pegs[0][i].done=pegs[1][i].done=true;
                pegs[1][k].prob=1.0;

                //initialize the missing pegs
                int m; cin >> m;
                for (int i=0; i<m; ++i) {
                        int y, x; cin >> y >> x; 
                        y+=2; //operations are on peg below missing peg
                        pegs[y][x].pegs.clear(); //clear queue leading to this peg
                        pegs[y][x].pegs.push_back(&pegs[y-2][x]); //reference missing peg only
                }

                double max=0; int pos;
                for (int i=0; i<=c-2; ++i) {
                        double cur=pegs[r][i].getProb();
                        if (cur>max) {
                                max=cur;
                                pos=i;
                        }
                }

                printf("%d %6lf\n", pos, max);
        }
}