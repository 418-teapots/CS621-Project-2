//To Run DDR: ./waf --run "cs621-dev02 --conf=DRR"
//To Run SPQ: ./waf --run "cs621-dev02 --conf=SPQ"
// Network topology (CS621 project 2)s
// client     queue      server
//  n0 ------- n1 -------n3
//

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include <climits>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <cstring>
#include <iomanip>
#include <map>


#include "ns3/ptr.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/histogram.h"
#include "ns3/flow-classifier.h"
#include "ns3/flow-probe.h"
#include "ns3/nstime.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/ipv4-flow-classifier.h"
#include "ns3/flow-monitor.h"
using std::cout;
using std::endl;

using namespace ns3;
std::string fileName = "";

void ThroughputMonitor (FlowMonitorHelper* fmhelper, Ptr<FlowMonitor> flowMon)
  {
    std::ofstream myFile;
    myFile.open(fileName, std::ios_base::app);
    flowMon->CheckForLostPackets();
    std::map<FlowId, FlowMonitor::FlowStats> flowStats = flowMon->GetFlowStats();
    Ptr<Ipv4FlowClassifier> classing = DynamicCast<Ipv4FlowClassifier> (fmhelper->GetClassifier());
    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator stats = flowStats.begin (); stats != flowStats.end (); ++stats)
    {
      Ipv4FlowClassifier::FiveTuple fiveTuple = classing->FindFlow (stats->first);
      if (fiveTuple.sourceAddress == Ipv4Address("10.1.1.1") && fiveTuple.destinationAddress == Ipv4Address("10.1.2.2")) {
        myFile << stats->first << "," << stats->second.timeLastRxPacket.GetSeconds() << "," << stats->second.rxPackets <<endl;

        std::cout<<"Flow ID     : " << stats->first <<" ; "<< fiveTuple.sourceAddress <<" -----> "<<fiveTuple.destinationAddress<<std::endl;
        std::cout<<"Number of Packets Received = " << stats->second.rxPackets <<std::endl;
        //std::cout<<"Duration    : "<<stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds()<<std::endl;
        std::cout<<"Last Received Packet  : "<< stats->second.timeLastRxPacket.GetSeconds()<<" Seconds"<<std::endl;
        //std::cout<<"Throughput: " << stats->second.rxBytes * 8.0 / (stats->second.timeLastRxPacket.GetSeconds()-stats->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps"<<std::endl;
        std::cout<<"---------------------------------------------------------------------------"<<std::endl;
      }
    }
    myFile.close();
      Simulator::Schedule(Seconds(0.5),&ThroughputMonitor, fmhelper, flowMon);


  }

NS_LOG_COMPONENT_DEFINE ("SimpleGlobalRoutingExample");

