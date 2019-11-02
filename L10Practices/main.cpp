//
//  main.cpp
//  L10Practices
//
//  Created by Han Zixuan on 19/10/19.
//  Copyright © 2019 Han Zixuan. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <sstream>


using namespace std;

pair <double, double> roots(double a, double b, double c)
{
    double delta = b*b - 4*a*c;
    if (delta <0 ){
        ostringstream os;
        os << "negative discriminant: " << delta;
        throw invalid_argument(os.str());
    }

    double disc = sqrt(delta);
    double a2= a*2;
    return make_pair((-b+disc)/a2, -(b+disc)/a2);
}

int main(int argc, const char * argv[]) {
    double a = 1, b = 1,c=1;
    try
    {
        auto res = roots(a, b, c);
        cout << res.first << ", " << res.second << "\n";
        return 0;
    }

    catch (const invalid_argument& e)
    {
        cout << e.what() << "\n";
        return -1;
    }
}
