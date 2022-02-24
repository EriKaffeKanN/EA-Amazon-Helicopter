#ifndef UTIL_H_
#define UTIL_H_

enum class Direction
{
    LEFT, RIGHT
};

struct UtilFunctions
{
    static int getMaxValue(int* array, int arrayLength)
    {
        int max = array[0];
        for(int i = 1; i < arrayLength; i++)
        {
            if(array[i] > max)
                max = array[i];
        }
        return max;
    }
};

#endif
