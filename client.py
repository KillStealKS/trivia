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
        print(
            "Welcome to the Magshimim Trivia Game!\n"
            "1. Signup\n"
            "2. Login\n"
            "3. Signout\n"
            "4. Get players in room\n"
            "5. Get rooms\n"
            "6. Join room\n"
            "7. Create room\n"
            "8. Get personal stats\n"
            "9. Get highscore\n"
        )
        choice = int(input("Choose an option: "))

        if choice == 1:
            username = get_input("username")
            password = hashlib.sha256(
                get_input(
                    "password",
                    "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{3,}$",
                ).encode()
            ).hexdigest()

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
        elif choice == 2:
            username = get_input("username")
            password = hashlib.sha256(
                get_input(
                    "password",
                    "^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{3,}$",
                ).encode()
            ).hexdigest()

            content = {"username": username, "password": password}
            code = LOGIN_CODE
        elif choice == 3:
            content = ""
            code = 3
        elif choice == 4:
            room_id = int(input("Room ID: "))

            content = {"roomId": room_id}
            code = 4
        elif choice == 5:
            content = ""
            code = 5
        elif choice == 6:
            room_id = int(input("Room ID: "))

            content = {"roomId": room_id}

            code = 6
        elif choice == 7:
            content["roomName"] = input("Room name: ")
            content["maxUsers"] = int(input("maxUsers: "))
            content["questionCount"] = int(input("questionCount: "))
            content["answerTimeout"] = int(input("answerTimeout: "))
            
            code = 7    

        elif choice == 8:
            content = ""
            code = 8
        elif choice == 9:
            content = ""
            code = 9

        content = ubjson.dumpb(content)
        content_len = len(content).to_bytes(4, byteorder="big")
        code = code.to_bytes(1, byteorder="big")

        msg = code + content_len + content
        sock.sendall(msg)

        server_msg = sock.recv(1024)
        code = server_msg[0]
        content_len = int.from_bytes(server_msg[1:5], byteorder="little")
        content = ubjson.loadb(server_msg[5:])
        print(code, content_len, content)

    sock.close()


if __name__ == "__main__":
    main()
