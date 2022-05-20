#!/usr/bin/env python3

import socket
import ubjson
import re
import hashlib

SERVER_IP = "localhost"
SERVER_PORT = 5656

SIGNUP_CODE = 2
LOGIN_CODE = 1


def get_input(name, regex=".*"):
    res = input(f"Enter {name}: ")
    if re.search(regex, res):
        return res
    else:
        print("Invalid input. Please try again.")
        return get_input(name, regex)


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    while True:
        print("Welcome to the Magshimim Trivia Game!\n" "1. Signup\n" "2. Login\n")
        is_signup = True if int(input("Choose an option: ")) == 1 else False

        username = get_input("username")
        password = hashlib.sha256(
            get_input(
                "password",
                "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{3,}$",
            ).encode()
        ).hexdigest()

        if is_signup:
            email = get_input("email", "^\S+@\S+$")
            addr = get_input("address", "^[A-z]+, \d+, [A-z]+$")
            phone = get_input("phone number", "^0\d{1,2}\d{7}$")
            date = get_input(
                "birth date", "^((\d{2}\/\d{2}\/\d{4})|(\d{2}\.\d{2}\.\d{4}))$"
            )
            content = {
                "username": username,
                "password": password,
                "email": email,
                "address": addr,
                "phone": phone,
                "date": date,
            }
            code = SIGNUP_CODE
        else:
            content = {"username": username, "password": password}
            code = LOGIN_CODE

        content = ubjson.dumpb(content)
        coontent_len = len(content).to_bytes(4, byteorder="big")
        code = code.to_bytes(1, byteorder="big")

        msg = code + coontent_len + content
        sock.sendall(msg)

        if msg == "QUIT":
            break

        server_msg = sock.recv(1024)
        code = server_msg[0]
        coontent_len = int.from_bytes(server_msg[1:5], byteorder="little")
        content = ubjson.loadb(server_msg[5:])
        print(code, coontent_len, content)

    sock.close()


if __name__ == "__main__":
    main()
