

#include "differentiated-services.h"
#include <iostream>


namespace ns3 {


DiffServ::DiffServ () 
{
  printf("DiffServ() start.");

  // TODO


  TrafficClass trafficClass;
  q_class.assign(1, &trafficClass);

}


// priorityPrams is a list of priority_level or weight. 
// e.g. 300 200 100 
DiffServ::DiffServ (uint32_t numQueue, vector<uint32_t> priorityPrams)
{
  printf("DiffServ(uint32_t numQueue, vector<uint32_t> priorityPrams) start.");

  // TODO

  // Example. TODO
  for (uint32_t i = 0; i < numQueue; ++i)
  {
    TrafficClass trafficClass(false);
    // TODO: What about priority_level (SPQ)?
    trafficClass.setWeight(priorityPrams[i]);
    q_class.push_back(&trafficClass);
  }

  ////// Filter settings example start. //////
  // Make conditions on which queue to go. 
  // e.g. ("1.1.1.1" AND 443) OR ("2.2.2.2" AND 888) => this packet goes to q_class[0]. 
  
  // For Filter 1. 
  Ipv4Address addr1("1.1.1.1");
  SourceIPAddress sourceIPAddress1(addr1);

  uint32_t portNum1 = 443;
  SourcePortNumber sourcePortNumber1(portNum1);

  Filter filter1;
  filter1.elements.push_back(&sourceIPAddress1);
  filter1.elements.push_back(&sourcePortNumber1);

  // For Filter 2. 
  Ipv4Address addr2("2.2.2.2");
  SourceIPAddress sourceIPAddress2(addr2);

  uint32_t portNum2 = 888;
  SourcePortNumber sourcePortNumber2(portNum2);

  Filter filter2;
  filter2.elements.push_back(&sourceIPAddress2);
  filter2.elements.push_back(&sourcePortNumber2);

  // Set Filter 1 and Filter 2 to filters. 
  vector<Filter*> filters;
  filters.push_back(&filter1);
  filters.push_back(&filter2);

  // Set filters to q_class[0]. 
  q_class[0]->filters = filters;

  ////// Filter settings example end. //////



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
  // Ptr<Packet> p = Schedule();

  Ptr<Packet> p = q_class[0]->Dequeue();

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

  uint32_t defaultQueue;
  for (uint32_t i = 0; i < q_class.size(); ++i)
  {
    if (q_class[i]->match(p)) 
    {
      return i;
    }

    if (q_class[i]->isDefaultQueue()) 
    {
       defaultQueue = i;
    }
  }

  return defaultQueue;
}




} // namespace ns3










