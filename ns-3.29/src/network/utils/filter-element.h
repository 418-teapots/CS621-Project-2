#ifndef FILTER_ELEMENT_H_
#define FILTER_ELEMENT_H_

#include "ns3/pointer.h"
#include "ns3/packet.h"
#include "ipv4-address.h"



// using namespace std;

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
  
  std::string GetSrcIpAddr (Ptr<Packet> p);
  std::string GetDestIpAddr (Ptr<Packet> p);
  uint32_t GetSrcPortNum (Ptr<Packet> p);
  uint32_t GetDestPortNum (Ptr<Packet> p);
  uint32_t GetProtocolNum (Ptr<Packet> p);


};


class SourceIPAddress : public FilterElement 
{
public:
  SourceIPAddress (Ipv4Address ipv4Address) : 
    m_srcIpAddr(ipv4Address)
  {

  }

  virtual ~SourceIPAddress ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    std::string srcIpAddrStr = GetSrcIpAddr (packet);
    Ipv4Address srcIpAddr = Ipv4Address (srcIpAddrStr.c_str());
    return srcIpAddr.IsEqual (m_srcIpAddr);
  }

private:

  Ipv4Address m_srcIpAddr;

};

class SourceMask : public FilterElement 
{
public:
  SourceMask (Ipv4Mask ipv4Mask, Ipv4Address ipv4Address) : 
    m_srcMask(ipv4Mask), 
    m_srcIpAddrForSubNet(ipv4Address)
  {

  }

  virtual ~SourceMask ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    std::string srcIpAddrStr = GetSrcIpAddr (packet);
    Ipv4Address srcIpAddr = Ipv4Address (srcIpAddrStr.c_str());
    return m_srcMask.IsMatch(srcIpAddr, m_srcIpAddrForSubNet);
  }

private:

  Ipv4Mask m_srcMask;
  Ipv4Address m_srcIpAddrForSubNet;

};

class SourcePortNumber : public FilterElement 
{
public:
  SourcePortNumber (uint32_t portNumber) : 
    m_srcPortNum(portNumber)
  {

  }

  virtual ~SourcePortNumber ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    uint32_t srcPortNum = GetSrcPortNum (packet);
    return srcPortNum == m_srcPortNum;
  }

private:

  uint32_t m_srcPortNum;

};

class DestinationIPAddress : public FilterElement 
{
public:
  DestinationIPAddress (Ipv4Address ipv4Address) : 
    m_destIpAddrStr(ipv4Address)
  {

  }

  virtual ~DestinationIPAddress ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    std::string destIpAddrStr = GetDestIpAddr (packet);
    Ipv4Address destIpAddr = Ipv4Address (destIpAddrStr.c_str());
    return destIpAddr.IsEqual (m_destIpAddrStr);
  }

private:

  Ipv4Address m_destIpAddrStr;

};

class DestinationMask : public FilterElement 
{
public:
  DestinationMask (Ipv4Mask ipv4Mask, Ipv4Address ipv4Address) : 
    m_destMask(ipv4Mask), 
    m_destIpAddrForSubNet(ipv4Address)
  {

  }

  virtual ~DestinationMask ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    std::string destIpAddrStr = GetDestIpAddr (packet);
    Ipv4Address destIpAddr = Ipv4Address (destIpAddrStr.c_str());
    return m_destMask.IsMatch(destIpAddr, m_destIpAddrForSubNet);
  }

private:

  Ipv4Mask m_destMask;
  Ipv4Address m_destIpAddrForSubNet;

};

class DestinationPortNumber : public FilterElement 
{
public:
  DestinationPortNumber (uint32_t portNumber) : 
    m_destPortNum(portNumber)
  {

  }

  virtual ~DestinationPortNumber ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    uint32_t destPortNum = GetDestPortNum (packet);
    return destPortNum == m_destPortNum;
  }

private:

  uint32_t m_destPortNum;

};

class ProtocolNumber : public FilterElement 
{
public:
  ProtocolNumber (uint32_t protocolNumber) : 
    m_protocolNum(protocolNumber)
  {

  }

  virtual ~ProtocolNumber ()
  {

  }

  bool match(Ptr<Packet> packet)
  {
    uint32_t protocolNum = GetProtocolNum (packet);
    return protocolNum == m_protocolNum;
  }

private:

  uint32_t m_protocolNum;

};

















} // namespace ns3

#endif /* FILTER_ELEMENT_H_ */


