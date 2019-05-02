#ifndef STRICT_PRIORITY_QUEUE_H
#define STRICT_PRIORITY_QUEUE_H

#include "differentiated-services.h"
#include "traffic-class.h"

namespace ns3 {

class SPQ : public DiffServ
{
public:

  // static TypeId GetTypeId (void);
  SPQ ();
  SPQ (uint32_t highPort, uint32_t lowPort);
  virtual ~SPQ ();

  uint32_t Schedule ();
  uint32_t Classify (Ptr<ns3::Packet> p);

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

  ns3::DiffServ::QueueMode queueMode;
  virtual bool DoEnqueue (Ptr<ns3::Packet> p);
  virtual Ptr<ns3::Packet> DoDequeue ();
  virtual Ptr<ns3::Packet> DoRemove ();
  virtual Ptr<const ns3::Packet> DoPeek ();
};

} // namespace ns3

#endif
