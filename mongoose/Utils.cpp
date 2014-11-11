#include <iostream>
#include <sstream>
#include "Utils.h"
#ifndef _MSC_VER
#include <unistd.h>
#endif
#ifdef _MSC_VER
#include <windows.h>
#endif

using namespace std;

namespace Mongoose
{
    string Utils::htmlEntities(string data)
    {
        string buffer;
        buffer.reserve(data.size());

        for(size_t pos = 0; pos != data.size(); ++pos) {
            switch(data[pos]) {
                case '&':  buffer.append("&amp;");       break;
                case '\"': buffer.append("&quot;");      break;
                case '\'': buffer.append("&apos;");      break;
                case '<':  buffer.append("&lt;");        break;
                case '>':  buffer.append("&gt;");        break;
                default:   buffer.append(1, data[pos]); break;
            }
        }

        return buffer;
    }

    void Utils::sleep(int ms)
    {
#ifdef WIN32
	Sleep(ms);
#else
    usleep(1000 * ms);
#endif
    }


	string Utils::urlDecode(const string &SRC) {
		string ret;
		char ch;
		int ii;
		for (int i = 0; i<SRC.length(); i++) {
			if (int(SRC[i]) == 37) {
				sscanf(SRC.substr(i + 1, 2).c_str(), "%x", &ii);
				ch = static_cast<char>(ii);
				ret += ch;
				i = i + 2;
			}
			else if (SRC[i] == '+'){
				ret += ' ';
			}
			else {
				ret += SRC[i];
			}
		}
		return (ret);
	}
}
