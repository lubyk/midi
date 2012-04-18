# --------------------------------------------------------------
#  midi_vendor
#  
#  expects:
#    MODULE_NAME defined in the CMakeLists for the module
#
#  provides:
#    midi/core.so
# --------------------------------------------------------------
set(target "${MODULE_NAME}_core")

include_directories(vendor)

# --------------------------------------------------------------
#  module_core                                 module/core.so
# --------------------------------------------------------------
file(GLOB CORE_SOURCES bind/dub/*.cpp bind/*.cpp vendor/*.cpp)
add_library(${target} MODULE ${CORE_SOURCES})
set_target_properties(${target}
  PROPERTIES OUTPUT_NAME core
  LINK_FLAGS ${PLAT_OBJ_FLAGS}
  PREFIX ""
  SUFFIX ".so"
)  
add_dependencies(${MODULE_NAME} ${target})

# --------------------------------------------------------------
#  install                                     
# --------------------------------------------------------------
install(TARGETS ${target}
  DESTINATION lib/lubyk/${MODULE_NAME}
)


