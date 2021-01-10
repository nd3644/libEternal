#ifndef DBGLOG_H
#define DBGLOG_H

#include <fstream>
#include <string>

namespace Eternal {
    class DbgLog {
        public:
            ~DbgLog();

            void Write(std::string str);

            void operator<<(std::string str);

            static DbgLog *GetInstance();
        private:
            DbgLog();
            static DbgLog *myInstance;
//            std::ofstream myFile;
    };
}

#endif

