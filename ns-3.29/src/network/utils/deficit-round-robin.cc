#include "deficit-round-robin.h"

using namespace std;

namespace ns3 {

// TypeId
// DRR::GetTypeId (void)
// {
//   static TypeId tid = TypeId (("ns3::DRR<" + GetTypeParamName<DRR> () + ">").c_str ())
//     .SetParent<DiffServ> () //TODO: SetParent
//     .SetGroupName ("Network")
//   ;
//   return tid;
// }


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

DRR::~DRR ()
{
    
}

Ptr<Packet> 
DRR::Schedule ()
{
  // TODO










  return 0;

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










} // namespace ns3






















