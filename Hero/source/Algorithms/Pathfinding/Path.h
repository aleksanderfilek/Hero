#pragma once

#include "../../Definitions.h"
#include "../../Containers/Array.h"
#include "../../Math/Float2.h"

namespace Pathfinding
{

	class HERO_API Path
	{
	private:
		class PathfindingManager* manager = nullptr;

	public:
		Path(class PathfindingManager* Manager);

		bool ReachedTarget = false;
		Array<class PathNode*> Nodes;

		void GetLocations(Array<Float2>& Locations) const;
	};

}