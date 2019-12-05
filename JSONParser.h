#include <string>
#include <fstream>

#include "JSONElement.h"

namespace jp {
    enum class JSONError {
        SYNTAX_ERROR,
        NO_DATA,
        NO_FILE,
        DUPLICATE
    };

    class JSONParser {
        public:
            JSONParser(std::string& file);

            JSONElement* parseFile();

        protected:
            JSONError openFile();

            JSONError checkSyntax();

            JSONError parseData();

        private:
            std::string fileName;
            std::ofstream* file;

            JSONElement* tempElement;
    };
}