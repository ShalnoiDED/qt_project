cmake_minimum_required(VERSION 3.16)

project(PacketTestProject LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(PacketTestProject
  main.cpp
  packets/Packet.h
  packets/answer/A01Auth.h
  packets/command/C01Auth.h
  packets/result/R01Auth.h
  packets/answer/A02AuthResponse.h
  packets/command/C02AuthResponse.h
  packets/result/R02AuthResponse.h
  packets/command/C03TextMessage.h
  packets/answer/A03TextMessage.h
  packets/result/R03TextMessage.h
  packets/command/C04DataTransfer.h
  packets/answer/A04DataTransfer.h
  packets/result/R04DataTransfer.h
  packets/command/C05ConnectionCheck.h
  packets/answer/A05ConnectionCheck.h
  packets/result/R05ConnectionCheck.h
  packets/command/C06ErrorReport.h
  packets/answer/A06ErrorReport.h
  packets/result/R06ErrorReport.h
)
target_link_libraries(PacketTestProject Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS PacketTestProject
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
