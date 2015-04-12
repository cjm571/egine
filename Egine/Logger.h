/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2015-04-12 *
*************************/
/*
Purpose:
 This class defines the Logger class, which is used to maintain a record of events
 which take place over the course of engine execution. This should aid in troubleshooting
 and debugging efforts in the future.
*/
#pragma once

#include <vector>
#include <string>
#include <time.h>

#include "StdAfx.h"

using namespace std;
class Logger
{
// Ctors
public:
	Logger(eLogMode);
	~Logger();

// Severity enumeration
public:
	enum eSeverity
	{
		Error	= 0,
		Warning	= 1,
		Info	= 2,
		Debug	= 3,
		Verbose	= 4,
		COUNT	= 5
	};
	
// Data Members
private:
	// Log data structure. Holds logs indexed by severity
	// Recorded time is time elapsed since log start
	vector<vector<pair<time_t,string>>> m_log;

	// Output mode. Silent, StdOut, or File
	eLogMode m_mode;

	// System time at log initialization
	time_t m_startTime;

// Public Methods
public:
	// Write a log entry at specified severity level
	void Write(eSeverity, string);

};