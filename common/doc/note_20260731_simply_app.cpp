
---

Fri 31 Jul 2026 11:48:49 CEST

- file da modificare

........................
// mpfw_fw2-fnct-base-0abst
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/base/layer/mpfw_fw2-fnct-base-0abst/src/sys/sysDebug/v_00/sysDebugModuleDefine.h
    // appl_app20250424_4appl
        // #define     DEBUG_DEF_APP_MANAGER_CMMN_CPP

~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-fnct-base_hw-0abst
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0GpioDgIntfc/v_00/hw0GpioDgIntfc.h
        virtual uint32_t    pinRead         (void) {return 0;}                              ;
        virtual void        pinWrite        ([[maybe_unused]] uint8_t p_status) {}          ;
        virtual void        pinInit         (void) {}                                       ;

        virtual void        pinConfig       ([[maybe_unused]] uint8_t  p_Port,      [[maybe_unused]] uint8_t p_pin, [[maybe_unused]] gpio_config_struct_t& p_config) {};

// fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0GpioIntfc/v_00/hw0GpioIntfc.h
        enum k_modePort_t: uint8_t   {


~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-fnct-hw-1trdp-sdk-mac
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuPinPort/v_02/mcuPinPort.cpp
    mcuPinPort_t::mcuPinPort_t(                 uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
         g_ptrPort      {&g_ptrPortArray[p_port]}
        ,g_mcuIdOwner   {MCU_DEVICE_DEFAULT}
        ,g_ptrShmPort   {nullptr}
        ,g_port         {p_port}
        ,g_pin          {p_pin}
        ,g_dir          {p_dir}
        // ,g_dtyStatus    {&g_status}
    {
        g_config.mode = static_cast<k_modePort_t>(p_dir);
    }


// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuPinPort/v_02/mcuPinPort.h

        mcuPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir  );
        mcuPinPort_t  (uint8_t p_mcuId,   uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config   );

        // section end   **** CONSTRUCTOR ***** 
        // ****************************************************
        // --------------------------
    // ****************************************************
    // section start **** PIN PORT MANAGEMENT *****

    ...

        uint8_t g_port;
        uint8_t g_pin;
        uint8_t g_dir;

~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// mpfw_fw2-fnct-hw-1trdp-sdk-nxp
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp/src/drivers/v_07/mcu/mcuPinPort/v_00/mcuPinPort.cpp

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
 * mcuPinPort.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */

#include "mcuPinPort.h"

#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "pin_mux.h"


// ****************************************************
// section start **** MACRO DEFINEs *****


    #define pinSet          g_ptrPort[g_pin] = 1
    #define pinClr          g_ptrPort[g_pin] = 0
    #define pinTst          g_ptrPort[g_pin]
    #define pinTgl          g_ptrPort[g_pin] = pinTst ? 0 : 1

    #define PIN_SET         GPIO->SET[g_port] = (1 << g_pin)    // g_ptrPortArray[g_port] = g_ptrPortArray[g_port] |  (1 << g_pin)
    #define PIN_CLR         GPIO->CLR[g_port] = (1 << g_pin)    // g_ptrPortArray[g_port] = g_ptrPortArray[g_port] & ~(1 << g_pin)

    // section end   **** ENUMs DEFINITIONs ***** 
    // ****************************************************
    // --------------------------

// ****************************************************
// section start **** CONSTRUCTOR *****

    mcuPinPort_t::mcuPinPort_t(                 uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
         g_ptrPort      { GPIO->B[p_port]   }
        ,g_port         { p_port            }
        ,g_pin          { p_pin             }
        ,g_dir          { p_dir          }
    {}


    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PIN PORT MANAGEMENT *****

    // public:

//        uint32_t hw0GpioDgIntfc_t::pinRead   (uint8_t p_port, uint32_t p_pin)    {
//            return GPIO_PinRead(GPIO, p_port, p_pin);
//        }
//
//        void hw0GpioDgIntfc_t::pinWrite  (uint8_t  p_Port, uint32_t p_pin, uint8_t p_status) {
//            GPIO_PinWrite(GPIO, p_Port, p_pin, p_status);
//        }

        uint32_t mcuPinPort_t::pinRead   (void)    {
            return GPIO_PinRead(GPIO, g_port, g_pin);
        }

        void mcuPinPort_t::pinWrite  (uint8_t p_status) {
            GPIO_PinWrite(GPIO, g_port, g_pin, p_status);
        }

        void mcuPinPort_t::pinInit   (void)    {
            const uint32_t digital_io_port_config = (/* Pin is configured as PIO */
                                        IOCON_PIO_FUNC0 |
                                        /* Selects pull-up function */
                                        IOCON_PIO_MODE_PULLUP |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);

            IOCON_PinMuxSet(IOCON, g_port, g_pin, digital_io_port_config);
            
            GPIO_PortInit(GPIO, g_port );
            
            if(k_modePort_output == g_dir)  {
                // Define the init structure for the output pin
                gpio_pin_config_t out_config = {
                    kGPIO_DigitalOutput,
                    1                       // Set default output value
                };

                GPIO_PinInit (GPIO, g_port, g_pin, &out_config);

            } else {
                // Define the init structure for the output pin
                gpio_pin_config_t in_config = {
                    kGPIO_DigitalInput,
                    0                       // this value is not used
                };

                GPIO_PinInit (GPIO, g_port, g_pin, &in_config);
            }
            
        }

//         void mcuPinPort_t::pinConfig ([[maybe_unused]] uint8_t  p_Port,      [[maybe_unused]] uint8_t p_pin, gpio_config_struct_t& p_config)    {
//             g_config.type = p_config.type;
//             g_config.mode = p_config.mode;
//         }

        void mcuPinPort_t::setHigh        (void)    {
            if(k_modePort_output == g_dir)
                pinSet;
        }

        void mcuPinPort_t::setLow         (void)    {
            if(k_modePort_output == g_dir)
                pinClr;
        }

        void mcuPinPort_t::tglPin       (void)  {
            if(pinTst)  {
                pinClr;
                g_valuePinOld = 0;
            }
            else    {
                pinSet;
                g_valuePinOld = 1;
            }
            g_valueModified = true;
        }

        void mcuPinPort_t::setPin       (bool p_state)  {
            if(p_state) {
                pinSet;
                g_valuePinOld = 1;
            }
            else    {
                pinClr;
                g_valuePinOld = 0;
            }
        }

        bool mcuPinPort_t::getPin       (void)    {
            g_valuePinOld = pinTst;
            if(pinTst)  {
                g_valuePinOld = 1;
            }
            else    {
                g_valuePinOld = 0;
            }
            return pinTst;
        }

    // section end   **** PIN PORT MANAGEMENT *****
    // ****************************************************
    // --------------------------




// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp/src/drivers/v_07/mcu/mcuPinPort/v_00/mcuPinPort.h
        mcuPinPort_t  (uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir);

        // section end   **** CONSTRUCTOR ***** 
        // ****************************************************
        // --------------------------
    // ****************************************************
    // section start **** PIN PORT MANAGEMENT *****

        public:

            uint32_t     pinRead         (void)                                                         override;
            void         pinWrite        (uint8_t p_status)                                             override;
            void         pinInit         (void)                                                         override;

            // void    pinConfig   (uint8_t  p_Port,      uint8_t p_pin, gpio_config_struct_t& p_config)   ; // override;
            void    setHigh     (void)                                                                  override;
            void    setLow      (void)                                                                  override;
            void    tglPin      (void)                                                                  override;
            void    setPin      (bool p_state)                                                          override;
            bool    getPin      (void)                                                                  override;

        protected:
            volatile uint8_t* g_ptrPort;
            uint8_t g_port;
            uint8_t g_pin;

            uint8_t g_dir;


~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// mpfw_fw2-fnct-hw-2wrpr-sdk
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// 01 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwPinPort/v_01/hwPinPort.cpp
    hwPinPort_t::hwPinPort_t(                 uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
        mcuPinPort_t    (         p_port, p_pin, p_dir)
    {}

//    hwPinPort_t::hwPinPort_t(                 uint8_t  p_port, uint8_t p_pin, const gpio_config_struct_t& p_config) :
//        mcuPinPort_t    (         p_port, p_pin, p_config)
//    {}


// 02 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwPinPort/v_01/hwPinPort.h
        // hwPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config);
        hwPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir);

// 03 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwPinPort/v_01/hwPinPort2.cpp
     hwPinPort_t   (p_confPort1.port, p_confPort1.pin,  p_confPort1.config.mode)
    ,g_pinPort2     {p_confPort2.port, p_confPort2.pin,  p_confPort2.config.mode}

// 04 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/prox/hw/hwManager/v_01/hwManagerTbl.h
#endif 	// HW_MANAGER_TBL_H

// 05 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/wsp/v_09hw_2/cmake/cpp_files.cmake
        	## -- ${${CURR_MOD_NAME}_sdk_SRC_DIR}/hw/hwPinPort2/v_${${CURR_MOD_NAME}_hwPinPort2_VER}/hwPinPort2.cpp

// ...

// 06 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/config/hw/usartRs485/hwConfig_hwUsartRs485.h
/*
 * hwConfig_hwUsartRs485.h
 *
 *  Created on: Feb, 24th 2026 (Wed)
 *      Author: Marco Dau
 */

#ifndef HW_CONFIG__HW_USART_RS485_H_
#define HW_CONFIG__HW_USART_RS485_H_

....

#endif  //  HW_CONFIG__HW_USART_RS485_H_


// 07 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwPinPort/v_01/hwPinPort.cpp
    hwPinPort_t::hwPinPort_t(uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
        mcuPinPort_t    (p_port, p_pin, p_dir)
    {}

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PROCESS MANAGEMENT *****

        void hwPinPort_t::hwInit                (void)      {
 
            pinInit();
 
        }

    // section end   **** PROCESS MANAGEMENT *****
    // ****************************************************
    // --------------------------


// 08 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwPinPort/v_01/hwPinPort.h
// class hwPinPort_t :     public     hw2ProxCmmn_t       // (all platforms)     - processes (init, loop, end) interface 
class hwPinPort_t :      public     mcuPinPort_t        // (specific platform) - sdk module
                        ,public     hw2ProxCmmn_t       // (all platforms)     - processes (init, loop, end) interface 
                        
{

// ****************************************************
// section start **** CONSTRUCTOR *****
    public:

    hwPinPort_t  (uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir);
    //hwPinPort_t  (uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config);

    // section end   **** CONSTRUCTOR ***** 
    // ****************************************************
    // --------------------------
// ****************************************************
// section start **** PROCESS MANAGEMENT *****

    public:
        void hwInit                (void) override;


// 09 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/prox/hw/hwManager/v_01/hwManagerTbl.h
#endif 	// HW_MANAGER_TBL_H

// 10 - fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/wsp/v_09hw_2/cmake/cpp_files.cmake
        	## -- ${${CURR_MOD_NAME}_sdk_SRC_DIR}/hw/hwPinPort2/v_${${CURR_MOD_NAME}_hwPinPort2_VER}/hwPinPort2.cpp


~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// mpfw_fw2-appl-app20250424-4appl
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// 01 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Buttons.cpp
/*
 * app_cmmn_pphDef_Buttons.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#include "app_cmmn_pphDef_Buttons.h"

// 02 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Buttons.h
/*
 * app_cmmn_pphDef_Buttons.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */

// 03 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Leds.cpp
// 04 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Leds.h

// 05 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/manager/app_managerCmmn/v_01/app_ManagerCmmn.cpp
#include "app_cmmn_pphDef_Buttons.h"
#include "app_cmmn_pphDef_Leds.h"
using namespace mpfw::apps;


uint8_t app_ManagerCmmn_t::g_status = 0xff;
uint8_t app_ManagerCmmn_t::g_ptrBuf_A[] = ".1234.01u|ZZ_answer|";
uint8_t app_ManagerCmmn_t::g_ptrBuf_B[] = ".1234.01u|YY_answer|";
uint8_t app_ManagerCmmn_t::g_ptrBuf_C[] = ".1234.01u|XX_answer|";

void app_ManagerCmmn_t::thread_loopApp1 (krThreadId p_ThreadId) {
    if(krThreadId::krThread_App_1 == p_ThreadId) {

        if( app_threads_t::statusThread_match(kStatusThread_LOOP_APP_1) )   {

            if(PPH_OBJ(BUTTON_SW2_ISP2).getPin())   {
                //app_threads_t::statusThread_next();
                PPH_OBJ(LED_LED1_D12).setHigh();
                PPH_OBJ(LED_LED2_D11).setHigh();
            }
        }
    }
}

// 06 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/wsp/v_13appl/cmake/cpp_files.cmake
		${${CURR_MOD_NAME}_cmmn_SRC_DIR}/instances/hw/units/app_cmmn_pphDef_Buttons.cpp
		${${CURR_MOD_NAME}_cmmn_SRC_DIR}/instances/hw/units/app_cmmn_pphDef_Leds.cpp

// 07 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/hw/app_hwManagerTbl.cpp
#include "hwManagerTbl.h"
#include "app_cmmn_pphDef_Buttons.h"
#include "app_cmmn_pphDef_Leds.h"


hw2ProxCmmn_t*  hwManagerTbl_t::UnitPtrArray[]   = {
     &PPH_OBJ   (BUTTON_SW2_ISP2)
    ,&PPH_OBJ   (BUTTON_SW3_ISP1)
    ,&PPH_OBJ   (BUTTON_SW4_ISP0)
    ,&PPH_OBJ   (BUTTON_SW5_USER)
    ,&PPH_OBJ   (LED_LED1_D12)
    ,&PPH_OBJ   (LED_LED2_D11)
    ,&PPH_OBJ   (LED_LED3_D9 )
    ,nullptr
};

// 08 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/hw/app_vhwManagerTbl.cpp
vhw2ProxCmmn_t*  vhwManagerTbl_t::UnitPtrArray[]   = {
     &PPH_OBJ   (BUTTON_UP)
    ,&PPH_OBJ   (BUTTON_TEST)
    ,&PPH_OBJ   (BUTTON_XXX)
    ,&PPH_OBJ   (LED_A)
    ,&PPH_OBJ   (LED_C)
    // ,&PPH_OBJ   (SWITCH_TST1)
    // ,&PPH_OBJ   (ALARM_A)

    ,&PPH_OBJ   (BUTTON_AAA)
    ,&PPH_OBJ   (BUTTON_BBB)
    ,&PPH_OBJ   (BUTTON_CCC)
    ,&PPH_OBJ   (LED_XXX)
    ,&PPH_OBJ   (LED_YYY)
    // ,&PPH_OBJ   (ALARM_NNN)
    // ,&PPH_OBJ   (SWITCH_GGG)
    // ,&PPH_OBJ   (LINK_TTT)
    ,&PPH_OBJ   (USART_1)
    ,&PPH_OBJ   (USART_1_DBG)
    ,&PPH_OBJ   (USART_2_REAL)
    ,nullptr
};

// 09 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/pph/app_pphDef_Mod1.cpp
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_XOR           )
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_NOR           )
// 
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_AND           )
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_NOT           )
// 
// 
// PPH_DEF_CPP_LINK    (pphRelay_t   ,ALARM_A     ,2 ,5     )
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_TST1           )
// PPH_DEF_CPP_LINK    (pphWired_t  ,LINK_A      ,3 ,1     )
// 
// PPH_DEF_CPP_LINK    (pphRelay_t   ,ALARM_NNN   ,2 ,5     )
// PPH_DEF_CPP         (pphSwitch_t ,SWITCH_GGG            )
// PPH_DEF_CPP_LINK    (pphWired_t  ,LINK_TTT    ,3 ,1     )

