/***************************************************
������ʹ��Schrage������д16807�����������
Schrage������
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
        seed(0x7FFFFFFF / 7) //�������Ӳ��������һ����ֵ;
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
