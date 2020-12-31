set(BOOST_ROOT C:/boost_1_68_0)
find_package(Boost REQUIRED)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(googletest)
add_subdirectory(json)
add_subdirectory(curl)
