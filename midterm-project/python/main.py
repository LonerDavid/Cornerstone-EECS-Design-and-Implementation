import argparse
import logging
import os
import sys
import time

import numpy as np
import pandas

from BTinterface import BTInterface
from maze import Action, Maze
from score import ScoreboardServer, ScoreboardFake

logging.basicConfig(
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s", level=logging.INFO
)

log = logging.getLogger(__name__)

# TODO : Fill in the following information (Done)
TEAM_NAME = "Team 7 Wed-AM"
SERVER_URL = "http://140.112.175.18:5000/"
MAZE_FILE = "data/medium_maze.csv"
BT_PORT = "COM10"


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("mode", help="0: treasure-hunting, 1: self-testing", type=str)
    parser.add_argument("--maze-file", default=MAZE_FILE, help="Maze file", type=str)
    parser.add_argument("--bt-port", default=BT_PORT, help="Bluetooth port", type=str)
    parser.add_argument(
        "--team-name", default=TEAM_NAME, help="Your team name", type=str
    )
    parser.add_argument("--server-url", default=SERVER_URL, help="Server URL", type=str)
    return parser.parse_args()


def main(mode: int, bt_port: str, team_name: str, server_url: str, maze_file: str):
    maze = Maze(maze_file)
    point = ScoreboardServer(team_name, server_url)
    #point = ScoreboardFake("your team name", "data/fakeUID.csv") # for local testing
    interface = BTInterface(port=bt_port)
    # TODO : Initialize necessary variables

    if mode == "0":
        log.info("Mode 0: For treasure-hunting")
        # TODO : for treasure-hunting, which encourages you to hunt as many scores as possible

    elif mode == "1":
        log.info("Mode 1: Self-testing mode.")
        # TODO: You can write your code to test specific function.
        M = Maze(filepath=MAZE_FILE)
        start = int(input("Enter the start : "))
        end = int(input("Enter the end : "))
        #幫我改這邊 用list把路徑儲存到moves中
        moves = []
        moves = M.actions_to_str(M.getActions(M.BFS_2(start, end)))
        #或是用字串輸出後用append儲存 看你
        moves = []
        moves_in_string = maze.strategy(1)
        for letter in moves_in_string:
            moves.append(letter)
        
        print(cmd)
        interface.start()
        interface.send_action(cmd[0])
        notfinish = True
        i = 0
        while notfinish:
            uid = interface.get_UID()
            if isinstance(uid,str):
                interface.send_action(moves.pop(0))
                
                print("Current raw uid: ")
                print(uid)
                result = uid.strip()[2:10]
                point.add_UID(result)
                
                print("Current : ")
                print(point.get_current_score())


            if cmd[i-1] == 'e': #finish
                interface.end_process()
                final_score = point.get_current_score()
                print("Final : ")
                print(final_score)
                notfinish = False
                    
    elif mode == '2':
        log.info("Mode 2: Mannual Route Input")
        # TODO: You can write your code to test specific function.
        M = Maze(filepath=MAZE_FILE)
        #start = int(input("Enter the start : "))
        #end = int(input("Enter the end : "))
        #cmd = M.actions_to_str(M.getActions(M.BFS_2(start, end)))
        cmd = 'rbfble'
        print(cmd)
        interface.start()
        notfinish = True
        i = 0
        while notfinish:
            uid = interface.get_UID()
            if isinstance(uid,str):
                print("Current raw uid: ")
                print(uid)
                if uid=='0x6e0a':
                    if cmd == '': #finish
                        interface.end_process()
                        final_score = point.get_current_score()
                        print("Final : ")
                        print(final_score)
                        notfinish = False
                    else:
                        interface.send_action(cmd[i])
                        print("action sent: " + cmd[i])
                        i = i + 1

                else:
                    result = uid.strip()[2:10]
                    point.add_UID(result)
                    print("Current : ")
                    print(point.get_current_score())
                   
    else:
        log.error("Invalid mode")
        sys.exit(1)


if __name__ == "__main__":
    args = parse_args()
    main(**vars(args))