// 10 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/tbl/app_hwManagerTbl.cpp

#include "app_cmmn_pphDef_Buttons.h"
#include "app_cmmn_pphDef_Leds.h"

hw2ProxCmmn_t*  hwManagerTbl_t::UnitPtrArray[]   = {
     &PPH_OBJ   (USART_1_REAL)
    ,&PPH_OBJ   (USART_2_REAL)
    ,&PPH_OBJ   (BUTTON_SW2_ISP2)
    ,&PPH_OBJ   (BUTTON_SW3_ISP1)
    ,&PPH_OBJ   (BUTTON_SW4_ISP0)
    ,&PPH_OBJ   (BUTTON_SW5_USER)
    ,&PPH_OBJ   (LED_LED1_D12)
    ,&PPH_OBJ   (LED_LED2_D11)
    ,&PPH_OBJ   (LED_LED3_D9 )
    ,nullptr
};

// 11 - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h

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
 * app_mcuPinPortDefineConfig.h
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */


#ifndef APP_MCU_PIN_PORT_DEFINE_CONFIG_H
#define APP_MCU_PIN_PORT_DEFINE_CONFIG_H

#include "LPC54608.h"
#include "hw0UsartRs485Params.h"
#include "hwConfig_hwUsartRs485.h"

using namespace fw2::fnct::base::hw;

