

#ifndef DEFICIT_ROUND_ROBIN_H_
#define DEFICIT_ROUND_ROBIN_H_

#include "differentiated-services.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"

using namespace std;

namespace ns3 {

class DRR : public DiffServ 
{
public:

  static TypeId GetTypeId (void);
  DRR ();
  virtual ~DRR ();

  Ptr<Packet> Schedule ();

};


} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



