

#ifndef DEFICIT_ROUND_ROBIN_H_
#define DEFICIT_ROUND_ROBIN_H_

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
  uint32_t Classify (Ptr<Packet> p);

private:

  /**
   * The vector (array) of TrafficClass pointers. 
   */
  // vector<TrafficClass*> q_class;

  enum Priority 
  {
    HIGH_PRIORITY,
    LOW_PRIORITY
  };

  // DiffServ::QueueMode queueMode;
  virtual bool DoEnqueue (Ptr<Packet> p);
  virtual Ptr<Packet> DoDequeue ();
  virtual Ptr<Packet> DoRemove ();
  virtual Ptr<const Packet> DoPeek ();
};


} // namespace ns3

#endif /* DEFICIT_ROUND_ROBIN_H_ */



