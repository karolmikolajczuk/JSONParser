#include <string>
#include <map>
#include <list>

class JSONElement {
    public:
        JSONElement(std::string& elementname) : elementName{elementname} {

        }

    protected:

    private:
        std::string elementName;
        std::map<std::string, std::string> attributes;
        std::list<JSONElement*> anotherElement;

};