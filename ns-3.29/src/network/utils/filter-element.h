#ifndef FILTER_ELEMENT_H_
#define FILTER_ELEMENT_H_

#include "ns3/pointer.h"
#include "ns3/packet.h"


using namespace std;

namespace ns3 {

/**
 * A base class for a primitive condition to match on. You should write one subclass for every 
 * seven (light purple) boxes in the design diagram. 
 */
class FilterElement
{
public:
  FilterElement ();
  virtual ~FilterElement ();

  virtual bool match(Ptr<Packet> p);
  

  /**
   * CS621 Project 2
   */
  // std::string GetSrcIpAddr (Ptr<Packet> p);
  // std::string GetDestIpAddr (Ptr<Packet> p);
  uint32_t GetSrcPortNum (Ptr<Packet> p);
  // std::string GetDestPortNum (Ptr<Packet> p);

};


class SourceIPAddress : public FilterElement 
{
public:
  SourceIPAddress (Ipv4Address ipv4Address) : 
    value(ipv4Address)
  {

  }

  virtual ~SourceIPAddress ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  Ipv4Address value;

};

class SourceMask : public FilterElement 
{
public:
  SourceMask (Ipv4Mask ipv4Mask) : 
    value(ipv4Mask)
  {

  }

  virtual ~SourceMask ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  Ipv4Mask value;

};

class SourcePortNumber : public FilterElement 
{
public:
  SourcePortNumber (uint32_t portNumber) : 
    value(portNumber)
  {

  }

  virtual ~SourcePortNumber ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    uint32_t srcPort = GetSrcPortNum (p);
    return srcPort == value;
  }

private:

  uint32_t value;

};

class DestinationIPAddress : public FilterElement 
{
public:
  DestinationIPAddress (Ipv4Address ipv4Address) : 
    value(ipv4Address)
  {

  }

  virtual ~DestinationIPAddress ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  Ipv4Address value;

};

class DestinationMask : public FilterElement 
{
public:
  DestinationMask (Ipv4Mask ipv4Mask) : 
    value(ipv4Mask)
  {

  }

  virtual ~DestinationMask ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  Ipv4Mask value;

};

class DestinationPortNumber : public FilterElement 
{
public:
  DestinationPortNumber (uint32_t portNumber) : 
    value(portNumber)
  {

  }

  virtual ~DestinationPortNumber ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  uint32_t value;

};

class ProtocolNumber : public FilterElement 
{
public:
  ProtocolNumber (uint32_t protocolNumber) : 
    value(protocolNumber)
  {

  }

  virtual ~ProtocolNumber ()
  {

  }

  bool match(Ptr<Packet> p)
  {
    // TODO
    // return p->?? == value;
    return 0;
  }

private:

  uint32_t value;

};

















} // namespace ns3

#endif /* FILTER_ELEMENT_H_ */