/*
    peripherals list
    - USART_RX
    - USART_TX
    - LED_TEST
    - LED_A
    - LED_B
    - LED_C
    - BUTTON_UP
    - SWITCH_TST1
    - ALARM_A_OUT
    - ALARM_A_IN

    for each (peripheral) create a #define of (PORT) and (PIN)
        #define MCU_[<device id>_]<peripheral name>_PORT_PTR  <sdk referiment port pointer>
        #define MCU_[<device id>_]<peripheral name>_PORT      <sdk referiment port ID>
        #define MCU_[<device id>_]<peripheral name>_PIN       <pin ID>

*/

// *********************************************
#define APP_BOARD_MARCO_TEST_SW2_PORT 0U
#define APP_BOARD_MARCO_TEST_SW2_PIN  6U

#define APP_BOARD_MARCO_TEST_LED2_PORT 3U
#define APP_BOARD_MARCO_TEST_LED2_PIN  3U

// *********************************************
#define APP_BOARD_MARCO_TEST_SW3_PORT 0U
#define APP_BOARD_MARCO_TEST_SW3_PIN  5U

#define APP_BOARD_MARCO_TEST_LED3_PORT 2U
#define APP_BOARD_MARCO_TEST_LED3_PIN  2U


#define MCU_USART_1_REAL
#define MCU_USART_2_REAL

