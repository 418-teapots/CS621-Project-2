#ifndef FILTER_ELEMENT_H_
#define FILTER_ELEMENT_H_

#include "ns3/pointer.h"
#include "ns3/packet.h"


using namespace std;

namespace ns3 {

/**
 * A base class for a primitive condition to match on. You should write one subclass for every 
 * seven (light purple) boxes in the design diagram. 
 */
class FilterElement
{
public:
  FilterElement ();
  virtual ~FilterElement ();

  virtual bool match(Ptr<Packet> p);
};




} // namespace ns3

#endif /* FILTER_ELEMENT_H_ */


