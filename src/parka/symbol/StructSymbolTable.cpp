namespace parka::validator
{
	// bool StructAst::declare(Declarable& declarable)
	// {
	// 	// TODO: Token snippet
	// 	const auto& name = declarable.name();
	// 	auto isDeclared = _symbols.insert(name, &declarable);

	// 	if (!isDeclared)
	// 	{
	// 		log::error("Member `$` has already been declared in struct $.", name, _identifier);
	// 	}

	// 	return isDeclared;
	// }

	// bool StructAst::declareSelf(PackageAst&)// parent)
	// {
	// 	log::notImplemented(here());
	// 	// _parent = &parent;

	// 	// bool success = _parent->declare(*this);

	// 	// for (auto *member : _members)
	// 	// {
	// 	// 	if (!member->declareSelf(*this))
	// 	// 		success = false;
	// 	// 		// TODO: Previous delcaration
	// 	// }

	// 	// return success;
	// }

	// Resolvable *StructAst::find(const Identifier& identifier)
	// {
	// 	auto *result = _symbols.find(identifier.text());

	// 	if (result != nullptr)
	// 		return *result;

	// 	return nullptr;
	// }

	// Resolution *StructAst::resolve(const QualifiedIdentifier& identifier)
	// {
	// 	return _parent->resolve(identifier);
	// }

	// bool StructAst::validate(const EntityAst& function)
	// {
	// 	bool success = true;

	// 	usize index = 0;

	// 	for (auto& member : _members)
	// 	{
	// 		for (usize j = 0; j < index; ++j)
	// 		{
	// 			const auto& previous = _members[j];

	// 			if (member.name() == previous.name())
	// 			{
	// 			friend std::ostream& operator<<(std::ostream& out, const StructAst& syntax);	success = false;
					
	// 				log::errorprintError(member.name(), "A member with same name is already declared in this struct.");
	// 				log::parseError(previous.name(), "Previous delcaration here.");

	// 				break;
	// 			}
	// 		}

	// 		if (member.validate(function))
	// 			success = false;

	// 		index += 1;
	// 	}

	// 	return success;
	// }

// 	std::ostream& operator<<(std::ostream& out, const StructAst& syntax)
// 	{
// 		out << "struct " << syntax._identifier << " {}";

// 		return out;
// 	}
}
