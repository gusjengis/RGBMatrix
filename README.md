# RGB Matrix

Minimal Arduino Mega 2560 project for a 64x32 HUB75 RGB matrix. The initial sketch lights one white pixel near the center of the panel.

The panel must use an external regulated 5V supply. Connect the supply ground,
panel ground, and Mega ground together; sharing an AC outlet is not a shared DC
signal ground. The sketch initializes the Waveshare panel's FM612x control
registers before starting normal HUB75 refresh.

Install pinned dependencies once:

```sh
./arduino setup
```

Build:

```sh
./arduino build
```

Upload to the connected Mega:

```sh
./arduino upload
```

The upload command performs a clean warning-enabled build, detects the Mega, uploads, and verifies the result. Override automatic port detection when needed:

```sh
PORT=/dev/ttyACM1 ./arduino upload
```

Other commands:

```sh
./arduino boards
./arduino clean
./arduino --help
```
