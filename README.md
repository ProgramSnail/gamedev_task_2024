# Game (Linux) - Slither.io offline clone

- Snake should eat apples to grow
- Current score displayed on top of the screen
- There are bots that eat apples and can not be destroyed by player. Snake is destroyed when its head intersects bot

Game is based on https://github.com/imp5imp5/game_template_linux.

Executable file for linux is placed in **release** section.

### Build (xmake)
``sudo apt install g++ cmake libx11-dev xmake`` \
``xmake``

### Run (xmake)
``xmake run``

### Build (cmake)
``sudo apt install g++ cmake libx11-dev`` \
``mkdir build && cd build`` \
``cmake -DCMAKE_BUILD_TYPE=Release ..`` \
``make``
