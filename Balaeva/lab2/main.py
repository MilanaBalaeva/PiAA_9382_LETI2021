import sys
import typing
import networkx as nx
import numpy.random as rnd
import matplotlib.pyplot as plt
import pylab


class Edge:
    src: str
    dest: str
    weight: float
    dead: bool

    def __init__(self, src: str, dest: str, weight: float, dead: bool):
        self.src = src
        self.dest = dest
        self.weight = weight
        self.dead = dead


def get_minimal(graph: typing.List, src: str) -> int:
    k = -1
    minimal = float("+inf")

    for i, node in enumerate(graph):
        if not node.dead and node.src == src and node.weight < minimal:
            minimal = graph[i].weight
            k = i

    return k


def print_recursion(message, count):
    msg = ''
    for val in range(0, count):
        msg += " "
    print(msg + message)


def get_way(graph: typing.List, qwert: typing.List[str], src: str, dest: str, pr) -> bool:
    print_recursion('Вход в рекурсию', pr)
    print_recursion("Добавляем '" + src + "' в массив пути(в ответ)", pr)
    qwert.append(src)

    if src == dest:
        print_recursion('Выход из рекурсии', pr)
        return True
    print_recursion("Находим ребро с минимальным весом для данной вершины'" + src + "'", pr)
    k = get_minimal(graph, src)
    m = str(graph[k].weight)
    print_recursion("Минимальное ребро:'" + src + graph[k].dest + "' с весом: " + m, pr)
    while k != -1:
        if get_way(graph, qwert, graph[k].dest, dest, pr + 1):
            print_recursion('Выход из рекурсии', pr)
            return True
        print_recursion("Удаляем вершину'"+ qwert[len(qwert)-1] + "' из массива ответа( из ответа) вершин", pr)
        qwert.pop(len(qwert) - 1)
        print_recursion("Отмечаем вершину'" + graph[k].dest + "'  посещенной", pr)
        graph[k].dead = True
        k = get_minimal(graph, src)

    print_recursion('Выход из рекурсии', pr)
    return False


if __name__ == "__main__":
    src, dest = input().split()

    graph = []
    qwert = []
    edges = []

    data = sys.stdin.readline()
    while data.strip():
        _src, _dest, _weight = data.split()
        _weight = float(_weight)
        edge = Edge(_src, _dest, _weight, False)
        graph.append(edge)
        edges.append((_src, _dest))
        data = sys.stdin.readline()

    way = get_way(graph, qwert, src, dest, 0)
    print("Ответ:" + ''.join(qwert))

    # РИСОВАНИЕ ГРАФА

    G = nx.DiGraph()
    for i in range(0, len(graph)):
        G.add_edge(graph[i].src, graph[i].dest, weight=graph[i].weight)
    pos = nx.spring_layout(G)
    nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'),
                           node_color='r', node_size=500)
    nx.draw_networkx_labels(G, pos)
    nx.draw_networkx_edges(G, pos, edgelist=edges, edge_color='r', arrows=True)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()
