cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
set(OWN_GXX_FLAGS "-Wall -Wextra -fstack-protector-all -std=c++14")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS} -pg -g")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################

# set(engine_sources
# 		src/easy_image.cc
# 		src/engine.cc
# 		src/ini_configuration.cc
# 		src/ini_configuration.h
# 		src/Line2D.cpp
# 		src/Line2D.h
# 		src/Color.cpp
# 		src/Color.h
# 		src/easy_image.h
# 		src/l_parser.cc
# 		src/l_parser.h
# 		src/Point2D.cpp
# 		src/Point2D.h
# 		src/Face.cpp
# 		src/Face.h
# 		src/Figure.cpp
# 		src/Figure.h
# 		src/vector3d.h
# 		src/vector3d.cc
# 		src/LSystem2D.cpp
# 		src/LSystem2D.h
# 		src/Platonic.cpp
# 		src/Platonic.h
# 		src/LSystem3D.cpp
# 		src/LSystem3D.h
# 		src/ZBuffer.cpp
# 		src/ZBuffer.h
# 		src/Utils.cpp
# 		src/Utils.h)

set(engine_sources
		easy_image.cc
		engine.cc
		ini_configuration.cc
		ini_configuration.h
		Line2D.cpp
		Line2D.h
		Color.cpp
		Color.h
		easy_image.h
		l_parser.cc
		l_parser.h
		Point2D.cpp
		Point2D.h
		Face.cpp
		Face.h
		Figure.cpp
		Figure.h
		vector3d.h
		vector3d.cc
		LSystem2D.cpp
		LSystem2D.h
		Platonic.cpp
		Platonic.h
		LSystem3D.cpp
		LSystem3D.h
		ZBuffer.cpp
		ZBuffer.h
		Utils.cpp
		Utils.h)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
