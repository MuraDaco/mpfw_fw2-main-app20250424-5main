//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork
//  Copyright (C) (2023) Marco Dau
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published
//  by the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//  
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  
//  You can contact me by the following email address
//  marco <d o t> ing <d o t> dau <a t> gmail <d o t> com
//  
//  *******************************************************************************

/*
 * vhwUnit.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#include <iomanip>      // std::quoted()
#include <iostream>
#include <string>
#include <stdexcept>

#include "appManager.h"

#define OUTPUT(a) std::cout << "output: " #a << '\n'

int main(int argc, char *argv[])      {
    //uint8_t g_portTest;
    uint8_t g_mcuId = 0;
    bool    g_shared_memory_reset = false;

    std::cout << "argc == " << argc << '\n';
 
    for(int ndx{}; ndx != argc; ++ndx) {
        std::cout << "argv[" << ndx << "] == " << std::quoted(argv[ndx]) << '\n';
        std::string l_string (argv[ndx]);
        if( "-id" == l_string)   {
            try
            {
                g_mcuId = std::stoi(argv[++ndx]); // Throws: no conversion
                std::cout << "-id parametr == " << static_cast<int> (g_mcuId) << '\n';
            }
            catch (std::invalid_argument const& ex)
            {
                std::cout << "#2: " << ex.what() << '\n';
            }
        }
        if( "--reset_shared_memory" == l_string)   {
            g_shared_memory_reset = true;
            std::cout << "shared memory reset == yes" << '\n';
        }
    }
    std::cout << "argv[" << argc << "] == "
              << static_cast<void*>(argv[argc]) << '\n';

    OUTPUT(million);
    std::cout << "output: " "test" << '\n';

    init_params_t l_initParams = {g_mcuId,g_shared_memory_reset};
    //vhwManager_t::loop(g_mcuId, g_shared_memory_reset);
    vhwManager_t::loop(&l_initParams);


}