// include needed
#include <utility>
#include <limits>
#include "pch.h"

#define IRESOURCE_EXPORTS
#include "Resource/IResource.hpp"

using namespace Resource;


void IResource::SetFileInfo(const std::string& filepath)
{
	p_directory = filepath.substr(0, filepath.find_last_of('\\'));
	p_name = filepath.substr(p_directory.size() + 1);
}
