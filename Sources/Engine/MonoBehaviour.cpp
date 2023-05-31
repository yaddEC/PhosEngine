// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Engine/MonoBehaviour.hpp"

Engine::MonoBehaviour::MonoBehaviour(bool _renderingComponent, bool _overrideTransform)
	: renderingComponent(_renderingComponent), overrideTransform(_overrideTransform)
{}


Engine::MonoBehaviour::~MonoBehaviour()
{}

void Engine::MonoBehaviour::OnInspector()
{
	GetMetaData().GUIUpdate(this);
}
