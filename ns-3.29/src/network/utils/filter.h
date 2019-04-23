#ifndef FILTER_H_
#define FILTER_H_

#include "filter-element.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"
#include <vector>

using namespace std;

namespace ns3 {

/**
 * A collection of conditions as FilterElements, all of which should match in order to trigger match.
 */
class Filter
{
public:
  Filter ();
  virtual ~Filter ();

  /**
   * the array of pointers to FilterElement.
   */
  vector<FilterElement*> elements;

  /**
   * \return Return true if all the FilterElement is true, otherwise false.
   */
  bool match (Ptr<Packet> p);
};

} // namespace ns3

#endif /* FILTER_H_ */


