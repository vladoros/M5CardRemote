# M5CardRemote

Fork of [M5CardRemote](https://github.com/VolosR/M5CardRemote) by VolosR.

**Note:** The IR codes in `codes.h` are specific to particular devices (Samsung TV and T-COM set-top box). Modify `codes.h` with your device's IR signals to use with different hardware.

Turn your M5Stack Cardputer into a TV remote that controls Samsung TVs and T-COM set-top boxes.

## Hardware Requirements

- M5Stack Cardputer (ESP32-based)
- IR LED connected to GPIO pin 44

## Features

- Visual on-screen remote control interface
- Dual mode support: Samsung TV and T-COM set-top box
- Keyboard-driven control

## Keyboard Controls

| Key | Samsung TV | T-COM |
|-----|-----------|-------|
| `0-9` | Number keys | Number keys |
| `s` | Volume Up | Volume Up |
| `z` | Volume Down | Volume Down |
| `m` | Mute | Mute |
| `f` | Channel Up | Channel Up |
| `c` | Channel Down | Channel Down |
| `,` `;` `/` `.` | Left/Up/Right/Down | Left/Up/Right/Down |
| `Enter` | OK | OK |
| `Space` | Home | Home |
| `Backspace` | Exit | Exit |
| `Tab` | Power | Power |
| `FN` | Toggle Samsung/T-COM mode | Toggle Samsung/T-COM mode |
| Button A | Power On | Power On |

## Building

### Option 1: PlatformIO (Recommended)

1. Install PlatformIO:
```bash
pip install platformio
```

2. Create `platformio.ini` in the project root (already included):
```ini
[env:m5stack-cardputer]
platform = espressif32
board = m5stack-cores3
framework = arduino
monitor_speed = 115200
upload_speed = 1500000
lib_deps = 
    m5stack/M5Cardputer@^1.0.1
    z3t0/IRremote@^4.3.0
```

3. Build and upload:
```bash
pio run --target upload
```

Or use the included Makefile:
```bash
make          # Build
make upload   # Build and upload
make monitor  # Open serial monitor
make clean    # Clean build artifacts
```

### Option 2: Arduino IDE

1. Install Arduino IDE
2. Install M5Stack Cardputer library via Library Manager
3. Install IRremote library via Library Manager
4. Open `M5CardRemote/src/M5CardRemote.ino` in Arduino IDE
5. Select "M5Stack Cardputer" as the board
6. Upload

## Project Structure

```
M5CardRemote/
├── src/
│   └── M5CardRemote.ino  # Main sketch
├── include/
│   ├── codes.h           # IR signal data
│   └── NotoSansBold15.h  # Font data
├── platformio.ini         # PlatformIO configuration
├── Makefile              # Build automation
└── README.md             # This file
```

## IR Configuration

- IR TX Pin: GPIO 44
- Samsung TV: Uses Samsung IR protocol
- T-COM: Uses raw 38kHz IR signals
