#include <climits>
#include <iostream>
#include <stdexcept>
using namespace std;

//TLE
int divide0(int dividend, int divisor) {
    if (divisor == 0)
        throw invalid_argument("Received zero divisor!");

    bool negative = false;
    if (dividend < 0) {
        dividend = -dividend;
        negative = !negative;
    }

    if (divisor < 0) {
        divisor = -divisor;
        negative = !negative;
    }

    int result = 0;
    for (int sum = 0; dividend-divisor-sum >= 0; sum += divisor, result++ );

    return negative ? -result : result;
}


//Pay attention to the possible overflow in negation when the dividend is INT_MIN
//and the divisor is -1
//Also pay attention to the possible overflow in shifting operations
int divide1(int dividend, int divisor) {
    if (divisor == 0)
        throw invalid_argument("Received zero divisor!");

    unsigned int posDividend = (dividend >= 0) ? dividend : -dividend;
    unsigned int posDivisor = (divisor > 0) ? divisor : -divisor;
    unsigned int posResult = 0;

    while (posDividend >= posDivisor) {
        unsigned int tempDivisor = posDivisor;

        for (unsigned int i = 1; posDividend >= tempDivisor; tempDivisor = tempDivisor << 1, i = i << 1)
        {
            posDividend -= tempDivisor;
            posResult += i;

            if ((tempDivisor-1) == INT_MAX)
                break;
        }
    }

    return ((dividend ^ divisor) < 0) ?  -posResult : posResult;
}

//Jianchao Li's answer
//https://discuss.leetcode.com/topic/15568/detailed-explained-8ms-c-solution
int divide(int dividend, int divisor) {
    if (!divisor || (dividend == INT_MIN && divisor == -1))
        return INT_MAX;
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
    long long dvd = labs(dividend);
    long long dvs = labs(divisor);
    int res = 0;
    while (dvd >= dvs) { 
        long long temp = dvs, multiple = 1;
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        dvd -= temp;
        res += multiple;
    }
    return sign == 1 ? res : -res; 
}

int main(int argc, char** argv)
{
    int dividend = atoi(argv[1]);
    int divisor = atoi(argv[2]);
    cout << dividend << " / " << divisor << " = " << divide(dividend, divisor) << endl;
    
    cout << "True Answer = " << dividend / divisor << endl;

    return 0;
}
