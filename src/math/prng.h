#pragma once
#include <ctype.h>


unsigned __int32 xorshift128();

void seed_using_rand_xorshift128(unsigned int seed1);
void seed_xorshift128(int x, int y, int z, int w);
double xorshift128d();
float xorshift128f();