#   *******************************************************************************
#   
#   mpfw / fw2 - Multi Platform FirmWare FrameWork 
#       
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

### ---------------------------
##
#   set_public_rpath.cmake
#
#   Created on: May, 23rd 2025  (Fri)
#   Author: Marco Dau
##
### ---------------------------

include_guard()

    set(CURR_MOD_NAME       MAIN-APP20250424-5MAIN)

	message(STATUS "Start set_public_config_rpath of -->> ${CURR_MOD_NAME} <<--")
 
### **************************************************
### --- set ..._<module name>_CONFIG_RPATH variable
## --- start section

    ## ....... HELP start 
    ## other's config files
        ## set(OWNR_MOD_NAME       <owner module name of config file> has the same format of <${CURR_MOD_NAME}>)
        ## set(${CURR_MOD_NAME}__${OWNR_MOD_NAME}__CONFIG__RPATH		${${CURR_MOD_NAME}_sdk_SRC_RPATH}/path to config file)
        ## RegisterConfigRpath(${OWNR_MOD_NAME}_CONFIG_RPATH		${CURR_MOD_NAME}__${OWNR_MOD_NAME}__CONFIG__RPATH)
    ## ....... HELP end 

    ## --- end section
    ### **************************************************
