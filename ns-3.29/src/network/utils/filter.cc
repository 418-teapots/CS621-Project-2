
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

  return false;
}

} // namespace ns3
