#pragma once

#ifdef PHOSENGINE_EXPORTS
#define PHOSENGINE_API __declspec(dllexport)
#else
#define PHOSENGINE_API __declspec(dllimport)
#endif