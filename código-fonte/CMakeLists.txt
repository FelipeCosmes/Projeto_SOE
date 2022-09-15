cmake_minimum_required(VERSION 2.8.12)


PROJECT(FelipeGomes&VitoriaBandeira)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})
include(../dlibAndModel/dlib/dlib/cmake )

MACRO(executar name)
  ADD_EXECUTABLE(${name} ${name}.cpp)
  TARGET_LINK_LIBRARIES(${name} ${OpenCV_LIBS} dlib::dlib)
ENDMACRO()

executar(projeto_SOE)
