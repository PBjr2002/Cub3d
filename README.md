# Cub3D

## Project Overview

**Cub3D** was my **first step into 3D graphics programming**. In this project, we built our **own 3D rendering engine from scratch**, using the **raycasting technique** — a simplified version of what’s used in classic games like *Wolfenstein 3D*.

We started from a flat 2D map described in a `.cub` file and turned it into a **"realistic" first-person 3D experience**. All of this is done using **MiniLibX**, without any game engine or external rendering libraries.

This project focused on:

- How to simulate 3D perspective with **raycasting**
- How to render with directional textures (N/S/E/W) 
- How to handle **real-time input and movement**
- How to **parse structured files** and render maps with textures
- How to manage **wall collisions** and map boundaries
- How to implement **real-time minimap overlays**
- How to handle **interactive doors** that open and close dynamically

---

## Gameplay

- The player moves using `W` / `A` / `S` / `D`
- The player view moves using `←` / `→` or with **Mouse movement**
- Doors open and close using `E`
- To use the mouse freely use `R`
- Pressing the **ESC** key exits the program cleanly
- Real-time minimap overlay  

---

## Demonstration
  
![Gameplay Demo](.gif/Cub.gif)

<!-- 
🎥 Add a gameplay GIF or video preview here later. 
You can use a screen recording tool (like OBS or Peek), convert it to GIF or upload the video directly.
Example:
![Gameplay Demo](./assets/demo.gif)
-->
