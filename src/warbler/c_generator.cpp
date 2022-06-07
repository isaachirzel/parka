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
            case AnnotationType::Struct:
            {
                const auto& def = program.structs().at(context.index());
                auto symbol = mangle_symbol(def.symbol());
                return symbol;
            }

            case AnnotationType::Primitive:
            {
                const auto& def = program.primitives().at(context.index());
                auto symbol = mangle_symbol(def.symbol());
                return symbol;
            }

            default:
                throw std::invalid_argument("Invalid type given to TypeAnnotationContext");
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

    String generate_c_struct(const StructContext& context, const ProgramContext& program)
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
                throw std::runtime_error("generation of this type of primitive is not supported yet");
        }

        return output;
    }

    String generate_c_type_annotation(const TypeAnnotationContext& type_annotation, const ProgramContext& program)
    {
        String output;

        output.reserve(32);

        switch (type_annotation.type())
        {
            case AnnotationType::Primitive:
            {
                const auto& primitive = program.primitives()[type_annotation.index()];

                output += primitive.symbol();
                break;
            }

            case AnnotationType::Struct:
                const auto& strct = program.structs()[type_annotation.index()];

                output += generate_c_struct(strct, program);
                break;
        }

        return output;
    }

    String generate_c_parameter(const ParameterContext& parameter, const ProgramContext& program)
    {
        String output;

        output.reserve(48);

        output += generate_c_type_annotation(parameter.type(), program);
        output += ' ';
        output += parameter.name();

        return output;
    }

    String generate_c_function_signature(const String& name, const FunctionSignatureContext& signature, const ProgramContext& program)
    {
        String output;

        output.reserve(256);

        output += signature.return_type().has_value()
            ? generate_c_type_annotation(signature.return_type().value(), program)
            : "void";

        output += ' ';
        output += name;
        output += '(';

        bool is_first = true;
        for (const auto& parameter : signature.parameters())
        {
            if (is_first)
            {
                output += ", ";
                is_first = false;
            }
            output += generate_c_parameter(parameter, program);
        }

        output += ')';


        return output;
    }

    String generate_c_constant(const ConstantContext& constant)
    {
        String output;

        output.reserve(16);

        switch (constant.type())
        {
            case ConstantType::Integer:
                output += std::to_string(constant.integer());
                break;

            default:
                throw std::runtime_error("Constant generation is not implemented for this type yet");
        }

        return output;
    }

    String generate_c_expression(const ExpressionContext& expression, const ProgramContext& program)
    {
        switch (expression.type())
        {
            case ExpressionType::Constant:
                return generate_c_constant(expression.constant());

            default:
                throw std::runtime_error("Expression generation is not implemented for this type");
        }
    }

    String generate_c_variable(const VariableContext& variable, const ProgramContext& program)
    {
        String output;

        output.reserve(32);

        // TODO: implement getting type from value if auto type;

        output += generate_c_type_annotation(variable.type(), program);
        output += ' ';
        output += variable.name();

        return output;
    }

    String generate_c_statement(const StatementContext& statement, const ProgramContext& program);

    String generate_c_declaration(const DeclarationContext& declaration, const ProgramContext& program)
    {
        String output;

        output.reserve(127);

        output += generate_c_variable(declaration.variable(), program);
        output += " = ";
        output += generate_c_expression(declaration.value(), program);
        output += ";\n";

        return output;
    }

    String generate_c_block_statement(const BlockStatementContext& block, const ProgramContext& program)
    {
        String output;

        output.reserve(1024);

        output += "\n{\n";

        for (const auto& statement : block.statements())
        {
            output += '\t';
            output += generate_c_statement(statement, program);
        }

        output += "}\n\n";

        return output;
    }

    String generate_c_statement(const StatementContext& statement, const ProgramContext& program)
    {
        switch (statement.type())
        {
            case StatementType::Block:
                return generate_c_block_statement(statement.block(), program);

            case StatementType::Declaration:
                return generate_c_declaration(statement.declaration(), program);

            default:
                throw std::runtime_error("Statement generation for this type is not implemented yet");
        }
    }

    String generate_c_function(const FunctionContext& function, const ProgramContext& program)
    {
        String output;

        output.reserve(1024);

        output += generate_c_function_signature(function.name(), function.signature(), program);
        output += generate_c_block_statement(function.body(), program);

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
            output += generate_c_struct(def, program);
        }

        // generate forward declarations
        for (const auto& function : program.functions())
        {
            output += generate_c_function_signature(function.name(), function.signature(), program);
            output += ";\n";
        }

        output += '\n';

        for (const auto& function : program.functions())
        {
            output += generate_c_function(function, program);
        }

        return output;
    }
}