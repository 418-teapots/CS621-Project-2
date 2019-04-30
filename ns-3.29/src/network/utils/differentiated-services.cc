#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () 
{
  printf("DiffServ() start. \n");

  // TODO
  // TrafficClass trafficClass;
  // q_class.assign(1, &trafficClass);

}

// 'numQueue' is the number of queues. 
DiffServ::DiffServ (uint32_t numQueue)
{
  printf("DiffServ(uint32_t numQueue) start. \n");
 
  // TODO
  // TrafficClass trafficClass;
  // q_class.assign(numQueue, &trafficClass);
 
}

vector<TrafficClass*>* 
DiffServ::GetQueuesPtr ()
{
  return &q_class;
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
  printf("Enqueue() in DiffServ start.\n");
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
  printf("Dequeue() in DiffServ start.\n");
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

Ptr<const Packet>
DiffServ::Peek (void) const
{
  Ptr<const Packet> p = DoPeek ();

  return p;
}

bool 
DiffServ::DoEnqueue (Ptr<Packet> p) 
{
  printf("DoEnqueue() in DiffServ start.\n");

  uint32_t trafficClassToGo = Classify (p);
  bool b = q_class[trafficClassToGo]->Enqueue (p);
  
  return b;
}

Ptr<Packet> 
DiffServ::DoDequeue ()
{
  printf("DoDequeue() in DiffServ start.\n");

  uint32_t queueIndex = Schedule ();

  Ptr<Packet> p = q_class[queueIndex]->Dequeue ();

  return p;
}

Ptr<Packet> 
DiffServ::DoRemove () 
{
  uint32_t queueIndex = Schedule ();

  Ptr<Packet> p = q_class[queueIndex]->Dequeue ();

  return p;
}

Ptr<const Packet> 
DiffServ::DoPeek (void) const
{
  uint32_t queueIndex = Schedule ();

  Ptr<const Packet> p = q_class[queueIndex]->Peek ();

  return p;
}

uint32_t
DiffServ::Schedule () const
{
  return 0;
}

uint32_t 
DiffServ::Classify (Ptr<Packet> p)
{
  printf("Classify() in DiffServ start. \n");

  printf("q_class.size(): %lu\n", q_class.size());    

  uint32_t defaultQueueIndex;
  for (uint32_t i = 0; i < q_class.size(); ++i)
  {
    if (q_class[i]->match (p)) 
    {
      return i;
    }

    // Get the default queue index. 
    // The packet that does not match any filter goes to the default queue. 
    if (q_class[i]->GetIsDefault ()) 
    {
       defaultQueueIndex = i;
    }
  }

  return defaultQueueIndex;
}







} // namespace ns3










