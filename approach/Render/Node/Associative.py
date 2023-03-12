from Render import Node
from Render.Node import Associative

# Associative.py
class Associative:
    def __init__(self):
        self._keys = {}
    def toArray(self):
        return self.nodes
    def add(self, name, content):
        self_ = Associative(name, content)
        self.nodes.append(self_)
        self._keys[str(name)] = self_
        return self_
    def has(self, name):
        return name in self._keys
    def get(self, name):
        return self._keys.get(str(name))
    def set(self, name, content):
        if self.has(name):
            self._keys[str(name)].content = content
        else:
            self.add(name, content)
        return self._keys[str(name)]
    def remove(self, name):
        if self.has(name):
            del self._keys[str(name)]
        return self
    def __contains__(self, offset):
        return self.has(str(offset))
    def __getitem__(self, offset):
        return self.get(str(offset))
    def __setitem__(self, offset, value):
        self.set(str(offset), value)
    def __delitem__(self, offset):
        self.remove(str(offset))