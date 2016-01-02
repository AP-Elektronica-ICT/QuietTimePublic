#ESP8266

Wat is er niet gelukt?

Wat had het kunnen worden?

#RF24 
Na al onze pogingen om een draadloos netwerk te bouwen, grijpen we terug naar de basis. Dankzij opzoekwerk had ik een bibliotheek gevonden om via RF een draadloos mesh netwerk te bouwen. RF (Radiofrequent) hebben we al gebruikt tijdens het labo van IoT. We hebben toen gebruik gemaakt van de nrf24l01. We wisten sowieso dat deze modules werkten, en we hadden er ook veel op het school.

Beide vorige pogingen miste één van deze kenmerken. De RF modules hadden twee groote nadelen. 
-  Standalone is onmogelijk
-  Timeslots, kanaal reservingen, ... (Wie mag er zenden, reserving).

Het eerste nadeel kunnen we niet oplossen met onze nrf24l01 modules, er zal steeds aan elke sensor een Arduino moeten hangen. In de praktijk kunnen we een zeer kleine Arduino gebruiken (Arduino Nano, Arduino Mini, ...).

Het tweede nadeel, lost onze bibliotheek op. In ons mesh netwerk zal er één node master zijn (Raspberry Pi), en zullen er verschillende sensor nodes zijn (Arduino + Microfoon). Deze "slaves" zullen data verzenden naar onze master. Maar dit moet uiteraard geregeld worden. Zo zijn er verschillende adressen die geconfigureerd moeten worden, moeten er "reading" en "writing" pipes geopend worden om te communiceren en nog veel meer. Wat bijvoorbeeld als er twee nodes tegelijk zenden en etc. Dit probleem is ondertussen al opgelost en dat netwerk noemen we het internet :). Er is echter ook een bibliotheek voor RF die gelijkaardige functionaliteit toevoegd aan ons project. Deze bibliotheek is zelfs TCP/IP stack compatibel. Zo is er DHCP, ARP, ... functionaliteit beschikbaar.

Zo we moeten ons al geen zorgen meer maken over deze zaken hier zorgt de RF24Mesh bibliotheek wel voor...</br>
TMRh20 heeft een fork gemaakt van de origele RF24 bibliotheek, en heeft deze verbeterd (under statement) en uitgebreid. Hij is ook de ontwikkelaar van de RF24Netwerk (Netwerk laag, DHCP functionaliteit, ...) en RF24Mesh bibliotheek. Hij heeft alles zeer goed gedocumenteerd! Ik raad zeker aan om zijn documentatie eens een kijkje te geven

- RF24 (fork van het origineel) => [LINK](http://tmrh20.github.io/RF24/)
- RF24Netwerk (netwerk layer van het OSI model) => [LINK](http://tmrh20.github.io/RF24Network/)
- RF24Mesh => [LINK](http://tmrh20.github.io/RF24Mesh/classRF24Mesh.html)


(Uitleg, bibliotheken, .....)

#RaspPI code 
(RF24, Tee, Tail, ...)

#NodeRED
(Werking, code)
