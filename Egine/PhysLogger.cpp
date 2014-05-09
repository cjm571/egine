/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-05-09 *
*************************/

#include "PhysLogger.h"


/********** CTORS **********/
FileLogPolicy::FileLogPolicy()
	: m_pOutStream(new std::ofstream)
{
}

FileLogPolicy::FileLogPolicy()
{
	CloseOutStream();
}


/********** PUBLIC METHODS **********/
void FileLogPolicy::OpenOutStream(const std::string& name)
{
	// Open stream in binary output mode
	m_pOutStream->open(name.c_str, std::ios_base::binary|std::ios_base::out);

	if (!m_pOutStream->is_open())
	{
		// TODO: is a runtime error best here?
		throw std::runtime_error("PHYSLOGGER: Unable to open output stream");
	}
}

void FileLogPolicy::CloseOutStream()
{
	if (m_pOutStream)
	{
		m_pOutStream->close();
	}
}

void FileLogPolicy::Write(const std::string& msg)
{
	// Write message appended by endline
	(*m_pOutStream)<<msg<<std::endl;
}


/********** PRINT FUNCTIONALITY **********/
template<typename LogPolicy>
	template<eSeverity severity, typename... Args>
void PhysLogger<LogPolicy>::Print(Args... args)
{
	write_mutex.lock();
	switch (severity)
	{
		m_writeMutex.lock();
		case eSeverity::Debug:
			m_logStream<<
	}
}