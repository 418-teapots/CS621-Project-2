

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
  /** 
   * 'numQueue' is the number of queues. 
   * 'priorityPrams' is a list of priority_level or weight. 
   *  e.g. 300 200 100 
   */
  DRR (uint32_t numQueue, vector<uint32_t> priorityPrams);
  virtual ~DRR ();

  Ptr<Packet> Schedule ();

private: 
  
  /**
   *  A list of queue indices whose queue contains at least one packet. 
   */ 
  vector<uint32_t> activeQueueList;

  uint32_t roundRobinPtr;

};


class DRRQueue : public TrafficClass
{
public:
  DRRQueue () : 
    deficitCounter (0)
  {

  }

  virtual ~DRRQueue () {}
  
  void setDeficitCounter (int n)
  {
    deficitCounter = n;
  }
  int getDeficitCounter ()
  {
    return deficitCounter;
  }

private: 

  int deficitCounter;


};



} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



