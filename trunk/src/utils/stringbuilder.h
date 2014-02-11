#ifndef STRINGBUILDER_H_
#define STRINGBUILDER_H_

#include <string>
#include <list>

#include "../core/config.h"
#include "../core/object.h"

NS_START

class StringBuilder {
public:
	StringBuilder(); 
	StringBuilder(const StringBuilder &); 
	virtual ~StringBuilder(); 
	StringBuilder & append(const char); 
	StringBuilder & append(const wchar_t); 
	StringBuilder & append(const std::string &); 
	StringBuilder & append(const std::wstring &); 
	StringBuilder & append(const int); 
	StringBuilder & append(const long); 
	StringBuilder & append(const double); 
	StringBuilder & append(const bool, const bool = true); 
	StringBuilder & append(const Object &); 
	StringBuilder & append(const StringBuilder &); 

	StringBuilder & insert(const int, const char); 
	StringBuilder & insert(const int, const wchar_t); 
	StringBuilder & insert(const int, const std::string &); 
	StringBuilder & insert(const int, const std::wstring &); 
	StringBuilder & insert(const int, const int); 
	StringBuilder & insert(const int, const long); 
	StringBuilder & insert(const int, const double); 
	StringBuilder & insert(const int, const bool, const bool = true); 
	StringBuilder & insert(const int, const Object &); 
	StringBuilder & insert(const int, const StringBuilder &); 

	StringBuilder & purge(const int = -1, const int = -1); 
	StringBuilder & deleteCharAt(const int); 

	StringBuilder & replace(const int, const int, const char); 
	StringBuilder & replace(const int, const int, const wchar_t); 
	StringBuilder & replace(const int, const int, const std::string &); 
	StringBuilder & replace(const int, const int, const std::wstring &); 
	StringBuilder & replace(const int, const int, const int);
	StringBuilder & replace(const int, const int, const long);
	StringBuilder & replace(const int, const int, const double);
	StringBuilder & replace(const int, const int, const bool, const bool = true);
	StringBuilder & replace(const int, const int, const Object &);
	StringBuilder & replace(const int, const int, const StringBuilder &);

	StringBuilder & reverse(void); 

	std::size_t length(void) const;
	std::wstring toWString(void) const; 
	std::string toString(void) const; 
private:
	std::list<wchar_t> charList;
};

NS_END

#endif /* STRINGBUILDER_H_ */
