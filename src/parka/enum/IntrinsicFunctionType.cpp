#include "parka/enum/IntrinsicFunctionType.hpp"

namespace parka
{
	String symbolFromIntrinsicFunctionType(IntrinsicFunctionType intrinsicFunctionType)
	{
		switch (intrinsicFunctionType)
		{
			case IntrinsicFunctionType::Println:
				return "println";
				
			default:
				break;
		}

		return "";
	}
}
