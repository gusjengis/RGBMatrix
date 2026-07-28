{
  description = "Arduino development environment for the RGB matrix project";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { nixpkgs, ... }:
    let
      systems = [
        "aarch64-darwin"
        "aarch64-linux"
        "x86_64-darwin"
        "x86_64-linux"
      ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      devShells = forAllSystems (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              arduino-cli
              jq
              python3
              shellcheck
            ];

            shellHook = ''
              export ARDUINO_DIRECTORIES_DATA="$PWD/.arduino/data"
              export ARDUINO_DIRECTORIES_DOWNLOADS="$PWD/.arduino/downloads"
              export ARDUINO_DIRECTORIES_USER="$PWD/.arduino/user"
            '';
          };
        });
    };
}
