# Lokaverkefni í VESM3 2021
#### Víðir D. Krogsgaard & Viktor B. Guðlaugsson

<br>
<br>

Í lokaverkefninu völdum við að gera rafknúna viftu sem kveikir og slekkur á sér eftir hversu heitt það er í kring um hita- og rakaskynjara sem keyrir utan viftunnar. Bætt var við IFTTT virkni sem tekur öll ný gildi úr feedinu og sendir þau inn í nýjann dálk með tíma- og dagsetningu gildisins.

## Íhlutir

DC motor var tilvalinn fyrir viftuna sjálfa því hann snýst frekar hratt og fer allar 360 gráðurnar. Við völdum lítinn standard DC mótor sem fylgdi Arduino kittinu fyrir fyrsta VESM áfangann því hann var nógu öflugur fyrir okkar verkefni.

Notaður var [MG995](README%20Images/MG995.jpg?raw=true) Servo mótor sem var fenginn frá kennaranum. Notað var efni frá [Microcontrollerslab.com](https://microcontrollerslab.com/mg995-servo-motor-pinout-interfacing-with-arduino-features-examples/) til að fá réttu pinnana fyrir mótorinn og almennilegann skilning á hvernig hann virkar. Þessi mótor er notaður til að snúa viftunni sjálfri því hann kemst einungis 180 gráður (þ.e.a.s. 90° til vinstri og 90° til hægri frá miðpunkti).

DHT11 hita- og rakaskynjari er til staðar og sendir hann frá sér hitastig til feed á Adafruit IO ef hann fær ekki sama gildið tvisvar á fimm sekúndna fresti. Þetta var gert til að koma í veg fyrir að overloada feedið því Adafruit IO lokar feedinu ef það er of mikil virkni í gangi í einu. Notað var efni frá [TheCustomizeWindows](https://thecustomizewindows.com/2019/03/esp32-arduino-with-dht11-sensor-connection-code/) og frá [Electronicshub](https://www.electronicshub.org/esp32-dht11-tutorial/).

ESP32 er microcontroller svipaður Arduino Uno og notuðum við þrjá. Hann tekur við kóða úr Arduino IDE og er því frekar auðvelt að vinna með hann. Hins vegar þurftum við að finna library fyrir alls konar hluti til að fá virkni á honum svipað og hægt er að fá úr Arduino. ESP32 hefur innbyggt WiFi og þarf því ekki að hafa áhyggjur af því. Hann getur hins vegar bara knúið 3.3V en ekki 5V og var því battery pack (4x 1.5V) notaður í staðinn, einnig til að vernda hann. Notað var efni frá [Espressif](
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/_images/esp32-devkitC-v4-pinout.png), höfundum ESP32 til að fá almennilegann skilning á pinnum tækisins.

## Tengingar

Fyrir DC mótorinn var notaður ESP32 til að stýra honum og 4x 1.5v rafhlöður til að knúa hann. Notaður var 330Ω resistor úr ESP32 yfir í transistor og diode úr mótornum yfir í transistorinn. Rafhlöðurnar tengdust í VCC (+) og common ground (-). Mynd má finna [hér](README%20Images/ESP32DCMotor.png?raw=true) til að sjá tengingarnar. Tinkercad hefur hins vegar ekki ESP32 og því var Arduino Uno notaður fyrir myndina í staðinn.<br>
Við grilluðum þrjá transistors með þessarri tengingu og skiptum við því yfir í L298N Dual H-Bridge Motor Controller. Tinkercad hefur engann stuðning fyrir þann íhlut og því er ekki hægt að gera nýja mynd fyrir hann. Rafhlöðurnar tengjast í GND (-) á motor controllernum og VCC (+). Þaðan tengjast vírar úr ESP32 yfir í 3 pinna á Motor Controllernum. ENA (Enable A) tengist pin 14, IN1 í 26 og IN2 í 27. Síðan er mótorinn tengdur í MOTORA tengin á controllernum.

DHT11 var frekar auðveldur. Hann var tengdur í 3.3V (+), GND (-) og pin 2 á ESP32.

Servo mótorinn var einnig tengdur í sinn eigin ESP32. 3.3V (+), GND (-) og pin 13 á ESP32.

## 3D
fyrir viftu blaðið tókum við design af netinu það er linkur á það í heimildir.
Síðan gerum við sjálfir design fyrir botninn á viftunni.

## Vandamál

1. DC mótorinn á til með að festast þar til ýtt er á hann. Þetta er lítið vandamál en er samt óheppilegt fyrir verkefni þar sem tilgangurinn á honum er að snúast.
2. Step mótorinn endurræsir sig alltaf þegar kveikt er á honum og hann fær gildi í fyrsta sinn.
3. Adafruit IO getur endurræst lykil (key) manns án leyfis og því getur allt hætt að virka út úr þurru. Þetta gerist vegna þess að Adafruit getur fundið lykil (key) manns á netinu og endurræst hann ef hann finnst. Því er ekki hægt að setja config.h skjöl með réttum lykil á Github án þess að skemma allt kerfið.

## Niðurstöður
Hér fyrir neðan má sjá myndir af tengingu okkar og síðan myndband af viftunni. Því miður var þrívíddarprentunin ókláruð og lítur hún ekki út eins og vifta fyrir utan blaðið sem fylgdi með Arduino kittinu.

[IFTTT Google Sheets skjal](https://docs.google.com/spreadsheets/d/1YgROKHKO5uyjV1rzHlPHnc0VvN5rg4wlrnPz9e9smkE/edit?usp=sharing)<br>

[Mynd 1](README%20Images/img1.png?raw=true)<br>
[Mynd 2](README%20Images/img2.png?raw=true)<br>
[Mynd 3](README%20Images/img3.png?raw=true)<br>
[Mynd 4](README%20Images/img4.png?raw=true)<br>
[Mynd 5](README%20Images/img5.png?raw=true)<br>
[Mynd 6](README%20Images/img6.png?raw=true)<br>
[Mynd 7](README%20Images/img7.png?raw=true)<br>

[Myndband](https://www.youtube.com/watch?v=LtIJxRhvcMk)

## Heimildir
https://www.tinkercad.com/things/gyyTM0Yr2t1-fan
https://microcontrollerslab.com/mg995-servo-motor-pinout-interfacing-with-arduino-features-examples/<br>
https://thecustomizewindows.com/2019/03/esp32-arduino-with-dht11-sensor-connection-code/<br>
https://www.electronicshub.org/esp32-dht11-tutorial/<br>
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/_images/esp32-devkitC-v4-pinout.png/<br>
https://www.tinkercad.com/things/gyyTM0Yr2t1 (Viftublað eftir Dudeless á Tinkercad)<br>
https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/<br>
https://learn.adafruit.com/adafruit-arduino-lesson-13-dc-motors/breadboard-layout<br>

## Libraries
https://github.com/adafruit/Adafruit_IO_Arduino<br>
https://github.com/adafruit/Adafruit_MQTT_Library<br>
https://github.com/bxparks/AUnit<br>
https://github.com/ERROPiX/ESP32_AnalogWrite<br>
https://madhephaestus.github.io/ESP32Servo/annotated.html<br>
https://github.com/RoboticsBrno/ServoESP32/<br>
https://desire.giesecke.tk/index.php/2018/01/30/esp32-dht11/<br>
