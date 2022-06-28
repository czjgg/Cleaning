#ifndef CPP_PRIMER_PRACTICE_CHAPTER6_H
#define CPP_PRIMER_PRACTICE_CHAPTER6_H

int fact(int val);
int func();

template <typename T>
T abs(T i)
{
    return i >= 0 ? i : -i;
}

#endif