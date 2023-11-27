#pragma once

#include "PathfindingStrategy.h"
#include "../../Containers/Map.h"

namespace Pathfinding
{

	class HERO_API PathfindingManager
	{
	private:
		PathfindingStrategy* strategy;
		Int2 size;
		float distanceBetweenNodes;

		class PathNode* nodes;

	public:
		PathfindingManager(PathfindingStrategy* Strategy, Int2 Size, float DistanceBetweenNodes);
		~PathfindingManager();

		Int2 GetSize() const { return size; }
		float GetDistanceBetweenNodes() const { return distanceBetweenNodes; }

		class Path* FindPath(class PathNode* StartNode, class PathNode* TargetNode);
		class PathNode* GetNodeOnLocation(const Float2& Location) const;

	private:
		class Path* TraverseInReversePath(class PathNode* CurrentNode, Map<PathNode*, PathNode*>& ClosedSet);
		void GetNodeNeighbours(class PathNode* Node, bool UnblockedOnly, Array<class PathNode*>& Neighbours);
		float GetHeuristicCost(class PathNode* FromNode, class PathNode* ToNode);

	};

}