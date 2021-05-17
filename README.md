## Gequoteerde functionaliteit

:ok_hand: Werkend  
:construction_worker: Deels werkend met gekende problemen (onderaan beschreven)  
:no_entry: Niet werkend of niet geïmplementeerd  


|   | Functionaliteit       | Status | Punten   |
|---|---------------------------|---|-----------|
| 1 | 2D L-systemen             | :ok_hand: | 1 |
|   | Met haakjes               | :ok_hand: | 0.125 |
|   | Stochastisch              | :ok_hand: | 0.125 |
| 2 | Transformaties            | :ok_hand: | 1 |
|   | Eye-point                 | :ok_hand: | 0 |
|   | Projectie                 | :ok_hand: | 0 |
| 3 | Platonische Lichamen      | :ok_hand: | 0.75 |
|   | Kegel en cylinder         | :ok_hand: | 0 |
|   | Bol                       | :ok_hand: | 0 |
|   | Torus                     | :ok_hand: | 0 |
|   | 3D L-systemen             | :ok_hand: | 0.25 |
| 4 | Z-buffering (lijnen)      | :ok_hand: | 1 |
| 5 | Triangulatie              | :ok_hand: | 0.75 |
|   | Z-buffering (driehoeken)  | :ok_hand: | 0.75 |
| 6 | 3D fractalen              | :ok_hand: | 0.75 |
|   | BuckyBall                 | :no_entry: | 0.125 |
|   | Mengerspons               | :ok_hand: | 0.125 |
|   | View Frustum              | :no_entry: | 0.5 |
| 7 | Ambient licht             | :ok_hand: | 0.3 |
|   | Diffuus licht (oneindig)  | :ok_hand: | 0.4 |
|   | Diffuus licht (puntbron)  | :ok_hand: | 0 |
|   | Speculair licht           | :ok_hand: | 0.4 |
| 8 | Schaduw                   | :ok_hand: | 1 |
|   | Texture mapping           | :ok_hand: | 0.75 |
| 9 | Bollen en cylinders       | :no_entry: | 0.75 |
|   | UV-coordinaten            | :no_entry: | 0.125 |
|   | Normaalvectoren           | :no_entry: | 0.125 |
|   | Cube mapping              | :no_entry: | .5 |
| 10| Total points              | :arrow_forward: | 9.475 |

Geïmplementeerde vorm van texture mapping: Texture mapping op een bol. Men kan de textuur afbeelden op het oppervlak van een figuur, een lichtbron (PointLight, InfLight & light) of beide. Ook kunnen er schaduwen toegevoegd worden aan de afbeelding en verschillende lichtbronnen. Volgende inputparameters gelden:
```cpp
type = "Texture"
```
```cpp
textureName = "texture.bmp"
```
Volgend .ini bestand is een voorbeeld waarbij enkel op de lichtBron een texture wordt afgebeeld:
```cpp
[General]
size = 4096
backgroundcolor = (0.01, 0.01, 0.01)
type = "Texture"
shadowMask = 8192
shadowEnabled = TRUE
nrLights = 1
eye = (-60, 30, 50)
nrFigures = 2

[Light0]
infinity = FALSE
textureName = "mars.bmp"
location = (0, 20, 30)
ambientLight = (1, 1, 1)
diffuseLight = (1, 1, 1)
specularLight = (1, 1, 1)

[Figure0]
type = "Sphere"
scale = 1
rotateX = 0
rotateY = 0
rotateZ = 0
center = (0, 0, 0)
n = 8
ambientReflection = (0.20, 0.20, 0.20)
diffuseReflection = (0.9, 0.9, 0.9)
specularReflection = (1, 1, 1)
reflectionCoefficient = 2

[Figure1]
type = "Sphere"
scale = 1.7
rotateX = 0
rotateY = 0
rotateZ = 0
center = (1.8, 0, 0)
n = 9
ambientReflection = (0.15, 0.15, 0.15)
diffuseReflection = (0.8, 0.8, 0.8)
specularReflection = (0.8, 0.8, 0.8)
reflectionCoefficient = 4
```
Dit bestand zal de volgende afbeelding genereren:
![](https://github.com/pabloDeputter/engine_computer_graphics/blob/main/ini_files/textures/textures036.png)

## Gekende problemen 
## Niet-gequoteerde functionaliteit
## Extra functionaliteit, niet in de opgaves beschreven
...

