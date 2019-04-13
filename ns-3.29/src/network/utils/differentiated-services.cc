

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () {

  
  // TrafficClass trafficClass;
  // q_class.assign(num_queue, &trafficClass)







}


DiffServ::~DiffServ () {
  
}


// void
// DiffServ::SetMode (QueueMode mode) {

// }

// QueueMode
// DiffServ::GetMode () {

// }

// Ptr<Packet>
// DiffServ::Schedule () {
//     // TODO

//     return 
// }
  
uint32_t
DiffServ::Classify (Ptr<Packet> p) {
    // TODO
    uint32_t priority_level;

    return priority_level;
}



bool
DiffServ::DoEnqueue (Ptr<Packet> p) {

  NS_LOG_FUNCTION (this << p);


  // TODO: Call Enqueue() in TrafficClass object.  
  // bool b = tc.Enqueue(p);
  
  uint32_t size = p->GetSize ();
  m_nBytes += size;
  m_nTotalReceivedBytes += size;

  m_nPackets++;
  m_nTotalReceivedPackets++;

  NS_LOG_LOGIC ("m_traceEnqueue (p)");
  m_traceEnqueue (p);

  return b;
}

Ptr<Packet> 
DiffServ::DoDequeue () {
    // TODO


}

Ptr<Packet> 
DiffServ::DoRemove () {
    // TODO


}

Ptr<const Packet> 
DiffServ::DoPeek () {
    // TODO


}























}








