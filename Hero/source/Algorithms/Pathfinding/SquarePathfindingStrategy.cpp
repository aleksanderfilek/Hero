#include "SquarePathfindingStrategy.h"
#include "PathNode.h"

namespace Pathfinding
{

	class PathNode* SquarePathfindingStrategy::ConstructGrid(const Int2& Size)
	{
		int nodesCount = Size.X * Size.Y;
		PathNode* nodes = new PathNode[nodesCount];

		for (int i = 0; i < nodesCount; i++)
		{
			nodes[i].coordsIndex = i;
		}

		return nodes;
	}

	void SquarePathfindingStrategy::GetNeighboursIndexes(const int& CoordIndex, const Int2& Size, Array<int>& CoordIndicies)
	{
		CoordIndicies = Array<int>(8);

		int coordX = CoordIndex % Size.X;
		int coordY = CoordIndex / Size.X;

		for (int y = -1; y <= 1; y++)
		{
			int yCoord = coordY + y;
			if (yCoord < 0 || yCoord >= Size.Y)
				continue;

			for (int x = -1; x <= 1; x++)
			{
				if (y == 0 && x == 0)
					continue;

				int xCoord = coordX + x;

				if (xCoord < 0 || xCoord >= Size.X)
					continue;

				CoordIndicies.Add(yCoord * Size.X + xCoord);
			}
		}
	}

	class PathNode* SquarePathfindingStrategy::GetNodeOnLocation(const Float2& Location, const Int2& Size, float DistanceBetweenNodes, class PathNode* Grid)
	{
		int x = (int)floorf(Location.X / (Size.X * DistanceBetweenNodes));
		int y = (int)floorf(Location.Y / (Size.Y * DistanceBetweenNodes));

		if (x < 0 || x >= Size.X || y < 0 || y >= Size.Y)
		{
			return nullptr;
		}

		return &Grid[y * Size.X + x];
	}

}