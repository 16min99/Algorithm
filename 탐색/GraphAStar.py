# -*- coding:utf-8 -*-
# 그래프 A*알고리즘
# by 전민규

class Graph:  # 그래프 (lanelet)
    # 초기화
    def __init__(self, graph_dict=None, directed=True):
        self.graph_dict = graph_dict or {}
        self.directed = directed
        if not directed:
            self.make_undirected()

    def make_undirected(self):
        for a in list(self.graph_dict.keys()):
            for (b, dist) in self.graph_dict[a].items():
                self.graph_dict.setdefault(b, {})[a] = dist

    def connect(self, A, B, distance):
        self.graph_dict.setdefault(A, {})[B] = distance
        if not self.directed:
            self.graph_dict.setdefault(B, {})[A] = distance

    def get(self, a, b=None):
        links = self.graph_dict.setdefault(a, {})
        if b is None:
            return links
        else:
            return links.get(b)

class node:  # 노드
    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y




def astar_search(graph, mynode, start, end): # A* search
    class Node:
        def __init__(self, name, parent):
            self.name = name
            self.parent = parent
            self.g = 0
            self.h = 0
            self.f = 0

        # 연산자 오버로딩
        def __eq__(self, other):  # ==
            return self.name == other.name

        def __lt__(self, other):  # >,<
            return self.f < other.f

        def __repr__(self):  # print format
            return ('({0},{1})'.format(self.name, self.f))


    def add_to_open(open, neighbor):
        for node in open:  # open에 있는 있는 것보다 f가 크면 추가 안해줌
            if (neighbor == node and neighbor.f > node.f):
                return False
        return True

    def heuristic(now, goal):  # heuristic을 계산하는 함수
        dx = abs(now.x - goal.x)
        dy = abs(now.y - goal.y)
        return (dx * dx + dy * dy) ** 0.5



    open = []
    closed = []

    start_node = Node(start, None) # start_node.name = 'A'
    goal_node = Node(end, None) # goal_node.name = 'F'

    open.append(start_node)



    while len(open) > 0: #open이 empty될때 까지
    
        # open에 저장된 Node중 f가 가장 낮은순서로 정렬후 현재 노드로 저장
        open.sort()

        current_node = open.pop(0)
        # 현재노드 closed에 추가
        closed.append(current_node)

        # 목적지 도착했으면 출력
        if current_node == goal_node:
            path = []
            while current_node != start_node:
                path.append(current_node.name + ': ' + str(current_node.g)) #실제이동한거리
                current_node = current_node.parent
            
            path.append(start_node.name + ': ' + str(start_node.g))
            # Return
            return path[::-1]

        def dxdy 


        neighbors = graph.get(current_node.name)
        
        for key, value in neighbors.items():
            neighbor = Node(key, current_node)
            if (neighbor in closed):
                continue #중복을 방지한거야

            neighbor.g = current_node.g + graph.get(current_node.name, neighbor.name) # get은 실제 길의 거리g를 불러오는거다
                                
            neighbor.h = heuristic(mynode[current_node.name], mynode[neighbor.name])
            neighbor.f = neighbor.g + neighbor.h
            if (add_to_open(open, neighbor) == True): # open에 있는 있는 것보다 f가 크면 추가 안해줌
                open.append(neighbor)
    return None #목적지 까지 경로가 없을때 아무것도 출력하지 않음



############################################################### 여기서 부터 보면 됩니다.
def main():
    # Node set     mynode['이름'] = node('이름',x좌표,y좌표)
    mynode = {}
    mynode['A'] = node('A', 1, 1)
    mynode['B'] = node('B', 5, 1)
    mynode['C'] = node('C', 2, 4)
    mynode['D'] = node('D', 5, 6)
    mynode['E'] = node('E', 9, 5)
    mynode['F'] = node('F', 6, 9)
    mynode['G'] = node('G', 11, 9)

    # lane set (A, B, distance)  A to B
    graph = Graph()
    graph.connect('A', 'B', 5)
    graph.connect('A', 'C', 4)
    graph.connect('B', 'E', 7)
    graph.connect('B', 'D', 4)
    graph.connect('C', 'D', 5)
    graph.connect('D', 'F', 4)
    graph.connect('D', 'E', 5)
    graph.connect('E', 'D', 5)
    graph.connect('E', 'G', 6)
    graph.connect('F', 'G', 9)

    #   graph.make_undirected()

    # (graph,mynode,출발노드이름,도착노드이름)
    print(astar_search(graph, mynode, 'A', 'F'))


if __name__ == "__main__": main()