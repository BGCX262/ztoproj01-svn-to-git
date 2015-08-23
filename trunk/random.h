#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED
#include <time.h>

using namespace std;


class random{
    static bool wasRandomized;
    static void randomize(){
        if(wasRandomized == false){
            wasRandomized = true;
            srand(time(NULL));
        };
    };
    public:
        random(){};
        int operator()(void){ random::randomize(); return rand(); };
        int operator()(int upperBound){ random::randomize(); return rand()%(upperBound+1); };
        int operator()(int lowerBound,int upperBound){ random::randomize(); return rand()%(upperBound - lowerBound + 1) + lowerBound; };
};

bool random::wasRandomized = false;

#endif // RANDOM_H_INCLUDED
