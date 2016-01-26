#ifndef _MONGOOSE_SESSIONS_H
#define _MONGOOSE_SESSIONS_H

#include "Request.h"
#include "Session.h"
#include "Mutex.h"

/**
 * A session contains the user specific values
 */
namespace Mongoose
{
    class Sessions
    {
        public:
            Sessions(std::string key = "sessid");
            virtual ~Sessions();

            /**
             * Gets the session ID of a certain request,
             * this will look in the cookies and create it if
             * necessary
             *
             * @param Request the request
             * @param Response the response in which the cookie should be write
             *
             * @return string the session ID for this request
             */
            std::string getId(Request &request, Response &response);

            /**
             * Gets the session for a certain request
             *
             * @param Request the request
             * @param Response the response inwhich the cookie should be write
             *
             * @return Session the session corresponding
             */
            Session &get(Request &request, Response &response);

            /**
             * Remove all the sessions older than age
             *
             * @param int the age of the too old sessions in second
             */
            void garbageCollect(int oldAge = 3600);

        protected:
            std::map<std::string, Session*> sessions;
            std::string key;
            Mutex mutex;
    };
}

#endif
