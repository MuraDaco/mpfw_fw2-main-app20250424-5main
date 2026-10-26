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


    set(CURR_MOD_NAME       MAIN-APP20250424-5MAIN)

    set(${CURR_MOD_NAME}_sdk_SOURCE_FILES_CPP

        ${${CURR_MOD_NAME}_sdk_SRC_DIR}/hwMain/v_${${CURR_MOD_NAME}_hwMain_VER}/hwMain.cpp
        ${${CURR_MOD_NAME}_sdk_SRC_DIR}/other/v_${${CURR_MOD_NAME}_other_VER}/cpp_config.cpp
        ${${CURR_MOD_NAME}_sdk_SRC_DIR}/other/v_${${CURR_MOD_NAME}_other_VER}/freertos.c
        ${${CURR_MOD_NAME}_sdk_SRC_DIR}/other/v_${${CURR_MOD_NAME}_other_VER}/semihost_hardfault.c
        ${${CURR_MOD_NAME}_sdk_SRC_DIR}/other/v_${${CURR_MOD_NAME}_other_VER}/startup_lpc54608.cpp

    )
