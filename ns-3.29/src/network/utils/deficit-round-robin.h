#ifndef DEFICIT_ROUND_ROBIN_H_
#define DEFICIT_ROUND_ROBIN_H_

#include <vector>
#include "differentiated-services.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"

using namespace std;

namespace ns3 {

/**
 * Handles Deficit-Round-Robin (DRR) algorithm with DiffServ class. 
 */
class DRR : public DiffServ 
{
public:

  // static TypeId GetTypeId (void);
  DRR ();
  /** 
   * 'numQueue' is the number of queues. 
   * 'priorityPrams' is a list of priority_level or weight. 
   *  e.g. 300 200 100 
   */
  DRR (uint32_t numQueue, vector<uint32_t> priorityParams, uint32_t maxPacketCount);
  virtual ~DRR ();

  /**
   * \return Returns a queue index whose queue has the next packet to be transmitted.
   */
  uint32_t Schedule ();
  uint32_t ScheduleForPeek () const;

  void SetRoundRobinPointer (uint32_t v);
  uint32_t GetRoundRobinPointer () const;
  uint32_t m_counter;

private: 
  
  /**
   * Indicates queue index whose queue will be serviced next.  
   */ 
  uint32_t m_roundRobinPointer;

};

/**
 * Holds Deficit Counter specifically for Deficit-Round-Robin algorithm, 
 * in addition to the members in TrafficClass. 
 */
class DrrQueue : public TrafficClass
{
public:
  DrrQueue () : 
    m_deficitCounter (0), 
    m_quantumFlag (true)
  {
    printf("DrrQueue constructor start. \n");

  }

  virtual ~DrrQueue () {}
  
  void SetDeficitCounter (uint32_t v)
  {
    m_deficitCounter = v;
  }
  uint32_t GetDeficitCounter ()
  {
    return m_deficitCounter;
  }

  void SetQuantumFlag (bool b)
  {
    m_quantumFlag = b;
  }

  bool GetQuantumFlag () const
  {
    return m_quantumFlag;
  }

private: 

  uint32_t m_deficitCounter;
  bool m_quantumFlag;

};



} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



