#include <time.h>
#include <iostream>
#include <string>
#include "Session.h"

using namespace std;

namespace Mongoose
{
    Session::Session()
    {
        ping();
    }

    void Session::ping()
    {
        mutex.lock();
        date = time(NULL);
        mutex.unlock();
    }

    void Session::setValue(string key, Session::TypeValue value)
    {
        mutex.lock();
        values[key] = value;
        mutex.unlock();
    }

    void Session::unsetValue(string key)
    {
        mutex.lock();
        values.erase(key);
        mutex.unlock();
    }

    bool Session::hasValue(string key)
    {
        return values.find(key) != values.end();
    }

    Session::TypeValue Session::get(string key, Session::TypeValue fallback)
    {
        mutex.lock();
        if (hasValue(key)) {
            TypeValue value = values[key];
            mutex.unlock();

            return value;
        } else {
            mutex.unlock();
            return fallback;
        }
    }

    int Session::getAge()
    {
        return time(NULL)-date;
    }
}
