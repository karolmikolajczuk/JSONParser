#include <string>
#include <map>
#include <list>

class JSONElement {
    public:
        JSONElement(std::string& elementname);

        std::string getElementsName() const;
        std::string getAttribute(std::string& attributesname) const;

        JSONElement* getAnotherJSONElement(std::string& elementname) const;

    protected:

    private:
        std::string elementName;
        std::map<std::string, std::string> attributes;
        std::list<JSONElement*> anotherElement;

};