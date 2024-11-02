# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PacketTestProject_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PacketTestProject_autogen.dir\\ParseCache.txt"
  "PacketTestProject_autogen"
  )
endif()
