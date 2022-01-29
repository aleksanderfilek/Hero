namespace Hero
{
namespace UI
{

HERO void VerticalStack::recalculate()
{
  int y = absolutePosition.y;

  for(auto it: children)
  {
    it.second->absolutePosition = {absolutePosition.x, y};
    y += it.second->size.y + spacing;
  }

  IGroup::recalculate();
}

HERO bool VerticalStack::add(const std::string& name, IElement* element)
{
  IGroup::add(name, element);
  
  recalculate();
}

}
}