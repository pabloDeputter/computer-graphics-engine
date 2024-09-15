# Computer Graphics Engine

## Introduction

This project aims to build a graphics engine capable of rendering both 2D and 3D objects using various graphical techniques. By parsing configuration files (`.ini` format), the engine generates images based on the specified properties and instructions. The project includes multiple exercises covering topics like color rectangles, blocks, 2D and 3D line drawings, transformations, and fractals.

**Created for the "Computer Graphics" 1st bachelor course at the University of Antwerp.**

## Features

1. **2D Image Rendering**
   - Color rectangles.
   - Checkerboard patterns (blocks).
   - 2D line drawings (QuarterCircle, Eye, Diamond).

2. **3D Line Drawings**
   - Basic wireframe models with rotation, scaling, and translation.
   - Eye-point transformation and perspective projection.

3. **3D Objects**
   - Platonic solids (Cube, Tetrahedron, Octahedron, Icosahedron, Dodecahedron).
   - Cylinders, cones, spheres, and tori.
   - Fractals based on 3D solids.

4. **Z-buffering**
   - Z-buffering with lines and triangles.
   - Backface culling for optimizing rendering performance.

5. **Lighting and Shadowing**
   - Ambient and diffuse lighting.
   - Specular reflection for glossy surfaces.
   - Shadow rendering for point light sources.

6. **Texture Mapping**
   - Basic texture mapping on surfaces.
   - Cube mapping for environment reflections.

## Compilation Instructions

1. Make sure you have a C++ compiler (e.g., GCC or Clang).
2. Use CMake to configure and build the project.

```bash
mkdir build
cd build
cmake ..
make
```

3. To run the engine:

```bash
./engine path_to_ini_file 
```

## INI File Structure

The engine is driven by configuration files in the INI format. Each task (2D shapes, 3D figures, lighting) is specified using different sections and parameters.

### Example INI File for a Cube:

```ini
[General]
type = "Wireframe"
size = 500
eye = (50, 50, 50)
backgroundcolor = (0.0, 0.0, 0.0)
nrFigures = 1

[Figure0]
type = "Cube"
scale = 1.0
rotateX = 30
rotateY = 45
rotateZ = 0
center = (0, 0, 0)
color = (1.0, 0.0, 0.0)
```

### Example INI File for Z-Buffering with Lighting:

```ini
[General]
type = "LightedZbuffering"
size = 800
backgroundcolor = (0.0, 0.0, 0.0)
eye = (100, 100, 100)
nrLights = 1
nrFigures = 1

[Figure0]
type = "Cube"
ambientReflection = (0.2, 0.2, 0.2)
diffuseReflection = (0.6, 0.6, 0.6)
specularReflection = (0.8, 0.8, 0.8)
reflectionCoefficient = 20
scale = 2.0
rotateX = 45
rotateY = 45
rotateZ = 0
center = (0, 0, 0)

[Light0]
infinity = true
direction = (0, -1, -1)
ambientLight = (0.3, 0.3, 0.3)
diffuseLight = (0.6, 0.6, 0.6)
specularLight = (0.8, 0.8, 0.8)
```

# Project Status

This section outlines the status of various functionalities implemented in this computer graphics engine. Each functionality is marked as:
- 👌 **Working**: Fully functional
- 👷 **Partially Working**: Implemented but with known issues (described below)
- ⛔ **Not Working**: Not implemented or non-functional

| **Functionaliteit**             | **Status** | **Punten** |
|----------------------------------|------------|------------|
| **1. 2D L-Systemen**             | 👌         | 1          |
| **- Met haakjes**                | 👌         | 0.125      |
| **- Stochastisch**               | 👌         | 0.125      |
| **2. Transformaties**            | 👌         | 1          |
| **- Eye-point**                  | 👌         | 0          |
| **- Projectie**                  | 👌         | 0          |
| **3. Platonische Lichamen**      | 👌         | 0.75       |
| **- Kegel en Cylinder**          | 👌         | 0          |
| **- Bol**                        | 👌         | 0          |
| **- Torus**                      | 👌         | 0          |
| **- 3D L-Systemen**              | 👌         | 0.25       |
| **4. Z-buffering (lijnen)**      | 👌         | 1          |
| **5. Triangulatie**              | 👌         | 0.75       |
| **- Z-buffering (driehoeken)**   | 👌         | 0.75       |
| **6. 3D Fractalen**              | 👌         | 0.75       |
| **- BuckyBall**                  | ⛔         | 0.125      |
| **- Mengerspons**                | 👌         | 0.125      |
| **- View Frustum**               | ⛔         | 0.5        |
| **7. Ambient licht**             | 👌         | 0.3        |
| **- Diffuus licht (oneindig)**   | 👌         | 0.4        |
| **- Diffuus licht (puntbron)**   | 👌         | 0          |
| **- Speculair licht**            | 👌         | 0.4        |
| **8. Schaduw**                   | 👌         | 1          |
| **- Texture mapping**            | 👌         | 0.75       |
| **9. Bollen en Cylinders**       | ⛔         | 0.75       |
| **- UV-coördinaten**             | ⛔         | 0.125      |
| **- Normaalvectoren**            | ⛔         | 0.125      |
| **- Cube mapping**               | ⛔         | 0.5        |
| **10. **Total Points**           | ▶️         | 9.475      |

## Texture Mapping Implementation

For the texture mapping feature, a texture can be applied to a figure, a light source (PointLight, InfLight & light), or both. Shadows and multiple light sources can be incorporated as well.

### Input Parameters for Texture Mapping

The following parameters control the texture mapping:

```ini
type = "Texture"
textureName = "texture.bmp"
```

### Example INI File for Texture Mapping

In the INI file below, texture mapping is applied only to the light source:

```ini
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

This will generate the following output:
![](https://github.com/pabloDeputter/engine_computer_graphics/blob/main/ini_files/textures/textures036.png)
