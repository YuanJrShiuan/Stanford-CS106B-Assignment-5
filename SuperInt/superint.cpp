/*
 * File: superint.cpp
 * ----------------
 * This file implements the superint.h interface
 * on Assignment #5.
 * [TODO: extend the documentation]
 */

#include <cctype>
#include <string>
#include <cstring>
#include "superint.h"
#include "error.h"
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

SuperInt::SuperInt()
{
 // TODO: fill the code
    m_list = new IntList(0);
    size = 0;
}

SuperInt::SuperInt(const SuperInt& s2)
{
 // TODO: fill the code
    size = s2.size;
    m_list = new IntList(s2.m_list->val);
    IntList *pre = m_list;
    IntList *cur = s2.m_list->next;
    while(cur != nullptr){
        pre->next = new IntList(cur->val);
        pre = pre->next;
        cur = cur->next;
    }
}

 SuperInt::SuperInt(const char* s)
{
 // TODO: fill the code
     m_list=new IntList(0);
     size = 0;
     if (strlen(s) == 0)return;

     //判断符号
     char first = s[0];
     switch (first){
     case '-':
         m_list->val = -1;
         s++;
         break;
     case '+':
         m_list->val = 1;
         s++;
         break;
     default:
         m_list->val = 1;
         break;
     }

     //去除首部无效的0
     while(strlen(s) != 0){
         if (s[0] == '0'){
             s++;
         }else{
             break;
         }
     }

     //000000
     if (strlen(s) == 0) {m_list->val = 0; return;}  // 0000或-0000等情况

     //头插法插入剩余数字 12345
     for (int i = 0; i < strlen(s); i++){
         int num = s[i] - '0';
         if (num < 0 || num > 9) error("can not format string to SuperInt with char " + to_string(s[i]));
         IntList* tmp = new IntList(num);
         tmp -> next = m_list->next;
         m_list->next = tmp;
         size++;
     }
}

SuperInt::SuperInt(string str)
{
 // TODO: fill the code
    m_list=new IntList(0);
    size = 0;
    if (str == "")return;

    char first = str[0];
    switch (first){
    case '-':
        m_list->val = -1;
        str = str.substr(1);
        break;
    case '+':
        m_list->val = 1;
        str = str.substr(1);
        break;
    default:
        m_list->val = 1;
        break;
    }

    while(str != ""){
        if (str[0] == '0'){
            str = str.substr(1);
        }else{
            break;
        }
    }

    if (str == "") {m_list->val = 0; return;}  // 0000或-0000等情况

    //头插法创建链表
    for (char c : str){
        int num = c - '0';
        if (num < 0 || num > 9) error("can not format string to SuperInt with char " + to_string(c));
        IntList* tmp = new IntList(num);
        tmp -> next = m_list->next;
        m_list->next = tmp;
        size++;
    }
}

SuperInt::SuperInt(long n)
{
 // TODO: fill the code
    m_list=new IntList(0);
    size = 0;
    if (n == 0)return;
    if (n < 0){
        m_list->val = -1;
        n = -n;
    }else{
        m_list->val = 1;
    }

    //尾插法创建链表 12345
    IntList *pre = m_list;
    while(n){
        int num = n % 10;
        n = n / 10;
        pre->next = new IntList(num);
        pre = pre->next;
        size++;
    }
}

SuperInt::~SuperInt()
{
  // TODO: fill the code
    IntList *del_p=nullptr;
    //当链表不为空
    while(m_list != nullptr)
    {
        del_p=m_list->next;
        delete m_list;
        m_list=del_p;
    }
    //删除最后一个指针
    delete m_list;
    size = 0;
}

string SuperInt::toString() const
{
   string str = "";
   // TODO: fill the code
   if (m_list->val == 0){
       str = "0";
   }else{
       IntList *cur = m_list->next;
       while(cur != nullptr){
           str = to_string(cur->val) + str;
           cur = cur->next;
       }
       if (m_list->val == -1) str = "-" + str;
   }
   return str;
}

const SuperInt SuperInt::operator-() const{
    SuperInt tmp(*this);
    tmp.m_list->val *= -1;
    return tmp;
}

