#include "parka/ir/Type.hpp"
#include "parka/ir/DummyTypeBase.hpp"
#include "parka/ir/Primitive.hpp"

namespace parka::ir
{
	const Type Type::packageType(DummyTypeBase::packageTypeBase);
	const Type Type::functionType(DummyTypeBase::functionTypeBase);
	const Type Type::typeNameType(DummyTypeBase::typeNameTypeBase);

	const Type Type::voidType(Primitive::voidPrimitive);
	const Type Type::u8Type(Primitive::u8Primitive);
	const Type Type::u16Type(Primitive::u16Primitive);
	const Type Type::u32Type(Primitive::u32Primitive);
	const Type Type::u64Type(Primitive::u64Primitive);
	const Type Type::i8Type(Primitive::i8Primitive);
	const Type Type::i16Type(Primitive::i16Primitive);
	const Type Type::i32Type(Primitive::i32Primitive);
	const Type Type::i64Type(Primitive::i64Primitive);
	const Type Type::f32Type(Primitive::f32Primitive);
	const Type Type::f64Type(Primitive::f64Primitive);
	const Type Type::boolType(Primitive::boolPrimitive);
	const Type Type::charType(Primitive::charPrimitive);
	const Type Type::stringType(Primitive::stringPrimitive);

	Type::Type(const TypeBase& base):
		_typeBase(&base)
	{}

	Type::Type(Type&& other):
		_typeBase(other._typeBase)
	{
		other._typeBase = nullptr;
	}

	Type::Type(const Type& other):
		_typeBase(other._typeBase)
	{}

	Type::~Type()
	{
		_typeBase = nullptr;
	}

	Type& Type::operator=(Type&& other)
	{
		_typeBase = other._typeBase;

		return *this;
	}

	Type& Type::operator=(const Type& other)
	{
		_typeBase = other._typeBase;

		return *this;
	}

	bool operator==(const Type& left, const Type& right)
	{
		return left._typeBase == right._typeBase;
	}

	bool operator!=(const Type& left, const Type& right)
	{
		return !(left == right);
	}
	
	std::ostream& operator<<(std::ostream& out, const Type& type)
	{
		out << *type._typeBase;

		return out;
	}
}
