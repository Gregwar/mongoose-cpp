#ifndef _MONGOOSE_REQUEST_HANDLER_H
#define _MONGOOSE_REQUEST_HANDLER_H

#include "Request.h"
#include "Response.h"
#include <string>

namespace Mongoose
{
    class RequestHandlerBase
    {
        public:
            virtual Response *process(Request &request)=0;
    };

    template<typename T, typename R>
    class RequestHandler : public RequestHandlerBase
    {
        public:
            typedef void (T::*fPtr)(Request &request, R &response);

            RequestHandler(T *controller_, fPtr function_)
                : controller(controller_), function(function_)
            {
            }

            /**
             * Called when an exception occur during the rendering
             *
             * @param string the error message
             *
             * @return response a response to send, 404 will occur if NULL
             */
            virtual void serverInternalError(Request& request, Response& response, string message)
            {
                response.setCode(HTTP_SERVER_ERROR);
                std::cerr << "Request: " << request.getUrl() << " Method: " << request.getMethod() << std::endl;
                std::cerr << "[500] Server internal error: " << message;
            }

            Response *process(Request &request)
            {
                R *response = new R;

                try {
                    controller->preProcess(request, *response);
                    (controller->*function)(request, *response);
                } catch (string exception) {
                    serverInternalError(request, *response, exception);
                } catch (const std::exception& exception) {
                    serverInternalError(request, *response, exception.what());
                } catch (...) {
                    serverInternalError(request, *response, "Unknown error");
                }

                return response;
            }

        protected:
            T *controller;
            fPtr function;
    };
}

#endif
