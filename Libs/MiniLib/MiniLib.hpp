
#ifndef MINILIB_LIB
#define MINILIB_LIB

//random float accuracy sellector
#define EXTARPOLATION_MLT 10000

//Used for pseudorandom functions
#include <cstdlib>

//Used for argument list in Min
#include <cstdarg>

namespace ACD{

    void Seed(long long int new_seed);
    int RandomInt(int min, int max);
    float RandomPoint();

    float RandomFloat(int min, int max);

    float RandomFloat(float min, float max);
   
   
    /// @brief Shuffles array members
    /// @tparam ArrayType type of array members
    /// @param arr pointer to array to shuffle
    /// @param size size of input array
    template<typename ArrayType>
    void Shuffle(ArrayType* arr, int size){
        //Generating some random int
        int swipe_times=RandomInt(size, size*5);


        //Switching two random values random amount of times
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

    /// @brief Search minimal value in provided list
    /// @tparam SearchType type of elements in list
    /// @param amount amount of elements in list
    /// @param sellected_unit pointer to int, to store number of sellected element
    /// @param ... list of elements
    /// @return minimal value
    template<typename SearchType>
    SearchType Min(int amount,int *sellected_unit , SearchType data...){
        //Reading value list
        va_list equ;
        va_start(equ, data);

        //Storing first value
        SearchType detected_min=data;
        (*sellected_unit)=0;
        
        //Searching minimal
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