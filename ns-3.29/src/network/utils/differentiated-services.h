#ifndef DIFFERENTIATED_SERVICES_H
#define DIFFERENTIATED_SERVICES_H

#include "queue.h"
#include <vector>
#include <queue>

using namespace std;

namespace ns3 {

/**
 * A base class for a primitive condition to match on. You should write one subclass for every 
 * seven (light purple) boxes in the design diagram. 
 */
class FilterElement
{
public:
  FilterElement ();
  virtual ~FilterElement ();

  virtual bool match(Ptr<Packet> p);
};

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
  std::vector<FilterElement*> elements;

  bool match (Ptr<Packet> p);
};

/**
 * Defines the characteristics of a queue.
 */
class TrafficClass 
{
public:
  TrafficClass ();
  virtual ~TrafficClass ();

  /**
   * A collection of conditions as Filters, any of which should match in order to trigger match.
   */
  vector<Filter*> filters;

  bool Enqueue (Ptr<Packet> p);
  Ptr<Packet> Dequeue ();
  bool match (Ptr<Packet> p);

private:
  /**
   * the count of bytes in the queue.
   */
  uint32_t bytes;
  /**
   * the count of packets in the queue.
   */
  uint32_t packets;
  /**
   * the maximum number of packets allowed in the queue.
   */
  uint32_t maxPackets;
  /**
   * the maximum number of bytes allowed in the queue. 
   */
  uint32_t maxBytes;
  /**
   * applicable if the QoS mechanism uses weight.
   */
  double weight;
  /**
   * applicable if the QoS mechanism uses priority level.
   */
  uint32_t priority_level;
  /**
   *
   */
  bool isDefault;
  /**
   *
   */
  queue<Ptr<Packet>> m_queue;
};

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

  bool DoEnqueue (Ptr<Packet> p);
  Ptr<Packet> DoDequeue ();
  Ptr<Packet> DoRemove ();
  Ptr<const Packet> DoPeek ();
};

} // namespace ns3

#endif /* DIFFERENTIATED_SERVICES_H */
