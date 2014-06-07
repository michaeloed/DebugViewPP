// (C) Copyright Gert-Jan de Vos and Jan Wilmans 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)

// Repository at: https://github.com/djeedjay/DebugViewPP/

#pragma once

#include "stdafx.h"
#include "DebugView++Lib/LogSource.h"
#include "DebugView++Lib/LineBuffer.h"
#include "DebugView++Lib/ProcessInfo.h"

namespace fusion {
namespace debugviewpp {

LogSource::LogSource(SourceType::type sourceType, ILineBuffer& linebuffer) : 
	m_sourceType(sourceType), m_linebuffer(linebuffer)
{

}

LogSource::~LogSource()
{
}

void LogSource::SetLineBuffer(ILineBuffer& linebuffer)
{
	m_linebuffer = linebuffer;
}

void LogSource::SetAutoNewLine(bool value)
{
	m_autoNewLine = value;
}

bool LogSource::GetAutoNewLine() const
{
	return m_autoNewLine;
}

std::wstring LogSource::GetDescription() const
{
	return m_description;
}

void LogSource::SetDescription(const std::wstring& description)
{
	m_description = description;
}

SourceType::type LogSource::GetSourceType() const
{
	return m_sourceType;
}

void LogSource::Add(double time, FILETIME systemTime, HANDLE handle, const char* message)
{
	m_linebuffer.Add(time, systemTime, handle, message, this);
}

void LogSource::Add(const char* message, HANDLE handle)
{
	m_linebuffer.Add(m_timer.Get(), GetSystemTimeAsFileTime(), handle, message, this);
}

void LogSource::Add(const std::string& message, HANDLE handle)
{
	Add(message.c_str(), handle);
}

std::string LogSource::GetProcessName(HANDLE handle) const
{
	return Str(ProcessInfo::GetProcessName(handle)).str();
}

} // namespace debugviewpp 
} // namespace fusion
