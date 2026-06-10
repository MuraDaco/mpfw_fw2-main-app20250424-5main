
---

Last login: Sat Feb 21 11:08:11 on ttys006
Restored session: Fri Feb 20 20:30:43 CET 2026

void    tx_rx_management    (void* user_data1, void* user_data2)   {
    hwUsartRs485_t* l_pBufferStatus = static_cast<hwUsartRs485_t*>(user_data1); 
    l_pBufferStatus->interruptHandler(user_data2);
}

// ********************************
// ************** fsl_usart_mod.c

status_t USART_TransferCreateHandle(USART_Type *base,
                                    usart_handle_t *handle,
                                    usart_transfer_callback_t callback,
                                    void *userData)

{
    /* Check 'base' */
    assert(!((NULL == base) || (NULL == handle)));

    uint32_t instance = 0;
    usart_to_flexcomm_t handler;
    handler.usart_master_handler = USART_TransferHandleIRQ;
    ...

    handle->userData    = userData;

    ...

    FLEXCOMM_SetIRQHandler(base, handler.flexcomm_handler, handle);

    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(s_usartIRQ[instance]);

    return kStatus_Success;

}

// ********************************

// ********************************
// ************** startup_lpc54608.cpp

#define ALIAS(f) __attribute__ ((weak, alias (#f)))
/*

The alias attribute causes the declaration to be emitted as an alias for another symbol, which must be specified. For instance,

          void __f () { // Do something. ; }
          void f () __attribute__ ((weak, alias ("__f")));
     

defines `f' to be a weak alias for `__f'. In C++, the mangled name for the target must be used. It is an error if `__f' is not defined in the same translation unit. 

*/


WEAK void IntDefaultHandler(void);
...
WEAK void FLEXCOMM0_IRQHandler(void);

...

void FLEXCOMM0_DriverIRQHandler(void) ALIAS(IntDefaultHandler);

...

//*****************************************************************************
// The vector table.
// This relies on the linker script to place at correct location in memory.
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
extern void * __Vectors __attribute__ ((alias ("g_pfnVectors")));

