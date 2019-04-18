#ifndef TRAFFIC_CLASS_H
#define TRAFFIC_CLASS_H

// #include "differentiated-services.h"
#include "filter.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"
#include <vector>
#include <queue>

using namespace std;

namespace ns3 {

/**
 * Defines the characteristics of a queue.
 */
class TrafficClass 
{
public:
  TrafficClass ();
  TrafficClass (const TrafficClass& tc);
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


} // namespace ns3

#endif /* TRAFFIC_CLASS_H */


