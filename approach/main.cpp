#include "xml.h"
using std::cout;

int main() {
 Approach::Render::XML div("div");

 div.id = "cool";
 div.classes = {"cool", "nice"};
 div.attributes = {{"style", "color: red;"}};
 div.content = "Hello, World!";

 cout << div << '\n';
}