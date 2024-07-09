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

	void render(std::ostream &stream) override {
	 this->RenderHead(stream);
	 this->RenderCorpus(stream);
	 this->RenderTail(stream);
	}

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

	friend std::ostream &operator<<(std::ostream &stream, Node &obj) {
	 obj.render(stream);
	 return stream;
	}

	friend std::ostream &operator<<(std::ostream &stream, Node *obj) {
	 obj->render(stream);
	 return stream;
	}
 };
}// namespace Approach::Render
