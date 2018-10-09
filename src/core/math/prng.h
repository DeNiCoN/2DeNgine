#pragma once
#include <ctype.h>


unsigned __int32 xorshift128();

void seedUsingRandXorshift128(unsigned int seed1);
void seedXorshift128(int x, int y, int z, int w);
double xorshift128d();
float xorshift128f();