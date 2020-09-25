# Game-Project 
This is a 2D game project which I'm trying to build with my spare time. It's basically a personal challenge for maintain a bigger codebase without getting lost and try to learn a little on how games are made.

![](https://user-images.githubusercontent.com/33965580/94323903-e19e7d80-ff6d-11ea-83a0-02ad2583d464.png)

Yes, this is what it currently looks like, 3 sprites, its still very simple. :)

# Getting started

On Debian based distros it will be easier to setup this project, you will just need to install some dependencies:

```console
sudo apt install cmake liblua5.1-dev libsfml-dev
git clone https://github.com/TulioAbreu/game-project
cd game-project
mkdir build
cd build
cmake ..
make
./gameProject
```

IMPORTANT: You want to make sure `sudo apt install libsfml-dev` is installing SFML 2.5.1 or higher.

I tried to run it on my Windows machine, but it was kinda annoying/complex. If you want to contribute with an easier Windows build I'll gladly accept :)
