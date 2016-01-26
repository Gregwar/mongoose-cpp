#ifndef _MONGOOSE_UTILS_H
#define _MONGOOSE_UTILS_H

namespace Mongoose
{
    class Utils
    {
        public:
            static std::string htmlEntities(std::string data);
            static void sleep(int ms);
    };
}

#endif

