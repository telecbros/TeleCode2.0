import sys
import copy

class Graph:

    def __init__(self):
        self.structure = {}
        self.E = 0 # Number of edges
    
    # Return the number of vertices
    def V(self):
        return len(self.structure)
    
    # Return the number of edges
    def E(self):
        return self.E
    
    def has_vertex(self, v):
        if v in self.structure:
            return True
        else:
            return False

    def has_edge(self, v, w):
        self.validate_vertex(v);
        self.validate_vertex(w);
        if w in self.structure[v]:
            return True
        else:
            return False
    
    def validate_vertex(self, v):
        if (not self.has_vertex(v)):
            raise ValueError("It's not a vertex")
    
    def degree(self, v):
        self.validate_vertex(v);
        return len(self.structure[v]);

    def add_edge(self, v, w):
        if (not self.has_vertex(v)):
            self.add_vertex(v)
        if (not self.has_vertex(w)):
            self.add_vertex(w)
        if (not self.has_edge(v, w)):
            self.E = self.E + 1
        self.structure[v].append(w)

    def add_vertex(self, v):
        if (not self.has_vertex(v)):
            self.structure[v] = []

    def vertices(self):
        return self.structure.keys();

    def adjacent_to(self, v):
        self.validate_vertex(v);
        return self.structure[v];
    
    # No borra los arcos que le referencian
    def delete_vertex(self, v):
        self.validate_vertex(v);
        del self.structure[v]
        '''
        for w in self.vertices():
            try:
                self.structure[w].remove(v)
            except ValueError:
                pass
        '''
    
    # ¡¡Cuidado!! Modifica el grafo. Hacer copia antes
    def has_path_to(self, v, w):  
        try:
            neighs = self.structure[v]
        except KeyError:
            return False
        
        for neigh in neighs:
            if neigh == w:
                return True
        
        self.delete_vertex(v)
        
        for neigh in neighs:
            if self.has_path_to(neigh, w):
                return True
        return False

    def __str__(self):
        s = ""
        for v in self.structure:
            s = s + v + ": "
            for w in self.structure[v]:
                s = s + w + " "
            s = s + "\n"
        return s 
        

n_ciudades = int(sys.stdin.readline())
for ciudad in range(n_ciudades):
    graph = Graph()
    k, c, h = sys.stdin.readline().split()
    
    # Insertamos vértices
    for v in range(1,int(k)+1):
        graph.add_vertex(str(v))
    
    # Obtenemos posición de hoteles
    hoteles = sys.stdin.readline().split()
    # Eliminamos duplicados
    hoteles = list(dict.fromkeys(hoteles))
    
    # Insertamos arcos
    for hotel in range(int(c)):
        v, w = sys.stdin.readline().split()
        graph.add_edge(v,w)
    
    
    cont = 0
    for hotel in hoteles:
        graph_copy = copy.deepcopy(graph)
        if (graph_copy.has_path_to(hotel, hotel)):
            cont = cont + 1
    print(cont)
