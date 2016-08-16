# simple DoIP parser
A simple Diagnostics over IP (DoIP) parser written in C. It does leverage [hammer](https://github.com/UpstandingHackers/hammer)
to be more reliable. This parser accepts DoIP messages which follow the
general format according to ISO 13400-2 and AUTOSAR 4.2.2. It can be used to develop
tools for vehicle diagnostics and poke at automotive security.
A more powerful parser which validates individual messages is available upon request.

# ressources
* [Specification of Diagnostic over IP](http://www.autosar.org/fileadmin/files/releases/4-2/software-architecture/diagnostic-services/standard/AUTOSAR_SWS_DiagnosticOverIP.pdf) according to [AUTOSAR](http://www.autosar.org) 4.2.2
* [DoIP and Advanced Diagnostics Using Ethernet in the Vehicle](https://www.mentor.com/embedded-software/resources/overview/doip-and-advanced-diagnostics-using-ethernet-in-the-vehicle-aa7f4020-8e33-4c3f-9975-22e345ca91cc) by Mentor Graphics

