from __future__ import annotations

from dataclasses import dataclass

import hid


class Controller:
    @dataclass
    class JoyStick:
        x: float = 0
        y: float = 0

    LSB: JoyStick = JoyStick()
    RSB: JoyStick = JoyStick()

    DPAD: int = 0

    A: bool = False
    B: bool = False
    X: bool = False
    Y: bool = False
    LB: bool = False
    RB: bool = False

    _bin: list = range(0, 256)

    def _mapJoyStick(self, x: int, y: int) -> tuple[float, float]:
        """
        Map Joystick values from range [0, 255] to [-1, 1]
        :param x: X - Axis value
        :param y: Y - Axis value
        :return: Tuple (x, y) containing transformed coordinates
        """
        assert x in self._bin
        assert y in self._bin

        dist: float = 255 / 2
        x: float = (x - dist) / 255
        y: float = (y - dist) / 255

        return x, y

    def SetLSB(self, x: int, y: int) -> None:
        """
        Set LSB Joystick X and Y axis values.
        """
        x, y = self._mapJoyStick(x, y)
        self.LSB.x = x
        self.LSB.y = y

    def SetRSB(self, x: int, y: int) -> None:
        """
        Set RSB Joystick X and Y axis values.
        """
        x, y = self._mapJoyStick(x, y)
        self.RSB.x = x
        self.RSB.y = y


class ControllerInputReader:
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

        self.Controller = Controller()

    def GetController(self) -> Controller:
        return self.Controller

    def InputReader(self):
        """
        Read input of Gamepad
        :return: Tuple containing transformed variables on input, else None
        """
        input = self.gamepad.read(64)
        if input:
            Ljoystick = input[:3]

            self.Controller.SetRSB(input[5], input[7])

            Rjoystick = input[3:6]

            button = input[10]
            match input[10]:
                case 1:
                    self.Controller.A = True
                case 2:
                    self.Controller.B = True
                case 4:
                    self.Controller.X = True
                case 8:
                    self.Controller.Y = True
