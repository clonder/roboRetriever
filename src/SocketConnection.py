import socket

HOST = ...
PORT = ...

class SocketConnection:
    """
    Wifi socket connection to the ESP32
    """
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.bind((HOST, PORT))

    def listener(self):
        pass

    def sender(self, data: dict):
        self.s.send(data)