# csnake

A copy of my [rsnake](https://github.com/mbvissers/rsnake) repository but using `ncurses` and C++ instead of Rust with `crossterm`.

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

And then of course, the following to run the file.

```
./csnake
```

## Note to self

To search for features in ncurses. Check the man page with `man ncurses`, and if you find a function,
go deeper into its docs using `man 3 <function>`
