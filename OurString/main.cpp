/*
 * File: main.cpp
 * This file is the starter project for OurString problem
 */


#include <iostream>
#include <cstring>
#include "console.h"
#include <string>
#include "ourstring.h"

using namespace std;

/*
 * Main program
 */

int main()
{
    OurString s0;
    OurString s1("123");

    OurString s2 = "67890";

    OurString s3 = s2;

    cout<<"s3 = "<<s3.toString()<<endl;
    cout<<"s3.subStr(2,2) = "<<s3.subStr(2,2)<<endl;
    cout<<"s3.subStr(0,8) = "<<s3.subStr(0,8)<<endl;
    cout<<"s3.subStr(1) = "<<s3.subStr(1)<<endl;

    cout<<"s1 = "<<s1<<endl;
    cout<<"s2 = "<<s2<<endl;
    cout<<"s1 + s2 = "<<s1+s2<<endl;

    OurString s4 = s1+s2;
    cout<<"s2 + s1 + s2 = "<<s2+s1+s2<<endl;
    cout<<"s4 = s1 + s2 :"<<s4<<endl;
    s3 = s2 = s1 + s2;

    s1 += s2;
    cout<<"s1 += s2:"<<s1<<endl;

    cout<<"&s1[2] = "<<s1[2]<<endl;

    cout<<"S3 = "<<s3<<endl;

    cout<<"S3 + ABC = "<<s3+"ABC"<<endl;
    s3+="EDF";
    cout<<"S3 += EDF:"<<s3<<endl;

    if(s4 == s2)
        cout<<"s4 = s2"<<endl;
    else
        cout<<"s4 != s2"<<endl;
    string tmp = "JKL";
    OurString s5(tmp);    // 加入string构造函数测试
    cout << "s5 = " <<s5 << endl;
    cout << "Enter the value of s5:";
    cin >> s5;
    cout << "s5 = " << s5 << endl;
    cout << "s5 > s4 ?" << (s5 > s4) << endl;
    cout << "s5 < s4 ?" << (s5 < s4) << endl;
    return 0;
}

