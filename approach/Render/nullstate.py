class nullstate(enum.IntEnum):
    null = 1              # the O.G. null, the state itself is unknown
    defined = 2           # object is well-defined
    undeclared = 3        # if(x) when x is not declared
    undefined = 4         # let x; if(x > 1) -- x has no value yet
    undefined_type = 5    # state of something that is explicitly not any null state (allows defined)
    uninitialized = 6     # let x; if(x.a > 1) -- calling member of undefined;
    empty = 7             # state of a node with null nodes and null content
    stalled = 8           # state of a connection which is not yet established -- or due to instability
    virtual = 9           # placeholder null. ex: new components and