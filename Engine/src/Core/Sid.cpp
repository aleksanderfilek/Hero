#include"Sid.hpp"

namespace Hero
{

HERO std::ostream& operator<< (std::ostream& stream, const Sid& sid)
{
  #ifdef HERO_DEBUG
  stream<<std::string(sid.text);
  #else
  stream<<std::to_string(sid.id);
  #endif
  return stream;
}

}