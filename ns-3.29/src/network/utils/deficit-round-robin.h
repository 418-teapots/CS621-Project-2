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

  uint32_t Schedule ();

  void setRoundRobinPointer (uint32_t v);
  uint32_t getRoundRobinPointer ();

private: 
  
  /**
   *  A list of queue indices whose queue contains at least one packet. 
   */ 
  // vector<uint32_t> activeQueueList;
  
  /**
   * Indicates queue index whose queue will be serviced next.  
   */ 
  uint32_t roundRobinPointer;

};

/**
 * Holds Deficit Counter specifically for Deficit-Round-Robin algorithm, 
 * in addition to the members in TrafficClass. 
 */
class DRRQueue : public TrafficClass
{
public:
  DRRQueue () : 
    deficitCounter (0)
  {

  }

  virtual ~DRRQueue () {}
  
  void setDeficitCounter (uint32_t v)
  {
    deficitCounter = v;
  }
  uint32_t getDeficitCounter ()
  {
    return deficitCounter;
  }

private: 

  uint32_t deficitCounter;

};



} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



