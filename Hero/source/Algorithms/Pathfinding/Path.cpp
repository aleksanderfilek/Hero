#include "Path.h"
#include "PathNode.h"
#include "PathfindingManager.h"

namespace Pathfinding
{

	Path::Path(class PathfindingManager* Manager) : manager(Manager)
	{

	}

	void Path::GetLocations(Array<Float2>& Locations) const
	{
		Locations = Array<Float2>(Nodes.Length());
		Int2 size = manager->GetSize();
		float distanceBetweenNodes = manager->GetDistanceBetweenNodes();

		for (PathNode* node : Nodes)
		{
			int coordX = node->coordsIndex % size.X;
			int coordY = node->coordsIndex / size.X;

			Float2 location;
			location.X = coordX * distanceBetweenNodes + 25;
			location.Y = coordY * distanceBetweenNodes + 25;

			Locations.Add(location);
		}
	}
}
