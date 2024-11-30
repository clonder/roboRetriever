from __future__ import annotations

from dataclasses import dataclass

from inputs import get_gamepad
import math
import threading


class Controller:
    MAX_TRIG_VAL = math.pow(2, 8)
    MAX_JOY_VAL = math.pow(2, 15)

    @dataclass
    class JoyStick:
        x: float = 0
        y: float = 0

    LSB: JoyStick = JoyStick()
    RSB: JoyStick = JoyStick()

    A: bool = False
    B: bool = False
    X: bool = False
    Y: bool = False
    LB: bool = False
    RB: bool = False

    _bin: list = range(0, 256)

    def __init__(self):
        self._monitor_thread = threading.Thread(target=self.read_controller, args=())
        self._monitor_thread.daemon = True
        self._monitor_thread.start()

    def read_controller(self):
        while True:
            events = get_gamepad()
            for event in events:
                if event.code == 'ABS_Y':
                    self.LSB.y = event.state / Controller.MAX_JOY_VAL
                elif event.code == 'ABS_X':
                    self.LSB.x = event.state / Controller.MAX_JOY_VAL
                elif event.code == 'ABS_RY':
                    self.RSB.y = event.state / Controller.MAX_JOY_VAL
                elif event.code == 'ABS_RX':
                    self.RSB.x = event.state / Controller.MAX_JOY_VAL
                elif event.code == 'BTN_SOUTH':
                    self.A = event.state == 1
                elif event.code == 'BTN_NORTH':
                    self.Y = event.state == 1
                elif event.code == 'BTN_WEST':
                    self.X = event.state == 1
                elif event.code == 'BTN_EAST':
                    self.B = event.state == 1

    def input_writer(self) -> str:
        """
        Write game pad input to string
        :return: String containing the input
        """
        input = f'[lsb:({self.LSB.x}, {self.LSB.y}), ' \
                f'rsb:({self.RSB.x}, {self.RSB.y}), ' \
                f'buttons: A:{self.A}, B:{self.B}, X:{self.X}, Y:{self.Y}]\n'
        return input
