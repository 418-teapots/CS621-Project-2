

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () 
{
  // TODO

  TrafficClass trafficClass;
  q_class.assign(1, &trafficClass);

}

DiffServ::DiffServ (uint32_t numQueue, vector<Filter*> filters)
{
  // TODO

  TrafficClass trafficClass;
  q_class.assign(numQueue, &trafficClass);

  q_class[0]->filters = filters;
  q_class[0]->setWeight(500);


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
  printf ("Enqueue() in DiffServ start.\n");
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
  printf ("Dequeue() in DiffServ start.\n");
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

  uint32_t trafficClassToGo = Classify(p);
  bool b = q_class[trafficClassToGo]->Enqueue(p);
  
  return b;
}

Ptr<Packet> 
DiffServ::DoDequeue ()
{
  printf ("DoDequeue() in DiffServ start.\n");

  // TODO

  Ptr<Packet> p = Schedule();
  return p;
}

Ptr<Packet> 
DiffServ::DoRemove () 
{
  // TODO

  return 0;
}

Ptr<const Packet> 
DiffServ::DoPeek () 
{
  // TODO

  return 0;
}

Ptr<Packet> 
DiffServ::Schedule () 
{
  // TODO
  
  return 0;
}


uint32_t 
DiffServ::Classify (Ptr<Packet> p)
{
  // TODO

  for (uint32_t i = 0; i < q_class.size(); i++)
  {
    if (q_class[i]->match(p)) 
    {
      return i;
    }
  }

  return -1;
}




} // namespace ns3










