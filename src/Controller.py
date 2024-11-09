from __future__ import annotations

import hid

class Controller:
    """
    Read controller inputs
    Input is a list of 12 entries.

    Input dictionary:

    index 0-2:
        Left joystick

    index 3 - 5:
        Right joystick

    index 8-10:
        LT - RT

    index 10:
        0 -> Nothing
        1 -> Button A
        2 -> Button B
        4 -> Button X
        8 -> Button Y
        16 -> Button LB
        32 -> Button RB
        64 -> Button Back
        128 -> Button Start

    index 11:
        0 -> Nothing
        1 -> LSB
        2 -> RSB
        4 -> D-PAD Up
        12 -> D-PAD Right
        28 -> D-PAD Left
        20 -> D-PAD Down

    """
    def __init__(self):
        self.gamepad = hid.device()
        self.gamepad.open(0x0e6f, 0x0413)
        self.gamepad.set_nonblocking(True)

    def InputReader(self) -> tuple | None:
        """
        Read input of Gamepad
        :return: Tuple containing transformed variables on input, else None
        """
        input = self.gamepad.read(64)
        if input:
            Ljoystick = input[:3]

            Rjoystick = input[3:6]

            button = input[10]

            button1 = input[11]
            return self.MapJoystick(input[5], input[7]), button, button1
        return None

    def MapJoystick(self, x: int, y: int) -> tuple[float, float]:
        """
        Map Joystick values from range [0, 255] to [-1, 1]
        :param x: X - Axis value
        :param y: Y - Axis value
        :return: Tuple (x, y) containing transformed coordinates
        """
        assert x is not None and y is not None

        dist: float = 255 / 2
        x: float = (x - dist) / 255
        y: float = (y - dist) / 255

        return x, y
