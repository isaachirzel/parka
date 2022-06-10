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

    String generate_c_primitive_annotation(const PrimitiveContext& primitive)
    {
        switch (primitive.type())
        {
            case PrimitiveType::SignedInteger:
                switch (primitive.size())
                {
                    case 1:
                        return "int8_t";
                    case 2:
                        return "int16_t";
                    case 4:
                        return "int32_t";
                    case 8:
                        return "int64_t";
                    default:
                        break;
                }
                throw std::runtime_error("Invalid size for integer literal: "
                    + std::to_string(primitive.size()));

            case PrimitiveType::UnsignedInteger:
                switch (primitive.size())
                {
                    case 1:
                        return "uint8_t";
                    case 2:
                        return "uint16_t";
                    case 4:
                        return "uint32_t";
                    case 8:
                        return "uint64_t";
                    default:
                        break;
                }
                throw std::runtime_error("Invalid size for usigned integer literal: "
                    + std::to_string(primitive.size()));

            case PrimitiveType::FloatingPoint:
                switch (primitive.size())
                {
                    case 4:
                        return "float";
                    case 8:
                        return "double";
                    default:
                        break;
                }
                throw std::runtime_error("Invalid size for float literal: "
                    + std::to_string(primitive.size()));

            case PrimitiveType::Boolean:
                return "bool";

            case PrimitiveType::Character:
                return "char";

            default:
                break;
        }

        throw std::runtime_error("Primitive annotation generation is not implemented for this type");
    }

    String generate_c_type_annotation(const TypeAnnotationContext& type_annotation, const ProgramContext& program)
    {
        switch (type_annotation.type())
        {
            case AnnotationType::Primitive:
            {
                assert(type_annotation.index() < primitive_count);

                const auto& primitive = primitives[type_annotation.index()];

                return generate_c_primitive_annotation(primitive);
            }

            case AnnotationType::Struct:
            {
                const auto& strct = program.structs()[type_annotation.index()];
                auto symbol = mangle_symbol(strct.symbol());

                return symbol;
            }

            default:
                break;
        }

        throw std::invalid_argument("Invalid type given to TypeAnnotationContext");
    }

    String generate_c_struct_member(const ProgramContext& program, const MemberContext& context)
    {
        String output;

        output.reserve(64);

        output += "\n\t";
        output += generate_c_type_annotation(context.type(), program);
        output += ' ';
        output += context.name();
        output += ';';

        return output;
    }

    String generate_c_struct_declaration(const StructContext& context)
    {
        String output;

        output.reserve(32);

        output += "struct ";
        output += mangle_symbol(context.symbol());

        return output;
    }

    String generate_c_struct(const StructContext& context, const ProgramContext& program)
    {
        
        String output;

        output.reserve(512);

        output += generate_c_struct_declaration(context);
        output += "\n{";

        for (const auto& member : context.members())
        {
            output += generate_c_struct_member(program, member.second);
        }

        output += "\n};\n\n";

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
        output += mangle_symbol(name);
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
            case ConstantType::SignedInteger:
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
        String output = "#include <stdint.h>\n#include <stdbool.h>\n\n";

        output += "// Type forward-declarations\n";
        for (const auto& def : program.structs())
        {
            output += generate_c_struct_declaration(def);
            output += ";\n";
        }

        output += '\n';
        
        output += "// Type definitions\n";

        for (const auto& def : program.structs())
        {
            output += generate_c_struct(def, program);
        }


        output += "// Function forward-declarations\n";
        // generate forward declarations
        for (const auto& function : program.functions())
        {
            output += generate_c_function_signature(function.name(), function.signature(), program);
            output += ";\n";
        }

        output += '\n';
        output += "// Function definitions\n";

        for (const auto& function : program.functions())
        {
            output += generate_c_function(function, program);
        }

        return output;
    }
}