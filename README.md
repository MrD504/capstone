# CAPSTONE 1 PROJECT

## Brief Description
A simple game engine for Udacity's capstone project.

This game engine is the bare bones for a simple game engine. I wanted to create this from stratch to help understand how Unity and Unreal engines work (in the simplest of terms).

The engine reads in a series of numbers from a map file and loads the corresponding image from a sprite sheet.
Various assets are also loaded, transformed and controlled by user input. A basic collision detection system has also been implemented.

*This is still a work in progress, but does meet enough of the criteria for project submission*

## Dependencies
This project was created on Lubuntu 18.04

``` sudo apt install libsdl2-dev libsdl2-image-dev build-essential libsdl-ttf-dev libsdl-mixer-dev liblua5.3-dev ```

- Note: the liblua packages maybe different for other flavours of linux

## File and Class Structure
- assets
  - fonts
    - arial.ttf
    - chariot.ttf
  - images
   - army-group-1.png
   - army-group-2.png
   - army-group-3.png
   - bullet-enemy.png
   - bullet-friendly.png
   - chopper-single.png
   - chopper-spritesheet.png
   - collision-texture.png
   - heliport.png
   - images.zip
   - obstacles.png
   - radar.png
   - rock-big-1.png
   - rock-big-2.png
   - rock-big-3.png
   - rock-big-4.png
   - rock-small-1.png
   - start.png
   - tank-big-down.png
   - tank-big-left.png
   - tank-big-right.png
   - tank-small-left.png
   - tank-small-right.png
   - tree-small-1.png
   - tree-small-2.png
   - tree-small-3.png
   - tree-small-4.png
   - tree-small-5.png
   - tree-small-6.png
   - tree-small-7.png
   - tree-small-8.png
   - truck-down.png
   - truck-left.png
   - truck-right.png

- lib
  - glm
    - CMakeLists.txt
    - common.hpp
    - detail
    - exponential.hpp
    - ext
    - ext.hpp
    - fwd.hpp
    - geometric.hpp
    - glm.hpp
    - gtc
    - gtx
    - integer.hpp
    - mat2x2.hpp
    - mat2x3.hpp
    - mat2x4.hpp
    - mat3x2.hpp
    - mat3x3.hpp
    - mat3x4.hpp
    - mat4x2.hpp
    - mat4x3.hpp
    - mat4x4.hpp
    - matrix.hpp
    - packing.hpp
    - simd
    - trigonometric.hpp
    - vec2.hpp
    - vec3.hpp
    - vec4.hpp
    - vector_relational.hpp
  - lua
     - lauxlib.h
     - luaconf.h
     - lua.h
     - lua.hpp
     - lualib.h
     - sol.hpp


- Makefile
- README.md
- src
  - Animation.cpp
  - Animation.h
  - AssetManager.cpp
  - AssetManager.h
  - Collision.cpp
  - Collision.h
  - Component.h
  - Components
    - ColliderComponent.h
    - KeyboardControlComponent.h
    - SpriteComponent.h
    - TileComponent.h
    - TransformComponents.h
  - Constants.h
  - Entity.cpp
  - Entity.h
  - EntityManager.cpp
  - EntityManager.h
  - Game.cpp
  - Game.h
  - Main.cpp
  - Map.cpp
  - Map.h
  - TextureManager.h
  - TextureManger.cpp

## Capstone Criteria Met
  - The project makes use of references in function declarations - *Entity.cpp - line 3*
  - Templates generalise functions - *Entity.h - line 30*
  - Derived Class function override virtual base class functions - *Component.h -line 10*
  - Classes encapsulate behaviour - * SpriteComponent.h - line 80 *
  - Class constructors utilize member initialisation lists - *Entity.h - line 3*
  - Classes use appropriate access specifiers - * See any header file*
  - Uses OOP
  - Reads - data from files - * map.cpp - line 17 *
  - Accepts user input - * Game.cpp - line 79, KeyControlComponent.h *
  - Demonstrates C++ functions - * See whole project *
  
## Acknowledgements
I wanted to do Capstone 2 but I didn't want to have all of the boiler plate done for me. I wanted to learn that too. So a big thank you to Pikuma.com, which was instrumental in teaching me how to build this game engine demo and also with supplying the assets.
