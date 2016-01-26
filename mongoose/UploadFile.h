#ifndef _MONGOOSE_UPLOAD_FILE_H
#define _MONGOOSE_UPLOAD_FILE_H
#include <string>

/**
 * A file uploaded in a request
 */
namespace Mongoose
{
    class UploadFile
    {
        public:
            UploadFile(std::string filename, std::string data);

            std::string getName();
            std::string getData();

            void saveTo(std::string directory);

        protected:
            std::string filename;
            std::string data;
    };
}

#endif // _MONGOOSE_UPLOAD_FILE_H
