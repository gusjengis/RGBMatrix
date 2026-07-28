# RGB Matrix

Arduino Mega 2560 serial text display for a 64x32 HUB75 RGB matrix. Text typed
on the computer wraps across four rows and scrolls as needed. Enter starts a new
line and Backspace removes the previous character.

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

After uploading, start the terminal client:

```sh
./matrix-terminal
```

The client auto-detects a single common USB serial port. Pass the port when
automatic detection is ambiguous:

```sh
./matrix-terminal /dev/ttyACM1
```

Type printable ASCII directly into the terminal. Use Enter for a new line,
Backspace to erase, and Ctrl-C or Ctrl-D to quit. Opening the serial connection
resets the Mega, so the client waits two seconds before accepting input.

Other commands:

```sh
./arduino boards
./arduino clean
./arduino --help
```
