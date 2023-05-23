# CMakeList.txt: проект CMake для Algebra-of-Polynomials; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
create_executable_project (Algebra-of-Polynomials)
add_depend(Algebra-of-Polynomials lib_SyntaxTree "../libs/Functional/lib_SyntaxTree")
add_depend(Algebra-of-Polynomials lib_Polynom "../libs/Functional/lib_Polynom")
add_depend(Algebra-of-Polynomials lib_OpenShuffleTable "../libs/Tables/lib_OpenShuffleTable")
add_depend(Algebra-of-Polynomials lib_ChainMethodTable "../libs/Tables/lib_ChainMethodTable")
add_depend(Algebra-of-Polynomials lib_LinearListTable "../libs/Tables/lib_LinearListTable")
add_depend(Algebra-of-Polynomials lib_SortedArrayTable "../libs/Tables/lib_SortedArrayTable")
add_depend(Algebra-of-Polynomials lib_LinearArrayTable "../libs/Tables/lib_LinearArrayTable")
add_depend(Algebra-of-Polynomials lib_AVLTreeTable "../libs/Tables/lib_AVLTreeTable")
add_depend(Algebra-of-Polynomials lib_Parser "../libs/Functional/lib_Parser")

# Add the target includes for PROJECT 
target_include_directories(Algebra-of-Polynomials PRIVATE ${FORMS_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(Algebra-of-Polynomials Qt6::Widgets)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
