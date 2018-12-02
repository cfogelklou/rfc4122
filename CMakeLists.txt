cmake_minimum_required (VERSION 3.5)
project (uuid)

file(GLOB MBEDTLS_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls_override/mbedtls/config.h
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/md5.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/sha1.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/platform_util.c
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include/md5.h
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include/sha1.h

  # Files below are needed to do random number generation with mbedtls.
  #${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/sha512.c
  #${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/platform.c
  #${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/entropy.c
  #${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/entropy_poll.c
  #${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/library/timing.c
)

file(GLOB LOCAL_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(SOURCE_FILES
  ${MBEDTLS_FILES}
  ${LOCAL_FILES}
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls_override
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include
  ${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include/mbedtls
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

