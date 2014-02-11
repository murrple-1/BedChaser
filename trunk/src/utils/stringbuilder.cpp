#include <sstream>
#include <limits>

#include "stringbuilder.h"

NS_START

StringBuilder::StringBuilder() {
}

StringBuilder::StringBuilder(const StringBuilder & sb) {
	std::list<wchar_t>::const_iterator iter;
	for(iter = sb.charList.begin(); iter != sb.charList.end(); iter++) {
		charList.push_back(*iter);
	}
}

StringBuilder::~StringBuilder() {
}

StringBuilder & StringBuilder::append(const char in) {
	wchar_t tmp = (wchar_t) in;
	charList.push_back(tmp);
	return *this;
}

StringBuilder & StringBuilder::append(const wchar_t in) {
	charList.push_back(in);
	return *this;
}

StringBuilder & StringBuilder::append(const std::string & in) {
	for(std::size_t i = 0; i < in.size(); i++) {
		append(in.at(i));
	}
	return *this;
}

StringBuilder & StringBuilder::append(const std::wstring & in) {
	for(std::size_t i = 0; i < in.size(); i++) {
		append(in.at(i));
	}
	return *this;
}

StringBuilder & StringBuilder::append(const int in) {
	std::stringstream ss;
	ss << in;
	append(ss.str());
	return *this;
}

StringBuilder & StringBuilder::append(const long in) {
	std::stringstream ss;
	ss << in;
	append(ss.str());
	return *this;
}

StringBuilder & StringBuilder::append(const double in) {
	std::stringstream ss;
	ss << in;
	append(ss.str());
	return *this;
}

StringBuilder & StringBuilder::append(const Object & in) {
	append(in.toString());
	return *this;
}

StringBuilder & StringBuilder::append(const bool in, const bool alpha) {
	std::stringstream ss;
	if(alpha) {
		ss << std::boolalpha << in;
	} else {
		ss << std::noboolalpha << in;
	}
	append(ss.str());
	return *this;
}

StringBuilder & StringBuilder::append(const StringBuilder & sb) {
	append(sb.toWString());
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const char in) {
	wchar_t tmp = (wchar_t) in;
	std::list<wchar_t>::iterator iter = charList.begin();
	for(int i = 0; i < offset; i++) {
		iter++;
	}
	charList.insert(iter, tmp);
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const wchar_t in) {
	std::list<wchar_t>::iterator iter = charList.begin();
	for(int i = 0; i < offset; i++) {
		iter++;
	}
	charList.insert(iter, in);
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const std::string & in) {
	for(std::size_t i = in.size(); i > 0; i--) {
		insert(offset, in.at(i - 1));
	}
	return *this;
}
StringBuilder & StringBuilder::insert(const int offset, const std::wstring & in) {
	for(std::size_t i = in.size(); i > 0; i--) {
		insert(offset, in.at(i - 1));
	}
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const int in) {
	std::stringstream ss;
	ss << in;
	insert(offset, ss.str());
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const long in) {
	std::stringstream ss;
	ss << in;
	insert(offset, ss.str());
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const double in) {
	std::stringstream ss;
	ss << in;
	insert(offset, ss.str());
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const bool in, const bool alpha) {
	std::stringstream ss;
	if(alpha) {
		ss << std::boolalpha << in;
	} else {
		ss << std::noboolalpha << in;
	}
	insert(offset, ss.str());
	return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const Object & obj) {
    insert(offset, obj.toString());
    return *this;
}

StringBuilder & StringBuilder::insert(const int offset, const StringBuilder & sb) {
    insert(offset, sb.toWString());
    return *this;
}

StringBuilder & StringBuilder::purge(const int begin, const int end) {
    std::list<wchar_t>::iterator beginIter = charList.begin(),
            endIter = charList.begin();
    for(int i = 0; i < begin; i++) {
	beginIter++;
    }
    for(int i = 0; i < end; i++) {
	endIter++;
    }
    charList.erase(beginIter, endIter);
    return *this;
}

StringBuilder & StringBuilder::deleteCharAt(const int pos) {
    std::list<wchar_t>::iterator iter = charList.begin();
    for(int i = 0; i < pos; i++) {
	iter++;
    }
    charList.erase(iter);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const char in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const wchar_t in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const std::string & in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const std::wstring & in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const int in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const long in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const double in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const bool in, const bool alpha) {
    insert(end + 1, in, alpha);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const Object & in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::replace(const int begin, const int end, const StringBuilder & in) {
    insert(end + 1, in);
    purge(begin, end);
    return *this;
}

StringBuilder & StringBuilder::reverse(void) {
	charList.reverse();
	return *this;
}

std::size_t StringBuilder::length(void) const {
    return charList.size();
}

std::wstring StringBuilder::toWString(void) const {
	wchar_t * str = new wchar_t[charList.size()];
	std::list<wchar_t>::const_iterator iter;
	int i = 0;
	for(iter = charList.begin(); iter != charList.end(); iter++) {
		str[i] = *iter;
		++i;
	}
	std::wstring retVal(str, charList.size());
	delete [] str;
	return retVal;
}

std::string StringBuilder::toString(void) const {
	char * str = new char[charList.size()];
	std::list<wchar_t>::const_iterator iter;
	int i = 0;
	for(iter = charList.begin(); iter != charList.end(); iter++) {
		if(*iter > std::numeric_limits<char>::max()) {
			str[i] = '?';
		} else {
			str[i] = *iter;
		}

		++i;
	}
	std::string retVal(str, charList.size());
	delete [] str;
	return retVal;
}

NS_END
