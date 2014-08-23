#include<iostream>
#include<stdio.h>

using namespace std;

int main(void) {
  int isprime;
  long long n;
  cerr<<"Enter range :";
  cin>>n;
  for( long long i = 2 ; i <= n ; i++)
  {
     isprime = 1;
     for( long long j = 2 ; j <= i ; j++)
     {
        if( i == j)
           continue;
        else if( i % j == 0)
        isprime = 0;
     }
     if(isprime)
     cout<<i<<",";
  }
}
