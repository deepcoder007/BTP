from igraph import *

f=open('graph.dat')
g=open('conf.dat')
data = f.readlines()  # buffer the whole data
f.close()
conf = g.readlines()
g.close()

conf = [ map(int,x.strip().split(',')) for x in conf  ]

edges = []

for x in data:
    edges.append( tuple(map(int,x.strip().split(','))) )

# The number of nodes in the graph
n = max([ max(k) for k in edges ])+1

def getColor(k,curr_conf): 
    if k==curr_conf[0]:   # the node with the robot
        return "red"
    elif k in curr_conf:
        return "blue"
    else:
        return "pink"

print edges

for x in range(len(conf)):
    g = Graph()
    g.add_vertices(n)
    g.add_edges(edges)
    g.vs["color"] = [getColor(xx,conf[x]) for xx in range(n)]
    g.vs["label"] = [ i for i in range(n) ]
    print g.vs["color"]
    layout = g.layout("circle")
    plot(g, layout=layout)
    break


