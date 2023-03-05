/*
 * File: superint.h
 * --------------
 * This interface exports the SuperInt class, which makes it possible to
 * represent nonnegative integers of arbitrary magnitude
 * on Assignment #5.
 * [TODO: extend the documentation]
 */

#ifndef _superint_h
#define _superint_h

#include <string>
#include <iostream>

using namespace std;

/*
 * Implementation notes: SuperInt data structure
 * -------------------------------------------
 * The SuperInt data structure stores the digits in the number in
 * a linked list in which the digits appear in reverse order with
 * respect to the items in the list.  Thus, the number 1729 would
 * be stored in a list like this:
 *
 *     start
 *    +-----+    +-----+    +-----+    +-----+    +-----+
 *    |  o--+--->|  9  |  ->|  2  |  ->|  7  |  ->|  1  |
 *    +-----+    +-----+ /  +-----+ /  +-----+ /  +-----+
 *               |  o--+-   |  o--+-   |  o--+-   | NULL|
 *               +-----+    +-----+    +-----+    +-----+
 *
 * The sign of the entire number is stored in a separate instance
 * variable, which is -1 for negative numbers and +1 otherwise.
 * Leading zeros are not stored in the number, which means that
 * the representation for zero is an empty list.
 */

struct IntList{
    int val;
    IntList *next;
    IntList(int val){
        this->val = val;
        this->next = nullptr;
    }
};

class SuperInt {

public:

    /*
     * Constructor: SuperInt
     * -----------------------
     * Usage: SuperInteger bi;
     * Constructs a new big integer with default style;
     */
   SuperInt();
    /*
     * Constructor: SuperInt
     * -----------------------
     * Usage: SuperInteger si1(si2);
     * Constructs a new super integer whose value is a copy of another super integer.
     */
   SuperInt(const SuperInt& s2);
   /*
    * Constructor: SuperInt
    * Usage: SuperInt sup(str);
    * -----------------------
    * Creates a new SuperInt from a string of decimal digits,
    * which may begin with a minus sign to indicate a negative value.
    */
  SuperInt(const char* s);
    /*
     * Constructor: SuperInt
     * Usage: SuperInt sup(s);
     * -----------------------
     * Creates a new SuperInt from a const string of decimal digits,
     * which may begin with a minus sign to indicate a negative value.
     */
   SuperInt(std::string str);
     /*
      * Constructor: SuperInt
      * Usage: SuperInt sup(long);
      * -----------------------
      * Creates a new SuperInt from a decimal long integer,
      * which may begin with a minus sign to indicate a negative value.
      */
    SuperInt(long n);
/*
 * Destructor: ~SuperInt
 * -------------------
 * Frees the memory used by a SuperInt when it goes out of scope.
 */
    ~SuperInt();
/*
 * Method: toString
 * Usage: string str = superint.toString();
 * --------------------------------------
 * Converts a SuperInt object to the corresponding string.
 */
    std::string toString() const;

    const SuperInt& operator=(const SuperInt &sint);

    const SuperInt operator-() const;
    const SuperInt operator+(const SuperInt &sint) const;
    const SuperInt operator-(const SuperInt &sint) const;

    const SuperInt abs() const;
    const SuperInt multi_ten_times(int times) const;
    const SuperInt operator*(const SuperInt &sint) const;
    friend ostream & operator<<(ostream &os, const SuperInt &sint);
    friend istream & operator>>(istream &is, SuperInt &sint);

private:
    //m_list->val 0 代表 0, -1 代表 负数, 1 代表 正数
    IntList *m_list = nullptr;
    //size 记录m_list后续结点长度
    unsigned int size = 0;
};

#endif
