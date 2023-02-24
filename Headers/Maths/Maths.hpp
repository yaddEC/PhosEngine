#pragma once

#ifdef MATHS_EXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif

extern "C" MATHS_API int calcul(int a, int b);