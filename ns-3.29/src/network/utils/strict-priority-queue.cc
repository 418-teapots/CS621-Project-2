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
  //  vector<TrafficClass*> q_class;
  // vector<TrafficClass*>* q_classPtr = GetQueuesPtr();
  // *q_class = &q_classPtr;

  printf("SPQ constructor\n");
  // printf("SPQ constructor: high-%d, low-%d\n",highPort, lowPort); //C
  TrafficClass* highPriorityQueue;
  highPriorityQueue = new TrafficClass();
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = new TrafficClass();
  lowPriorityQueue->SetPriorityLevel(uint32_t (LOW_PRIORITY));

  // q_classPtr->push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;

  // q_classPtr->push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  q_class.push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
  q_class.push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  queueMode = DiffServ::GetMode();

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
  q_class[HIGH_PRIORITY]->filters = highFilters;

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
  q_class[LOW_PRIORITY]->filters = lowFilters;

  printf("[TEST]q_class size = %lu\n", q_class.size());
}

SPQ::SPQ (uint32_t highPort, uint32_t lowPort)
{
  printf("SPQ constructor: high-%d, low-%d\n",highPort, lowPort);
  TrafficClass* highPriorityQueue;
  highPriorityQueue = new TrafficClass();
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = new TrafficClass();
  lowPriorityQueue->SetPriorityLevel(uint32_t (LOW_PRIORITY));

  q_class.push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
  q_class.push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  queueMode = DiffServ::GetMode();

  //HighPort Queue
  DestinationPortNumber* highPortNumber = 0;
  highPortNumber = new DestinationPortNumber (highPort);

  vector<FilterElement*> highFilterElements;
  highFilterElements.push_back(highPortNumber);

  Filter* highFilter = 0;
  highFilter = new Filter;
  highFilter->filterElements = highFilterElements;

  vector<Filter*> highFilters;
  highFilters.push_back(highFilter);
  q_class[HIGH_PRIORITY]->filters = highFilters;

  //LowPort Queue
  DestinationPortNumber* lowPortNumber = 0;
  lowPortNumber = new DestinationPortNumber (lowPort);

  vector<FilterElement*> lowFilterElements;
  lowFilterElements.push_back(lowPortNumber);

  Filter* lowFilter = 0;
  lowFilter = new Filter;
  lowFilter->filterElements = lowFilterElements;

  vector<Filter*> lowFilters;
  lowFilters.push_back(lowFilter);
  q_class[LOW_PRIORITY]->filters = lowFilters;

}

SPQ::~SPQ ()
{
	
}

uint32_t
SPQ::Schedule ()
{
  printf("SPQ Schedule\n");
  TrafficClass* highPriorityQueue;
  highPriorityQueue = q_class[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = q_class[LOW_PRIORITY];

  if (highPriorityQueue->GetPacketsCount() > 0) 
  {
    return uint32_t(HIGH_PRIORITY);
  }
  if (lowPriorityQueue->GetPacketsCount() > 0) 
  {
    return uint32_t(LOW_PRIORITY);
  }
  return 0;
}

/**
 * A single port or IP address can be set by the user and 
 * matching traffic is sorted into the priority queue,
 * all other traffic is sorted into the lower priority 
 * default queue.
 */
uint32_t 
SPQ::Classify (Ptr<ns3::Packet> p)
{
  printf("SPQ Classify\n");
  uint32_t defaultQueueIndex;
  for (uint32_t i = 0; i < q_class.size(); ++i)
  {
    if (q_class[i]->match(p)) 
    {
      return i;
    }

    // Get the default queue index. 
    // The packet that does not match any filter goes to the default queue. 
    if (q_class[i]->GetIsDefault()) 
    {
       defaultQueueIndex = i;
    }
  }

  return defaultQueueIndex;
  
}

bool 
SPQ::DoEnqueue (Ptr<ns3::Packet> p)
{
  printf("SPQ DoEnqueue\n");
  TrafficClass* highPriorityQueue;
  highPriorityQueue = q_class[HIGH_PRIORITY];

  TrafficClass* lowPriorityQueue;
  lowPriorityQueue = q_class[LOW_PRIORITY];


  uint32_t trafficClassToGo;
  trafficClassToGo = Classify(p);

  if (trafficClassToGo == 0) // high
  {
    if (highPriorityQueue->Enqueue(p)) 
    {
      highPriorityQueue->SetPacketsCount(highPriorityQueue->GetPacketsCount() + 1);
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
      lowPriorityQueue->SetPacketsCount(lowPriorityQueue->GetPacketsCount() + 1);

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

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();


  q_class[trafficClassToGo]->SetPacketsCount(q_class[trafficClassToGo]->GetPacketsCount() - 1);

	return toDequeue;
}

Ptr<ns3::Packet> 
SPQ::DoRemove ()
{
  printf("SPQ DoRemove\n");
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();

  q_class[trafficClassToGo]->SetPacketsCount(q_class[trafficClassToGo]->GetPacketsCount() - 1);


  return toDequeue;
}

Ptr<const ns3::Packet> 
SPQ::DoPeek ()
{  
  printf("SPQ DoPeek\n");
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();

  return toDequeue;
}

} // namespace ns3