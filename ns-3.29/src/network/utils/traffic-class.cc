
#include "traffic-class.h"
#include "queue.h"
// #include "differentiated-services.h"
#include <iostream>

using namespace std;


namespace ns3 {


TrafficClass::TrafficClass () {

}
// Copy Constructor. 
TrafficClass::TrafficClass (const TrafficClass& tc) {

}

TrafficClass::~TrafficClass () {

}

bool 
TrafficClass::Enqueue (Ptr<Packet> p) {
  printf ("Enqueue() in TrafficClass start.\n");

  // Check if the queue is full. 
  if (packets >= maxPackets)
    {
      printf ("Queue is full.\n");

      return false;
    }

  m_queue.push (p);

  return true;
}

Ptr<Packet> 
TrafficClass::Dequeue () {
  printf ("Dequeue() in TrafficClass start.\n");
  
  Ptr<Packet> p;
  if (m_queue.empty ()) 
    {
      printf ("Queue is empty.\n");
      return 0;
    }

  p = m_queue.front ();
  m_queue.pop ();

  std::string packetStr = p->ToString ();
  cout << packetStr << endl;
  
  return p;
}

bool 
TrafficClass::match (Ptr<Packet> p) {
  // TODO


  return true;
}






} // namespace ns3































