#include "MiniLib.hpp"

/// @brief Change seed for all random events
/// @param new_seed new seed
void ACD::Seed(long long int new_seed)
{
    srand(new_seed);
}

/// @brief Generate pseudorandom int (including min/max)
/// @param min minimal value
/// @param max max value
/// @return pseudorandom value in range [min; max]
int ACD::RandomInt(int min, int max)
{
    //Checking user input
    if(min==max)
    {
        return min;
    }

    if(min>max)
    {
        RandomInt(max, min);
    }

    //Generting pseudorandom int
    return min+(rand()%(max-min));
}

/// @brief Generate random float after dot
/// @return Pseudorandom float in range [0; 1]
float ACD::RandomPoint()
{
    return float(rand())/float(RAND_MAX);
}

/// @brief Generates random float from min to max
/// @param min minimal value
/// @param max maximum value
/// @return Pseudo random float in range [min; max]
float ACD::RandomFloat(int min, int max)
{
    //Generating pseudorandom int, and adding pseudorandom point float
    float ret=RandomInt(min, max-1);
    ret+=RandomPoint();

    return ret;

}

/// @brief Generates random float from min to max
/// @param min minimal value
/// @param max maximum value
/// @return pseudorandom float in range [min; max]
float ACD::RandomFloat(float min, float max)
{
    //Extarpolating input float (so we can use standart RandomInt())
    int extarp_min, extarp_max, extarp_ret;
    float ret;
    extarp_min=min*EXTARPOLATION_MLT;
    extarp_max=max*EXTARPOLATION_MLT;

    //Generating random int
    extarp_ret=RandomInt(extarp_min, extarp_max);
    //Reduction of result
    ret=float(extarp_ret)/float(EXTARPOLATION_MLT);

    return ret;
}
