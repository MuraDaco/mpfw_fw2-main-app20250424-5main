
---

Wed 12 Aug 2026 10:25:19 CEST

- aggiornamenti futuri da fare
    - 1. necessario
        - aggornare le classi
            - ;[hwManager]
            - ;[vhwManager]
            - ;[hwPinPort] della piattaforma mac
                - eliminare la derivazione dalla classe [hw2ProxCmmn_t]
                    - questi componenti hw sono solo virtuali
                - e contemporaneamente aggiornare le tabelle
                    - ;[app_hwManagerTbl.cpp]
                    - ;[app_vhwManagerTbl.cpp]
        - eliminare
            - ;[hw2ManagerCmmn_t]
    - 2. importante
        - ;[g_usart4_this] da sostituire con elemento di un array
            - creare l'array di puntatori agli oggetti della classe 
                - ;[hwUsartRs485_t] necessari per implementare gli handler dei ;[FLEXCOMM]
        - implementare anche la seriale di default della scheda LPCXpresso546xx rev. D ovvero la
            - ;[FLEXCOMM0]
    - 3. importante
        - implementare i tasti ed i leds presenti nella piattaforma reale ;[nxp] in quella virtuale ;[mac]
    - 4. importante
        - implementare anche la piattaforma ;[stm32f769_disco]
    - 5. importante
        - implementare la classe usart reale anche nella piattaforma virtuale ;[mac]
            - vedere poi di gestire un hub per la comunicazione seriale anche per più istanze dell applicazione
                - a tale proposito si potrebbe pensare ad una cosa del genere
                    - a) derivare la classe virtuale
                        - in modo che il canale virtuale è sempre attivo
                    - b) aggiungere un processo "nascosto" nel buffer dei processi che condividono la ;[shared_memory]
                        - questo processo nascosto fa quanto segue
                            - quello che riceve sulla ;[shared_memory] lo invia sulla seriale ;[/dev/tty.xxx]
                            - quello che riceve sulla seriale ;[/dev/tty.xxx] lo mette sulla ;[shared_memory]
                - però visto quanto si deve fare sarebbe meglio implementare una classe usart reale
                    - in qusto modo l'implementazione risulterebbe più semplice 
                    - e fornirebbe una base per implementare un hub seriale
                - forse però le cose potrebbero essere più semplici di quanto ipotizzato all'inizio
                    - semplicemente
                        - si prende una istanza della seriale "virtuale"
                        - e poi si implementa una classe uart reale che lavora allo stsso modo di un componente tui
                            - ovvero usa l'istanza della seriale "virtuale"
                                - quello che viene ricevuto nella s. virtuale lo invia sul canale ;[/dev/tty.xxx]
                                - quello che viene ricevuto sul canale ;[/dev/tty.xxx] lo invia sulla s. virtuale                   
    - 6. facoltativo
        - uniformare la classe [hwManager] e renderla uguale per tutte le piattaforme "virtuali" e "reali"
            - infatti non è detto che anche le piattaforme "reali" (nxp, stm32f769_disco); possano istanziare oggetti hw virtuali
            
- file da modificare/aggiornare

