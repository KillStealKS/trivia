from ast import Str
from typing import Any, Dict
import requests
import sqlite3
from sqlite3 import Error, Connection

AMOUNT = 10
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

    sql = """DELETE FROM Questions;"""  # FIXME: Reset ID.

    try:
        c = conn.cursor()
        c.execute(sql)
    except Error as e:
        print(e)


def insert_question(conn: Connection, question: Dict) -> Any:
    sql = """INSERT INTO Questions(Question,Answer,Inc1,Inc2,Inc3)
             VALUES(?,?,?,?,?);"""

    c = conn.cursor()
    c.execute(
        sql,
        (
            question["question"],
            question["correct_answer"],
            question["incorrect_answers"][0],
            question["incorrect_answers"][1],
            question["incorrect_answers"][2],
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