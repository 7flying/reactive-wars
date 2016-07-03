# Reactive Wars

Twin stick isometric shooter with procedural map generation developed for
*Multimedia and videogames* subject. 

- The procedural map generation is made with [Perlin Noise](https://en.wikipedia.org/wiki/Perlin_noise).
- Uses SMFL.

![Screenshot](https://github.com/7flying/reactive-wars/raw/master/screenshots/00-gameplay.png)

## Controls

```./reactive-wars``` will show a small window, press ```SPACE``` to start. You
can zoom-in/out and resize the window. 

Use ```WASD``` to move the character, and the arrow keys to shoot.

`R` reloads the map.

You have a single life.

## Install dependencies

Library and latest compilers:

```bash
wget http://www.sfml-dev.org/files/SFML-2.3.2-linux-gcc-64-bit.tar.gz
tar -zxf SFML-2.3.2-linux-gcc-64-bit.tar.gz
sudo cp -r SFML-2.3.2 /usr/local/
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install libsfml-dev gcc-4.9 g++-4.9
```

## Stuff to do / to fix

Here be dragons:

- Fine-grained collisions. Now it's hardcore.
- Title screen.
- ?¿ Memory leak on enemy dispatch routine.


## Disclaimer

The player and enemy sprites have been taken from [Little War Game](http://www.littlewargame.com/)
and belong to their respective authors.

Other sprites are from the internet and belong to their respective authors.
