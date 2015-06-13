/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2015-04-12 *
*************************/

#include "Logger.h"

/********** CTORS **********/
Logger::Logger()
	: m_mode(Silent)
{
}

Logger::Logger(LogModeFlag _logModeFlag)
	: m_mode(_logModeFlag)
{
	// Record logger starting time
	m_startTime = time(NULL);

	m_log.push_back(vector<pair<time_t, string>>()); // Error
	m_log.push_back(vector<pair<time_t, string>>()); // Warning
	m_log.push_back(vector<pair<time_t, string>>()); // Info
	m_log.push_back(vector<pair<time_t, string>>()); // Debug
	m_log.push_back(vector<pair<time_t, string>>()); // Verbose

	//TODO Open file in file mode
	// Initialize log
	Write(Error, "LOG_START");
	Write(Warning, "LOG_START");
	Write(Info, "LOG_START");
	Write(Debug, "LOG_START");
	Write(Verbose, "LOG_START");
}

Logger::~Logger()
{
	// Record logger ending time
	time_t endtime = time(NULL);

	// Endcap log entries
	Write(Error, "LOG_END");
	Write(Warning, "LOG_END");
	Write(Info, "LOG_END");
	Write(Debug, "LOG_END");
	Write(Verbose, "LOG_END");
	//TODO Close file in file mode
}


/********** PUBLIC METHODS **********/
void Logger::Write(eSeverity sev, string msg)
{
	time_t elapsed = time(NULL) - m_startTime;
	m_log[sev].push_back(make_pair(elapsed, msg));

	if (m_mode != 0)
	{
		int hour = (int)elapsed / 60 / 60;
		int min = (elapsed / 60) % 60;
		int sec = elapsed % 60;

		// Console output
		if (m_mode == StdOut)
		{
			fprintf(stderr, "[%s] %d:%d:%d - %s\n", "TEMP", hour, min, sec, msg.c_str());
		}
		// File output
		if (m_mode == File)
		{
			fprintf(stderr, "%d:%d:%d - %s\n", hour, min, sec, msg.c_str());
		}
	}
}