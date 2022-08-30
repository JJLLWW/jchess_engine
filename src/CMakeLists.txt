add_executable(jengine 
    main.cpp
    uci/uci_loop.cpp
    uci/uci_command.cpp
    uci/uci_execute.cpp
    uci/uci_fen.cpp
)

target_compile_features(jengine PRIVATE cxx_std_17)

target_include_directories(jengine
    PRIVATE
    uci
)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(jengine PRIVATE fmt::fmt)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(jengine PRIVATE spdlog::spdlog spdlog::spdlog_header_only)