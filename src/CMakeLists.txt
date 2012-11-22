# --------------------------------------------------------------
#  midi_vendor
#
#  expects:
#    MODULE_NAME defined in the CMakeLists for the module
#
#  provides:
#    midi/core.so
# --------------------------------------------------------------

include_directories(vendor bind)

file(GLOB SOURCES bind/dub/*.cpp bind/*.cpp vendor/*.cpp)

if(MODULES_STATIC)
  set(target "${MODULE_NAME}_static")
  add_library(${target} ${SOURCES})
else(MODULES_STATIC)
  set(target "${MODULE_NAME}_core")
  # --------------------------------------------------------------
  #  module_core                                 module/core.so
  # --------------------------------------------------------------
  add_library(${target} MODULE ${SOURCES})
  set_target_properties(${target} PROPERTIES
    OUTPUT_NAME core
    LINK_FLAGS "${PLAT_OBJ_FLAGS} -framework CoreMIDI -framework CoreAudio"
    PREFIX ""
    SUFFIX ".so"
  )
  add_dependencies(${MODULE_NAME} ${target})

  # --------------------------------------------------------------
  #  install
  # --------------------------------------------------------------
  install(TARGETS ${target}
    DESTINATION ${LUBYK_LIB}/lib/${MODULE_NAME}
  )
endif(MODULES_STATIC)


