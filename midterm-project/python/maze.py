import csv
import logging
import math
from enum import IntEnum
from typing import List

import numpy as np
import pandas
from collections import deque

from node import Direction, Node

log = logging.getLogger(__name__)


class Action(IntEnum):
    ADVANCE = 1
    U_TURN = 2
    TURN_RIGHT = 3
    TURN_LEFT = 4
    HALT = 5


class Maze:
    def __init__(self, filepath: str):
        # TODO : read file and implement a data structure you like
        # For example, when parsing raw_data, you may create several Node objects.
        # Then you can store these objects into self.nodes.
        # Finally, add to nd_dict by {key(index): value(corresponding node)}
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.node_dict = dict() # key: index, value: the correspond node
        self.max_points = 0
        self.max_path = []
        self.amount = len(self.max_path)
        self.nodes = []
        self.cmd = [] * (self.amount)

        for row in self.raw_data:
            node = int(row[0])
            neighbors = [int(x) for x in row[1:5] if not np.isnan(x)]
            self.node_dict[node] = neighbors
        #print(self.raw_data)
        #print(self.node_dict)

    def get_start_point(self):
        if len(self.node_dict) < 2:
            log.error("Error: the start point is not included.")
            return 0
        return self.node_dict[1]

    def get_node_dict(self):
        return self.node_dict

    def BFS(self, node: Node):
        # TODO : design your data structure here for your algorithm
        # Tips : return a sequence of nodes from the node to the nearest unexplored deadend
        return None

    def BFS_2(self, node_from: Node, node_to: Node):
        # TODO : similar to BFS but with fixed start point and end point
        # Tips : return a sequence of nodes of the shortest path
        queue = deque([(node_from, [node_from])])
        visited = set()
        predecessor = {}  # Dictionary to store predecessors

        while queue:
            node, path = queue.popleft()
            visited.add(node)

            if node == node_to:
                #print(path)
                #print(len(path)-1)
                return path  # Return both the path and predecessors

            for neighbor in self.node_dict.get(node, []):
                if neighbor not in visited:
                    predecessor[neighbor] = node  # Update predecessor of neighbor
                    queue.append((neighbor, path + [neighbor]))
        return None


    def getAction(self, car_dir, node_from: Node, node_to: Node):
        # TODO : get the car action
        # Tips : return an action and the next direction of the car if the node_to is the Successor of node_to
        # If not, print error message and return 0
        dx = node_to - node_from
        if dx == -1:
            dir = Direction.NORTH  # North
        elif dx == 1:
            dir = Direction.SOUTH  # South
        elif dx == 6:
            dir = Direction.WEST  # West
        elif dx == -6:
            dir = Direction.EAST  # East

        if car_dir - dir == 0:
            return Action.ADVANCE, dir  # Front
        elif car_dir - dir == 2:
            return Action.U_TURN, dir  # Back
        elif car_dir - dir == -2:
            return Action.U_TURN, dir  # Back
        elif car_dir - dir == 1:
            return Action.TURN_LEFT, dir  # Left
        elif car_dir - dir == -3:
            return Action.TURN_LEFT, dir  # Left
        elif car_dir - dir == 3:
            return Action.TURN_RIGHT, dir # Right
        elif car_dir - dir == -1:
            return Action.TURN_RIGHT, dir  # Right
        
        return None

    def getActions(self, nodes: List[Node],car_dir_init):
        # TODO : given a sequence of nodes, return the corresponding action sequence
        # Tips : iterate through the nodes and use getAction() in each iteration
        action_sequence = []
        car_dir = car_dir_init
        for i in range(len(nodes) - 1):  # Iterate through the range of indices of nodes
            action, car_dir = self.getAction(car_dir, nodes[i], nodes[i+1])
            #print(action, car_dir) 
            action_sequence.append(action)
            if i == len(nodes) - 1 -1:
                car_dir_current = car_dir
        
        return action_sequence,car_dir_current

    def actions_to_str(self, actions):
        # cmds should be a string sequence like "fbrl....", use it as the input of BFS checklist #1
        cmd = "fbrls"
        cmds = ""
        for action in actions:
            cmds += cmd[action - 1]
        log.info(cmds)
        return cmds

    def strategy(self, node: Node):
        return self.BFS(node)

    def strategy_2(self, node_from: Node, node_to: Node):
        return self.BFS_2(node_from, node_to)
    
    def multiple_node(self,nodes:List[Node]):
        start = nodes[0]
        end = nodes[1]
        car_dir = int(input("Enter the initial direction(1=North,2=East,3=South,4=West) :"))
        for i in range(self.amount-1):
            cmd_total = ""
            start = nodes[i]
            end = nodes[i+1]
            cmd_sequence,car_dir = self.getActions(self.BFS_2(start, end),car_dir)
            self.cmd.append(self.actions_to_str(cmd_sequence))
            #print(cmd[i])
        cmd_total = ""
        pathlist = []
        for i in range(len(self.cmd)):
            pathlist.insert(i,self.cmd[i])
            cmd_total += self.cmd[i]
            
            if i == len(self.cmd) - 1:
                print(self.cmd[i])
            else:
                print(self.cmd[i], end="") 
        print(pathlist)
        return cmd_total
     
    def distance(self, node_from: Node, node_to: Node):
        path = self.BFS_2(node_from,node_to)
        if path == None:
            return None
        else:
            return len(path)-1
        
    def total_point(self, nodes):
        total = 0
        for node in nodes:
            total += 10 * self.distance(node, 6)  # Point of each node is the distance to node 6
        return total

    def permute(self ,nodes, start, max_distance, current_path=[], current_distance=0):
        
        
        if current_distance > max_distance:
            return
        
        if len(current_path) > len(self.max_path):
            self.max_path = current_path[:]
            self.max_points = self.total_point(current_path)
        
        for i in range(len(nodes)):
            next_node = nodes[i]
            next_distance = self.distance(start, next_node)
            
            # Add the next node to the current path
            new_path = current_path + [next_node]
            
            # Recursively generate permutations for the rest of the elements
            self.permute(nodes[:i] + nodes[i+1:], next_node, max_distance, new_path, current_distance + next_distance)
    
    
    
    
            

if __name__ == "__main__":

    M = Maze(filepath='data/big_maze_112.csv')
    
    
    #print(M.distance(start,end))
    # Driver code
    specified_nodes = [3, 5, 7, 15, 16, 27, 28, 31, 34, 37, 43, 48]
    start_node = 6
    max_distance = 25

    # Remove start_node from specified_nodes if it's present
    if start_node in specified_nodes:
        specified_nodes.remove(start_node)

    # Add start_node to the beginning of the specified_nodes list
    specified_nodes.insert(0, start_node)

    

    M.permute(specified_nodes, 6, max_distance)
    #M.multiple_node(max_path)
    print("Path with the most points within the max distance:", M.max_path)
    print("Total points:", M.max_points)
    
    M.amount = len(M.max_path)
    M.nodes = []
    M.cmd = [] * (M.amount)
    
    for i in range(0, M.amount):
        ele = M.max_path[i]
        # adding the element
        M.nodes.append(ele)
    M.multiple_node(M.nodes)
    '''
    print(M.distance(6,5))
    print(M.distance(6,3))
    print(M.distance(6,27))
    print(M.distance(6,31))
    print(M.distance(6,37))
    print(M.distance(6,43))
    print(M.distance(6,48))
    '''
    
    