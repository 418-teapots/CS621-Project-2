
#include "filter.h"

namespace ns3 {

// Constructor
Filter::Filter () {

}
// Destructor
Filter::~Filter () {
}

bool
Filter::match (Ptr<Packet> p) {
  // TODO
  
  // bool isMaching = false;

  // for (int i = 0; i < elements.size(); i++)
  // {
  //   isMaching = element[i].mactch();
  //   if (!isMaching)
  //   {
  //     return false;
  //   }
  // }

  return true;
}

} // namespace ns3
