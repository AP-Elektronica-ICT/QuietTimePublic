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

###Code ( opzetten van alles )

####Sensor
*Array met sensor objecten*

Elk sensor object bevat het volgende:
* place: String, plaats waar de sensor zich bevindt
* x: number, x-coördinaat van de map
* y: number, y-coördinaat van de map
* value: number, waarde die men krijgt van de Json file
* radius: number, grootte van de cirkel van een value

####data 
*data formaat dat door de heatmap wordt aangenomen*

Dit bevat twee dingen:

* max: maximale waarde die men binnenkrijgt ( deze zal visueel een rode kleur krijgen )
* sensor: alle sensorobjecten die werden ingesteld staan in deze array

om deze op de heatmap te zetten maken we gebruik van een functie van de heatmap library: *heatmapinstance.setData(data)*

###Code (invullen van de heatmap)

Voorgaande code was allemaal voorbereiding voor de heatmap en de sensoren te kunnen gebruiken.
Onderstaande code zal meer uitleg geven over hoe we aan data van de sensoren geraken en hoe we deze in de heatmap gaan zetten.

####Sensordata uitlezen

Dit wordt gedaan via de *refreshData()* functie die we gemaakt hebben.
Deze zal een ajax call doen naar een bepaalde pagina op een site die we hebben opgezet.
Het datatype dat we vragen is in *jsonp* gezien we hierdoor cross scripting restricties kunnen ontwijken die we normaal zouden krijgen als we een *json* formaat zouden vragen.

Als dit succesvol gebeurd returnen we het jsonp object in een global object dat we in het project gaan gebruiken voor de sensoren in te vullen.

####Sensordata invullen

Een sensorobject in het global object met sensorwaarden bevat 2 dingen:
* id: hiermee kunnen we bepalen over welke sensor het gaat
* value: waarde die de sensor geeft bij een bepaald geluid signaal

In onze *Update()* functie gaan we de data van onze sensoren invullen.
Eerst gaan we de hele array van het gereturnde object doorlopen en kijken of we onze sensoren er uit kunnen halen afhankelijk van hun *sensorid*.
Bij een match gaan we de waarde van de sensor eerst moeten vermenigvuldigen omdat de waarde van de sensor te klein is om direct mee te werken in ons programma. Als dit gebeurt is stellen we de waarde van de ingelezen sensor gelijk aan het matchende sensorObject dat we daarstraks hebben aangemaakt.
Hierna pushen we sensorObject.value terug in de array zodat deze de laatst binnengehaalde data heeft.

Uiteindelijk waneer alle sensoren zijn uitgelezen die we hadden binnengebregen roepen we terug *heatmapinstance.setData(data)* aan om alle nieuwe waarden op de heatmap weer te geven.

####Loop

Omdat bovenstaande gewoon functies zijn moeten we ervoor zorgen dat deze constant worden uitgevoerd om de laatste info van de sensoren op de heatmap te zetten. Dit gebeurt door een interval in te stellen van een gekozen tijd (500ms in ons geval) en dit de *Update()* functie uit te laten voeren. Gezien de *refreshData()* wordt aangeroepen in de *Update()* functie wordt deze automatisch terug gebruikt.
