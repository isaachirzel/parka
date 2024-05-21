#include "parka/enum/KeywordType.hpp"

#include "parka/util/FlatMap.hpp"

namespace parka
{
	static FlatMap<String, KeywordType> initKeywords()
	{
		auto keywords = FlatMap<String, KeywordType>(25);
		
		keywords.insert("break", KeywordType::Break);
		keywords.insert("case", KeywordType::Case);
		keywords.insert("continue", KeywordType::Continue);
		keywords.insert("yield", KeywordType::Yield);
		keywords.insert("enum", KeywordType::Enum);
		keywords.insert("import", KeywordType::Import);
		keywords.insert("export", KeywordType::Export);
		keywords.insert("false", KeywordType::False);
		keywords.insert("for", KeywordType::For);
		keywords.insert("in", KeywordType::In);
		keywords.insert("function", KeywordType::Function);
		keywords.insert("operator", KeywordType::Operator);
		keywords.insert("if", KeywordType::If);
		keywords.insert("else", KeywordType::Else);
		keywords.insert("loop", KeywordType::Loop);
		keywords.insert("match", KeywordType::Match);
		keywords.insert("mut", KeywordType::Mut);
		keywords.insert("return", KeywordType::Return);
		keywords.insert("struct", KeywordType::Struct);
		keywords.insert("then", KeywordType::Then);
		keywords.insert("true", KeywordType::True);
		keywords.insert("type", KeywordType::Type);
		keywords.insert("private", KeywordType::Private);
		keywords.insert("public", KeywordType::Public);
		keywords.insert("var", KeywordType::Var);
		keywords.insert("while", KeywordType::While);
		keywords.insert("as", KeywordType::As);

		return keywords;
	}

	const FlatMap<String, KeywordType> keywords = initKeywords();

	KeywordType toKeywordType(const String& text)
	{
		const auto *keywordType = keywords.find(text);

		if (!keywordType)
			return KeywordType::None;

		return *keywordType;
	}

	std::ostream& operator<<(std::ostream& out, const KeywordType& type)
	{
		switch (type)
		{
			case KeywordType::None:
				out << "(none)";
				break;

			case KeywordType::Break:
				out << "break";
				break;

			case KeywordType::Case:
				out << "case";
				break;

			case KeywordType::Continue:
				out << "continue";
				break;

			case KeywordType::Yield:
				out << "yield";
				break;

			case KeywordType::Else:
				out << "else";
				break;

			case KeywordType::Enum:
				out << "enum";
				break;

			case KeywordType::Export:
				out << "export";
				break;

			case KeywordType::False:
				out << "false";
				break;

			case KeywordType::For:
				out << "for";
				break;

			case KeywordType::In:
				out << "in";
				break;

			case KeywordType::Function:
				out << "function";
				break;

			case KeywordType::Operator:
				out << "operator";
				break;

			case KeywordType::If:
				out << "if";
				break;

			case KeywordType::Import:
				out << "import";
				break;

			case KeywordType::Loop:
				out << "loop";
				break;

			case KeywordType::Match:
				out << "match";
				break;

			case KeywordType::Mut:
				out << "mut";
				break;

			case KeywordType::Private:
				out << "private";
				break;

			case KeywordType::Public:
				out << "public";
				break;

			case KeywordType::Return:
				out << "return";
				break;

			case KeywordType::Struct:
				out << "struct";
				break;

			case KeywordType::Then:
				out << "then";
				break;

			case KeywordType::True:
				out << "true";
				break;

			case KeywordType::Type:
				out << "type";
				break;

			case KeywordType::Var:
				out << "var";
				break;

			case KeywordType::While:
				out << "while";
				break;

			case KeywordType::As:
				out << "as";
				break;
		}

		return out;
	}
}