int main (int argc, char *argv[])
{
  //declare  of given variables

  uint32_t packetSize = 1000; //#size of the packets
  uint32_t maxPacketCount = 3000;//# of packets to send
  // std::string dataRate = "3Mbps";
  std::string dataRate = "1.6Mbps";
  std::string outputDataRate = "1Mbps";
  std::string configFile;
  std::vector<uint32_t> queueList;
  // Allow the user to override any of the defaults and the above
  CommandLine cmd;
  cmd.AddValue("conf", "Specify the config file", configFile);
  cmd.Parse (argc, argv);
  if (!(configFile == "DRR" || configFile == "SPQ" )) {
    std::cout << "You must specify the configuration file" << endl; // must specify compression link capacity
    return 0;
  }
  //initailze variables with values from config file
  std::ifstream cFile("config/" + configFile + ".txt");
  if (cFile.is_open())
  {
    cout << "Config file detected" << endl;
    std::string line;
    while(getline(cFile, line, ','))
    {
      queueList.push_back(std::stoi(line));
      cout << line << endl;
    }
  }
  else {
    cout << "No config file detected" << endl;
    return 0;
  }
  if (configFile == "SPQ") {
    dataRate = "3Mbps";
    outputDataRate = "1Mbps";
  }

  //Create three nodes and form a group
  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create (3);
  NodeContainer n0n1 = NodeContainer (c.Get (0), c.Get (1));
  NodeContainer n1n2 = NodeContainer (c.Get (1), c.Get (2));

  //install internet
  InternetStackHelper internet;
  internet.Install (c);

  // We create the channels first without any IP addressing information
  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue (dataRate));
  p2p.SetChannelAttribute ("Delay", StringValue ("10ms"));
  NetDeviceContainer d0d1 = p2p.Install (n0n1); //outer links
  p2p.SetDeviceAttribute ("DataRate", StringValue (outputDataRate));
  p2p.SetChannelAttribute ("Delay", StringValue ("10ms"));
  NetDeviceContainer d1d2 = p2p.Install (n1n2); //outer links

  //Add IP addresses
  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i0i1 = ipv4.Assign (d0d1);

  ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i1i2 = ipv4.Assign (d1d2);

  // Create router nodes, initialize routing database and set up the routing tables in the nodes.
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  // (Server)
  // Create a RequestResponseServer application on node three.

  NS_LOG_INFO ("Create Applications.");
  uint16_t port = 9;  // well-known echo port number
  RequestResponseServerHelper server (port);
  // uint32_t responseSize = 1024;
  // server.SetAttribute ("PacketSize", UintegerValue (responseSize));
  ApplicationContainer apps = server.Install (c.Get (2));
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (60.0));

  if (configFile == "SPQ") {
    fileName = "stats_SPQ.csv";
    Ptr<NetDevice> netDevice = d1d2.Get(0);
    Ptr<PointToPointNetDevice> p2pNetDevice = StaticCast<PointToPointNetDevice>(netDevice);
    Ptr<SPQ> spq = Create<SPQ>();
    p2pNetDevice->SetQueue(spq);

    // (Client)
    // Create a RequestResponseClient application to send UDP datagrams from node zero to node three.
    Time interPacketInterval = Seconds (0.01);
    RequestResponseClientHelper client (i1i2.GetAddress (1), 443);
    client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    client.SetAttribute ("Interval", TimeValue (interPacketInterval));
    client.SetAttribute ("PacketSize", UintegerValue (packetSize));
    apps = client.Install (c.Get (0));
    apps.Start (Seconds (5.0));
    apps.Stop (Seconds (60.0));

    RequestResponseClientHelper client2 (i1i2.GetAddress (1), 6881);
    client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
    client2.SetAttribute ("PacketSize", UintegerValue (packetSize));
    apps = client2.Install (c.Get (0));
    apps.Start (Seconds (2.0));
    apps.Stop (Seconds (60.0));
  }
  else { //DRR
    fileName = "stats_DRR.csv";
    Ptr<NetDevice> netDevice = d1d2.Get(0);
    Ptr<PointToPointNetDevice> p2pNetDevice = StaticCast<PointToPointNetDevice>(netDevice);
    Ptr<DRR> drr = Create<DRR>(3, queueList, maxPacketCount);
    p2pNetDevice->SetQueue(drr);
    // (Client)
    // Create a RequestResponseClient application to send UDP datagrams from node zero to node three.
    Time interPacketInterval = Seconds (0.01);
    RequestResponseClientHelper client (i1i2.GetAddress (1), 2048);
    client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    client.SetAttribute ("Interval", TimeValue (interPacketInterval));
    client.SetAttribute ("PacketSize", UintegerValue (packetSize));
    apps = client.Install (c.Get (0));
    apps.Start (Seconds (2.0));
    apps.Stop (Seconds (60.0));

    RequestResponseClientHelper client2 (i1i2.GetAddress (1), 2049);
    client2.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    client2.SetAttribute ("Interval", TimeValue (interPacketInterval));
    client2.SetAttribute ("PacketSize", UintegerValue (packetSize));
    apps = client2.Install (c.Get (0));
    apps.Start (Seconds (2.0));
    apps.Stop (Seconds (60.0));

    RequestResponseClientHelper client3 (i1i2.GetAddress (1), 2050);
    client3.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
    client3.SetAttribute ("Interval", TimeValue (interPacketInterval));
    client3.SetAttribute ("PacketSize", UintegerValue (packetSize));
    apps = client3.Install (c.Get (0));
    apps.Start (Seconds (2.0));
    apps.Stop (Seconds (60.0));
  }

  AsciiTraceHelper ascii;
  p2p.EnableAsciiAll (ascii.CreateFileStream ("cs621-dev02.tr"));
  p2p.EnablePcap("UDPsender.pcap",d0d1.Get(0), false, true);
  p2p.EnablePcap("MiddleNode.pcap",d1d2.Get(0), false, true);
  p2p.EnablePcap("UDPreceiver.pcap",d1d2.Get(1), false, true);

  //Flow Monitor
  //Use flow monitor to get stats on when the last packet in the packet train arrives
  std::ifstream file(fileName);
  if (file) {
    std::remove(fileName.c_str());
  }
  file.close();
  std::ofstream myfile(fileName);
  myfile << "flowID,timePacketReceived,numPackets" << endl;
  myfile.close();
  FlowMonitorHelper flowmonHelper;
  Ptr<FlowMonitor> monitor = flowmonHelper.InstallAll ();
  monitor->SetAttribute("DelayBinWidth", DoubleValue(0.001));
  monitor->SetAttribute("JitterBinWidth", DoubleValue(0.001));
  monitor->SetAttribute("PacketSizeBinWidth", DoubleValue(20));
  NS_LOG_INFO ("Run Simulation.");
  //Simulator::Schedule(Seconds(0.2),&sendHandler,udp, nodes2, Ptr<Packet>(&a));
  Simulator::Stop (Seconds (60));
  ThroughputMonitor(&flowmonHelper ,monitor);
  Simulator::Run ();
  NS_LOG_INFO ("Done.");

  Simulator::Destroy ();

  return 0;
}
