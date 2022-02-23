find_package(Doxygen)

if(Doxygen_FOUND)
  doxygen_add_docs(JitterDocs ${PROJECT_SOURCE_DIR}/include)
endif()
