#include "node.h"

/*
 * . List
 * 	. Sublist1
 * 	. SubList2
 * 		. Sublist2.1
 * 			. Sublist2.1.1
 * 				. Sublist2.1.1.1
 * 	. Sublist3
 * */
namespace Approach::Render {
 class Outline : public Node {
 private:
	string dot = "•";

 public:
	int depth = 0;

	void RenderHead(std::ostream &stream) {
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

	// not needed, to be fixed
	void render(std::ostream &stream) override {
	 this->RenderHead(stream);
	 this->RenderCorpus(stream);
	 this->RenderTail(stream);
	}

	explicit Outline(const std::string &content) {
	 this->content = content;
	}
 };
}// namespace Approach::Render
