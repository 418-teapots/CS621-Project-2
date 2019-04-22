
#include "traffic-class.h"
#include "queue.h"
// #include "differentiated-services.h"
#include <iostream>

using namespace std;

namespace ns3 {

TrafficClass::TrafficClass () : 
  bytes (0),
  packets (0),
  maxPackets (1000),
  maxBytes (10000),
  weight(0), 
  priority_level(0)
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
TrafficClass::setWeight (double w) 
{
  weight = w;
}

double 
TrafficClass::getWeight () 
{
  return weight;
}

void 
TrafficClass::setPriorityLevel (uint32_t pl) 
{
  priority_level = pl;
}

uint32_t 
TrafficClass::getPriorityLevel () 
{
  return priority_level;
}

bool
TrafficClass::getIsDefault()
{
  return isDefault;
}

void
TrafficClass::setIsDefault(bool b)
{
  isDefault = b;
}




bool 
TrafficClass::Enqueue (Ptr<Packet> p) 
{
  printf ("Enqueue() in TrafficClass start.\n");

  // Check if the queue is full. 
  if (packets >= maxPackets)
    {
      printf ("Queue is full.\n");

      return false;
    }

  m_queue.push (p);

  packets++;

  return true;
}

Ptr<Packet> 
TrafficClass::Dequeue () 
{
  printf ("Dequeue() in TrafficClass start.\n");
  
  Ptr<Packet> p;
  if (m_queue.empty ()) 
    {
      printf ("Queue is empty.\n");
      return 0;
    }

  p = m_queue.front ();
  m_queue.pop ();
  packets--;

  string packetStr = p->ToString ();
  cout << "Packet dequeued: " << packetStr << endl;
  
  return p;
}

Ptr<Packet> 
TrafficClass::Peek () 
{  
  Ptr<Packet> p;
  if (m_queue.empty ()) 
    {
      printf ("Queue is empty.\n");
      return 0;
    }

  p = m_queue.front ();

  string packetStr = p->ToString ();
  cout << "Packet peeked: " << packetStr << endl;
  
  return p;
}

// Return true if at least one Filter is true, otherwise false. 
bool 
TrafficClass::match (Ptr<Packet> p) 
{
  bool isMaching = false;

  for (uint32_t i = 0; i < filters.size(); i++)
  {
    isMaching = filters[i]->match(p);
    if (isMaching)
    {
      return true;
    }
  }

  return false;
}


} // namespace ns3































