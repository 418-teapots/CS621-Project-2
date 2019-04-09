

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ (int num_queue) {
  NS_LOG_FUNCTION (this);

  
  TrafficClass trafficClass;

  q_class.assign(num_queue, &trafficClass)







}


DDiffServ::~DiffServ () {
  NS_LOG_FUNCTION (this);
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
    // TODO
    NS_LOG_FUNCTION (this << p);
 
   if (GetCurrentSize () + p > GetMaxSize ())
     {
       NS_LOG_LOGIC ("Queue full -- dropping pkt");
       DropBeforeEnqueue (p);
       return false;
     }
 
   m_packets.insert (pos, p);
 
   uint32_t size = p->GetSize ();
   m_nBytes += size;
   m_nTotalReceivedBytes += size;
 
   m_nPackets++;
   m_nTotalReceivedPackets++;
 
   NS_LOG_LOGIC ("m_traceEnqueue (p)");
   m_traceEnqueue (p);
 
   return true;


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








