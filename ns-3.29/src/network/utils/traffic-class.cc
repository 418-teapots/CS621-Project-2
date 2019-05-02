#include "traffic-class.h"
#include "queue.h"
#include <iostream>

using namespace std;

namespace ns3 {

TrafficClass::TrafficClass () : 
  bytes (0),
  packets (0),
  maxPackets (1000),
  maxBytes (10000),
  weight (0), 
  priority_level (0),
  isDefault (false)
{

}


// Copy Constructor. 
// TrafficClass::TrafficClass (const TrafficClass& tc) 
// {

// }

TrafficClass::~TrafficClass () 
{

}

void 
TrafficClass::SetPacketsCount (uint32_t packetsCount) 
{
  packets = packetsCount;
}

uint32_t 
TrafficClass::GetPacketsCount () 
{
  return packets;
}

void 
TrafficClass::SetWeight (double w) 
{
  weight = w;
}

double 
TrafficClass::GetWeight () 
{
  return weight;
}

void 
TrafficClass::SetPriorityLevel (uint32_t pl) 
{
  priority_level = pl;
}

uint32_t 
TrafficClass::GetPriorityLevel () 
{
  return priority_level;
}

void
TrafficClass::SetIsDefault(bool b)
{
  isDefault = b;
}

bool
TrafficClass::GetIsDefault ()
{
  return isDefault;
}

bool 
TrafficClass::Enqueue (Ptr<Packet> p) 
{
  printf("Enqueue() in TrafficClass start.\n");

  // Check if the queue is full. 
  if (packets >= maxPackets)
    {
      printf("Queue is full.\n");

      return false;
    }

  m_queue.push(p);

  packets++;

  return true;
}

Ptr<Packet> 
TrafficClass::Dequeue () 
{
  printf("Dequeue() in TrafficClass start.\n");
  
  Ptr<Packet> p;
  if (m_queue.empty()) 
    {
      printf("Queue is empty.\n");
      return 0;
    }

  p = m_queue.front();
  m_queue.pop ();
  packets--;

  // string packetStr = p->ToString ();
  // cout << "Packet dequeued: " << packetStr << endl;
  
  return p;
}

Ptr<Packet> 
TrafficClass::Peek () 
{  
  Ptr<Packet> p;
  if (m_queue.empty()) 
    {
      printf("Queue is empty.\n");
      return 0;
    }

  p = m_queue.front();

  // string packetStr = p->ToString ();
  // cout << "Packet peeked: " << packetStr << endl;
  
  return p;
}

// Return true if at least one Filter is true, otherwise false. 
bool 
TrafficClass::match (Ptr<Packet> p) 
{
  printf("match() in TrafficClass start.\n");

  bool isMatchedFilter = false;

  printf("filters.size(): %lu\n", filters.size());    

  for (uint32_t i = 0; i < filters.size(); i++)
  {
    isMatchedFilter = filters[i]->match (p);

    printf("isMatchedFilter: %d\n", isMatchedFilter);

    if (isMatchedFilter)
    {
      return true;
    }
  }

  return false;
}


} // namespace ns3