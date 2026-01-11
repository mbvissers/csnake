{
  description = "C++ ncurses dev shell for csnake";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";

  outputs = { self, nixpkgs, ... }:
    let
      pkgs = import nixpkgs { system = "x86_64-linux"; };
    in
    {
      devShells.x86_64-linux.default = pkgs.mkShell {
        name = "csnake-dev";

        buildInputs = [
          pkgs.gcc          # g++
          pkgs.cmake        # optional
          pkgs.ncurses      # headers + library
          pkgs.clang-tools  # clangd
        ];

        shellHook = ''
          echo "Welcome to csnake dev shell!"
          export CXXFLAGS="-std=c++20"
          export CC=gcc
          export CXX=g++
          export PATH=$pkgs.clang-tools/bin:$PATH
        '';
      };
    };
}
