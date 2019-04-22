

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () 
{
  printf("DiffServ() start.");

  TrafficClass trafficClass;
  q_class.assign(1, &trafficClass);

}


// 'numQueue' is the number of queues. 
// 'priorityPrams' is a list of priority_level or weight. 
// e.g. 300 200 100 
DiffServ::DiffServ (uint32_t numQueue, vector<uint32_t> priorityPrams)
{
  printf("DiffServ(uint32_t numQueue, vector<uint32_t> priorityPrams) start.");
 
  for (uint32_t i = 0; i < numQueue; ++i)
  {
    TrafficClass trafficClass;

    // TODO: What about priority_level (SPQ)?
    trafficClass.setWeight(priorityPrams[i]);

    q_class.push_back(&trafficClass);
  }
 
}


void 
DiffServ::setFilters (uint32_t queueIndex, vector<Filter*> filters) 
{
  q_class[queueIndex]->filters = filters;
}

void 
DiffServ::setDefaultQueue (uint32_t queueIndex, bool b) 
{
  q_class[queueIndex]->setIsDefault(b);
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
Ptr<const Packet>
DiffServ::Peek (void) const
{
  Ptr<const Packet> p = DoPeek ();

  return p;
}

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
  // Ptr<Packet> p = q_class[0]->Dequeue();

  return p;
}

Ptr<Packet> 
DiffServ::DoRemove () 
{
  // TODO
  // Ptr<Packet> p = Schedule();

  Ptr<Packet> p = q_class[0]->Dequeue();

  return 0;
}

Ptr<const Packet> 
DiffServ::DoPeek (void) const
{
  // TODO
  Ptr<const Packet> p = Schedule();

  return p;
}

Ptr<Packet> 
DiffServ::Schedule () const
{
  // TODO?
  
  return 0;
}


uint32_t 
DiffServ::Classify (Ptr<Packet> p)
{
  uint32_t defaultQueueIndex;
  for (uint32_t i = 0; i < q_class.size(); ++i)
  {
    if (q_class[i]->match(p)) 
    {
      return i;
    }

    // Get the default queue index. 
    // The packet that does not match any filter goes to the default queue. 
    if (q_class[i]->getIsDefault()) 
    {
       defaultQueueIndex = i;
    }
  }

  return defaultQueueIndex;
}







} // namespace ns3










