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
  TrafficClass* highPriorityQueue;
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));
  TrafficClass* lowPriorityQueue;
  lowPriorityQueue->SetPriorityLevel(uint32_t (LOW_PRIORITY));

  q_class.push_back(highPriorityQueue); //q_class[0]:highPriorityQueue;
  q_class.push_back(lowPriorityQueue);  //q_class[1]:lowPriorityQueue;

  queueMode = DiffServ::GetMode();

  //HighPort Queue
  DestinationPortNumber* highPortNumber = 0;
  highPortNumber = new DestinationPortNumber (443);

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

  vector<FilterElement*> lowFilterElements;
  lowFilterElements.push_back(lowPortNumber);

  Filter* lowFilter = 0;
  lowFilter = new Filter;
  lowFilter->filterElements = lowFilterElements;

  vector<Filter*> lowFilters;
  lowFilters.push_back(lowFilter);
  q_class[LOW_PRIORITY]->filters = lowFilters;
}

SPQ::SPQ (uint32_t highPort, uint32_t lowPort)
{
  TrafficClass* highPriorityQueue;
  highPriorityQueue->SetPriorityLevel(uint32_t (HIGH_PRIORITY));
  TrafficClass* lowPriorityQueue;
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
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();

	return toDequeue;
}

Ptr<ns3::Packet> 
SPQ::DoRemove ()
{
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();

  return toDequeue;
}

Ptr<const ns3::Packet> 
SPQ::DoPeek ()
{
  uint32_t trafficClassToGo;
  trafficClassToGo = Schedule();

  Ptr<ns3::Packet> toDequeue = q_class[trafficClassToGo]->Dequeue();

  return toDequeue;
}

} // namespace ns3