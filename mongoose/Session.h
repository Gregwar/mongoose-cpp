#ifndef _MONGOOSE_SESSION_H
#define _MONGOOSE_SESSION_H

#include <map>
#include "Mutex.h"
#ifdef ENABLE_SESSION_BOOST_ANY
#  include <boost/any.hpp>
#endif

using namespace std;


/**
 * A session contains the user specific values
 */ 
namespace Mongoose
{
    class Session
    {
#ifdef ENABLE_SESSION_BOOST_ANY
        typedef boost::any TypeValue;
#else
        typedef std::string TypeValue;
#endif
        public:
            Session();

            /**
             * Sets the value of a session variable
             *
             * @param string the name of the variable
             * @param Session::TypeValue the value of the variable
             */
            void setValue(string key, Session::TypeValue value);

            /**
             * Unset a session varaible
             *
             * @param string the variable name
             */
            void unsetValue(string key);

            /**
             * Check if the given variable exists
             *
             * @param string the name of the variable
             */
            bool hasValue(string key);

            /**
             * Try to get the value for the given variable
             *
             * @pram string the name of the variable
             * @param Session::TypeValue the fallback value
             *
             * @return Session::TypeValue the value of the variable if it exists, fallback else
             */
            TypeValue get(string key, Session::TypeValue fallback = Session::TypeValue());

#ifdef ENABLE_SESSION_BOOST_ANY
            /**
             * Try to get the value for the given variable
             *
             * @pram string the name of the variable
             * @param TypeValue the fallback value
             *
             * @return Type the value of the variable if it exists, fallback else
             */
            template<class Type>
            Type get(const string& key, Type fallback = Type())
			{
				TypeValue any = get(key);
				if(any.empty())
					return boost::any_cast<Type>(any);
				else
					return fallback;
			}
#endif

            /**
             * Pings the session, this will update the creation date to now
             * and "keeping it alive"
             */
            void ping();

            /**
             * Returns the session age, in seconds
             *
             * @return int the number of sessions since the last activity of the session
             */
            int getAge();

        protected:
            map<string, TypeValue> values;
            int date;
            Mutex mutex;
    };
}

#endif
