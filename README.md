# CS621-Project-2
https://docs.google.com/presentation/d/1VV-1ngyyMgo-Q9YdXSRjuxhnVsX-THiMQAzee5MXspY/edit?usp=sharing   
Project 1 report: https://www.overleaf.com/5567836938cvzgshctgkrd      
Project 2 report: https://www.overleaf.com/4439697492dtgztcbqjjzh    

## Overview
The ultimate purpose of this project is to learn about and implement a selection of differentiated services. Because
there is a large amount of shared structure amongst differentiated services, it is a practical exercise to start by
creating a base class. The API for the base class is laid out for you. Your assignment is to implement it.
After completion of the base class, you will implement two differentiated services: SPQ and DRR. Refer to Lecture
10 and the corresponding reading assignments for a detailed discussion of these services. To conclude the project, you
will validate and verify your implemented services. This will require creating and running various ns-3 applications
and simulations.

## Installation/Usage Guide
Refer to [Technical Manual](Technical_Manual.md)

## Project Outcomes
1. Build a base class for Differentiated Services in ns-3.
2. Implement Strict Priority Queueing (SPQ) and Deficit Round Robin (DRR), using the base class.
3. Validate and verify your SPQ and DRR implementations
## Components
### (1) DiffServ: A Base Class to Simulate Differentiated Services
DiffServ class provides basic functionalities required to simulate differentiated services:
• Classification - The classify function utilizes filter aspect to sort the traffic packets into appropriate traffic
queues.
• Scheduling - The schedule function carries out designed Quality-of-Service (QoS) algorithm to schedule which
traffic queue to be served at the time.
Two separate functions need to be implemented per QoS algorithm design of the developers choice. For network
queues, DoEnqueue() and DoDequeue() functions can be overwritten to meet implementation requirements for
various QoS algorithms.
Your base class will be a subclass of ns-3::Queue, as such you should start this project out by learning in detail
the ns-3::Queue API reference and the closely related ns-3::DropTailQueue API reference.
Your base class should follow the requirements laid out in the UML diagram in Figure 1.
Here is a short description detailing the role of some of classes in the figure and their members.
• DiffServ
– m mode - The QueueMode specifies whether service is in byte mode or packet mode.
– q class - The vector (array) of TrafficClass pointers. setMode()/getMode() - the accessor and modifier
for private variable m mode.
– Schedule() - Returns a packet to transmit.
Figure 1: Base Class Design
– Classify(p) - Takes a packet and returns an integer.
• TrafficClass - Defines the characteristics of a queue.
– bytes - the count of bytes in the queue.
– packets - the count of packets in the queue.
– maxPackets - the maximum number of packets allowed in the queue.
– maxBytes - the maximum number of bytes allowed in the queue.
– weight - applicable if the QoS mechanism uses weight.
– priority level - applicable if the QoS mechanism uses priority level.
– filters - A collection of conditions as Filters, any of which should match in order to trigger match.
• Filter - A collection of conditions as FilterElements, all of which should match in order to trigger match.
Refer to Figure 2 for an example.
– elements - the array of pointers to FilterElement.
• FilterElement - a base class for a primitive condition to match on. You should write one subclass for every
seven (light purple) boxes in the design diagram. Refer to Figure 2 for an example.
### (2) Implementing SPQ and DRR with DiffServ
You will make two separate implementations, one implementing Strict Priority Queueing, and the other implementing DRR, both using your implemented DiffServ class.
Your SPQ implementation should take exactly one command line input, the name of a config file. In that file you
should specify the number of queues and a priority level for each queue.
Your DRR implementation should also take only that one input for the config file. It specifies the number of queues
and the corresponding quantum value for each queue.
Extra Credit: Implement a parser for your config file for SPQ, so that the config file is a sequence of CLI commands
for Cisco Catalyst 3750 switch.
Figure 2: An example of how users of your base class will be able to match any boolean condition given the right
set of Filters and FilterElements.
### (3) Simulation Verification and Validation
As the last part of your project, you are to create ns-3 applications and simulations to demonstrate the correctness
of your implementations above. For both SPQ and DRR, create a 3-node topology (set data-rates to 4-1 Mps),
where the middle node is a QoS-enabled router and two outer nodes are end-hosts running simple client/server
bulk data transfer applications.
To validate SPQ, you should create two client server applications A and B. Configure the router on the path so
that, A traffic is prioritized over B. Application A should begin sometime after application B starts. In this case,
your router has two queues.
For your DRR verification, you should initialize three queues with quanta ratio 3:2:1. Then, start three client-server
bulk data transfer applications, all starting at the same time.
For both simulations your demonstration should include a plot of throughput vs. time for all applications. An
example of throughput vs. time plot is provided in Figure 3.
## Collaborators 
Kei Fukutani - kayfuku - kfukutani@usfca.edu   
Domingo Huang - DomingoWong - yhuang158@dons.usfca.edu  
Tae Lee - leeth7830  