................................................
// --- a/appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common
        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Buttons.h/.cpp
            // .h
                /*
                --> * app_cmmn_pphDef_Buttons.h

            // .cpp
                /*
                --> * app_cmmn_pphDef_Buttons.cpp
                 *
                 *  Created on: Jun, 27 2024
                 *      Author: Marco Dau
                 */


                --> #include "app_cmmn_pphDef_Buttons.h"
            // end

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_cmmn_pphDef_Leds.h/.cpp
            // .h
                /*
                --> * app_cmmn_pphDef_Leds.h

            // .cpp
                /*
                --> * app_cmmn_pphDef_Leds.cpp
                 *
                 *  Created on: Jun, 27 2024
                 *      Author: Marco Dau
                 */


                --> #include "app_cmmn_pphDef_Leds.h"
            // end

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_pphDef_ModCmmn.cpp
            --> hwUsartInitParams_t glo_usartParams_2Real    = HW_USART_INIT_PARAMS_DEF;
            // end

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/manager/app_managerCmmn/v_01/app_ManagerCmmn.h/cpp
            // .h
                private:
                    static uint8_t g_status;
                    static uint8_t g_ptrBuf_A[];
                    static uint8_t g_ptrBuf_B[];
                    static uint8_t g_ptrBuf_C[];

                -->    static bool     g_tx_on;
            // .cpp
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
                 * app_Manager.cpp
                 *
                 *  Created on: Dec, 27th 2025 (Sat)
                 *      Author: Marco Dau
                 */

                #include "app_ManagerCmmn.h"

                //#include "fsl_gpio.h"
                //
                #include "app_ManagerCmmn_dbgSetup.h"

                #include "pphManager.h"
                #include "sysTimer.h"

                #include "app_threads.h"
                #include "app_threadsConfig.h"
                #include "app_pphDef_ModCmmn.h"
                #include "app_cmmn_pphDef_Buttons.h"
                #include "app_cmmn_pphDef_Leds.h"
                using namespace mpfw::apps;


                uint8_t app_ManagerCmmn_t::g_status = 0xff;
                uint8_t app_ManagerCmmn_t::g_ptrBuf_A[] = ".1234.01u|ZZ_answer|";
                uint8_t app_ManagerCmmn_t::g_ptrBuf_B[] = ".1234.01u|YY_answer|";
                uint8_t app_ManagerCmmn_t::g_ptrBuf_C[] = ".1234.01u|XX_answer|";

                bool app_ManagerCmmn_t::g_tx_on = true;

                void app_ManagerCmmn_t::thread_loopApp1 (krThreadId p_ThreadId) {
                    if(krThreadId::krThread_App_1 == p_ThreadId) {
                    
                        if( app_threads_t::statusThread_match(kStatusThread_LOOP_APP_1) )   {
                        
                            if(!PPH_OBJ(BUTTON_SW2_ISP2).getPin())   {
                                g_tx_on = true;
                                PPH_OBJ(LED_LED2_D11).setHigh();
                                PPH_OBJ(LED_LED3_D9).setHigh();
                            } else {
                                PPH_OBJ(LED_LED2_D11).setLow();
                                PPH_OBJ(LED_LED3_D9).setLow();
                            }

                            // if(!PPH_OBJ(BUTTON_SW4_ISP0).getPin())   {
                            //     PPH_OBJ(LED_LED2_D11).setHigh();
                            //     PPH_OBJ(LED_LED3_D9).setHigh();
                            // } else {
                            //     PPH_OBJ(LED_LED2_D11).setLow();
                            //     PPH_OBJ(LED_LED3_D9).setLow();
                            // }

                            // if(!PPH_OBJ(BUTTON_SW3_ISP1).getPin())   {
                            //     PPH_OBJ(LED_LED1_D12).setHigh();
                            // } else {
                            //     PPH_OBJ(LED_LED1_D12).setLow();
                            //     pph_USART_2_REAL.send(g_ptrBuf_A);
                            // }

                            if(!g_tx_on) {
                                rx_tx(&pph_USART_2_REAL);
                            }

                            if(PPH_OBJ(BUTTON_SW3_ISP1).getPin())   {
                                // button released
                                PPH_OBJ(LED_LED1_D12).setHigh();
                            } else {
                                // button pressed
                                PPH_OBJ(LED_LED1_D12).setLow();

                                if(g_tx_on) {
                                    // leds ON
                                    PPH_OBJ(LED_LED2_D11).setHigh();
                                    PPH_OBJ(LED_LED3_D9).setHigh();
                                    uint8_t l_str1[] = "01u|Messaggio di test|";
                                    // pph_USART_2_REAL.send(l_str1);
                                    if(pph_USART_2_REAL.tx_packetSent(l_str1, sizeof(l_str1)))  {
                                        while(!pph_USART_2_REAL.getBufferStatusFree()){
                                            if(!PPH_OBJ(BUTTON_SW4_ISP0).getPin())   {
                                                // button pressed
                                                pph_USART_2_REAL.setBufferStatusFree();                            
                                            }
                                        }
                                    }
                                    g_tx_on = false;
                                }
                            }

                //            if(GPIO_PinRead(GPIO, APP_BOARD_MARCO_TEST_SW2_PORT, APP_BOARD_MARCO_TEST_SW2_PIN))
                //                GPIO_PinWrite(GPIO, APP_BOARD_MARCO_TEST_LED2_PORT, APP_BOARD_MARCO_TEST_LED2_PIN, 1);
                //            else
                //                GPIO_PinWrite(GPIO, APP_BOARD_MARCO_TEST_LED2_PORT, APP_BOARD_MARCO_TEST_LED2_PIN, 0);
                //
                //            if(GPIO_PinRead(GPIO, APP_BOARD_MARCO_TEST_SW3_PORT, APP_BOARD_MARCO_TEST_SW3_PIN))
                //                GPIO_PinWrite(GPIO, APP_BOARD_MARCO_TEST_LED3_PORT, APP_BOARD_MARCO_TEST_LED3_PIN, 1);
                //            else
                //                GPIO_PinWrite(GPIO, APP_BOARD_MARCO_TEST_LED3_PORT, APP_BOARD_MARCO_TEST_LED3_PIN, 0);

                            app_threads_t::statusThread_next();
                        }
                    }
                }


                void app_ManagerCmmn_t::rx_tx (pphUsartRs485_t* p_usart) {
                            uint8_t l_id1 = 0; 
                            uint8_t l_rxBufferSize = p_usart->rx_packetCheck();
                            if(l_rxBufferSize)  {
                                uint8_t* l_pPphUsartBuff = p_usart->rxBuff_getPtrCleaned();

                                // 1. step: init
                                if(
                                        ( 'A'   == l_pPphUsartBuff[4] ) 
                                    &&  ( 'A'   == l_pPphUsartBuff[5] ) 
                                    &&  ( 0xff  == g_status ) 
                                ) g_status = 1;
                                if(
                                        ( 'B'   == l_pPphUsartBuff[4] ) 
                                    &&  ( 'B'   == l_pPphUsartBuff[5] ) 
                                    &&  ( 0xff  == g_status ) 
                                ) g_status = 2;
                                if(
                                        ( 'C'   == l_pPphUsartBuff[4] ) 
                                    &&  ( 'C'   == l_pPphUsartBuff[5] ) 
                                    &&  ( 0xff  == g_status ) 
                                ) g_status = 3;


                                // 2. step: answer
                                if(
                                        ( '1'   == l_pPphUsartBuff[4] ) 
                                    &&  ( '1'   == l_pPphUsartBuff[5] ) 
                                    &&  (  1    == g_status ) 
                                )   {
                                    l_id1 = 1;
                                }
                                if(
                                        ( '2'   == l_pPphUsartBuff[4] ) 
                                    &&  ( '2'   == l_pPphUsartBuff[5] ) 
                                    &&  (  2    == g_status ) 
                                )   {
                                    l_id1 = 2;
                                }

                                if(
                                        ( '3'   == l_pPphUsartBuff[4] ) 
                                    &&  ( '3'   == l_pPphUsartBuff[5] ) 
                                    &&  (  3    == g_status ) 
                                )   {
                                    l_id1 = 3;
                                }

                                // unlock the rxBuffer to receive other new packets
                                p_usart->setBufferStatusFree();
                            }


                            // 2. step: answer
                            if(
                                    ( 1   == l_id1 ) 
                            )   {
                                p_usart->send(g_ptrBuf_A);
                                while(!p_usart->getBufferStatusFree()){
                                    if(!PPH_OBJ(BUTTON_SW4_ISP0).getPin())   {
                                        // button pressed
                                        p_usart->setBufferStatusFree();                            
                                    }
                                }

                            }
                            if(
                                    ( 2   == l_id1 ) 
                            )   {
                                p_usart->send(g_ptrBuf_B);
                            }
                            if(
                                    ( 3   == l_id1 ) 
                            )   {
                                p_usart->send(g_ptrBuf_C);
                            }

                }

                uint8_t app_ManagerCmmn_t::setStatus (pphUsartRs485_t* p_usart) {
                    uint8_t l_status = 0; 
                    uint8_t l_rxBufferSize = p_usart->rx_packetCheck();
                    if(l_rxBufferSize)  {
                        uint8_t* l_pPphUsartBuff = p_usart->rxBuff_getPtrCleaned();

                        // 1. step: init
                        if(
                                ( 'F'   == l_pPphUsartBuff[4] ) 
                            &&  ( 'F'   == l_pPphUsartBuff[5] ) 
                            &&  ( 0xff  == g_status ) 
                        ) g_status = 4;
                        if(
                                ( 'G'   == l_pPphUsartBuff[4] ) 
                            &&  ( 'G'   == l_pPphUsartBuff[5] ) 
                            &&  ( 0xff  == g_status ) 
                        ) g_status = 5;
                        if(
                                ( 'H'   == l_pPphUsartBuff[4] ) 
                            &&  ( 'H'   == l_pPphUsartBuff[5] ) 
                            &&  ( 0xff  == g_status ) 
                        ) g_status = 6;


                        // 2. step: answer
                        if(
                                (   ( '1'   == l_pPphUsartBuff[4] ) 
                                &&  ( '1'   == l_pPphUsartBuff[5] ) 
                                &&  (  4    == g_status ) 
                                )
                            ||  (   ( '2'   == l_pPphUsartBuff[4] ) 
                                &&  ( '2'   == l_pPphUsartBuff[5] ) 
                                &&  (  5    == g_status ) 
                                )
                            ||  (   ( '3'   == l_pPphUsartBuff[4] ) 
                                &&  ( '3'   == l_pPphUsartBuff[5] ) 
                                &&  (  6    == g_status ) 
                                )
                        )   {
                            l_status = g_status;
                        }

                        // unlock the rxBuffer to receive other new packets
                        p_usart->setBufferStatusFree();
                    }

                    return l_status;
                }

                void app_ManagerCmmn_t::thread_loopApp2 (krThreadId p_ThreadId) {
                    if(krThreadId::krThread_App_2 == p_ThreadId) {
                    
                        if( app_threads_t::statusThread_match(kStatusThread_LOOP_APP_2) )   {

                            // rx_tx(&pph_USART_2_REAL);

                            app_threads_t::statusThread_next();
                        }
                    }
                }
            // end    

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/wsp/v_13appl/cmake/cpp_files.cmake
    		${${CURR_MOD_NAME}_cmmn_SRC_DIR}/instances/hw/units/app_cmmn_pphDef_Buttons.cpp
    		${${CURR_MOD_NAME}_cmmn_SRC_DIR}/instances/hw/units/app_cmmn_pphDef_Leds.cpp
            // end
        // end

    // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac
        // ragionamenti
            . è proprio necessario gestire due tabelle di componenti hardware?
                . vhw2ProxCmmn_t    --> app_vhwManagerTbl.cpp
                . hw2ProxCmmn_t     --> app_hwManagerTbl.cpp
            . io direi di sì con un aggiunta però
                . i componenti hardware se fanno parte di una tabella non possono far parte anche dell altra
                    . questo significa che le classi dei componenti hw, come ad esempio hwPinPort,
                        . DEVONO ereditare una sola delle classi
                            . vhw2ProxCmmn_t e hw2ProxCmmn_t
                        . quindi si dovrebbe aggiornare la classe [hwPinPort_t] per la piattaforma [mac]
                        . ed eliminare la derivazione dalla classe [hw2ProxCmmn_t]
                . è giusto che ci sia una differenziazione tra componenti "reale" e "virtuali"/"simulati"
                    . nel caso della piattaforma [mac] può essere il caso del componente [usart] che può essere
                    . sia reale (si usa /dev/tty.xxxx) che virtuale (si usa la shared memory)
            . quindi è giusto differenziare gli elementi hw tra "reali" e "virtuali"
            . notare poi che la gestione degli elementi "virtuali" è subordinata a quella degli elementi "reali" nel senso che
            . il "manager" degli elementi "virtuali" (vhwManager) è usato dal manager degli elementi "reali"
                . nel caso di piattaforma che istanzia elementi "virtiuali"
            . un altra nota
                . sembrerebbe che la classe [hw2ManagerCmmn_t] sia vuota quindi si può eliminarla
                . aggiornando contemporanemente anche le classi [hwManager] e [vhwManager]

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/hw/app_hwManagerTbl.cpp
            /*
             * app_pphManagerTbl.cpp
             *
             *  Created on: Jun, 27 2024
             *      Author: Marco Dau

                see the mcuPinPort.h to know how to compose the PORT and PIN #define name
                MCU_<port function name>_PORT
                MCU_<port function name>_PIN

             */

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

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/hw/app_vhwManagerTbl.cpp

            /*
             * app_pphManagerTbl.cpp
             *
             *  Created on: Jun, 27 2024
             *      Author: Marco Dau

                see the mcuPinPort.h to know how to compose the PORT and PIN #define name
                MCU_<port function name>_PORT
                MCU_<port function name>_PIN

             */

            #include "vhwManagerTbl.h"

            #include "app_pphDef_Buttons.h"
            #include "app_pphDef_Leds.h"
            #include "app_pphDef_Mod1.h"
            #include "app_pphDef_ModCmmn.h"

            extern pphButton_t pph_BUTTON_UP;

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

        // app_mcuPinPortDefineConfig
            #define USART_INSTANCE_ID_4     4
            #define USART_PARAMS_4          k_hw0Usart_t::ch_1
            #define HW_USART_INIT_PARAMS_DEF     { 4, k_hw0Usart_t::ch_1 }


            #define MCU_BUTTON_SW2_ISP2         

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/pph/app_pphDef_Mod1.cpp
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


            hwUsartInitParams_t glo_usartParams_1       = {2  ,k_hw0Usart_t::ch_1};
            hwUsartInitParams_t glo_usartParams_2Dbg    = {1  ,k_hw0Usart_t::ch_1};
            PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1      ,glo_usartParams_1           )
            PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1_DBG  ,glo_usartParams_2Dbg        )

    // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/tbl/app_hwManagerTbl.cpp
            /*
             * app_pphManagerTbl.cpp
             *
             *  Created on: Jun, 27 2024
             *      Author: Marco Dau
             */

            #include "hwManagerTbl.h"
            #include "app_pphDef_ModCmmn.h"
            #include "app_pphDef_Mod_nxp.h"
            #include "app_cmmn_pphDef_Buttons.h"
            #include "app_cmmn_pphDef_Leds.h"

            hw2ProxCmmn_t*  hwManagerTbl_t::UnitPtrArray[]   = {
                // &PPH_OBJ   (USART_1_REAL)
                 &PPH_OBJ   (USART_2_REAL)
                ,&PPH_OBJ   (BUTTON_SW2_ISP2)
                ,&PPH_OBJ   (BUTTON_SW3_ISP1)
                ,&PPH_OBJ   (BUTTON_SW4_ISP0)
                ,&PPH_OBJ   (BUTTON_SW5_USER)
                // ,&PPH_OBJ   (LED_LED1_D12)
                // ,&PPH_OBJ   (LED_LED2_D11)
                // ,&PPH_OBJ   (LED_LED3_D9 )
                ,nullptr
            };

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h
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

            using namespace fw2::fnct::base::hw;


            // usart configuration registers
            // step 1 - Determmine the usart pins 
            #define DEMO_MARCO_USART_RX_PORT           3      // FUNC3 - FC4_RXD_SDA_MOSI       // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
            #define DEMO_MARCO_USART_RX_PIN            26                               // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
            #define DEMO_MARCO_USART_TX_PORT           3      // FUNC3 - FC4_TXD_SCL_MISO       // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
            #define DEMO_MARCO_USART_TX_PIN            27                               // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
            // in FC4_RXD_SDA_MOSI & FC4_TXD_SCL_MISO, FC4 stands for FlexComm4 (therefore FLEXCOMM_ID is 4) 
            // to detertmine REG_PTR for FLEXCOMM4 / USART4 
            //      see Fig. 2 - Main Memory Map pag. 21 (UM10912 User Manual) from 0x4008 A000 to 0x4008 B000 &
            //      see "LPC54608.h" at line 14186
            //      to know the offset registers respect base address 0x4008 A000 about FLEXCOMM4 / USART4 - see Tab. 429 pag. 383 (UM10912 User Manual)
            // to detertmine CLOCK_ATTACH see Table 118 pag. 93 (UM10912 User Manual)


            // step 2 - determine usart registers based on rx/tx pins
            /* see Table 118 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h) */
            #define DEMO_MARCO_USART_FLEXCOMM_ID            4                       
            #define DEMO_MARCO_USART_REG_PTR                USART4                  /* see Table 422 & 429 (UM10912 User Manual)    & USART_Type struct  (LPC54608.h) */
            #define DEMO_MARCO_USART_CLOCK_ATTACH           kFRO12M_to_FLEXCOMM4    /* see Table 118 & 157 (UM10912 User Manual)    & SYSCON_Type (LPC54608.h) - typedef enum _clock_attach_id (fsl_clock.h) */
            #define DEMO_MARCO_USART_CLK_FREQ               CLOCK_GetFlexCommClkFreq(DEMO_MARCO_USART_FLEXCOMM_ID)
            #define DEMO_MARCO_USART_IRQn                   FLEXCOMM4_IRQn          /* see Table B1-4 (**DDI0403E_e_armv7m_arm.pdf** *pg B1-525*) & typedef enum IRQn USART_Type struct  (LPC54608.h) */
            #define DEMO_MARCO_USART_NVIC_PRIO              5

            // step 3 - configure interrupt
            // LPC54608.h
            // to understand "typedef enum IRQn" & FLEXCOMM4_IRQn defined at line 106 in LPC54608 see 
            //      - Table 89 (Register overview: NVIC (base address 0xE000 E000)) pag. 74 (UM10912 User Manual)
            //      - Fig. 2 Main Memory Map pag. 21 (UM10912 User Manual) from 0xE000 E000 ()
            //          - N.B.: The NVIC registers are located on the ARM private peripheral bus.
            //      - Table 90 (Interrupt Set-Enable Register 0) ISER0 register
            //      - "void (* const g_pfnVectors[])(void)" defined at line 237 of startup_lpc54608.cpp
            //      - Table 88. Connection of interrupt sources to the NVIC
            //      - Table B1-4 Exception numbers & Table B1-5 Vector table format pag. B1-523 (DDI0403E_e_armv7m_arm.pdf - arm = Architecture Reference Manual)
            //          - /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/docs/nxp/lpcxpresso54608D/getting_start/micro_manuals/MPU/DDI0403E_e_armv7m_arm.pdf

            //      - Figure 3-1 System address map pag. 3-14 (DDI0439B_cortex_m4_r0p0_trm.pdf - trm = Technical Reference Manual)
            //          - /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/docs/nxp/lpcxpresso54608D/getting_start/micro_manuals/MPU/arm_cortexm4_processor_trm_100166_0001_04_en.pdf

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


            #define ICON_FUNC_03            IOCON_PIO_FUNC3
            #define USART_RX_PIN            DEMO_MARCO_USART_RX_PIN         // 26
            #define USART_RX_PORT           DEMO_MARCO_USART_RX_PORT        // 3
            #define USART_TX_PIN            DEMO_MARCO_USART_TX_PIN         // 27
            #define USART_TX_PORT           DEMO_MARCO_USART_TX_PORT        // 3
            #define USART4_RS485_EN         true                            // true
            #define RS485_RE_PIN            APP_BOARD_MARCO_TEST_LED3_PIN   // 2
            #define RS485_RE_PORT           APP_BOARD_MARCO_TEST_LED3_PORT  // 2
            #define RS485_DE_PIN            APP_BOARD_MARCO_TEST_LED2_PIN   // 3
            #define RS485_DE_PORT           APP_BOARD_MARCO_TEST_LED2_PORT  // 3

            // ***********


            // class hw0UsartRs485ParamsReal_t: public hw0UsartRs485Params_t {
            // 
            //     public:
            //         void    clrTxEnablePin      (void) override;
            //         void    setRxEnablePin      (void) override;
            //         void    setTxEnablePin      (void) override;
            //         void    clrRxEnablePin      (void) override;
            // 
            // 
            // };

            #define MCU_USART_1_REAL
            #define MCU_USART_2_REAL

            #define HW_USART_INIT_PARAMS_DEF    {   \
                                                     DEMO_MARCO_USART_FLEXCOMM_ID    \
                                                    ,DEMO_MARCO_USART_REG_PTR        \
                                                    ,DEMO_MARCO_USART_CLOCK_ATTACH   \
                                                    ,DEMO_MARCO_USART_IRQn           \
                                                    ,DEMO_MARCO_USART_NVIC_PRIO      \
                                                    ,ICON_FUNC_03                    \
                                                    ,USART_RX_PIN                    \
                                                    ,USART_RX_PORT                   \
                                                    ,USART_TX_PIN                    \
                                                    ,USART_TX_PORT                   \
                                                    ,USART4_RS485_EN                 \
                                                    ,RS485_RE_PIN                    \
                                                    ,RS485_RE_PORT                   \
                                                    ,RS485_DE_PIN                    \
                                                    ,RS485_DE_PORT                   \
                                                }


            #endif 	// APP_MCU_PIN_PORT_DEFINE_CONFIG_H

        // appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_pphDef_Mod_nxp.cpp
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
             * app_app_pphDef_nxp.cpp
             *
             *  Created on: Apr, 22nd 2026 (Thu)
             *      Author: Marco Dau
             */


            #include "app_pphDef_Mod_nxp.h"


            #define USART0_FLEXCOMM_ID  0
            #define HW_USART_1_INIT_PARAMS_DEF    {   \
                                                     USART0_FLEXCOMM_ID                             /*  USART_FLEXCOMM_ID   */   \
                                                    ,USART0                                         /* ,USART_REG_PTR       */   \
                                                    ,kFRO12M_to_FLEXCOMM0                           /* ,USART_CLOCK_ATTACH  */   \
                                                    ,FLEXCOMM0_IRQn                                 /* ,USART_IRQn          */   \
                                                    ,5                                              /* ,USART_NVIC_PRIO     */   \
                                                    ,IOCON_PIO_FUNC1                                /* ,IOCON_PIO_FUNC1     */   \
                                                    ,29                                             /* ,USART_RX_PIN        */   \
                                                    ,0                                              /* ,USART_RX_PORT       */   \
                                                    ,30                                             /* ,USART_TX_PIN        */   \
                                                    ,0                                              /* ,USART_TX_PORT       */   \
                                                    ,false                                          /* ,USART_RS485_EN      */   \
                                                    ,2                                              /* ,RS485_RE_PIN        */   \
                                                    ,2                                              /* ,RS485_RE_PORT       */   \
                                                    ,3                                              /* ,RS485_DE_PIN        */   \
                                                    ,3                                              /* ,RS485_DE_PORT       */   \
                                                }

            hwUsartInitParams_t glo_usartParams_1Real    = HW_USART_1_INIT_PARAMS_DEF;
            PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1_REAL ,glo_usartParams_1Real        )




    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/apps/mpfw_code_apps_tst_20230810app
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // apps/mpfw_code_apps_tst_20230810app/wsp/xpresso/tst_20230810app/.cproject

    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/cmake/mpfw_fw2_cmake
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // cmake/mpfw_fw2_cmake/v_03/toolchain/nxp/link_script/rls/LPC54608_tst_freertos_Release_library.ld
        GROUP (
          "libgcc.a"
          "libc_nano.a"
          "libstdc++_nano.a"
          "libm.a"
          "libcr_newlib_nohost.a"
          "crti.o"
          "crtn.o"
          "crtbegin.o"
          "crtend.o"
        -->  "libpower_hardabi.a"
        )


    // cmake/mpfw_fw2_cmake/v_03/toolchain/nxp/link_option.cmake
        target_link_options(${EXECUTABLE} PRIVATE
            --> -L${TRDP-SDK-NXP-0TRDP_cmmn_EXT_LIB_DIR_FROM_BUILD} 
            -nostdlib 
            -Wl,-Map=${PROJECT_NAME}.map
            -Wl,--gc-sections
            -Wl,-print-memory-usage
            -Wl,--sort-section=alignment
            -Wl,--cref
            -mcpu=cortex-m4
            -mfpu=fpv4-sp-d16
            -mfloat-abi=hard
            -mthumb
            -T LPC54608_tst_freertos.ld
            --> ## -l:libpower_hardabi.a   # questa opzione è ininfluente, sembra venga ignorata dal linker perchè inserita prima della lista dei file oggetto nel comando di link (arm-none-eabi-ld), vedere il file "... CMakeFiles/TestMarco_cmake.out.dir/link.txt"
            --> ##                         # per poter inserire questa opzione come ultima del comando di link bisogna usare "target_link_libraries"
        )

        --> ## target_link_libraries(${EXECUTABLE} PRIVATE
        --> ##     :libpower_hardabi.a
        --> ## )


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/base/layer/mpfw_fw2-fnct-base-0abst
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // fnct/base/layer/mpfw_fw2-fnct-base-0abst/src/hw/com/comBufferInterface/v_01/comBufferInterface.h
        virtual void        setBufferStatusFree                 (void)                                      = 0;
        --> virtual bool        getBufferStatusFree                 (void)                                      = 0;

        // receiver
        virtual void        rx_interrupt_buffer_management      (void)                                      = 0;

    // fnct/base/layer/mpfw_fw2-fnct-base-0abst/src/sys/sysDebug/v_00/sysDebugModuleDefine.h
        // appl_app20250424_4appl
        -->    // #define     DEBUG_DEF_APP_MANAGER_CMMN_CPP

        // fnct_core_3real
            // #define     DEBUG_DEF_UY_PROTOCOL_CPP



    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0GpioDgIntfc/v_00/hw0GpioDgIntfc.h
        static void         pinWrite        (uint8_t  p_Port,      uint32_t p_pin, uint8_t p_status)    ;

        --> virtual uint32_t    pinRead         (void) {return 0;}                              ;
        --> virtual void        pinWrite        ([[maybe_unused]] uint8_t p_status) {}          ;
        --> virtual void        pinInit         (void) {}                                       ;
        --> 
        --> virtual void        pinConfig       ([[maybe_unused]] uint8_t  p_Port,      [[maybe_unused]] uint8_t p_pin, [[maybe_unused]] gpio_config_struct_t& p_config) {};
        virtual void        setHigh         (void)                                                                  = 0;

    // fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0GpioIntfc/v_00/hw0GpioIntfc.h
        --> enum k_modePort_t: uint8_t   {
            ...
        }
    // fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0UsartIntfc/v_00/hw0UsartIntfc.h
        // receive
        --> virtual bool    rx_chkInterruptRaised   (void)            = 0;
        virtual bool    rx_chkError_overrun     (void)            = 0;

    // fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0UsartRs485Params/v_00/hw0UsartRs485Params.h
        class hw0UsartRs485Params_t {
        
            public:
                virtual void    setTxEnablePin      (void)  = 0;
                virtual void    clrTxEnablePin      (void)  = 0;
                virtual void    setRxEnablePin      (void)  = 0;
                virtual void    clrRxEnablePin      (void)  = 0;
        --> (removed row)
        };


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/core/layer/mpfw_fw2-fnct-core-3real
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // fnct/core/layer/mpfw_fw2-fnct-core-3real/src/com/comBufferStatus/v_00/comBufferStatus.h/.cpp
        // .h
            bool        getBufferStatusFree                 (void)                                      override;

        // .cpp
            bool        comBufferStatus_t::getBufferStatusFree      (void)  {
                return (k_state_t::free == g_state);
            }


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuPinPort/v_02/mcuPinPort.h/.cpp
        // .h
            mcuPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir  );
            
            ...

            uint8_t g_dir;

        // .cpp

            // ****************************************************
            // section start **** CONSTRUCTOR *****

                --> mcuPinPort_t::mcuPinPort_t(                 uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
                -->      g_ptrPort      {&g_ptrPortArray[p_port]}
                -->     ,g_mcuIdOwner   {MCU_DEVICE_DEFAULT}
                -->     ,g_ptrShmPort   {nullptr}
                -->     ,g_port         {p_port}
                -->     ,g_pin          {p_pin}
                -->     ,g_dir          {p_dir}
                -->     // ,g_dtyStatus    {&g_status}
                --> {
                -->     g_config.mode = static_cast<k_modePort_t>(p_dir);
                --> }

                mcuPinPort_t::mcuPinPort_t(uint8_t p_mcuId, uint8_t  p_port, uint8_t p_pin, const gpio_config_struct_t& p_config) :
                     g_ptrPort      {&g_ptrPortArray[p_port]}
                    ,g_config       {p_config}
                    ,g_mcuIdOwner   {p_mcuId}
                    ,g_ptrShmPort   {nullptr}
                    ,g_port         {p_port}
                    ,g_pin          {p_pin}
                    // ,g_dtyStatus    {&g_status}
                {}

    // fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuUsartRs485/v_05/mcuUsartRs485.h
        // .h
            --> // receive
            -->     bool    rx_chkInterruptRaised   (void)            override;

        // .cpp
            // receive
            -->    bool    mcuUsartRs485_t::rx_chkInterruptRaised    (void)             {
            -->        // return !shmMcuUsart_t::pidMatches();
            -->        return !pidMatches();    // derived from shmMcuUsart_t
            -->    }

                bool    mcuUsartRs485_t::rx_chkError_overrun   (void)                         {
                    ...
                }
    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

        // fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp/src/drivers/v_07/mcu/mcuPinPort/v_00/mcuPinPort.h/.cpp
            // .h

                // ****************************************************
                // section start **** CLASS DEFINITION *****

                class mcuPinPort_t :    public     hw0GpioDgIntfc_t    // (all platforms)     - component interface
                {
                
                
                // ****************************************************
                // section start **** CONSTRUCTOR *****
                    public:

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

                        gpio_config_struct_t g_config;
                        uint8_t g_valuePinOld;
                        bool    g_valueModified;

                    private:

                    // section end   **** PIN PORT MANAGEMENT *****
                    // ****************************************************
                    // --------------------------



                };
            // .cpp
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

        // fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp/src/drivers/v_07/mcu/mcuUsartRs485/v_00/mcuUsartRs485.h/.cpp
            // .h
                class mcuUsartRs485_t :  public hw0UsartIntfc_t
                {
                    public:

                        mcuUsartRs485_t  (USART_Type* p_usartRegs, hw0UsartRs485Params_t* p_pConfig);

                        // general
                            bool    chkInterruptsRaised     (void)                      override ;
                        // transmit
                            bool    tx_chkInterruptRaised   (void)                      override ;
                            void    tx_eventBegin           (void)                      override ;
                            void    tx_eventFirstData       (void)                      override ;
                            void    tx_eventSendData        (uint8_t p_data)            override ;
                            void    tx_eventLastData        (void)                      override ;
                            void    tx_eventEnd             (void)                      override ;

                        // receive

                            bool    rx_chkInterruptRaised   (void)                      override ;
                            bool    rx_chkError_overrun     (void)                      override ;
                            void    rx_eventBegin           (void)                      override ;
                            uint8_t rx_eventReceiveData     (void)                      override ;
                            void    rx_eventEnd             (void)                      override ;

                    protected:
                        hw0UsartRs485Params_t*  g_pConfig;


                    private:

                        USART_Type*                 g_pUsartRegs;

                };

            // .cpp

                        // DIS-able tx interrupt
                        g_pUsartRegs->FIFOINTENCLR = USART_FIFOINTENCLR_TXLVL_MASK;
                        //      . DIS-able "last byte completely sent"/"tx idle" interrupt
                        g_pUsartRegs->INTENCLR |= USART_INTENCLR_TXIDLECLR_MASK;
                    }

                // receive
                    bool    mcuUsartRs485_t::rx_chkInterruptRaised     (void)    {
                        return  (
                                    (0U != (g_pUsartRegs->FIFOSTAT & USART_FIFOSTAT_RXNOTEMPTY_MASK))       // RX INTERRUPT
                                ||  (0U != (g_pUsartRegs->FIFOSTAT & USART_FIFOSTAT_RXERR_MASK))            // RX INTERRUPT overrun error
                                );
                    }




    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // common
    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/common/src/hw/v_00/hw2UsartCmmn/v_03/hw2UsartCmmn.h
        // .h
            class hw2UsartCmmn_t:   public comBufferStatus_t
            {
            
                public:
                    hw2UsartCmmn_t  (hw0UsartIntfc_t* p_pChannel, comProtocolInterface_t* p_pProto);

                    uint8_t*    rxBuff_getPtr               (void);
                    uint8_t*    rxBuff_getPtrCleaned        (void);
                    uint8_t     rxBuff_getLenghtCleaned     (void);
                    uint8_t     rx_packetCheck              (void);

                    static void interruptHandler_00  (hw2UsartCmmn_t* p_this);
                    static void interruptHandler_0  (void* p_this);

                protected:
                    void interruptHandler           (void);
                    hw0UsartIntfc_t* g_pChannel;
                    uint8_t g_data_rx;


                private:
                    uint8_t g_rxBuff[HW_2_USART_CMMN_RX_BUFFER_SIZE];
            };

        // .cpp
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
             * hw2UsartCmmn.cpp
             *
             *  Created on: Feb, 22nd 2025 (Sun)
             *      Author: Marco Dau
             */

            // module include
            #include "hw2UsartCmmn.h"

            #include "comBufferStatus_dbgSetup.h"

                hw2UsartCmmn_t::hw2UsartCmmn_t  (hw0UsartIntfc_t* p_pChannel, comProtocolInterface_t* p_pProto):  
                     comBufferStatus_t       (p_pChannel, p_pProto)
                    ,g_pChannel              {p_pChannel}
                {
                    g_pChannel              = p_pChannel;
                }


                uint8_t*    hw2UsartCmmn_t::rxBuff_getPtr       (void)       {
                    return g_rxBuff;
                }

                uint8_t*    hw2UsartCmmn_t::rxBuff_getPtrCleaned        (void)  {
                    return  g_rxBuff + getBufferFirstDirtyBytes();
                }

                uint8_t     hw2UsartCmmn_t::rxBuff_getLenghtCleaned     (void)  {
                    return  getBufferLengthCleaned();
                }

                uint8_t     hw2UsartCmmn_t::rx_packetCheck   (void)      {
                    return rx_packetReceived(g_rxBuff, HW_2_USART_CMMN_RX_BUFFER_SIZE) ? getBufferLength() : 0;
                }



                void        hw2UsartCmmn_t::interruptHandler_00      (hw2UsartCmmn_t* p_this)   {
                    p_this->interruptHandler();
                    // p_this->g_pChannel->rx_eventEnd();
                    // p_this->g_pChannel->tx_eventEnd();
                }

                void        hw2UsartCmmn_t::interruptHandler_0      (void* p_this)   {
                
                    // if(nullptr == static_cast<hw2UsartCmmn_t*>(p_this)->g_pChannel)
                    //     static_cast<hw2UsartCmmn_t*>(p_this)->g_pChannel = static_cast<hw0UsartIntfc_t*>(p_this);

                    // static_cast<hw2UsartCmmn_t*>(p_this)->interruptHandler();

                    static_cast<hw2UsartCmmn_t*>(p_this)->g_pChannel->rx_eventEnd();
                    static_cast<hw2UsartCmmn_t*>(p_this)->g_pChannel->tx_eventEnd();

                }

                void        hw2UsartCmmn_t::interruptHandler        (void)	{
                    // return;
                	/*  =================================================
                        "virtual" case description
                        --------------------------
                            check shared memory buffer status
                            check the "lock" status of the virtual serial comunication channel:
                            if shm buffer is locked means that a process is sending a packet and hence 
                            1. a byte must be read
                            2. or the byte that was written/sent has been read/received from all processes, therefore
                               the writer/tx process can send another byte (standard tx interrupt) or 
                               close the transmission releasing/unlocking the shared memory buffer (completely send byte tx interrupt)

                            N.B.: only one process at time can write to
                        ================================================= */
                	if(g_pChannel->chkInterruptsRaised())	{
                        // INTERRUPT TRIGGER of "Receive byte"/"rx overrun error" or "Send byte"/"Last byte phisically send"

                		// write/read procedure is on
                    	if(g_pChannel->tx_chkInterruptRaised())	{
                            // "virtual" case
                			//      . the current process is the process that write/add data to packet buffer
                			//        and all processes have read the previous data sent
                            //      . it is equivalent to the "real" case tx interrupt 
                            // "real" case
                            //      . the tx interrupt is raised; it means that some data has to be sent
                			// therefore ...

                            tx_interrupt_buffer_management();

                		} 
                        if(g_pChannel->rx_chkInterruptRaised()) {
                            // "virtual" case
                			//      . the current process is not the process that add data to shared memory buffer (that simulates the packet buffer)
                            //      . it is equivalent to the "real" case tx interrupt 
                            // "real" case
                            //      . the rx interrupt is raised; it means that a packet is being received

                            rx_interrupt_buffer_management();
                            // g_data_rx = g_pChannel->rx_eventReceiveData();
                            // g_pChannel->rx_eventEnd();
                		}

                        // g_data_rx = g_pChannel->rx_eventReceiveData();
                        // g_pChannel->rx_eventEnd();
                	} else {
                        // only "virtual" case
                		// the channel is free:
                        // - no byte received to be managed
                        // - check if there is a new packet to send
                		tx_interrupt_buffer_management();

                	}

                }

    // mac
    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwPinPort/v_01/hwPinPort.h
        // .h
            // for all platforms
                // hwPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, const gpio_config_struct_t& p_config);
                hwPinPort_t  (                   uint8_t  p_port,    uint8_t p_pin, uint8_t p_dir);
            // for the specific platform

        // .cpp
                hwPinPort_t::hwPinPort_t(                 uint8_t  p_port, uint8_t p_pin, uint8_t p_dir) :
                    mcuPinPort_t    (         p_port, p_pin, p_dir)
                {}

            //    hwPinPort_t::hwPinPort_t(                 uint8_t  p_port, uint8_t p_pin, const gpio_config_struct_t& p_config) :
            //        mcuPinPort_t    (         p_port, p_pin, p_config)
            //    {}

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/prox/hw/hwManager/v_01/hwManagerTbl.h
        #endif 	// HW_MANAGER_TBL_H

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/wsp/v_09hw_2/cmake/cpp_files.cmake
            	## ${${CURR_MOD_NAME}_sdk_SRC_DIR}/hw/hwPinPort2/v_${${CURR_MOD_NAME}_hwPinPort2_VER}/hwPinPort2.cpp

    // nxp
    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/config/hw/xxx_usartRs485
        --> removed

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwPinPort/v_01/hwPinPort.h
        // .h
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

                // section end   **** PROCESS MANAGEMENT *****
                // ****************************************************
                // --------------------------
        // .cpp
            // ****************************************************
            // section start **** CONSTRUCTOR *****

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

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwUsartInitParams/v_00/hwUsartInitParams.h
        
        #ifndef     HW_USART_INIT_PARAMS_H_
        #define     HW_USART_INIT_PARAMS_H_

        #include "LPC54608.h"
        #include "pin_mux.h"
        using namespace fw2::fnct::base::hw;

        struct  hwUsartInitParams_t {
        
            uint32_t            flexcomm_id;
            USART_Type*         register_ptr;
            clock_attach_id_t   clock_attach;
            IRQn_Type           irq_n;
            uint32_t            nvic_priority;
            // ----------
            uint8_t             icon_func;
            uint8_t             rx_pin;
            uint8_t             rx_port;
            uint8_t             tx_pin;
            uint8_t             tx_port;
            bool                rs485_enabled;
            uint8_t             RE_pin;
            uint8_t             RE_port;
            uint8_t             DE_pin;
            uint8_t             DE_port;

        };



        #endif  //  HW_USART_INIT_PARAMS_H_

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwUsartRs485/v_01/hwUsartRs485.h
        // .h
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
             * hwUsartRs485.cpp
             *
             *  Created on: Feb, 23rd 2026 (Mon)
             *      Author: Marco Dau
             */


            #ifndef HW_USART_RS485_H_
            #define HW_USART_RS485_H_

            #include "mcuUsartRs485.h"
            #include "hw2ProxCmmn.h"
            #include "hw2UsartCmmn.h"

            #include "hwUsartInitParams.h"


            // (specific platform) - processes (init, loop, end) interface (about virtual platforms)


            class hwUsartRs485_t :   public mcuUsartRs485_t         // (specific platform) - sdk module
                                    ,public hw0UsartRs485Params_t   // (specific platform) - sdk module
                                    ,public hw2ProxCmmn_t           // (all platforms)     - processes (init, loop, end) interface 
                                    ,public hw2UsartCmmn_t          // (all platform)


            {
            
                public:
                    hwUsartRs485_t  (hwUsartInitParams_t* p_pConfig, comProtocolInterface_t* p_pProto);

                    void hwInit (void) override;

                    void    setTxEnablePin      (void) override;
                    void    clrTxEnablePin      (void) override;
                    void    setRxEnablePin      (void) override;
                    void    clrRxEnablePin      (void) override;

                    static hw2UsartCmmn_t* g_usart4_this;

                private:
                    void InitPins_IOCON   (void);
                    void InitPins_GPIO    (void);


                    usart_handle_v2_t g_handle;
                    hwUsartInitParams_t* g_pConfig;
                    bool g_rs485_enabled;

            };



            #endif  //  HW_USART_RS485_H_
        
        // .cpp
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
             * hwUsartRs485.cpp
             *
             *  Created on: Feb, 14th 2026 (Sat)
             *      Author: Marco Dau
             */


            #include "hwUsartRs485.h"
            #include "pin_mux.h"
            #include "fsl_iocon.h"
            #include "fsl_gpio.h"
            #include "clock_config.h"
            #include "comBufferInterface.h"




                hwUsartRs485_t::hwUsartRs485_t(hwUsartInitParams_t* p_pConfig, comProtocolInterface_t* p_pProto)  :
                     mcuUsartRs485_t        (p_pConfig->register_ptr, this)
                    ,hw2UsartCmmn_t         (this, p_pProto)
                    ,g_pConfig              {p_pConfig}
                {}

            // #define DEMO_MARCO_USART_FLEXCOMM_ID            4                       
            // #define DEMO_MARCO_USART_REG_PTR                USART4                  /* see Table 422 & 429 (UM10912 User Manual)    & USART_Type struct  (LPC54608.h) */
            // #define DEMO_MARCO_USART_CLOCK_ATTACH           kFRO12M_to_FLEXCOMM4    /* see Table 118 & 157 (UM10912 User Manual)    & SYSCON_Type (LPC54608.h) - typedef enum _clock_attach_id (fsl_clock.h) */
            // #define DEMO_MARCO_USART_CLK_FREQ               CLOCK_GetFlexCommClkFreq(DEMO_MARCO_USART_FLEXCOMM_ID)
            // #define DEMO_MARCO_USART_IRQn                   FLEXCOMM4_IRQn          /* see Table B1-4 (**DDI0403E_e_armv7m_arm.pdf** *pg B1-525*) & typedef enum IRQn USART_Type struct  (LPC54608.h) */
            // #define DEMO_MARCO_USART_NVIC_PRIO              5

                hw2UsartCmmn_t* hwUsartRs485_t::g_usart4_this = nullptr;


                void hwUsartRs485_t::hwInit (void)        {
                    uint8_t l_test = 0;
                    g_usart4_this = this;
                    if(nullptr == hw2UsartCmmn_t::g_pChannel)   {
                        hw2UsartCmmn_t::g_pChannel = this;
                        l_test += 1;
                    }
                    if(nullptr == mcuUsartRs485_t::g_pConfig)    {
                        mcuUsartRs485_t::g_pConfig = this;
                        l_test += 2;
                    }

                    // CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
                    // RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);

                    BOARD_BootClockPLL180M();
            //        CLOCK_AttachClk(g_pConfig->clock_attach);
                    // - step 1
                    //      - configuring pins: tx, rx, rs485-enable-tx, rs485-enable-rx
                    InitPins_IOCON();   // (see Table Table 256 pag. 196 [UM10912_LPC546xx_User_Manual.pdf])
                    InitPins_GPIO();    // (see Table Table 283 pag. 234 [UM10912_LPC546xx_User_Manual.pdf])

                    // - step 2
                    //      - configuring UART module

                    // - step 2.1.a
                    //      - load default configuration
                    //
                    // config.baudRate_Bps = 115200U;
                    // config.parityMode = kUSART_ParityDisabled;
                    // config.stopBitCount = kUSART_OneStopBit;
                    // config.loopback = false;
                    // config.enableTx = false;
                    // config.enableRx = false;
                    //
                    usart_config_t config;
                    USART_GetDefaultConfig(&config);
                    // - step 2.1.b
                    //      - default configuration customization
                    config.baudRate_Bps = 9600;
                    config.enableTx     = true;
                    config.enableRx     = true;


                    // - step 2.2
                    //      - enabling and configuring UART
                    // - step 2.2.a 
                    //      - attach 12 MHz clock to FLEXCOMM4 (USART)
                    // . CLOCK_AttachClk
                    //      . input
                    //          - typedef enum _clock_attach_id / clock_attach_id_t in fsl_clock.h
                    //      . register
                    //          - SYSCON->MAINCLKSELA / SYSCON->FCLKSEL4 (see Table Table 118 & 157 [UM10912_LPC546xx_User_Manual.pdf])
                    CLOCK_AttachClk(g_pConfig->clock_attach);

                    // - step 2.2.b 
                    //      - enable clock and reset/start UART
                    //      - set UART registers based on configuration previously set
                    // . CLOCK_EnableClock(s_flexcommClocks[idx]); 
                    //      . input 
                    //          - typedef enum _clock_ip_name" in fsl_clock.h
                    //      . register
                    //          - SYSCON->AHBCLKCTRLSET register (see Table Table 118 & 140 [UM10912_LPC546xx_User_Manual.pdf])
                    // . RESET_PeripheralReset(s_flexcommResets[idx]);
                    //      . input:
                    //          - typedef enum _SYSCON_RSTn in fsl_reset.h
                    //      . register
                    //          - SYSCON->PRESETCTRL / SYSCON->PRESETCTRLSET / SYSCON->PRESETCTRLCLR (see Table Table 118 & 130 [UM10912_LPC546xx_User_Manual.pdf])
                    uint32_t l_clock_freq = CLOCK_GetFlexCommClkFreq(g_pConfig->flexcomm_id);
                    USART_Init(g_pConfig->register_ptr, &config, l_clock_freq  );

                    uint8_t l_str[] = "**.** Messaggio di test **";
                    l_str[2] = l_test + 0x30;
                    USART_WriteBlocking(g_pConfig->register_ptr, l_str, sizeof(l_str) - 1);
                    // - step 2.2.c
                    //      - enabling and configuring interrupt UART to use a no-blocking tx-rx procedures
                    //
                    //      - set priority interrupt 
                    //  . NVIC_SetPriority
                    //      . inputs
                    //          - typedef enum IRQn / IRQn_Type in LPC54608.h
                    //          - integer in the range of 0...7 (0 max priority / 7 min priority)
                    //      . register
                    //          - NVIC->IP regiter (see Table 89 & 104 [UM10912_LPC546xx_User_Manual.pdf])
                    NVIC_SetPriority(g_pConfig->irq_n, g_pConfig->nvic_priority);

                    //      - set handler of the interrupt
                    //          - hang the "USART_TransferHandleIRQ" function (fsl_uasart.c) to "FLEXCOMM0_DriverIRQHandler" function (fsl_flexcomm.c)
                    //          - N.B.: "FLEXCOMM0_DriverIRQHandler" is called by "FLEXCOMM0_IRQHandler" function (startup_lpc54608.cpp)
                    //          - see Table 88 in [UM10912_LPC546xx_User_Manual.pdf] & Table B1-4 in [DDI0403E_e_armv7m_arm.pdf]
                    // . EnableIRQ
                    //      . input
                    //          - typedef enum IRQn / IRQn_Type in LPC54608.h
                    //      . register
                    //          - NVIC->ISER register (see Table 89 & 90 [UM10912_LPC546xx_User_Manual.pdf])


                    // usart_user_data.pHwUsartIntfc = this;
                    // status_t USART_TransferCreateHandle(USART_Type *base,
                    //                                     usart_handle_t *handle,
                    //                                     usart_transfer_callback_t callback,
                    //                                     void *userData)


                    // USART_TransferCreateHandle_v2(g_pConfig->register_ptr, &g_handle, interruptHandler_0, this);

                    (void)EnableIRQ(FLEXCOMM4_IRQn);

                    // instance = USART_GetInstance(g_pConfig->register_ptr);

                    // uint8_t l_str1[] = "01u|Messaggio di test|";
                    // uint8_t l_str2[] = "01u|Messaggio di test via blocking|";
                    // uint8_t l_str3[] = "*** ERRORE ***";
                    //     setRxEnablePin();
                    //     while(getBufferStatusFree()){};
                    // (void)DisableIRQ(FLEXCOMM4_IRQn);
                    // if(tx_packetSent(l_str1, sizeof(l_str1))) {
                    //     while(!getBufferStatusFree()){};
                    //     // USART_WriteBlocking(g_pConfig->register_ptr, l_str2, sizeof(l_str2) - 1);
                    // } 
                    // else {
                    //    USART_WriteBlocking(g_pConfig->register_ptr, l_str3, sizeof(l_str3) - 1);
                    // }
                /*
                    // status_t USART_TransferCreateHandle(USART_Type *base,
                    //                                     usart_handle_t *handle,
                    //                                     usart_transfer_callback_t callback,
                    //                                     void *userData)

                    // send the first packet 
                    // Tx("rsSerial build.005 - krInitStatic -> UART init OK\r\nOOO");

                */
                }

                void hwUsartRs485_t::InitPins_IOCON (void)      {
                
                    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
                    CLOCK_EnableClock(kCLOCK_Iocon);

                    // *********************************************************************************************************
                    // usart4 RX & TX pin configuration
                    const uint32_t iocon_usart_config = (/* Pin is configured as FC4_RXD_SDA_MOSI */
                                                         g_pConfig->icon_func |              
                                                         /* No addition pin function */
                                                         IOCON_PIO_MODE_INACT |
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
                    /* PORT0 PIN29 (coords: K5) is configured as FC4_RXD_SDA_MOSI */
                    // IOCON_PinMuxSet(IOCON, g_pConfig->rx_port, g_pConfig->rx_pin, iocon_usart_config);
                    IOCON_PinMuxSet(IOCON, g_pConfig->rx_port, g_pConfig->rx_pin, iocon_usart_config);
                    // IOCON_PinMuxSet(IOCON, g_pConfig->tx_port, g_pConfig->tx_pin, iocon_usart_config);
                    IOCON_PinMuxSet(IOCON, g_pConfig->tx_port, g_pConfig->tx_pin, iocon_usart_config);


                    // *********************************************************************************************************


                    if(g_pConfig->rs485_enabled) {
                        const uint32_t iocon_rs485_config = (/* Pin is configured as digital PIN */
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
                        // pin to drive led 2 & max 485-DE
                        /* PORT3 PIN3 (coords: A13) is configured as PIO3_3 */
                        IOCON_PinMuxSet(IOCON, g_pConfig->DE_port, g_pConfig->DE_pin, iocon_rs485_config);
                        // pin to drive led 3 & max 485-RE
                        /* PORT3 PIN3 (coords: C3) is configured as PIO3_3 */
                        IOCON_PinMuxSet(IOCON, g_pConfig->RE_port, g_pConfig->RE_pin, iocon_rs485_config);
                    }


                }

                void hwUsartRs485_t::InitPins_GPIO    (void)      {
                
                    if(g_pConfig->rs485_enabled) {
                        // enable clock & reset peripheral according with the compile time definitions
                        GPIO_PortInit(GPIO, g_pConfig->DE_port);
                        GPIO_PortInit(GPIO, g_pConfig->RE_port);

                        /* Define the init structure for the output LED pin*/
                        gpio_pin_config_t out_config = {
                            kGPIO_DigitalOutput,
                            0,
                        };

                        GPIO_PinInit (GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, &out_config);
                        GPIO_PinInit (GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, &out_config);

                        // rs485 tx enable & rs485 rx disable
                        setTxEnablePin();
                    }
                }

                void    hwUsartRs485_t::setTxEnablePin      (void) {
                    if(g_pConfig->rs485_enabled) {
                        GPIO_PinWrite(GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, 1);
                        GPIO_PinWrite(GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, 1);
                    }
                }

                void    hwUsartRs485_t::clrTxEnablePin      (void) {
                    setRxEnablePin();
                }

                void    hwUsartRs485_t::setRxEnablePin      (void) {
                    if(g_pConfig->rs485_enabled) {
                        GPIO_PinWrite(GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, 0);
                        GPIO_PinWrite(GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, 0);
                    }
                }

                void    hwUsartRs485_t::clrRxEnablePin      (void) {
                    setTxEnablePin();
                }

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/prox/hw/hwManager/v_01/hwManagerTbl.h
        #endif 	// HW_MANAGER_TBL_H

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/wsp/v_09hw_2/cmake/init/no_set_public_dirs.cmake
        --> removed

    // fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/wsp/v_09hw_2/cmake/cpp_files.cmake
        -->         	## ${${CURR_MOD_NAME}_sdk_SRC_DIR}/hw/hwPinPort2/v_${${CURR_MOD_NAME}_hwPinPort2_VER}/hwPinPort2.cpp

    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/hw/layer/mpfw_fw2-fnct-hw-3real
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

    // fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphButton/v_00/pphButton.h
        // .h
            pphButton_t::pphButton_t(uint8_t p_port, uint8_t p_pin)  :
                 hwPinPort_t  (p_port, p_pin, 0 ) // 0 -> input
            {}

        // .cpp
            class pphButton_t : public hwPinPort_t {
            
            public:
                pphButton_t(uint8_t p_port,   uint8_t p_pin);

            };

    // fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphLed/v_02/pphLed.h
        // .h
            class pphLed_t : public hwPinPort_t {
            
            public:
                pphLed_t(uint8_t p_port,   uint8_t p_pin);


            };

        // .cpp
            pphLed_t::pphLed_t(uint8_t p_port, uint8_t p_pin)  :
                 hwPinPort_t  (p_port, p_pin, 1)    // 1 -> output
            {}

    // fnct/hw/layer/mpfw_fw2-fnct-hw-3real/wsp/v_10hw_3/cmake/cpp_files.cmake
        set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_CPP

 		## pph
 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphButton/v_${${CURR_MOD_NAME}_pphButton_VER}/pphButton.cpp
 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphLed/v_${${CURR_MOD_NAME}_pphLed_VER}/pphLed.cpp
            ## 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphManager/v_${${CURR_MOD_NAME}_pphManager_VER}/pphManager.cpp
 	        ## ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphRelay/v_00/pphRelay.cpp
 	        ## ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphSwitch/v_00/pphSwitch.cpp
 	        ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphUsartRs485/v_${${CURR_MOD_NAME}_pphUsartRs485_VER}/pphUsartRs485.cpp
 	        # ${${CURR_MOD_NAME}_SRC_DIR}/pph/v_${${CURR_MOD_NAME}_pph_VER}/pphWired/v_00/pphWired.cpp
    )


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/fnct/tui/layer/mpfw_fw2-fnct-tui-2wrpr-ui
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/libs/mpfw_code_libs_fw2_wrapper_resources
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // libs/mpfw_code_libs_fw2_wrapper_resources/nxp/src/rs/rsSerial/v_06/rsSerial.cpp
            Tx("rsSerial v.06 - 20260728 - krInitStatic -> UART init OK\r\nOOO");

    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/libs/mpfw_code_libs_sdk_stm32f769_disco
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // libs/mpfw_code_libs_sdk_stm32f769_disco/wsp/cube/sdk_stm32f769_disco/.settings/language.settings.xml


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/main/app20250424/layer/mpfw_fw2-main-app20250424-5main
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // main/app20250424/layer/mpfw_fw2-main-app20250424-5main/trdp/sdk/nxp/src/other/startup_lpc54608.cpp
        --> added
    
    // main/app20250424/layer/mpfw_fw2-main-app20250424-5main/trdp/sdk/nxp/wsp/v_16main/cmake/cpp_files.cmake
        -->         ${${CURR_MOD_NAME}_sdk_SRC_DIR}/other/startup_lpc54608.cpp


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/main/mpfw_code_main_tst_20230810main
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // main/mpfw_code_main_tst_20230810main/wsp/xpresso/project/nxp/tst_20230810main/tst_20230810main LinkServer Debug (1).launch
    // main/mpfw_code_main_tst_20230810main/wsp/xpresso/project/nxp/tst_20230810main/tst_20230810main LinkServer Debug (2).launch

    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// --- a/trdp/sdk/nxp/layer/mpfw_fw2-trdp-sdk-nxp-0trdp
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // trdp/sdk/nxp/layer/mpfw_fw2-trdp-sdk-nxp-0trdp/src/v_06/startup/startup_lpc54608.cpp
        --> unused

    // trdp/sdk/nxp/layer/mpfw_fw2-trdp-sdk-nxp-0trdp/wsp/v_34nxp0/cmake/cpp_files.cmake
        set(CODE_FILES_SDK_NXP_C_STARTUP
            --> ## ${LIBS_SDK_PLATFORM_SRC_DIR}/${SDK_NXP_STARTUP_DIR}/startup_lpc54608.cpp
        )


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

................................................
// nome_modulo
    ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~


    ~~~~~~~~~~~~~~~~~~~~~~~~
    ........................

---

Thu  6 Aug 2026 11:25:06 CEST


- file da modificare

........................
// mpfw_fw2-fnct-base_hw-0abst
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0UsartIntfc/v_00/hw0UsartIntfc.h
//      . UN-CHANGED
class hw0UsartIntfc_t {

    public:
        // general
        virtual bool    chkInterruptsRaised     (void)            = 0;
        // transmit
        virtual bool    tx_chkInterruptRaised   (void)            = 0;
        virtual void    tx_eventBegin           (void)            = 0;
        virtual void    tx_eventFirstData       (void)            = 0;
        virtual void    tx_eventSendData        (uint8_t p_data)  = 0;
        virtual void    tx_eventLastData        (void)            = 0;
        virtual void    tx_eventEnd             (void)            = 0;

        // receive
        virtual bool    rx_chkError_overrun     (void)            = 0;
        virtual void    rx_eventBegin           (void)            = 0;
        virtual uint8_t rx_eventReceiveData     (void)            = 0;
        virtual void    rx_eventEnd             (void)            = 0;

};


// fnct/base_hw/layer/mpfw_fw2-fnct-base_hw-0abst/src/hw/hw0UsartRs485Params/v_00/hw0UsartRs485Params.h
//      . UPDATED
//          . "void* g_params; " removed

class hw0UsartRs485Params_t {

    public:
        virtual void    setTxEnablePin      (void)  = 0;
        virtual void    clrTxEnablePin      (void)  = 0;
        virtual void    setRxEnablePin      (void)  = 0;
        virtual void    clrRxEnablePin      (void)  = 0;

};


~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-fnct-hw-1trdp-sdk-nxp
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-nxp/src/drivers/v_07/mcu/mcuUsartRs485/v_00/mcuUsartRs485.h/.cpp

class mcuUsartRs485_t :  public hw0UsartIntfc_t
{
    public:

        mcuUsartRs485_t  (USART_Type* p_usartRegs, hw0UsartRs485Params_t* p_pConfig);
    ...

}

~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-fnct-hw-1trdp-sdk-mac
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuUsartRs485/v_05/mcuUsartRs485.cpp/.h
//      . UN-CHANGED .h & .cpp
// .h
class mcuUsartRs485_t :  public mcuBase_t
                        ,public shmMcuUsart_t
                        ,public hw0UsartIntfc_t
{
    public:

        mcuUsartRs485_t  (                   k_hw0Usart_t p_ch);
        mcuUsartRs485_t  (uint8_t p_pid2,    k_hw0Usart_t p_ch);

    ...

}

// .cpp

    // It is called in an "application thread/routine" when the user has to send a packet 
    // therefore when the buffer status is set to "init"
    void    mcuUsartRs485_t::tx_eventBegin           (void)                         {
        // case "virtual"
        //      . do nothing
        //          N.B.: the interrupt routine is simulated by a "loop" routine (vhwLoop) and it is always performed at every "main" cycle
        // case "real"
        //      1. enable tx interrupt
        //      2. set tx-enable pin (automatically clear rx-enable pin) (Rs485 config)
        g_pUsartRegs->FIFOINTENSET |= USART_FIFOINTENSET_TXLVL_MASK;
        g_pConfig->setTxEnablePin();    // in "virtual" case it doesn't any
    }


~~~~~~~~~~~~~~~~~~~~~~~~
........................


........................
// mpfw_fw2-fnct-hw-2wrpr-sdk
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwUsartInitParams/v_00/hwUsartInitParams.h
//      . UN-CHANGED
struct  hwUsartInitParams_t {

    uint8_t         pid2;
    k_hw0Usart_t    ch;
};

// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/mac/src/hw/hwUsartRs485/v_02/hwUsartRs485.h/cpp
//      . UN-CHANGED
class hwUsartRs485_t :   public mcuUsartRs485_t     // (specific platform) - sdk module 
                        ,public vhw2ProxCmmn_t       // (all virtual platform) - processes (init, loop, end) interface (about virtual platforms)
                        ,public hw2UsartCmmn_t       // (all platform)
{

    public:
        hwUsartRs485_t  (hwUsartInitParams_t* p_pConfig, comProtocolInterface_t* p_pProto);

        void vhwInit (void) override;
        void vhwLoop (void) override;


};


// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/config/hw/usartRs485/hwConfig_hwUsartRs485.h
//      . REMOVED
//          . it is moved in "appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h"
//          . see also "fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/wsp/v_09hw_2/cmake/init/no_set_public_dirs.cmake"
//              . no more own config files

#define DEMO_MARCO_USART_FLEXCOMM_ID            4                       // see Table 118 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
#define DEMO_MARCO_USART_REG_PTR                USART4                  // see Table 422 & 429 (UM10912 User Manual)    & USART_Type struct  (LPC54608.h)
#define DEMO_MARCO_USART_CLOCK_ATTACH           kFRO12M_to_FLEXCOMM4    // see Table 118 & 157 (UM10912 User Manual)    & SYSCON_Type (LPC54608.h) - typedef enum _clock_attach_id (fsl_clock.h)
#define DEMO_MARCO_USART_CLK_FREQ               CLOCK_GetFlexCommClkFreq(DEMO_MARCO_USART_FLEXCOMM_ID)
#define DEMO_MARCO_USART_IRQn                   FLEXCOMM4_IRQn          // see Table B1-4 (**DDI0403E_e_armv7m_arm.pdf** *pg B1-525*) & typedef enum IRQn USART_Type struct  (LPC54608.h)
#define DEMO_MARCO_USART_NVIC_PRIO              5

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


// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwUsartInitParams/v_00/hwUsartInitParams.h
//      . UPDATED

#include "LPC54608.h"
#include "pin_mux.h"
#include "hw0UsartRs485Params.h"
using namespace fw2::fnct::base::hw;

struct  hwUsartInitParams_t {

    uint32_t            flexcomm_id;
    USART_Type*         register_ptr;
    clock_attach_id_t   clock_attach;
    uint32_t            clock_freq;
    IRQn_Type           irq_n;
    uint32_t            nvic_priority;
    // ----------
    uint8_t             icon_func;
    uint8_t             rx_pin;
    uint8_t             rx_port;
    uint8_t             tx_pin;
    uint8_t             tx_port;
    bool                rs485_enabled;
    uint8_t             RE_pin;
    uint8_t             RE_port;
    uint8_t             DE_pin;
    uint8_t             DE_port;

};


// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/src/hw/hwUsartRs485/v_01/hwUsartRs485.h/.cpp
//      . UPDATE .h & .cpp
// .h
#include "mcuUsartRs485.h"
#include "hw2ProxCmmn.h"
#include "hw2UsartCmmn.h"

#include "hwUsartInitParams.h"

 
// (specific platform) - processes (init, loop, end) interface (about virtual platforms)


class hwUsartRs485_t :   public mcuUsartRs485_t         // (specific platform) - sdk module
                        ,public hw0UsartRs485Params_t   // (specific platform) - sdk module
                        ,public hw2ProxCmmn_t           // (all platforms)     - processes (init, loop, end) interface 
                        ,public hw2UsartCmmn_t          // (all platform)

                        
{

    public:
        hwUsartRs485_t  (hwUsartInitParams_t* p_pConfig, comProtocolInterface_t* p_pProto);

        void hwInit (void) override;

        void    setTxEnablePin      (void) override;
        void    clrTxEnablePin      (void) override;
        void    setRxEnablePin      (void) override;
        void    clrRxEnablePin      (void) override;

    private:
        void InitPins_IOCON   (void);
        void InitPins_GPIO    (void);

        
        usart_handle_v2_t g_handle;
        hwUsartInitParams_t* g_pConfig;
        bool g_rs485_enabled;

};


// .cpp

#include "pin_mux.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "comBufferInterface.h"


    hwUsartRs485_t::hwUsartRs485_t(hwUsartInitParams_t* p_pConfig, comProtocolInterface_t* p_pProto)  :
         mcuUsartRs485_t        (p_pConfig->register_ptr, this)
        ,hw2UsartCmmn_t         (this, p_pProto)
        ,g_pConfig              {p_pConfig}
    {}

    void hwUsartRs485_t::hwInit (void)        {
            
        // - step 1
        //      - configuring pins: tx, rx, rs485-enable-tx, rs485-enable-rx
        InitPins_IOCON();   // (see Table Table 256 pag. 196 [UM10912_LPC546xx_User_Manual.pdf])
        InitPins_GPIO();    // (see Table Table 283 pag. 234 [UM10912_LPC546xx_User_Manual.pdf])

        // - step 2
        //      - configuring UART module

        // - step 2.1.a
        //      - load default configuration
        //
        // config.baudRate_Bps = 115200U;
        // config.parityMode = kUSART_ParityDisabled;
        // config.stopBitCount = kUSART_OneStopBit;
        // config.loopback = false;
        // config.enableTx = false;
        // config.enableRx = false;
        //
        usart_config_t config;
        USART_GetDefaultConfig(&config);
        // - step 2.1.b
        //      - default configuration customization
        config.baudRate_Bps = 9600;
        config.enableTx     = true;
        config.enableRx     = true;


        // - step 2.2
        //      - enabling and configuring UART
        // - step 2.2.a 
        //      - attach 12 MHz clock to FLEXCOMM4 (USART)
        // . CLOCK_AttachClk
        //      . input
        //          - typedef enum _clock_attach_id / clock_attach_id_t in fsl_clock.h
        //      . register
        //          - SYSCON->MAINCLKSELA / SYSCON->FCLKSEL4 (see Table Table 118 & 157 [UM10912_LPC546xx_User_Manual.pdf])
        CLOCK_AttachClk(g_pConfig->clock_attach);

        // - step 2.2.b 
        //      - enable clock and reset/start UART
        //      - set UART registers based on configuration previously set
        // . CLOCK_EnableClock(s_flexcommClocks[idx]); 
        //      . input 
        //          - typedef enum _clock_ip_name" in fsl_clock.h
        //      . register
        //          - SYSCON->AHBCLKCTRLSET register (see Table Table 118 & 140 [UM10912_LPC546xx_User_Manual.pdf])
        // . RESET_PeripheralReset(s_flexcommResets[idx]);
        //      . input:
        //          - typedef enum _SYSCON_RSTn in fsl_reset.h
        //      . register
        //          - SYSCON->PRESETCTRL / SYSCON->PRESETCTRLSET / SYSCON->PRESETCTRLCLR (see Table Table 118 & 130 [UM10912_LPC546xx_User_Manual.pdf])
        USART_Init(g_pConfig->register_ptr, &config, g_pConfig->clock_freq  );

        // - step 2.2.c
        //      - enabling and configuring interrupt UART to use a no-blocking tx-rx procedures
        //
        //      - set priority interrupt 
        //  . NVIC_SetPriority
        //      . inputs
        //          - typedef enum IRQn / IRQn_Type in LPC54608.h
        //          - integer in the range of 0...7 (0 max priority / 7 min priority)
        //      . register
        //          - NVIC->IP regiter (see Table 89 & 104 [UM10912_LPC546xx_User_Manual.pdf])
        NVIC_SetPriority(g_pConfig->irq_n, g_pConfig->nvic_priority);

        //      - set handler of the interrupt
        //          - hang the "USART_TransferHandleIRQ" function (fsl_uasart.c) to "FLEXCOMM0_DriverIRQHandler" function (fsl_flexcomm.c)
        //          - N.B.: "FLEXCOMM0_DriverIRQHandler" is called by "FLEXCOMM0_IRQHandler" function (startup_lpc54608.cpp)
        //          - see Table 88 in [UM10912_LPC546xx_User_Manual.pdf] & Table B1-4 in [DDI0403E_e_armv7m_arm.pdf]
        // . EnableIRQ
        //      . input
        //          - typedef enum IRQn / IRQn_Type in LPC54608.h
        //      . register
        //          - NVIC->ISER register (see Table 89 & 90 [UM10912_LPC546xx_User_Manual.pdf])


        // usart_user_data.pHwUsartIntfc = this;
        // status_t USART_TransferCreateHandle(USART_Type *base,
        //                                     usart_handle_t *handle,
        //                                     usart_transfer_callback_t callback,
        //                                     void *userData)

    
        USART_TransferCreateHandle_v2(g_pConfig->register_ptr, &g_handle, interruptHandler_0, this);
    /*
        // status_t USART_TransferCreateHandle(USART_Type *base,
        //                                     usart_handle_t *handle,
        //                                     usart_transfer_callback_t callback,
        //                                     void *userData)

        // send the first packet 
        // Tx("rsSerial build.005 - krInitStatic -> UART init OK\r\nOOO");

    */
    }


    void hwUsartRs485_t::InitPins_IOCON (void)      {
    
        /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
        CLOCK_EnableClock(kCLOCK_Iocon);
    
        // *********************************************************************************************************
        // usart4 RX & TX pin configuration
        const uint32_t iocon_usart_config = (/* Pin is configured as FC4_RXD_SDA_MOSI */
                                             g_pConfig->icon_func |
                                             /* No addition pin function */
                                             IOCON_PIO_MODE_INACT |
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
        /* PORT0 PIN29 (coords: K5) is configured as FC4_RXD_SDA_MOSI */
        IOCON_PinMuxSet(IOCON, g_pConfig->rx_port, g_pConfig->rx_pin, iocon_usart_config);
        IOCON_PinMuxSet(IOCON, g_pConfig->tx_port, g_pConfig->tx_pin, iocon_usart_config);
    
    
        // *********************************************************************************************************

        
        if(g_pConfig->rs485_enabled) {
            const uint32_t iocon_rs485_config = (/* Pin is configured as digital PIN */
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
            // pin to drive led 2 & max 485-DE
            /* PORT3 PIN3 (coords: A13) is configured as PIO3_3 */
            IOCON_PinMuxSet(IOCON, g_pConfig->DE_port, g_pConfig->DE_pin, iocon_rs485_config);
            // pin to drive led 3 & max 485-RE
            /* PORT3 PIN3 (coords: C3) is configured as PIO3_3 */
            IOCON_PinMuxSet(IOCON, g_pConfig->RE_port, g_pConfig->RE_pin, iocon_rs485_config);
        }
    
   
    }

    void hwUsartRs485_t::InitPins_GPIO    (void)      {

        if(g_pConfig->rs485_enabled) {
            // enable clock & reset peripheral according with the compile time definitions
            GPIO_PortInit(GPIO, g_pConfig->DE_port);
            GPIO_PortInit(GPIO, g_pConfig->RE_port);

            /* Define the init structure for the output LED pin*/
            gpio_pin_config_t out_config = {
                kGPIO_DigitalOutput,
                0,
            };

            GPIO_PinInit (GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, &out_config);
            GPIO_PinInit (GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, &out_config);

            // rs485 tx enable & rs485 rx disable
            setTxEnablePin();
        }
    }

    void    hwUsartRs485_t::setTxEnablePin      (void) {
        if(g_pConfig->rs485_enabled) {
            GPIO_PinWrite(GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, 1);
            GPIO_PinWrite(GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, 1);
        }
    }

    void    hwUsartRs485_t::clrTxEnablePin      (void) {
        setRxEnablePin();
    }

    void    hwUsartRs485_t::setRxEnablePin      (void) {
        if(g_pConfig->rs485_enabled) {
            GPIO_PinWrite(GPIO, g_pConfig->DE_port, g_pConfig->DE_pin, 0);
            GPIO_PinWrite(GPIO, g_pConfig->RE_port, g_pConfig->RE_pin, 0);
        }
    }

    void    hwUsartRs485_t::clrRxEnablePin      (void) {
        setTxEnablePin();
    }

// fnct/hw/layer/mpfw_fw2-fnct-hw-2wrpr-sdk/trdp/sdk/nxp/wsp/v_09hw_2/cmake/init/set_public_dirs.cmake
//      . REMOVED (moved in "no_set_public_dirs.cmake" file)


~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-fnct-hw-3real
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// fnct/hw/layer/mpfw_fw2-fnct-hw-3real/src/pph/v_03/pphUsartRs485/v_00/pphUsartRs485.h/.cpp
//      . UN-CHANGED

class pphUsartRs485_t :   public hwUsartRs485_t
{

    public:
        pphUsartRs485_t  (hwUsartInitParams_t* p_pConfig);

        int16_t send           (uint8_t* p_buffPtr);

    private:
        comProtocolStatus_t g_proto;
};

~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// mpfw_fw2-appl-app20250424-4appl
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

// appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/src/instances/hw/units/app_pphDef_ModCmmn.cpp/.h
//      . UPDATED only .cpp

// .cpp
// ------ hwUsartInitParams_t glo_usartParams_2Real    = {USART_INSTANCE_ID_4  ,USART_PARAMS_4};
hwUsartInitParams_t glo_usartParams_2Real    = HW_USART_INIT_PARAMS_DEF;
PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_2_REAL  ,glo_usartParams_2Real        )

// .h
extern PPH_DEF_H__(pphUsartRs485_t,  USART_2_REAL )


// appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/pph/app_mcuPinPortDefineConfig.h
//      . UPDATED

#define MCU_USART_1
#define MCU_USART_1_DBG
#define MCU_USART_1_REAL
#define MCU_USART_2_REAL

// ---- #define USART_INSTANCE_ID_4     4
// ---- #define USART_PARAMS_4          k_hw0Usart_t::ch_1
#define HW_USART_INIT_PARAMS_DEF     { 4, k_hw0Usart_t::ch_1 }

// appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/pph/app_pphDef_Mod1.cpp/.h
//      . UPDATE only .cpp
// .h
extern PPH_DEF_H__(pphUsartRs485_t,  USART_1     )
extern PPH_DEF_H__(pphUsartRs485_t,  USART_1_DBG )

// .cpp
hwUsartInitParams_t glo_usartParams_1       = {2  ,k_hw0Usart_t::ch_1};
hwUsartInitParams_t glo_usartParams_2Dbg    = {1  ,k_hw0Usart_t::ch_1};
PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1      ,glo_usartParams_1           )
PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1_DBG  ,glo_usartParams_2Dbg        )


// appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h
//      . UPDATED heavily
#ifndef APP_MCU_PIN_PORT_DEFINE_CONFIG_H
#define APP_MCU_PIN_PORT_DEFINE_CONFIG_H

#include "LPC54608.h"
#include "hw0UsartRs485Params.h"

using namespace fw2::fnct::base::hw;


// usart configuration registers
// step 1 - Determmine the usart pins 
#define DEMO_MARCO_USART_RX_PORT           3      // FUNC3 - FC4_RXD_SDA_MOSI       // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
#define DEMO_MARCO_USART_RX_PIN            26                               // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
#define DEMO_MARCO_USART_TX_PORT           3      // FUNC3 - FC4_TXD_SCL_MISO       // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
#define DEMO_MARCO_USART_TX_PIN            27                               // see sheet 4 (LPC54608_Dev_brd_schematic_Rev-D_170614.pdf)  &  Table 256 pag. 196 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h)
// in FC4_RXD_SDA_MOSI & FC4_TXD_SCL_MISO, FC4 stands for FlexComm4 (therefore FLEXCOMM_ID is 4) 
// to detertmine REG_PTR for FLEXCOMM4 / USART4 
//      see Fig. 2 - Main Memory Map pag. 21 (UM10912 User Manual) from 0x4008 A000 to 0x4008 B000 &
//      see "LPC54608.h" at line 14186
//      to know the offset registers respect base address 0x4008 A000 about FLEXCOMM4 / USART4 - see Tab. 429 pag. 383 (UM10912 User Manual)
// to detertmine CLOCK_ATTACH see Table 118 pag. 93 (UM10912 User Manual)


