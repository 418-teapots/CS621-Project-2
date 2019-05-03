#include "strict-priority-queue.h"

namespace ns3 {

// TypeId
// SPQ::GetTypeId (void)
// {
//   static TypeId tid = TypeId (("ns3::SPQ<" + GetTypeParamName<SPQ> () + ">").c_str ())
//     .SetParent<DiffServ> () //TODO: SetParent
//     .SetGroupName ("Network")
//   ;
//   return tid;
// }


SPQ::SPQ ()
{ 
  queueMode = DiffServ::GetMode();
  //  vector<TrafficClass*> q_class;
  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();
  // *q_class = &q_classPtr;

  printf("SPQ constructor\n");
  // printf("SPQ constructor: high-%d, low-%d\n",highPort, lowPort); //C
  TrafficClass* highPriorityQueue;
  highPriorityQueue = new TrafficClass();
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));

  //HighPort Queue
  DestinationPortNumber* highPortNumber = 0;
  highPortNumber = new DestinationPortNumber (443);
  // highPortNumber = new DestinationPortNumber (highPort); //C

  vector<FilterElement*> highFilterElements;
  highFilterElements.push_back(highPortNumber);

  Filter* highFilter = 0;
  highFilter = new Filter;
  highFilter->filterElements = highFilterElements;

  vector<Filter*> highFilters;
  highFilters.push_back(highFilter);
  highPriorityQueue->filters = highFilters;


  (*q_classPtr).push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
//=========

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = new TrafficClass();
  lowPriorityQueue->SetPriorityLevel(uint32_t (LOW_PRIORITY));

  //LowPort Queue
  DestinationPortNumber* lowPortNumber = 0;
  lowPortNumber = new DestinationPortNumber (6881);
  // lowPortNumber = new DestinationPortNumber (lowPort); //C

  vector<FilterElement*> lowFilterElements;
  lowFilterElements.push_back(lowPortNumber);

  Filter* lowFilter = 0;
  lowFilter = new Filter;
  lowFilter->filterElements = lowFilterElements;

  vector<Filter*> lowFilters;
  lowFilters.push_back(lowFilter);
  lowPriorityQueue->filters = lowFilters;


  (*q_classPtr).push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  // q_class.push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
  // q_class.push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

}

SPQ::SPQ (uint32_t highPort, uint32_t lowPort)
{
  printf("SPQ constructor: high-%d, low-%d\n",highPort, lowPort);
  queueMode = DiffServ::GetMode();
  //  vector<TrafficClass*> q_class;
  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();
  // *q_class = &q_classPtr;

  TrafficClass* highPriorityQueue;
  highPriorityQueue = new TrafficClass();
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));

  //HighPort Queue
  DestinationPortNumber* highPortNumber = 0;
  // highPortNumber = new DestinationPortNumber (443);
  highPortNumber = new DestinationPortNumber (highPort); //C

  vector<FilterElement*> highFilterElements;
  highFilterElements.push_back(highPortNumber);

  Filter* highFilter = 0;
  highFilter = new Filter;
  highFilter->filterElements = highFilterElements;

  vector<Filter*> highFilters;
  highFilters.push_back(highFilter);
  highPriorityQueue->filters = highFilters;


  (*q_classPtr).push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
//=========

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = new TrafficClass();
  lowPriorityQueue->SetPriorityLevel(uint32_t (LOW_PRIORITY));

  //LowPort Queue
  DestinationPortNumber* lowPortNumber = 0;
  // lowPortNumber = new DestinationPortNumber (6881);
  lowPortNumber = new DestinationPortNumber (lowPort); //C

  vector<FilterElement*> lowFilterElements;
  lowFilterElements.push_back(lowPortNumber);

  Filter* lowFilter = 0;
  lowFilter = new Filter;
  lowFilter->filterElements = lowFilterElements;

  vector<Filter*> lowFilters;
  lowFilters.push_back(lowFilter);
  lowPriorityQueue->filters = lowFilters;


  (*q_classPtr).push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

}

SPQ::~SPQ ()
{
	
}

