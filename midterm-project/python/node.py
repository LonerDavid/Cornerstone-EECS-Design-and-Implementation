from enum import IntEnum


# You can get the enumeration based on integer value, or make comparison
# ex: d = Direction(1), then d would be Direction.NORTH
# ex: print(Direction.SOUTH == 1) should return False
class Direction(IntEnum):
    NORTH = 1
    SOUTH = 3
    WEST = 4
    EAST = 2


# Construct class Node and its member functions
# You may add more member functions to meet your needs
class Node:
    def __init__(self, index: int = 0):
        self.index = index
        # store successor as (Node, direction to node, distance)
        self.successors = []

    def get_index(self):
        return self.index

    def get_successors(self):
        return self.successors

    def set_successor(self, successor, direction, length=1):
        self.successors.append((successor, Direction(direction), int(length)))
        print(f"For Node {self.index}, a successor {self.successors[-1]} is set.")
        return

    def get_direction(self, node):
        # TODO : if node is adjacent to the present node, return the direction of node from the present node
        # For example, if the direction of node from the present node is EAST, then return Direction.EAST = 4
        # However, if node is not adjacent to the present node, print error message and return 0
        prev = self.get_successors(node)
        dx = node - prev
        if dx == -1:
            return Direction.NORTH  # North
        elif dx == 1:
            return Direction.SOUTH  # South
        elif dx == 6:
            return Direction.WEST  # West
        elif dx == -6:
            return Direction.EAST  # East

    def is_successor(self, node):
        for succ in self.successors:
            if succ[0] == node:
                return True
        return False