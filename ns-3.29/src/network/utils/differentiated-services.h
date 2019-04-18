#ifndef DIFFERENTIATED_SERVICES_H_
#define DIFFERENTIATED_SERVICES_H_

#include "traffic-class.h"
#include "queue.h"
#include <vector>
#include <queue>

using namespace std;

namespace ns3 {



/**
 * DiffServ class provides basic functionalities required to simulate differentiated services:
 *
 * 1. Classification - The classify function utilizes filter aspect to sort the traffic packets 
 * into appropriate traffic queues.
 * 2. Scheduling - The schedule function carries out designed Quality-of-Service (QoS) algorithm 
 * to schedule which traffic queue to be served at the time.
 */
class DiffServ : public Queue<Packet>
{
public:
  DiffServ ();
  virtual ~DiffServ ();

  // void SetMode (QueueMode mode);
  // QueueMode GetMode ();
  /**
   * \return Returns a packet to transmit.
   */
  Ptr<Packet> Schedule ();
  /**
   * \brief Takes a packet and returns an integer.
   * \return An integer
   */
  uint32_t Classify (Ptr<Packet> p);

private:
  /**
   * The QueueMode specifies whether service is in byte mode or packet mode.
   */
  // QueueMode m_mode;

  /**
   * The vector (array) of TrafficClass pointers. 
   * setMode()/getMode() - the accessor and modifier for private variable m mode.
   */
  vector<TrafficClass*> q_class;

  virtual bool DoEnqueue (Ptr<Packet> p);
  virtual Ptr<Packet> DoDequeue ();
  Ptr<Packet> DoRemove ();
  Ptr<const Packet> DoPeek ();
};

} // namespace ns3

#endif /* DIFFERENTIATED_SERVICES_H_ */
