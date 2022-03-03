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

    // Generates a memory leak on demand (for when you need to leak memory)
    static void memoryLeak()
    {
        int* lol[100];
        for(int i = 0; i < 100; i++)
        {
            lol[i] = new int(5);
        }
    }

    // Useful function
    static void doNothingAtAll(int gg)
    {
        int lol = 3;

        if(gg <= 1)
            return;
        else
            doNothingAtAll(gg - 1);
    }
};

#endif