// step 2 - determine usart registers based on rx/tx pins
/* see Table 118 (UM10912 User Manual)          & SYSCON_Type struct (LPC54608.h) */
#define DEMO_MARCO_USART_FLEXCOMM_ID            4                       
#define DEMO_MARCO_USART_REG_PTR                USART4                  /* see Table 422 & 429 (UM10912 User Manual)    & USART_Type struct  (LPC54608.h) */
#define DEMO_MARCO_USART_CLOCK_ATTACH           kFRO12M_to_FLEXCOMM4    /* see Table 118 & 157 (UM10912 User Manual)    & SYSCON_Type (LPC54608.h) - typedef enum _clock_attach_id (fsl_clock.h) */
#define DEMO_MARCO_USART_CLK_FREQ               CLOCK_GetFlexCommClkFreq(DEMO_MARCO_USART_FLEXCOMM_ID)
#define DEMO_MARCO_USART_IRQn                   FLEXCOMM4_IRQn          /* see Table B1-4 (**DDI0403E_e_armv7m_arm.pdf** *pg B1-525*) & typedef enum IRQn USART_Type struct  (LPC54608.h) */
#define DEMO_MARCO_USART_NVIC_PRIO              5

// step 3 - configure interrupt
// LPC54608.h
// to understand "typedef enum IRQn" & FLEXCOMM4_IRQn defined at line 106 in LPC54608 see 
//      - Table 89 (Register overview: NVIC (base address 0xE000 E000)) pag. 74 (UM10912 User Manual)
//      - Fig. 2 Main Memory Map pag. 21 (UM10912 User Manual) from 0xE000 E000 ()
//          - N.B.: The NVIC registers are located on the ARM private peripheral bus.
//      - Table 90 (Interrupt Set-Enable Register 0) ISER0 register
//      - "void (* const g_pfnVectors[])(void)" defined at line 237 of startup_lpc54608.cpp
//      - Table 88. Connection of interrupt sources to the NVIC
//      - Table B1-4 Exception numbers & Table B1-5 Vector table format pag. B1-523 (DDI0403E_e_armv7m_arm.pdf - arm = Architecture Reference Manual)
//          - /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/docs/nxp/lpcxpresso54608D/getting_start/micro_manuals/MPU/DDI0403E_e_armv7m_arm.pdf

