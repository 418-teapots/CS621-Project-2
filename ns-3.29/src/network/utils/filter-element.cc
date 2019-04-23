#include "filter-element.h"

namespace ns3 {

// Constructor
FilterElement::FilterElement() {

}
// Destructor
FilterElement::~FilterElement() {

}

bool
FilterElement::match (Ptr<Packet> p) {
  
  return false;
}


} // namespace ns3
