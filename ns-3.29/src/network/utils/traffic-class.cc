
#include "queue.h"
#include "differentiated-services.h"
#include <iostream>

// using std::cout;
// using std::endl;

using namespace std;


namespace ns3 {


TrafficClass::TrafficClass () {

}
TrafficClass::~TrafficClass () {

}

bool 
TrafficClass::Enqueue (Ptr<Packet> p) {
  printf("Enqueue() start.");

  if (GetCurrentSize () + p > GetMaxSize ())
    {
      NS_LOG_LOGIC ("Queue full -- dropping pkt");
      DropBeforeEnqueue (p);
      return false;
    }

  m_queue.push (p);

  return true;
}

Ptr<Packet> 
TrafficClass::Dequeue () {
  printf("Dequeue() start.");
  
  Ptr<Packet> p;
  if (!m_queue.empty ()) 
    {
      p = m_queue.front ();
      std::string packetStr = p->ToString ();
      cout << packetStr << endl;

      m_queue.pop ();
    }
  
  return p;
}

bool 
TrafficClass::match (Ptr<Packet> p) {
  // TODO


  return true;
}






} // namespace ns3































