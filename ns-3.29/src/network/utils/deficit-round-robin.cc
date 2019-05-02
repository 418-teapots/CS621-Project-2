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
  m_counter (0),
  m_roundRobinPointer (0)
{
  printf("Default DRR constructor start. \n");

}

/**
 * \param numQueue  the number of queues.
 * \param priorityParams  a list of priority_level or weight. e.g. 300 200 100
 */
DRR::DRR (uint32_t numQueue, vector<uint32_t> priorityParams, uint32_t maxPacketCount) :
  m_counter (maxPacketCount * 3),
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
  DestinationPortNumber* destinationPortNumber0 = 0;
  destinationPortNumber0 = new DestinationPortNumber (portNum0);

  vector<FilterElement*> filterElements0;
  filterElements0.push_back(destinationPortNumber0);

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
  DestinationPortNumber* destinationPortNumber1 = 0;
  destinationPortNumber1 = new DestinationPortNumber (portNum1);

  vector<FilterElement*> filterElements1;
  filterElements1.push_back(destinationPortNumber1);

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
  DestinationPortNumber* destinationPortNumber2 = 0;
  destinationPortNumber2 = new DestinationPortNumber (portNum2);

  vector<FilterElement*> filterElements2;
  filterElements2.push_back(destinationPortNumber2);

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
DRR::GetRoundRobinPointer () const
{
  return m_roundRobinPointer;
}

uint32_t
DRR::Schedule ()
{
  printf("Schedule() in DRR start. \n");

  vector<TrafficClass*>* queuesPtr = GetQueuesPtr ();

  uint32_t numQueue = (*queuesPtr).size();
  uint32_t rrp = GetRoundRobinPointer ();
  while (m_counter > 0)
  {
    printf("m_counter: %u\n", m_counter);

    rrp = rrp % numQueue;
    //printf("rrp: %u\n", rrp);
    DrrQueue* queuePtr = (DrrQueue*)(*queuesPtr)[rrp];

    // Check if the queue is empty.
    uint32_t packetsCount = queuePtr->GetPacketsCount ();
    if (packetsCount <= 0)
    {
      // Move on to the next queue.
      //printf("This queue is empty. Move on to the next queue. \n");
      rrp++;
      continue;
    }

    // Add the quantum to the Deficit Counter of the queue.
    bool quantumFlag = queuePtr->GetQuantumFlag ();
    uint32_t quantum = 0;
    if (quantumFlag)
    {
      quantum = static_cast<uint32_t>(queuePtr->GetWeight ());
      queuePtr->SetQuantumFlag (false);
      printf("quantum added: %u\n", quantum);
    }
    uint32_t dc = queuePtr->GetDeficitCounter ();
    dc += quantum;

    // Check the size of the packet in the front and
    // Dequeue it if the Deficit Counter is larger than the size.
    Ptr<Packet> packet = queuePtr->Peek ();
    uint32_t packetSize = packet->GetSize ();
    if (dc >= packetSize)
    {
      printf("dc >= packetSize \n");
      // Update the Deficit Counter.
      if (packetsCount == 1)
      {
        // Queue is going to be empty. Set the DC to 0.
        dc = 0;
      }
      else
      {
        dc -= packetSize;
      }

      queuePtr->SetDeficitCounter (dc);
      SetRoundRobinPointer (rrp);

      printf("Schedule() in DRR end. Returns %u\n", rrp);
      m_counter--;
      return rrp;
    }
    else
    {
      // dc < packetSize
      printf("dc < packetSize \n");
      queuePtr->SetDeficitCounter (dc);
      queuePtr->SetQuantumFlag (true);
      rrp++;
    }

  } // end of while(true)

  return 0;
}

uint32_t
DRR::ScheduleForPeek () const
{
  printf("ScheduleForPeek() in DRR start. \n");

  const vector<TrafficClass*>* queuesPtr = GetQueuesPtrForPeek ();

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
      return rrp;
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
