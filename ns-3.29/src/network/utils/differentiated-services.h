#ifndef DIFFERENTIATED_SERVICES_H
#define DIFFERENTIATED_SERVICES_H

#include "queue.h"

namespace ns3 {

template <typename Item>
class DiffServ : public Queue<ns3::Packet>
{
public:
  DiffServ ();
  virtual ~DiffServ ();

  void SetMode (QueueMode mode);
  QueueMode GetMode ();
  Ptr<ns::Packet> Schedule ();
  uint32_t Classify (Ptr<ns::Packet> p);

private:
  QueueMode m_mode;
  vector<TrafficClass*> q_class;

  bool DoEnqueue (Ptr<ns::Packet> p);
  Ptr<ns::Packet> DoDequeue ();
  Ptr<ns::Packet> DoRemove ();
  Ptr<const ns::Packet> DoPeek ();
};

class TrafficClass 
{
public:
  TrafficClass ();
  virtual ~TrafficClass ();

  vector<Filter*> filters;

  bool Enqueue (Ptr<ns3::Packet> p);
  Ptr<ns3::Packet> Dequeue ();
  bool match (Ptr<ns3::Packet> p);

private:
  uint32_t bytes;
  uint32_t packets;
  uint32_t maxPackets;
  uint32_t maxBytes;
  double_t weight;
  uint32_t priority_level;
  bool isDefault;
  std::queue<Ptr<ns3::Packet>> m_queue;
};

class Filter
{
public:
  Filter ();
  virtual ~Filter ();

  std::vector<FilterElement*> elements;

  bool match (Ptr<ns3::Packet> p);
};

class FilterElement
{
public:
  FilterElement ();
  virtual ~FilterElement ();

  virtual bool match(Ptr<ns3::Packet> p)
};

}