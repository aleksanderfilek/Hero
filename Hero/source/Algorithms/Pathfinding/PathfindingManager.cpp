#include "PathfindingManager.h"
#include "PathNode.h"
#include "Path.h"
#include "../../Containers/Set.h"

namespace Pathfinding
{

	PathfindingManager::PathfindingManager(PathfindingStrategy* Strategy, Int2 Size, float DistanceBetweenNodes)
		: strategy(Strategy), size(Size), distanceBetweenNodes(DistanceBetweenNodes)
	{
		nodes = strategy->ConstructGrid(size);
	}

	PathfindingManager::~PathfindingManager()
	{
		delete[] nodes;
	}

	class Path* PathfindingManager::FindPath(class PathNode* StartNode, class PathNode* TargetNode)
	{
		if (!StartNode || !TargetNode)
		{
			return nullptr;
		}

		if (StartNode == TargetNode)
		{
			return nullptr;
		}

		Set<PathNode*> openSet;
		Map<PathNode*, float> gScoreMap;
		Map<PathNode*, float> fScoreMap;
		Map<PathNode*, PathNode*> closedSet;

		openSet.Add(StartNode);
		gScoreMap.Add(StartNode, 0.0f);
		fScoreMap.Add(StartNode, GetHeuristicCost(StartNode, TargetNode));

		while (openSet.Length() > 0)
		{
			float minimumFScore = std::numeric_limits<float>::max();
			PathNode* currentNode = nullptr;
			for (PathNode* node : openSet)
			{
				float value = fScoreMap[node];
				if (value < minimumFScore)
				{
					minimumFScore = value;
					currentNode = node;
				}
			}

			if (currentNode == TargetNode)
			{
				return TraverseInReversePath(currentNode, closedSet);
			}

			openSet.Remove(currentNode);

			float currentNodeGScore = gScoreMap[currentNode];

			Array<PathNode*> neighbours;
			GetNodeNeighbours(currentNode, !TargetNode->blocked, neighbours);
			for (PathNode* neighbour : neighbours)
			{
				if (neighbour->blocked)
				{
					if (neighbour == TargetNode)
					{
						Path* path = TraverseInReversePath(currentNode, closedSet);
						path->ReachedTarget = false;
						return path;
					}
					continue;
				}


				float tentativeGScore = 1.0f + currentNodeGScore;

				float neighbourGScore = std::numeric_limits<int>::max();;
				if (gScoreMap.Contains(neighbour))
				{
					neighbourGScore = gScoreMap[neighbour];
				}

				if (tentativeGScore < neighbourGScore)
				{
					closedSet.Add(neighbour, currentNode);
					gScoreMap.Add(neighbour, tentativeGScore);
					fScoreMap.Add(neighbour, tentativeGScore + GetHeuristicCost(neighbour, TargetNode));

					if (!openSet.Contains(neighbour))
					{
						openSet.Add(neighbour);
					}
				}
			}
		}

		return nullptr;
	}

	class Path* PathfindingManager::TraverseInReversePath(class PathNode* CurrentNode, Map<PathNode*, PathNode*>& ClosedSet)
	{
		Array<PathNode*> reversedPathNodes(50, 10);
		PathNode* currentNode = CurrentNode;

		reversedPathNodes.Add(currentNode);
		while (ClosedSet.Contains(currentNode))
		{
			currentNode = ClosedSet[currentNode];
			reversedPathNodes.Add(currentNode);
		}

		int nodesNumber = reversedPathNodes.Length();
		Array<PathNode*> pathNodes(nodesNumber);
		for (int i = 0; i < nodesNumber; i++)
		{
			pathNodes.Add(reversedPathNodes[nodesNumber - i - 1]);
		}

		Path* path = new Path(this);
		path->Nodes = pathNodes;
		return path;
	}

	void PathfindingManager::GetNodeNeighbours(class PathNode* Node, bool UnblockedOnly, Array<class PathNode*>& Neighbours)
	{
		Array<int> coordIndicies;
		strategy->GetNeighboursIndexes(Node->coordsIndex, size, coordIndicies);

		Neighbours = Array<PathNode*>(coordIndicies.Length());

		for (int index : coordIndicies)
		{
			PathNode* node = &nodes[index];

			if (!(node->blocked && UnblockedOnly))
			{
				Neighbours.Add(node);
			}
		}
	}

	float PathfindingManager::GetHeuristicCost(class PathNode* FromNode, class PathNode* ToNode)
	{
		Int2 fromCoords(FromNode->coordsIndex % size.X, FromNode->coordsIndex / size.X);
		Int2 toCoords(ToNode->coordsIndex % size.X, ToNode->coordsIndex / size.X);
		Int2 coordDiff = fromCoords - toCoords;
		return fabs(coordDiff.X) + fabs(coordDiff.Y);
	}

	class PathNode* PathfindingManager::GetNodeOnLocation(const Float2& Location) const
	{
		return strategy->GetNodeOnLocation(Location, size, distanceBetweenNodes, nodes);
	}

}