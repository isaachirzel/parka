
#include "parka/ir/TypeIr.hpp"
#include "parka/ir/BoolPrimitiveIr.hpp"
#include "parka/ir/CharPrimitiveIr.hpp"
#include "parka/ir/DummyTypeBaseIr.hpp"
#include "parka/ir/FloatPrimitiveIr.hpp"
#include "parka/ir/IntegerPrimitiveIr.hpp"
#include "parka/ir/StringPrimitiveIr.hpp"
#include "parka/ir/VoidPrimitiveIr.hpp"
#include "parka/util/Hash.hpp"

namespace parka::ir
{
	Set<TypeIr> TypeIr::_typeIrs(256, 1'000'000);

	const TypeIr& TypeIr::packageType = _typeIrs.insert(TypeIr(DummyTypeBase::packageTypeBase));
	const TypeIr& TypeIr::functionType = _typeIrs.insert(TypeIr(DummyTypeBase::functionTypeBase));
	const TypeIr& TypeIr::typeNameType = _typeIrs.insert(TypeIr(DummyTypeBase::typeNameTypeBase));
	const TypeIr& TypeIr::integerType = _typeIrs.insert(TypeIr(DummyTypeBase::integerTypeBase));
	const TypeIr& TypeIr::floatType = _typeIrs.insert(TypeIr(DummyTypeBase::floatTypeBase));
	const TypeIr& TypeIr::voidType = _typeIrs.insert(TypeIr(VoidPrimitiveIr::voidPrimitive));
	const TypeIr& TypeIr::u8Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::u8Primitive));
	const TypeIr& TypeIr::u16Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::u16Primitive));
	const TypeIr& TypeIr::u32Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::u32Primitive));
	const TypeIr& TypeIr::u64Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::u64Primitive));
	const TypeIr& TypeIr::i8Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::i8Primitive));
	const TypeIr& TypeIr::i16Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::i16Primitive));
	const TypeIr& TypeIr::i32Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::i32Primitive));
	const TypeIr& TypeIr::i64Type = _typeIrs.insert(TypeIr(IntegerPrimitiveIr::i64Primitive));
	const TypeIr& TypeIr::f32Type = _typeIrs.insert(TypeIr(FloatPrimitiveIr::f32Primitive));
	const TypeIr& TypeIr::f64Type = _typeIrs.insert(TypeIr(FloatPrimitiveIr::f64Primitive));
	const TypeIr& TypeIr::boolType = _typeIrs.insert(TypeIr(BoolPrimitiveIr::boolPrimitive));
	const TypeIr& TypeIr::charType = _typeIrs.insert(TypeIr(CharPrimitiveIr::charPrimitive));
	const TypeIr& TypeIr::stringType = _typeIrs.insert(TypeIr(StringPrimitiveIr::stringPrimitive));

	TypeIr::TypeIr(const TypeBaseIr& typeBase):
		_typeBase(typeBase)
	{}

	const TypeIr& TypeIr::of(const TypeBaseIr& typeBase)
	{
		return _typeIrs.insert(TypeIr(typeBase));
	}

	bool TypeIr::operator==(const TypeIr& other) const
	{
		return &_typeBase == &other._typeBase;
	}

	bool TypeIr::operator!=(const TypeIr& right) const
	{
		return !(*this == right);
	}
	
	std::ostream& operator<<(std::ostream& out, const TypeIr& type)
	{
		out << type._typeBase;
		
		return out;
	}
}

std::size_t std::hash<parka::ir::TypeIr>::operator()(const parka::ir::TypeIr& type) const
{
	return parka::hashNumber((size_t)&type._typeBase);
}