//      - Figure 3-1 System address map pag. 3-14 (DDI0439B_cortex_m4_r0p0_trm.pdf - trm = Technical Reference Manual)
//          - /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/docs/nxp/lpcxpresso54608D/getting_start/micro_manuals/MPU/arm_cortexm4_processor_trm_100166_0001_04_en.pdf

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


#define ICON_FUNC_03            IOCON_PIO_FUNC3
#define USART_RX_PIN            DEMO_MARCO_USART_RX_PIN         // 26
#define USART_RX_PORT           DEMO_MARCO_USART_RX_PORT        // 3
#define USART_TX_PIN            DEMO_MARCO_USART_TX_PIN         // 27
#define USART_TX_PORT           DEMO_MARCO_USART_TX_PORT        // 3
#define USART4_RS485_EN         true                            // true
#define RS485_RE_PIN            APP_BOARD_MARCO_TEST_LED3_PIN   // 2
#define RS485_RE_PORT           APP_BOARD_MARCO_TEST_LED3_PORT  // 2
#define RS485_DE_PIN            APP_BOARD_MARCO_TEST_LED2_PIN   // 3
#define RS485_DE_PORT           APP_BOARD_MARCO_TEST_LED2_PORT  // 3

// ***********


// class hw0UsartRs485ParamsReal_t: public hw0UsartRs485Params_t {
// 
//     public:
//         void    clrTxEnablePin      (void) override;
//         void    setRxEnablePin      (void) override;
//         void    setTxEnablePin      (void) override;
//         void    clrRxEnablePin      (void) override;
// 
// 
// };

