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
  m_roundRobinPointer (0)
{

}

/** 
 * \param numQueue  the number of queues. 
 * \param priorityParams  a list of priority_level or weight. e.g. 300 200 100 
 */
DRR::DRR (uint32_t numQueue, vector<uint32_t> priorityParams) : 
  m_roundRobinPointer (0)
  // DiffServ(numQueue)
{

  vector<TrafficClass*>* queuesPtr = GetQueuesPtr();

  // Queue 0. 
  DrrQueue* drrQueue0 = new DrrQueue;
  // For Filter 1. 
  uint32_t portNum0 = 2048;
  SourcePortNumber sourcePortNumber0(portNum0);

  Filter filter0;
  filter0.elements.push_back(&sourcePortNumber0);

  // Set Filter 1 and Filter 2 to filters. 
  vector<Filter*> filters0;
  filters0.push_back(&filter0);

  // Assign filters and other settings to q_class[0]. 
  drrQueue0->filters = filters0;
  drrQueue0->SetIsDefault(false);
  drrQueue0->SetWeight(priorityParams[0]);
  (*queuesPtr).push_back(drrQueue0);


  // Queue 1. 
  DrrQueue* drrQueue1 = new DrrQueue;

  uint32_t portNum1 = 2049;
  SourcePortNumber sourcePortNumber1(portNum1);

  Filter filter1;
  filter1.elements.push_back(&sourcePortNumber1);

  vector<Filter*> filters1;
  filters1.push_back(&filter1);

  // Assign filters and other settings to q_class[1]. 
  drrQueue1->filters = filters1;
  drrQueue1->SetIsDefault(false);
  drrQueue1->SetWeight(priorityParams[1]);
  (*queuesPtr).push_back(drrQueue1);
  

  // Queue 2. 
  DrrQueue* drrQueue2 = new DrrQueue;

  uint32_t portNum2 = 2050;
  SourcePortNumber sourcePortNumber2(portNum2);

  Filter filter2;
  filter2.elements.push_back(&sourcePortNumber2);

  vector<Filter*> filters2;
  filters2.push_back(&filter2);

  // Assign filters and other settings to q_class[2]. 
  drrQueue2->filters = filters2;
  drrQueue2->SetIsDefault(true);
  drrQueue2->SetWeight(priorityParams[2]);
  (*queuesPtr).push_back(drrQueue2);


  ////////////  other priority settings examples   //////////////


  // Make conditions on which queue to go. 
  // e.g. (src IP: "1.1.1.1" AND src port: 2048) OR (src IP: "2.2.2.2" AND src port: 2048) 
  //      => this packet goes to q_class[0]. 
  
  // // Queue 0. 
  // DrrQueue* drrQueue0 = new DrrQueue;
  // // For Filter 1. 
  // Ipv4Address addr1("1.1.1.1");
  // SourceIPAddress sourceIPAddress1(addr1);

  // uint32_t portNum1 = 2048;
  // SourcePortNumber sourcePortNumber1(portNum1);

  // Filter filter1;
  // filter1.elements.push_back(&sourceIPAddress1);
  // filter1.elements.push_back(&sourcePortNumber1);

  // // For Filter 2. 
  // Ipv4Address addr2("2.2.2.2");
  // SourceIPAddress sourceIPAddress2(addr2);

  // uint32_t portNum2 = 2048;
  // SourcePortNumber sourcePortNumber2(portNum2);

  // Filter filter2;
  // filter2.elements.push_back(&sourceIPAddress2);
  // filter2.elements.push_back(&sourcePortNumber2);

  // // Set Filter 1 and Filter 2 to filters. 
  // vector<Filter*> filters0;
  // filters0.push_back(&filter1);
  // filters0.push_back(&filter2);

  // // Assign filters and other settings to q_class[0]. 
  // drrQueue0->filters = filters0;
  // drrQueue0->SetIsDefault(false);
  // drrQueue0->SetWeight(priorityParams[0]);
  // (*queuesPtr).push_back(drrQueue0);


  // // Queue 1. 
  // DrrQueue* drrQueue1 = new DrrQueue;

  // Ipv4Address addr3("1.1.1.1");
  // SourceIPAddress sourceIPAddress3(addr3);

  // uint32_t portNum3 = 2049;
  // SourcePortNumber sourcePortNumber3(portNum3);

  // Filter filter3;
  // filter3.elements.push_back(&sourceIPAddress3);
  // filter3.elements.push_back(&sourcePortNumber3);

  // vector<Filter*> filters1;
  // filters1.push_back(&filter3);

  // // Assign filters and other settings to q_class[1]. 
  // drrQueue1->filters = filters1;
  // drrQueue1->SetIsDefault(false);
  // drrQueue1->SetWeight(priorityParams[1]);
  // (*queuesPtr).push_back(drrQueue1);
  

  // // Queue 2. 
  // DrrQueue* drrQueue2 = new DrrQueue;

  // Ipv4Address addr4("1.1.1.1");
  // SourceIPAddress sourceIPAddress4(addr4);

  // uint32_t portNum4 = 2050;
  // SourcePortNumber sourcePortNumber4(portNum4);

  // Filter filter4;
  // filter4.elements.push_back(&sourceIPAddress4);
  // filter4.elements.push_back(&sourcePortNumber4);

  // vector<Filter*> filters2;
  // filters2.push_back(&filter4);

  // // Assign filters and other settings to q_class[2]. 
  // drrQueue2->filters = filters2;
  // drrQueue2->SetIsDefault(true);
  // drrQueue2->SetWeight(priorityParams[2]);
  // (*queuesPtr).push_back(drrQueue2);
  ///////////////////////////////////////////////////////////////////


}

DRR::~DRR ()
{
    
}

void 
DRR::SetRoundRobinPointer (uint32_t v)
{
  m_roundRobinPointer = v;
}

uint32_t 
DRR::GetRoundRobinPointer ()
{
  return m_roundRobinPointer;
}

uint32_t
DRR::Schedule ()
{
  uint32_t nextScheduledQueueIndex = 0;
  
  vector<TrafficClass*>* queuesPtr = GetQueuesPtr();

  uint32_t numQueue = (*queuesPtr).size();
  uint32_t rrp = GetRoundRobinPointer();
  while (true)
  {
    rrp = rrp % numQueue;
    DrrQueue* queuePtr = (DrrQueue*)(*queuesPtr)[rrp];

    // Check if the queue is empty. 
    uint32_t packetsCount = queuePtr->GetPacketsCount();
    if (packetsCount <= 0)
    {
      rrp++;
      continue;
    }
    
    // Add the quantum to the Deficit Counter of the queue.
    uint32_t quantum = static_cast<uint32_t>(queuePtr->GetWeight());
    uint32_t dc = queuePtr->GetDeficitCounter();
    dc += quantum;

    // Check the size of the packet in the front and 
    // Dequeue it if the Deficit Counter is larger than the size. 
    Ptr<Packet> packet = queuePtr->Peek();
    uint32_t packetSize = packet->GetSize();
    if (dc - packetSize > 0)
    {
      nextScheduledQueueIndex = rrp;
      packetsCount--;
      queuePtr->SetPacketsCount(packetsCount);

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

      queuePtr->SetDeficitCounter(dc);
      SetRoundRobinPointer(rrp);

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






