uint32_t
SPQ::Schedule ()
{
  printf("SPQ Schedule\n");

  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();

  TrafficClass* highPriorityQueue;
  highPriorityQueue = (*q_classPtr)[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = (*q_classPtr)[LOW_PRIORITY];

  if (highPriorityQueue->GetPacketsCount() > 0) 
  {
    return uint32_t(HIGH_PRIORITY);
  }
  if (lowPriorityQueue->GetPacketsCount() > 0) 
  {
    return uint32_t(LOW_PRIORITY);
  }
  printf("SPQ Schedule Nothing!\n");
  return 0;
}

/**
 * A single port or IP address can be set by the user and 
 * matching traffic is sorted into the priority queue,
 * all other traffic is sorted into the lower priority 
 * default queue.
 */
// uint32_t 
// SPQ::Classify (Ptr<ns3::Packet> p)
// {
//   printf("SPQ Classify\n");
//   uint32_t defaultQueueIndex;
//   for (uint32_t i = 0; i < q_class.size(); ++i)
//   {
//     if (q_class[i]->match(p)) 
//     {
//       return i;
//     }

//     // Get the default queue index. 
//     // The packet that does not match any filter goes to the default queue. 
//     if (q_class[i]->GetIsDefault()) 
//     {
//        defaultQueueIndex = i;
//     }
//   }

//   return defaultQueueIndex;
  
// }

bool 
SPQ::DoEnqueue (Ptr<ns3::Packet> p)
{
  printf("SPQ DoEnqueue\n");
  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();

  TrafficClass* highPriorityQueue;
  highPriorityQueue = (*q_classPtr)[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = (*q_classPtr)[LOW_PRIORITY];


  uint32_t trafficClassToGo;
  trafficClassToGo = Classify(p);

  if (trafficClassToGo == 0) // high
  {
    if (highPriorityQueue->Enqueue(p)) 
    {
      // highPriorityQueue->SetPacketsCount(highPriorityQueue->GetPacketsCount() + 1);
      printf("HighPriorityQueue enqueue, packetsCount:%d\n", highPriorityQueue->GetPacketsCount());
      // NS_LOG_LOGIC ("High Priority Queue push");
      return true;
    }
    else 
    {

      return false;
    }
  }
  else // low
  {
    if (lowPriorityQueue->Enqueue(p))
    {

      // lowPriorityQueue->SetPacketsCount(lowPriorityQueue->GetPacketsCount() + 1);
      printf("LowPriorityQueue enqueue, packetsCount:%d\n", lowPriorityQueue->GetPacketsCount());
      // NS_LOG_LOGIC ("Low Priority Queue push");
      return true;
    }
    else 
    {
      // NS_LOG_LOGIC ("All Queues are full");
      return false;
    }
  }

}

Ptr<ns3::Packet> 
SPQ::DoDequeue ()
{
  printf("SPQ DoDequeue\n");
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();

  TrafficClass* highPriorityQueue;
  highPriorityQueue = (*q_classPtr)[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = (*q_classPtr)[LOW_PRIORITY];

  Ptr<ns3::Packet> toDequeue = 0;
  if (trafficClassToGo == 0) 
  {
    toDequeue = highPriorityQueue->Dequeue();
  }
  else 
  {
    toDequeue = lowPriorityQueue->Dequeue();
  }
  

  // q_class[trafficClassToGo]->SetPacketsCount(q_class[trafficClassToGo]->GetPacketsCount() - 1);

  // printf("PriorityQueue %d dequeue, packetsCount:%d\n", trafficClassToGo, q_class[trafficClassToGo]->GetPacketsCount());
	return toDequeue;
}

Ptr<ns3::Packet> 
SPQ::DoRemove ()
{
  printf("SPQ DoRemove\n");
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();

  TrafficClass* highPriorityQueue;
  highPriorityQueue = (*q_classPtr)[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = (*q_classPtr)[LOW_PRIORITY];

  Ptr<ns3::Packet> toDequeue = 0;
  if (trafficClassToGo == 0) 
  {
    toDequeue = highPriorityQueue->Dequeue();
  }
  else 
  {
    toDequeue = lowPriorityQueue->Dequeue();
  }
  

  // q_class[trafficClassToGo]->SetPacketsCount(q_class[trafficClassToGo]->GetPacketsCount() - 1);

  // printf("PriorityQueue %d dequeue, packetsCount:%d\n", trafficClassToGo, q_class[trafficClassToGo]->GetPacketsCount());
  return toDequeue;
}

Ptr<const ns3::Packet> 
SPQ::DoPeek ()
{  
  printf("SPQ DoPeek\n");
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  vector<TrafficClass*>* q_classPtr = GetQueuesPtr();

  TrafficClass* highPriorityQueue;
  highPriorityQueue = (*q_classPtr)[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = (*q_classPtr)[LOW_PRIORITY];

  Ptr<ns3::Packet> toDequeue = 0;
  if (trafficClassToGo == 0) 
  {
    toDequeue = highPriorityQueue->Dequeue();
  }
  else 
  {
    toDequeue = lowPriorityQueue->Dequeue();
  }
  // q_class[trafficClassToGo]->SetPacketsCount(q_class[trafficClassToGo]->GetPacketsCount() - 1);

  // printf("PriorityQueue %d dequeue, packetsCount:%d\n", trafficClassToGo, q_class[trafficClassToGo]->GetPacketsCount());
  return toDequeue;
}

} // namespace ns3