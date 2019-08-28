#pragma once

#include "qtserialcommands_global.h"

#include "ArgType.h"
#include <QVariant>

class QTSERIALCOMMANDS_EXPORT SerialCommandArg
{
public:
	SerialCommandArg(QVariant arg, ArgType type);
	~SerialCommandArg();

	inline bool operator==(SerialCommandArg const & serialCommandArg) const;
	inline bool operator!=(SerialCommandArg const & serialCommandArg) const;

	const QVariant & getArg() const { return m_arg; }
	const ArgType & getType() const { return m_type; }

private:
	const QVariant m_arg;
	const ArgType m_type;
};