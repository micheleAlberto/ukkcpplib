
include_directories(${UKKCLIB_SOURCE_DIR}/tree)
link_directories(${UKKCLIB_BINARY_DIR}/tree)
add_library(node node.c)
add_library(tree tree.c)



