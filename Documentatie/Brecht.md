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

Hier moeten we ons al geen zorgen meer om maken. De RF24Mesh bibliotheek zorgt hier wel voor...</br>
TMRh20 heeft een fork gemaakt van de origele RF24 bibliotheek, en heeft deze verbeterd (under statement) en uitgebreid. Hij is ook de ontwikkelaar van de RF24Netwerk (Netwerk laag, DHCP functionaliteit, ...) en RF24Mesh bibliotheek. Hij heeft alles zeer goed gedocumenteerd! Ik raad zeker aan om zijn documentatie eens een kijkje te geven 

- RF24 (fork van het origineel) => [LINK](http://tmrh20.github.io/RF24/)
- RF24Netwerk (netwerk layer van het OSI model) => [LINK](http://tmrh20.github.io/RF24Network/)
- RF24Mesh => [LINK](http://tmrh20.github.io/RF24Mesh/classRF24Mesh.html)

Door de schitterende documentatie is het gebruik van deze bibliotheken echt gemakkelijk. Indien je deze in Arduino wilt gebruiken kun je gebruik maken van de 'Bibliotheekbeheerder'. Door te zoeken naar RF24 kun je de 3 bibliotheken vinden. Nadat je deze geïnstaleerd hebt zullen ook de examples tevoorschijn komen bij *Bestand -> Voorbeelden*.

![Bibliotheekbeheerder](http://i.imgur.com/0VG4MqV.png)

In het labo hebben we ineens geprobeerd de RF24Mesh te testen, dit lukte niet. Thuis heb ik besloten om alles stap voor stap te testen. Te beginnen bij de basis, RF24/GettingStarted. Dit is eigenlijk LABO2 van tijdens de labosessies van IoT. Dit werkte niet van de 1ste keer. Toen heb ik gewoon onze sketch van Labo2 geprobeerd en kwam ik tot de conclusie dat de rf module niet werkte. Later bleek dat hij wel werkte maar de connecties 'zwak' waren. Als je er mee schudde werkte hij wel. Dit terzijde.

Ik had gelukkig nog een 3de RF module meegenomen naar huis en heb als eerst terug onze sketch van LABO2 geprobeerd. Dit werkte en daarna de GettingStarted sketch en na een paar aanpassingen werkte dit ook. Zo we hadden een basis waar we verder mee konden.

Mijn volgende stap was om één van de Arduino's te vervangen door onze Raspberry Pi2. Allereerst moesten we de RF module verbinden met onze Raspberry Pi2, dit gaat via de 40 pins header. 

![Pinlayout RPi24](https://ms-iot.github.io/content/images/PinMappings/RP2_Pinout.png)

Je kunt hier duidelijk de pinnen voor SPI zien! 

**TODO Volledige PIN LAYOUT**

Als volgende stap moest ik de RF24 bibliotheken installeren op onze RPi 2. Ik heb dit gedaan door de volgende stappen te volgen:

[Installatie process op Raspberry Pi](http://tmrh20.github.io/RF24/RPi.html)

Hierin wordt dus verteld hoe ik de code van alle RF24 bibliotheken op mijn RPi krijg, er bevind zich ook een map bij waarin examples voor de RPi staan. We builden de bestanden in de juiste map */home/IoT/rf24libs/RF24/examples_RPi*. En we voeren op de RPi ook de GettingStarted sketch uit. Dit werkte!

> [Code Arduino](http://tmrh20.github.io/RF24/GettingStarted_8ino-example.html) </br>
> [Code RPi2](http://tmrh20.github.io/RF24/GettingStarted_8cpp-example.html)

Als volgende stap heb ik eerst RF24Network getest. De RF24Mesh bibliotheek maakt hier gebruik van, dus wou ik eerst zeker zijn dat dit werkte. Ik test eerst helloworld_tx op Arduino en helloworld_rw op RPi2 en hierna andersom. Beide situaties werkten!

> [Arduino Helloworld_tx](http://tmrh20.github.io/RF24Network/helloworld_tx_8ino-example.html)</br>
> [Arduino Helloworld_rx](http://tmrh20.github.io/RF24Network/helloworld_rx_8ino-example.html)

> [RPi Helloworld_tx](https://github.com/TMRh20/RF24Network/blob/master/examples_RPi/helloworld_rx.cpp)</br>
> [RPi Helloworld_rx](https://github.com/TMRh20/RF24Network/blob/master/examples_RPi/helloworld_rx.cpp)

Onze logische volgende stap is de examples testen voor de RF24Mesh bibliotheek. Op de Arduino zullen we de 'slave' sketch starten en op de RPi de 'master' sketch. De master node is de node die de adressen en etc. zal verdelen. Deze sketch wordt verder in deze tekst uitgelegd. Deze keer werkte het van de 1ste keer.

![Het werkt](http://i.imgur.com/ovVwfA2.jpg)

> [Code Arduino](http://tmrh20.github.io/RF24Mesh/RF24Mesh_Example_8ino-example.html)</br>
> [Code RPi2](http://tmrh20.github.io/RF24Mesh/RF24Mesh_Example_Master_8cpp-example.html)

Nu we dit werkend hebben, is het de bedoeling dat we ons netwerk uitbreiden. We moeten dus een extra sensor in het netwerk koppelen.
We doen dit door de Arduino code nog eens up te loaden naar een andere Arduino met RF zender. Het enigste wat we moeten aanpassen is de NodeID, 2 keer dezelfde mag niet voorkomen in het zelfde netwerk (vgl met MAC adres). Dit werkt ook! Ons mesh netwerk is gebouwd!

![Twee nodes](http://i.imgur.com/4cOcbdp.png)

De laatste stappen zijn de Arduino code integreren in de sketch van de Microfoon (@Arne Schoonvliet) en de sketch van de RPi2 aanpassen naar onze noden. Dit leest u in het volgende deel!

#RaspPI code 

```c
//Include the correct libaries
#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>

//Init our RF modules, Start SPI!
RF24 radio(RPI_V2_GPIO_P1_15, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

int main(int argc, char** argv) 
{
	// Set the nodeID to 0 for the master node
	mesh.setNodeID(0);
	// Connect to the mesh
	mesh.begin();
	
	while(1)
	{
		// Call network.update as usual to keep the network updated
		mesh.update();

		// In addition, keep the 'DHCP service' running on the master node so addresses will
		// be assigned to the sensor nodes
		mesh.DHCP();

		// Check for incoming data from the sensors
		while(network.available())
		{
			RF24NetworkHeader header;
			network.peek(header);
			uint32_t dat=0;
			
			//Check which data type we recieved
			switch(header.type){
				case 'M': network.read(header,&dat,sizeof(dat));
				  //%03d => Always have 3 numbers, if not lead it with zeroes => d (decimal)
				  //mesh.getNodeID() => Similear to ARP, gets node id from the node address
				  //dat => Actual data in our case, the sound intensity
					printf("%03d%u\n",mesh.getNodeID(header.from_node),dat);
					break;
				default:  network.read(header,0,0);
					printf("Rcv bad type %d from 0%o\n",header.type,header.from_node);
					break;
			}

			fflush(stdout);
		}
	  
		delay(2);
		
	}
	
	return 0;

}
```

De code is vrij 'self-explanatory'. We moesten een paar dinges toevoegen aan de example code en dan waren we al klaar voor wat betreft het ontvangen van de data!

#### Printen van de data
Het is de bedoeling dat later elke regel die nu op het scherm verschijnt wordt verwerkt en toonbaar is op een website. Hierdoor moesten we dus een afspraak maken hoe de data eruit ziet. We hebben gekozen voor

> 123987

De eerste 3 cijfers stellen de Node ID voor van de sensor. Deze zullen later gebruikt worden om te bepalen in welk lokaal de sensor stond. We moesten ervoor zorgen dat deze altijd 3 cijfers lang was. Dus 1 moest 001 worden. We hebben dit zo gedaan:

> %03d

De laatste 3 cijfers stellen de *sound intensity* voor. Deze waarde is dus hoe luid het is in de omgeving van de sensor. Dit is de waarde die uitgelezen wordt door de ADC van de Arduino.

#### ARP!?
Standaard werd het *node address* geprint op het scherm. Dit kun je vergelijken met het IP adress in een thuisnetwerk. Deze is immers ook door de 'DHCP service' uitgedeeld! Het probleem is dat deze dus kan veranderen. En dat mag niet één bepaalde sensor hangt in een kamer en die kamer die veranderd niet. Gelukkig is er ook een soort ARP oplossing en kunnen we gemakkelijk de *node id* te weten komen. Deze id hebben we ingesteld in de Arduino sketch op de node zelf!

#### fflush(stdout)
De bedoeling is dat we de output van ons script gaan schrijven naar een bestand. STDout is het process waarop je momenteel je programma 'bekijk', dit kan een SSH sessie zijn, een telnet sessie of gewoon lokaal via het scherm. Het is belangrijk dat we na elke keer we iets geschreven hebben, bij ons dus na de switch, we het sturen naar stdout! Zonder dit kan het zijn dat het in een buffer blijft staan! Waarom dit schadelijk is lees je bij 'Tee'.

(Tee, Tail, ...)

#NodeRED
(Werking, code)
