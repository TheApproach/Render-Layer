from Render import Node
from Render import XML

class HTML(XML):
    NoAutoAttributes = ['html','head','link','script','meta','title']

    def __init__(self, tag=None, id=None, classes=None, attributes=Attribute(), content=None, styles=[], prerender=False, selfContained=False):
        self.classes = Node()
        if isinstance(classes, list) or isinstance(classes, str):
            classes = classes if isinstance(classes, list) else classes.split(' ')
            for class in classes:
                self.classes.append(Node(class))
        elif isinstance(classes, Attribute):
            self.classes.append(classes)
        if isinstance(attributes, list):
            self.attributes = Attribute.fromArray(attributes)
        self.set_render_id()

    def RenderTextNode(self):
        if self.selfContained:
            return self.before + self.content + self.after
        return self.before + self.prefix + self.content + self.suffix + self.after
    
    def RenderHead(self):
        yield self.before + '<' + self.tag + (len(self.classes.nodes) > 0 ? ' class="' + self.classes + '"' : '') + self.attributes + self.BuildStyles() + (self.selfContained ? ' />' : '>' + self.prefix)
    
    def buildContent(self):
        for renderObject in self.children:
            self.content += renderObject.render()