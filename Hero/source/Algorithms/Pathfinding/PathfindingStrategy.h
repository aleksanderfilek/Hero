#pragma once

#include "../../Definitions.h"
#include "../../Math/Int2.h"
#include "../../Math/Float2.h"
#include "../../Containers/Array.h"

namespace Pathfinding
{

	class PathfindingStrategy
	{
	public:
		virtual ~PathfindingStrategy(){}
		virtual class PathNode* ConstructGrid(const Int2& Size) = 0;
		virtual void GetNeighboursIndexes(const int& CoordIndex, const Int2& Size, Array<int>& CoordIndicies) = 0;
		virtual class PathNode* GetNodeOnLocation(const Float2& Location, const Int2& Size, float DistanceBetweenNodes, class PathNode* Grid) = 0;
	};

}