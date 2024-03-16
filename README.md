# AntColony

My personal research(#1) project.

# Installation

- Requires SFML 2.6 [SFML](https://www.sfml-dev.org/index.php)

use following command to build

```bash
cmake -S . -B build
cmake --build build --config Release
```

after that, Project binary should be in `build/bin/` directory.
in order to change project name, change `MyResearch1` in `CMakeLists.txt` file.

# Controls

- use mouse wheel to zoom in and out
- use left click and drag to move around
- Press ESC to exit

# Screenshots
![1710287426](https://github.com/0Akise/AntColony/assets/128660223/4976b124-ac47-4cb5-a59e-d62d953636f1)

# Known Bugs

- [ ] Ants have absolute seizure when they are on food source.
- [ ] Sidepanel CameraPos is always (0.0, 0.0)
- [ ] Sidepanel MousePos is not set respect to the World
- [ ] Hive hitbox is not accurate
- [ ] Ant textures escape border of the world
- [ ] Ants are following different color of pheromones
