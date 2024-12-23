#include "MiniLib.hpp"

void ACD::Seed(long long int new_seed)
{
    srand(new_seed);
}
int ACD::RandomInt(int min, int max)
{

    if(min>max){
        int pop=min;
        min=max;
        max=pop;
    }

    if(min==max){
        return min;
    }

    return min+rand()%(max+1);

};

