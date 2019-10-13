//
//  main.cpp
//  L6Practices
//
//  Created by Han Zixuan on 13/10/19.
//  Copyright © 2019 Han Zixuan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    
    string main_path = __FILE__;
    string cd = main_path.substr(0, main_path.rfind("main.cpp"));   //get cd of this working file
    cout << cd <<endl;
    
{   //hello world.txt
    ofstream outf(cd + "helloworld.txt");   // using absoulte path
    outf << "Hello World! \n";
    // outf.close();    //redundent, outf will destroy itself when out of scope
}
    
{   // input1.txt
    ofstream outf(cd + "input1.txt");
    outf << std::setprecision(6) << fixed;
    outf << 2342234.02384 << endl << 3424.340 << endl << 340349.29347 << endl << 923482.23784 << endl << 92347.347 << endl << 20342.234234 << endl << 820482.03284 << endl;
    outf.close();

    ifstream inf(cd + "input1.txt");
    cout << endl << "Output from input1.txt: " << endl;
    double i;
    cout << std::setprecision(6) << fixed;
    while (!inf.eof()) {
        inf >> i;
        cout << i << endl;
    }
    inf.close();
}
    
{   // input2.txt
    ofstream outf(cd + "input2.txt");
    outf << "jjsf" << endl << 3444 << endl << "&*^*&("<< endl << 3234 << endl << "abc" << endl << "def" << endl << 123 << endl << "xyz" << endl;
    outf.close();
    
    ifstream inf(cd + "input2.txt");
    cout << endl << "Output from input2.txt: " << endl;
    
    int i; string s; int sum = 0;
       while (!inf.eof()) {
           inf >> i;            //read into int
           if (inf.fail()) {    //if input is not an integer
                    inf.clear();
                    inf >> s;       //read into string to get rid of it
                    continue;
                }
           cout << i << endl;
           sum += i;
       }
    inf.close();
    cout << "Sum of all numbers =  " << sum << endl;
}
    
    
{   // input3.txt
    ofstream outf(cd + "input3.txt");
    outf << "This is a textfile containing text."  << endl;
    outf.close();
    
    ifstream inf(cd + "input3.txt");
    cout << endl << "Output from input3.txt: " << endl;
    
    string s;
    while (!inf.eof()) {
        getline(inf,s);
        cout << s << "\n";
    }
}
    
    return 0;
}
