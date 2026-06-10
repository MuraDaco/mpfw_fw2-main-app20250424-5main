#   *******************************************************************************
#   
#   mpfw / fw2 - Multi Platform FirmWare FrameWork 
#       library that contains the "main" entry point and, 
#       eventualy, application code that is platform dependent
#   Copyright (C) (2023) Marco Dau
#   
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as published
#   by the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#   
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.
#   
#   You can contact me by the following email address
#   marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
#   
#   *******************************************************************************

#### _______________________________________________________________
## *** Section  0 - HOW_TO_USE

#### _______________________________________________________________
## *** Section  1 - CMAKE INIT
    cmake_minimum_required(VERSION 3.16)

#### _______________________________________________________________
## *** Section  2 - SET ROOT RELATIVE PATHS
    include(${MPFW_CODE_CMAKE_DIR}/CMakeLists_steps/init_step_0.cmake)

#### _______________________________________________________________
## *** Section  3 - SET STANDARD PROJECT VARIABLES
    # set the project name and version
    set(PROJECT_NAME exec_${APP_NAME_LOWER}_ExecPrj)
    project(${PROJECT_NAME} VERSION 1.0)

#### _______________________________________________________________
## *** Section  4 - SET STANDARD AND SPECIFIC VARIABLES & BUILD LIBRARY CONFIG COMMANDS
    include(${MPFW_CODE_CMAKE_DIR}/CMakeLists_steps/step_all_exec.cmake)

