#include <string>
#include <map>


class JSONElement {
    public:
        JSONElement(std::string& elementname) : elementName{elementname} {

        }

    protected:

    private:
        std::string elementName;
        std::map<std::string, std::string> attributes;

};