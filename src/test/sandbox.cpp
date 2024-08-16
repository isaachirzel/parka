#include "parka/fs/File.hpp"

using namespace parka;

int main()
{
	auto file = File::from(
		"source.pk",
		R"==(
			function main()
			{
				var a = 1 as bool;
			}
		)=="
	);
	return 0;
}
