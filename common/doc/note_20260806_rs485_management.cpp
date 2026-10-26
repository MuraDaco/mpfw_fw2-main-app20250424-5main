
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

