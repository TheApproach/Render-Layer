#include "node.h"

namespace Approach::Render {
 class Outline : public Node {
 private:
	string dot = "•";

 public:
	int depth = 0;

	void RenderHead(std::ostream &stream) override {
	 for (size_t i = 0; i < depth; i++) {
		stream << '\t';
	 }
	 stream << dot << ' ';
	}

	void RenderCorpus(std::ostream &stream) override {
	 stream << this->content << '\n';
	 for (auto c: this->nodes) {
		auto t = (Outline *) c;
		t->depth = this->depth + 1;
		stream << t;
	 }
	}

	explicit Outline(const std::string &content) {
	 this->content = content;
	}
 };
}// namespace Approach::Render
