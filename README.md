# 42_Cub3D

<div align="center">

[<kbd style="background-color: #00a651; color: #ffffff; font-weight: bold;"> <br> Code for Cub3D <br> (inverted x direction) <br> (texture handler to upgrade) <br> </kbd>](https://github.com/Tablerase/42_Cub3D/archive/refs/heads/main.zip)

<div style="display: flex; justify-content: space-between; padding: 10px; align-items: center;">
  <img src="https://github.com/Tablerase/42_Projects/raw/main/Projects/Cube3D/Media/cub3d-japan.gif" width="50%" style="margin-right: 10px;">
  <img src="https://github.com/Tablerase/42_Projects/raw/main/Projects/Cube3D/Media/cub3d-stone.gif" width="50%" style="margin-left: 10px;">
</div>

<img src="https://img.shields.io/badge/Version-2024-000000?style=for-the-badge&logo=42" alt="42 2024">
<img src="https://img.shields.io/badge/Grade-123-brightgreen?style=for-the-badge" alt="Grade 123">

</div>

## 📖 About

This project is inspired by the world-famous eponymous game, which was the first FPS ever. It is a remarkable challenge for a beginner in the programming world. The goal is to create a dynamic view inside a maze, in which the player must find his way. The game is based on the Ray-Casting principle.

## 🚀 Features

### Mandatory

- Map parsing
  - `North texture`
  - `South texture`
  - `West texture`
  - `East texture`
  - `Floor color`
  - `Ceiling color`
  - `Player position` and `orientation`
  - `Map`
- Wall projection
  - `Raycasting`
- Player movement
  - `W`: Move forward
  - `S`: Move backward
  - `A`: Move left
  - `D`: Move right
- Player rotation
  - `←`: Rotate left
  - `→`: Rotate right
- Player collision
- Texture mapping
  - `Affine texture mapping`

### Bonus

- Sprite rendering
- Door opening and closing
  - `Space`: Open/Close door
- Minimap
- Mouse rotation

## 📚 Resources

- [📓 **This Repo Detailled Documentation**](https://github.com/Tablerase/42_Projects/tree/main/Projects/Cube3D)

## 🛠️ Installation

```bash
# Clone the repository
git clone git@github.com:Tablerase/42_Cub3D.git cub3d
cd cub3d
```

```bash
# Build the project
make
```

```bash
# Build the project with bonus
make bonus
```

## 🚦 Usage

```bash
# Mandatory
./cub3D ./assets/maps/mandatory/map_name.cub
```

```bash
# Bonus
./cub3D_bonus ./assets/maps/bonus/map_name.cub
```
