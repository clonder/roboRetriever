import tkinter as tk
from ControllerInputReader import ControllerInputReader
from SocketConnection import SocketConnection

JOYSTICK_RADIUS = 100
CANVAS_SIZE = 300


class RobotGUI:
    """
    GUI for the remote movement of the Quadruped robot.
    """
    def __init__(self):
        self.canvas = None
        self.joystick = None

        self.window = tk.Tk()

        self.game_pad = ControllerInputReader()
        self.socket = SocketConnection()

        self.MainGUI()

        self.UpdateJoyStick()

        self.window.mainloop()

    def MainGUI(self):
        self.PaintJoyStick()


    def PaintJoyStick(self):
        self.canvas = tk.Canvas(self.window, width=CANVAS_SIZE, height=CANVAS_SIZE, bg="white")
        self.canvas.pack()

        self.canvas.create_oval(CANVAS_SIZE // 2 - JOYSTICK_RADIUS, CANVAS_SIZE // 2 - JOYSTICK_RADIUS,
                           CANVAS_SIZE // 2 + JOYSTICK_RADIUS, CANVAS_SIZE // 2 + JOYSTICK_RADIUS,
                           outline="black")

        self.joystick = self.canvas.create_oval(CANVAS_SIZE // 2 - 10, CANVAS_SIZE // 2 - 10,
                                      CANVAS_SIZE // 2 + 10, CANVAS_SIZE // 2 + 10,
                                      fill="blue")

    def UpdateJoyStick(self):
        """
        Periodically reads input from gamepad and updates Joystick position in GUI.
        """
        result = self.game_pad.InputReader()
        if result is not None:
            RjoyStick, button, button1 = result

            dx = (RjoyStick[0]) * JOYSTICK_RADIUS
            dy = (RjoyStick[1]) * JOYSTICK_RADIUS

            self.canvas.coords(self.joystick, CANVAS_SIZE // 2 + dx - 10, CANVAS_SIZE // 2 + dy - 10,
                          CANVAS_SIZE // 2 + dx + 10, CANVAS_SIZE // 2 + dy + 10)

        self.window.after(10, self.UpdateJoyStick)

if __name__ == '__main__':
    RobotGUI()