# --------------------------------------------------------------
#  midi
#
#  provides:
#    midi.lua
#    midi/vendor.so, midi/In.lua, etc
# --------------------------------------------------------------
#   OFF: TODO: needs a complete rewrite
#
#   set(MODULE_NAME midi)
#   # --------------------------------------------------------------
#   #  module
#   # --------------------------------------------------------------
#   add_custom_target(${MODULE_NAME} true)
#   
#   # --------------------------------------------------------------
#   #  src
#   # --------------------------------------------------------------
#   add_subdirectory(src)
#   
#   # --------------------------------------------------------------
#   #  module_bind                                   
#   # --------------------------------------------------------------
#   file(GLOB MODULE_HEADERS include/${MODULE_NAME}/*.h)
#   add_custom_target("${MODULE_NAME}_bind"
#     COMMAND lua bind.lua
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     DEPENDS ${MODULE_HEADERS} bind.lua)
#   
#   # --------------------------------------------------------------
#   #  install                                     
#   # --------------------------------------------------------------
#   install(DIRECTORY lubyk
#     DESTINATION lib
#   )                                  
#   
