cmake_minimum_required(VERSION 3.6)
project(apl)

include(cmsi_import)

cmsi_import(dpl)

find_package(ASIO REQUIRED)

cmsi_importp(aplechoclient)
cmsi_importp(aplechoserver)
cmsi_importp(apltcp)

add_custom_target(apl DEPENDS
  aplechoclient
  aplechoserver
  apltcp
)

# ----------------------------------------------------------------------------
# Copyright 2017 Bloomberg Finance L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
