#include "MiniLib.hpp"

void ACD::Seed(long long int new_seed)
{
    srand(new_seed);
}

int ACD::RandomInt(int min, int max)
{
    if(min==max)
    {
        return min;
    }

    if(min>max)
    {
        RandomInt(max, min);
    }

    return min+(rand()%(max-min));
}

float ACD::RandomPoint()
{
    return float(rand())/float(RAND_MAX);
}

float ACD::RandomFloat(int min, int max)
{
    float ret=RandomInt(min, max-1);
    ret+=RandomPoint();

    return ret;

}

float ACD::RandomFloat(float min, float max)
{
    int extarp_min, extarp_max, extarp_ret;
    float ret;
    extarp_min=min*EXTARPOLATION_MLT;
    extarp_max=max*EXTARPOLATION_MLT;

    extarp_ret=RandomInt(extarp_min, extarp_max);
    ret=float(extarp_ret)/float(EXTARPOLATION_MLT);

    return ret;
}
