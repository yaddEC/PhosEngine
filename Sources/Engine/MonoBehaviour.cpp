// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#define MONOBEHAVIOUR_EXPORTS
#include "Engine/MonoBehaviour.hpp"

Engine::MonoBehaviour::MonoBehaviour(bool _renderingComponent)
	: renderingComponent(_renderingComponent)
{}

Engine::MonoBehaviour::~MonoBehaviour()
{}
