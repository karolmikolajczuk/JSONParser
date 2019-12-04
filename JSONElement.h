#include <string>

class JSONElement {
    public:
        JSONElement(std::string& elementname) : elementName{elementname} {

        }


    protected:

    private:
        std::string elementName;

};