#define MCU_USART_1_REAL
#define MCU_USART_2_REAL

#define HW_USART_INIT_PARAMS_DEF    {   \
                                         DEMO_MARCO_USART_FLEXCOMM_ID    \
                                        ,DEMO_MARCO_USART_REG_PTR        \
                                        ,DEMO_MARCO_USART_CLOCK_ATTACH   \
                                        ,DEMO_MARCO_USART_CLK_FREQ       \
                                        ,DEMO_MARCO_USART_IRQn           \
                                        ,DEMO_MARCO_USART_NVIC_PRIO      \
                                        ,ICON_FUNC_03                    \
                                        ,USART_RX_PIN                    \
                                        ,USART_RX_PORT                   \
                                        ,USART_TX_PIN                    \
                                        ,USART_TX_PORT                   \
                                        ,USART4_RS485_EN                 \
                                        ,RS485_RE_PIN                    \
                                        ,RS485_RE_PORT                   \
                                        ,RS485_DE_PIN                    \
                                        ,RS485_DE_PORT                   \
                                    }


#endif 	// APP_MCU_PIN_PORT_DEFINE_CONFIG_H

// appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_pphDef_Mod_nxp.cpp/.h
//      . UPDATE only .cpp
// .h

extern PPH_DEF_H__(pphUsartRs485_t,  USART_1_REAL )

