/*
 * File: ourString.cpp
 * --------------
 * This file implements the ourString.h interface
 * on Assignment #5.
 * [TODO: extend the documentation]
*/

#include <iostream>
#include <cstring>
#include "ourstring.h"
#include "strlib.h"
using namespace std;

OurString::OurString(){   //默认生成空串
    ptr = new char[1];
    ptr[0] = '\0';
}

OurString::OurString(const char *str){   //char数组类型构造函数
    int len = strlen(str);
    if(len > MAX_LENGTH) error("Beyond the limit!");
    ptr = new char[len+1];
    strncpy(ptr,str,len);
    ptr[len] = '\0';  // 结尾加入空字符，防止泄露
}

OurString::OurString(const OurString &dstr){  // 同类型对象构造函数
    int len = dstr.length();
    ptr = new char[len+1];
    strncpy(ptr,dstr.ptr,len);
    ptr[len] = '\0';
}

OurString::OurString(const string str){  // 使用string类构造函数
    const char*tmp = str.data();
    int len = strlen(tmp);
    if(len > MAX_LENGTH) error("Beyond the limit!");
    ptr = new char[len+1];
    strncpy(ptr,tmp,len);
    ptr[len] = '\0';
}

OurString::~OurString(){  // 析构函数，释放动态数组
    delete [] ptr;
}

string OurString::toString() const{
 string str = "";
 for(int i = 0;i<length();i++) str += charToString(ptr[i]);  //将char类型转换为string类并加入字符串
 return str;
}

OurString OurString::subStr(unsigned int start, unsigned int n) const{
    OurString p;
    p.ptr = new char[n+1];  //依据所需长度构造动态数组
    if(n == MAX_LENGTH || n > length()-start){  // 截取至末尾的情况
        for(int i =start;i<length();i++){
            p.ptr[i-start] = ptr[i];
        }
        p.ptr[length()-start] = '\0';
    }
    else{   //截取所需长度的情况
        for(int i =start;i<n+start;i++){
            p.ptr[i-start] = ptr[i];
        }
        p.ptr[n] = '\0';
    }
    return p;
}

bool OurString::operator > (const OurString &dstr) const{  //利用strcmp函数重载比较运算符
    int t = strcmp(ptr,dstr.ptr);
    if(t > 0) return true;
    else return false;
}

bool OurString::operator < (const OurString &dstr) const{
    int t = strcmp(ptr,dstr.ptr);
    if(t < 0) return true;
    else return false;
}

bool OurString::operator >= (const OurString &dstr) const{
    int t = strcmp(ptr,dstr.ptr);
    if(t >= 0) return true;
    else return false;
}

bool OurString::operator <= (const OurString &dstr) const{
    int t = strcmp(ptr,dstr.ptr);
    if(t <= 0) return true;
    else return false;
}

bool OurString::operator == (const OurString &dstr) const{
    if(strcmp(ptr,dstr.ptr) == 0) return true;
    else return false;
}
bool OurString::operator != (const OurString &dstr) const{
    if(strcmp(ptr,dstr.ptr) == 0) return false;
    else return true;
}

unsigned int OurString::length () const{
    return strlen(ptr);
}

const OurString& OurString::operator = (const OurString &dstr){
    if(this == &dstr) return *this;  // 防止复制自己时将自己释放
    delete [] ptr;   //释放原有空间
    ptr = new char[dstr.length()+1];
    strncpy(ptr,dstr.ptr,dstr.length());
    ptr[dstr.length()] = '\0';
    return *this;
}

const OurString& OurString::operator = (const char *str){
    delete [] ptr;
    ptr = new char[strlen(str)+1];
    strncpy(ptr,str,strlen(str));
    ptr[strlen(str)] = '\0';
    return *this;
}

char& OurString::operator[](int index){
    if(index >= length() || index < 0) error("Sting index is out of bounds!");  //防止越界
    return ptr[index];
}

const OurString OurString::operator + (const OurString &dstr) const{
    OurString q;
    q.ptr = new char[length()+dstr.length()+1];
    strncpy(q.ptr,ptr,length());
    strncat(q.ptr,dstr.ptr,dstr.length());
    return q;
}

const OurString OurString::operator + (const char *str) const{
    OurString q;
    q.ptr = new char[length()+strlen(str)+1];
    strncpy(q.ptr,ptr,length());
    strncat(q.ptr,str,strlen(str));
    return q;
}

const OurString& OurString::operator += (const OurString &dstr){
    char* q = new char[length()+1];   //先用一个新数组储存原来的内容
    strncpy(q,ptr,length());
    delete [] ptr;  // 释放ptr以扩展空间
    ptr = new char[strlen(q)+dstr.length()+1];
    strncpy(ptr,q,strlen(q));
    strncat(ptr,dstr.ptr,dstr.length());
    delete [] q;  // 释放过渡数组
    return *this;
}

const OurString& OurString::operator += (const char *str){
    char* q = new char[length()+1];
    strncpy(q,ptr,length());
    delete [] ptr;
    ptr = new char[strlen(q)+strlen(str)+1];
    strncpy(ptr,q,strlen(q));
    strncat(ptr,str,strlen(str));
    delete [] q;
    return *this;
}

ostream & operator<<(ostream &os, const OurString &dstr){
    os << dstr.toString();  // 以string方法cout
    return os;
}

istream & operator>>(istream &is, OurString &dstr){
    char* ch = new char[MAX_LENGTH+1];
    is.getline(ch,MAX_LENGTH);
    dstr = ch;  // 利用重载运算符方法赋值
    return is;
}



