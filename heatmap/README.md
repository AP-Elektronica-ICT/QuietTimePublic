#Heatmap uitleg
*Javascript library voor het visualiseren van heat points in bepaalde gebieden*

##HTML 
*Alle code die in HTML gebruikt wordt*

###div: class heatmap

div waar de heatmap terecht komt

###style .heatmap
*styling voor de heatmap class*

hier worden de volgende elementen aangepast voor de heatmap:
* display: block (vorm van de heatmap)
* height: hoogte van de heatmap
* width: breedte van de heatmap
* position: plek waar de heatmap in het scherm tevoorschijn komt
* background-image: de afbeelding waar de heatmap over komt

##Scripts

###Library's
* heatmap.js : bibliotheek voor heatmap te kunnen gebruiken
* Jquerry.min.js : Jquerry kunnen gebruiken

###The code 

####Sensor
*Array met sensor objecten*

Elk sensor object bevat het volgende:
* place: String, plaats waar de sensor zich bevindt
* x: number, x-coördinaat van de map
* y: number, y-coördinaat van de map
* value: number, waarde die men krijgt van de Json file
* radius: number, grootte van de cirkel van een value


