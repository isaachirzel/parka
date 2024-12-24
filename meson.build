project('parka', 'cpp')

common_sources = [
	'src/parka/ast/FunctionBodyAst.cpp',
	'src/parka/ast/IdentifierAst.cpp',
	'src/parka/ast/ParameterAst.cpp',
	'src/parka/ast/QualifiedIdentifierAst.cpp',
	'src/parka/enum/AssignmentType.cpp',
	'src/parka/enum/BinaryExpressionType.cpp',
	'src/parka/enum/ContextType.cpp',
	'src/parka/enum/ErrorCode.cpp',
	'src/parka/enum/ExpressionType.cpp',
	'src/parka/enum/IntrinsicFunctionType.cpp',
	'src/parka/enum/JumpType.cpp',
	'src/parka/enum/KeywordType.cpp',
	'src/parka/enum/PrimitiveType.cpp',
	'src/parka/enum/StatementType.cpp',
	'src/parka/evaluation/AssignmentOperatorEvaluator.cpp',
	'src/parka/evaluation/BinaryOperatorEvaluator.cpp',
	'src/parka/evaluation/CastEvaluator.cpp',
	'src/parka/evaluation/Evaluator.cpp',
	'src/parka/evaluation/GlobalState.cpp',
	'src/parka/evaluation/LocalState.cpp',
	'src/parka/evaluation/Value.cpp',
	'src/parka/fs/Directory.cpp',
	'src/parka/fs/File.cpp',
	'src/parka/fs/FilePosition.cpp',
	'src/parka/fs/FileSnippet.cpp',
	'src/parka/fs/Path.cpp',
	'src/parka/fs/Project.cpp',
	'src/parka/ir/AssignmentOperatorIr.cpp',
	'src/parka/ir/BinaryOperatorIr.cpp',
	'src/parka/ir/CastIr.cpp',
	'src/parka/ir/FloatLiteralIr.cpp',
	'src/parka/ir/FunctionBodyIr.cpp',
	'src/parka/ir/FunctionIr.cpp',
	'src/parka/ir/IntegerLiteralIr.cpp',
	'src/parka/ir/IntrinsicFunctionEvaluator.cpp',
	'src/parka/ir/InvalidTypeIr.cpp',
	'src/parka/ir/ParameterIr.cpp',
	'src/parka/ir/PrimitiveIr.cpp',
	'src/parka/ir/PrototypeIr.cpp',
	'src/parka/log/Annotation.cpp',
	'src/parka/log/Color.cpp',
	'src/parka/log/Indent.cpp',
	'src/parka/log/Line.cpp',
	'src/parka/log/Link.cpp',
	'src/parka/log/Log.cpp',
	'src/parka/log/Margin.cpp',
	'src/parka/log/Prompt.cpp',
	'src/parka/log/Underline.cpp',
	'src/parka/parser/ParkaParser.cpp',
	'src/parka/parser/Token.cpp',
	'src/parka/util/Arena.cpp',
	'src/parka/util/ArenaStreamBuffer.cpp',
	'src/parka/util/Float.cpp',
	'src/parka/util/Hash.cpp',
	'src/parka/util/Integer.cpp',
	'src/parka/util/PathUtils.cpp',
	'src/parka/util/Print.cpp',
	'src/parka/util/TableUtil.cpp',
	'src/parka/util/Threadpool.cpp',
	'src/parka/util/Timer.cpp',
	'src/parka/validation/AssignmentOperatorKey.cpp',
	'src/parka/validation/BinaryOperatorKey.cpp',
	'src/parka/validation/BlockContext.cpp',
	'src/parka/validation/BoolTypeContext.cpp',
	'src/parka/validation/CharTypeContext.cpp',
	'src/parka/validation/F32TypeContext.cpp',
	'src/parka/validation/F64TypeContext.cpp',
	'src/parka/validation/FloatTypeContext.cpp',
	'src/parka/validation/FunctionContext.cpp',
	'src/parka/validation/FunctionEntry.cpp',
	'src/parka/validation/GlobalContext.cpp',
	'src/parka/validation/I16TypeContext.cpp',
	'src/parka/validation/I32TypeContext.cpp',
	'src/parka/validation/I64TypeContext.cpp',
	'src/parka/validation/I8TypeContext.cpp',
	'src/parka/validation/IntegerTypeContext.cpp',
	'src/parka/validation/PackageContext.cpp',
	'src/parka/validation/PackageEntry.cpp',
	'src/parka/validation/ParameterEntry.cpp',
	'src/parka/validation/Resolvable.cpp',
	'src/parka/validation/TypeKey.cpp',
	'src/parka/validation/U16TypeContext.cpp',
	'src/parka/validation/U32TypeContext.cpp',
	'src/parka/validation/U64TypeContext.cpp',
	'src/parka/validation/U8TypeContext.cpp',
	'src/parka/validation/Validator.cpp',
	'src/parka/validation/VariableEntry.cpp'
]

test_sources = [
]

fs = import('fs')
include_dirs = include_directories('include')

executable('parka', common_sources, include_directories: include_dirs)

foreach source: test_sources
	source_file_name = fs.name(source).replace('.test.cpp', '')
	unit_test_name = source_file_name
	unit_test_exe_name = source_file_name + '.test'
	unit_test_exe = executable(unit_test_exe_name, source, common_sources, include_directories: include_dirs)
	
	test(unit_test_name, unit_test_exe)
endforeach
