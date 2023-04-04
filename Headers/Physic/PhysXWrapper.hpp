#pragma once
#include <Physx/PxPhysicsAPI.h>
#include <memory>

#ifdef PHYSXWRAPPER_EXPORTS
#define PHYSXWRAPPER_API __declspec(dllexport)
#else
#define PHYSXWRAPPER_API __declspec(dllimport)
#endif