

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () {

  // TODO

  TrafficClass trafficClass;
  // q_class.assign(num_queue, &trafficClass)
  q_class.assign(1, &trafficClass);



}


DiffServ::~DiffServ () 
{

  // m_mode = QUEUE_MODE_PACKETS;

}

// void 
// DiffServ::SetMode (QueueMode mode)
// {
//   m_mode = mode;
// }
  
// QueueMode 
// DiffServ::GetMode ()
// {
//   return m_mode;
// }

bool
DiffServ::Enqueue (Ptr<Packet> packet)
{
  printf ("DoEnqueue() in DiffServ start.\n");
  bool b = DoEnqueue (packet);
  
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
DiffServ::Dequeue (void)
{
  printf ("DoEnqueue() in DiffServ start.\n");
  Ptr<Packet> p = DoDequeue ();
  
  // uint32_t size = p->GetSize ();
  // m_nBytes += size;
  // m_nTotalReceivedBytes += size;

  // m_nPackets++;
  // m_nTotalReceivedPackets++;

  // // NS_LOG_LOGIC ("m_traceEnqueue (p)");
  // m_traceEnqueue (p);

  return p;
}

Ptr<Packet>
DiffServ::Remove (void)
{
  Ptr<Packet> p = DoRemove ();

  return p;
}

// TODO error. 
// Ptr<const Packet>
// DiffServ::Peek (void) const
// {
//   return DoPeek ();
// }

bool 
DiffServ::DoEnqueue (Ptr<Packet> p) 
{
  printf ("DoEnqueue() in DiffServ start.\n");

  return false;
}

Ptr<Packet> 
DiffServ::DoDequeue ()
{
  printf ("DoDequeue() in DiffServ start.\n");

  return 0;
}

Ptr<Packet> 
DiffServ::DoRemove () 
{
  return 0;
}

Ptr<const Packet> 
DiffServ::DoPeek () 
{

  return 0;
}

Ptr<Packet> 
DiffServ::Schedule () 
{
  return 0;
}

uint32_t 
DiffServ::Classify (Ptr<Packet> p)
{
  return 0;
}




} // namespace ns3










