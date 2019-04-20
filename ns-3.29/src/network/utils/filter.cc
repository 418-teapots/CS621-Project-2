
#include "filter.h"

namespace ns3 {

// Constructor
Filter::Filter () {

}
// Destructor
Filter::~Filter () {
}

// Return true if all the FilterElement is true, otherwise false. 
bool
Filter::match (Ptr<Packet> p) 
{
  bool isMaching = false;

  for (uint32_t i = 0; i < elements.size(); i++)
  {
    isMaching = elements[i]->match(p);
    if (!isMaching)
    {
      return false;
    }
  }

  return true;
}

} // namespace ns3
