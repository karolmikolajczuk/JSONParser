#include <string>
#include <fstream>


namespace jp {
    class JSONParser {
        public:
            JSONParser(std::string& file);


        protected:

        private:
            std::string fileName;
            std::ofstream* file;

    };
}