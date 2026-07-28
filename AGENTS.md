# Project Instructions

Use the repository `./arduino` script for routine Arduino operations. It enters the Nix flake automatically; do not depend on globally installed tools or repeat raw CLI setup.

Run commands from the repository root:

```sh
./arduino setup
./arduino build
./arduino upload
./arduino boards
```

For a simple build or upload request, run the corresponding script command directly. `upload` performs a clean build, detects the Mega by FQBN, uploads, and verifies it. If automatic detection is ambiguous, specify the port:

```sh
PORT=/dev/ttyACM1 ./arduino upload
```

Use `nix develop 'path:.' -c arduino-cli <args>` only for operations not exposed by the script.

## Hardware

- Board: Elegoo Mega 2560 R3 / ATmega2560 (Arduino Mega compatible)
- Display: Waveshare P5 64x32 RGB HUB75 LED matrix
- Panel marking: P5(2121)-3264-16S-M5
- Scan mode: 1/16

## Wiring

| Signal | Mega pin |
| --- | --- |
| R1 | 24 |
| G1 | 25 |
| B1 | 26 |
| R2 | 27 |
| G2 | 28 |
| B2 | 29 |
| A | A0 |
| B | A1 |
| C | A2 |
| D | A3 |
| CLK | 11 |
| LAT/STB | 10 |
| OE | 9 |
| GND | GND |
