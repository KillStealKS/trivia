from ast import Str
from typing import Any, Dict
import requests
import sqlite3
from sqlite3 import Error, Connection
from bs4 import BeautifulSoup as bs

AMOUNT = 100
URL = f"https://opentdb.com/api.php?amount={AMOUNT}&type=multiple"
DB_FILE = "./questions.sqlite"


def create_connection(db_file: Str) -> Connection:
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except Error as e:
        print(e)

    return conn


def create_table(conn: Connection) -> None:
    sql = """CREATE TABLE IF NOT EXISTS Questions (
        ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
        Question TEXT NOT NULL, 
        Answer TEXT NOT NULL, 
        Incorrect1 TEXT NOT NULL, 
        Incorrect2 TEXT NOT NULL, 
        Incorrect3 TEXT NOT NULL);"""

    try:
        c = conn.cursor()
        c.execute(sql)
    except Error as e:
        print(e)

    sql = """DELETE FROM Questions;"""

    try:
        c = conn.cursor()
        c.execute(sql)
    except Error as e:
        print(e)


def insert_question(conn: Connection, question: Dict) -> Any:
    sql = """INSERT INTO Questions(Question,Answer,Incorrect1,Incorrect2,Incorrect3)
             VALUES(?,?,?,?,?);"""

    c = conn.cursor()
    c.execute(
        sql,
        (
            bs(question["question"]).text,
            bs(question["correct_answer"]).text,
            bs(question["incorrect_answers"][0]).text,
            bs(question["incorrect_answers"][1]).text,
            bs(question["incorrect_answers"][2]).text,
        ),
    )
    conn.commit()
    return c.lastrowid


def main() -> None:
    response = requests.get(URL)
    questions = response.json()
    # print(questions)

    if questions["response_code"] == 0:
        questions = questions["results"]
    else:
        print("Error while fetching questions")
        return

    conn = create_connection(DB_FILE)
    create_table(conn)

    for q in questions:
        insert_question(conn, q)


if __name__ == "__main__":
    main()