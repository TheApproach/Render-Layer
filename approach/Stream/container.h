#include "stream.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace Approach::Render {
 class Container : public Stream {
 private:
	ProcUnit ActiveRenderCount = 0;

 public:
	ProcUnit RenderID{};
	std::vector<Stream *> nodes;

	Container() { SetRenderID(); }

	std::vector<std::string> _node_labels;
	std::vector<size_t> _labeled_nodes;
	std::string content;

	// Set Unique Global Render ID based on static member ActiveRenderCount
	void SetRenderID() {
	 RenderID = ActiveRenderCount;
	 ++ActiveRenderCount;
	};

	Stream *offsetGet(const std::string &label) {
	 auto index = getNodeLabelIndex(label);
	 return getLabeledNode(index);
	}

	void offsetSet(const std::string &label, Stream *obj) {
	 auto offset = getNodeLabelIndex(label);

	 this->nodes.push_back(obj);
	 if (offset == -1) {
		_labeled_nodes.push_back(this->nodes.size() - 1);
		_node_labels.push_back(label);
	 } else {
		_labeled_nodes[offset] = this->nodes.size() - 1;
		_node_labels[offset] = label;
	 }
	}

	Stream *getLabeledNode(int label_index) {
	 return this->nodes[_labeled_nodes[label_index]];
	}

	int getNodeLabelIndex(const std::string &label) {
	 auto offset = std::find(_node_labels.begin(), _node_labels.end(), label);
	 if (offset != _node_labels.end()) {
		return offset - _node_labels.begin();
	 } else {
		return -1;
	 }
	}

	virtual void render(std::ostream &stream) {
	 this->RenderHead(stream);
	 this->RenderCorpus(stream);
	 this->RenderTail(stream);
	}

	virtual void RenderCorpus(std::ostream &stream) {
	 for (auto &node: this->nodes) {
		stream << node;
	 }
	}

	void prerender(std::ostream &stream) {
	 this->RenderHead(stream);
	 this->RenderTail(stream);
	}

	Stream *operator[](const std::string &label) { return offsetGet(label); }

	// enable s[0] = new Stream();
	Stream *operator[](int index) { return nodes[index]; }

	// enable setting s[0] = new Stream();
	Container &operator=(Stream *node) {
	 this->nodes.push_back(node);
	 return *this;
	}

	// add << operator to add a node to the container
	inline Container &operator<<(Stream &node) {
	 this->nodes.push_back(&node);
	 return *this;
	}

	inline friend Container &operator<<(Stream &node, Container &to) {
	 to.nodes.push_back(&node);
	 return to;
	}

	// add << operator to add a node to the container
	inline Container &operator<<(Stream *node) {
	 this->nodes.push_back(node);
	 return *this;
	}

	inline friend Container &operator<<(Stream *node, Container &to) {
	 to.nodes.push_back(node);
	 return to;
	}

	/** Supports "normal" syntax cout<<XML; is not really a member function */
	inline friend Stream &operator<<(Container &to, Container &node) {
	 to.nodes.push_back(&node);
	 return to;
	}

	/* Typecast from XML to Node by calling XML.render() into Node.content */
	inline explicit operator std::string() {
	 std::ostringstream stream;
	 this->prerender(stream);
	 return stream.str();
	}

	// Make typecasts friendly
	inline friend Container &operator<<(Container &to, std::string &node) {
	 to.content += node;
	 return to;
	}

	inline friend Container &operator<<(Container &to, const char *node) {
	 to.content += node;
	 return to;
	}
 };
}// namespace Approach::Render

/*
  Add friend << operator to add a node to the container
*/
inline Approach::Render::Stream &
operator<<(Approach::Render::Container &container,
					 Approach::Render::Stream &node) {
 container.nodes.push_back(&node);
 return node;
}

inline Approach::Render::Stream &
operator<<(Approach::Render::Container &container,
					 Approach::Render::Stream *node) {
 container.nodes.push_back(node);
 return *node;
}
