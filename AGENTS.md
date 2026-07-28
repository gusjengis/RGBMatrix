# Project Instructions

Use the repository Nix flake for all Arduino CLI operations. Do not depend on a globally installed `arduino-cli`.

Run commands from the repository root:

```sh
nix develop -c arduino-cli <args>
```

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
