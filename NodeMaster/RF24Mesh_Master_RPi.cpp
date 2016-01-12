 /* Raspberry Pi Code for IoT Quiet Time
  * Edited example file by Brecht Carlier
  * 2015 - 2016 3EA2 AP Hogeschool
  * Used a nRF24L01 module
  * The explanation of this code/project can be found in Verslag.md
 */

#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>


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
			
			switch(header.type){
				case 'M': network.read(header,&dat,sizeof(dat));
					//%03d => Always have 3 numbers, if not lead it with zeroes => d (decimal) => u (unsigned integer)
					//mesh.getNodeID() => Similear to ARP, gets node id from the node address
					//dat => Actual data in our case, the sound intensity
					printf("%03d%03u\n",mesh.getNodeID(header.from_node),dat);
					break;
				default:  network.read(header,0,0);
					printf("Rcv bad type %d from 0%o\n",header.type,header.from_node);
					break;
			}

			//Check verslag.md for the explanation
			//Flushes the stdout buffer!
			fflush(stdout);
		}
	  
		delay(2);
	  
	}
	
	return 0;

}
