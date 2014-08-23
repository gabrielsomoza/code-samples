#include<iostream>
using namespace std;
int main(){
    int N, kase, P, R, F, i,k,ans;
    bool board[18][18];
    char piece[17][17];
    char arr[10];
    //freopen("fb_p2_main3.txt","r",stdin);
    //freopen("fb_p2_maino3.txt","w",stdout);

    scanf("%d",&N);
    for (kase=1;kase<=N;kase++){
        for(i=1;i<=16;i++)
            for(k=1;k<=16;k++){
                board[i][k]=0;
                piece[i][k] = 0;
            }

        scanf("%d",&P);
        for(i=1;i<=P;i++){
            scanf("%1s %d %d",arr,&R,&F);
            piece[R][F] = arr[0];
        }
        /*
        for(R=1;R<=16;R++){
            for(F=1;F<=16;F++){
                printf("%d ",piece[R][F]);
            }
            cout<<endl;
        }
        */

        for(R=1;R<=16;R++){
            for(F=1;F<=16;F++){
                   switch(piece[R][F]){
                         default:break;
                         case 'Q':
                              for(i=1;R-i>=1;i++){
                                  board[R-i][F]=1;
                                  if(piece[R-i][F])
                                     break;
                              }

                              for(i=1;R+i<=16 ;i++){
                                  board[R+i][F]=1;
                                  if(piece[R+i][F])
                                     break;
                              }
                              for(i=1;F-i>=1;i++){
                                  board[R][F-i]=1;
                                  if(piece[R][F-i])
                                     break;
                              }
                              for(i=1;F+i<=16;i++){
                                  board[R][F+i]=1;
                                  if(piece[R][F+i])
                                     break;
                              }

                              for(i=1;R-i>=1 && F-i>=1;i++){
                                        board[R-i][F-i]=1;
                                        if(piece[R-i][F-i])
                                           break;
                              }
                              for(i=1;R-i>=1 && F+i<=16;i++){
                                        board[R-i][F+i]=1;
                                        if(piece[R-i][F+i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F-i>=1;i++ ){
                                        board[R+i][F-i]=1;
                                        if(piece[R+i][F-i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F+i<=16 ;i++){
                                        board[R+i][F+i]=1;
                                        if(piece[R+i][F+i])
                                           break;
                              }
                              break;
                         case 'K':
                              board[R-1][F-1]=1;
                              board[R-1][F] = 1;
                              board[R-1][F+1]=1;
                              board[R][F-1]=1;
                              board[R][F+1]=1;
                              board[R+1][F-1]=1;
                              board[R+1][F]=1;
                              board[R+1][F+1]=1;
                              break;
                         case 'R':
                              for(i=1;R-i>=1;i++){
                                  board[R-i][F]=1;
                                  if(piece[R-i][F])
                                     break;
                              }

                              for(i=1;R+i<=16 ;i++){
                                  board[R+i][F]=1;
                                  if(piece[R+i][F])
                                     break;
                              }
                              for(i=1;F-i>=1;i++){
                                  board[R][F-i]=1;
                                  if(piece[R][F-i])
                                     break;
                              }
                              for(i=1;F+i<=16;i++){
                                  board[R][F+i]=1;
                                  if(piece[R][F+i])
                                     break;
                              }
                              break;
                         case 'B':
                              for(i=1;R-i>=1 && F-i>=1;i++){
                                        board[R-i][F-i]=1;
                                        if(piece[R-i][F-i])
                                           break;
                              }
                              for(i=1;R-i>=1 && F+i<=16;i++){
                                        board[R-i][F+i]=1;
                                        if(piece[R-i][F+i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F-i>=1;i++ ){
                                        board[R+i][F-i]=1;
                                        if(piece[R+i][F-i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F+i<=16 ;i++){
                                        board[R+i][F+i]=1;
                                        if(piece[R+i][F+i])
                                           break;
                              }
                              break;
                         case 'N':
                              if(R-2>=1 && F-1>=1) board[R-2][F-1]=1;
                              if(R-1>=1 && F-2>=1) board[R-1][F-2]=1;
                              if(R-2>=1 && F+1<=16) board[R-2][F+1]=1;
                              if(R-1>=1 && F+2<=16) board[R-1][F+2]=1;
                              if(R+1<=16 && F+2<=16) board[R+1][F+2]=1;
                              if(R+2<=16 && F+1<=16) board[R+2][F+1]=1;
                              if(R+2<=16 && F-1>=1) board[R+2][F-1]=1;
                              if(R+1<=16 && F-2>=1) board[R+1][F-2]=1;
                              break;
                         case 'S':
                              for(i=1;R-2*i>=1 && F-i>=1;i++){
                                                board[R-2*i][F-i]=1;
                                                if(piece[R-2*i][F-i])
                                                   break;
                              }
                              for(i=1;R-i>=1 && F-2*i>=1;i++){
                                             board[R-i][F-2*i]=1;
                                             if(piece[R-i][F-2*i])
                                                break;
                              }
                              for(i=1;R-2*i>=1 && F+i<=16;i++){
                                                board[R-2*i][F+i]=1;
                                                if( piece[R-2*i][F+i])
                                                   break;
                              }
                              for(i=1;R-i>=1 && F+2*i<=16 ;i++){
                                              board[R-i][F+2*i]=1;
                                              if(piece[R-i][F+2*i])
                                                 break;
                              }
                              for(i=1;R+i<=16 && F+2*i<=16 ;i++){
                                               board[R+i][F+2*i]=1;
                                               if(piece[R+i][F+2*i])
                                                  break;
                              }
                              for(i=1;R+2*i<=16 && F+i<=16;i++){
                                                 board[R+2*i][F+i]=1;
                                                 if(piece[R+2*i][F+i])
                                                    break;
                              }
                              for(i=1;R+2*i<=16 && F-i>=1;i++){
                                                 board[R+2*i][F-i]=1;
                                                 if(piece[R+2*i][F-i])
                                                    break;
                              }
                              for(i=1;R+i<=16 && F-2*i>=1;i++){
                                               board[R+i][F-2*i]=1;
                                               if(piece[R+i][F-2*i])
                                                  break;
                              }
                              break;
                         case 'A':
                              if(R-2>=1 && F-1>=1) board[R-2][F-1]=1;
                              if(R-1>=1 && F-2>=1) board[R-1][F-2]=1;
                              if(R-2>=1 && F+1<=16) board[R-2][F+1]=1;
                              if(R-1>=1 && F+2<=16) board[R-1][F+2]=1;
                              if(R+1<=16 && F+2<=16) board[R+1][F+2]=1;
                              if(R+2<=16 && F+1<=16) board[R+2][F+1]=1;
                              if(R+2<=16 && F-1>=1) board[R+2][F-1]=1;
                              if(R+1<=16 && F-2>=1) board[R+1][F-2]=1;
                              for(i=1;R-i>=1 && F-i>=1;i++){
                                        board[R-i][F-i]=1;
                                        if(piece[R-i][F-i])
                                           break;
                              }
                              for(i=1;R-i>=1 && F+i<=16;i++){
                                        board[R-i][F+i]=1;
                                        if(piece[R-i][F+i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F-i>=1;i++ ){
                                        board[R+i][F-i]=1;
                                        if(piece[R+i][F-i])
                                           break;
                              }
                              for(i=1;R+i<=16 && F+i<=16 ;i++){
                                        board[R+i][F+i]=1;
                                        if(piece[R+i][F+i])
                                           break;
                              }
                              break;
                         case 'E':
                              for(i=1;i<=16;i++)
                                 for(k=1;k<=16;k++)
                                     if(i!=R || k!=F)
                                      board[i][k]=1;
                              break;
                   }
            }
        }
        /*
        cout<<"Board\n";
        for(R=1;R<=16;R++){
            for(F=1;F<=16;F++){
                printf("%d ",board[R][F]);
            }
            cout<<endl;
        }
        */
        ans=0;
        for(R=1;R<=16;R++){
            for(F=1;F<=16;F++){
                if(piece[R][F] && board[R][F]==1)
                   ans++;
            }
        }
        cout<<ans<<endl;

    }
    return 0;
}
