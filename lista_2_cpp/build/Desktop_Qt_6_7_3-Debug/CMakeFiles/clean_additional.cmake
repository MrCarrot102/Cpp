# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lista_2_cpp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lista_2_cpp_autogen.dir/ParseCache.txt"
  "lista_2_cpp_autogen"
  )
endif()
