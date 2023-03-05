/*
 * File: main.cpp
 * --------------------
 * This file tests Super Integer.
 */

#include <iostream>
#include <string>
#include <map.h>
#include "console.h"
#include "superint.h"
#include "strlib.h"
using namespace std;

//use map store calculated fact value
map<int, string> FACT_MAP;

SuperInt fact(int n)  // calculate n! with SuperInt
{
    SuperInt result("1");

    if (FACT_MAP.count(n)) return SuperInt(FACT_MAP[n]);

    if (n >= 2){
        if (not FACT_MAP.count(n - 1)){
            result = fact(n - 1) * SuperInt(long(n));
        }else {
            result = SuperInt(FACT_MAP[n - 1]) * SuperInt(long(n));
        }
    }

    FACT_MAP[n] = result.toString();
    return result;
}

int main()
{
    SuperInt s0;
    SuperInt s1("");  // same as SuperInt("0");
    SuperInt s2("-50");
    SuperInt s3(-120);
    SuperInt s4(s3);

    s0 = s1 = s2*s3;
    cout <<"s0 = "<<s0<<"  s1 = "<<s1<<endl;
    cout <<"s2 = "<<s2<<"  s3 = "<<s3<<endl;
    cout <<"absolute value of s2 = "<<s2.abs()<<" ; absolute value of s3 = "<<s3.abs()<<endl;
    cout <<"s3 + s2 = "<< s3+s2 << endl;
    cout <<"s3 - s2 = "<< s3-s2 << endl;
    cout <<"s2 - s3 = "<< s2-s3 << endl;
    cout <<"s3 * s2 = "<< s3*s2 << endl;

    cout <<"1000 - 999 = "<< SuperInt(1000) - SuperInt(999) << endl;

    cout <<"s0 - s3 = "<< s0-s3 << endl;
    cout <<"s1 + s2 = "<< s1+s2 << endl;
    cout <<"s0 - s1 = "<< s0-s1 << endl;

    cout <<"input s0: ";
    cin >> s0;
    cout <<"s0 = "<< s0 << endl;

    for (int i = 0; i <= 52; i++) {
        if (i < 10) cout << " ";   // too simple to test
        cout << i << "! = " << fact(i) << endl;
    }

    return 0;
}
