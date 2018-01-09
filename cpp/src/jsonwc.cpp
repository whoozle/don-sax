#include <jsonwc.h>

namespace jsonwc
{
	Parser::Parser(IObjectReceiver *root): _current(root)
	{ }

	void Parser::Feed(const void *data, size_t size)
	{ }

}
