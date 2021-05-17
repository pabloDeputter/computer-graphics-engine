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
size = 1024
backgroundcolor = (0, 0, 0)
type = "Texture"
shadowMask = 2048
shadowEnabled = TRUE
nrLights = 1
eye = (100, 50, 75)
nrFigures = 1

[Light0]
infinity = FALSE
textureName = "rusty.bmp"
location = (5, 9, 10)
ambientLight = (1, 1, 1)
diffuseLight = (1, 1, 1)
specularLight = (1, 1, 1)

[Figure0]
type = "Sphere"
scale = 1.2
rotateX = 0
rotateY = 0
rotateZ = 0
center = (0, 0, 0)
n = 7
ambientReflection = (0.30, 0.30, 0.30)
diffuseReflection = (0.60, 0.60, 0.60)
specularReflection = (1, 1, 1)
reflectionCoefficient = 5
```

## Gekende problemen 
## Niet-gequoteerde functionaliteit
## Extra functionaliteit, niet in de opgaves beschreven
...

