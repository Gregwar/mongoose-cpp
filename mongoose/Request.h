#ifndef _MONGOOSE_REQUEST_H
#define _MONGOOSE_REQUEST_H

#include <iostream>
#include <sstream>
#include <vector>
#ifdef ENABLE_REGEX_URL
#include <regex>
#endif
#include <mongoose.h>
#include "UploadFile.h"
#include "Response.h"

/**
 * Request is a wrapper for the clients requests
 */
namespace Mongoose
{
    class Request
    {
        public:
            Request(struct mg_connection *connection);

            /**
             * Sends a given response to the client
             *
             * @param Response a response for this request
             */
            void writeResponse(Response *response);

            /**
             * Check if the variable given by key is present in GET or POST data
             *
             * @param string the name of the variable
             *
             * @return bool true if the param is present, false else
             */
            bool hasVariable(std::string key);

            /**
             * Get All variable present in GET or POST data
             *
             * @brief getAllVariable
             * @return map<string, string> with all variables
             */
            std::map<std::string, std::string> getAllVariable();

            /**
             * Get the value for a certain variable
             *
             * @param string the name of the variable
             * @param string the fallback value if the variable doesn't exists
             *
             * @return string the value of the variable if it exists, fallback else
             */
            std::string get(std::string key, std::string fallback = "");

            /**
             * Checks if the given cookie exists
             *
             * @param string the name of the cookie
             *
             * @return bool true if the given cookie is set
             */
            bool hasCookie(std::string key);

            /**
             * Try to get the cookie value
             *
             * @param string the name of the cookie
             * @param string the fallback value
             *
             * @retun the value of the cookie if it exists, fallback else
             */
            std::string getCookie(std::string key, std::string fallback = "");


            std::string getHeaderKeyValue(const std::string& header_key);

            /**
             * Handle uploads to the target directory
             *
             * @param string the target directory
             * @param path the posted file path
             */
            void handleUploads();

            std::string getUrl();
            std::string getMethod();
            std::string getData();

#ifdef ENABLE_REGEX_URL
            smatch getMatches();
            bool match(std::string pattern);
#endif
            bool readVariable(const char *data, std::string key, std::string &output);

            /**
             * Files uploaded in this request
             */
            std::vector<UploadFile> uploadFiles;

        protected:
            std::string method;
            std::string url;
            std::string data;
            struct mg_connection *connection;
    };
}

#endif
