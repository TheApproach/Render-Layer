#include "node.h"
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace Approach::Render {
 class XML : public Node {
 public:
	enum class Option : ProcUnit {
	 id = 0,
	 tag,
	 attributes,
	 // classes,
	 // properties,
	 content,
	 // data,
	 // context,
	 // binding,
	 // component,
	 // service,
	 // message
	};

	std::string tag, id;
	std::map<std::string, std::string> attributes;
	std::vector<std::string> classes;

	/************************
				 *   CONSTRUCTORS        *
				 *                       *
				 * Supply NULL to skip an argument
				 * XML(tag [,options])
				 * XML(tag,id [,options])
				 * XML(tag,id,classes [,options])
				 * XML(tag,id,classes,attributes [,options])
				 * XML(tag,id,classes,attributes [,options])
				 *                       *
				 *                       */

	/* Strict Typing */
	explicit XML(const std::string &_tag) noexcept : tag(_tag) { XML::SetRenderID(); }

	XML(const std::string &_tag, const std::string &_id) noexcept : tag(_tag), id(_id) { XML::SetRenderID(); }

	XML(const std::string &_tag, const std::string &_id,
			std::vector<std::string> &_classes) noexcept : tag(_tag), id(_id), classes(_classes) { XML::SetRenderID(); }

	XML(const std::string &_tag, const std::string &_id,
			std::vector<std::string> &_classes,
			std::map<std::string, std::string> &_attributes) noexcept : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
	 XML::SetRenderID();
	}

	explicit XML(std::string &_tag) noexcept : tag(_tag) { XML::SetRenderID(); }

	XML(std::string &_tag, std::string &_id) noexcept : tag(_tag), id(_id) { XML::SetRenderID(); }

	XML(std::string &_tag, std::string &_id, std::vector<std::string> &_classes) noexcept : tag(_tag), id(_id), classes(_classes) { XML::SetRenderID(); }

	XML(std::string &_tag, std::string &_id, std::vector<std::string> &_classes,
			std::map<std::string, std::string> &_attributes) noexcept : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
	 XML::SetRenderID();
	}

	/* Mixed Typing */

	XML() { XML::SetRenderID(); }

	XML(std::string _tag, std::map<ProcUnit, void *> options) noexcept : tag(std::move(_tag)) {
	 XML::SetRenderID();
	 SetOptions(options);
	}

	XML(const std::string &_tag, const std::string &_id,
			std::map<ProcUnit, void *> options) noexcept : tag(_tag), id(_id) {
	 XML::SetRenderID();
	 SetOptions(options);
	}

	XML(const std::string &_tag, const std::string &_id,
			std::vector<std::string> &_classes, std::map<ProcUnit, void *> options) noexcept : tag(_tag), id(_id), classes(_classes) {
	 XML::SetRenderID();
	 SetOptions(options);
	}

	XML(const std::string &_tag, const std::string &_id,
			std::vector<std::string> &_classes,
			std::map<std::string, std::string> &_attributes,
			std::map<ProcUnit, void *> options) noexcept : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
	 XML::SetRenderID();
	 SetOptions(options);
	}

	/* Options only */

	explicit XML(std::map<ProcUnit, void *> options) {
	 XML::SetRenderID();
	 SetOptions(options);
	}

	/************************
				 *       ACTIONS         *
				 *                       */

	void SetOptions(std::map<ProcUnit, void *> options) {
	 std::map<ProcUnit, void *>::iterator option;
	 for (option = options.begin(); option != options.end(); ++option) {
		switch ((XML::Option) option->first) {
		 case Option::tag:
			tag = *(std::string *) option->second;
			break;
		 case Option::id:
			id = *(std::string *) option->second;
			break;
			// case Option::classes:
			//   classes = *(std::vector<std::string> *)(option->second);
			//   break;
		 case Option::attributes:
			attributes = *(std::map<std::string, std::string> *) (option->second);
			break;
		 default: /* generic option call; */
			break;
		}
	 }
	}

	/************************
				 *   STREAM TO CLASS     *
				 *                       */

	/** Nests child nodes into the instance by pointer */
	inline void operator<<(Node *object) {
	 this->nodes.push_back((XML *) (object));
	}

	/** Nests child nodes into the instance by reference */
	inline void operator<<(Node &object) {
	 this->nodes.push_back((XML *) (&object));
	}

	/************************
				 *   RENDERING PIPELINE  *
				 *                       */

	void prerender(std::ostream &stream, const XML &object) {
	 this->RenderHead(stream);
	 this->RenderTail(stream);
	}

	/** Outputs this node's tag, id and attributes to the stream. */
	void RenderHead(std::ostream &stream) override {
	 // stream opening tag
	 stream << std::endl
					<< "<";// open tag
	 if (!this->id.empty())
		stream << this->tag << " id=\"" << this->id << "\"";
	 else {
		stream << this->tag;
	 }

	 // stream attributes
	 if (!this->attributes.empty())// if node has attributes
	 {
		for (auto & attribute : this->attributes)// for each attribute
		{
		 stream << " " << attribute.first << "=\"" << attribute.second
						<< "\"";// output attribute to stream
		}
	 }
	 stream << ">";// close tag

	 if (!this->content.empty())
		stream << std::endl
					 << this->content << std::endl;
	}

	/** Outputs any child nodes to stream. */
	void RenderCorpus(std::ostream &stream) override {
	 if (!this->nodes.empty())
		for (auto &node: this->nodes) {
		 stream << *(XML *) node;
		}
	}

	/** Outputs closing tag to stream. */
	void RenderTail(std::ostream &stream) override {
	 stream << std::endl
					<< "</" << this->tag << ">";
	}
 };
}// namespace Approach::Render