// .cpp

#include "app_pphDef_Mod_nxp.h"


#define USART0_FLEXCOMM_ID  0
#define HW_USART_1_INIT_PARAMS_DEF    {   \
                                         USART0_FLEXCOMM_ID                             /*  USART_FLEXCOMM_ID   */   \
                                        ,USART0                                         /* ,USART_REG_PTR       */   \
                                        ,kFRO12M_to_FLEXCOMM0                           /* ,USART_CLOCK_ATTACH  */   \
                                        ,CLOCK_GetFlexCommClkFreq(USART0_FLEXCOMM_ID)   /* ,USART_CLK_FREQ      */   \
                                        ,FLEXCOMM0_IRQn                                 /* ,USART_IRQn          */   \
                                        ,5                                              /* ,USART_NVIC_PRIO     */   \
                                        ,IOCON_PIO_FUNC1                                /* ,IOCON_PIO_FUNC1     */   \
                                        ,29                                             /* ,USART_RX_PIN        */   \
                                        ,0                                              /* ,USART_RX_PORT       */   \
                                        ,30                                             /* ,USART_TX_PIN        */   \
                                        ,0                                              /* ,USART_TX_PORT       */   \
                                        ,false                                          /* ,USART_RS485_EN      */   \
                                        ,2                                              /* ,RS485_RE_PIN        */   \
                                        ,2                                              /* ,RS485_RE_PORT       */   \
                                        ,3                                              /* ,RS485_DE_PIN        */   \
                                        ,3                                              /* ,RS485_DE_PORT       */   \
                                    }

