#pragma once



#include "ArgType.h"
#include <QVariant>

class SerialCommandArg
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
