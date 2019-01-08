#include "SerialCommandArg.h"



SerialCommandArg::SerialCommandArg(QVariant arg, ArgType type) :
	m_arg{ arg },
	m_type{ type }
{
}


SerialCommandArg::~SerialCommandArg()
{
}

bool SerialCommandArg::operator==(SerialCommandArg const& serialCommandArg) const
{
	return serialCommandArg.getArg() == m_arg && serialCommandArg.getType() == m_type;
}

bool SerialCommandArg::operator!=(SerialCommandArg const& serialCommandArg) const
{
	return serialCommandArg.getArg() != m_arg || serialCommandArg.getType() != m_type;
}
