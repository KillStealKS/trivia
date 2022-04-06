#!/usr/bin/env python3

import socket

SERVER_IP = "localhost"
SERVER_PORT = 5656


def main():
    while True:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        server_address = (SERVER_IP, SERVER_PORT)
        sock.connect(server_address)

        msg = input("Enter message: ")
        sock.sendall(msg.encode())

        if msg == "QUIT":
            break

        server_msg = sock.recv(1024).decode()
        print(server_msg)

    sock.close()


if __name__ == "__main__":
    main()
