#ifndef WARBLER_C_GENERATOR_HPP
#define WARBLER_C_GENERATOR_HPP

#include <warbler/context.hpp>
#include <warbler/util/string.hpp>

namespace warbler
{
    String generate_c_program(const ProgramContext& program);
}

#endif
