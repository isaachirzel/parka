#include <warbler/c_generator.hpp>
#include <warbler/type.hpp>

#include <stdexcept>

namespace warbler
{
    static String mangle_symbol(const String& symbol)
    {
        String mangled_symbol;

        mangled_symbol.reserve(symbol.size() * 2);

        for (usize i = 0; i < symbol.size(); ++i)
        {
            char c = symbol[i];
            switch (c)
            {
                case '_':
                    mangled_symbol += "__";
                    break;

                case ':':
                    i += 1;
                    mangled_symbol += '_';
                    break;

                default:
                    mangled_symbol += c;
                    break;
            }
        }

        return mangled_symbol;
    }

    String generate_c_type_annotation(const ProgramContext& program, const TypeAnnotationContext& context)
    {
        // TODO: generate pointers
        switch (context.type())
        {
            case SymbolType::Struct:
            {
                const auto& def = program.structs().at(context.index());
                auto symbol = mangle_symbol(def.symbol());
                return symbol;
            }

            case SymbolType::Primitive:
            {
                const auto& def = program.primitives().at(context.index());
                auto symbol = mangle_symbol(def.symbol());
                return symbol;
            }

            default:
                throw new std::invalid_argument("Invalid type given to TypeAnnotationContext");
        }
    }

    String generate_c_struct_member(const ProgramContext& program, const MemberContext& context)
    {
        String output;

        output.reserve(64);

        output += "\n\t";
        output += generate_c_type_annotation(program, context.type);
        output += ' ';
        output += context.name;
        output += ';';

        return output;
    }

    String generate_c_struct(const ProgramContext& program, const StructContext& context)
    {
        auto symbol = mangle_symbol(context.symbol());
        String output;

        output.reserve(512);

        output += "typedef struct ";
        output += symbol;
        output += "\n{";

        for (const auto& member : context.members())
        {
            output += generate_c_struct_member(program, member.second);
        }

        output += "\n} ";
        output += symbol;
        output += ";\n\n";

        return output;
    }

    String generate_c_primitive(const PrimitiveContext& context)
    {
        String output;

        output.reserve(32);

        auto size_text = std::to_string(context.size() * 8);

        switch (context.type())
        {
            case PrimitiveType::UnsignedInteger:
                output += "typedef uint";
                output += size_text;
                output += "_t u";
                output += size_text;
                output += ";\n";
                break;

            case PrimitiveType::SignedInteger:
                output += "typedef int";
                output += size_text;
                output += "_t i";
                output += size_text;
                output += ";\n";
                break;

            default:
                throw new std::runtime_error("generation of this type of primitive is not supported yet");
        }

        return output;
    }

    String generate_c_program(const ProgramContext& program)
    {
        String output = "#include <stdint.h>\n\n";

        for (const auto& primitive : program.primitives())
        {
            output += generate_c_primitive(primitive);
        }

        output += '\n';

        for (const auto& def : program.structs())
        {
            output += generate_c_struct(program, def);
        }

        return output;
    }
}