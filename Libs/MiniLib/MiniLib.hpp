
#ifndef MINILIB_LIB
#define MINILIB_LIB

#define EXTARPOLATION_MLT 10000

#include <cstdlib>
#include <cstdarg>

namespace ACD{

    void Seed(long long int new_seed);
    int RandomInt(int min, int max);
    float RandomPoint();

    float RandomFloat(int min, int max);

    float RandomFloat(float min, float max);

    template<typename ArrayType>
    void Shuffle(ArrayType* arr, int size){
        int swipe_times=RandomInt(size, size*5);

        do
        {
            int switch_pos_a, switch_pos_b;
            switch_pos_a=RandomInt(0, size-1);
            do
            {
                switch_pos_b=RandomInt(0, size-1);
            } while (switch_pos_a==switch_pos_b);

            ArrayType pop;

            pop=arr[switch_pos_a];
            arr[switch_pos_a]=arr[switch_pos_b];
            arr[switch_pos_b]=pop;            
            swipe_times--;


        } while (swipe_times>0);
        

    };

    template<typename SearchType>
    SearchType Min(int amount,int *sellected_unit , SearchType data...){
        va_list equ;
        va_start(equ, data);

        SearchType detected_min=data;
        (*sellected_unit)=0;
        
        for (int i = 0; i < amount-1; i++)
        {
            SearchType checked=va_arg(equ, SearchType);
            if(detected_min>checked){
                detected_min=checked;
                (*sellected_unit)=i+1;
            }
        }
        

        return detected_min;
    };

}

#endif