# GameProject 
This is a 2D game project which I'm trying to build with my spare time.

# Getting started

## Debian based distros
```console
$ sudo apt install g++ cmake liblua5.1-dev libsfml-dev
$ cd build
$ cmake ..
$ make
$ ./gameProject
```

## Windows

-  Download windows dependencies:
> Mingw (you can install with [Chocolatey](http://chocolatey.org/))

> [Lua 5.1](https://www.lua.org/download.html)

> [SFML](https://www.sfml-dev.org/download/sfml/2.5.1/)

- Install Lua5.1 and SFML libraries into your mingw.
- Modify game.ps1/editor.ps1 `-I` filepath, for matching with your Lua5.1 and SFML includes paths
- Run the powershell build scripts. Since they're used for development, they are removing the generated .exe after closing the game

