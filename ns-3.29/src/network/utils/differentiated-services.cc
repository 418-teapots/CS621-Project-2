

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () {

  // TODO

  TrafficClass trafficClass;
  // q_class.assign(num_queue, &trafficClass)
  q_class.assign(1, &trafficClass);



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
    // uint32_t priority_level;

    return 1;
}

bool 
DiffServ::DoEnqueue (Ptr<Packet> p) {
  printf ("DoEnqueue() in DiffServ start.\n");

  // TODO: Call Enqueue() in TrafficClass object.  
  bool b = q_class[0]->Enqueue(p);
  
  // uint32_t size = p->GetSize ();
  // m_nBytes += size;
  // m_nTotalReceivedBytes += size;

  // m_nPackets++;
  // m_nTotalReceivedPackets++;

  // // NS_LOG_LOGIC ("m_traceEnqueue (p)");
  // m_traceEnqueue (p);

  return b;
}

Ptr<Packet> 
DiffServ::DoDequeue () {
  printf ("DoDequeue() in DiffServ start.\n");

  // TODO
  Ptr<Packet> p = q_class[0]->Dequeue();

  // if (p != 0)
  //   {
  //     NS_ASSERT (m_nBytes.Get () >= p->GetSize ());
  //     NS_ASSERT (m_nPackets.Get () > 0);

  //     m_nBytes -= p->GetSize ();
  //     m_nPackets--;

  //     NS_LOG_LOGIC ("m_traceDequeue (p)");
  //     m_traceDequeue (p);
  //   }

  return p;
}

Ptr<Packet> 
DiffServ::DoRemove () {
    // TODO

  return 0;
}

Ptr<const Packet> 
DiffServ::DoPeek () {
    // TODO

  return 0;
}























}








