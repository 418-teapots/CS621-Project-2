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
  DiffServ (uint32_t numQueue);
  virtual ~DiffServ ();

  /**
   * setMode()/getMode() - the accessor and modifier for private variable m mode.
   */
  // void SetMode (QueueMode mode);
  // QueueMode GetMode ();


  vector<TrafficClass*>* getQueuesPtr();


  /**
   * \return Returns a queue index whose queue has the next packet to be transmitted.
   */
  virtual uint32_t Schedule () const;

  /**
   * \brief Takes a packet and returns an integer.
   * \return An integer
   */
  uint32_t Classify (Ptr<Packet> p);

  virtual bool Enqueue (Ptr<Packet> p);
  virtual Ptr<Packet> Dequeue (void);
  virtual Ptr<Packet> Remove (void);
  virtual Ptr<const Packet> Peek (void) const;

private:
  /**
   * The QueueMode specifies whether service is in byte mode or packet mode.
   */
  // QueueMode m_mode;

  /**
   * The vector (array) of TrafficClass pointers. 
   */
  vector<TrafficClass*> q_class;

  bool DoEnqueue (Ptr<Packet> p);
  Ptr<Packet> DoDequeue ();
  Ptr<Packet> DoRemove ();
  Ptr<const Packet> DoPeek (void) const;
};

} // namespace ns3

#endif /* DIFFERENTIATED_SERVICES_H_ */
































