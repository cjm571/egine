/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-05-09 *
*************************/
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <mutex>

// Abstract base class for various logging policies
class PhysLoggerPolicyInterface
{
public:
	virtual void OpenOutStream(const std::string& name) = 0;
	virtual void CloseOutStream() = 0;
	virtual void Write(const std::string& msg) = 0;
};

// File logging policy class
class FileLogPolicy : public PhysLoggerPolicyInterface
{
private:
	// Log file output stream pointer
	std::unique_ptr<std::ofstream> m_pOutStream;

// Ctors
public:
	FileLogPolicy();
	~FileLogPolicy();

// Public Methods
public:
	// Opens the output stream and assigns it the given name
	void OpenOutStream(const std::string& name);
	// Closes the output stream
	void CloseOutStream();
	// Writes the given message to the output stream
	void Write(const std::string& msg);
};

template <typename LogPolicy>
class PhysLogger
{
// Ctors
public:
	PhysLogger(const std::string& name);
	~PhysLogger();

// Data Members
private:
	LogPolicy* m_policy;
	std::stringstream m_logStream;
	std::mutex m_writeMutex;
	unsigned int m_lineNum;

// Helper Functions
private:
	// Returns string representation of current time
	std::string GetTime();
	// Returns string representation of current log line number
	std::string GetLineNumber();

	/*** Core printing functionality ***/
	void PrintImpl();
	template<typename First, typename... Rest>
	void PrintImpl(First param1, Rest... Param);

// Public Method
public:
	template <eSeverity severity, typename... Args>
	void print(Args... args);

// Severity enum
public:
	enum eSeverity
	{
		Off		= 0,
		Error	= 1,
		Warning = 2,
		Info	= 3,
		Debug	= 4
	};
};

