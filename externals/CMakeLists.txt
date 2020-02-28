SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(googletest)
add_subdirectory(json)
add_subdirectory(curl)
add_subdirectory(plog)
