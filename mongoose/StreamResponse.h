#ifndef _MONGOOSE_STREAM_RESPONSE_H
#define _MONGOOSE_STREAM_RESPONSE_H

#include <map>
#include <sstream>
#include <iostream>

#include "Response.h"

/**
 * A stream response to a request
 */
namespace Mongoose
{
    class StreamResponse : public std::ostringstream, public Response
    {
        public:
            /**
             * Gets the response body
             *
             * @return string the response body
             */
            virtual std::string getBody();
    };
}

#endif
