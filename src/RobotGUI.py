import tkinter as tk
from ControllerInput import Controller
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

        self.game_pad = Controller()
        self.socket = SocketConnection()

        self.window = tk.Tk()
        self.MainGUI()

        self.update_gui_joy_stick()

        self.window.mainloop()

    def MainGUI(self):
        self.paint_joy_stick()


    def paint_joy_stick(self):
        self.canvas = tk.Canvas(self.window, width=CANVAS_SIZE, height=CANVAS_SIZE, bg="white")
        self.canvas.pack()

        self.canvas.create_oval(CANVAS_SIZE // 2 - JOYSTICK_RADIUS, CANVAS_SIZE // 2 - JOYSTICK_RADIUS,
                           CANVAS_SIZE // 2 + JOYSTICK_RADIUS, CANVAS_SIZE // 2 + JOYSTICK_RADIUS,
                           outline="black")

        self.joystick = self.canvas.create_oval(CANVAS_SIZE // 2 - 10, CANVAS_SIZE // 2 - 10,
                                      CANVAS_SIZE // 2 + 10, CANVAS_SIZE // 2 + 10,
                                      fill="blue")

    def update_gui_joy_stick(self):
        """
        Periodically reads input from gamepad and updates Joystick position in GUI.
        """
        self.socket.sender(self.game_pad.input_writer())

        dx = (self.game_pad.LSB.x) * JOYSTICK_RADIUS
        dy = (self.game_pad.LSB.y) * JOYSTICK_RADIUS

        self.canvas.coords(self.joystick, CANVAS_SIZE // 2 + dx - 10, CANVAS_SIZE // 2 + dy - 10,
            CANVAS_SIZE // 2 + dx + 10, CANVAS_SIZE // 2 + dy + 10)

        self.window.after(10, self.update_gui_joy_stick)

if __name__ == '__main__':
    RobotGUI()