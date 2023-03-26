class Node:
    def __init__(self, id, posx, posy,type,unvisited):
        self.id = id
        self.pos = [posx, posy]
        self.adjacents = {}
        self.unvisited = unvisited
        self.type = type

    def get_id(self):
        return self.id

    def add_adjacent(self, adjacent, weight=0):
        self.adjacents[adjacent] = weight

    def get_connections(self):
        return self.adjacents.keys()
    def get_unvisited_directions(self):
        return self.unvisited
    def get_weight(self, adjacent_id):
        return self.adjacents[adjacent_id]

    def get_type(self):
        return self.type

    def get_pos_x(self):
        return int(self.pos[0])

    def get_pos_y(self):
        return int(self.pos[1])
