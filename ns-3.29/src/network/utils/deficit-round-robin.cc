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

DRR::DRR () : 
  roundRobinPointer (0)
{

}

/** 
 * 'numQueue' is the number of queues. 
 * 'priorityPrams' is a list of priority_level or weight. 
 *  e.g. 300 200 100 
 */
DRR::DRR (uint32_t numQueue, vector<uint32_t> priorityPrams) : 
  roundRobinPointer (0)
  // DiffServ(numQueue)
{

  vector<TrafficClass*>* queuesPtr = getQueuesPtr();

  // Make conditions on which queue to go. 
  // e.g. (src IP: "1.1.1.1" AND src port: 2048) OR (src IP: "2.2.2.2" AND src port: 2048) => this packet goes to q_class[0]. 
  
  // Queue 0. 
  DRRQueue* drrQueue0 = new DRRQueue;
  // For Filter 1. 
  Ipv4Address addr1("1.1.1.1");
  SourceIPAddress sourceIPAddress1(addr1);

  uint32_t portNum1 = 2048;
  SourcePortNumber sourcePortNumber1(portNum1);

  Filter filter1;
  filter1.elements.push_back(&sourceIPAddress1);
  filter1.elements.push_back(&sourcePortNumber1);

  // For Filter 2. 
  Ipv4Address addr2("2.2.2.2");
  SourceIPAddress sourceIPAddress2(addr2);

  uint32_t portNum2 = 2048;
  SourcePortNumber sourcePortNumber2(portNum2);

  Filter filter2;
  filter2.elements.push_back(&sourceIPAddress2);
  filter2.elements.push_back(&sourcePortNumber2);

  // Set Filter 1 and Filter 2 to filters. 
  vector<Filter*> filters0;
  filters0.push_back(&filter1);
  filters0.push_back(&filter2);

  // Assign filters and other settings to q_class[0]. 
  drrQueue0->filters = filters0;
  drrQueue0->setIsDefault(false);
  drrQueue0->setWeight(priorityPrams[0]);
  (*queuesPtr).push_back(drrQueue0);


  // Queue 1. 
  DRRQueue* drrQueue1 = new DRRQueue;

  Ipv4Address addr3("1.1.1.1");
  SourceIPAddress sourceIPAddress3(addr3);

  uint32_t portNum3 = 2049;
  SourcePortNumber sourcePortNumber3(portNum3);

  Filter filter3;
  filter3.elements.push_back(&sourceIPAddress3);
  filter3.elements.push_back(&sourcePortNumber3);

  vector<Filter*> filters1;
  filters1.push_back(&filter3);

  // Assign filters and other settings to q_class[1]. 
  drrQueue1->filters = filters1;
  drrQueue1->setIsDefault(false);
  drrQueue1->setWeight(priorityPrams[1]);
  (*queuesPtr).push_back(drrQueue1);
  

  // Queue 2. 
  DRRQueue* drrQueue2 = new DRRQueue;

  Ipv4Address addr4("1.1.1.1");
  SourceIPAddress sourceIPAddress4(addr4);

  uint32_t portNum4 = 2050;
  SourcePortNumber sourcePortNumber4(portNum4);

  Filter filter4;
  filter4.elements.push_back(&sourceIPAddress4);
  filter4.elements.push_back(&sourcePortNumber4);

  vector<Filter*> filters2;
  filters2.push_back(&filter4);

  // Assign filters and other settings to q_class[2]. 
  drrQueue2->filters = filters2;
  drrQueue2->setIsDefault(true);
  drrQueue2->setWeight(priorityPrams[2]);
  (*queuesPtr).push_back(drrQueue2);


  




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

void 
DRR::setRoundRobinPointer (uint32_t v)
{
  roundRobinPointer = v;
}

uint32_t 
DRR::getRoundRobinPointer ()
{
  return roundRobinPointer;
}

uint32_t
DRR::Schedule ()
{
  uint32_t nextScheduledQueueIndex = 0;
  
  vector<TrafficClass*>* queuesPtr = getQueuesPtr();

  uint32_t numQueue = (*queuesPtr).size();
  uint32_t rrp = getRoundRobinPointer();
  while (true)
  {
    rrp = rrp % numQueue;
    DRRQueue* queuePtr = (DRRQueue*)(*queuesPtr)[rrp];

    // Check if the queue is empty. 
    uint32_t packetsCount = queuePtr->getPacketsCount();
    if (packetsCount <= 0)
    {
      rrp++;
      continue;
    }
    
    // Add the quantum to the Deficit Counter of the queue.
    uint32_t quantum = static_cast<uint32_t>(queuePtr->getWeight());
    uint32_t dc = queuePtr->getDeficitCounter();
    dc += quantum;

    // Check the size of the packet in the front and 
    // Dequeue it if the Deficit Counter is larger than the size. 
    Ptr<Packet> packet = queuePtr->Peek();
    uint32_t packetSize = packet->GetSize();
    if (dc - packetSize > 0)
    {
      nextScheduledQueueIndex = rrp;
      packetsCount--;
      queuePtr->setPacketsCount(packetsCount);

      // Update the Deficit Counter. 
      if (packetsCount <= 0)
      {
        // Queue is empty. Set the DC to 0. 
        dc = 0;
        rrp++;
      }
      else
      {
        dc -= packetSize;
      }

      queuePtr->setDeficitCounter(dc);
      setRoundRobinPointer(rrp);

      return nextScheduledQueueIndex;
    }
    else
    {
      rrp++;
    }

  }

}

// Schedule member function that returns packet. 
// Ptr<Packet> 
// DRR::Schedule ()
// {
  
//   vector<TrafficClass*>* queuesPtr = getQueuesPtr();

//   uint32_t numQueue = (*queuesPtr).size();
//   uint32_t rrp = getRoundRobinPointer();
//   while (true)
//   {
//     rrp = rrp % numQueue;
//     DRRQueue* queuePtr = (DRRQueue*)(*queuesPtr)[rrp];

//     // Check if the queue is empty. 
//     if (queuePtr->getPacketsCount() <= 0)
//     {
//       rrp++;
//       continue;
//     }
    
//     // Add the quantum to the Deficit Counter of the queue.
//     uint32_t quantum = static_cast<uint32_t>(queuePtr->getWeight());
//     uint32_t dc = queuePtr->getDeficitCounter();
//     dc += quantum;

//     // Check the size of the packet in the front and 
//     // Dequeue it if the Deficit Counter is larger than the size. 
//     Ptr<Packet> packet = queuePtr->Peek();
//     uint32_t packetSize = packet->GetSize();
//     if (dc - packetSize > 0)
//     {
//       packet = queuePtr->Dequeue();

//       // Update the Deficit Counter. 
//       if (queuePtr->getPacketsCount() <= 0)
//       {
//         // Queue is empty. Set the DC to 0. 
//         dc = 0;
//         rrp++;
//       }
//       else
//       {
//         dc -= packetSize;
//       }

//       queuePtr->setDeficitCounter(dc);
//       setRoundRobinPointer(rrp);

//       return packet;
//     }
//     else
//     {
//       rrp++;
//     }

//   }

// }










} // namespace ns3






















