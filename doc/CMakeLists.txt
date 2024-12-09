# VSCODE: To activate, need to add "DOCUMENTATION": "ON" for cmake.configureSettings in settings.json

option(DOCUMENTATION "Activate documentation" OFF)
if (DOCUMENTATION)
   set(DOXYGEN_EXECUTABLE doxygen)
   set(DOXYFILE Doxyfile)
   add_custom_target(doc_doxygen ALL
     COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${DOXYFILE}
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
     COMMENT "Generating API documentation with Doxygen"
     VERBATIM)
endif(DOCUMENTATION)
