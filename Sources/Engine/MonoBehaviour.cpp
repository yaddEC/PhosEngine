// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Engine/MonoBehaviour.hpp"

Engine::MonoBehaviour::MonoBehaviour(bool _renderingComponent)
	: renderingComponent(_renderingComponent)
{}

Engine::MonoBehaviour::~MonoBehaviour()
{}

void Engine::MonoBehaviour::OnInspector()
{
	GetMetaData().GUIUpdate(this);
}
