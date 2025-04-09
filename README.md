# due_usb_parallel

Use Arduino Due as a 3.3V Parallel I/O Converter via USB MIDI.

## Depends on

- [lathoub/Arduino-USBMIDI](https://github.com/lathoub/Arduino-USBMIDI)

## Usage

### Analog Write (PWM)
  - Arduino Due **receives** MIDI *CC* `#2` to `#13`
    - Mapped to `D2` to `D13` on Arduino

### Digital Write
  - Arduino Due **receives** MIDI *Note* `#14` to `#33`
    - Mapped to `D14` to `D33` on Arduino

### Digital Read
  - Arduino Due **sends** MIDI *Note* `#34` to `#53`
    - Mapped to `D34` to `D53` on Arduino

### Analog Read
  - Arduino Due **sends** MIDI *CC* `#54` to `#65`
    - Mapped to `D54` to `D65` on Arduino

### Analog Write (DAC)
  - Arduino Due **receives** MIDI *CC* `#66` and `#67`
    - Mapped to `DAC2/D66` and `DAC1/D67` on Arduino

## Pin mappings

| Arduino | Function | MIDI Role    | MIDI # |
| ------- | -------- | ------------ | ------ |
| D0      | (RX)     |              |        |
| D1      | (TX)     |              |        |
| D2      | PWM0     | Receive CC   | 2      |
| D3      | PWM1     | Receive CC   | 3      |
| D4      | PWM2     | Receive CC   | 4      |
| D5      | PWM3     | Receive CC   | 5      |
| D6      | PWM4     | Receive CC   | 6      |
| D7      | PWM5     | Receive CC   | 7      |
| D8      | PWM6     | Receive CC   | 8      |
| D9      | PWM7     | Receive CC   | 9      |
| D10     | PWM8     | Receive CC   | 10     |
| D11     | PWM9     | Receive CC   | 11     |
| D12     | PWM10    | Receive CC   | 12     |
| D13     | PWM11    | Receive CC   | 13     |
| D14     | DO0      | Receive Note | 14     |
| D15     | DO1      | Receive Note | 15     |
| D16     | DO2      | Receive Note | 16     |
| D17     | DO3      | Receive Note | 17     |
| D18     | DO4      | Receive Note | 18     |
| D19     | DO5      | Receive Note | 19     |
| D20     | DO6      | Receive Note | 20     |
| D21     | DO7      | Receive Note | 21     |
| D22     | DO8      | Receive Note | 22     |
| D23     | DO9      | Receive Note | 23     |
| D24     | DO10     | Receive Note | 24     |
| D25     | DO11     | Receive Note | 25     |
| D26     | DO12     | Receive Note | 26     |
| D27     | DO13     | Receive Note | 27     |
| D28     | DO14     | Receive Note | 28     |
| D29     | DO15     | Receive Note | 29     |
| D30     | DO16     | Receive Note | 30     |
| D31     | DO17     | Receive Note | 31     |
| D32     | DO18     | Receive Note | 32     |
| D33     | DO19     | Receive Note | 33     |
| D34     | DI0      | Send Note    | 34     |
| D35     | DI1      | Send Note    | 35     |
| D36     | DI2      | Send Note    | 36     |
| D37     | DI3      | Send Note    | 37     |
| D38     | DI4      | Send Note    | 38     |
| D39     | DI5      | Send Note    | 39     |
| D40     | DI6      | Send Note    | 40     |
| D41     | DI7      | Send Note    | 41     |
| D42     | DI8      | Send Note    | 42     |
| D43     | DI9      | Send Note    | 43     |
| D44     | DI10     | Send Note    | 44     |
| D45     | DI11     | Send Note    | 45     |
| D46     | DI12     | Send Note    | 46     |
| D47     | DI13     | Send Note    | 47     |
| D48     | DI14     | Send Note    | 48     |
| D49     | DI15     | Send Note    | 49     |
| D50     | DI16     | Send Note    | 50     |
| D51     | DI17     | Send Note    | 51     |
| D52     | DI18     | Send Note    | 52     |
| D53     | DI19     | Send Note    | 53     |
| A0      | AI0      | Send CC      | 54     |
| A1      | AI1      | Send CC      | 55     |
| A2      | AI2      | Send CC      | 56     |
| A3      | AI3      | Send CC      | 57     |
| A4      | AI4      | Send CC      | 58     |
| A5      | AI5      | Send CC      | 59     |
| A6      | AI6      | Send CC      | 60     |
| A7      | AI7      | Send CC      | 61     |
| A8      | AI8      | Send CC      | 62     |
| A9      | AI9      | Send CC      | 63     |
| A10     | AI10     | Send CC      | 64     |
| A11     | AI11     | Send CC      | 65     |
| DAC2    | AO0      | Receive CC   | 66     |
| DAC1    | AO1      | Receive CC   | 67     |

## Note

You can test MIDI I/O with command-line tools like [gbevin/SendMIDI](https://github.com/gbevin/SendMIDI) or python modules like [`mido`](https://github.com/mido/mido) + [`python-rtmidi`](https://github.com/SpotlightKid/python-rtmidi)(backend).