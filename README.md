# 🎮 Game Engine Demo: Starship & RabbitHammer

## 📌 Description

This repository contains two mini-games built to test the versatility of a custom-made game engine.

- **Starship** is the most polished and is recommended to try first.
- Both games demonstrate different mechanics and input handling using SDL2 and C++.

---

## 🚀 Starship

In **Starship**, the player uses a **Pistol** to shoot down or capture enemies.

### 🎯 Objective
- Shoot or capture **20 enemies**.
- If **3 enemies** get past the player, the game is lost.

### 🕹 Controls
- Aim with the **mouse**.
- Shoot by **clicking**.

---

## 🐰 RabbitHammer

In **RabbitHammer**, the player uses a **Sledgehammer** to smash enemies appearing on the screen.

### 🎯 Objective
- Smash **20 enemies**.
- If **3 enemies** disappear before being smashed, the game is lost.

### 🕹 Controls
- Move the hammer with the **mouse**.
- Hit by **clicking**.

---

## 🛠️ Build & Run Instructions

### 📁 Resource Paths

Resource files are stored in the `resources/` directory with three subfolders:

- `fonts/`
- `images/`
- `sounds/`

All assets are loaded using paths defined in `constants.h`.

#### 🧩 Example:
```cpp
shipTexture = IMG_LoadTexture(sys.ren, (constants::gResPath + "images/Enemy.png").c_str());
