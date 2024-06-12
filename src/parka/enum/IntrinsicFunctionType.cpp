#include "parka/enum/IntrinsicFunctionType.hpp"

namespace parka
{
	String symbolFromIntrinsicFunctionType(IntrinsicFunctionType intrinsicFunctionType)
	{
		switch (intrinsicFunctionType)
		{
			case IntrinsicFunctionType::Println:
				return "println";

			case IntrinsicFunctionType::PrintInt:
				return "printInt";
				
			default:
				break;
		}

		return "";
	}
}