const SuperInt SuperInt::operator+(const SuperInt &sint) const{
    if (m_list->val * sint.m_list->val == 0){  // 0 + 某个数
        return m_list->val == 0 ? sint : *this;
    }

    SuperInt result("0");
    if (m_list->val * sint.m_list->val == 1){   //s1, s2同号
        result.m_list->val = m_list->val; //确定结果符号
        IntList *pre = result.m_list;
        IntList *cur1 = m_list->next;
        IntList *cur2 = sint.m_list->next;
        int carry = 0; //进位

        while(cur1 != nullptr && cur2 != nullptr){
            int num = cur1->val + cur2->val + carry;
            carry = num / 10;
            num = num % 10;
            pre->next = new IntList(num);
            pre = pre->next;
            result.size++;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        while(cur1 != nullptr){
            int num = cur1->val + carry;
            carry = num / 10;
            num = num % 10;
            pre->next = new IntList(num);
            pre = pre->next;
            result.size++;
            cur1 = cur1->next;
        }

        while(cur2 != nullptr){
            int num = cur2->val + carry;
            carry = num / 10;
            num = num % 10;
            pre->next = new IntList(num);
            pre = pre->next;
            result.size++;
            cur2 = cur2->next;
        }

        if(carry > 0){
            pre->next = new IntList(carry);
            result.size++;
        }
    }else{                                      //s1, s2异号 适用减法
        if (m_list->val == 1){        // a + b = a - (-b)
            return *this - (-sint);
        }else{           // a + b = b - (-a)
            return sint - (-*this);
        }
    }

    return result;
}

const SuperInt& SuperInt::operator = (const SuperInt &sint){
    if (this != &sint){
        IntList *del_p=nullptr;
        //当链表不为空
        while(m_list!=nullptr)
        {
            del_p=m_list->next;
            delete m_list;
            m_list=del_p;
        }
        //删除最后一个指针
        delete m_list;
        size = sint.size;
        m_list = new IntList(sint.m_list->val);
        IntList *pre = m_list;
        IntList *cur = sint.m_list->next;
        while(cur != nullptr){
            pre->next = new IntList(cur->val);
            pre = pre->next;
            cur = cur->next;
        }
    }
    return *this;
}

//判断两个等长链表的大小关系（从末尾开始）相等返回0，l1 > l2返回正数，l2 > l1返回负数
int compare(IntList *l1, IntList *l2){
    if (l1 == nullptr) return 0;
    int before = compare(l1->next, l2->next);
    return before != 0 ? before : l1->val - l2->val;
}

const SuperInt SuperInt::operator-(const SuperInt &sint) const{
    if (m_list->val * sint.m_list->val == 0){  // 0 - 某个数 或 某个数 - 0
        if (m_list->val == 0){
            return -sint;
        }
        return *this;
    }

    if (m_list->val * sint.m_list->val == 1){   //s1, s2同号
        SuperInt result("0");
        int this_larger = 0;  //判断两数大小
        if (size != sint.size){
            this_larger = size - sint.size;
        }else{
            this_larger = compare(m_list->next, sint.m_list->next);
        }

        if (this_larger == 0) return result;

        result.m_list->val = this_larger > 0 ? 1 : -1; //确定结果符号
        IntList *pre = result.m_list;
        IntList *cur1 = this_larger > 0 ? m_list->next : sint.m_list->next;
        IntList *cur2 = this_larger < 0 ? m_list->next : sint.m_list->next;;
        int borrow = 0; //借位

        while(cur1 != nullptr && cur2 != nullptr){
            int num1 = cur1->val - borrow;
            int num2 = cur2->val;

            borrow = num1 < num2;
            num1 += borrow * 10;

            pre->next = new IntList(num1 - num2);
            pre = pre->next;
            result.size++;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        while(cur1 != nullptr){
            int num1 = cur1->val - borrow;

            borrow = num1 < 0;
            num1 += borrow * 10;

            pre->next = new IntList(num1);
            pre = pre->next;
            result.size++;
            cur1 = cur1->next;
        }
        //减法最后没有借位

        //删除首部无意义的0
        string tmp = result.toString();
        while(tmp != ""){
            if (tmp[0] == '0'){
                tmp = tmp.substr(1);
            }else{
                break;
            }
        }
        return SuperInt(tmp);
    }else{                                      //s1, s2异号 适用加法
        if (m_list->val == 1){      // a - b = a + (-b)
            return -sint + *this;
        }else{              // a - b = -((-a) + b)
            return -(-*this + sint);
        }
    }
}

const SuperInt SuperInt::multi_ten_times(int times) const{
    SuperInt result(*this);
    if (m_list->val == 0) return result;
    while(times > 0){
        IntList *tmp = new IntList(0);
        tmp->next = result.m_list->next;
        result.m_list->next = tmp;
        result.size++;
        times--;
    }
    return result;
}

const SuperInt SuperInt::operator*(const SuperInt &sint) const{
    if (m_list->val*sint.m_list->val==0){           //0 * n = n * 0 = 0 * 0 = 0
        return SuperInt("");
    }else {
        if (size == 1 || sint.size == 1){           //个位数乘多位数
            SuperInt result("");
            result.m_list->val = m_list->val * sint.m_list->val;
            IntList *pre = result.m_list;
            int num = size == 1 ? m_list->next->val : sint.m_list->next->val;
            IntList *cur = size == 1 ? sint.m_list->next : m_list->next;
            int carry = 0;
            while (cur != nullptr){
                int cur_num = cur->val * num + carry;
                carry = cur_num / 10;
                pre->next = new IntList(cur_num % 10);
                result.size++;
                pre = pre->next;
                cur = cur->next;
            }
            if (carry > 0) {
                pre->next = new IntList(carry);
                result.size++;
            }
            return result;
        }

        SuperInt num1(*this);
        SuperInt num2(sint);
        num1.m_list->val = 1;
        num2.m_list->val = 1;

        int half = min(size, sint.size) / 2;                       //分段点为n/2

        string a = num1.toString().substr(0, size - half);        //将num1分为a， b
        string b = num1.toString().substr(size - half);
        string c = num2.toString().substr(0, sint.size - half);    //将num2分为c， d
        string d = num2.toString().substr(sint.size - half);

        SuperInt z1(SuperInt(a) * SuperInt(c));                               //递归计算z1=ac
        SuperInt z2(SuperInt(b) * SuperInt(d));                               //递归计算z2=bd
        SuperInt z3(SuperInt(a) * SuperInt(d) + SuperInt(b) * SuperInt(c));   //递归计算z3=ad+bc

        SuperInt result(z1.multi_ten_times(2*half) + z3.multi_ten_times(half) + z2);         //num1 * num2 = ac * 2nE +（ad + bc）* nE + bd
        result.m_list->val = m_list->val*sint.m_list->val;
        return result;
    }
}

const SuperInt SuperInt::abs() const{
    SuperInt abs = *this;
    if(abs.m_list->val == -1) abs.m_list->val = 1;
    return abs;
}

ostream & operator<<(ostream &os, const SuperInt &sint){
    os<<sint.toString();
    return os;
}

istream & operator>>(istream &is, SuperInt &sint){
    string str = "";
    is>>str;
    sint = SuperInt(str);
    return is;
}