__attribute__ ((used, section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM4
    &_vStackTop,                       // The initial stack pointer
    ResetISR,                          // The reset handler
    NMI_Handler,                       // The NMI handler
    HardFault_Handler,                 // The hard fault handler
    MemManage_Handler,                 // The MPU fault handler
    BusFault_Handler,                  // The bus fault handler
    UsageFault_Handler,                // The usage fault handler
    __valid_user_code_checksum,        // LPC MCU checksum
    0,                                 // ECRP
    0,                                 // Reserved
    0,                                 // Reserved
    SVC_Handler,                       // SVCall handler
    DebugMon_Handler,                  // Debug monitor handler
    0,                                 // Reserved
    PendSV_Handler,                    // The PendSV handler
    SysTick_Handler,                   // The SysTick handler

    // Chip Level - LPC54608
    WDT_BOD_IRQHandler,         // 16: Windowed watchdog timer, Brownout detect
    DMA0_IRQHandler,            // 17: DMA controller
    GINT0_IRQHandler,           // 18: GPIO group 0
    GINT1_IRQHandler,           // 19: GPIO group 1
    PIN_INT0_IRQHandler,        // 20: Pin interrupt 0 or pattern match engine slice 0
    PIN_INT1_IRQHandler,        // 21: Pin interrupt 1or pattern match engine slice 1
    PIN_INT2_IRQHandler,        // 22: Pin interrupt 2 or pattern match engine slice 2
    PIN_INT3_IRQHandler,        // 23: Pin interrupt 3 or pattern match engine slice 3
    UTICK0_IRQHandler,          // 24: Micro-tick Timer
    MRT0_IRQHandler,            // 25: Multi-rate timer
    CTIMER0_IRQHandler,         // 26: Standard counter/timer CTIMER0
    CTIMER1_IRQHandler,         // 27: Standard counter/timer CTIMER1
    SCT0_IRQHandler,            // 28: SCTimer/PWM
    CTIMER3_IRQHandler,         // 29: Standard counter/timer CTIMER3
    FLEXCOMM0_IRQHandler,       // 30: Flexcomm Interface 0 (USART, SPI, I2C, FLEXCOMM)
    FLEXCOMM1_IRQHandler,       // 31: Flexcomm Interface 1 (USART, SPI, I2C, FLEXCOMM)

};



https://gcc.gnu.org/onlinedocs/gcc-4.5.3/gcc/Function-Attributes.html

#define ALIAS(f) __attribute__ ((weak, alias (#f)))


// ********************************

// ********************************
// ************** fsl_flexcomm.c

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
#if defined(FLEXCOMM0) // is defining
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

// ********************************
// ************** LPC54608.h

/*!
 * @}
 */ /* end of group FLEXCOMM_Register_Masks */


/* FLEXCOMM - Peripheral instance base addresses */
/** Peripheral FLEXCOMM0 base address */
#define FLEXCOMM0_BASE                           (0x40086000u)
/** Peripheral FLEXCOMM0 base pointer */
#define FLEXCOMM0                                ((FLEXCOMM_Type *)FLEXCOMM0_BASE)
/** Peripheral FLEXCOMM1 base address */
#define FLEXCOMM1_BASE                           (0x40087000u)
/** Peripheral FLEXCOMM1 base pointer */
#define FLEXCOMM1                                ((FLEXCOMM_Type *)FLEXCOMM1_BASE)
/** Peripheral FLEXCOMM2 base address */
#define FLEXCOMM2_BASE                           (0x40088000u)
/** Peripheral FLEXCOMM2 base pointer */
#define FLEXCOMM2                                ((FLEXCOMM_Type *)FLEXCOMM2_BASE)

// ********************************


---

enum kError_t: uint16_t  {
    none
}

constexpr <error_enum_type> <error_name> = static_cast<enum_type>(<error_value>)
constexpr kError_t txError = static_cast<kError_t>(kError_t::none + 25)
oppure
constexpr auto txError = static_cast<kError_t>(kError_t::none + 25)

kError_comProtocol_group = 


---

Last login: Mon Feb 16 07:41:10 on ttys006
Restored session: Sun Feb 15 20:24:00 CET 2026

// gestione della comunicazione seriale rs485
/*    - user / [application]
*/
    {   // tuiComponent
        uint8_t l_comBuffer[100];
        int16_t l_length = g_pphComRs485.rxReceive(l_comBuffer, sizeof(l_comBuffer))

        if(l_length > 0)    {
            // packet management
            // 1. display packet
            // 2. parsing packet
        }

        if(l_length < 0)    {
            // rx error management
        }

        if(g_pphComRs485.txChkError()) {
            // tx error management
        }


    }

    - [hwUsartRs485]


---

Last login: Fri Feb 13 07:48:32 on ttys006
Restored session: Thu Feb 12 20:34:50 CET 2026

- mcuUsart (comConfigFunct_rs485_t* p_config)
    - implementa 
        - le funzioni che gestiscono i registri della mcu
        - gli eventi legati al processo di tx/rx
            - per implementarli in  modo completo chiama le funzioni dell oggetto comConfigFunct_rs485[.] 
- comBufferStatus (mcuUsart_t* p_pChannel, comProtocolInterface_t* p_pProto)
- comInterruptHandler (mcuUsart_t* p_pChannel, comBufferInterface_t* p_pBuffer)

- pphUsartRs485_t (comConfigRs485_t* p_pConfig, comProtocolInterface_t* p_pProto)
    g_channel       (p_pConfig)
    ,g_buffer       (&g_channel, &g_channel)
    - mcuUsart_t g_channel
    - comBufferStatus_t g_buffer

- class pphUsartRs485_t: public hwUsartRs485_t (comConfigRs485_t * p_pConfig, comProtocolInterface_t* p_pProto)  :
    hwUsartRs485_t  (p_pConfig)
    g_buffer        (this, p_pProto)
    g_interrupt     (this, &g_buffer)

    pphUsartRs485_t (comConfigRs485_t* p_pConfig, comProtocolInterface_t* p_pProto)

- chi gestisce/implementa gli eventi ha bisogno di aver l'istanza della classe comConfigRs485_t
    - e quindi è quello che definisce anche come si chiamerà la classe
        - sto pensando alle classi
            - hwUsart
            - hwUsartRs485
    - per gestire gli eventi di comunicazione bisogna conoscere l'hardware sia del micro che del canale quindi
    - i moduli/claassi più opportune dove far risiedere il codice sono quelle dei driver
        - in questa parte del codice ci si concentra sul caso reale non si lavora in astratto
        - inoltre si lavora ancora sugli elementi singoli
        - questi elementi singoli sono messi insieme nei moduli di più alto livello
        - quei livelli in cui ci sono più informazioni che permettono di mettere insieme tutti gli elementi singoli dei v ari moduli/elementi/classi/oggetti coinvolti



---

Last login: Thu Feb 12 08:35:19 on ttys006
Restored session: Wed Feb 11 19:44:13 CET 2026

- definire gli elementi
    - buffer
    - protcollo
    - eventi di comunicazione
        - specifici per rs485
    - funzioni base sui registri 
    - funzione handler del interrupt
        - standard 


- comEventInterface_t
- comUsartEvent_t : comEventInterface_t
    - comUsartEvent_t   (comChannelInterface_t* )

- il ivello di aplicazione non deve entrare nel merito di come predisporre le varie funzioni
    - questo lo sanno i moduli di più basso livello e specifici per quel compito
    - a livello di app ci deve essere solo funzioni di configurazione che si possono conoscere solo al momento dell istanziazione
        - queste funzioni contengono informazioni che non riguardano i moduli di livello più basso
            - deve gestire informazioni che sono fuori la zona di visione dei moduli più specifici
                - questo significa che eventuali parametri che vengono passati al modulo /* appUsartConfig */ non devono avere legami diretti con i moduli usart di più basso livello
                - quindi la filosofia è questa
                    - semplicemente passare ai livelli più bassi quegli elementi che solo a livello applicativo si possono conoscere
                        - sarà poi compito dei livelli più bassi disporli e gestirli in modo opportuno
                    - questo in pratica significa 
                        - chiamare le funzioni di interfaccia del modulo comUsartConfigInterface_t in modo opportuno
                            - non ha senso parlare di eventi, gli eventi li gestirano i livelli più bassi che sono quelli più specifici
                            - in particolare gli eventi li gestirà il modulo
                                - [wrap] hwUsart oppure
                                - [real] pphUsart
                            - i moduli che hanno tutte le conoscenze e le informazioni per gestire gli elementi e quinndi per implementare correttamente gli eventi
                            - ad esempio nel caso della [usart]/[rs485_com] le funzioni di configurazioni saranno
                                - [enableTx/disableTx]
                                - [enableRx/disableRx]
                        



- pphUsart
    - ppUsart(&appUsartEvent)    

class comInterruptHandler_t {
    comInterruptHandler_t   (p_channel, p_buffer)
};



uint8_t mcuUsart_t::check_read_write(void)	{
	uint8_t l_result = TX_OK;

	/*  =================================================
        check shared memory buffer status
        check the "lock" status of the virtual serial comunication channel:
        if shm buffer is locked means that a process is sending a packet and hence 
        1. a byte must be read
        2. or the byte that was written/sent has been read/received from all processes, therefore
           the writer/tx process can send another byte or close the transmission releasing/unlocking the shared memory buffer
    
        N.B.: only one process at time can write to
        ================================================= */
	if(g_channel->chkInterruptsRaised())	{
        // INTERRUPT TRIGGER of "Receive byte" or "Send byte"/"Last byte phisically send"

		// write/read procedure is on
		// if(shmMcuUsart_t::pidMatches()) {
    	if(g_channel->chkTxInterruptRaised())	{
			// the current process is the process that write/add data to packet buffer
			// all processes have read the data
			// therefore ...

            g_buffer->tx_interrupt_buffer_management();

		} else {
			// the current process is not the process that add data to packet buffer
			// therefore ...
    		// there is a data to read

            g_buffer->rx_interrupt_buffer_management();

		}
	} else {
		// the channel is free:
        // - no byte received to be managed
        // - check if there is a new packet to send
		g_buffer->tx_interrupt_buffer_management();

	}

	return l_result;
}




---

Last login: Tue Feb 10 07:53:54 on ttys006
Restored session: Mon Feb  9 20:01:29 CET 2026

namespace fw2::fnct::base   {

    fnct-base-0abst {
        src/com{
            struct comBuffer_callback_t  {
                tx_interruptBufferManagement
                rx_interruptBufferManagement
            }

            struct comChannel_callback_t   {
                tx_eventStartUp / tx_eventInit
                tx_eventBegin / tx_eventFirstData
                tx_eventSendData
                tx_eventLastData
                tx_eventEnd
            }

            class comProtocolInterface_t  {
                void tx_interruptBufferManagement
                void rx_interruptBufferManagement
            }

            class comBufferInterface_t  {
                void tx_interruptBufferManagement
                void rx_interruptBufferManagement
            }

            class comChannelInterface_t   {
                void tx_eventStartUp / tx_eventInit
                void tx_eventBegin / tx_eventFirstData
                void tx_eventSendData
                void tx_eventLastData
                void tx_eventEnd
            }
        }
    }
}

namespace fw2::fnct::core   {
    fnct-core-3real {
        src/com {
            class comProtocolStatus_t   {

            }

            class comBufferStatus_t: public comBufferInterface_t {
             
                comBufferStatus_t::comBufferStatus_t(comProtocolStatus_t* p_proto, comChannelInterface_t* p_channel)

                comProtocolStatus_t*    g_proto;
                comChannelInterface_t*  p_channel;

            }
        }
    }
}

namespace fw2::fnct::hw   {
    
    fnct-hw-1trdp {
        src/hw {
            class mcuUsart_t:    public mcuBase_t
                                ,public vhwProxIntfc_t
                                ,public shmMcuUsart_t   {
                mcuUsart_t::mcuUsart_t();
            }

            class mcuUsartEvents_t: public mcuUsart_t {
                mcuUsartEvents_t::mcuUsartEvents_t()
            }
        }
    }

    fnct-hw-2wrp {
        src/common/hw {
            class hwUsartInterface_t  {

            }
        }

        src/trdp/hw {
            class hwUsartRs485_t: public mcuUsartEvents_t, public hwUsartInterface_t {
                hwUsartRs485_t::hwUsartRs485_t(comConfigRs485_t* p_pConfig): {

                }

                void vhwLoop    (void)  {
                    comInterruptHandler_t::run(this, p_buffer);
                }

                
            }

        }
    }

    fnct-hw-3real {
        src/hw  {
            class pphUsartRs485_t: public hwUsartRs485_t  {
                pphUsartRs485_t::pphUsartRs485_t(comProtocolInterface_t* p_proto, comUsartConfigInterface_t* p_config):
                    hwUsartRs485_t  (g_buffer, p_config)
                    g_buffer    (p_proto, this)
                {}

                comBufferStatus_t g_buffer;
            }
        }
    }


---

Last login: Thu Feb  5 11:15:41 on ttys006


void hwUsartIntfc_t::Tx       (uint8_t p_Num)  {
    dgFormatDigit l_FormatNum (&p_Num, 1, DIGIT_NUM_3, dgFormatDigit::kEncoding_Decimal, 0, false);
    l_FormatNum.vValueToString();

    if(comBufferState::tx_startUp())   {
        // ------------------------------
        rs485_TxPinEnable();
        USART_TxIntEnable();
    }
}

// by specific command
{
    g_rs485_Buff->tx_sendPacket();

}

// while loop

- si possono avere più istanze di uno stesso protocollo 
    - ciascuna istanza può essere usata in canali di comunicazione diversi il protocollo può essere usato in più istanze del buffer
        - quindi essere associata a diversi buffer
- a sua volta si possono avere più istanze di un buffer 
    - ciascuna istanza usata in canali di comunicazioone diversi
    - e quindi con funzioni di [callback] relative all'sdk' diverse

class pphUsart  {

    pphUsart    (comProtocolSatus_t* p_proto)
        g_rs485_Buff    {p_proto}

    - definizione delle funzioni di callback 
        - usate dal buffer ed implementate nell'sdk'
            - come implementare le funzioni di callback riguarda l'sdk' mentre 
            - come associare le funzioni di callback riguarda il modulo che identifica il canale di comunicazione
            - quindi il modulo pphUsartRs485
            - una parte di queste funzione sono implementate a livello di applicazione ad esempio nell /* evento di end */ si deve disabilitare il pin di tx-enbable
                - ma questo pin fa pate della configurazione della piattaforma quindi sarà ad un livello più alto
                - tuttavia essendo legato alla configurazione lo si potrebbe ridurre ad un parametro
                    - parametro dinamico
                        - lo si passa nel costruttore e quindi lo si imposta nel momento in cui vine istanziato l'oggetto'
                    - parametro statico/costante
                        - lo si definisce in un file .h di configurazione
        - usate dall'sdk' ed implementate dal buffer

}

{
    if(g_rs485_Buff->tx_chkError()) {
        // tx error management
        // 1. user interface (like leds o display) show the error
        // 2. log the error
        // update status to free
    }

    if(!g_rs485_Buff->rx_startUp())  {

        if(g_rs485_Buff->rx_chkCompleted()) {
            // parsing packet data
        }

        if(g_rs485_Buff->rx_chkError()) {
            // rx error management
            // 1. user interface (like leds o display) show the error
            // 2. log the error
            // update status to free
        }

    }


}