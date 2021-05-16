#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Core/BasicTypes.hpp"

class Log {
public:

	static const std::string emptyMessage;
	static std::ofstream logFile;

	Log() = default;
	~Log() = default;

	static void init();
	static void terminate();

	static void log(const std::string& str);

	static void trace(const std::string file, u32 line, const std::string function, const std::string message =
			emptyMessage);

	static void echo(const std::string& message);

	template<class T>
	static void var(const std::string& varname, T var){
		// std::cout << "VAR > " << varname << " : " << var << std::endl;
		std::string varStr;
		if constexpr (std::is_same<T, std::string>::value){
			varStr = var;
		} else {
			varStr = std::to_string(var);
		}

		log("VAR > " + varname + " : " + varStr);
	};

	template<class T>
	static void val(const T &var){
		// std::cout << "VAL > " << var << std::endl;
		log("VAL > " + std::to_string(var));
	};

	static void error(const std::string& message);

	static void brline();
};

#ifdef DE_ENABLE_LOGS
  #define TRACE() Log::trace(__FILE__, __LINE__, __PRETTY_FUNCTION__);
  #define TO_STR(s) #s
  #define ECHO(x) Log::echo(x);
  #define VAR(T,x) Log::var<T>(#x, x);
  #define VAL(T,x) Log::val<T>(x);
  #define ERROR(x) Log::error(x);
  #define BRLINE() Log::brline();
#else
#define TRACE()
#define TO_STR(s)
#define ECHO(x)
#define VAR(T,x)
#define VAL(T,x)
#define ERROR(x)
#define BRLINE()
#endif
