#include "node.h"
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace Option {
enum {
  id = 0,
  tag,
  attributes,
  classes,
  properties,
  content,
  data,
  context,
  binding,
  component,
  service,
  message
};
};

class XML : public Node {
private:
  ProcUnit ActiveRenderCount = 0;

public:
  ProcUnit RenderID;
  std::string tag, id, content;
  std::map<std::string, std::string> attributes;
  std::vector<std::string> classes;

  // Set Unique Global Render ID based on static member ActiveRenderCount
  inline const void SetRenderID() {
    RenderID = ActiveRenderCount;
    ++ActiveRenderCount;
  }

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

  XML(const std::string &_tag) throw() : tag(_tag) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id)
  throw() : tag(_tag), id(_id) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes)
  throw() : tag(_tag), id(_id), classes(_classes) { XML::SetRenderID(); }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes,
      std::map<std::string, std::string> &_attributes)
  throw() : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
    XML::SetRenderID();
  }

  /* Mixed Typing */

  XML(const std::string &_tag, std::map<ProcUnit, void *> options)
  throw() : tag(_tag) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes, std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id), classes(_classes) {
    XML::SetRenderID();
    SetOptions(options);
  }
  XML(const std::string &_tag, const std::string &_id,
      std::vector<std::string> &_classes,
      std::map<std::string, std::string> &_attributes,
      std::map<ProcUnit, void *> options)
  throw() : tag(_tag), id(_id), classes(_classes), attributes(_attributes) {
    XML::SetRenderID();
    SetOptions(options);
  }

  /* Options only */

  XML(std::map<ProcUnit, void *> options) {
    XML::SetRenderID();
    SetOptions(options);
  }

  /************************
   *       ACTIONS         *
   *                       */

  void SetOptions(std::map<ProcUnit, void *> options) {
    std::map<ProcUnit, void *>::iterator option;
    for (option = options.begin(); option != options.end(); ++option) {
      switch (option->first) {
      case Option::tag:
        tag = *(std::string *)option->second;
        break;
      case Option::id:
        id = *(std::string *)option->second;
        break;
      case Option::classes:
        classes = *(std::vector<std::string> *)(option->second);
        break;
      case Option::attributes:
        attributes = *(std::map<std::string, std::string> *)(option->second);
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
    this->nodes.push_back(static_cast<XML *>(object));
  }

  /** Nests child nodes into the instance by reference */
  inline void operator<<(Node &object) {
    this->nodes.push_back(static_cast<XML *>(&object));
  }

  /************************
   *   RENDERING PIPELINE  *
   *                       */

  inline void prerender(std::ostream &outputstream, const XML &object) {
    this->RenderHead(outputstream);
    this->RenderTail(outputstream);
  }

  inline void render(std::ostream &outputstream) {
    this->RenderHead(outputstream);
    this->RenderCorpus(outputstream);
    this->RenderTail(outputstream);
  }

  /** Outputs this node's tag, id and attributes to the stream. */
  inline void RenderHead(std::ostream &outputstream) {
    // stream opening tag
    outputstream << std::endl << "<"; // open tag
    if (!this->id.empty())
      outputstream << this->tag << " id=\"" << this->id << "\"";
    else
      outputstream << this->tag;

    // stream attributes
    if (!this->attributes.empty()) // if node has attributes
    {
      for (std::map<std::string, std::string>::const_iterator attribute =
               this->attributes.begin();
           attribute != this->attributes.end();
           ++attribute) // for each attribute
      {
        outputstream << " " << attribute->first << "=\"" << attribute->second
                     << "\""; // output attribute to stream
      }
    }
    outputstream << ">"; // close tag

    if (!this->content.empty())
      outputstream << std::endl << this->content << std::endl;
  }

  /** Outputs any child nodes to stream. */
  inline void RenderCorpus(std::ostream &outputstream) {
    if (!this->nodes.empty())
      for (ProcUnit i = 0, L = this->nodes.size(); i < L; ++i) {
        outputstream << *static_cast<XML *>(this->nodes[i]);
      }
  }

  /** Outputs closing tag to stream. */
  inline void RenderTail(std::ostream &outputstream) {
    outputstream << std::endl << "</" << this->tag << ">";
  }

  /************************
   *   STREAM OPERATORS    *
   *                       */

  /** Funky XML>>cout syntax, works in situations without the non-member friend
   */
  inline void operator>>(std::ostream &outputstream) {
    this->render(outputstream);
  }

  /** Supports "normal" syntax cout<<XML; is not really a member function */
  inline friend std::ostream &operator<<(std::ostream &outputstream, XML &obj) {
    obj.render(outputstream);
    return outputstream;
  }
};
