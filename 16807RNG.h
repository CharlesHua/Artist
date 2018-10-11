/***************************************************
本程序使用Schrage方法编写16807随机数生成器
Schrage方法：
m = a*q + r , q = [m/a] , r = m mod a,
(a*z) mod m = a*(z mod q)-r*[z/q], if >=0;
              a*(z mod q)-r*[z/q]+m ,otherwise
***************************************************/
#ifndef _16807RNG_H
#define _16807RNG_H

class RandomNumber_16807
{
public:
    RandomNumber_16807():
        seed(0x7FFFFFFF / 7) //定义种子并任意给它一个初值;
    {}

    RandomNumber_16807(int the_seed):
        seed(the_seed)
    {}

    double get_random_number()
    {
        seed = rng_a * (seed % rng_q) - rng_r * (seed / rng_q);
        if (seed<0)
            seed += rng_m;
        return seed/2147483647.0;
    }

private:
    static const int rng_a = 16807;
    static const int rng_m = 0x7FFFFFFF;
    static const int rng_q = rng_m / rng_a;
    static const int rng_r = rng_m % rng_a;
    int seed;
};

#endif // _16807RNG_H
