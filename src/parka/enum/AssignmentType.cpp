#include "parka/enum/AssignmentType.hpp"
namespace parka
{
	std::ostream& operator<<(std::ostream& out, const AssignmentType& type)
	{
		switch (type)
		{
			case AssignmentType::Assign:
				out << "=";
				break;

			case AssignmentType::MultiplyAssign:
				out << "*=";
				break;
				
			case AssignmentType::DivideAssign:
				out << "/=";
				break;
				
			case AssignmentType::ModulusAssign:
				out << "%=";
				break;
				
			case AssignmentType::AddAssign:
				out << "+=";
				break;
				
			case AssignmentType::SubtractAssign:
				out << "-=";
				break;
				
			case AssignmentType::LeftShiftAssign:
				out << "<<=";
				break;
				
			case AssignmentType::RightShiftAssign:
				out << ">>=";
				break;
				
			case AssignmentType::BitwiseAndAssign:
				out << "&=";
				break;
				
			case AssignmentType::BitwiseOrAssign:
				out << "|=";
				break;
				
			case AssignmentType::BitwiseXorAssign:
				out << "^=";
				break;
				
			default:
				out << "(Invalid " << (int)type << ")";
		}

		return out;
	}
}
