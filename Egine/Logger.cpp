/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2015-04-12 *
*************************/

#include "Logger.h"

/********** CTORS **********/
Logger::Logger(eLogMode _mode)
	: m_mode(_mode)
{
	// Record logger starting time
	m_startTime = time(NULL);

	// Initialize log
	m_log[Error].push_back(make_pair(m_startTime, string("LOG START")));
	m_log[Warning].push_back(make_pair(m_startTime, string("LOG START")));
	m_log[Info].push_back(make_pair(m_startTime, string("LOG START")));
	m_log[Debug].push_back(make_pair(m_startTime, string("LOG START")));
	m_log[Verbose].push_back(make_pair(m_startTime, string("LOG START")));
}

Logger::~Logger()
{
	// Record logger ending time
	time_t endtime = time(NULL);

	// Endcap log entries
	m_log[Error].push_back(make_pair(endtime, string("LOG END")));
	m_log[Warning].push_back(make_pair(endtime, string("LOG END")));
	m_log[Info].push_back(make_pair(endtime, string("LOG END")));
	m_log[Debug].push_back(make_pair(endtime, string("LOG END")));
	m_log[Verbose].push_back(make_pair(endtime, string("LOG END")));
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
			printf("%d:%d:%d - %s", hour, min, sec, msg);
		}
		// File output
		if (m_mode == File)
		{
			fprintf(stderr, "%d:%d:%d - %s", hour, min, sec, msg);
		}
	}
}