#include <string>
#include <fstream>

#include "JSONElement.h"

namespace jp {
    class JSONParser {
        public:
            JSONParser(std::string& file);


            JSONElement* parseFile();

        protected:

        private:
            std::string fileName;
            std::ofstream* file;

            JSONElement* tempElement;
    };
}