class Node(ArrayObject):
    _labeled_nodes = []
    _node_labels = []
    nodes = []
    null = None
    _render_count = 0
    _render_id = 0
    prerender = False
	
    def toArray(self):
        return [
            self.getNodeProperties(),
            *self.nodes.getNodeProperties() 
        ]
	
    def __set(self, label, val):
        self.offsetSet(label, val)
	
    def __get(self, label):
        return self.offsetGet(label)
	
    def getNodeProperties(self):
        return [
            *self.getHeadProperties(),
            *self.getCorpusProperties(),
            *self.getTailProperties()
        ]
	
    def getHeadProperties(self):
        return []
	
    def getCorpusProperties(self):
        return [
            'content'	: self.content		# TODO: make enum labels
        ]
	
    def getTailProperties(self):
        return []
	
    def offsetExists(self, label):
        if isinstance(label, int):
            return label in self.nodes
        else:
            return label in self._labeled_nodes and self.nodes[self._labeled_nodes[label]] is not None
	
    def offsetGet(self, label):
        if isinstance(label, int):
            return self.getLabeledNode(label) or None
        else:
            label_index = self.getNodeLabelIndex(label)
            if label_index is not None:
                return self.getLabeledNode(label_index) or None
            else:
                return None
	
    def offsetSet(self, label, value):
        if label is None:
            self.nodes.append(value)
            return
		
        label_index = self.getNodeLabelIndex(label)
		
        if label_index is not None and self.getLabeledNode(label_index) is not None:
            selected = self.getLabeledNode(label_index)
            selected = value
        else:
            self.nodes.append(value)
            node_index = len(self._node_labels)
            self._node_labels.append(label)
            self._labeled_nodes[node_index] = self.nodes[-1]
	
    def getLabeledNode(self, label_index):
        return self._labeled_nodes[label_index] or None
	
    def getNodeLabelIndex(self, label):
        offset = self._node_labels.index(label)
        if offset is not False:
            return offset
        else:
            return None
	
    def offsetUnset(self, label):
        if isinstance(label, int) and label in self.nodes:
            del self.nodes[label]
            return
		
        if label in self.nodes[self._labeled_nodes[label]]:
            del self.nodes[self._labeled_nodes[label]]
	
    def __init__(self, content = None, prerender = False):
        # self.set_render_id()
        self.content = content
        self.prerender = prerender
	
    @staticmethod
    def GetById(root, _render_id):
        if root._render_id == _render_id:
            return root
		
        for child in root.children:
            result = Node.GetById(child, _render_id)
			
            if isinstance(result, Node):
                if result._render_id == _render_id:
                    return result
	
        return None

    def set_render_id(self):
        self._render_id = Node._render_count
        self.prerender = False
        Node._render_count += 1
	
    def __str__(self):
        return self.render()
	
    def render(self):
        output = ''
        for r in self.RenderHead():
            output += r
        for r in self.RenderCorpus():
            output += r
        for r in self.RenderTail():
            output += r
		
        return output
	
    def RenderHead(self):
        yield ''
	
    def RenderCorpus(self):
        if self.content is not None:
            yield self.content 
		
        if self.prerender is False:
            for n in self.nodes:
                for r in n.RenderHead():
                    yield r
                for r in n.RenderCorpus():
                    yield r
                for r in n.RenderTail():
                    yield r
                # n.prerender = True

    def RenderTail(self):
        yield None
		
def copyInto(into, level = 255):
	if level == 255:
		full_copyInto(into)
	elif level == 1:
		shallow_copyInto(into)
	else:
		full_copyInto(into)
	return self

def full_copyInto(into):
	shallow_copyInto(into)
	for i in range(len(self.children)):
		self.children[i].copyInto(into.children[i])

def shallow_copyInto(into):
	into = self.clone 
	self.set_render_id()