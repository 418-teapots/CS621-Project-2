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

  // Make conditions on which queue to go. 
  // ("1.1.1.1" AND 443) OR ("2.2.2.2" AND 888)
  
  // Ipv4Address addr1("1.1.1.1");
  // SourceIPAddress sourceIPAddress1(addr1);

  // uint32_t portNum1 = 443;
  // SourcePortNumber sourcePortNumber1(portNum1);

  // Filter filter1;
  // filter1.elements.push_back(&sourceIPAddress1);
  // filter1.elements.push_back(&sourcePortNumber1);


  // Ipv4Address addr2("2.2.2.2");
  // SourceIPAddress sourceIPAddress2(addr2);

  // uint32_t portNum2 = 888;
  // SourcePortNumber sourcePortNumber2(portNum2);

  // Filter filter2;
  // filter2.elements.push_back(&sourceIPAddress2);
  // filter2.elements.push_back(&sourcePortNumber2);


  // vector<Filter*> filters;
  // filters.push_back(&filter1);
  // filters.push_back(&filter2);

  // q_class[0]->filters = filters;


  // DiffServ(3, filters);
  

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






















