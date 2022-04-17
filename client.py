#!/usr/bin/env python3

import socket
import ubjson
import struct

SERVER_IP = "localhost"
SERVER_PORT = 5656

SIGNUP_CODE = 1
LOGIN_CODE = 2


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    while True:
        is_signup = (
            True
            if input("S for signup, any other key for login: ").lower() == "s"
            else False
        )

        username = input("Enter username: ")
        password = input("Enter password: ")

        if is_signup:
            mail = input("Enter mail: ")
            content = {"username": username, "password": password, "mail": mail}
            code = SIGNUP_CODE
        else:
            content = {"username": username, "password": password}
            code = LOGIN_CODE

        content = ubjson.dumpb(content)
        len = len(content).to_bytes(4, byteorder="big")
        code = code.to_bytes(1, byteorder="big")

        msg = code + len + content
        sock.sendall(msg.encode())

        if msg == "QUIT":
            break

        server_msg = sock.recv(1024).decode()
        code = int.from_bytes(server_msg[0], byteorder="big")
        len = int.from_bytes(server_msg[1:5], byteorder="big")
        content = ubjson.loadb(server_msg[5:])
        print(code, len, content)

    sock.close()


if __name__ == "__main__":
    main()