#define USART_INSTANCE_ID_4 USART0


#define MCU_BUTTON_SW2_ISP2         
#define MCU_BUTTON_SW3_ISP1         
#define MCU_BUTTON_SW4_ISP0         
#define MCU_BUTTON_SW5_USER         

// #define MCU_BUTTON_SW2_ISP2_PORT_PTR             SDK_MCU_PORT_0_PTR                 // see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_BUTTON_SW2_ISP2_PORT                 APP_BOARD_MARCO_TEST_SW2_PORT      // port 0 - see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_BUTTON_SW2_ISP2_PIN                  APP_BOARD_MARCO_TEST_SW2_PIN       // pin  6 - see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"

// #define MCU_BUTTON_SW3_ISP1_PORT_PTR             SDK_MCU_PORT_0_PTR                 // see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_BUTTON_SW3_ISP1_PORT                 APP_BOARD_MARCO_TEST_SW3_PORT      // port 0 - see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_BUTTON_SW3_ISP1_PIN                  APP_BOARD_MARCO_TEST_SW3_PIN       // pin  5 - see "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"

// #define MCU_BUTTON_SW4_ISP0_PORT_PTR             SDK_MCU_PORT_0_PTR
#define MCU_BUTTON_SW4_ISP0_PORT                 0
#define MCU_BUTTON_SW4_ISP0_PIN                  4

