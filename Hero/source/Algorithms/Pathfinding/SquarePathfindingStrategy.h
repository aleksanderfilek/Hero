#pragma once

#include "PathfindingStrategy.h"

namespace Pathfinding
{

	class HERO_API SquarePathfindingStrategy : public PathfindingStrategy
	{
	public:
		virtual class PathNode* ConstructGrid(const Int2& Size) override;
		virtual void GetNeighboursIndexes(const int& CoordIndex, const Int2& Size, Array<int>& CoordIndicies) override;
		virtual class PathNode* GetNodeOnLocation(const Float2& Location, const Int2& Size, float DistanceBetweenNodes, class PathNode* Grid) override;

	};

}