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
  printf("Default DRR constructor start. \n");

}

/** 
 * \param numQueue  the number of queues. 
 * \param priorityParams  a list of priority_level or weight. e.g. 300 200 100 
 */
DRR::DRR (uint32_t numQueue, vector<uint32_t> priorityParams) : 
  m_roundRobinPointer (0)
  // DiffServ(numQueue) 
{
  printf("Constructor DRR (uint32_t numQueue, vector<uint32_t> priorityParams) start. \n");


  vector<TrafficClass*>* queuesPtr = GetQueuesPtr ();

  // Queue 0. 
  DrrQueue* drrQueue0 = 0;
  drrQueue0 = new DrrQueue;

  // Create FilterElement settings. 
  uint32_t portNum0 = 2048;
  SourcePortNumber* sourcePortNumber0 = 0;
  sourcePortNumber0 = new SourcePortNumber (portNum0);

  vector<FilterElement*> filterElements0;
  filterElements0.push_back(sourcePortNumber0);

  // Set the FilterElement to Filter. 
  Filter* filter0 = 0;
  filter0 = new Filter;
  filter0->filterElements = filterElements0;

  // Set the Filter to TrafficClass. 
  vector<Filter*> filters0;
  filters0.push_back(filter0);
  drrQueue0->filters = filters0;

  // Set other settings to q_class[0]. 
  drrQueue0->SetIsDefault (false);
  drrQueue0->SetWeight (priorityParams[0]);
  (*queuesPtr).push_back(drrQueue0);


  // Queue 1. 
  DrrQueue* drrQueue1 = 0;
  drrQueue1 = new DrrQueue;

  // Create FilterElement settings. 
  uint32_t portNum1 = 2049;
  SourcePortNumber* sourcePortNumber1 = 0;
  sourcePortNumber1 = new SourcePortNumber (portNum1);

  vector<FilterElement*> filterElements1;
  filterElements1.push_back(sourcePortNumber1);

  // Set the FilterElement to Filter. 
  Filter* filter1 = 0;
  filter1 = new Filter;
  filter1->filterElements = filterElements1;

  // Set the Filter to TrafficClass. 
  vector<Filter*> filters1;
  filters1.push_back(filter1);
  drrQueue1->filters = filters1;

  // Set other settings to q_class[1]. 
  drrQueue1->SetIsDefault (false);
  drrQueue1->SetWeight (priorityParams[1]);
  (*queuesPtr).push_back(drrQueue1);
  

  // Queue 2. 
  DrrQueue* drrQueue2 = 0;
  drrQueue2 = new DrrQueue;

  // Create FilterElement settings. 
  uint32_t portNum2 = 2050;
  SourcePortNumber* sourcePortNumber2 = 0;
  sourcePortNumber2 = new SourcePortNumber (portNum2);

  vector<FilterElement*> filterElements2;
  filterElements2.push_back(sourcePortNumber2);

  // Set the FilterElement to Filter. 
  Filter* filter2 = 0;
  filter2 = new Filter;
  filter2->filterElements = filterElements2;

  // Set the Filter to TrafficClass. 
  vector<Filter*> filters2;
  filters2.push_back(filter2);
  drrQueue2->filters = filters2;

  // Set other settings to q_class[2]. 
  drrQueue2->SetIsDefault (true);
  drrQueue2->SetWeight (priorityParams[2]);
  (*queuesPtr).push_back(drrQueue2);



  

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
  
  vector<TrafficClass*>* queuesPtr = GetQueuesPtr ();

  uint32_t numQueue = (*queuesPtr).size();
  uint32_t rrp = GetRoundRobinPointer ();
  while (true)
  {
    rrp = rrp % numQueue;
    DrrQueue* queuePtr = (DrrQueue*)(*queuesPtr)[rrp];

    // Check if the queue is empty. 
    uint32_t packetsCount = queuePtr->GetPacketsCount ();
    if (packetsCount <= 0)
    {
      rrp++;
      continue;
    }
    
    // Add the quantum to the Deficit Counter of the queue.
    uint32_t quantum = static_cast<uint32_t>(queuePtr->GetWeight ());
    uint32_t dc = queuePtr->GetDeficitCounter ();
    dc += quantum;

    // Check the size of the packet in the front and 
    // Dequeue it if the Deficit Counter is larger than the size. 
    Ptr<Packet> packet = queuePtr->Peek ();
    uint32_t packetSize = packet->GetSize ();
    if (dc - packetSize > 0)
    {
      nextScheduledQueueIndex = rrp;
      packetsCount--;
      queuePtr->SetPacketsCount (packetsCount);

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

      queuePtr->SetDeficitCounter (dc);
      SetRoundRobinPointer (rrp);

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






