// #define MCU_BUTTON_SW5_USER_PORT_PTR             SDK_MCU_PORT_1_PTR
#define MCU_BUTTON_SW5_USER_PORT                 1
#define MCU_BUTTON_SW5_USER_PIN                  1


#define MCU_LED_LED1_D12
#define MCU_LED_LED2_D11
#define MCU_LED_LED3_D9 


// #define MCU_LED_LED1_D12_PORT_PTR                SDK_MCU_PORT_3_PTR                 // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED1_D12_PORT                    3                 // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED1_D12_PIN                     14                // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"

// #define MCU_LED_LED2_D11_PORT_PTR                SDK_MCU_PORT_3_PTR                 // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED2_D11_PORT                    APP_BOARD_MARCO_TEST_LED2_PORT     // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED2_D11_PIN                     APP_BOARD_MARCO_TEST_LED2_PIN      // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"

// #define MCU_LED_LED3_D9_PORT_PTR                 SDK_MCU_PORT_2_PTR                 // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED3_D9_PORT                     APP_BOARD_MARCO_TEST_LED3_PORT     // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"
#define MCU_LED_LED3_D9_PIN                      APP_BOARD_MARCO_TEST_LED3_PIN      // see  "LPC54608_Dev_brd_schematic_Rev-D_170614.pdf"

