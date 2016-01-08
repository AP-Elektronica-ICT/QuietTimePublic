## Microfoon
Om de hoeveelheid geluid te kunnen bepalen binnen een bepaalde ruimte moeten we een device hebben dat geluid kan detecteren. We hebben ervoor gekozen om een microfoon te gebruiken dat analoge data genereert afhankelijk van het geluid.

### MAX4466
We hebben ervoor gekozen om een kloon van de Adafruit Electret Microphone Amplifier - MAX4466 with Adjustable Gain te kopen bij mchobby.be . Na eerst wat tegenslag te hebben gehad door het kopen van een microfoon waarbij geen analoge uitgang was zijn we toch blij dat we deze microfoon gevonden hadden. Het is zeker geen ideaal component voor onze toepassing maar om de kosten niet absurd hoog te laten gaan is dit de ideale oplossing. 

#### Specificaties
Een microfoon alleen is niet genoeg om aan de ADC (analog digital converter) te hangen. Het signaal moet versterkt worden en dit doet de MAX4466. Dit is een low cost micropower microphone amplifier. Deze werkt van 2.4V tot 5.5V, heeft een goede  Power-Supply Rejection Ratio (112dB) en Common-Mode Rejection Ratio (126dB). Verder is het stroomverbruik beperkt op slechts 24µA in normale omstandigheden. 

#### Gebruik
We hebben deze microfoon natuurlijk niet zelf opgebouwd. We hebben deze opgebouwd gekocht zodat we deze ook onmiddellijk konden gebruiken. Het aansluiten van deze microfoon is ontzettend gemakkelijk. We hebben maar 3 pinnen: de VCC (3.3V), OUT en de GND. Waar VCC en GND moeten is duidelijk en de OUT hangen we aan een analoge ingang van de ADC. 

![alt text](http://i.imgur.com/L9gK17x.jpg?1 "Logo Title Text 1")

### Code
Een kort woordje uitleg over de code in verband met de microfoon. Deze code is de standalone code voor de microfoon maar word gebruikt in de eigenlijke node code. Voor de uitleg van deze code lijkt het me makkelijker om dit op deze manier te doen.


Eerst hebben we enkele globale variabele die we initialiseren en verder zorgen we dat we de serial initialiseren voor debug doeleinde.
```c
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(9600);
}
 
```

Dan gaan we verder naar onze eigenlijke meting van de het geluid. We starten met het initialiseren van variabelen naar hun startwaarden. Dan gaan we voor 50ms het geluid meten dat de microfoon opvangt. We slaan de hoogste en de laagste waarde op. Na de 50ms berekenen we de peak-to-peak waarde van het geluid en zetten deze om in de eigenlijke voltages. Dit geven we weer op het debug venster. In de eigenlijke node code zal deze data verstuurd worden naar de raspberry pi.
```c
void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
   delay(100);
 
   Serial.println(volts);
}
```

### Voor - en nadelen
##### - Voordelen
* Deze microfoon is gemakkelijk te gebruiken. Iedereen die een ADC kan uitlezen kan deze gebruiken
* Afhankelijk waar je de microfoon koopt is deze niet prijzig
* Er is een potentiometer op geïnstalleerd zodat je de gain van de pre-amplifier kan instellen

##### - Nadelen
* De sensitiviteit van de microfoon is niet optimaal
* Het totale bereik van de microfoon had beter gekunt
* Het meest ideale zou zijn dat we een microfoon hadden die dB waardes zou kunnen geven. Dit zou de prijs absurd hoog brengen en we hebben er dus voor gekozen om dit niet te doen. 

 
