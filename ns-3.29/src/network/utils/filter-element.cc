#include "filter-element.h"

namespace ns3 {

// Constructor
FilterElement::FilterElement () {

}
// Destructor
FilterElement::~FilterElement () {

}

bool
FilterElement::match (Ptr<Packet> p) {
  
  return false;
}

std::string
FilterElement::GetSrcIpAddr (Ptr<Packet> packet) {

  PacketMetadata::ItemIterator i = packet->BeginItem ();
  while (i.HasNext ())
  {
     PacketMetadata::Item item = i.Next ();
     std::string headerName = item.tid.GetName ();

     if (item.type == PacketMetadata::Item::HEADER && headerName == "ns3::Ipv4Header")
     {
        // std::cout << headerName << " (";

        {
          Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
          ObjectBase *instance = constructor ();
          Chunk *chunk = dynamic_cast<Chunk *> (instance);

          // Buffer::Iterator start = item.current;
          Buffer::Iterator end = item.current;
          // printf(" item.currentSize: %u ", item.currentSize);
          // start.Next (4);
          // end.Next (5);
          // end.Next (item.currentSize); 
          end.Next (item.currentSize); // move from start 
          chunk->Deserialize (item.current, end);
          // chunk->Deserialize (start, end);
          // chunk->Print (std::cout);


          std::ostringstream oss;
          chunk->Print (oss);
          std::string content = oss.str();
          // std::cout << "content: " << content;

          // Split. 
          std::vector<std::string> result;
          std::istringstream iss(content);
          for(std::string s; iss >> s; )
          {
            result.push_back(s);
          }
    
          delete chunk;

          return result[19];
          // std::cout << "src IP addr: " << result[19];
          // std::cout << " dest IP addr: " << result[21];
        }

     }

  }

  return 0;
}

std::string
FilterElement::GetDestIpAddr (Ptr<Packet> packet) {

  PacketMetadata::ItemIterator i = packet->BeginItem ();
  while (i.HasNext ())
  {
     PacketMetadata::Item item = i.Next ();
     std::string headerName = item.tid.GetName ();

     if (item.type == PacketMetadata::Item::HEADER && headerName == "ns3::Ipv4Header")
     {
        // std::cout << headerName << " (";

        {
          Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
          ObjectBase *instance = constructor ();
          Chunk *chunk = dynamic_cast<Chunk *> (instance);

          // Buffer::Iterator start = item.current;
          Buffer::Iterator end = item.current;
          // printf(" item.currentSize: %u ", item.currentSize);
          // start.Next (4);
          // end.Next (5);
          // end.Next (item.currentSize); 
          end.Next (item.currentSize); // move from start 
          chunk->Deserialize (item.current, end);
          // chunk->Deserialize (start, end);
          // chunk->Print (std::cout);


          std::ostringstream oss;
          chunk->Print (oss);
          std::string content = oss.str();
          // std::cout << "content: " << content;

          // Split. 
          std::vector<std::string> result;
          std::istringstream iss(content);
          for(std::string s; iss >> s; )
          {
            result.push_back(s);
          }

          delete chunk;

          return result[21];
          // std::cout << "src IP addr: " << result[19];
          // std::cout << " dest IP addr: " << result[21];
        }

     }

  }

  return 0;
}


uint32_t
FilterElement::GetSrcPortNum (Ptr<Packet> packet) {

  PacketMetadata::ItemIterator i = packet->BeginItem ();
  while (i.HasNext ())
  {
     PacketMetadata::Item item = i.Next ();
     std::string headerName = item.tid.GetName ();

     if (item.type == PacketMetadata::Item::HEADER && headerName == "ns3::UdpHeader")
     {
        // std::cout << headerName << " (";

        {
          Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
          ObjectBase *instance = constructor ();
          Chunk *chunk = dynamic_cast<Chunk *> (instance);

          // Buffer::Iterator start = item.current;
          Buffer::Iterator end = item.current;
          // printf(" item.currentSize: %u ", item.currentSize);
          // start.Next (4);
          // end.Next (5);
          // end.Next (item.currentSize); 
          end.Next (item.currentSize); // move from start 
          chunk->Deserialize (item.current, end);
          // chunk->Deserialize (start, end);
          // chunk->Print (std::cout);


          std::ostringstream oss;
          chunk->Print (oss);
          std::string content = oss.str();
          // std::cout << "content: " << content;

          // Split. 
          std::vector<std::string> result;
          std::istringstream iss(content);
          for(std::string s; iss >> s; )
          {
            result.push_back(s);
          }

          delete chunk;

          return (uint32_t) std::stoi(result[2]);
          // std::cout << "src port: " << result[2];
          // std::cout << " dest port: " << result[4];
        }

     }

  }

  return 0;
}

uint32_t
FilterElement::GetDestPortNum (Ptr<Packet> packet) {

  PacketMetadata::ItemIterator i = packet->BeginItem ();
  while (i.HasNext ())
  {
     PacketMetadata::Item item = i.Next ();
     std::string headerName = item.tid.GetName ();

     if (item.type == PacketMetadata::Item::HEADER && headerName == "ns3::UdpHeader")
     {
        // std::cout << headerName << " (";

        {
          Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
          ObjectBase *instance = constructor ();
          Chunk *chunk = dynamic_cast<Chunk *> (instance);

          // Buffer::Iterator start = item.current;
          Buffer::Iterator end = item.current;
          // printf(" item.currentSize: %u ", item.currentSize);
          // start.Next (4);
          // end.Next (5);
          // end.Next (item.currentSize); 
          end.Next (item.currentSize); // move from start 
          chunk->Deserialize (item.current, end);
          // chunk->Deserialize (start, end);
          // chunk->Print (std::cout);


          std::ostringstream oss;
          chunk->Print (oss);
          std::string content = oss.str();
          // std::cout << "content: " << content;

          // Split. 
          std::vector<std::string> result;
          std::istringstream iss(content);
          for(std::string s; iss >> s; )
          {
            result.push_back(s);
          }

          delete chunk;

          return (uint32_t) std::stoi(result[4]);
          // std::cout << "src port: " << result[2];
          // std::cout << " dest port: " << result[4];
        }

     }

  }

  return 0;
}

uint32_t
FilterElement::GetProtocolNum (Ptr<Packet> packet) {

  PacketMetadata::ItemIterator i = packet->BeginItem ();
  while (i.HasNext ())
  {
     PacketMetadata::Item item = i.Next ();
     std::string headerName = item.tid.GetName ();

     if (item.type == PacketMetadata::Item::HEADER && headerName == "ns3::Ipv4Header")
     {
        // std::cout << headerName << " (";

        {
          Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
          ObjectBase *instance = constructor ();
          Chunk *chunk = dynamic_cast<Chunk *> (instance);

          // Buffer::Iterator start = item.current;
          Buffer::Iterator end = item.current;
          // printf(" item.currentSize: %u ", item.currentSize);
          // start.Next (4);
          // end.Next (5);
          // end.Next (item.currentSize); 
          end.Next (item.currentSize); // move from start 
          chunk->Deserialize (item.current, end);
          // chunk->Deserialize (start, end);
          // chunk->Print (std::cout);


          std::ostringstream oss;
          chunk->Print (oss);
          std::string content = oss.str();
          // std::cout << "content: " << content;

          // Split. 
          std::vector<std::string> result;
          std::istringstream iss(content);
          for(std::string s; iss >> s; )
          {
            result.push_back(s);
          }

          delete chunk;

          return (uint32_t) std::stoi(result[11]);
          // std::cout << "src port: " << result[2];
          // std::cout << " dest port: " << result[4];
        }

     }

  }

  return 0;
}


// uint32_t
// FilterElement::GetSrcPortNum (Ptr<Packet> packet) {

//   PacketMetadata::ItemIterator i = packet->BeginItem ();
//   while (i.HasNext ())
//   {
//      PacketMetadata::Item item = i.Next ();
//      std::string headerName = item.tid.GetName ();

//      if (item.type == PacketMetadata::Item::HEADER && 
//          (headerName == "ns3::UdpHeader" || headerName == "ns3::Ipv4Header"))
//      {
//         // std::cout << headerName << " (";

//         {
//           Callback<ObjectBase *> constructor = item.tid.GetConstructor ();
//           ObjectBase *instance = constructor ();
//           Chunk *chunk = dynamic_cast<Chunk *> (instance);

//           // Buffer::Iterator start = item.current;
//           Buffer::Iterator end = item.current;
//           // printf(" item.currentSize: %u ", item.currentSize);
//           // start.Next (4);
//           // end.Next (5);
//           // end.Next (item.currentSize); 
//           end.Next (item.currentSize); // move from start 
//           chunk->Deserialize (item.current, end);
//           // chunk->Deserialize (start, end);
//           // chunk->Print (std::cout);


//           std::ostringstream oss;
//           chunk->Print (oss);
//           std::string content = oss.str();
//           // std::cout << "content: " << content;

//           // Split. 
//           std::vector<std::string> result;
//           std::istringstream iss(content);
//           for(std::string s; iss >> s; )
//           {
//             result.push_back(s);
//           }

//           if (headerName == "ns3::UdpHeader")
//           {
//             return (uint32_t) std::stoi(result[2]);
//             // std::cout << "src port: " << result[2];
//             // std::cout << " dest port: " << result[4];
//           } 
//           else if (headerName == "ns3::Ipv4Header")
//           {
//             // std::cout << "src IP addr: " << result[19];
//             // std::cout << " dest IP addr: " << result[21];
//           }

//           delete chunk;
//         }

//         if (headerName == "ns3::UdpHeader")
//         {
//           // std::cout << ")";
//           break;
//         } 

//      }

//      if (i.HasNext ())
//      {
//         std::cout << " | ";
//      }
//   }

//   return 0;
// }





} // namespace ns3
