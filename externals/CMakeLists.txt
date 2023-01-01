find_package(Boost REQUIRED)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(googletest)
add_subdirectory(json)
add_subdirectory(fmt)
add_subdirectory(cpr)
add_subdirectory(cpp-dotenv)
