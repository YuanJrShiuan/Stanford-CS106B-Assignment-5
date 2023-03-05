/*
 * File: ourstring.h
 * ------------
 * This file exports the OurString interface
 */

#ifndef _ourstring_h
#define _ourstring_h

#include <iostream>
#include <cstring>

using namespace std;

static const int MAX_LENGTH = 256;

class OurString{

public:
    OurString();
    OurString(const char *str);
    OurString(const OurString &dstr);
    OurString(const string str);
    ~OurString();
    string toString() const;
    OurString subStr(unsigned int start, unsigned int n = MAX_LENGTH) const;
    unsigned int length() const;
    bool operator>(const OurString &dstr) const;
    bool operator<(const OurString &dstr) const;
    bool operator>=(const OurString &dstr) const;
    bool operator<=(const OurString &dstr) const;
    bool operator==(const OurString &dstr) const;
    bool operator!=(const OurString &dstr) const;
    char& operator[](int index);
    const OurString& operator=(const OurString &dstr);
    const OurString& operator=(const char *str);
    const OurString operator+(const OurString &dstr) const;
    const OurString operator+(const char *str) const;
    const OurString& operator+=(const OurString &dstr);
    const OurString& operator+=(const char *str);

    friend ostream & operator<<(ostream &os, const OurString &dstr);
    friend istream & operator>>(istream &is, OurString &dstr);

private:
    char *ptr;
};

#endif
