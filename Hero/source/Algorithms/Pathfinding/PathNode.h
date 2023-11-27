#pragma once

#include "../../Definitions.h"

namespace Pathfinding
{

	class HERO_API PathNode
	{
	public:
		int coordsIndex = 1;
		bool blocked = false;
	};

}