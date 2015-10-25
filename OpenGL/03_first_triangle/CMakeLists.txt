project(03_first_triangle)
cmake_minimum_required(VERSION 2.8)


#################################################
#enable c++11 features
#################################################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


#################################################
#enable threads
#################################################
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
message (STATUS "Enable multithreading.")
else()
    message (STATUS "Cannot enable multithreading.")
endif()

###########################################################
#Enable OpenGL and other libs/frameworks for  OSX platform
###########################################################
IF(APPLE)
   message (STATUS "Using OSX platform.")	

   set(CMAKE_MODULE_PATH /usr/local/lib/cmake )
   set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/local/include")

   #Libs specific for OSX platform
   find_library(carbon_lib Carbon)
   find_library(iokit_lib IOKit)
   find_library(forcefeedback_lib ForceFeedback)
   find_library(cocoa_lib Cocoa)
   find_library(audiounit_lib AudioUnit)
   find_library(coreaudio_lib CoreAudio)
   find_library(corevideo_lib CoreVideo)
   find_library(corefoundation_lib CoreFoundation)

   set(OSX_FRAMEWORKS
       ${carbon_lib}
       ${iokit_lib}
       ${forcefeedback_lib}
       ${cocoa_lib}
       ${audiounit_lib}
       ${coreaudio_lib}
       ${corevideo_lib}
       ${corefoundation_lib}
   )
									
   message (STATUS "OSX FRAMEWORKS => " ${OSX_FRAMEWOKS})

   find_package (glfw REQUIRED)
   set(GLFW_LIBRARY ${glfw})  

   find_package (glew REQUIRED)
   set(GLEW_LIBRARY ${glew})  
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${GLEW_INCLUDE_DIRS}")

   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(GLUT_LIBRARY GLUT )
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
   
   MARK_AS_ADVANCED (COCOA_LIBRARY
                     GLUT_LIBRARY
                     OpenGL_LIBRARY)

   SET(OPENGL_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})

   message(STATUS "OpenGL dirs for OSX: ${OPENGL_LIBS} ")
ELSE(APPLE)
	message ("No configurations for Windows or Linux platforms...")
ENDIF (APPLE)

#################################################
#source files
#################################################
aux_source_directory(. SRC_LIST)

#################################################
#create executables
#################################################
add_executable(${PROJECT_NAME} ${SRC_LIST})

#################################################
#Link libs and executables
#################################################
target_link_libraries( ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${OPENGL_LIBS} ${OSX_FRAMEWORKS} ${GLFW_LIBRARY} ${GLEW_LIBRARY})
