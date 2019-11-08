cmake_minimum_required(VERSION 3.0)
project(Pures)

# Settings
set(CONFIG Release)
set(DIR_INC ./Headers)
set(DIR_SRC ./Sources)
set(DIR_USE ./Mains)
set(OPT_COMPILE /TC /WX /Wall /O2 /Ob2 /Oi /Ot /GL)
set(OPT_LINK /LTCG)

set(CMAKE_CONFIGURATION_TYPES ${CONFIG})
set(CMAKE_BUILD_TYPE ${CONFIG})
set(CMAKE_STATIC_LINKER_FLAGS ${OPT_LINK})
set(CMAKE_EXE_LINKER_FLAGS ${OPT_LINK})
set(CMAKE_SUPPRESS_REGENERATION true)

# ThrPure
set(NAME thrpure)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# StrPure
set(NAME strpure)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c ${DIR_SRC}/strpain.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# TimPure
set(NAME timpure)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# Thread Tester
set(NAME threading)
add_executable(${NAME} ${DIR_USE}/${NAME}.c)
target_include_directories(${NAME} PRIVATE ${DIR_INC})
target_compile_options(${NAME} PRIVATE ${OPT_COMPILE})
target_link_libraries(${NAME} PRIVATE thrpure)
