# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-src"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-build"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/tmp"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/src"
  "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/mario/master_ws/build/pick_ik/_deps/catch2-subbuild/catch2-populate-prefix/src/catch2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
