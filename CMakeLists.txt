# --------------------------------------------------------------
#  midi
#
#  provides:
#    midi.lua
#    midi/vendor.so, midi/In.lua, etc
# --------------------------------------------------------------
set(MODULE_NAME midi)

include_directories(include)
include_directories(../core/include)
# --------------------------------------------------------------
#  module
# --------------------------------------------------------------
add_custom_target(${MODULE_NAME} true)

# --------------------------------------------------------------
#  src
# --------------------------------------------------------------
if(APPLE)
  set(PLAT_OBJ_FLAGS "${PLAT_OBJ_FLAGS} -framework CoreMIDI -framework CoreAudio")
endif(APPLE)

add_subdirectory(src)

# --------------------------------------------------------------
#  module_bind                                   
# --------------------------------------------------------------
file(GLOB MODULE_HEADERS include/${MODULE_NAME}/*.h)
add_custom_target("${MODULE_NAME}_bind"
  COMMAND lua bind.lua
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS ${MODULE_HEADERS} bind.lua)

# --------------------------------------------------------------
#  install                                     
# --------------------------------------------------------------
install(DIRECTORY lib
  DESTINATION ${LUBYK_LIB}
)