// ***********


class hw0UsartRs485ParamsReal_t: public hw0UsartRs485Params_t {

    public:
        void    clrTxEnablePin      (void) override;
        void    setRxEnablePin      (void) override;
        void    setTxEnablePin      (void) override;
        void    clrRxEnablePin      (void) override;


};

#define USART_PARAMS_4    &g_usartParams

extern hw0UsartRs485ParamsReal_t g_usartParams;

#endif 	// APP_MCU_PIN_PORT_DEFINE_CONFIG_H


~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// mpfw_fw2-fnct-hw-3real
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphButton/v_00/pphButton.cpp
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
 * pphButton.cpp
 *
 *  Created on: Jun, 27 2024
 *      Author: Marco Dau
 */

#include "pphButton.h"

// #include "hw0GpioIntfc.h"

pphButton_t::pphButton_t(uint8_t p_port, uint8_t p_pin)  :
     hwPinPort_t  (p_port, p_pin, 0 ) // 0 -> input
{}


// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphButton/v_00/pphButton.h

    // to remove
        pphButton_t(gpio_base_struct_t p_ConfPinPort  );


// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphButton/v_00/pphLed.cpp
     hwPinPort_t  (p_port, p_pin, 1)    // 1 -> output

// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphButton/v_00/pphLed.h

    // to remove
        pphLed_t(gpio_base_struct_t p_ConfPinPort  );

// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/wsp/v_10hw_3/cmake/cpp_files.cmake

        set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_CPP
    
     		## pph
     	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphButton/v_${${CURR_MOD_NAME}_pphButton_VER}/pphButton.cpp
     	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphLed/v_${${CURR_MOD_NAME}_pphLed_VER}/pphLed.cpp
     	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphManager/v_${${CURR_MOD_NAME}_pphManager_VER}/pphManager.cpp
    ## - 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphRelay/v_00/pphRelay.cpp
    ## - 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphSwitch/v_00/pphSwitch.cpp
     	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphUsartRs485/v_${${CURR_MOD_NAME}_pphUsartRs485_VER}/pphUsartRs485.cpp
    ## - 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphWired/v_00/pphWired.cpp
    )


~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// ---
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// ---
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// ---
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

~~~~~~~~~~~~~~~~~~~~~~~~
........................


