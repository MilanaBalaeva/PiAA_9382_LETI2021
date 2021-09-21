import sys
import typing
import networkx as nx
import numpy.random as rnd
import matplotlib.pyplot as plt
import pylab



class Edge:

    def __init__(self, src: str, dest: str, weight: int):
        self.src = src
        self.dest = dest
        self.weight = weight


class Vertex:

    def __init__(self, name: str, src: typing.Any, f: int, g: int):
        self.name = name
        self.src = src
        self.f = f
        self.g = g

    def __str__(self) -> str:
        if self.src:
            return str(self.src) + self.name
        return self.name


def minimal_f(q: typing.List[Vertex]) -> int:
    k = 0
    minimal = q[k]

    for i in range(1, len(q)):

        if q[i].f == minimal.f:
            if minimal.f - minimal.g > q[i].f - q[i].g:
                minimal = q[i]
                k = i

        elif q[i].f < minimal.f:
            minimal = q[i]
            k = i

    return k




def A1(graph: typing.List[Edge], start: str, end: str):
    q = []
    u = []

    begin = Vertex(start, None, abs(ord(end) - ord(start)), 0)
    q.append(begin)
    print("Записываем " + "'" + begin.name +"'" + " в список рассматриваемых вершин")

    while q:

        index = minimal_f(q)
        current = q[index]
        if current.name == end:
            print("Ответ: "  + str(current))
            return True
        print("Удаляем " + "'" + q[index].name + "'" + " из списка рассматриваемых вершин")
        q.pop(index)
        print("Cписок рассматриваемых вершин:")
        for i in range(len(q)):
            print(q[i].name, end="")
        print(" ")
        print("Записываем " + "'" + current.name + "'" + " в список посещенных вершин")
        u.append(current)
        print("Cписок посещенных вершин:")
        for i in range(len(u)):
            print(u[i].name, end = "")
        print(" ")

        for i in range(len(graph)):
            if current.name == graph[i].src:
                print("Находим смежную вершину для " + "'" + current.name + "'" + " c наименьшей эвристикой и наименьшим весом")
                neighbor = Vertex(graph[i].dest, current,
                                  abs(ord(end) - ord(graph[i].dest)) + graph[i].weight + current.g,
                                  graph[i].weight + current.g)
                print("Выбрана вершина: " + "'" + neighbor.name + "'")
                l = str(graph[i].weight)
                print("Вес текущего ребра " + "'" + current.name + neighbor.name + "'" + " равен: " + l)
                print(" наименьшая стоимость пути в' " + neighbor.name + "' из стартовой вершины = "+ str(neighbor.g))
                print(" эвристическое приближение стоимости пути от ' " + neighbor.name + "' до конечной цели." + str(neighbor.f-neighbor.g))
                if neighbor in u:
                    continue

                if neighbor not in q:
                    q.append(neighbor)
                    print("Записываем " + "'" + neighbor.name + "'" + "в список рассматриваемых вершин")

                else:
                    index_neighbor = q.index(neighbor)

                    if neighbor.g < q[index_neighbor].g:
                        print("Заменяем " + "'" + q[index_neighbor].name + "' на '" +current + "'")
                        q[index_neighbor].src = current
                        q[index_neighbor].g = neighbor.g
                        q[index_neighbor].f = neighbor.f


    return False


if __name__ == "__main__":
    begin, last = input().split()
    graph = []
    edges = []
    data = sys.stdin.readline()
    while data.strip():
        src, dest, weight = data.split()
        weight = int(float(weight))
        graph.append(Edge(src, dest, weight))
        edges.append((src, dest))
        data = sys.stdin.readline()
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

    A1(graph, begin, last)