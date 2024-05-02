#include "stream.h"
#include <ostream>
#include <vector>
#include <algorithm>

// The container class
class Container : public Stream<std::ostream> {
public:
  std::vector<Container *> nodes;
  std::vector<std::string> _node_labels;
  std::vector<int> _labeled_nodes;

  virtual void render(std::ostream &stream) {
    this->RenderHead(stream);
    this->RenderCorpus(stream);
    this->RenderTail(stream);
  }

  virtual void prerender(std::ostream &stream) {
    this->RenderHead(stream);
    this->RenderTail(stream);
  }

  virtual void RenderHead(std::ostream &stream) {}

  virtual void RenderCorpus(std::ostream &stream) {}

  virtual void RenderTail(std::ostream &stream) {}

  Container *offsetGet(std::string label) {
    auto index = getNodeLabelIndex(label);
    return getLabeledNode(index);
  }

  void offsetSet(std::string label, Container *obj) {
    auto offset = getNodeLabelIndex(label);

    if (offset == -1) {
      _labeled_nodes[nodes.size()] = nodes.size();
      // FIXME: Does'nt work:
      // The static casting fails for some reason
      // The error seems to be that the obj, which is being passed in as a XML
      // is unable to be casted as a Container *
      nodes.push_back(static_cast<Container *>(obj));
    } else {
    }
  }

  Container *getLabeledNode(int label_index) {
    return nodes[_labeled_nodes[label_index]];
  }

  int getNodeLabelIndex(std::string label) {
    auto offset = std::find(_node_labels.begin(), _node_labels.end(), label);
    if (offset != _node_labels.end()) {
      return offset - _node_labels.begin();
    } else {
      return -1;
    }
  }
};
