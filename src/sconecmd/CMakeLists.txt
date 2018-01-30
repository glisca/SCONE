add_executable(sconecmd sconecmd.cpp)

if(UNIX)
    set(REALTIME_LIB ncurses)
    if(NOT APPLE)
        list(APPEND REALTIME_LIB tinfo)
    endif()
endif()

target_link_libraries(sconecmd sconelib ${REALTIME_LIB})