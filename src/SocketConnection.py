import socket

HOST = "192.168.4.1"
PORT = 80

class SocketConnection:
    """
    Wifi socket connection to the ESP32
    """
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((HOST, PORT))

    def listener(self) -> str:
        pass

    def sender(self, data: str) -> None:
        """
        Send data over socker
        :param data: Data formatted as string
        """
        self.s.send(data.encode())
