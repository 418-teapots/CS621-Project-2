#include "deficit-round-robin.h"

using namespace std;

namespace ns3 {

TypeId
DRR::GetTypeId (void)
{
  static TypeId tid = TypeId (("ns3::DRR<" + GetTypeParamName<DRR> () + ">").c_str ())
    .SetParent<DiffServ> () //TODO: SetParent
    .SetGroupName ("Network")
  ;
  return tid;
}


DRR::DRR ()
{

  // TODO

  // TrafficClass* highPriorityQueue;
  // highPriorityQueue->setPriorityLevel(HIGH_PRIORITY);
  // TrafficClass* lowPriorityQueue;
  // lowPriorityQueue->setPriorityLevel(LOW_PRIORITY);

  // q_class.push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
  // q_class.push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  // queueMode = DiffServ::GetMode ();
}

virtual ~DRR ()
{
    
}

Ptr<Packet> 
DRR::Schedule ()
{
  // TODO


  // TrafficClass* highPriorityQueue;
  // highPriorityQueue = q_class[HIGH_PRIORITY];

  // TrafficClass* lowPriorityQueue;
  // lowPriorityQueue = q_class[LOW_PRIORITY];

  // Ptr<Packet> toDequeue = highPriorityQueue->Dequeue();
  // if (toDequeue != 0) 
  // {
  //   NS_LOG_LOGIC ("High Priority Queue pop");
  //   return toDequeue;
  // }
  // else
  // {
  //   toDequeue = lowPriorityQueue->Dequeue();
  //   if (toDequeue != 0)
  //   {
  //     NS_LOG_LOGIC ("Low Priority Queue pop");
  //     return toDequeue;
  //   }
  //   else 
  //   {
  //     NS_LOG_LOGIC ("All Queues are empty");
  //     return 0;
  //   }
  // }
}

/**
 * A single port or IP address can be set by the user and 
 * matching traffic is sorted into the priority queue,
 * all other traffic is sorted into the lower priority 
 * default queue.
 */
uint32_t 
DRR::Classify (Ptr<Packet> p)
{
  for (uint32_t i = 0; i < q_class.size(); i++)
  {
    if (q_class[i].match(p)) 
    {
      return i;
    }
  }

  return -1;

/*TODO: setMode()??????
  if (queueMode == DiffServ::QUEUE_MODE_PACKETS) 
    {
      if (highPriorityQueue->getPackets() < highPriorityQueue->getMaxPackets())
        {
        }
      else
        { 
        }
    } 
  else if (queueMode == DiffServ::QUEUE_MODE_BYTES)
    {
    }
    */
  
}

bool 
DRR::DoEnqueue (Ptr<Packet> p)
{
  printf ("DoEnqueue() in DRR start.\n");
  
  // TODO
  uint32_t trafficClassToGo = Classify(p);


  


  // TODO: Call Enqueue() in TrafficClass object.  
  bool b = q_class[trafficClassToGo]->Enqueue(p);
  
  // uint32_t size = p->GetSize ();
  // m_nBytes += size;
  // m_nTotalReceivedBytes += size;

  // m_nPackets++;
  // m_nTotalReceivedPackets++;

  // // NS_LOG_LOGIC ("m_traceEnqueue (p)");
  // m_traceEnqueue (p);

  return b;




  // TrafficClass* highPriorityQueue;
  // highPriorityQueue = q_class[HIGH_PRIORITY];

  // TrafficClass* lowPriorityQueue;
  // lowPriorityQueue = q_class[LOW_PRIORITY];


  // uint32_t trafficClassToGo;
  // trafficClassToGo = Classify(p);

  // if (trafficClassToGo == 0) // high
  // {
  //   if (highPriorityQueue->Enqueue(p)) 
  //   {
  //     NS_LOG_LOGIC ("High Priority Queue push");
  //   }
  //   else 
  //   {
  //     if (lowPriorityQueue->Enqueue(p))
  //     {
  //       NS_LOG_LOGIC ("Low Priority Queue push");
  //     }
  //     else 
  //     {
  //       NS_LOG_LOGIC ("All Queues are full");
  //     }
  //   }
  // }

}

Ptr<Packet> 
DRR::DoDequeue ()
{
  printf ("DoDequeue() in DRR start.\n");

  return Schedule();
}

Ptr<Packet> 
DRR::DoRemove ()
{
    
}

Ptr<const Packet> 
DRR::DoPeek ()
{
  //TODO: add a peek() in TrafficClass
    
}

} // namespace ns3






















