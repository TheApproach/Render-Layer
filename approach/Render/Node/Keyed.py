from Render import Node

class Keyed(Node):
    segmentation_phrase = ' '
    associative_phrase = '='
    encapsulating_phrase = '"'
    chaining_phrase = ''

    def __init__(self, name=None, content=None):
        Node.__init__(self)
        self._keys[str(name)] = self
        self.name = name
        self.content = content

    @classmethod
    def fromArray(cls, dictionary):
        a = cls()
        if Approach.isArrayAssociative(dictionary):
            for k, v in dictionary.items():
                a[str(k)] = v
        else:
            for v in dictionary:
                a.append(v)
        return a

    def toArray(self):
        a = []
        for node in self.nodes:
            a = array_merge(a, node.toArray())
        if self.name is not None:
            a[str(self.name)] = self.content
        return a

    def RenderHead(self):
        if self.name is None and self.content is None:
            yield ''
        else:
            yield self.segmentation_phrase

    def RenderCorpus(self):
        if self.name is not None:
            yield str(self.name)
            if self.content is not None:
                yield self.associative_phrase + self.encapsulating_phrase + self.content + self.encapsulating_phrase
        yield ''

    def RenderTail(self):
        for node in self.nodes:
            yield self.name is not None: self.chaining_phrase : ''
            yield from node.RenderHead()
            yield from node.RenderCorpus()
            yield from node.RenderTail()