from Render import Node

# XML.py
class XML(Node)
    selfContained: bool
    tag: str
    attributes: Attribute
    before: str
    prefix: str
    suffix: str
    after: str

    def __init__(
        self,
        tag: str = None,
        content: str = None,
        attributes: Attribute = Attribute(),
        prerender: bool = False
    ):
        self.selfContained = selfContained
        self.tag = tag
        self.attributes = attributes
        self.before = before
        self.prefix = prefix
        self.suffix = suffix
        self.after = after
        self.set_render_id()

    def RenderHead(self) -> Traversable:
        yield self.before + "<" + self.tag + self.attributes + (
            "" if self.selfContained else ">" + self.prefix
        )

    def RenderCorpus(self) -> Traversable:
        if not self.prerender:
            for n in self.nodes:
                yield from n.RenderHead()
                yield from n.RenderCorpus()
                yield from n.RenderTail()
            self.prerender = True
        yield self.content

    def RenderTail(self) -> Traversable:
        yield (
            "" if self.selfContained else self.suffix + "</" + self.tag + ">"
        ) + self.after

    @staticmethod
    def GetByTag(root: Node, tag: str) -> list:
        store = []
        for child in root.children:
            if child.tag == tag:
                store.append(child)
            for children in child.children:
                store = store + XML.GetByTag(children, tag)
        return store

    @staticmethod
    def GetFirstByTag(root: Node, tag: str) -> Node:
        return XML.GetByTag(root, tag)[0] if len(XML.GetByTag(root, tag)) > 0 else None