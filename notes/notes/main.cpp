//
//  main.cpp
//  FE5226
//
//  Created by Han Zixuan on 17/8/19.
//  Copyright © 2019 Han Zixuan. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

/*
 Author: Fabio Cannizzo
 NUS FE5226 Example Program

 A dumb String class
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class String
{
    char *m_data;

    void reset(const char *s)
    {
        if (s != m_data) {
            // release previous memory
            delete [] m_data;
            // allocate new memory: add 1 for the zero at the end
            m_data = new char[strlen(s) + 1];
            // copy from s
            strcpy(m_data, s);
        }
    }

    friend  ostream& operator<<(ostream& os, const String& s);

public:
    String() : m_data(NULL) { reset(""); }
    String(const char *s) : m_data(NULL) { reset(s); }
    String(const String& s) : m_data(NULL) { reset(s.m_data); }

    ~String() { delete[] m_data; }

    // lenght of the string
    unsigned length() const { return strlen(m_data); }

    const char *operator()() const
    {
        return m_data;
    }

    // first overload += operator
    String& operator+=(const char* rhs)
    {
        unsigned n2 = strlen(rhs);
        if (n2>0) {
            unsigned n1 = length();
            char *tmp = new char[n1+n2+1];
            strncpy(tmp, m_data, n1);
            strcpy(tmp+n1, rhs);
            delete [] m_data;
            m_data = tmp;
        }
        return *this;
    }

    // second overload += operator
    String& operator+=(const String& rhs)
    {
        return *this += rhs.m_data;
    }

    // first overload += operator
    String& operator=(const char* rhs)
    {
        reset(rhs);
        return *this;
    }

    // second overload += operator
    String& operator=(const String& rhs)
    {
        return *this = rhs.m_data;
    }
};

ostream& operator<<(ostream& os, const String& s)
{
    os << s.m_data;
    return os;
}

int main()
{
    String s1("Hello");
    String s2("World");

    cout << s1 << endl;
    
    s1 += " ";
    cout << s1 << endl;
    
    s1 += s2;
    cout << s1 << endl;

    String s3;
    s3 = s1;
    cout << s3 << endl;

    return 0;
}


 



#if 0
//Array指针基础
int main() {
    int x[5] = {10, 20, 30, 40, 50};
    int * px = x; // 指向x[0]的内存地址
    cout <<"memory add of x[0]: "<< px   <<" or "<< x   <<" or "<< &x[0] <<" don't use-> "<< &x     << endl;
    cout <<"memory add of x[1]: "<< px+1 <<" or "<< x+1 <<" or "<< &x[1] <<" don't use-> "<< &x + 1 << endl;
    cout << "1st element of x: " << px[0] <<" or "<< *px     <<" or "<< *x     <<" or " << x[0] << endl;
    cout << "end element of x: " << px[1] <<" or "<< *(px+1) <<" or "<< *(x+1) <<" or " << x[1] << endl;
    cout << "last element of x: " << *((int*)(&x + 1)-1) << endl;
    cout << "sizeof(x): " << sizeof(x) << endl;
    cout << "sizeof(px): " << sizeof(px) << endl;
    cout << (x+1)[-1] <<" and "<< (x+1)[-1] << endl;   //取到x的第一和第三个element
    
    for (int *i = x; i != x+5; ++i){
        cout << ++*i << ", "; // *i 取对象值 -> ++ 把对象值做修改了+1 -> cout打出来
        //cout << *i++ << ", "; // 乱码
    } cout << endl;
    
    //指针的指针
    int *y = x;
    int **z = &y;
    cout << (*z)[2] <<" or "<< *(*z+2)  << endl;
    
    //Arry of pointer
    const char *msg[] = { "ABC", "def" }; // msg[]本身是一个包含2个指针的array，msg[0]->"ABC“这个array的”A“的地址， msg[1]->“def”这个array的“d”的地址
    cout << *(msg[1]+1) << endl; //  msg[1]+1 -> 指向“def”这个array的第二位“e“的地址，然后再用*把对象指取出
    cout << *msg[1] << endl; // 一个char类型的指针好像就是这个string本身？
}
#endif

#if 0 // Dynamic create array of unknown length, stop when user enter value < 0
struct myArray {
    const size_t initial_size = 2;
    const size_t growth_factor = 2;
    
    size_t length = 0;
    size_t capacity = initial_size;
    int *v;
};
int main() {

    int x;
    myArray numbers;
    numbers.v = new int[numbers.capacity];
    
    while (true)  {
        cout << "Input a number (<0 to terminate)";
        
        if (!(cin >> x) || x < 0) break;
    
        if (numbers.length == numbers.capacity){
            int * temp = new int[numbers.capacity *= numbers.growth_factor];
            for (int i = 0; i < numbers.length; ++i){
                temp[i] = numbers.v[i];
            }
            delete [] numbers.v;
            numbers.v = temp;
        }
    numbers.v[numbers.length++] = x;
    }
    
    for (size_t i = 0; i < numbers.length; ++i) cout << numbers.v[i] << ",";
    return 0;
}
#endif

#if 0 //Struct Dynamic Allocation
int main() {
    // define the new type ComplexNumber
    struct ComplexNumber
    {
        double realPart;
        double imagPart;
    };
    // declare a pointer variable of type ComplexNumber
    ComplexNumber *ptr = NULL;
    ptr = new ComplexNumber; // allocate memory (note no square brackets)
    // initialize members
    ptr->realPart = 3.0;
    ptr->imagPart = -2.2;
    // print the data members of y
    cout << ptr->realPart << ", " << ptr->imagPart << endl;
    delete ptr; // de-allocate memory (note no square brackets)
}
#endif

#if 0 //Pointer to Struct
int main() {
    // define the new type ComplexNumber
    struct ComplexNumber
    {
        double realPart;
        double imagPart;
    };
    // declare a variable of type complexNumber
    ComplexNumber x = {1.0, 1.0 };
    ComplexNumber *ptr = &x; // a pointer to x
    // print the data members of y
    cout << ptr->realPart << ", " << ptr->imagPart << endl;
}
#endif

#if 0 //double loop测质数：世界上只有两种正整数，质数和可以写成质数乘积的合数
int main () {
    unsigned primes [80000]; //over-dimensioned
    unsigned nPrimesFound = 0;
    unsigned upperBond = 100; //let's find all primes under 100
    for (unsigned i = 2; i < upperBond; ++i) {
        unsigned largest = static_cast<unsigned>(sqrt(static_cast<double>(i)));
        bool isPrime = true;
        // 测每一个小于sqrt(i)的质数，如果不能被这些质数整除，说明i是质数
        for (unsigned j = 0; j < nPrimesFound; ++j) {
            if (primes[j] > largest) //no need to check further
                break; //exit j loop
            if (i % primes[j] == 0) {
                isPrime = false;
                break;//exit j loop
            }
        }
        if (isPrime) primes[nPrimesFound++] = i;
    }
    for (unsigned i = 0; i < nPrimesFound; ++i) cout << primes[i] << ",";
    return 0;
}
#endif