hwUsartInitParams_t glo_usartParams_1Real    = HW_USART_1_INIT_PARAMS_DEF;
PPH_DEF_CPP_USART_2 (pphUsartRs485_t ,USART_1_REAL ,glo_usartParams_1Real        )



~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// .....
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

/*

- usart interrupt calls
    - FLEXCOMM4_IRQHandler
    - FLEXCOMM4_DriverIRQHandler
    - USART_TransferHandleIRQ_v2            <<===>>     s_flexcommIrqHandler[4]
    - hw0UsartCmmn_t::interruptHandler_0    <<===>>     handle->callback(handle->userData)
    - hw0UsartCmmn_t::interruptHandler

- usart configuring function calls
    - hwUsartRs485_t::hwInit
    - USART_TransferCreateHandle_v2
        - g_handle (it must be empty, it is filled in this function)
        - interruptHandler_0
        - hwUsartRs485_t::this
    - FLEXCOMM_SetIRQHandler
        - USART_TransferHandleIRQ_v2
        - g_handle
        - set
            - s_flexcommIrqHandler  = USART_TransferHandleIRQ_v2
            - s_flexcommIrqHandle   = g_handle (it is the USART_TransferHandleIRQ_v2 parameter)

- calling / using
    - FLEXCOMM4_IRQHandler see .map file
        - FLEXCOMM4_DriverIRQHandler
            - call
                - s_flexcommIrqHandler[4]( . , .); == configured by USART_TransferCreateHandle_v2 & FLEXCOMM_SetIRQHandler ==>> USART_TransferHandleIRQ_v2 (USART_Type *base, usart_handle_v2_t *handle)
                    - handle->callback(handle->userData);
                        - userData ==> this / hwUsartRs485_t
                        - callback ==> interruptHandler_0(this)
                            - this->interruptHandler / hw2UsartCmmn.cpp
- configuring
    - hwUsartRs485.cpp
        USART_TransferCreateHandle_v2(DEMO_MARCO_USART_REG_PTR, &g_handle, interruptHandler_0, this);   // this = hwUsartRs485_t
    - USART_TransferCreateHandle_v2
        - usart_to_flexcomm_v2_t handler;
        - handler.usart_master_handler = USART_TransferHandleIRQ_v2;
            - handler.flexcomm_handler <<====>> handler.usart_master_handler
                - typedef union usart_to_flexcomm_v2 (from fsl_usart_upd.c)
                  {
                      flexcomm_usart_irq_handler_v2_t usart_master_handler;
                      flexcomm_irq_handler_t flexcomm_handler;
                  } usart_to_flexcomm_v2_t;
        - handle->callback    = callback; <<====>> g_handle->callback    = callback; 
        - handle->userData    = userData; <<====>> g_handle->userData    = userData; 
        - FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle); <<==>> FLEXCOMM_SetIRQHandler ( . , USART_TransferHandleIRQ_v2, g_handle ) // g_handle = {interruptHandler_0, this}
            - set
                - handler = USART_TransferHandleIRQ_v2)
                - s_flexcommIrqHandler[.] = handler

*/

// /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/archive/app20250424/mpfw_code/trdp/sdk/nxp/layer/mpfw_fw2-trdp-sdk-nxp-0trdp/src/v_06/drivers/fsl_flexcomm.c
// fsl_flexcomm.c

/*! brief Sets IRQ handler for given FLEXCOMM module. It is used by drivers register IRQ handler according to FLEXCOMM
 * mode */
void FLEXCOMM_SetIRQHandler(void *base, flexcomm_irq_handler_t handler, void *handle)
{
    uint32_t instance;

    /* Look up instance number */
    instance = FLEXCOMM_GetInstance(base);

    /* Clear handler first to avoid execution of the handler with wrong handle */
    s_flexcommIrqHandler[instance] = NULL;
    s_flexcommHandle[instance]     = handle;
    s_flexcommIrqHandler[instance] = handler;
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}

/* IRQ handler functions overloading weak symbols in the startup */
#if defined(FLEXCOMM0)
void FLEXCOMM0_DriverIRQHandler(void)
{
    assert(s_flexcommIrqHandler[0]);
    s_flexcommIrqHandler[0]((uint32_t *)s_flexcommBaseAddrs[0], s_flexcommHandle[0]);
/* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
  exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}
#endif


~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// .....
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~



~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// .....
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~



~~~~~~~~~~~~~~~~~~~~~~~~
........................

........................
// .....
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~



~~~~~~~~~~~~~~~~~~~~~~~~
........................

