
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/DummyTypeBaseIr.hpp"
#include "parka/ir/PrimitiveIr.hpp"
#include "parka/util/Hash.hpp"
#include "parka/util/Print.hpp"

namespace parka::ir
{
	Set<TypeIr> TypeIr::_typeIrs(256, 1'000'000);

	const TypeIr& TypeIr::packageType = _typeIrs.insert(TypeIr(DummyTypeBase::packageTypeBase));
	const TypeIr& TypeIr::functionType = _typeIrs.insert(TypeIr(DummyTypeBase::functionTypeBase));
	const TypeIr& TypeIr::typeNameType = _typeIrs.insert(TypeIr(DummyTypeBase::typeNameTypeBase));
	const TypeIr& TypeIr::integerType = _typeIrs.insert(TypeIr(DummyTypeBase::integerTypeBase));
	const TypeIr& TypeIr::floatType = _typeIrs.insert(TypeIr(DummyTypeBase::floatTypeBase));
	const TypeIr& TypeIr::voidType = _typeIrs.insert(TypeIr(PrimitiveIr::voidPrimitive));
	const TypeIr& TypeIr::u8Type = _typeIrs.insert(TypeIr(PrimitiveIr::u8Primitive));
	const TypeIr& TypeIr::u16Type = _typeIrs.insert(TypeIr(PrimitiveIr::u16Primitive));
	const TypeIr& TypeIr::u32Type = _typeIrs.insert(TypeIr(PrimitiveIr::u32Primitive));
	const TypeIr& TypeIr::u64Type = _typeIrs.insert(TypeIr(PrimitiveIr::u64Primitive));
	const TypeIr& TypeIr::i8Type = _typeIrs.insert(TypeIr(PrimitiveIr::i8Primitive));
	const TypeIr& TypeIr::i16Type = _typeIrs.insert(TypeIr(PrimitiveIr::i16Primitive));
	const TypeIr& TypeIr::i32Type = _typeIrs.insert(TypeIr(PrimitiveIr::i32Primitive));
	const TypeIr& TypeIr::i64Type = _typeIrs.insert(TypeIr(PrimitiveIr::i64Primitive));
	const TypeIr& TypeIr::f32Type = _typeIrs.insert(TypeIr(PrimitiveIr::f32Primitive));
	const TypeIr& TypeIr::f64Type = _typeIrs.insert(TypeIr(PrimitiveIr::f64Primitive));
	const TypeIr& TypeIr::boolType = _typeIrs.insert(TypeIr(PrimitiveIr::boolPrimitive));
	const TypeIr& TypeIr::charType = _typeIrs.insert(TypeIr(PrimitiveIr::charPrimitive));
	const TypeIr& TypeIr::stringType = _typeIrs.insert(TypeIr(PrimitiveIr::stringPrimitive));

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
