
#ifndef MINILIB_LIB
#define MINILIB_LIB

#include <cstdlib>

namespace ACD{

    void Seed(long long int new_seed);

    int RandomInt(int min, int max);

    template<typename ArrayType>
    void Shuffle(ArrayType* arr, int size){
        
    };

    template<typename SearchType>
    SearchType Min(int amount, SearchType data...){
        va_list equ;
        va_start(equ, data);

        SearchType detected_min=data;
        
        for (int i = 0; i < amount-1; i++)
        {
            SearchType checked=va_arg(equ, SearchType);
            if(detected_min>checked){
                detected_min=checked;
            }
        }
        

        return detected_min;
    };

}

#endif