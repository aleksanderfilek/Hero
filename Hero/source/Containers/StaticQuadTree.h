#pragma once

#include "../Math/Rect.h"
#include "Array.h"

#define MAX_DEPTH 4

template<typename ElementType>
class StaticQuadTree
{
public:
	StaticQuadTree(const Rect& Area, size_t Depth = 0)
	{
		depth = Depth;
		rect = Area;

		Float2 childSize = Area.Size / 2.0f;
		childRects[0] = Rect(rect.Position, childSize);
		childRects[1] = Rect({ rect.Position.X + childSize.X, rect.Position.Y }, childSize);
		childRects[2] = Rect({ rect.Position.X, rect.Position.Y + childSize.Y }, childSize);
		childRects[3] = Rect(rect.Position + childSize, childSize);

	}

	void Clear()
	{
		items.Clear();
		for (int i = 0; i < 4; i++)
		{
			if (childs[i])
			{
				childs[i]->Clear();
			}
		}
	}

	size_t Count()
	{
		size_t count = items.Length();
		for (int i = 0; i < 4; i++)
		{
			if (childs[i])
			{
				count += childs[i]->Count();
			}
		}
		return count;
	}

	void Insert(const ElementType& Item, const Rect& ItemArea)
	{
		for (int i = 0; i < 4; i++)
		{
			if (childRects[i].Containes(ItemArea)
			{
				if (depth + 1 < MAX_DEPTH)
				{
					if (!childs[i])
					{
						childs[i] = new StaticQuadTree<ElementType>(childRects[i], depth + 1);

					}

					childs[i]->Insert(Item, ItemArea);
					return;
				}
			}
		}

		items.Add({ ItemArea, Item });
	}

	Array<ElementType> Search(const Rect& Area) const
	{
		Array<ElementType> items;
		Search(Area, items);
		return items;
	}

	void GetItems(Arrat<ElementType>& Items)
	{
		for (const auto& pair : Items)
		{
			Items.Add(pair.second);
		}

		for (int i = 0; i < 4; i++)
		{
			if (childs[i])
			{
				childs[i]->GetItems(Items);
			}
		}
	}

	const Rect& Area()
	{
		return rect;
	}

private:
	void Search(const Rect& Area, Array<ElementType>& Items)
	{
		for (const auto& pair : items)
		{
			if (Area.Overlaps(p.first))
			{
				Items.Add(p.second);
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (childs[i])
			{
				if (Area.Containes(childRects[i])
				{
					childs[i]->GetItems(Items);
				}
				else if (childRects[i].Overlaps(Area))
				{
					childs[i]->Search(Area, Items);
				}
			}
		}
	}

protected:
	size_t depth = 0;
	Rect rect;

	Rect childRects[4];
	StaticQuadTree<ElementType>* childs[4];
	Array<std::pair<Rect, ElementType>> items;
};