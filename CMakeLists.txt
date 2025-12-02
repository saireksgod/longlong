cmake_minimum_required(VERSION 3.10)
set(PLUGIN_OUTPUT longlong)
project(${PLUGIN_OUTPUT})

function(add_samp_plugin plugin_name)
  add_library(${plugin_name} MODULE ${ARGN})

  foreach(file IN ITEMS ${ARGN})
    get_filename_component(file_path "${file}" PATH)

    string(REPLACE "${CMAKE_SOURCE_DIR}" "" group_path "${file_path}")

    string(REPLACE "/" "\\" group_path "${group_path}")

    source_group("${group_path}" FILES "${file}")
  endforeach()

  target_compile_features(${plugin_name} PRIVATE cxx_std_17)

  set_target_properties(${plugin_name} PROPERTIES PREFIX "" OUTPUT_NAME "${PLUGIN_OUTPUT}")

  if(MSVC)
    target_compile_definitions(${plugin_name} PRIVATE _CRT_SECURE_NO_WARNINGS HAVE_STDINT_H)

    target_compile_options(${plugin_name} PRIVATE /wd4005 /wd4305 $<$<CONFIG:Debug>:/MTd> $<$<CONFIG:Release>:/MT>)

  elseif(CMAKE_COMPILER_IS_GNUCC)
    target_compile_definitions(${plugin_name} PRIVATE _GLIBCXX_USE_CXX11_ABI=0)

    set_property(TARGET ${plugin_name} PROPERTY POSITION_INDEPENDENT_CODE Off)
    set_property(TARGET ${plugin_name} APPEND_STRING PROPERTY COMPILE_FLAGS "-m32 -O3 -w")
    set_property(TARGET ${plugin_name} APPEND_STRING PROPERTY LINK_FLAGS "-m32 -O3 -static-libgcc -static-libstdc++")
  endif()
endfunction()


add_samp_plugin(${PROJECT_NAME}
    src/longlong.def
    src/main.cpp
	src/Core.h

	src/SDK/amxplugin.cpp
	src/SDK/plugincommon.h
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
