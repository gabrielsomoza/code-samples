/* 
 * File:   main.cpp
 * Author: Gabriel Somoza
 * Webpage: http://gabrielsomoza.com
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <math.h>

#define length(a) ( sizeof ( a ) / sizeof ( *a ) )

typedef unsigned long ulong64;

using namespace std;

ulong64 cache[10000001];

bool is_prime(ulong64 n) {
    static unsigned int primes55[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
        181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257};

    for (unsigned int i = 0; i < 55; i++) {
        if (n % primes55[i] == 0) {
            if (n == primes55[i]) {
                return true;
            } else {
                return false;
            }
        }
    }

    ulong64 maxtest = n >> 4;

    for (ulong64 i = 259; i < maxtest; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

long factorful(ulong64 i, long n) {
    long c = 0;

    if (i == 1) return 0;
    if (cache[i] > 0) return cache[i];

    if (i % 2 == 0) return 2;
    
    for (ulong64 div = 3; i / div >= div; div += 2) {
        if (i % div == 0)
            c++;
        if(c>n) {
            c == 0;
            break;
        }
    }

    if (c != 0 && cache[i] == 0) cache[i] == c;
    return c;
}

int main() {
    int T, n;
    ulong64 a, b;
    long c, r;

    cache[1] = 0;

    cin >> T;
    for (int t = 1; t <= T; t++) {
        cerr << "Remaining: " << (T - t + 1) << endl;
        cin >> a >> b >> n;
        if (n == 0) {
            if (a <= 1)
                c = 1;
            else
                c = 0;
        } else {
            c = 0;
            for (ulong64 i = a; i <= b; i++) {
                if ((r = factorful(i, n)) == n)
                    c++;
            }
        }
        cout << c << endl;
    }
}

