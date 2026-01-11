# csnake

A copy of my [rsnake](https://github.com/mbvissers/rsnake) repository but using `ncurses` and C++.

## Installation / Running

We use a Nix file to run a dev terminal with the tools installed.

Run the following command to enter the `nix` dev shell.

```
nix develop
```

And the following to build to program.

```
g++ src/main.cpp -std=c++20 -lncurses -o csnake
```

And then of course, to following to run the file.

```
./csnake
```
