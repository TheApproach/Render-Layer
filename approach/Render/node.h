#include "approach/Stream/container.h"

namespace Approach::Render {
 using std::string;

 class Node : public Container {
 public:
	explicit Node(const string &content) {
	 this->content = content;
	 this->SetRenderID();
	};

	Node() {
	 this->content = "";
	 this->SetRenderID();
	};

	void RenderCorpus(std::ostream &stream) override {
	 stream << this->content << '\n';
	 for (auto c: this->nodes) {
		stream << (Node *) c;
	 }
	}

	inline friend Container &operator<<(Container &to, Stream &node) {
	 to.nodes.push_back(&node);
	 return to;
	}

	inline friend Container &operator<<(Container &to, Stream *node) {
	 to.nodes.push_back(node);
	 return to;
	}
 };
}// namespace Approach::Render
