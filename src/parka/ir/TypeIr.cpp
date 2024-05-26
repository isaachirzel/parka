
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/DummyTypeBaseIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/Hash.hpp"
#include "parka/util/Print.hpp"

namespace parka::ir
{
	const TypeIr TypeIr::packageType(DummyTypeBase::packageTypeBase);
	const TypeIr TypeIr::functionType(DummyTypeBase::functionTypeBase);
	const TypeIr TypeIr::typeNameType(DummyTypeBase::typeNameTypeBase);
	const TypeIr TypeIr::integerType(DummyTypeBase::integerTypeBase);
	const TypeIr TypeIr::floatType(DummyTypeBase::floatTypeBase);

	const TypeIr TypeIr::voidType(PrimitiveIr::voidPrimitive);
	const TypeIr TypeIr::u8Type(PrimitiveIr::u8Primitive);
	const TypeIr TypeIr::u16Type(PrimitiveIr::u16Primitive);
	const TypeIr TypeIr::u32Type(PrimitiveIr::u32Primitive);
	const TypeIr TypeIr::u64Type(PrimitiveIr::u64Primitive);
	const TypeIr TypeIr::i8Type(PrimitiveIr::i8Primitive);
	const TypeIr TypeIr::i16Type(PrimitiveIr::i16Primitive);
	const TypeIr TypeIr::i32Type(PrimitiveIr::i32Primitive);
	const TypeIr TypeIr::i64Type(PrimitiveIr::i64Primitive);
	const TypeIr TypeIr::f32Type(PrimitiveIr::f32Primitive);
	const TypeIr TypeIr::f64Type(PrimitiveIr::f64Primitive);
	const TypeIr TypeIr::boolType(PrimitiveIr::boolPrimitive);
	const TypeIr TypeIr::charType(PrimitiveIr::charPrimitive);
	const TypeIr TypeIr::stringType(PrimitiveIr::stringPrimitive);

	TypeIr::TypeIr(const TypeBaseIr& typeBase):
		_typeBase(&typeBase)
	{}

	TypeIr& TypeIr::operator=(TypeIr&& other)
	{
		_typeBase = other._typeBase;

		return *this;
	}

	TypeIr& TypeIr::operator=(const TypeIr& other)
	{

		_typeBase = other._typeBase;

		return *this;
	}

	bool TypeIr::operator==(const TypeIr& other) const
	{
		return _typeBase == other._typeBase;
	}

	bool TypeIr::operator!=(const TypeIr& right) const
	{
		return !(*this == right);
	}
	
	std::ostream& operator<<(std::ostream& out, const TypeIr& type)
	{
		if (type._typeBase)
			out << *type._typeBase;
		else
			out << "(Invalid)";
		
		return out;
	}
}

std::size_t std::hash<parka::ir::TypeIr>::operator()(const parka::ir::TypeIr& type) const
{
	return parka::hashNumber((size_t)type._typeBase);
}
