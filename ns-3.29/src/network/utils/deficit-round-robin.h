

#ifndef DEFICIT_ROUND_ROBIN_H_
#define DEFICIT_ROUND_ROBIN_H_

#include <vector>
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
  DRR (vector<uint32_t> priorityPrams);
  virtual ~DRR ();

  Ptr<Packet> Schedule ();
  void setDeficitCounter (int n);
  int getDeficitCounter ();
  // void setQuantum (uint32_t quantum);
  // uint32_t getQuantum ();

private: 
  
  vector<uint32_t> activeQueueList;
  int deficitCounter;
  // uint32_t quantum;

};


} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



