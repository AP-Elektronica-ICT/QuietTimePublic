#ESP8266

Wat is er niet gelukt?

Wat had het kunnen worden?

#RF24 
Na al onze pogingen om een draadloos netwerk te bouwen, grijpen we terug naar de basis. Dankzij opzoekwerk had ik een bibliotheek gevonden om via RF een draadloos mesh netwerk te bouwen. RF (Radiofrequent) hebben we al gebruikt tijdens het labo van IoT. We hebben toen gebruik gemaakt van de nrf24l01. We wisten sowieso dat deze modules werkten, en we hadden er ook veel op het school.

Beide vorige pogingen miste één van deze kenmerken. De RF modules hadden twee groote nadelen. 
-  Standalone is onmogelijk
-  Timeslots, kanaal reservingen (wie mag er zenden), ...

Het eerste nadeel kunnen we niet oplossen met onze nrf24l01 modules, er zal steeds aan elke sensor een Arduino moeten hangen. In de praktijk kunnen we een zeer kleine Arduino gebruiken (Arduino Nano, Arduino Mini, ...).

Het tweede nadeel, lost onze bibliotheek op. In ons mesh netwerk zal er één node master zijn (Raspberry Pi), en zullen er verschillende sensor nodes zijn (Arduino + Microfoon). Deze "slaves" zullen data verzenden naar onze master. Maar dit moet uiteraard geregeld worden. Zo zijn er verschillende adressen die geconfigureerd moeten worden, moeten er "reading" en "writing" pipes geopend worden om te communiceren en nog veel meer. Wat bijvoorbeeld als er twee nodes tegelijk zenden en etc. Dit probleem is ondertussen al opgelost en dat netwerk noemen we het internet :). Er is echter ook een bibliotheek voor RF die gelijkaardige functionaliteit toevoegd aan ons project. Deze bibliotheek is zelfs TCP/IP stack compatibel. Zo is er DHCP, ARP, ... functionaliteit beschikbaar.

Zo we moeten ons al geen zorgen meer maken over deze zaken hier zorgt de RF24Mesh bibliotheek wel voor...</br>
TMRh20 heeft een fork gemaakt van de origele RF24 bibliotheek, en heeft deze verbeterd (under statement) en uitgebreid. Hij is ook de ontwikkelaar van de RF24Netwerk (Netwerk laag, DHCP functionaliteit, ...) en RF24Mesh bibliotheek. Hij heeft alles zeer goed gedocumenteerd! Ik raad zeker aan om zijn documentatie eens een kijkje te geven

- RF24 (fork van het origineel) => [LINK](http://tmrh20.github.io/RF24/)
- RF24Netwerk (netwerk layer van het OSI model) => [LINK](http://tmrh20.github.io/RF24Network/)
- RF24Mesh => [LINK](http://tmrh20.github.io/RF24Mesh/classRF24Mesh.html)

Door de schitterende documentatie is het gebruik van deze bibliotheken echt gemakkelijk. Indien je deze in Arduino wilt gebruiken kun je gebruik maken van de 'Bibliotheekbeheerder'. Door te zoeken naar RF24 kun je de 3 bibliotheken vinden. Nadat je deze geïnstaleerd hebt zullen ook de examples tevoorschijn komen bij *Bestand -> Voorbeelden*.

![Bibliotheekbeheerder](http://i.imgur.com/0VG4MqV.png)

In het labo hebben we ineens geprobeerd RF24Mesh te testen, dit lukte niet. Thuis heb ik besloten om alles stap voor stap te testen. Te beginnen bij de basis, RF24/GettingStarted. Dit is eigenlijk LABO2 van tijdens de labosessies van IoT. Dit werkte niet van de 1ste keer. Toen heb ik gewoon onze sketch van Labo2 geprobeerd en kwam ik tot de conclusie dat de rf module niet werkte. Later bleek dat hij wel werkte maar de connecties 'zwak' waren. Als je er mee schudde werkte hij wel. Dit terzijde.

Ik had gelukkig nog een 3de RF module meegenomen naar huis, en heb eerst terug onze sketch van LABO2 geprobeerd. Dit werkte en daarna de GettingStarted sketch en na een paar aanpassingen werkte dit ook. Zo we hadden een basis waar we verder mee konden.

Mijn volgende stap was om één van de Arduino's te vervangen door onze Raspberry Pi2. Allereerst moesten we de RF module verbinden met onze Raspberry Pi2, dit gaat via de 40 pins header. 

![Pinlayout RPi24](https://ms-iot.github.io/content/images/PinMappings/RP2_Pinout.png)

Je kunt hier duidelijk de pinnen voor SPI zien! 

**TODO Volledige PIN LAYOUT**

Als volgt moest ik de RF24 bibliotheken installeren op onze RPi 2. Ik heb dit gedaan door de volgende stappen te volgen:

[Installatie process op Raspberry Pi](http://tmrh20.github.io/RF24/RPi.html)

Hierin wordt dus verteld hoe ik de code van alle RF24 bibliotheken op mijn RPi krijg, er bevind zich ook een map bij waarin examples voor de RPi staan. We builden de bestanden in de juiste map */home/IoT/rf24libs/RF24/examples_RPi*. En we voeren op de RPi ook de GettingStarted sketch uit. Dit werkte!



#RaspPI code 
(RF24, Tee, Tail, ...)

#NodeRED
(Werking, code)
