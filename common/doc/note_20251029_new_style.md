
---

Last login: Tue Apr 28 07:56:18 on ttys009

- cose da fare
    - implementare il riordino in base alle priorità delle funzioni presenti negli array dei servizi
        - cmake --help-command list
    - update github
    - update macco-bucco



.. signature::
  list(SORT <list> [COMPARE <compare>] [CASE <case>] [ORDER <order>])

  Sorts the list in-place alphabetically.

  .. versionadded:: 3.13
    Added the ``COMPARE``, ``CASE``, and ``ORDER`` options.

  .. versionadded:: 3.18
    Added the ``COMPARE NATURAL`` option.

  Use the ``COMPARE`` keyword to select the comparison method for sorting.
  The ``<compare>`` option should be one of:

    ``STRING``
      Sorts a list of strings alphabetically.
      This is the default behavior if the ``COMPARE`` option is not given.

    ``FILE_BASENAME``
      Sorts a list of pathnames of files by their basenames.

    ``NATURAL``
      Sorts a list of strings using natural order
      (see ``strverscmp(3)`` manual), i.e. such that contiguous digits
      are compared as whole numbers.
      For example: the following list `10.0 1.1 2.1 8.0 2.0 3.1`
      will be sorted as `1.1 2.0 2.1 3.1 8.0 10.0` if the ``NATURAL``
      comparison is selected where it will be sorted as
      `1.1 10.0 2.0 2.1 3.1 8.0` with the ``STRING`` comparison.

  Use the ``CASE`` keyword to select a case sensitive or case insensitive
  sort mode.  The ``<case>`` option should be one of:

    ``SENSITIVE``
      List items are sorted in a case-sensitive manner.
      This is the default behavior if the ``CASE`` option is not given.

    ``INSENSITIVE``
      List items are sorted case insensitively.  The order of
      items which differ only by upper/lowercase is not specified.

  To control the sort order, the ``ORDER`` keyword can be given.
  The ``<order>`` option should be one of:

    ``ASCENDING``
      Sorts the list in ascending order.
      This is the default behavior when the ``ORDER`` option is not given.

    ``DESCENDING``
      Sorts the list in descending order.


---

Last login: Mon Apr 27 07:16:04 on ttys009

/Applications/MCUXpressoIDE_11.5.1_7266/ide/plugins/com.nxp.mcuxpresso.tools.macosx_11.5.1.202201181444/tools/bin/../lib/gcc/arm-none-eabi/10.3.1/../../../../arm-none-eabi/bin/ld: 
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/build_main/nxp/lib_appl-app20250424-4appl.out.a(app_pphDef_Mod_nxp.cpp.obj):
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h:76: multiple definition of `g_usartParams'; 
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/common/build_main/nxp/lib_appl-app20250424-4appl.out.a(app_managerCmmn.cpp.obj):
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/nxp/src/instances/hw/units/app_mcuPinPortDefineConfig.h:76: first defined here

---

Last login: Mon Apr 20 07:44:07 on ttys009

- gestione dello stato di [FIRST_BYTE] nel protocollo di comunicazione
    - ragionamenti
        - se permetto di inserire nel buffer di trasmissione [dirty_byte] all'inizio del buffer
        - dall'altra anche il buffer di ricezione avrà dei dati sporchi
        - per fare una cposa elegante e semplice è quella di accettare che anche il bnuffer di ricezione abbia i primi byte sporchi
            - quando si andrà a fare  il parsing del buffer di ricezione  si dovra considerare anche i [dirty_byte] ricevuti
    - le parti del codice da modificare sono
        - la ricezione
        - l'invio
            - nel comando di invio ci deve essere la possibilità di inmpostare il parametro di quanti [dirty_byte] inviare
            - capire quale modalità sia la migliore
                - 1. eseguire uno shift in avanti del buffer Tx
                    - pro
                        - implementazione semplice e veloce
                    - contro
                        - si modifica un parametro di livello più alto all'insaputa del proprietario
                            - può non essere sufficente la dimensione del buffer
                        - assomiglia molto ad una "pezza"
                - 2. creare uno stato [data_dirty] in cui si invia un byte sporco diverso dal primo byte per n-volte
                    - quante sono impostate nel parametro [data_dirty_num]
                    - pro
                        - implementazione più ortodossa, concettualmente più pulita e, IMPORTANTISSIMO, molto più chiara
                    - contro 
                        - implementazione più laboriosa

---

Last login: Fri Apr 17 07:20:00 on ttys008
Restored session: Thu Apr 16 17:45:23 CEST 2026

- analisi gestione hardware virtuale
    - in particolare come viene gestito il "cambio di stato"
        - [shmManager]
            - 


---

Last login: Tue Apr 14 05:35:06 on ttys009

- gestione dei thread e fase di terminazione
    - se si esegue l'exit di un processo che ha dei thread attivi prima che venganmo eseguite le istruzioni di join associate a cascun thread
        - si ottiene un errore di "zsh: segmentation fault  ./exec_app20250424.out -id 5 --reset_shared_memory"



---

Last login: Mon Apr 13 07:40:48 on ttys009


- cose da fare
    - aggiornare il modulo [krThreadManager]
        - creare il modulo [krThreadsArray]
            - il file .h risiederà nel modulo [mpfw_fw2-fnct-core-2wrpr]
            - mentre il file .cpp nel modulo del gruppo [appl] nella directory [sdk/<platform>/src/config/fnct-core-2wrpr]
            - nella directory [sdk/<platform>/src/config/fnct-core-2wrpr] sarà presente anche il file di copnfigurazione [cg_krThread]
        - modificare il modulo [krThreadManager]
            - inserire il riferimento al modulo [krThreadsArray]
    - spostare il file
        - mpfw_fw2-fnct-core-2wrpr/trdp/sdk/nxp/src/kr/krThread/v_06/krThreadCfgTbl.cpp
            - nella directory [sdk/<platform>/src/config/fnct-core-2wrpr] del modulo del gruppo [appl]
    - aggiornare il file [cpp_files.cmake]
        - vedere se è possibile creare la sezione [config] come quella presente nel file [include_files.cmake]
            - non credo sia possibile
                - percheè quando si va a compilare il file e questo fa riferimento a file include non presenti nel modulo radice la compilazione fallisce
- steps
    - 1. stepp
        - introdurre il modulo [krThreadsArray]
        - e modificare di conseguenza il modulo [krThreadManager]
        - ed il file [cpp_files.cmake]
    


- gestione loop functions on thread
    - messo ordine nella creazione dei thread
        - nel caso
            - virtuale
                - si usa la libreria standard [std::thread]
                    - si creano istanze dinamiche dei thread ee si useranno i puntatori alle istanze dei thread
                        - si veda
                            - static krThread_t* g_krTh[];
                            - nel modulo [krThreadManager]
            - reale
                - si usa la libreria [freeRTOS] 
                - si possono creare dei thread statici o dinamici
                - 1. thread statici
                    - per thread statici si creereano e useranno direttamente le istanze dei thread
                        - si veda 
                            - static krThread_t 	ThreadArray[];
                            - nel modulo [krThreadManager]
                    - in questo caso le istanze vengono definite come variabili globali e vengono "inizializzate" con dei parametri di conmfigurazione
                    - l'inizializzazione viene compiuta chiamando la funzione [krThread_t::CreateStatic]->[freeRTOS::xTaskCreateStatic]
                        - l'inizializzazione consiste, molto probabilmente (per essere certi si dovrebbe analizzare il codice [freeRTOS]), nell'aggiungere il thread ad un array il quale verrà usato dalla funzione [freeRTOS::vTaskStartScheduler] che è quella che esegue il codice dei thread in particolare della funzione ad esso associata
        - la funzione associata ai thread a le seguenti caratteristiche valide per entrambe i casi [reale] e [virtuale]
            - la funzione loop
                - 1. è identica per tutti i thread
                - 2. esegue le funzioni presenti in un array
                    - ciascuna di queste funzioni dell'array 
                        - "deciderà" se eseguire il proprio codice in base all'identificativo del thread che gli viene passato come parametro
                        - non deve avere codice bloccante
                        - ad esempio
                            - le funzioni presenti in questo array saranno le [funzioni_manager] dei vari possibili servizi
                            - in particolare saranno sempre presenti i seguenti servizi
                                - timer
                                    - krTimer
                                - state machine
                                    - svStateMachine
                - 3. è una funzione bloccante in particolare esegue all'infinito il loop sull'array di funzioni descritto al punto precedente
                    - ad ogni loop può chiamare una funzione di sleep che cede il controllo ad un altro thread
                    - della funzione di slee si può fare a nche a  meno a seconda di come sono stati confgirati i thread ed in particolare la regola di scheduling
                        - a tale riguardo vedere la documentazioone del [freeRTOS]
                




---

Last login: Fri Apr 10 08:40:46 on ttys009

- eseguire l'override di una funzione statica di una classe derivata
    - 
- array 
    - delle istanze della 
        - krThread krThreadCfgTbl::ThreadArray[]
    - e 
    - array di puntatori alla
        - krThread* krThreadManager::g_krTh[krThread_Num];
    - classe [krThread]



- gestione dei thread
    - migliorare la gestione dell'array delle istanze dei thread [g_krTh]
        - al momento sembra usata solo dalla piattaforma virtuale mac 
        - mentre la paiattaforma virtuale nxp ha l'array [krThreadCfgTbl::ThreadArray]
            - quindi capire se 
                - usarlo anche nella piattaforma reale
                - oppure
                - eliminarlo dalla piattaforma reale
    - pensare anche di creare un modulo [krEnd] sulla modello del modulo [krInit]/[krInitStatic]
        - questi moduli contengono il codice che deve essere eseguito al termine dei loop associati ai thread
        - il codice di questi moduli può essere eseguito sul processo principale e non nei thread
        - quindi dopo le istruzioni [join] nel caso di piattaforma virtuale [mac]/[linux]/[window]
            - si rammenta che 
                - nelle piattaforme virtuali 
                    - l'istruzione [join] ha lo scopo di bloccare il flusso di codice del processo principale affinchè non termini
                    - i thread diventano attivi ovvero vanno in esecuzione con l'istruzione [new] che crea l'istanza della classe thread
                - nelle piattaforme reali [freeRTOS]/[nxp]/[stm32f769_disco] 
                    - l'istruzione [join] non è necessaria 
                    - in particolare è sostituita dall'unica istruzione [vTaskStartScheduler]
                    - i thread (statici) vengono definiti/configurati con l'struzione [CreateStatic]/[freeRTOS::xTaskCreateStatic]
                        - che deve esseeguita prima dell'ìistruzione [vTaskStartScheduler]
    - i moduli di riferimento per la gestione di thread sono
        - [krThreadManager]
            - le funzioni chev engono eseguite sono
                - [InitThenRun]
                    - calls
                        - piattaforma reale 
                            - [krThread::CreateStatic] -> [freeRTOS::xTaskCreateStatic]
                            - [freeRTOS::vTaskStartScheduler]
                        - piattaforma virtuale
                            - [new] of [krThread] -> [thread_t] (that is [std::thread] by typedef)
                                - in questo momento il thread inizia ad essere in esecuzione
                - [Exit]
                    - calls
                        - piattaforma reale
                            - nessuna chiamata al momento 
                            - si potrebbe spostare qui l'istruzione [freeRTOS::vTaskStartScheduler] 
                                - per avere un parallelo con il codice delle piattaforme virtuali
                        - piattaforma virtuale
                            - [std::thread::join]
            - queste istruzioni sono eseguite nel processo
        - [krThread]
            - [CreateStatic]
            - [loop]
                - rappresenta il codice eseguito nel thread e per ogni thread è uguale
                - in particolare 
                    - esegue il codice [loop] dei moduli che usano il servizio [krThread]
                    - esegue un loop sull'array delle funzioni [loop]
                        - questo array è definito nel modulo [] ed è un codice autogenerato
                            - per auto generare questo codice si devonmo seguire i seguenti passi





---

Last login: Thu Apr  9 11:39:31 on ttys009


- gestione dei thread
    - generale
        - la funzione associata ai thread è uguale per tutti
            - in particolare esegue un loop sull'array delle funzioni loop
            - questo array è impostato in modo automatico e lo si trova nella directory [autogen]
                - questo array è definito nel modulo [krThreadTbl]
                    - il file [.h] si trova nel modulo [core-2wrpr]
                    - mentre il file .cpp si trova nella directory [autogen] citata precedentemente
                - questo array contiene funzioni loop [NON_BLOCCANTI]/[NO_BLOCKING]
    - mac
        - gestione della terminazione di un thread
            - il segnale parte dall'istanza della classe [tuiGrphRealUnit5Root_t] atraverso il valorte di ritorno della funzione [loop]
            - la funzione [loop] viene chiamata dal l'istanza "statica" della classe tuiManager
    - FreeRTOS / nxp
    - FreeRTOS / stm32F769_disco



---

Last login: Thu Apr  2 08:52:45 on ttys009
Restored session: Wed Apr  1 18:09:04 CEST 2026


- analisi del flusso delle istruzioni riguardanti la comunicazione seriale
    - fase di inizializzazione
    - fase di loop


---

Last login: Tue Mar 31 06:20:41 on ttys010
Restored session: Mon Mar 30 19:47:49 CEST 2026

- gestione configurazione delle [trdp]
    - dovrebbe essere fatta a livello di cmake e non si parametro shell
        - perchè deve dipendere solo dalla libreria che usa la specifica [trdp]
        - in particolare l'informazione della [trdp] la deve fornire il modulo che dipendende da  
            - un modulo [2wrpr-...]
            - oppure
            - un modulo [3real] o di livello superiore che ha una directory [trdp]
            - N.B.: il modulo [2wrpr] contiene anche l'informazione di che tipo/classe di libreria è
                - al momento ci sono due tipologie
                    - sdk
                    - ui (user interface)
            - a questo punto credo sia abbastanza chiaro dove inserire l'informazione della [trdp]
            - nella lista delle dipendenze si deve aggiungere il campo [trdp] che conterrà una lista delle trdp che si è deciso di usare
                - questa lista però ha una priorità inferiore a quella che viene data dalla shella con il comando di build
                - diciamo che questa è una lista di default

---

Last login: Thu Mar 26 09:45:05 on ttys009
Restored session: Wed Mar 25 19:54:31 CET 2026


[ 97%] Linking CXX executable exec_app20250424.out
Undefined symbols for architecture x86_64:
  "vhwManager_t::init()", referenced from:
      hwManager_t::init() in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
      hwManager_t::init(int, char**) in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
  "hwManagerTbl_t::UnitPtrArray", referenced from:
      hwManager_t::init() in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
      hwManager_t::init(int, char**) in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
      hwManager_t::loop() in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
      hwManager_t::end() in lib_fnct-hw-2wrpr-sdk.out.a[6](hwManager.cpp.o)
  "mcuUsartRs485_t::rx_eventEnd()", referenced from:
      vtable for pphUsartRs485_t in lib_fnct-hw-3real.out.a[6](pphUsartRs485.cpp.o)
      vtable for hwUsartRs485_t in lib_fnct-hw-2wrpr-sdk.out.a[5](hwUsartRs485.cpp.o)
      vtable for mcuUsartRs485_t in lib_fnct-hw-1trdp-sdk-mac.out.a[12](mcuUsartRs485.cpp.o)
  "mcuUsartRs485_t::rx_eventBegin()", referenced from:
      vtable for pphUsartRs485_t in lib_fnct-hw-3real.out.a[6](pphUsartRs485.cpp.o)
      vtable for hwUsartRs485_t in lib_fnct-hw-2wrpr-sdk.out.a[5](hwUsartRs485.cpp.o)
      vtable for mcuUsartRs485_t in lib_fnct-hw-1trdp-sdk-mac.out.a[12](mcuUsartRs485.cpp.o)
  "mcuUsartRs485_t::rx_chkError_overrun()", referenced from:
      vtable for pphUsartRs485_t in lib_fnct-hw-3real.out.a[6](pphUsartRs485.cpp.o)
      vtable for hwUsartRs485_t in lib_fnct-hw-2wrpr-sdk.out.a[5](hwUsartRs485.cpp.o)
      vtable for mcuUsartRs485_t in lib_fnct-hw-1trdp-sdk-mac.out.a[12](mcuUsartRs485.cpp.o)
  "tuiFnctAbstUnit1Cntr_t::initChildren(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::clickingChild(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::selectByMouse(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::displayChildren(dtyIntfcAbstractUnitGraphic_t*, bool)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::refreshChildren(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::vEventHndlKey_up(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::vEventHndlKey_down(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::vEventHndlKey_enter(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::updCoordNboundsChilds()", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::vEventHndlMouse_rollUp(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::vEventHndlMouse_rollDown(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::init(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      tuiFnctRealCplx3McuUsartX_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      non-virtual thunk to tuiFnctRealCplx3McuUsartX_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      tuiFnctRealCplx3McuUsartXX_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      non-virtual thunk to tuiFnctRealCplx3McuUsartXX_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      tuiFnctRealUnit3McuUsart_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      non-virtual thunk to tuiFnctRealUnit3McuUsart_t::init(dtyIntfcAbstractUnitGraphic_t*) in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      ...
  "tuiFnctAbstUnit1Cntr_t::tuiFnctAbstUnit1Cntr_t(char const*, dtyCntnr0BaseUnit_t*)", referenced from:
      tuiFnctRealUnit2Cntnr_t::tuiFnctRealUnit2Cntnr_t(char const*, dtyCntnr0BaseUnit_t*) in lib_fnct-tui-0abst.out.a[14](tuiFnctRealUnit2Cntnr.cpp.o)
      tuiFnctRealUnit2Cntnr_t::tuiFnctRealUnit2Cntnr_t(char const*, dtyCntnr0BaseUnit_t*) in lib_fnct-tui-0abst.out.a[14](tuiFnctRealUnit2Cntnr.cpp.o)
  "vtable for fw2::fnct::core::comProtocolStatus_t", referenced from:
      fw2::fnct::core::comProtocolStatus_t::comProtocolStatus_t() in lib_fnct-core-3real.out.a[4](comProtocolStatus.cpp.o)
      fw2::fnct::core::comProtocolStatus_t::comProtocolStatus_t() in lib_fnct-core-3real.out.a[4](comProtocolStatus.cpp.o)
   NOTE: a missing vtable usually means the first non-inline virtual member function has no definition.
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::displayChildren(dtyIntfcAbstractUnitGraphic_t*, bool)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::refreshChildren(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::updCoordNboundsChilds()", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::initChildren(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::init(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiCpltCtnr2StreamFormattedString_t in lib_fnct-tui-3real.out.a[17](tuiCpltCtnr2StreamFormattedString.cpp.o)
      vtable for tuiCpltCtnr2StreamFormattedStringX_t in lib_fnct-tui-3real.out.a[18](tuiCpltCtnr2StreamFormattedStringX.cpp.o)
      vtable for tuiFnctRealUnit2Cntnr_t in lib_fnct-tui-0abst.out.a[14](tuiFnctRealUnit2Cntnr.cpp.o)
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::clickingChild(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
  "non-virtual thunk to tuiFnctAbstUnit1Cntr_t::selectByMouse(dtyIntfcAbstractUnitGraphic_t*)", referenced from:
      vtable for tuiCpltUnit3ShmProxX_t in lib_fnct-tui-3real-trdp-sdk-mac.out.a[3](tuiCpltUnit3ShmProxX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[3](tuiFnctRealCplx3McuUsartX.cpp.o)
      vtable for tuiFnctRealCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[4](tuiFnctRealCplx3McuUsartXX.cpp.o)
      vtable for tuiFnctRealUnit3McuUsart_t in lib_fnct-tui-3real.out.a[5](tuiFnctRealUnit3McuUsart.cpp.o)
      vtable for tuiCpltCplx3McuUsartX_t in lib_fnct-tui-3real.out.a[14](tuiCpltCplx3McuUsartX.cpp.o)
      vtable for tuiCpltCplx3McuUsartXX_t in lib_fnct-tui-3real.out.a[15](tuiCpltCplx3McuUsartXX.cpp.o)
      vtable for tuiCpltCplx4McuUsartUU_t in lib_fnct-tui-3real.out.a[16](tuiCpltCplx4McuUsartUU.cpp.o)
      ...
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make[2]: *** [exec_app20250424.out] Error 1
make[1]: *** [CMakeFiles/exec_app20250424.out.dir/all] Error 2
make: *** [all] Error 2
work@umtiefs-Mac-mini cmake % 

---

Last login: Wed Mar 25 09:20:43 on ttys004

- gestione comunicazione
    - a rigore i moduli [comProtocolStatus] e [comPacketBody] si dovrebbero considerare come librerie esterne al pari delle librerie per la [user_interface]
        - conisederando i moduli citati in questo modo è possibile lasciare il nome di moduli così come è, ovvero generale
        - diversamente sarebbe da aggiornare il nome delmodulo assegnando un nome al protocollo ad esempio "abc" quindi il nome del modulo diventerebbe [comProtocolStatus_abc]
    - quindi la cosa più giustra è quella di creare un modulo  radice dedicato alla comunicazione [com] 
        - questo modulo a sua volta può avere due possibilità
            - essere un modulo [wrapper] quindi con il layer [2wrpr]
                - qui si dovranno decidere i nomi da assegnare alle varie versioni dipendenti dal proprietaro del protocollo
                - in questo caso il nome del proprietario del protocollo comparirà nella linea di comado quindi come un parametro
                    - quuetsa coas può essere considerata un vantaggio a lieve discapiuto della modularità dal momento che il codice dovrà esssere integrato in unmodulo [2wrpr]
                        - il vantaggio consiste nel non dover cambiare il codice (c++/cmake) per avere lo stesso firmware ma con un protocollo diverso
            - oppure
            - essere un modulo senza il layer [wrapper] ma con l'informazione nel nome del modulo del proprietario
                - rispetto la precedentwe possobilità il nome del proprietario della libreria sarà "cablato" nel senso che se si vuole avere lo stesso firmware con un protocollo diverso si dovrà aggiornare il codice
        - pensare che ci possono essere più produtori di un dispositivo che utilizzano lo stesso firmware ma ch hanno un protocollo di comunicazione diverso
        - per non avere "conflitti" tra le varie librerie si deve tener traccia del nome del proprietario
        - questo, appnto, può essere fatto in due modi, quellio descritto nei punti precedenti

- comunicazione tra oggetti locali o tra oggetti in remoto
    - si usaneranno dei protocolli annidati
        - pacchetti all'interno di altri pacchetti
    - eventi
        - elementi/struttura
            - sorgente degli eventi
            - destinatario/gestore degli eventi
            - evento
        - flusso degli eventi
            - gli eventi devono avere la possibilità di transitare sui cnamlio di comunicazione siano essi locali o remoti
        - alcuni esempi
            - [keyboard]/[user_interface]







---

Last login: Tue Mar 24 04:44:07 on ttys009
Restored session: Mon Mar 23 20:14:25 CET 2026

- buffer dati formattati
    - contiene informazioni necessarie per la comunicazione
    - contiene informazioni che possono modificare il flusso di operazioni di una procedura
    - contiene informazioni sui parametri di una procedura/oggetto

- comunicazione tra oggetti che girano (la loro funzionei di [loop]) su thread diversi



---

Last login: Mon Mar 23 08:07:31 on ttys004


- gestione dei protocolli in modo ricorsivo/nidificato
    - si dovrebbe avere un codice associato al protocollo
        - capire se questo protocollo si deve torvare al'interno o all'esterno del buffer
    - parsing del corpo di dati
        - proprietà del [body]
            - può avere o NON avere un [header]
            - dato il buffer/[body] (penasere che ci possono essere dei body annidati/ricorsivi)
                - ci sono informazioni da ottenere
                    - mittente
                    - destinatario
                    - lunghezza del pacchetto
                    - body / puntatore alla parte data del pacchetto
                        - mappatura della memoria
                    - comandi
                        - ad esempio
                            - scrivi/leggi un parametro o una porzione di memoria

- flusso delle operazioni
    - 1. c'è un pacchetto che si deve inviare/ricevere
        - è rappresentato da un buffer di dati
            - 1. c'è bisogno di conoscere la lunghezzqa del pacchetto
            - 2. c'è bisogno di conoscere il [body]
                - del body si deve capire se contiene
                    - 1. altri pacchetti
                    - 2. comandi
                    - 3. porzioni di memoria/record di dati



---

Last login: Tue Mar 17 07:41:19 on ttys006

- gestione della procedura di build
    - eseguire un controllo sulla versione delle librerie per evitare eventuali disallineamenti
        - segnalare un errore quando il modulo superiore passa al moddulo inferiore la versione di una libreria, da cui il modulo inferiore dipende, diversa da quella che il modulo inferiore ha nella propria lista delle dipendenze vedere file [set_dependencies_list.cmake]
            - 


- gestione dei pacchetti di ricezione
    - ricezione paccheti formattati
    - ricezione stringhe
    - ricezione stringhe multiple
    - ricezione pacchetti non formattati
        - termine della ricezione via [timeouit]
    - controlli mentre si sta ricevendo i byte del pacchetto
        - controllo sul preambolo del protocollo
            - il preambolo dobrebbe avere un [checksum]
            - generazione di errore di protocollo
                - se il preambolo non rispetta il protocollo e si sta ricevendo un pacchetto con prtocollo si genererà un errore
            - fine della ricezione
                - se generato un errore
        - controllo caratteri ascii con caratteri di controllo ][cr/lf]:[\n\r]
            - generazione errore stringa
                - se si sta esplicitamente ricevendo una stringa
                - se non viene ricevuto il terminatore nullo, erore di overflow
        - controllo terminatore nullo per una stinga
            - il controllo viene effettutato solo se non è stato riconosciuto nessun protocollo
            - fine della ricezione se 
                - errore sul protocollo ovvero il pacchetto non segue nessun protocollo
                - ricevuto terminatore nullo (byte [zero]) e fino al momento si sono ricevuti solo caratteri [ascii+CR/LF]

- parametri
    - tipologie del pacchetto
        - con protocoolo
            - se il puntatore al proitocollo non è nullo
        - stringa
        - multi-stringa
        - ascii-buffer
            - in questo caso non viene fatto il cpontrollo del terminatore nullo ma si termina per timeout
        - unknown



---

Last login: Mon Mar 16 06:13:13 on ttys006
Restored session: Sun Mar 15 16:25:08 CET 2026

- gestione dei pacchetti senza protocollo nopn definito
    - stringhe
    - pacchetti lioberi
        - timeout
        


- bool comBufferStatus_t::tx_packetFormatFree           (uint8_t* p_bufferPtr, uint16_t p_bufferSize)	{
    - si esegue il reset
    - si imposta la lunghezza del pacchetto che sarà uguale al size
        - viene anche fatto un controllo per vedere se il size del buffer del pacchetto supera il buffer di trasmissione

- bool comBufferStatus_t::tx_packetFormated             (char* p_string)	{
    - 
- bool comBufferStatus_t::tx_string           (char* p_string)	{
    - si eseguono i controlli che 
        - tutti i caratteri siano ascii
        - sia presente il teminatore nullo
        - la lunghezza della stringa non ecceda quella del buffer di trasmissione
- bool comBufferStatus_t::tx_strings          (char* p_bufferPtr, uint16_t p_bufferSize)	{
    - una stringa con terminatore nullo
    - una stringa che può contenere i caratteri di controllo [/n/r] [CR/LF]

- bool comBufferStatus_t::tx_packetAscii           (char* p_bufferPtr, uint16_t p_bufferSize)	{
    - è una stringa senza terminatore 
    - si esegue il reset
    - si esegue un controllo che tuti i caratteri siano ascii



---

Last login: Wed Mar 11 06:37:17 on ttys006
Restored session: Tue Mar 10 19:37:40 CET 2026

- come decidere la locazione di un modulo di codice
    - domande da porsi
        - 1. da quali moduli deve dipendere?
        - 2. ci sono più moduli che lo usano e che possono creare dei loop nel flusso delle dipendenze?
    - quualche esempio
        - moduli di codice
            - hw0GpioIntfc/v_00
            - hw0GpioDgIntfc/v_00
            - hw0UsartIntfc/v_00
            - hw0UsartRs485Params/v_00
        - il modulo [hw0UsartIntfc] viene usato da
            - [fnct-core-3real]/[comBufferStatus]
            - [fnct-hw-1trdp-...]/[mcuUsartIntfc]
        - il modulo [fnct-hw-2wrpr-sdk]/[hw0UsartRs485] dipende dal modulo [fnct-core-3real]/[comBufferStatus]
        - il modulo [fnct-core-3real]/[comBufferStatus] dipende dal modulo [hw0UsartIntfc]
        - schema delle dipendenze
            - gruppo di moduli [fnct-core] 
                - dipendenze 
                    - [trdp-sdk]
            - gruppo di moduli [fnct-hw]
                - dipendenze
                    - [fnct-core]
                        - si ricorda che
                            - il modulo [fnct-hw-2wrpr-sdk]/[hw0UsartRs485] dipende dal modulo [fnct-core-3real]/[comBufferStatus]
        - locazione dei moduli di codice
            - 1. scelta ottimale
                - inserire imoduli di codice nel gruppo di moduli [fnct-base_hw]/<namespace fnct::base::hw>
            - 2. scelta che non rispetta il flusso di dipendenzae tra gruppi di moduli
                - inserire i moduli di codice nel gruppo di moduli [fnct-hw]/<namespace fnct::hw> (in particolare nel modulo [fnct-hw-0abst])
                    - in questo caso si crea un loop nelle dipendenze tra i gruppi di moduli [fnct-core] e [fnct-hw]
                        - si ricorda che
                            - il modulo [fnct-hw-2wrpr-sdk]/[hw0UsartRs485] dipende dal modulo [fnct-core-3real]/[comBufferStatus]
                            - il modulo [fnct-core-3real]/[comBufferStatus] dipende dal modulo [fnct-hw-0abst]/[hw0UsartIntfc]


---


- gestione delle dipendenze
    - livelli
        - gruppo di modulio radice
            - esempio
                - [fnct-base]
                    - questo gruppo in realta si riduce ad un unico livello e mette a disposizione le strutture dati utilizaate dai moduli di livello superiore
                    - in pratica definisce le strutture dati e le costanti condivise tra più moduli che possono avere la necessità di non vedersi per evitare eventuali loop di dipendenze
                        - al suo interno avra delle sezioni
                            - [core_threads]
                                - definizioni riguardanti i thread, servono al modulo [core-service]
                            - [core_com]
                                - definizione e interfacce riguardanti i canali sdi comunicazione
                            - [hw]
                        - queste sezioni possono eventualmente essere nuovi moduli radice 
                            - [fnct-base_general]
                            - [fnct-base_core_threads]
                            - [fnct-base_hw]
                                - definizone delle interfacce che il livello [1trdp-sdk] del moduylo [fnct-hw] dovrà implementare
                    - dipendenze
                        - [nessuna]
                - [fnct-core]
                    - questo modulo potrebbe esserre suddiviso in più moduli
                        - [core-thread] la parte dipendente dall'sdk
                            - implementazione 
                                - threads
                            - dipendenze
                                - [fnct-base]
                                - [trdp-sdk-...]
                        - [core-service] la parte astratta indipendente da ogni librerira [trdp]
                            - implementazione dei servizi
                                - timer
                                - state machine
                            - dipendenze
                                - [fnct-base]
                        - [core-com] la parte astratta
                            - implementazione
                                - [comBufferStatus]
                                - [comProtocolStatus_XxX]
                                - [comProtocolStatus_YyY]
                                - [comProtocolStatus_ZzZ]
                            - dipendenze
                                - [fnct-base_hw]
                                - [fnct-core_service]
                        - [core-service-test] fornisce le funzioni di debug del modulo [core-service] e si serve della comunicazione seriale per scambiare le informazioni di debug
                            - dipendenze
                                - [fnct-base_hw]
                                - [fnct-core_service]
                                - [fnct-hw]
                - [fnct-hw]
                    - dipendenze
                        - [fnct-base_hw]
                        - [fnct-core_service]
                        - [fnct-core_com]
                - fnct-hw
                - trdp-sdk-nxp
                - trdp-sdk-mac
            - tra i gruppi di moduli radice 
                - [NON] ci devono essere dipendenze reciproche fino al livello 3 (0abst, 1trdp, 2wrpr, 3real)
                    - i livelli sopra il 4 (4appl, 4test, 5main) possono vedere tutto
                - le dipendenze devono seguire un flusso lineare
                - [NON] devono essere presenti loop



---

Last login: Mon Mar  9 05:15:43 on ttys006

- gestione del parametero [mcuId]
    - [g_mcuId] -> [g_mcuIdOwner]
        - questo è il parametro assegnato a [compile_time] ed è il paramtero che associa il componente al processo che ha quel preciso [mcuId]
    - [p_mcuId] -> [g_mcuIdCurrent]
        - questo parametro è quello passato come parametro nelle funzioni e rappresenta l'[mcuId] del processo e che viene assegnato a [run_time] in particolare dalla linea di comando
            - questo comando può essere impostato anche attraverso la funzione di [init]


---

Last login: Fri Mar  6 04:35:42 on ttys006
Restored session: Thu Mar  5 18:21:19 CET 2026

- i moduli [mcu] hanno una visibilità limitata possono vedere solo il codice SDK
    - class mcuPinPort_t :       public     mcuBase_t           // (specific platform) - (mac) common to all virtual hardware components
                                ,public     shmMcuPinPort_t     // (specific platform) - (mac) low level sdk (mcu registers simnlation)
                                ,public     hwPinPortIntfc_t    // (all platforms)     - component interface
    - class mcuUsartRs485_t :    public mcuBase_t               // (specific platform) - (mac) common to all virtual hardware components
                                ,public shmMcuUsart_t           // (specific platform) - (mac) low level sdk (mcu registers simnlation)
                                ,public comChannelInterface_t   // (all platforms)     - component interface
    - class mcuUsartRs485_t :    public comChannelInterface_t   // (all platforms)     - component interface


- i moduli [hw] hanno una visibilità più ampia ed hanno il compito di connettere le funzioni SDK con quelle di altri componenti
    - class hwPinPort_t :        public mcuPinPort_t        // (specific platform) - sdk module (mac)
                                ,public vhwProxIntfc_t      // (specific platform) - processs (init, loop, end) interface about virtual platforms
    - class hwUsartRs485_t :     public mcuUsartRs485_t     // (specific platform) - sdk module (mac)
                                ,public vhwProxIntfc_t      // (specific platform) - processes (init, loop, end) interface (about virtual platforms)
    - class hwUsartRs485_t :     public mcuUsartRs485_t     // (specific platform) - sdk module (nxp, stm32)
                                ,public hwProxtIntfc_t      // (all platforms)     - processes (init, loop, end) interface 



---

Last login: Thu Mar  5 08:54:24 on ttys006
Restored session: Wed Mar  4 19:59:58 CET 2026

- gestione configurazione dei pin del micro
    - hwGpio::
    - hwPinPortDigital <-> hwPinPort <-> hwPinPortDgtl
    - hwPinPortAnalogic / hwPinPortAnlg
    - hwPortUsart
    - hwPortSpi

- gestione [loops] per i moduli [hw]
    - per  il momento si è deciso di usare il modulo pphManager solo per le piattaforme virtuali
        - in particolare per simulare gli interrupt delle piattaforme reali
    - in questo caso non dovrebbe esistere il modulo pphManager ma solo il modulo hwManger che verrà usato solo nelle piattaforme virtuali
        - il lavoro da faree è il seguente
            - trasferire il modulo pphManager nel modulo hwManager


---

Last login: Wed Mar  4 03:57:23 on ttys001
Restored session: Tue Mar  3 19:47:53 CET 2026

- livelli di dipendenza
    - dipendenza dalla piattaforma
        - dal [micro]
            - dalla [motherBoard]
                - 

- pulizia del codice
    - sembra che il parametro [g_mcuId]
        - non venga utilizzato
        - inoltre
        - è definito <static> nella classe [mcuBase] ma anche nelle classi che da essa derivano!!!
            - è un doppione oltre a non essere utilizzato
                - sarebbe da testare il codice senza questo parametro è devere cosa succede
    - da quanto mi ricordo è stato introdotto per gestire la configurazione dell'hardware nel caso di piattaforma virtuale tra più processi
        - ogni processo/istanza dell'applicazione ha il suo [g_mcuId]
            - in ogni caso npon è chiara la presenza della doppia definizione nella classe [mcuBase] e le sue derivate

- gestione parametri del modulo [pphUsartRs485]
    - si puo usare un file di configurazione per
        - impostare una struttra dati dei parametri
            - questa struttura è caratterisca della piattyaforma o di un gruppo doi poiayttyafortme
                - è il caso delle piataforme virtuali e reali
                - in questo caso la struttura sarà impostata a livello di driver o wrapper
                    - hwUsartInitParams_t
        - oppure
        - impostare direttamente i parametri 

---


- da capire
    - dove introdurre le modifiche/gli aggiornamenti al sdk
        - nel modulo radice 
            - 1trdp-sdk-...
                - forse è meglio evitare di inserirlo qui
                - il motivo o i motivi possono essere
                    - aggiornare l'sdk significa introdurre informazioni che non riguardano direttamente l'hardware come ad esempio la gestione del buffer di comunicazione
                        - si ricorda invece che il modulo 1trdp-sdk **DEVE** riguardare solo l'hardware
            - oppure
            - 2wrpr-sdk-...
                - in base a quanto sopra esposto è bene posizionare le modifiche in questo modulo
        


---

Last login: Sun Feb 22 11:11:14 on ttys006
Restored session: Sat Feb 21 20:59:47 CET 2026

- ci sono due modi per fa eseguire una funzione di callback scritta in c++ da un codice scritto in c
    - definire una variabile globale
        - pro
        - contro
    - usare una funzione di inizializzazione insieme ad una struttura dati che verrà passata alla funzione di inizizializzazione comne puntatore generico [void*]

---

Last login: Sat Feb 21 11:08:11 on ttys006
Restored session: Fri Feb 20 20:30:43 CET 2026

- gestione oggetti modulo [usart] e sue istanze
    - alla routine di interrupt bisogna fargli sapere quale istanza  usart è attiva
        - questo viene fatto con un parametro impostato nella fase di inizializzazione
            - intp_l0
                - intp_l1 (istanza_usart)
        - ci daranno du livelli di inizializzazione 
            - il primo livello è quello che definisce l'stanza del modulo/classe [pphUsart]
            - il secondo livello è quello che definisce l'handler della periferica hardware


---

Last login: Fri Feb 20 08:30:16 on ttys006
Restored session: Thu Feb 19 20:04:14 CET 2026

- [FLEXCOMM0_IRQHandler] in [startup_lpc54608.cpp] nel vettore degli interrupt [g_pfnVectors]
    - [FLEXCOMM0_DriverIRQHandler] 
        - it is called in [startup_lpc54608.cpp]
        - it is defined in [fsl_flexcomm.c]
        - it calls
            - [flexcomm_irq_handler_t] / **s_flexcommIrqHandler[0]((uint32_t *)s_flexcommBaseAddrs[0], s_flexcommHandle[0]);**
                - it is a function pointer 
                    - set by [FLEXCOMM_SetIRQHandler] function
                    - defined  in [fsl_flexcomm.c]

typedef union usart_to_flexcomm // N.B.: this is a UNION data type it means that usart_master_handler is renamed/mapped in flexcomm_handler
{
    flexcomm_usart_irq_handler_t usart_master_handler;
    flexcomm_irq_handler_t flexcomm_handler;
} usart_to_flexcomm_t;

- [FLEXCOMM_SetIRQHandler] is
    - defined in [fsl_flexcomm.c]
    - called in [fs_usart.c] by [USART_TransferCreateHandle] function

---

Last login: Tue Feb 17 11:28:30 on ttys006


- come assegnare i codici di errore
    - intanto è importante capire come estendere i valori del tipo di dato enum che defiisce le costanti di errore
        - vedere
            - Screenshot 2026-02-17 at 17-07-54 Extending enums in C - Stack Overflow
            - Screenshot 2026-02-17 at 17-15-27 About extending enum in C - Stack Overflow



---

Last login: Mon Feb 16 07:41:10 on ttys006
Restored session: Sun Feb 15 20:24:00 CET 2026

- gestione della comunicazione seriale rs485
    - user / [application]
        - 
    - [hwUsartRs485]

---

Last login: Sun Feb 15 10:59:48 on ttys006
Restored session: Sat Feb 14 20:28:32 CET 2026

- albero delle flusso di dipendenze nel propcesso di istanziazione della classe [pphUsartRs485]
    - [pphUsartRs485X_t]
        - description
            - riceve in ingresso i parametri e li passa interamente al modulo wrapper da cui deriva
            - non quasi niente
        - <nested objects>
            - [comProtocolStatusX_t]
                - N.B.: questa classe potrebbe essere anche una classe derivata
        - <derived from>
            - [pphUsartRs485_t]
                - riceve in ingressso
                    - [comProtocolStatusX_t]
                    - [comConfig_t]
        - <constructor inputs>
            - [comConfig_t]
    - [pphUsartRs485_t]
        - description
            - riceve in ingresso i parametri e li passa interamente al modulo wrapper da cui deriva
            - non quasi niente
        - <derived from>
            - [hwUsartRs485_t]
                - riceve in ingressso
                    - [comProtocolInterface_t]/[comProtocolStatusX_t]
                    - [comConfig_t]
        - <constructor inputs>
            - [comProtocolInterface_t]
            - [comConfig_t]
    - [hwUsartRs485_t]
        - descrizione
            - implementa 
                - le funzioni che verranno usate nei livelli più alti ed in particolare di quelli applicativi per
                    - inviare/ricevere pacchetti
                        - txSend
                        - rxReceive
                    - gestire gli errori di comunicazione rx/tx
                    - i prototipi di queste funzioni sono presesenti nella classe derivata [hwUsartInterface_t]
                - la funzione di interrupt (interrupt handler) associata agli interrupt rx/tx
                    - nel caso di piattaforma virtuale implmenta la funzione [vhwLoop] il cui prototipo e definito nella classe derivata [vhwProxIntfc_t]
            - per far questo usa le istanze delle classi
                - [comBufferStatus_t]
                - le funzioni "evento" implementate nella classe derivata [mcuUsartRs485_t]
        - <derived from>
            - [hwUsartInterface_t]
            - [mcuUsartRs485_t]
            - [vhwProxIntfc_t]
        - <nested objects> IS ALMOST EQUIVALENT TO <derived class>
            - [comBufferStatus_t]
                - riceve in ingressso
                    - [comProtocolInterface_t]/[comProtocolStatusX_t]
                    - [comChannelInterface_t]/[this]
        - <constructor inputs>
            - [comProtocolInterface_t]/[comProtocolStatusX_t]
                - descrizione
                    - viene utilizzato per istanziare la classe [comBufferStatus_t]
            - [comConfig_t]
    - [comBufferStatus_t]
        - descrizione
            - lavora in astratto ed implementa i processi tx/rx 
            - in particolare i prototipi delle funzioni che qui vengono implementate sono riportati nella classe [comBufferInterface_t]
            - e riguardano
                - le routine di interrupt per la Tx e per la Rx, rispettivamente
                    - tx_interupt_management
                    - rx_interupt_management
                - che saranno usate dal modulo [hwUsarts485_t]
                - le funzioni necessarie al modulo [hwUsartRs485] per implementare le procedure di tx/rx che verranno usate dagli user
                    - txSend
                    - rxReceive
                    - chkStatusFree
                    - chkStatusRxCompleted
                    - chkStatusTxError
                    - chkStatusRxError
            - gli elementi di cui ha bisogno sono
                - [comProtocolInterface_t]
                - [comChannelInterface_t]
        - <constructor inputs>
            - [comProtocolInterface_t]
            - [comChannelInterface_t]
        - <derived from>
            - [comBufferInterface_t]
                - fornisce il prototipo delle funzioni da implementare 
    - [comBufferInterface_t]
        - descizione
            - gestisce la macchina a stati associata al buffer di comuicazione tx/rx
            - ovvero gestisce il processo di rx/tx in pratica legge/scrive il buffer di comunicazione
                - gli stati rappresentano le fasi nel processo di tx/rx
                    - questi stati sono eseguiti in due thread differenti
                        - un thread è quello assegnato alla fuyzione di interrupt
                        - l'altro thread è quello in cui lo user esegue i comandi messi a disposizione dal modulo
    - [comProtocolInterface_t]
        - esegue l'analisi dei pacchetti per 
            - ottenerne la lunghezza e 
            - controllare la presenza di errori nella loro formattazione
    - [comConfig_t]
        - contiene le funzioni la cui implementazione necessita di conoscenze ed informazioni che sono di pertinenza esclusiva dei livelli più alti
            - ad esempio
                - l'impostazione dei pin di tx/rx enable per un canale rs485
    - [hwUsartInterface_t]
        - fonisce il prototipo delle funzioni che defiscono un modulo [hwUsart]
    - [mcuUsartRs485_t]
        - implementa le funzioni evento del processo di rx/tx legate all'hardware
            - scittura/lettura dei registri usart della mcu
            - abilita/disabilita il tx/rx del canale rs485
                - in questo caso usaerà l'istanza della classe [comConfig_t] che gli viene passata come parametro
            - abilita/disabilita gli interrupt
            - N.B.: i prototipi delle funzioni evento sono presenti nella classe derivata [comChannelInterface_t]
        - <derived from>
            - [comChannelInterface_t]
    - [vhwProxIntfc_t]


---

Last login: Thu Feb 12 08:35:19 on ttys006
Restored session: Wed Feb 11 19:44:13 CET 2026



---

Last login: Tue Feb 10 07:53:54 on ttys006
Restored session: Mon Feb  9 20:01:29 CET 2026


- le domande che bisogna porsi per l'implementazione dei moduli/classi
    - <quante istanze può avere? (le istanze si riferiscono al modulo "owner" )>
        - [una]
        - [multiple]
    - <ci sono istanze di altri moduli? (questi moduli sono definiti "guest" )>
        - [in_caso_AFFERMATIVO]
            - <le istanze del modulo "guest" sono statiche o dinamiche?>
            - <le istanze di cui al punto precedente si riferiscono ad un unica classe o ad un gruppo di classi rappresentati da un interfaccia comune? >
            - [nel_caso] di
                - [unico_modulo]
                    - <l'istanza viene passata come parametro o viene creata all interno del modulo "owner"?>
                - [gruppo_di_moduli]
    - <svolge dei servizi? / esegue funzioni di callback?>
        - <le funzioni di callback sono parametri (puntatori a funzione) statici o dinamici?>
            - [nel_caso]
                - [statico]
                    - <l'impostazione è valida per tutte le applicazioni o ogni applicazione può avere la sua?>
                - [dinamico]


- gestione delle funzioni di [callback]
    - [nel_caso] di moduli implementati con
        - [linguaggio_c]
            - [caso_1]: definizione statica
                - definizione di una funzione [weak] che può essere ridefinita in moduli esterni
                    - la funzione è valida per tutte le "istanze" non può essere configurata quindi è impostata a [compile_time]
            - [caso_2]: definizione dianamica
                - viene passata come paramero ad una funzione di inizializzazione, quindi viene impostata a [run_time]
        - [linguaggio_c++]
            - [caso_1]: definizione statica
                - forse ancora più semplice dello stesso caso nel linguaggio c, infatti è sufficente definirla nel .h poi la si può implementare in qualunque altro modulo
                - N.B.: questa cosa è resa possibile dal momento che l'implementazione della funzione richiede di specificare la classe a cui appartiene
			- [caso_2]: definizione dinamica
                - viene passata come parametro nel costruttore o in una funzione di inizializzazione in entrambe i casi viene impostata a [run_time]


---

Last login: Mon Feb  9 08:21:47 on ttys006

- le domande che bisogna porsi per l'implementazione dei moduli/classi
    - <quante istanze può avere? (le istanze si riferiscono al modulo "owner" )>
        - [una]
            - ovvero è una classe [singletone] ovvero statica
            - non c'è bisogno di istanziarla
        - [multiple]
            - per usare questo modulo deve essere istanziata la classe
    - <ci sono istanze di altri moduli? (questi moduli sono definiti "guest" )>
        - [in_caso_AFFERMATIVO]
            - <le istanze del modulo "guest" sono statiche o dinamiche?>
            - ovvero: questa istanza è statica (unica istanza del modulo "guest" per tutte le istanze del modulo "owner") o dinamica (ogni istanza del modulo "owner" può avere la sua istanza del modulo "guest" )?
            - <le istanze di cui al punto precedente si riferiscono ad un unica classe o ad un gruppo di classi rappresentati da un interfaccia comune? >
            - [nel_caso] di
                - [unico_modulo]
                    - <l'istanza viene passata come parametro o viene creata all'interno del modulo "owner"?>
                - [gruppo_di_moduli]
                    - si dovrà definire un puntatore al modulo interfaccia
                        - sarà un parametro statico 
                            - in questo caso il puntatore è una variabile statica è dovrà essere definita o nello stesso modulo o in un modulo di livello superiore
                        - o dinamico
                            - in questo caso il puntatore può essere passato come parametro nel costruttore
    - <svolge dei servizi? / esegue funzioni di callback?>
        - ovvero, vengono eseguite funzioni di [callback] (parametri che sono [puntatori_a_funzione])?
        - [in_caso_AFFERMATIVO]
            - <le funzioni di callback sono parametri (puntatori a funzione) statici o dinamici?>
            - queste funzioni di [callback] sono un parametro statico (valido per tutte le istanze) o dinamico (ogni istanza ha il suo puntatore a funzione)?
                - [nel_caso]
                    - [statico]
                        - <l'impostazione è valida per tutte le applicazioni o ogni applicazione può avere la sua?>
                        - impostate a [compile_time] quindi eseguito il build di un applicazione 
                            - N.B.: si possono cambiare queste impostazioni ma si deve eseguire di nuovo il build dell'applicazione
                                - ovvero ogni progetto/applicazione può avere la sua impostazione
                    - [dinamico]
            - queste funzioni sono implementate in [linguaggio_c] o [linguaggio_c++]
            - [nel_caso] di moduli implementati in 
                - [linguaggio_c] le funzioni di [callback] possono essere raggruppate in una unica struttura
                    - come e quando istanziare questa struttura che contiene le funzioni di [callback]
                        - [nel_caso] il modulo [sdk]
                            - <HA><> tutte le informazioni & tutte conoscenze per implementare completamente queste funzioni 
                                - l'istanza di questa struttura può essere definita dal modulo [sdk]
                            - <NON HA> tutte le informazioni & conoscenze per implementare <completamente> ma solo <parzialmente> tutte queste funzioni
                                - [nel_caso] queste informazioni 
                                    <POSSANO> essere gestite come parametri di configurazione
                                        - l'istanza di questa struttura può essere definita dal modulo [sdk]
                                        - ma si dovranno gestire opportunamente dei file di configurazione
                                - [nel_caso] queste conoscenze (sotto-procedure complesse) 
                                    - <POSSANO> essere ricondotte ad una funzione di [callback]
                                        - l'istanza di questa struttura può essere definita dal modulo [sdk]
                                        - ma si dovranno gestire opportunamente le funzioni di [callback]
                                        - e quindi si ritorna al caso di un modulo con funzioni di [callback] ovvero che svolge dei servizi
                                            - potranno essere 
                                                - [statiche] (ovvero uniche)
                                                    - definite come variabili globali [extern] e quindi definite esternamente al modulo [sdk] in moduli a più alto livello
                                                - [dinamiche] (più di una possibile)
                                                    - passate come parametri in funzioni di inizializzazione
                                    - <NON POSSANO> essere ricondotte ad una funzione di [callback]
                                        - moduli a livello più alto, in particolare il primo a partire dal modulo [sdk], implementeranno queste funzioni e l'ultimo di questi avrà la possibilità di istanziare l'intera struttura inserendovi le funzioni implementate nei moduli a livello più basso
                        - questa struttura può essere istanziata dal modulo [sdk] 
                            - in questo caso tutte le funzioni deve averle implementate
                            - in caso conter
                    - o dai moduli a più alto livello da essi 
                - [linguaggio_c++] le funzioni di callback faranno parte di un modulo/classe interfaccia del gruppo dei moduli/classe a livello [sdk] che implementano il canale di comunicazione
                    - si definirà come parametro un puntatore al modulo/classe interfaccia di cui si è fatta menzione appena sopra
                    - a questo parametro verrà assegnata un istanza di un modulo/classe "reale" 
                        - [nel_caso] di parametro statico
                            - definita staticamente in un modulo di livello superiore
                        - [nel_caso] di parametro statico
                            - passata come parametro nel costruttore
    - ci sono funzioni statiche che devono essere implementate da mdouli esterni di più alto livello?
        - in fin dei conti sono funzioni di [callback]



- un modulo/classe 
    - ha degli input
        - questi input possono essere passati
            - a compile-time
                - alcuni possono far parte della configurazione
            - a run-time
        - gli input possono essere
            - tipi di dati "semplici"
                - come stringhe, puntatori a carattere, interi, puntatori di array di interi, etc.
            - puntatori a funzioni
                - questi puntatori a funzione possono essere dei parametri dinamici e non statici quindi ogni istanza può avere puntatori a funzioni differenti da quelli di un'altra istanza
                    - nel caso siano statici e possibile definire un puntatore a funzione statico e poi impostarlo in un modulo/classe di più alto livello
            - puntatori di istanze di altri moduli/classi
        - 
    - collabora
        - con istanze di altri moduli/classi
            - significa che 
                - chiama delle funzioni di questi moduli/classi
                - e a sua volta questi moduli/classi chiamano delle funzioni del corrente modulo/classe
                    - per evitare loop pericolosi nella sequenza delle dipendenze uno dei due moduli deve essere sdoppiato in modo che 
                        - la seguenza delle dipendenza diventi
                            - classe A.2 -> classe B -> classe A.1

- analisi del modulo/classe [comProtocolStatus]
    - <quante istanze può avere?>
        - [multiple]
            - in base al buffer a cui verrà associato
                - questa associazione verrà fatta ad un livello superiore
            - uno stesso protocollo può essere usato in canali diversi di comunicazione
            - ad esempio
                - usart con due canali distinti di comunicazione che possono lavorare in contemporanea
                - spi
            - e queste canali possono essere contemporaneamente attivi
    - <ci sono istanze di altri moduli?>
        - [no]
    - <svolge dei servizi? / esegue funzioni di callback?>
        - [si]
            - <le funzioni di callback sono parametri statici o dinamici>
- analisi del modulo/classe [comBufferStatus]
    - quante istanze può avere?
        - multiple
            - tante quanti sono i canali di comunicazione che possono essere contemporaneamente attivi
                - il canale di comunicazione viene determinato a propria insaputa (nel senso che viene deciso ad un livello superiore, ovvero il modulo/classe che identificherà il canale di comunicazione) in base alla scelta delle funzioni [sdk]
                - ad esempio, i canali di comunicazioni possono essere
                    - usart
                    - spi
                    - ethernet
                    - etc.
    - ci sono istanze di altri moduli?
        - [si]
            - istanza del modulo [comProtocolStatus]
            - le istanze di questo modulo si riferiscono ad un unico modulo/classe oppure fanno riferimento ad un gruppo di moduli identificato dalla loro interfaccia comune
                - fanno riferimento ad un gruppo di moduli/classi
                    - infatti il buffer può gestire pacchetti con differenti protocolli
                - quindi tra i prametri ci sara il puntatore all'interfaccia dei protocolli in particolare al modulo [comProtcolInterface]
                - il puntatore gli verrà passato come parametro nel costruttore
    - svolge dei servizi
        - [si]
            - in particolare esegue gli handler degli eventi collegati alla procedura di invio dati nel canale di comuniocazione che sono implementati in un modulo SDK (ma non tutte!!!), questi eventi sono
                - tx_eventStartUp       (eseguito in un application thread)
                - tx_eventBegin         (eseguito in interrupt)
                - tx_eventSendByte      (eseguito in interrupt)
                - tx_eventLastByte      (eseguito in interrupt)
                - tx_eventEnd           (eseguito in interrupt)
            - N.B.: si può verificare il caso in cui il modulo [sdk] che dovrebbe implmentare queste funzioni non abbia sufficenti informazioni (parametri di configurazione) o conoscenze (sotto-procedure) per farlo
                - quindi il modulo che le implementerà sara
                    - il primo modulo tra quelli a livello più alto, a partire dal modulo [sdk], che ha tutte le informazioni/conoscenze per implementare le funzioni
            - queste funzioni di [callback] sono un parametro statico (valido per tutte le istanze) o dinamico (ogni istanza ha il suo puntatore a funzione)?
                - dinamico
                    - infatti il modulo [comBufferStatus] può essere associato a più canali di comunicazione
                        - N.B.: l'associazione al canale di comunicazione viene fatto da un modulo/classe di livello più alto in particolare nel caso venga associato al canale di comunicazione seriale rs485 il modulo di livello più alto sarà il [pphUsart_Rs485]
            - [nel_caso] di moduli implementati in 
                - [linguaggio_c] le funzioni di [callback] possono essere raggruppate in una unica struttura
                    - come e quando istanziare questa struttura che contiene le funzioni di [callback]
                        - [nel_caso] il modulo [sdk]
                            - <HA><> tutte le informazioni & tutte conoscenze per implementare completamente queste funzioni 
                                - l'istanza di questa struttura può essere definita dal modulo [sdk]
                            - <NON HA> tutte le informazioni & conoscenze per implementare <completamente> ma solo <parzialmente> tutte queste funzioni
                                - [nel_caso] queste informazioni 
                                    <POSSANO> essere gestite come parametri di configurazione
                                        - l'istanza di questa struttura può essere definita dal modulo [sdk]
                                        - ma si dovranno gestire opportunamente dei file di configurazione
                                - [nel_caso] queste conoscenze (sotto-procedure complesse) 
                                    - <POSSANO> essere ricondotte ad una funzione di [callback]
                                        - l'istanza di questa struttura può essere definita dal modulo [sdk]
                                        - ma si dovranno gestire opportunamente le funzioni di [callback]
                                            - potranno essere 
                                                - [statiche] (ovvero uniche)
                                                    - definite come variabili globali [extern] e quindi definite esternamente al modulo [sdk] in moduli a più alto livello
                                                - [dinamiche] (più di una possibile)
                                                    - passate come parametri in funzioni di inizializzazione
                                    - <NON POSSANO> essere ricondotte ad una funzione di [callback]
                                        - moduli a livello più alto, in particolare il primo a partire dal modulo [sdk], implementeranno queste funzioni e l'ultimo di questi avrà la possibilità di istanziare l'intera struttura inserendovi le funzioni implementate nei moduli a livello più basso
                        - questa struttura può essere istanziata dal modulo [sdk] 
                            - in questo caso tutte le funzioni deve averle implementate
                            - in caso conter
                    - o dai moduli a più alto livello da essi 
                - [linguaggio_c++] le funzioni di callback faranno parte di un modulo/classe interfaccia del gruppo dei moduli/classe a livello [sdk] che implementano il canale di comunicazione
                    - 
- analisi del modulo/classe [pphUsart_Rs485]



---

Last login: Fri Feb  6 08:03:02 on ttys006

- definizione struttura che contiene le funzioni di callback (puntatori a funzioni) usate nel modulo comBufferStatus
    - comBufferStatus_CallbackFunctions_t
        - tx_beginProcedure
        - tx_endProcedure
        - tx_regWrite       (void*, uint8_t)
        - rx_regRead        (void*)
    - sdkUsart_callbackFunctions_t

- come si defisce l'istanza del modulo [ppUsart]
    - questo modulo fornisce il servizio di invio e ricezioni dati attraverso la comuicazione seriale quindi su canali [rs232] o [rs485]
        - questo modulo deve essere configurato
            - istanza del modulo [comProtocolStatus]
                - deve conoscere il tipo di protocollo che deve essere usato
                    - dovra essere presente nel costruttore come parametro di ingresso 
                    - o in caso fosse assente considerare una istanza di default chè figurerà come parametro
            - l'istanza del modulo [comBufferStatus] è un parametro del modulo
            - istanza della struttura [comProtocolStatus_callbackFunctions]
                - questa istanza associa al modulo [comBufferStatus] il modulo collegato all'hardware quindi un modulo appartenente all'[SDK]
            - istanza [sdkUsart_callbackFunctions]
                - qui viene implementata con le funzioni del modulo [comBufferStatus]


---

Last login: Thu Feb  5 11:15:41 on ttys006

- sarebbe opportuno creare un interfaccia per la classe [comProtocolStatus] da cui poi essa deriverà


void hwUsartIntfc_t::Tx       (uint8_t p_Num)  {
    dgFormatDigit l_FormatNum (&p_Num, 1, DIGIT_NUM_3, dgFormatDigit::kEncoding_Decimal, 0, false);
    l_FormatNum.vValueToString();

    if(uyProtocol::status_get_tx__free())   {
        // ------------------------------
        rs485_TxPinEnable();
        uyProtocol::send_non_blocking((uint8_t* ) l_FormatNum.m_StringValueField);
        USART_TxIntEnable();
        uyProtocol::waitingTxCompleted();
    }
}


---

Last login: Wed Feb  4 08:47:02 on ttys006
Restored session: Tue Feb  3 19:51:05 CET 2026

- gestione dei buffer di comunicazione
    - quando si vuole inviare un pacchetto potrebbe non essere necessario specificare il size
        - il size lo si puo ricavare
        - casi d'uso in cui sia necessario o meno specificasre il size
            - NECESSARIO
                - un buffer con dati binary
                    - definito come [uint8_t*]
                    - in questo caso non è possibile ricavare il size
            - NON necessario
                - una stringa di caratteri
                    - definita come [char*]
                    - in questo caso si può ricavare il size determinando la posizione del carattere nullo
                - pacchetti con protocollo
        - in ogni caso ci sarà sempre un limite di default ad esempio 100 o 200, etc. che viene imposto al size
            - nel caso della trasmissione non è strettamente necessario specificare il size dal momento che sul buffer non viene compiuta nessa scrittura
            - diversa è la situazione per il buffer di ricezione che deve sempre specificare il size dato che verrà scritto

- gestione degli stati del buffer
    - si può pensare di impostare la comunicazione in questo modo
        - la ricezione è sempre attiva
        - a meno che non si debba inviare qualche pacchetto
        - gestione della ricezione
            - si controlla lo stato del buffer
                - se [free]
                    - si avvia la ricezione impostando lo stato in [rx_waiting_packet]
                - se [rx_completed]
                    - si esegue l'analisi del pacchetto ricevuto
                        - se necessario si può eseguire una copia del pacchetto per liberare il buffer di ricezione e disporlo a ricevee nuovi pacchetti
                    - si imposta lo stato in [free]
                    - oppure pronto ad inviare una risposta 
                        - N.B.: in questo caso non ci sarà nessuna attesa per impostare il buffer di trasmissione
        - gestione della trasmissione

---

Last login: Sat Jan 31 07:51:34 on ttys006

- [mpfw_fw2-appl-app20250424-4appl]
    - [app_pphUsartProtocol]
- [mpfw_fw2-fnct-core-3real]
    - [uyProtocol]
        - [receive_non_blocking]
- [mpfw_fw2-fnct-hw-1trdp-sdk-mac]
    - [mcuUsat]
        - [check_read_write]
            - 
                - // // check status rxBuffer then read data
                - // if(g_callback_protocol_functions.rx_status_get__waiting_packets()) {
                - //     g_callback_protocol_functions.rx_status_set__running();
                - // }
            -   
                - // // reset rx status (when a malformed packet is received) if it is set to "running"
                - // if(g_callback_protocol_functions.rx_status_get__running()) {
                - //     g_callback_protocol_functions.rx_status_set__free();
                - // }
- [mpfw_fw2-fnct-hw-2wrpr-sdk]
    - [hwUsartIntfc]
        - [Tx]
        - [Rx]
- [mpfw_fw2-fnct-hw-3real]
    - [pphUsart]
        - [rxBuff_receive]
- [mpfw_fw2-fnct-tui-3real] 
    - [tuiFnctRealUnit3McuUsartX]
        - [loop]
        - [sendMessage]




---

string is empty. 
string is empty. 
string is empty. 
string is empty. 
string is empty. 

string is empty. 
string is empty. 

string is empty. 
31313131313536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141511111111

31313131313536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141511111111
33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141533333333

33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314153333333
0^a
32323232323536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314152222222
31313131313536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314151111111
31313131313536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314151111111

33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314153333333
32323232323536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314152222222

33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141533333333
3232323232 353637 3839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F101112131415 22222222
3131313131 353637 3839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F101112131415 1111111
3131313131 353637 3839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F101112131415 1111111

01u|AAhffdsyte786dsghfd|
01u|BBffdsyte786dsghfd|
123456789-01u|ghffdsyte786dsghfd|
-1234-01u|xx_0_yeg__hermann|
0102301u/ghffdsyte786dsghfH\
0102801u/ghffdsyte786dsghfH12345

01u|ghffdsyte786dsghfd|
01u|ghffdsyte786dsghfd5|
01u|ghffdsyte786dsghfd56|

01u|ghffdsyte786dsghfd234|

01u|ghffdsyte786dsghfd12345|
01u|ghffdsyte786dsghfd1234|

31313131313536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141511111111
33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F10111213141533333333

0102901u/ghffdsyte786dsghfH1234567
0102601u/ghffdsyte786dsghfH1234
0102901u/ghffdsyte786dsghfH1234567
0103001u/ghffdsyte786dsghfH12345678
0103001u/ghffdsyte786dsghfH12345678
0102801u/ghffdsyte786dsghfH123456
0102701u/ghffdsyte786dsghfH12345


0102301u/ghffdsyte786dsghf1uuP
0102301u/ghffdsyte786dsghf1uu
0102301u/ghffdsyte786dsghf1uuP
0102301u/ghffdsyte786dsghf1uuPQR
0102301u/ghffdsyte786dsghf1uuPQRS

0102301u/ghffdsyte786dsghfH

0102801u/ghffdsyte786dsghfH12345
33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314153333333
0102801u/ghffdsyte786dsghfH12345
33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314153333333

string is empty. 
string is empty.-
33333333333536373839303132333435363738393031323334356162636465666768696A6B6C6D6E6F707172737475767778797A000102030405060708090A0B0C0D0E0F1011121314153333333

---

Last login: Fri Jan 23 07:59:13 on ttys004

- file di configurazione
    - chi lo deve vedere?
        - mi fa capire chi sarà il proprietario di questo file di config
    - dipende da chi?
        - dalla applicazione?
        - da moduli radice (moduli di libreria) più specifico dell'applicazione?
        - mi fa capire quale modulo radice non proprietario ha  bisogno di impostarlo

- gestione uyProtocol
    - nella determinazione della lunghezza del paccketto
        - lo shift del buffer riguarda solo la ricezione
            - ed ha lo scopo di non memorizzare un eventuale serie di caratteri sporchi all'inizio del pacchetto


---

Last login: Thu Jan 22 08:20:49 on ttys004

- quando si chiude una versione ricordarsio di memoprizzare anche la configurazione dei sorgenti
    - fare un copia e incolla dell'output del comando
        - build_platform_cmake2.sh mac "mac;ncurses"

---

Last login: Wed Jan 21 08:07:11 on ttys004

- getione ITC
    - un buffer di comunicazione inter-thread
        - [produttore/consumatore] or [scrittore/lettore]
        - ci sarà un [id_lettore] l'id a cui è destinato il messaggio
    - identificare i loop bloccanti nei vari moduli in modo da facilitare le analisi per possibili situazioni di stallo


            # send the command "SET MASTER" to device with addr "1"
            [01u|91100|]

            # send the command "SET SLAVE"  to device with addr "3"
            [01u|93200|]

            # send the command "SET ADDRESS" to device with addr "3" changing its address from "3" to "5"
            [01u|93305|]

            #send the packet to device with addr "5"
            [01u|95jshud...hghgsy|]
        
---

Last login: Tue Jan 20 08:36:52 on ttys005
Restored session: Mon Jan 19 20:26:36 CET 2026

- creare una funzione di sistema [exit()]
    - questa funzione devono vederla tutti i moduli
        - deve essere definita nel modulo radice [base-0abst]
    - questa funzione deve essere configurata 
        - quindi sarà una funzione di callback che verrà impostata in un modulo radice di livello superiore

- i messaggi di debug "eseguiti" nei moduli di [hw] girano su un thread diverso dei moduli [tui] 
    - quindi a rigore si devono gestire con dei passaggi intermedi che possono essere affidati ad un gewstore di comunicazione Inter-Threads
        - si potrebbe pensare ad un sistema di questo tipo
            - si chiama un gestore che fornisce un servizio di esecuzione puntatore di funzioni
                - callManager::perform/exec(threadSource, ptrFunction, threadDestination)
                - callManager::loop(idThread)
                    - possibilità di conflitti
                        - se ad esempio
                            - il [thread(1)] ha chiesto di eseguire una funzione nel [trhread(3)]
                            - e viceversa
                            - allora c'è un conflitto, l'ultimo arrivato si vedrà negata l'esecuzione
                                - oppure lui stesso dovra eseguire la funzione 
                                    - ma questo è possbile??

---

Last login: Mon Jan 19 08:15:47 on ttys001

- analisi flusso delle istruzioni nella gestione della comunicazione seriale
    - 

- "la mia regola è non avere regole" (detto da Jocker nel film "Batman begins" di Christopher Nolan)
    - quindi nelle stesse condizioni e stessi input non si ha mai uno stesso comportamento/risposta
    - il contrario del side-effect che con lo stesso input si ha sempre lo stesso output



---

Last login: Mon Jan 12 08:21:43 on ttys002
Restored session: Sun Jan 11 20:22:12 CET 2026

- analis delle dipendenze e aggiunta di nuovi moduli radice
    - i moduli radice relativi alle funzionalità si possono distinguere in due grandi categorie
    - o forse meglio pensare in termini di livelli di generalità
        - ci sara un modulo radice "base" il più generale di tutti
            - questo siginifica che è adattato per tutte le applicazioni
        - ci saranno, via via, dei moduli sempre più specifici per un più ristretto inisieme di applicazioni

- i moduli "class" [tuiCplt]
    - sono i moduli il cui nome inizia con "tuiCplt" che sta per [tui_Complete] ovvero sono classi derivate dalle due classi base della libreria [tui] ovvero [tuiFnct] e [tuiGraph]
    - questi moduli dal momento che dipendono dai due moduli [tuiFnct] e [tuiGraph] si trovano in un moduilo radice di livello [3real]
    - di questi moduli ci saranno moduli più generali e moduli più specifici
        - inoltre i moduli più specifici potranno dipendere ma non necessariamente da quelli più generali
        - schematicamente l'albero delle dipenendenze potrà avere questa struttura
            - [fnct_tui_3real_trdp_appG2]
                - [fnct_tui_3real_appG1]
                    - ...
                    - [fnct_tui_3real]
                - [fnct_tui_0abst_trdp_appG2]
                    - [fnct_tui_0abst] optional
        - esempio pratico
            - gestione del componente [tui] che visualizza la lista dei processi attivi
            - [mpfw_fw2-fnct-tui-3real-trdp-sdk-mac]
                - [fnct_tui_3real]
                    - [mpfw_fw2-fnct-tui-2wrpr-ui] or [mpfw_fw2-fnct-tui-2wrpr]
                        - [fnct_tui_0abst]
                - [mpfw_fw2-fnct-tui-0abst-trdp-sdk-mac]
                    - [fnct_hw_0abst-trdp-sdk-mac]
                    - [fnct_base_0abst]


- imoduloi 


---

Last login: Tue Jan  6 08:46:19 on ttys002
Restored session: Mon Jan  5 20:34:00 CET 2026

- per fare le cose corrette si dovrebbe pensare di creare il servizio [pphManager] per eseguire su thread diversi im loopdelle varie periferiche
    - in questo modo si nasconderebbe la gestione del loop virtuale per la simulazione su piattaforma mac
    - adesso si può trovare un compromesso  permettendo al [pphManager] di eseguire esplicitamante il loop virtuali delle unita chiamando òa funzione [vhwLoop] oppure lasciare l'implementazione al modulo wrapper [hwManager]

- gestione dell'hardware virtuale usato nella siumulazione
    - nuovi possibili moduli
        - [mpfw_fw2-fnct-hw-0abst-trdp-sdk-mac]
            - questo modulo dipende dal modulo [mpfw_fw2-fnct-hw-0abst]
        - [mpfw_fw2-fnct-tui-0abst-trdp-sdk-mac]
            - questo modulo dipende dal modulo [mpfw_fw2-fnct-hw-0abst]

- gestione delle dipendenze tra moduli
    - livello [0abst]
        - questo livello dipende solo dai moduli di livello [0abst] di altri moduli
        - all'interno di un gruppo di moduli si possono avere più moduli di livello [0abst]
        - nel nome del modulo ci deve essere anche un riferimento alle dipendenze
            - considerare ad esempio i moduli
                - [mpfw_fw2-fnct-hw-0abst]
                    - c'è solo il riferimento al proprio gruppo
                    - quindi questo modulo all'interno del suo gruppo non dipende da altri moduli 
                    - può però dipendere da moduli di livello [0abst] di altri [gruppi]/[funzionalità] di moduli 
                    - N.B.: i [gruppi] di moduli sono un insieme di moduli suddivisi per livelli di dipenedenza e astrattezza che servono per implementare una [funzionalità]
                - [mpfw_fw2-fnct-hw-0abst-trdp-sdk-mac]
                    - ci sono i riferimenti al proprio gruppo [hw] e a [trdp-sdk-mac] quindi questo modulo
                    - può dipendere dal modulo [mpfw_fw2-fnct-hw-0abst] e certamente da un modulo [0abst] e/o [0abst-trdp-sdk-mac] di qualche altra [funzionalità]


---

Last login: Mon Jan  5 08:26:34 on ttys002


- gestione del codice [trdp]
    - il codice [trdp] è quello sviluppato da terze parti ed importato nel ambiente di sviluppo [mpfw_fw2]
        - per il fatto che è sviluppato da terze parti non ha alcuna dipendenza con il codice [mpwf_fw2]
            - quindi anche il codice [sdk] relativo alla piattaforma mac deve avere questa caratteristica
                - in questa ottica dovrebbe essere rivista la locazione dei seguenti moduli / files
                    - [fnct/hw/layer/mpfw_fw2-fnct-hw-0abst/src/config/dtyHwCfgUsart.h]
                    - [fnct/hw/layer/mpfw_fw2-fnct-hw-0abst/src/dty/general/sdk_dtyPtfmHwGnrlTypesDefs.h]
                        - dipende dalla piattaforma
                    - [fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuUsart/v_02/mcuUsartTypeDefs.h]
                    - [fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuDeviceConfig.h]
                    - [fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/mcu/mcuBase]
            -  quindi il codice dei moduli [wrpr] non è necessario che implementino delle classi derivate specie nel caso di codice [trdp] sviluppato in linguaggio C
    - le aggiunte/modifiche al codice [mpfw_code/trdp] che dipendono da moduli [fnct] è corretto inserirli nel gruppo di moduli [mpfw_code/fnct] nel caso possano essere associati a moduli specifici
        - nel caso che queste aggiunte/modifiche siano generali e valide per tutti i moduli si posson inserire nel gruppo di moduli [mpfw_code/trdp]

- importante editare pph -> hw -> mcu
    - la parte dipendente dalla piattaforma non sarebbe da ereditare ma da insrire come mebro
        - il problema è che l'implementazione del wrapper 
- capire bene come strutturare un modulo wrapper [wrpr]
    - quali regole adottare
        - ad esempio
            - quali sono i moduli/classi che devono essere implementati in tutte le situazioni (nel caso specifico dell'hardware in tutte le piattafornme)
            - questi moduli devono stare nella folder [trdp] del [modulo]
            - ed in particolare sotto la folder [intfc]

---

Last login: Sun Jan  4 07:58:20 on ttys002
Restored session: Sat Jan  3 20:05:21 CET 2026

- passaggio dei parametri di init hardware
    - si puo fare
        - modulo [wrpr]
            - common
                - ATTENZIONE!!!! 
                    - i moduli superiori devono fare riferimento solo ai file header [.h] presenti in [common] e non in [trdp]
                    - nella sezione [trdp] vanno messe le implementazioni lasciate dalla sezione [common] perche fanno riferimento a codice [trdp]
                - hwManagerIntfc.h
                    - definizione
                        - void init (void)
            - trdp
                - mac
                    - hwManagerMac.h
                        - #include "hwManagerIntfc.h"
                            - implementazione
                                - void hwManagerIntfc_t::init (void)    { ... }
                - mac
                    - hwManagerNxp.h
                        - #include "hwManagerIntfc.h"
                            - implementazione
                                - void hwManagerIntfc_t::init (void)    { ... }


---

Last login: Sat Jan  3 10:17:57 on ttys002
Restored session: Fri Jan  2 19:56:55 CET 2026


pphModule & uyProtocol - step 2 - (tuiManager & pphManager [loop] run in different thread) - build is OK / first debug is OK

---

Last login: Fri Jan  2 08:33:43 on ttys002

    - FNCT-HW-3REAL_SRC_CFG: ~~~~~~~ 05                      FNCT-HW-3REAL_WSP_VER: ~~~~~~~ 07hw_3
        - FNCT-HW-2WRPR-SDK_SRC_CFG: ~~~~~~~ 01              FNCT-HW-2WRPR-SDK_WSP_VER: ~~~~~~~ 06hw_2
            - FNCT-CORE-3REAL_SRC_CFG: ~~~~~~~ 06            FNCT-CORE-3REAL_WSP_VER: ~~~~~~~ 27cor3
                - FNCT-CORE-2WRPR_SRC_CFG: ~~~~~~~ 03        FNCT-CORE-2WRPR_WSP_VER: ~~~~~~~ 24cor2
            - FNCT-HW-1TRDP-SDK-MAC_SRC_CFG: ~~~~~~~ 03      FNCT-HW-1TRDP-SDK-MAC_WSP_VER: ~~~~~~~ 05hw_1
                - FNCT-HW-0ABST_SRC_CFG: ~~~~~~~ 00          FNCT-HW-0ABST_WSP_VER: ~~~~~~~ 01hw_0
                    - FNCT-BASE-0ABST_SRC_CFG: ~~~~~~~ 00    FNCT-BASE-0ABST_WSP_VER: ~~~~~~~ 00base

    - APPL-APP20250424-4APPL_WSP_VER: ~~~~~~~ 11appl
        - FNCT-TUI-3REAL_WSP_VER: ~~~~~~~ 10tui3
            - FNCT-HW-3REAL_WSP_VER: ~~~~~~~ 07hw_3
                - FNCT-HW-2WRPR-SDK_WSP_VER: ~~~~~~~ 06hw_2
                    - FNCT-CORE-3REAL_WSP_VER: ~~~~~~~ 27cor3
                        - FNCT-CORE-2WRPR_WSP_VER: ~~~~~~~ 24cor2
                    - FNCT-HW-1TRDP-SDK-MAC_WSP_VER: ~~~~~~~ 05hw_1
                        - FNCT-HW-0ABST_WSP_VER: ~~~~~~~ 01hw_0
                            - FNCT-BASE-0ABST_WSP_VER: ~~~~~~~ 00base
            - FNCT-TUI-2WRPR-UI_WSP_VER: ~~~~~~~ 07tui2
                - FNCT-TUI-0ABST_WSP_VER: ~~~~~~~ 06tui0
                    - FNCT-HW-0ABST_WSP_VER: ~~~~~~~ 01hw_0
                        - FNCT-BASE-0ABST_WSP_VER: ~~~~~~~ 00base
-- Start set_public_rpath of -->> APPL-APP20250424-4APPL <<--
-- Start set_public_rpath of -->> FNCT-TUI-3REAL <<--
-- Start set_public_rpath of -->> TUI/3REAL <<--
-- Start set_public_rpath of -->> FNCT-HW-3REAL <<--
-- Start set_public_rpath of -->> FNCT-HW-2WRPR-SDK <<--
-- Start set_public_rpath of -->> FNCT-CORE-3REAL <<--
-- Start set_public_rpath of -->> CORE/3REAL <<--
-- Start set_public_rpath of -->> FNCT-CORE-2WRPR <<--
-- Start set_public_rpath of -->> CORE/2WRPR <<--
-- Start set_public_rpath of -->> HW/2WRPR <<--
-- Start set_public_rpath of -->> FNCT-HW-1TRDP-SDK-MAC <<--
-- Start set_public_rpath of -->> HW/1TRDP_SDK <<--
INFO - Config dir is just registered by FNCT-HW-1TRDP-SDK-MAC__FNCT-HW-0ABST_CONFIG__RPATH with "fnct/hw/layer/mpfw_fw2-fnct-hw-1trdp-sdk-mac/src/config/hw0abst" relative path
-- Start set_public_rpath of -->> FNCT-HW-0ABST <<--
-- Start set_public_rpath of -->> FNCT-BASE-0ABST <<--
-- Start set_public_rpath of -->> BASE <<--
-- Start set_public_rpath of -->> FNCT-TUI-2WRPR-UI <<--
-- Start set_public_rpath of -->> FNCT-TUI-0ABST <<--
-- Start set_public_rpath of -->> APPL <<--
INFO - Config dir is just registered by APPL-APP20250424-4APPL__FNCT-CORE-2WRPR__CONFIG__RPATH with "appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/config/core2wrpr/krThread/v_00" relative path
    - APPL-APP20250424-4APPL_SRC_CFG: ~~~~~~~ 25
        - FNCT-TUI-3REAL_SRC_CFG: ~~~~~~~ 12
            - FNCT-HW-3REAL_SRC_CFG: ~~~~~~~ 05
                - FNCT-HW-2WRPR-SDK_SRC_CFG: ~~~~~~~ 01
                    - FNCT-CORE-3REAL_SRC_CFG: ~~~~~~~ 06
                        - FNCT-CORE-2WRPR_SRC_CFG: ~~~~~~~ 03
                    - FNCT-HW-1TRDP-SDK-MAC_SRC_CFG: ~~~~~~~ 03
                        - FNCT-HW-0ABST_SRC_CFG: ~~~~~~~ 00
                            - FNCT-BASE-0ABST_SRC_CFG: ~~~~~~~ 00
            - FNCT-TUI-2WRPR-UI_SRC_CFG: ~~~~~~~ 09
                - FNCT-TUI-0ABST_SRC_CFG: ~~~~~~~ 08
                    - FNCT-HW-0ABST_SRC_CFG: ~~~~~~~ 00
                        - FNCT-BASE-0ABST_SRC_CFG: ~~~~~~~ 00


---

Last login: Mon Dec 29 07:45:08 on ttys003
Restored session: Sun Dec 28 20:37:40 CET 2025

- dtyCntnr1StreamListX
- dtyCntnr1StreamUnitShmProx

---

Last login: Sun Dec 28 07:54:27 on ttys000
Restored session: Sat Dec 27 20:33:01 CET 2025

TUI_DEF_H___CPLT_UNIT_3_SHM_PROX_X
TUI_DEF_CPP_CPLT_UNIT_3_SHM_PROX_X

- class tuiCpltUnit3ShmProxX_t :    
    - public tuiFnctRealUnit2Cntnr_t
        - class tuiFnctRealUnit2Cntnr_t :    public tuiFnctAbstUnit1Cntr_t
            - class tuiFnctAbstUnit1Cntr_t :    public tuiFnctAbstUnit0_t 
                - class tuiFnctAbstUnit0_t :    public dtyIntfcAbstractUnitFunctional_t
                    - class dtyIntfcAbstractUnitFunctional_t :     public dtyIntfcUiEvent_t
                    -                                             ,public dtyIntfcUiStateFnct_t
                    -                                             ,public dtyIntfcUiDsplyFnct_t
                    -                                             ,public dtyIntfcUiCntnrFnct_t
                    -                                             ,public dtyIntfcProcessFnct_t
    - public tuiGrphRealUnit5Base_t
        - class tuiGrphRealUnit5Base_t : public tuiGrphAbstUnit4InOut_t  {
            - class  tuiGrphAbstUnit4InOut_t : public tuiGrphAbstUnit3Event_t {
                - class tuiGrphAbstUnit3Event_t :     public tuiGrphAbstUnit2Coord_t
                    - class tuiGrphAbstUnit2Coord_t:  public tuiGrphAbstUnit1State_t {
                        - class tuiGrphAbstUnit1State_t: public tuiGrphAbstUnit0_t {
                            - class tuiGrphAbstUnit0_t :   public dtyIntfcAbstractUnitGraphic_t
                                - class dtyIntfcAbstractUnitGraphic_t :    public dtyIntfcUiCoord_t
                                -                                         ,public dtyIntfcUiInOut_t
                                -                                         ,public dtyIntfcUiCntnrGrph_t
                                -                                         ,public dtyIntfcUiStateGrph_t
                                -                                         ,public dtyIntfcUiDsplyGrph_t
                                -                                         ,public dtyIntfcProcessGrph_t
    - <parameter>
        - tuiCplt_dtyCntnr2StreamListShmProxX_t
            - dtyCntnr1StreamListX_t
            - <parameter>
                - dtyCntnr1StreamUnitShmProx_t
                    - dtyCntnr0StreamUnitIntfc_t
                - tuiCpltUnit1MmyInt_t                        
                    - public tuiFnctRealUnit1MmyInt_t
                        - tuiFnctAbstUnit0_t
                            - dtyIntfcAbstractUnitFunctional_t
                                - public dtyIntfcUiEvent_t
                                - ,public dtyIntfcUiStateFnct_t
                                - ,public dtyIntfcUiDsplyFnct_t
                                - ,public dtyIntfcUiCntnrFnct_t
                                - ,public dtyIntfcProcessFnct_t
                    - public tuiGrphRealUnit5Base_t


---

Last login: Tue Dec 23 07:51:00 on ttys002
Restored session: Mon Dec 22 20:34:33 CET 2025


- gestione [pphUsart]
    - non dovrebbe fare nessun riferimento a moduli del [sdk] quindi
        - è il modulo [wrpr::hwUsart] che dovrebbe ereditare  [mcuUsart] e non [pphUsart]
        

---

Last login: Mon Dec 22 08:05:55 on ttys002
Restored session: Sun Dec 21 20:00:29 CET 2025

/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/fnct/core/layer/mpfw_fw2-fnct-core-3real/src/kr/krTimer/v_04/krTimerManager.h


---

Last login: Sun Dec 21 07:59:05 on ttys002

- fasi di lavoro nell'implementazione del modulo [uyProtocol] con i moduli [real::pphUsart]/[wrpr::hwUsart]/[sdk::mcuUsart]/[sdk::shmUsart]
    - [real::pphUsart]
    - [wrpr::hwUsart]
    - [sdk]
        - [sdk::mcuUsart]
        - [sdk::shmUsart]
    - [real::uyProtocol]
        - rivedere il nome dei field della struttura [uyProtocol::callback_sdk_functions_t]
            - farli uguali a quelli delle funzioni
        - sarebbe inoltre da definire la struttura in un modulo [0abst] insieme all'altra struttura [callback_protocol_functions_t]
            - questo però significa spostare il modulo [uyProtocol] in un altro modulo, cosa, questa, abbastanza raccomandabile
                - il modulo potrebbe essere [fnct-core-0abst]
                    - considerare il fatto che al momento il modulo [uyProtocol] non ha nessuna dipendenza ma probabilmente con la nuova gestione si avrà bisogno di servizi come [svStateMachine] e [krThread]
                        - quindi un modulo radice più adato dovrebbe esseree ad un livello più alto del [fnct_core]
                            - potrebbe essere anche il modulo [fnct-hw-3real]
        - 




- gestione dei thread
    - gira nell'applicazione [app20240619_new_bis] e nell'applicazione [tst_20230810]
    - non gira ancora nell'applicazione [app20250424]

- procedura per ricevere un buffer dal canale di comunicazione
    - 0. Configurazione
            - la configurazione consiste nello stabilire 
                - quale [protocollo]
                - e quale [procedura_hardware]
            - usare
            - questa fase si concretizza con  l'impostare due strutture dati
                - [callback_protocol_functions_t]
                    - contiene le funzioni riguardanti la gestione del protocollo
                    - viene usata dal modulo [sdk] che implementa la procedura hardware della comunicazione
                - [uyProtocol::callback_sdk_functions_t]
                    - contiene le funzioni riguardanti la procedura hardware
                    - viene usata dal modulo [uyProtocol]
                - l'implementazione di queste due strutture dati dipende dall'applicazione o da un gruppo di applicazioni e quindi verrà fatta in un modulo [appl] o in un modulo [fnct]
    - 1. Avviare la procedura di ricezione
        - viene fatto con la funzione [pph::rxStart]
            - questa funzione esegue le seguenti macro istruzioni
                - impostare lo stato del canale di ricezione in [SDK_USART_RX_STATUS__RUNNING]
                    - questo viene fatto con la funzione [uyProtocol::receive_non_blocking]
                    - questa funzione viene chiamata dallo user nel loop [appl_loop]
                        - questa funzione imposta il puntatore al buffer del modulo uyProtcol con il puntatore al buffer dell'applicazione
                        - [appl::ptrBuffer] ==>> [uyProtocol::ptrBuffer]
                - impostare l'hardware virtuale/reale
                    - caso reale
                        - attivazione degli interrupt di ricezione
                    - caso virtuale
                        - non c'è bisogno di fare niente
                            - infatti il loop che simula la routine di interrupt è sempre attivo
    - 2. interrupt loop & funzioni di protocollo
        - controllo del canale di trasmissione
            - caso reale
                - è attivo l'interrupt 
            - caso virtuale
                - c'è la funzione di loop che simula la routine di interrupt
        - le funzioni di interrupt sono quelle che chiamano le funzioni di protocollo del modulo [uyProtocol]
        - le funzioni di interrupt sono implementate nei moduli [sdk] e attraverso funzioni di callback anche in moduli di livello superiore dipendenti dalla piattaforma e dall'applicazione o dal gruppo di applicazioni
            - un esempio sono le funzioni di init
                - [init]
                - [txPinEnable]/[rxPinEnable]

---

Last login: Sat Dec 20 08:04:07 on ttys002


- dal [registro/mcu] al [buffer/user] e viceversa
    - quindi ci sarà uno stato per il registro ed uno stato per il buffer
- gestione buffer e registro
    - il modulo [uyProtocol] gestisce il [buffer]
    - il modulo [pphUsart]/[hwUsart]/[mcuUsart] gestiscono il [registro]
    - chi esegue il trasferimento tra [buffer] e [registro]?
        - [uyProtocol::tx_buffer_management(.)]
        - [uyProtocol::rx_buffer_management(.)]
    - gestione [stato_registro]
    - gestione [stato_buffer]
- analisi delle fasi nel processo di trasmissione e ricezione
    - 1. la sorgente scrive un byte nella [shared_memory]
    - 2. lettura del byte
        - 2. 1. la destinazione si predispone in uno stato per riempire il [buffer] di ricezione
            - in questo caso ci dovrebbe essere lo stato di [waiting_rx_data]
                - in questo stato è attivo l'interrupt di ricezione
                - si passerà allo stato di [rx_running] quando verrà ricevuto un byte in accordo con il protocollo
        - 2. 2. ad ogni ciclo viene eseguita la funzione
                - [sdk::mcuUsart_t::check_read_write]
                    - quando lo stato della comunicazione è [waiting_rx_data] o [rx_running] e l'interrupt di ricezione si è attivato
                        - la condizione che simula l'attivazione dell'interrupt di ricezione è
                            - [shmMcuUsart_t::WriterPidGet()] -> true o comunque di verso da zero
                            - [shmMcuUsart_t::pidMatches()] -> false
                    - viene eseguita la funzione
                        - [g_callback_protocol_functions.rx_buffer_management()]
                            - se lo stato è in [waiting_rx_data] si passa allo stato [rx_running]
                            - [g_callback_sdk_functions.reg_read()]
                                - [shmMcuUsart_t::getData()]
                                - trasferimento [registro] -> [buffer]
- analisi degli stati del canale di comunicazione
    - [SDK_USART_TX_STATUS__FREE]
    - [SDK_USART_RX_STATUS__FREE]
        - [user] può modificare
        - [loop_interrupt] può solo leggere
        - ==>> [SDK_USART_TX_STATUS__RUNNING]/[SDK_USART_RX_STATUS__RUNNING]
    - [SDK_USART_TX_STATUS__RUNNING]
        - [user] può solo leggere
        - [loop_interrupt] può modificare
        - ==>> [SDK_USART_TX_STATUS__WAITING_LAST_BYTE_SEND]
    - [SDK_USART_TX_STATUS__WAITING_LAST_BYTE_SEND] <new>
        - [user] può solo leggere
        - [loop_interrupt] può modificare
        - ==>> [SDK_USART_TX_STATUS__COMPLETED]
    - [SDK_USART_TX_STATUS__COMPLETED]
        - [user] può modificare
        - [loop_interrupt] può solo leggere
        - ==>> [SDK_USART_TX_STATUS__FREE]/[SDK_USART_RX_STATUS__FREE]
    - [SDK_USART_RX_STATUS__RUNNING]
        - [user] può solo leggere
        - [loop_interrupt] può modificare
        - ==>> [SDK_USART_RX_STATUS__COMPLETED]
    - [SDK_USART_RX_STATUS__COMPLETED]
        - [user] può modificare
        - [loop_interrupt] può solo leggere
        - ==>> [SDK_USART_TX_STATUS__FREE]/[SDK_USART_RX_STATUS__FREE]




---

Last login: Fri Dec 19 08:12:16 on ttys002

- analisi delle parti di un applicazione
    - su piattaforma "reale"
    - su piattaforma "virtuale"
        - parte [funzionale]
        - parte [simulazione]
            - ha le sue istanze dei vari elementi che compongono la [motherBoard]
                - le istanze saranno complementari a quelle della parte funzionale
                    - ad esempio se un pin nella parte funzionale è configurato come ingresso nella parte di dimulazione sarà configurato in uscita
    - da capire
        - gestione dei thread
            - parte [funzionale] e parte [simulazione] su due thread differenti?
                - forse non ha senso fare questa distinzione dal momento che entrambe le parti si possono sviluppare su più thread differenti
                - in base ai moduli/elementi utilizzati
            - per la gestione dei thread conviene pensare sugli elementi costitutivi delle due parti
            - quindi
                - moduli appl
                - moduli hw/pph
                - moduli interfaccia (tui)
                - moduli core
                    - [timer]
                    - [stateMachine]
            - in particolare
                - nel caso della [usart] al momento nel loop dei moduli [appl] vengomno utiliuzzate delle funzioni bloccanti 
                - che dipendono da parametri della [usart] 
                - se il codice di questi due moduli viene messo nello stesso thread il flusso di programma si bloccherà
                - quindi necessariamente i loop
                    - dei [pph]
                    - e quello del [tui]
                - dovrebbero risiedere in due thread differenti

- codice di controllo nella gestione di processi paralleli/multi-thread
    - da escludere come codice di debug
        - inoltre sarebbe interessante capire se possibile avere un resoconto di tutti gli "assert" eseguiti con successo e quelli non eseguiti

- gestione [uyProtocol]/[new_pph/hwUsartIntfc]
    - le funzioni
        - [txBuff_check]
        - [rxBuff_check]
    - verranno sostituite dalle funzioni dell'[uyProtocol]


- versione senza [uyProtocol]
    - pphUsart_t::txBuff_send()
        - ==>> user_Txbuffer -> pph::g_txBuff
        - pphUsart_t::txBuff_check()
            - ==>> pph::g_txBuff[] -> mcuUsart::g_tx_data
    - si dovrebbe sostituire con la funzione [uyProtocol::send_non_blocking]
- versione con [uyProtocol]
    - 


............
uyProtocol::callback_sdk_functions_t uyProtocol::g_callback_sdk_functions = {

    .reg_write  = hwUsart::tx_fifo_write,
    .reg_read   = hwUsart::rx_fifo_read,

};

void sdk_usart::reg_write(void* p_ptrData, char c)	{

	sdk_process::tx_fifo_write(c);
    shmMcuUsart_t::setData(g_tx_data); 
	addch(c);
}

void hwUsart::tx_fifo_write(void* p_ptrData, char c)	{
    UNUSED(p_ptrData);
    shmMcuUsart_t::setData(c); 
}

uint8_t hwUsart::rx_fifo_read(void* p_ptrData)	{
    UNUSED(p_ptrData);
    return shmMcuUsart_t::getData();

}


void pphUsart_t::vhwLoop (void) {
    txBuff_check();

    // virtual/real channel management
    //    1) it writes the data if "tx_fifo_full" is true
    //    or
    //    2) it reads the channel and saves sent data in "rx_data" and set "rx_data_new" to true
    check_read_write();

    rxBuff_check();

}
............


---

Last login: Thu Dec 18 07:55:14 on ttys002
Restored session: Wed Dec 17 20:13:55 CET 2025

- vediamo di fare un analisi partendo dall'alto
    - parte reale (deve girare in tutte le piattaforme)
        - app_loop
            - devo usare solo le funzioni del modulo [uyProtocol]
            - quindi il modulo [pph] sostituisce il modulo [rsSerial]
    - parte simulata
        - virtual_loop
            - 
    - interfaccia utente
        - condizione
            - per il momento si assume che l'applicazione reale non abbia intrefaccia
            - quindi l'interfaccia per il momento rigurada solo il service e viene implementata solo nella piattaforma [mac]
        - considerazioni
            - la parte di [service] 
                - deve essere vista come un processo "reale" che gira in parallelo con la parte [funzionale] e può essere implementata anche nelle piattaforme reali
                - deve essere indipenedente dalla parte [funzionale]
        - deve acquisire e/o inviare dati dal canale di comunicazione sia esso virtuale che reale 
    - le parti dell'applicazione sono le seguenti
        - [reale]
            - [funzionale]
            - [service]
        - [simulazione]
            - hardware
                - pin
                - usart
                - lcd
                - etc.
            - parte di codice presente solo nelle piattafforme virtuali come [linux/mac/android/windows]
        - [serial_com_service]
            - presente solo nell'applicazione su piattaforme virtuali, quindi piattaforma [mac]
            - è l'equivalente di un applicazione [terminal] come ad esempio [minicom] (per linux/mac) o [hyperTerminal] per windows
                - ma con l'ulteriore funzione di interfacciarsi con le parti di [simulazione]
                    - ad esempio
                        - simulare la chiusura/apertura degli ingressi digitali
                        - simulare gli ingressi analogici come ad esempio 
                            - i livelli di tensione sui pin oppure 
                            - OPPURE la misura di temperatura
            - in base a queste funzionalità si dovrebbero avere due finestre/applicazioni
                - finestra [serialCom]
                    - applicazione pr la comunicazione seriale da usarsi in sostituzione di applicazioni come [mninicom]/[hyperTerminal] etc.
                - finestra [motherBoard]
                    - ci saranno tutti gli elementi che compongono la mother board
                        - led
                        - button
                        - din/dout
                        - ain/aout
                        - adc
                        - sensore di temperatura
                        - usart

- appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/tui/app_tuiMainWindow
- appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw/pph

- integrazione del modulo [uyProtocol] con il modulo [pphUsart]
    - il modulo [pphUsart] sembra sia costituito da due gruppi di funzioni
        - il gruppo di funzioni riguardanti la simulazione 
            - queste funzioni sono utilizzate solo dal codice che si occupa della simulazione quindi dal codice su piattaforma [mac]
        - il gruppo di funzioni rigurdanti la parte reale, il codice "reale" quello che deve girare in tutte le piattaforme
            - queste funzioni sono utilizzate in tutte le piattaforme e sono quelle chiamate nel modulo [appl] valido per utte le piattaforme
    - il file [mcuUsartTypeDefs.h]
        - dovrebbe essere un file comune a tutte le piattaforme, un interfaccia per chi vuole implementare la gestioone secondo il modulo [uyProtocol]
        - sarebbe da metterlo nel modulo [hw_0abst]
..........
- sdk
    - mac
        class mcuUsart_t :   public mcuBase_t
                            ,public dtyCmmnHwGnrlAbst0Intfc_t
                            ,public shmMcuUsart_t
        {
        public:

            mcuUsart_t  (                   uint8_t p_mcuId, k_mcuUsart_t p_ch);
            mcuUsart_t  (uint8_t p_pid2,    uint8_t p_mcuId, k_mcuUsart_t p_ch);


            void vhwInit (void)         override;
            //void vhwLoop (void)         override;

            bool tx_fifo_full           (void);
            bool rx_fifo_full           (void);
            void tx_fifo_empty_out      (void);
            void tx_fifo_write          (char c);
            uint16_t rx_fifo_read       (void);
            bool check_read_write       (void);     // simula l'interrupt delle piattaforme reali 
            uint16_t read               (void);
            void chEnable               (void);

            static callback_protocol_functions_t g_callback_protocol_functions;
        }
    - nxp
    - stm32f7569_disco

'''''''''''''''''''''''''''''''''''''''''
- pph
    - codice dipendente dalla piattaforma in particolare valido solo per quelle di simulazioone
        void pphUsart_t::vhwLoop (void) {
            txBuff_check();

            // virtual/real channel management
            //    1) it writes the data if "tx_fifo_full" is true
            //    or
            //    2) it reads the channel and saves sent data in "rx_data" and set "rx_data_new" to true
            check_read_write();

            rxBuff_check();

        }

    uint8_t* pphUsart_t::rxBuff_getPtr  (void)      {
        return g_rxBuff;
    }


    void pphUsart_t::txBuff_check       (void)      {
        if(g_txBuffReady)   {
            if(g_txBuffCounter < g_txBuffSize)  {
                tx_fifo_write(g_txBuff[g_txBuffCounter]);
                g_txBuffCounter++;
            } else {
                g_txBuffReady   = false;
                g_txBuffCounter = 0;
            }
        }
    }

    void pphUsart_t::rxBuff_check       (void)      {
        // 
        if(rx_fifo_full())   {
            g_rxBuff[g_rxBuffCounter] = rx_fifo_read();
            g_rxBuffCounter++;
            if(rxBuff_protocolCheck()) g_rxBuffReady = true;
        } else {
            if(g_rxBuffCounter) {
                g_rxBuffReady = true;
            }
        }
    }

    bool pphUsart_t::txBuff_send (uint8_t* p_pTxBuff, uint8_t p_txBuffSize) {
        bool l_result = false;
        if(!g_txBuffReady)  {
            // 1. set buffer size
            g_txBuffSize = p_txBuffSize;

            // 2. copy p_pTxBuff ==>> g_txBuff
            for(uint8_t i=0;i<p_txBuffSize;i++) g_txBuff[i] = p_pTxBuff[i];

            // 3. update status tx buffer
            g_txBuffReady = true;

            l_result = true;
        }

        return l_result; 
    }


    uint8_t pphUsart_t::rxBuff_receive (void) {
        uint8_t l_result = 0;
        if(g_rxBuffReady)  {

            l_result = g_rxBuffCounter;
            g_rxBuffCounter = 0;
            g_rxBuffReady = false;
        }

        return l_result; 
    }

    bool pphUsart_t::rxBuff_protocolCheck   (void)      {
        return false;
    }

..........


---

Last login: Wed Dec 17 07:57:40 on ttys002
Restored session: Tue Dec 16 20:07:20 CET 2025

- gestione multi-thread
    - meglio andare per gradi
        - il prossimo passo è quello di aggiornare l'applicazione "mpfw_fw2-appl-app20250424-4appl" per fare entrare nelle dipendenze i moduli [fnct-core]
            - attraverso l'uso del sotto-modulo [uyProtocol]


- lo scopo della "nuova" applicaziopne è
    - lasciare inalterata l'interfaccia utente quindi il modulo [ap_krThread02]
        - forse non  conviene dal momento che le funzopni di gestione della usart viortuale sono "fuse" con le funzioni di visualizazioni
            - quindi se volglio sostituire le funzioni della usart vitruale con la versione "nuova" 
            - devo necessariamente usare un'altra interfaccia 
                - da qui diventa inutile implementare le funzioni
                    - [rsSerial::CheckService()]
                    - [rsSerial::RxStop()]
    - cambiare la gestione della comuicazione usando i nuovi "moduli"
    - questo significa che le funzioni
        - [rsSerial::CheckService()]
        - [rsSerial::RxStop()]
    - devono essere implementate con il nuovo sistema
        - quindi si deve capire come sostituire le funzioni
            - [sdk_usart::rx_stop()]
                - ha lo scopo di 
            - [sdk_usart::check_loop_end()]
                - necessario per uscire dal thread implementao nel mdoulo [ap_krThread02] nella piattaforma virtuale 
                - fornisce l'informazionne 
    

- gestione dell'impostazione dei pin che gestiscono l'abilityazione della tx/rx nella comunicazione [rs485]
    - questi pin riguardano la configurazione dell'hardware e quindi l'implementazione delle fuzioni [txEnable]/[rxEnable] dpovrebbe essere messa
    - im un modfulo che sia un estensione dell'sdk e che dipenda da un gfruppo di applicazioni che usano la stessa confiugurazione hardware 
        - stabilire il tipo
            - appl
                - lo si potrebbe inserire in questa classe di moduli
                    - contro
                        - ogni applicazione che usa la stessa configurazione a rigor di logic dovra duplicare il modulo 1trdp
            - fnct
                - creare un modulo che possa essere usato da più applicazioni che usano la stssa confiugurazione hardware
                - credo che questa sia la scelta più opportuna
                - esempio
                    - [fnct-app_group-appl_20251216-standard-1trdp-sdk-mac]
                        - [fnct/app_group/appl_20251216/layer/fnct-app_group-appl_20251216-standard-1trdp-sdk-mac]
            - trdp
                - anche questa classe di moduli può essere interessante usare
                - avrei il v antaggio di avere l'elenco delle varie configurazioni hardware per ciuscuna piattaforma
                - esempio
                    - [trdp-sdk-mac-1trdp-config_hw-appl_20251216]

        - stabilire il livello
            - 1trdp
                - pro/contro
                    - per ogni configurazione avro un modulo diverso
                        - questo potrebbe essere una cosa positiva per un vberso e negativa per un altro
                            - la cosa positiva è che è modulare
                            - la cposa negativa è che devo creare un nuovo modulo per ogniconfigurazione diversa dell'ìhw
                                - la qual cosa tutto somma mi sembra anche giusta
            - oppure
            - 2wrpr
                - contro
                    - per una stessa piattaforma/sdk posso avere più configurazioni hardware
                    - per esemmpio per la scheda stm32f769_disco posso avere più di una configurazione hardware
                    - tuttavia per ciascuna sdk posso avere umna sola configurszione a meno di usare le versioni dei file sorgente che però come abbiamo detto ieri forse è meglio evitare
                - questo livello sarebbe meglio evitae di usarlo

---

Last login: Tue Dec 16 08:03:01 on ttys002
Restored session: Mon Dec 15 20:09:43 CET 2025

- gestione dei moduli
    - i moduli [res] vengono sostituiti dai moduli [hw] in particolare
        - i moduli
            - [mpfw_fw2-fnct-res-1trdp-sdk-nxp]
            - [mpfw_fw2-fnct-res-1trdp-sdk-stm-stm32f769_disco]
        - verranno sostituiti dai moduli
            - [mpfw_fw2-fnct-hw-1trdp-sdk-nxp]
            - [mpfw_fw2-fnct-hw-1trdp-sdk-stm-stm32f769_disco]
        - oppure
            - [mpfw_fw2-trdp-sdk-mac-1trdp-usart]
            - [mpfw_fw2-trdp-sdk-nxp-1trdp-usart]
            - [mpfw_fw2-trdp-sdk-stm-stm32f769_disco-1trdp-usart]
    - il modulo [hw-0abst]
        - 
    - i moduli [hw-2wrpr-sdk]
        - 
- gestione delle implementazione in funzione dell'applicazione o più in generale dei livelli superiori di dipendenze
    - esempio, gestione della comunicazione [rs485]
        - l'implementazione delle funzioni [txEnable]/[rxEnable] dove si gestisce a livello hardware i pin di abilitazione del canale di trasmissione/ricezione per la comunicazione [rs485/half-duplex]
    - ci sono più possibilità
        - agire sulle versioni dei file sorgenti
            - pro
                - si gestisce tutto all'interno di un o stesso modulo
            - contro
                - se si adotta questo metodo per n-situazioni per stabilire il nome della configurazione a livello più alto si complica troppo
                - non è del tutto modulare (e forse questo aspetto è quello più negativo)
                    - per ogni applicazione dovrei modificare il modulo di basso livello facendo una integrazione
                    - quindi indirettamente il modulo contiene informazioni di moduli di livello superiore il che (la qual cosa) è molto poco raccomandabile
            - aggiornamenti richiesti
                - stabilire una codifica del nome delle versioni
        - implementare le funzioni fuori dal file sorgente ".cpp" e in un altro modulo
            - in particolare
                - nel caso specifico della [rs485] riportarlo del modulo app di configurazione dell'hardware
            - pro
                - è un sistema modulare
                    - non si deve modificare nessun modulo di più basso livello
            - contro
                - non mi piace distrbuire ovunque l'implementazione delle funzioni di una classe
                    - mi piace tenere tutto nel file ".cpp" della classe
                    - però per la definzione dei moduli [pph] indirettamente, per mezzo delle [macro_define], si usa un sitema di questo tipo se non sbaglio
                    - forse questo aspetto negativo potrebbe essere considerato non rilevante
                    - come chiamare il modulo che ospiterà le implementazione?
                        - nome del modulo radice
                            - appl/app20250424/layer/mpfw_fw2-appl-app20250424-4appl/trdp/sdk/mac/src/instances/hw
                        - nome del file ".cpp"
                            - app_hwUsart.cpp
        - tenere tutto all'intereno di uno stesso modulo a basso livello
    - sempre nell'ambito della comnunicazione seriale considerare il caso di come e dove gestire la connessione tra i mmoduli [uyProtocol] e i moduli [sdk-usart], ad esempio [mpfw_fw2-fnct-hw-1trdp-sdk-nxp]
        - l'implementazione degli array
            - [g_callback_protocol_functions]
            - [g_callback_sdk_functions]
        - anche questa può essere fatta nel modulo [appl] oppure  anche in un modulo di livello più basso  per evitare di impostare sempre gli stessi elementi per un gruppo di n-applicazioni
            - un esempio di modulo di più basso livello potrebbe essere 
                - [fnct-<company_name>-app_group_<application_group_name>-2wrpr-sdk]
                    - fnct/xxx_company/app_group_yyy/fnct-xxx_company-app_group_yyy-2wrpr-sdk
                - [fnct-<company_name>-app_group_<application_group_name>-1trdp-sdk-mac]
                - [fnct-app_group-<company_name>-<application_group_name>-1trdp-sdk-mac]
                - [fnct-app_group-<application_name>-<application_group_name>-1trdp-sdk-mac]
                - [fnct-app_group-appl_20251216-standard-1trdp-sdk-mac]
                    - contiene l'implementazione di funzionalità specifiche per un gruppo di applicazioni relative all'sdk
                        - assegnare un nome al gruppo di applicazioni
                            - può essere il nome di un applicazione di riferimento
                            - oppure il nome di una funzionalità generale
                                - ad esempio: [serial_com_standard]
                - [trdp-sdk-mac-1trdp-usart-appl_20251216-standard]
                    - contiene l'implementazione di funzionalità riguardanti l'sdk specifiche per un gruppo di applicazioni
                    - fnct/xxx_company/app_group_yyy/layer/fnct-xxx_company-app_group_yyy-1trdp-sdk/src/serial_com/app_hwUsart/v_xx/app_hwUsart.
                - notare come nel nome del modulo c'è la presenza delle due dipenendenze
                    - [gruppo_delle_applicazioni]
                    - [sdk]
                - credo che il [livello] più opportuno da assegnare al modulo è quello del [1trdp] dal momento che per implementare i due array sono necessari solo elementi specifici per la piattaforma/sdk e non c'è nessun elemento in comune con altri sdk

- gestione del nome dei moduli
    - è importante assegnare un oppotuno nome ai moduli affinche le relazioni di dipendenza siano il più chiare possbili
        - un esempio
            - comunicazione seriale
                - il fatto di eseguire l'implementazione degli array
                    - [g_callback_protocol_functions]
                    - [g_callback_sdk_functions]
                - in un modulo diverso da [mpfw_fw2-fnct-hw-1trdp-sdk-nxp]
                - risiede nel fatto che 
                    - questa implementazione riguarda l'applicazione o un gruppo di applicazioni
                        - infatti applicazioni diverse possono usare un protocollo diverso 
                    - mentre il modulo in questione [mpfw_fw2-fnct-hw-1trdp-sdk-nxp] è un modulo generale che va bene per tutte le applicazioni
                    - inoltre inserendo l'implementazione degli array nel modulo appena citato si inserirebbero delle informazioni riguardanti moduli di livello superiore che infrangerebbero la regola delle dipendenze
                        - i modulòi di livello inferirore NON DEVONO sapere ninete di quello che succede sopra di loro


---

Last login: Tue Dec  9 06:37:49 on ttys004

- correggere i warning nei progetti degli ambienti di sviluppo ide di nxp e stm
    - risultati dell'analisi
        - sembra che il problema sia sulla locazione dei sorgenti
            - in particolare sembra non gli piaccia la variabile che definisce le versioni dei sorgenti
        - quindi non dipende da dove si defniscono le variabili delle versioni dei sorgenti
    - la definizione dedlle versiuoini dei sorgenti può essere messa in due file differenti uno di workspace l'altro specifico del progetto
         - main/mpfw_code_main_tst_20230810main/wsp/cube/project/stm32f769_disco/tst_20230810main/.settings/org.eclipse.cdt.core.prefs
            - doxygen/doxygen_new_line_after_brief=true
            - doxygen/doxygen_use_brief_tag=false
            - doxygen/doxygen_use_javadoc_tags=true
            - doxygen/doxygen_use_pre_tag=false
            - doxygen/doxygen_use_structural_commands=false
            - eclipse.preferences.version=1
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/CODE_DIR/delimiter=\:
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/CODE_DIR/operation=append
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/CODE_DIR/value=${ProjDirPath}/../../../../../../..
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/TEST_TEST/delimiter=\:
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/TEST_TEST/operation=append
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/TEST_TEST/value=2
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/append=true
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.debug.756143850/appendContributed=true
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.release.1794332031/CODE_DIR/delimiter=\:
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.release.1794332031/CODE_DIR/operation=append
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.release.1794332031/CODE_DIR/value=${ProjDirPath}/../../../../../../..
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.release.1794332031/append=true
            - environment/project/com.st.stm32cube.ide.mcu.gnu.managedbuild.config.exe.release.1794332031/appendContributed=true
         - main/mpfw_code_main_tst_20230810main/wsp/cube/workspace/stm32f769_disco/.metadata/.plugins/org.eclipse.core.runtime/.settings/org.eclipse.cdt.core.prefs
            - eclipse.preferences.version=1
            - environment/workspace/FW2_WRAPPER_CORE_CONF_RPATH/delimiter=\:
            - environment/workspace/FW2_WRAPPER_CORE_CONF_RPATH/operation=append
            - environment/workspace/FW2_WRAPPER_CORE_CONF_RPATH/value=common/cg/libs/fw2_wrapper_core
            - environment/workspace/MAIN_NAME/delimiter=\:
            - environment/workspace/MAIN_NAME/operation=append
            - environment/workspace/MAIN_NAME/value=tst_20230810main
            - environment/workspace/PLATFORM_NAME/delimiter=\:
            - environment/workspace/PLATFORM_NAME/operation=append
            - environment/workspace/PLATFORM_NAME/value=stm32f769_disco
            - environment/workspace/SDK_PLATFORM_CONF_RPATH/delimiter=\:
            - environment/workspace/SDK_PLATFORM_CONF_RPATH/operation=append
            - environment/workspace/SDK_PLATFORM_CONF_RPATH/value=stm32f769_disco/Inc/sdk_conf
            - environment/workspace/SDK_PLATFORM_FREERTOS_CONF_RPATH/delimiter=\:
            - environment/workspace/SDK_PLATFORM_FREERTOS_CONF_RPATH/operation=append
            - environment/workspace/SDK_PLATFORM_FREERTOS_CONF_RPATH/value=stm32f769_disco/Inc/freertos
            - environment/workspace/SDK_PLATFORM_INTERRUPT_CONF_RPATH/delimiter=\:
            - environment/workspace/SDK_PLATFORM_INTERRUPT_CONF_RPATH/operation=append
            - environment/workspace/SDK_PLATFORM_INTERRUPT_CONF_RPATH/value=stm32f769_disco/Inc/interrupt
            - environment/workspace/SDK_PLATFORM_SDK_CONF_RPATH/delimiter=\:
            - environment/workspace/SDK_PLATFORM_SDK_CONF_RPATH/operation=append
            - environment/workspace/SDK_PLATFORM_SDK_CONF_RPATH/value=stm32f769_disco/Inc/sdk_conf
            - environment/workspace/SDK_PLATFORM_UART_CONF_RPATH/delimiter=\:
            - environment/workspace/SDK_PLATFORM_UART_CONF_RPATH/operation=append
            - environment/workspace/SDK_PLATFORM_UART_CONF_RPATH/value=stm32f769_disco/Inc/uart
            - environment/workspace/append=true
            - environment/workspace/appendContributed=true
            - environment/workspace/fw2_core_core_DG_FORMAT_DIGIT_VER/delimiter=\:
            - environment/workspace/fw2_core_core_DG_FORMAT_DIGIT_VER/operation=append
            - environment/workspace/fw2_core_core_DG_FORMAT_DIGIT_VER/value=01
            - environment/workspace/fw2_core_core_DG_INTERFACE_VER/delimiter=\:
            - environment/workspace/fw2_core_core_DG_INTERFACE_VER/operation=append
            - environment/workspace/fw2_core_core_DG_INTERFACE_VER/value=01
            - environment/workspace/fw2_core_core_DT_DEF_VER/delimiter=\:
            - environment/workspace/fw2_core_core_DT_DEF_VER/operation=append
            - environment/workspace/fw2_core_core_DT_DEF_VER/value=00
            - environment/workspace/fw2_core_core_KR_EVENT_VER/delimiter=\:
            - environment/workspace/fw2_core_core_KR_EVENT_VER/operation=append
            - environment/workspace/fw2_core_core_KR_EVENT_VER/value=02
            - environment/workspace/fw2_core_core_KR_INIT_VER/delimiter=\:
            - environment/workspace/fw2_core_core_KR_INIT_VER/operation=append
            - environment/workspace/fw2_core_core_KR_INIT_VER/value=03
            - environment/workspace/fw2_core_core_KR_TIMER_VER/delimiter=\:
            - environment/workspace/fw2_core_core_KR_TIMER_VER/operation=append
            - environment/workspace/fw2_core_core_KR_TIMER_VER/value=03
            - environment/workspace/fw2_core_core_SV_STATE_MACHINE_VER/delimiter=\:
            - environment/workspace/fw2_core_core_SV_STATE_MACHINE_VER/operation=append
            - environment/workspace/fw2_core_core_SV_STATE_MACHINE_VER/value=03
            - environment/workspace/fw2_core_core_SV_STATE_VER/delimiter=\:
            - environment/workspace/fw2_core_core_SV_STATE_VER/operation=append
            - environment/workspace/fw2_core_core_SV_STATE_VER/value=02
            - environment/workspace/fw2_core_core_SV_SYNC_VER/delimiter=\:
            - environment/workspace/fw2_core_core_SV_SYNC_VER/operation=append
            - environment/workspace/fw2_core_core_SV_SYNC_VER/value=02
            - environment/workspace/fw2_core_core_TB_KR_INIT_VER/delimiter=\:
            - environment/workspace/fw2_core_core_TB_KR_INIT_VER/operation=append
            - environment/workspace/fw2_core_core_TB_KR_INIT_VER/value=02
            - environment/workspace/fw2_core_core_TB_KR_THREAD_VER/delimiter=\:
            - environment/workspace/fw2_core_core_TB_KR_THREAD_VER/operation=append
            - environment/workspace/fw2_core_core_TB_KR_THREAD_VER/value=04
            - environment/workspace/fw2_core_core_TB_KR_TIMER_VER/delimiter=\:
            - environment/workspace/fw2_core_core_TB_KR_TIMER_VER/operation=append
            - environment/workspace/fw2_core_core_TB_KR_TIMER_VER/value=02
            - environment/workspace/fw2_core_core_TB_SV_STATE_MACHINE_VER/delimiter=\:
            - environment/workspace/fw2_core_core_TB_SV_STATE_MACHINE_VER/operation=append
            - environment/workspace/fw2_core_core_TB_SV_STATE_MACHINE_VER/value=02
            - environment/workspace/fw2_core_core_UY_PROTOCOL2_VER/delimiter=\:
            - environment/workspace/fw2_core_core_UY_PROTOCOL2_VER/operation=append
            - environment/workspace/fw2_core_core_UY_PROTOCOL2_VER/value=01
            - environment/workspace/fw2_core_core_UY_PROTOCOL_VER/delimiter=\:
            - environment/workspace/fw2_core_core_UY_PROTOCOL_VER/operation=replace
            - environment/workspace/fw2_core_core_UY_PROTOCOL_VER/value=03
            - environment/workspace/fw2_wrapper_core_KR_THREAD_VER/delimiter=\:
            - environment/workspace/fw2_wrapper_core_KR_THREAD_VER/operation=append
            - environment/workspace/fw2_wrapper_core_KR_THREAD_VER/value=04
            - environment/workspace/fw2_wrapper_core_SY_THREAD_VER/delimiter=\:
            - environment/workspace/fw2_wrapper_core_SY_THREAD_VER/operation=append
            - environment/workspace/fw2_wrapper_core_SY_THREAD_VER/value=01
            - environment/workspace/fw2_wrapper_core_TB_KR_THREAD_VER/delimiter=\:
            - environment/workspace/fw2_wrapper_core_TB_KR_THREAD_VER/operation=append
            - environment/workspace/fw2_wrapper_core_TB_KR_THREAD_VER/value=01
            - environment/workspace/fw2_wrapper_resources_RS_SERIAL_VER/delimiter=\:
            - environment/workspace/fw2_wrapper_resources_RS_SERIAL_VER/operation=append
            - environment/workspace/fw2_wrapper_resources_RS_SERIAL_VER/value=07
            - environment/workspace/fw2_wrapper_resources_TB_KR_INIT_VER/delimiter=\:
            - environment/workspace/fw2_wrapper_resources_TB_KR_INIT_VER/operation=append
            - environment/workspace/fw2_wrapper_resources_TB_KR_INIT_VER/value=02
            - environment/workspace/sdk_stm32f769_disco_SDK_PLATFORM_LIB_VER/delimiter=\:
            - environment/workspace/sdk_stm32f769_disco_SDK_PLATFORM_LIB_VER/operation=append
            - environment/workspace/sdk_stm32f769_disco_SDK_PLATFORM_LIB_VER/value=03
            - environment/workspace/tst_20230810app_AP_KR_THREAD02_VER/delimiter=\:
            - environment/workspace/tst_20230810app_AP_KR_THREAD02_VER/operation=append
            - environment/workspace/tst_20230810app_AP_KR_THREAD02_VER/value=05
            - environment/workspace/tst_20230810app_AP_KR_TIMER01_VER/delimiter=\:
            - environment/workspace/tst_20230810app_AP_KR_TIMER01_VER/operation=append
            - environment/workspace/tst_20230810app_AP_KR_TIMER01_VER/value=01
            - environment/workspace/tst_20230810app_AP_SV_STATE_MACHINE_VER/delimiter=\:
            - environment/workspace/tst_20230810app_AP_SV_STATE_MACHINE_VER/operation=append
            - environment/workspace/tst_20230810app_AP_SV_STATE_MACHINE_VER/value=01
            - environment/workspace/tst_20230810app_AP_SV_STATE_VER/delimiter=\:
            - environment/workspace/tst_20230810app_AP_SV_STATE_VER/operation=append
            - environment/workspace/tst_20230810app_AP_SV_STATE_VER/value=01
            - environment/workspace/tst_20230810app_AP_SV_SYNC_VER/delimiter=\:
            - environment/workspace/tst_20230810app_AP_SV_SYNC_VER/operation=append
            - environment/workspace/tst_20230810app_AP_SV_SYNC_VER/value=04
            - environment/workspace/tst_20230810app_TB_KR_INIT_VER/delimiter=\:
            - environment/workspace/tst_20230810app_TB_KR_INIT_VER/operation=append
            - environment/workspace/tst_20230810app_TB_KR_INIT_VER/value=02
            - environment/workspace/tst_20230810app_TB_KR_THREAD_VER/delimiter=\:
            - environment/workspace/tst_20230810app_TB_KR_THREAD_VER/operation=append
            - environment/workspace/tst_20230810app_TB_KR_THREAD_VER/value=03
            - environment/workspace/tst_20230810app_TB_KR_TIMER_VER/delimiter=\:
            - environment/workspace/tst_20230810app_TB_KR_TIMER_VER/operation=append
            - environment/workspace/tst_20230810app_TB_KR_TIMER_VER/value=02
            - environment/workspace/tst_20230810app_TB_SV_STATE_MACHINE_VER/delimiter=\:
            - environment/workspace/tst_20230810app_TB_SV_STATE_MACHINE_VER/operation=append
            - environment/workspace/tst_20230810app_TB_SV_STATE_MACHINE_VER/value=02
            - environment/workspace/tst_20230810main_TB_KR_INIT_VER/delimiter=\:
            - environment/workspace/tst_20230810main_TB_KR_INIT_VER/operation=append
            - environment/workspace/tst_20230810main_TB_KR_INIT_VER/value=01
            - environment/workspace/tst_20230810main_TB_KR_THREAD_VER/delimiter=\:
            - environment/workspace/tst_20230810main_TB_KR_THREAD_VER/operation=append
            - environment/workspace/tst_20230810main_TB_KR_THREAD_VER/value=01
            - environment/workspace/tst_20230810main_TB_KR_TIMER_VER/delimiter=\:
            - environment/workspace/tst_20230810main_TB_KR_TIMER_VER/operation=append
            - environment/workspace/tst_20230810main_TB_KR_TIMER_VER/value=01
            - environment/workspace/tst_20230810main_TB_SV_STATE_MACHINE_VER/delimiter=\:
            - environment/workspace/tst_20230810main_TB_SV_STATE_MACHINE_VER/operation=append
            - environment/workspace/tst_20230810main_TB_SV_STATE_MACHINE_VER/value=01
            - macros/workspace=<?xml version\="1.0" encoding\="UTF-8" standalone\="no"?>\n<macros/>\n


---

Last login: Thu Dec  4 04:43:00 on ttys008
Restored session: Wed Dec  3 07:23:33 CET 2025


- cose da rivedere 
    - come fare l'upload del firmware ingannando l'IDE sostituendo il file binario
    - ricordarsi di come scriere in automatico i numeri di versione dei sorgenti scivendo direttamente sul file
        - main/mpfw_code_main_tst_20230810main/wsp/cube/workspace/stm32f769_disco/.metadata/.plugins/org.eclipse.core.runtime/.settings/org.eclipse.cdt.core.prefs


- from "dm00104712-stm32cubemx-for-stm32-configuration-and-initialization-c-code-generation-stmicroelectronics.pdf"
    - location: "$HOME/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/docs/stm/stm32f769_disco/stm32F769/doc/GettinStarted"
    - STM32Cube overview
        - The STM32Cube HAL, STM32 abstraction layer embedded software ensuring maximized portability across the STM32 portfolio.
        - Low-layer APIs (LL) offering a fast light-weight expert-oriented layer, which is closer to the hardware than the HAL. LL APIs are available only for a set of peripherals
    - Getting started with STM32CubeMX
        - The time taken to migrate to new platforms and update the C code to new firmware drivers
            - adds unnecessary delays to the project. STM32CubeMX was developed within STM32Cube
            - initiative which purpose is to meet customer key requirements to maximize software reuse
            - and minimize the time to create the target system:
                - Software reuse and application design portability are achieved through STM32Cube
                - firmware solution proposing a common Hardware Abstraction Layer API across STM32
                - portfolio.
                - • Optimized migration time is achieved thanks to STM32CubeMX built-in knowledge of
                - STM32 microcontrollers, peripherals and middleware (LwIP and USB communication
                - protocol stacks, FatFs file system for small embedded systems, FreeRTOS).


---

Last login: Mon Dec  1 06:06:41 on ttys004
Restored session: Sun Nov 30 17:48:06 CET 2025



---

Last login: Sun Nov 30 05:38:28 on ttys004

- gestione della serial com virtuale
    - si potrebbe pensare che il loop dei componenti virtuali [pph] venga eseguito in un solo thread per tutti
        - in questo modo non è necessario gestire in modo più complesso la funzione [shmMcuUsart_t::WriterPidSet]
            - che è l'nica situazione di scrittura concorrente tra due processi che possono girare su thread diversi
            

---

Last login: Sat Nov 29 05:00:20 on ttys004

- gestione multi-thread delle procedure legate al protocollo nella comunicazione seriale
    - da capire se il seguewnte schema si può applicare
        - le procedure eseguite in interrupt modificano lo stato solo se questo ha precisi valori 
        - stessa cosa per le funzioni usate dallo user
        - naturalmente l'insieme di valori dello stato associato alle funzioni di [interrupt] e quello associato alle funzioni [user] devono essere tra loro complementari ovvero la loro intersezione è l'insieme vuoto
    - per poter appliucare lo schema appena sopra esposto la principale difficoltà è quella di controllare che nessuna funzione di [interrupt] venga eseguita dallo [user] e viceversa

- gestione hardware virtuale
    - pensare a come gestire in multi-threading l'hardware virtuale
        - il problema nasce quando due processi scrivono su un pin appartenente alla stssa porta
            - per risolvere questo problema si potrebbe usare una funzione [atomic]
        - l'altro problema 

---

Last login: Fri Nov 28 04:59:47 on ttys004
Restored session: Thu Nov 27 18:28:40 CET 2025


- [serialComunication] management
    - talvolta quando si deve inviare un buffer si ha la necessità di attendere che il buffer sia interamente inviato per poter continuare la procedura, ad esempio nelle situazioni di debug
        - in questo caso si può pensare di eseguire le funzioni bloccanti in un thread a parte
        - quindi si avrebbe la situazione in cui alcune procedure [user] vengono eseguite in thread diversi
            - da capire se sia possibile organizzare il codice per rendere questo uso possibile

- hardwae virtuale & multi-threading
    - per non avere problemi di conflitti e per non modificare il codice attuale si potrebbe pensare di dedicare un thread solo per l'hardware virtuale
    - lo scopo principale del loop associato agli elementi dell'hardware virtuale è
    - simulare l'interazioone con altri dispositivi collegati e 
    - quindi controllare la memoria condivisa usata per la comunicazione Inter-process
        - questo signbifica che le sue procedure sono sono predisposte per la il multithreading
        - però
        - una parte del coidce è stata implementata pensando alla simulazione di na routine di interrupt
            - mi riferisco in particolare alla funzione [mcuUsart_t::check_read_write]
            - il processo di ricezione e trasmissione sfruttano una gestione degli stati [circolare]
            - ovvero 
            - prma di modificare lo stato si verifica prima lo stato stesso
                - in uno stato opera solo la routine di interrupt oppure le funzioni riservate agli user
            - in ogni caso
            - un controllo del codice dovrà essere fatto per poter lavorare senza problemi con il multithreading 
                
- ATTENZIONE!!!!
    - le funzioni
        - uyProtocol::status_set_tx__running
        - uyProtocol::status_set_rx__running
    - è molto probabile non siano implementate correttamente
        - da una prima analisi sembra che non siano utilizzate

---

Last login: Thu Nov 27 05:05:33 on ttys004
Restored session: Wed Nov 26 17:11:37 CET 2025


- obiettivo della nuova gestione della comunicazione seriale
    - fare riferimento ai moduli [pph]
        - in tutte le piattaforme per usare la seriale si dovrà usare il modulo [pphUsart]
            - questo modulo sostituisce il modulo [rsSerial]
    - dubbi
        - gestione dei thread
            - c'è la possibilità di assegnare separatamente ad ogni istanza [pph] su quaòle thread far girare il proprio loop?
            

bool uyProtocol::receive_check	(void)	{
void uyProtocol::buffer_management(char c)	{
void uyProtocol::status_set_

- gestione del processo di ricezione
    - non-blocking
        - void rsSerial::RxStart       (uint8_t* p_CharBufferTx, size_t p_SizeOf)
            - void uyProtocol::receive_non_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length)
                - impoosta lo stato di ricezione in running
                - questo permette alla routine di interrupt di eseguire le operazioni di lettura
                - e quando queste sono finite aggiornare lo stato della ricezione
        - bool rsSerial::RxCheck     (void)
- ci deve essere una sincronizzazione tra 
    - lo stato del buffer di ricezione libero di ricevere nuovi dati e 
    - colui che invia i dati e quindi nella ricezione di nuovi dati
        - processo attivato da un interrupt

- considewrare i due thread
    - procedura di RICEZIONE
        - thread dell'applicazione / [ap_krThread02]
            - void rsSerial::RxStart       (uint8_t* p_CharBufferTx, size_t p_SizeOf)
                - void uyProtocol::receive_non_blocking(uint8_t* p_ptrBuffer, uint8_t p_size_buffer, uint8_t p_length)
                    - impoosta lo stato di ricezione in running
                    - questo permette alla routine di interrupt di eseguire le operazioni di lettura
                    - e quando queste sono finite aggiornare lo stato della ricezione
            - bool rsSerial::RxCheck     (void)
                - controlla lo stato del buffer di rx
                    - se è pieno (avrà lo stato "ricezione terminata") significa che è da leggere
        - thread di service / interrupt / [thread_service_rsSerial] / [vhwMain->vhwManager/appManager]
            - appManager::vhwManager_t::loop
                - pphManager_t::body
                    - loop on <Name> of pph<Name>_t::vhwLoop()
                        - pphUsart
                            - mcuUsart_t::check_read_write
    - procedura di TRASMISSIONE
        - thread di service
        - thread dell'applicazione

- passagio dei parametri ai thread
    - i thread condividono la stessa mnemoria del processo principale 
    - quindi non è necessariop passargli dei paramentri quando  vengono inizializzati


---

Last login: Wed Nov 26 06:14:00 on ttys004
Restored session: Tue Nov 25 17:58:16 CET 2025

- implementazione della funzione di callback [tx_status_set__txEnd]/[tx_status_set__last_byte_send] che gestisce l'informazione dell'invio "fisico" dell'ultimo byte è molto semplice nel caso della comunicazione RS485, fa semplicemente due operazioni
    - abilita il pin della ricezione
        - questa è un istruzione che naturalmente dipende dall'hardware
    - imposta lo stato della comunicazioone in lettura
- utilizzo della funzione di callback
    - il connettore [rsSerialonnection] usa la funzione di callback per "connetterla" ovvero impostare la variabile associata appartenente al modulo sdk che la "urtilizza"/"chiama"
- colloocazione del modulo connettore [rsSerialConection]
    - questo modulo dovrebbe essere collocato in un modulo wrapper dipendendente dalla'applicazione o gruppo di applicazioni
        - [mpfw_fw2-<applcation_name>-2wrpr-sdk-usart] oppure
            - questo sarà un modulo specifico per la comunicazione seriale
            - il vantaggio di usare un modulo specifico è   quello che lo si può riutilizzare per altre applicazioni
        - [mpfw_fw2-<applcation_name>-2wrpr-hw_config]
            - questo sarà un modulo più generale che conterrà più sub-moduli che riguarderanno la configurazione hardware dell'applicazione
                - tra questi sub moduli certamente rientreranno quelli in cui si implementerano le funzioni associtte agli interrupts
    - tuttavia in via porvvisoria come impostazione di default lo si potrtebbe collocare nel modulo [mpfw_fw2-fnct-hw-2wrpr-sdk] poer spostare i files è sufficente creare una nuova versione della directory [wsp] cambiando i file [include_files.cmake] e [cpp_files.cmake]

- il modulo [rsSerial] che al si trova in un modulo wrapper [wrpr] verrà sostituito da un modulo [pph] che si trova in un modulo [real] oppure da un modulo 
    - tuttavia in via del tutto provvisoria lo si sotituira con un modulo wrapper [wrpr] in particolare
        - [hwUsart]
        - [hwUsartConfig]
        - [hwUsartIntfc]
    - situato nel modulo
        - [mpfw_fw2-fnct-hw-2wrpr-sdk]

- gestione modulo [uyProtocol] 
    - per poter essere il più generali possibile si dovrebbe avere una classe interfccia anche per il modulo [uyProtocol] perchè si possono avere più protocolli di comunicazione

---

Last login: Tue Nov 25 05:00:28 on ttys008
Restored session: Mon Nov 24 19:43:33 CET 2025


- gestione funzione di callback per la gestione del fine tx/rx
    - scopo uniformare l'interfacia della funzione di callback per la fine del processo di ricezione e di trasmissione
        - le risorse/periferiche di una microcontrollore/piattaforma necessitano di 
            - una configurazione iniziale che dipende dall'applicazione
            - questo codice dovrebbe essere contenute in funzioni la cui interfaccia invece è standard overo non dipende dalla applicazione ne dalla piattaforma
            - le condizionni di cui sopra fanno capire che questo codice dovrebbe esseere contenuto in un modulo wrapper [wrpr]
- collocare il modulo che implementa la comunicazione RS485 [pphRs485]
    - dovrebbe andare nei moduli [pph] e sarebbe deiriuvato dai moduli [pphRs232] & [pphPinPort]
        - in questo modo la gestione del canale rs485 sarebbe indipendente dalla piattaforma e non verrebbe implementato in un modulo wrapper [wrpr] ma in un modulo [real] che non gestisce direttamente codice dipendente dalla piataforma
    - altrimenti, in modo provvisorio,  dove potrebbe essere insierita l'iomplementazione della funzione di callback che si occupa della gestione dell'incvio dell'ultimo byte del buffer??
        - sarebbe da collocare questa implementazione nel modulo [hw_2wrpr] in un modulo suo ed insieme al modulo [rsSerialConnestions] che lo userebbe per "completare"/definire i parametri [extern] nel caso di sdk scritti in c o per definire le variabili [static] nel caso di codice scritto in c++
            - N.B.: il modulo [rsSerialConnections] è un modulo "particolare" ha il solo scopo di definire variabili "lasciate in sospeso" (variabili definite [extern]/[c_language] o definite [static]/[c++_language]) da altri moduli perche contenenti informazioni riguardanti livelli superiori al proprio che esulano dal proprio scopo (sono tipicamente funzioni di [callback] ed i moduli sono soo moduli che forniscpono un servizio)
- collocare il modulo di connessione per la configurazione della comunicazione seriale l'attuale [rsSerialConnections]
    - questo modulo dipenderebbe da un gruppo di applicazioni in particolare da chi decide che protocollo implementare (adesso che ci penso anche il modulo [uyProtocol] potrebbe far parte del codice [trdp] ma a questo punto anche i mnoduli [appl] potrebbero far parte a buon diritto del codice [trdp] )
- ripensando all'attuale gestione della seriale con i suoi moduli
    - [uyProtocol]
    - [sdk]
    - [rsSerialConnection]
    - sarebbe più ortodosso avere un modulo astratto che mette a disposizione delle strutture dati comunia cui fanno riferimento i due moduli principali e tra loro indipendenti
        - per essere ppiù chiari il file [mcuUsartTypeDefs.h] dovrebbe far parte di questo modulo che fondamentalmente ha il compito di fornire le interfacce di interazione tra 


---

Last login: Mon Nov 24 05:34:54 on ttys004
Restored session: Fri Nov 21 18:06:10 CET 2025

- gestione seriale
    - seriale virtuale
        - modulo [mcuUsart]
            - gestione "Last byte send" e lettura da parte di tutti i processi nella seriale virgtuale/simulata
                - è importante aspetaare che tutti i processi abbiano letto l'ultimo byte 
                    - diversamente se si rilascia subito il canale e subito un altro processo lo prende l'ultimo byte del precedente prcesso verrà cancellato/sovrascritto dal primo byte del nuovo processo
        - il  modulo di connessione [rsSerialConnection] dipende dall'applicazione o da un gruppo di applicazioni quindi non deve essere inserito nel modulo 
            - fa parte del codice di configurazione dell'hardware
                - a questo punto si potrebbe inserire nell'sdk ma parametrizzare le funzioni da "connettere" con delle [#define]
                    - non credo sia molto corretto perchè il modulo rsSerialConnesction per essere compilato introduce una dipendenza dal codice esterno all'SDK, e dipendente dall'applicazione, che non puo più essere posto ad un livello [0trdp]
                    - <da eseguire un test di compilazione della libreria> per dare l'ultimo responso


---

Last login: Fri Nov 21 04:57:06 on ttys004
Restored session: Thu Nov 20 18:01:03 CET 2025


- gestione del buffer di trasmissione & ultimo byte fisicamente spedito
    - il dubbio/la domanda è
        - chi deve gestire l'informazione relativa all'invio dell'ultimo byte fisicamene completato?
        - in particolare chi è che deve implementare la funzione di callback relativa all'ultimo byte?
            - questa informazione è importante per gestire la comunicazione rs-485 half-duplex e serve per conoscere il momento "giusto" in cui disattivare la trasmissione e attivare la ricezione
                - infatti è bene non essere
                    - nè troppo veloci
                        - altrimenti l'ultimo byte potrebbe essere tagliato e quindi essere perso
                    - nè troppo lenti 
                        - si rischia di perdere una eventuale risposa da parte di qualche altro dispositivo che ha ricevuto il buffer appena innviato
        - i possibili candidati sono i moduli
            - [uyProtocol]
            - [mcuUsart]
            - da creare [pphRs485] e lui che gestirà questa indformazione
                - il fatto che sia presente un modulo specifico per la rs485 è giusto 
                - è da capire da chi questo nuovo modulo possa reperire l'informazione relativa all'invio fisico dell'ultimo byte del buffer
                    - 
        - effettivamente questa innformazione dato che riguarda la comunicazione rs485 dovrebbe essere gestia dal modulo associato ad essa
            - chi si occupa della sola USART non è corretto che si occupi di essa
        - quando mettersi in modalità di ricezione?
            - questa è un informazione che però anche il modulo che gestisce in modo astrato la comunicazione è giusto che abbia
        - pensandoci bene sia il modulo [uyProtocol] sia il modulo [pphRs485] ma anche il modulo [mcuUsart] ha senso che gestiscano questa informazione
            - tuttavia se ci sono delle situazioni particolarmente stringenti in cui lo switch tra tx ed rx deve essere fatto il prima possibile "senza perdere millisecondi preziosi" questa informazione ed la relativa funzione di callback devono essere gestite ed implementate dal modulo che agisce direttamente sui pin che gestiscono questo switch quindi dovrà essere il modulo [pphRs485]
                - questa dovrebbe essere la soluzione migliore anche nell'ottica del multipiattaforma dal momento che se, diversamente, si agissce a livello sdk allora tutti gli sdk devono dotarsi dio un ulteriore modulo per gestire lo switch ena/disa, lavorando invece sul [pph] lo si fa automaticamante per tute le piattaforme

- implementazione del modulo [pphRs485]
    - il dubbio alla base è:
        - questo nuovo modulo deriva dai moduli
            - [pphUsart]
            - [pphPinPort]
        - oppure deriva solo dal modulo
            - [pphUsart]
            - e per il [pphPinPort] gli viene passato come parametro una sua istanza? 

- quando viene istanziata una periferica , pin port o seriale si fornisce anche la configurazione
    - la configrazione p,uò essere passata come funzione di callback da esseeree eseguita nella funzione init dell'elemento istanziato
    - questa dovrebbe essere l'impostazione dei moduli [pph]
    - in particolare il modulo rsSerial come si diceva dovrebbe esswere sostiruito da un modulo pph
- gestione di una periferica RS-485
    - questa deriva dll'unione di
        - periferica USART
        - periferica pinPort (enable/disable Tx/Rx)
    - questa unione però sarebbe da farla a livello wrapper/sdk e non a livello pph
        - il motivo è che la gestione del tx/rx enable/disable dovrebbe essere operata ad un livello il più vicino all'hw
            - non sono certo che questa motivazione abbia 
                - mancherebbe il perchè
                    - il perchè potrebbe essere il fatto che 
                        - il modulo wrapper si dovrebbe occupare solo dell'interfaccia comune  di lettura scrittura seriale per tute le piattaforme
                        - per   quanto riguarda i detagli hardware dell'implementazione dovrebbe invwce essere compito esclusivo dell'sdk
                        - la gestione dell'hardware mi aspetto di trovarla a livello sdk e non a livello più alto
                            - però è anche vero che i moduli stessi delle periferiche si riferiscono all'hardware
                                - diciamo che sono sempre sdk ma ad un livello più generalizzato valido per tutte le piattaforme

- com procedere per implementare le nuove modifiche
    - innanzitutto l'obiettivo
        - Step 1
            - quello di avere l'applicazione [mpfw_code_main_tst_20230810main]/[mpfw_fw2-main-app20240619_new_bis-5main]
                - funzionante con i moduli
                    - pph/uyProtocol (versione aggiornata ed eventuialmente rinomnato con un nome più appropriato ad esempio [svSerialCom]) 
                - e quindi anche con la gestione dell'hardware virtuale basata sui moduli
                    - [mcu]/[shm]
                - e mandare in archivio i moduli rsSerial e le sue dipendenze
        - Step 3
            - implementare la versione reale su piattaforma mac della seriale quindi usando i moduli hardware via usb
                - lo scopo è quello di sotituire l'utilizzo del [minicom]
        - Step 2
            - aggiornare l'interfaccia per l'applicazione basata sulla piattaforma mac
            - quindi usare i moduli [tui] per creare l'interfaccia di simulazione  anche per la parte di service
        - Step 3
            - iniziare a implementare l'interfaccia utente da far girare nelle piattaforme reali e inserirla all'interno dell'ambiente di simulqzione/service per le piattaforme virtuali come quella [mac]
    - 
        


- modifiche da apportare al codice corrente
    - modulo [uyProtcol]
        - aggiungere la funzione di callback [g_callback_protocol_functions.tx_status_set__last_byte_send] che verrà usata nel modulo [mcuUsart]
        - uso delle funzioni di callback [TxEnable/RxEnable]
            - da capire chi le deve implementare 
                - dipendono dalla piattaforma ma non dal micro
                    - quindi non dovrebbero andare nell'sdk
                    - però si può pensare all'esistenza di più livelli di sdk
                        - ad esempio ci possono essere due piattaforme che usano la stessa scheda ma la configurano a livello hardware in modo diverso
                        - viene spontaneo pensare che una parte delcodce dell'sdk sia diverso
                        - però si potrebbe pensare che dipenda dall'applicazione partricolare
                            - ogni applicazione ha la sua configurazione hardware pur avendo la stessa piattaforma
                            - questo è il caso in cui i moduli [appl] & [main] hanno il codice [trdp/sdk]
                        - quindi 
                - quidi da inseirle come esten
    - modulo [mcuUsart]
        - inserire le funzioni di callback implementate dal modulo [uyProtocol], in particolare
            - g_callback_protocol_functions.tx_buffer_management(.)
            - g_callback_protocol_functions.tx_status_get__completed()
            - g_callback_protocol_functions.tx_status_set__last_byte_send()
                - questa funzione è già implementata nel modulo wrapper [rsSerial]
    - modulo [pphUsart]
    - modulo [rs5erial] da sostituire con il modulo [pphUsart]
        - adesso
            - questo modulo è della tipologia/livello wrapper
            - gestisce il tx/rx enable/disable
            - fornisce un interfaccia comune a tutte le piattaforme
    - modulo [ap_krThread02]
        - eliminare la dipendenza dal modulo [rsSerial]
        - usare al suo posto il modulo [pphUsart]/[pphRs485]


---

Last login: Thu Nov 20 05:13:11 on console
Restored session: Wed Nov 19 16:52:34 CET 2025


- modulo [pphUsart]
    - questo modulo dipenderà dal modulo [uyProtocol]
    - quindi deve essere totalmente rivisto e ripensato almeno nella sua parte inteerna
    - come interfaccia per moduli di livello superiore dovrebbe andare bene così come è adesso

- gestione hardware virtuale
    - sequenza delle scritture nel processo di trasmissione e fine dello stesso
        - funzioni usate dal modulo "user"
            - [wrTxFifo/fullTxFifo]  ...|___|[W]---|[W]---|x-----|x-----|x-----|[W]---|x-----|x-----|x-----|x-----|x-----|x-----|x-----|[E]---|...
                - [W]: eseguite le funzioni di <wrTxFifo/fullTxFifo> dai processi "user"
                - [E]: stato del buffer di Tx posto a [Tx_completed] 
        - funzioni usate dai moduli [mcuUsart] & [shmMcuUsart]
            - [sendData/emptyTxFifo] ...|_r_|--[W]-|_rrrr_|_rrrr_|_rrrr_|--[W]-|_rrrr_|_rrrr_|_rrrr_|--[W]-|_rrrr_|_rrrr_|_rrrr_|--[U]-|_rrrr_|...
                - [W]: esegite le funzioni di <sendData/emptyTxFifo> dal modulo [mcuUsart]
                - [U]: UN-lock del lock del canale di trasmissione ed eventuale chiamata di una funzione di callback
    - come integrare il modulo [uyProtocol] con la gestione virtuale della periferica Usart ne quindi con i moduli [shmMcuUsart], [mcuUsart]
        - la procedura di comunicazione ovvero l'equivalene dellla funzione di interrupt [fsl_usart_mod/USART_TransferHandleIRQ] è la funzione
            - [mcuUsart_t::check_read_write]
                - "da capire" / "il problema da risolvere"
                    - come usare le funzioni di callback definite nel modulo [uyProtocol]
                        - 1. la funzione [shmMcuUsart_t::setData(g_tx_data)] dovrebbe essere chiamata indirettamente attraverso la funzione 
                            - [g_callback_protocol_functions.tx_buffer_management(base)]
                    - come distinguere le funzioni svolte dall'hardware/registri e quelle che agiscono sul buffer?
                        - focalizzarsi su
                            - lo stato del "registro" che rappresenta il byte che viene "fisicamente" trasmesso/ricevuto
                            - il buffer di dati che deve essere inviato sul canale di comunicazione
                        - pensare che ci sono due strutture dati 
                            - registro periferica
                            - ram buffer
                        - messe in sequenza, allora
                            - il modulo [mcuUsart] si occupa di trasferire i dati tra queste due strutture dati
                            - il modulo [uyProtocol] si occupa dell'interfaccia tra il buffer e lo user ovvero i moduli di livello superiore che usano il servizio della comunicazione seriale
                        - analisi delle funzioni dei moduli [shmMcuUsart] & [mcuUsart] comparate con quelle "reali" di un mirco, ad esempiuo nxp si veda quindi il modulo [fsl_usart_mod]
                            - [shmMcuUsart::writeProcedureRun]
                                - controlla se l'interrupt associato alla seriale ed in particolarfe alla procedura di trasmissione è attivo
                                    - i partametri letti sono
                                        - [g_ptrShmActive->gDataWriterPid]
                            - [shmMcuUsart::pidMatches]
                                - dice se il processo che ha attivato l'interrupt sia quello che adesso ne sta eseguendo la funzione handler
                                - N.B.: insieme alla precedente funzione equivale alla funzione svolta dalla flag [base->FIFOSTAT::USART_FIFOSTAT_TXNOTFULL_MASK]
                                    - questa flag dice se l'interrupt è stato ativato dalla trasmissione, l'altra possibilità è che sia attivato dalla ricezione
                            - [shmMcuUsart::getData]
                                - legge dal registro in particolare dal file condiviso tra i processi
                            - [shmMcuUsart::setData]
                                - scrive nel registro in particolare nel file condiviso tra i processi
	                        - [shmMcuUsart::WriterPidClr]
                                - rilascia il lock del canale di comunicazione
	                        - [shmMcuUsart::WriterPidSet]
                                - esegue il lock del canale di comunicazione
                            - [mcuUsart::tx_fifo_full]
                                - viene letta nell'handler dell'interrupt della communicazione
                                - 
                            - [mcuUsart::tx_fifo_write]
                                - viene eseguita da moduli user posti ad un livello più alto
                            - [mcuUsart::tx_fifo_empty_out]
                                - viene eseguita nell'handler dell'interrupt della communicazione
                                - ed eseguita dopo aver scritto nel registro
                                - per permettere ai moduli di livello superiore di poterla di nuovo impostare
                            - da aggiungere [setDataEnd]/[txDataEnd_functionality]
                                - dice se l'ultimo byte che è stato inviato è stato ricevuto
                                    - a questa funzione nel caso del modulo [fsl_usart_mod] è associata anche una funzione di [callback] che viene chiamata quando l'evento si verifica;
                                        - questa funzione di callback dovrebbe essere implemntata dal modulo [uyProtocol]
                                - da capire se questa funzione a motivo di esserci
                                    - avrebbe lo scopo di simulare la flag [USART_INTENSET_TXIDLEEN_MASK] del micro nxp
                                        - nel caso della usart virtuale potrebbee essere usata per accertarsi che tutti i processi abbaino letto il byte/buffer inviato
                                    - questa funzione è utile nel caso si debba gestire [Tx/Rx_enable] come nel caso della comuincazione [RS-485/Halfduplex]
                            - da aggiungere la funzione di [level_Watermark]
                                - questa funzione ha lo scopo di "allargare" il "registro" di Tx/Rx per farlo diventare un buffer
                                    - permetterebbe di velocizzare la procedura di trasmissione anche se ha lo svantaggiodi complicare la gestione della comunicazione
                                        - per questo motivo non ha una priorità molto alta a meno che la coumunicazione risulti molto lenta
                                        - per questo motivo non ha una priorità molto alta ma solo se la coumunicazione non risulti molto lenta
                                        - per questo motivo non ha una priorità molto alta subordinato al fatto che la coumunicazione non risulti molto lenta
                                - N.B.: questa possibilità è gia contemplata dal modulo [shmMcuUsart] ma non dal modulo [mcuUsart] 
    - da capire
        - perchè ci sono due [pid] nel mdoulo [shmMcuUSART]?
            - ciascuno che significato ha?
                - il [g_pid] è il numero di processo associato all'applicazione e fornito/rilasciato dal sistema operativo della piataforma ad esempio [mac_osx]
                    - viene letto con la funzione di sistema [getpid()] all'inizio della funzione [shmManager_t::open]
                - non si capisce invece l'utilità e/o la funzione del [g_pid2]
                    - è abbastanza probabile che il suo scopo è quello di gestire più istanze dell'oggetti [mcuUsart]
                    - viene assegnato quando un oggetto pphUsart viene istanziato
                        - di default gli viene assegnato un valore pari a 0 (zero)
        - e come vengono inizializzati/impostati?
            - il [g_pid] viene assegnato eseguendo la funzione [shmManager_t::open]
            - il [g_pid2] viene assegnato nel costruttore della classe [mcuUsart]

---

Last login: Wed Nov 19 06:13:49 on ttys003

- gestione delle dipendenze tra moduli & significato dei livelli presenti nel nome del mmodulo (0abst, 0trdp, 1trdp, 2wrpr, etc.)
    - 0abst
        - è alla base del gruppo di moduli con lo stesso nome
    - 0trdp
        - è un modulo di terze parti che non conosce l'ambiente [mpfw_fw2] e quindi non ha nessuna dipendenza cpn esso
    - 1trdp
        - è tipicamente un modulo che serve ad "adattare"
    - le dipendenze tra tipi di moduli
        - [x]<y>abst: non dipendende da nessuno
        - [x]<y>trdp: 
            - può dipendere solo da abst
            - puo dipendere da un modulo 0trdp esterno al gruppo del modulo 
        - [x]<y>wrpr: dipende da trdp e eventualmente da abst
        - [x]<y>real: 
            - ha lo scopo di rendere "reali" gli oggetti astratti (interfacce tipicamante) definiti nel modulo abst attrverso anche il modulo wrpr
            - non dovrebbe dipendere direttamente da trdp
                - questa restrizione ha lo scopo di semplificare le operazioni di aggiunta di nuove piattaforme e in genere di moduli [trdp]
            - può dipendere (direttamente) solo da abst
            - può dipendere (direttamente) solo da wrpr  
        - [x]<y>appl
            - non dovrebbe dipendere direttamente da trdp
                - ma questo non significa che non possa avere lui stesso una sezione [trdp]
                - questa restrizione ha lo scopo di semplificare le operazioni di aggiunta di nuove piattaforme e in genere di moduli [trdp]
        - [x]<y>test
            - non deve dipendere direttamente da trdp
        - [x]<y>main
            - non deve dipendere direttamente da trdp

- gestione dell'hardware virtuale
    - alla base c'è il modulo [hw-1trdp::shm]
        - in particolare
            - [shmBase]
                - da cui derivano
                    - [shmManager]
                        - imposta la struttura di [shmBase]
                        - in particolare il pid dei processi
                    - [shmPinPort]
                        - legge la struttura [shmBase]
                        - in particolare il pid dei processi
                        - per gestire le operazioni si lettura e scrittura in mmodo sincronizzato con il semaforo messo a disposizione
                    - [shmUsart]
                        - legge la struttura [shmBase]
                        - in particolare il pid dei processi
                        - per gestire le operazioni si lettura e scrittura in mmodo sincronizzato in modo di non avere sovrapposizione tra i processi

- implementare la versione real della seriale
    - 
- implmenetare la versione virtual della seriale attraverso il modulo [uyProtocol]
    - quindi ccapire come implementae le funzioni di callback
        - il file condiviso creato nel modulo [shm]/[mpfw_fw2-fnct-hw-1trdp-sdk-mac] con la funzione [shm_open(...)]
        - è l'equivalente dei registri associati al buffer di comunicazione "fisico" di un microcontrollore
        - da capire
            - come inserire le funzioni di callback implemenate dal modulo [uyProtocol]
                - dubbio!!!
                    - analizzando il codice associato alla piattaforma [nxp] mi chiedo:
                        - come viene attivato l'interrupt la cui funzione di handler è [USART_TransferHandleIRQ] quando si trasmette il buffer?
                            - si può capire con la ricezione
                            - ma con la trasmissione come fare?
                                - viene fatto con la funzione del modulo [fsl_usart_mod] o del modulo [stm32f7xx_hal_uart_mod] [USART_tx_enable]
                - analisi del flusso delle chiamate
                    - nel processo di trasmissione sotto la piattaforma [mac]/(usart virtuale)
                        - 
                        - [pphUsart_t::txBuff_send]
                    - nel processo di trasmissione sotto la piattaforma [nxp]
                        - [rsSerial::Tx] chiamato dallo user
                            - [uyProtocol::send_non_blocking] preparazione dello stato del buffer
                            - [rsSerial::USART_tx_enable]  attivazione dell'interrupt di trasmissione 
                                - per simulare l'interrupt si dovrebbe attivare un thread
                                    - da capire come fare
                        - inizio del ciclo di trasmissione
                            - si ricorda che si a inviando un buffer di dai
                        - [fsl_usart_mod/USART_TransferHandleIRQ] invio del buffer con la chimata alla funzione [tx_buffer_management]
                            - [uyProtocol::tx_buffer_management]
                                - [uyProtocol::buffer_management] chiama la funzione di [callback] [fsl_usart_mod/reg_write]
                                    - [fsl_usart_mod/reg_write] invio sul canale fisico di un byte
                            - [] l'istruzione
                                - if( (base->FIFOSTAT & USART_FIFOSTAT_TXNOTFULL_MASK)  != 0U ) ...
                                    - azzera la flag dell'interrupt che viene riattivata con l'istruzione di write ma dopo che il processo di invio è sato completato
                        - fine del ciclo (il cilco termina quando il buffer gestito da [uyProtocol] è vuoto)


- quando si seleziona la piattaforma mac si deve mettere come [trdp] la seriale virtuale o reale

- gestione della seriale
    - si potrebbe pensare di attivare un funzionalità [trdp] in particolare della seriale
        - quindi avere 
            - [trdp/rs232/virtual_rs232]
            - [trdp/rs232/real_rs232]
                - [mpfw_fw2-trdp-sdk-mac-1trdp-virtual_usart]
                - [mpfw_fw2-trdp-sdk-mac-1trdp-real_usart]
                - oppure
                - [mpfw_fw2-trdp-mac_real-0trdp]
                - [mpfw_fw2-trdp-mac_virtual-0trdp]

:::::::::::::::::::
- extract from "note_20251106_app_scope_n_implementation.md"
    Friday, 15th August 2025
    
    - cose da fare
        - il parsing del nome del layer
            - come si vede dagli esempi sono diversi nel caso di
                - type diverso da [trdp] e livello [1trdp]
                    - mpfw_fw2-res-1trdp-sdk-stm-stm342f769_disco -> mpfx_fw2-<type>-<functionality>-1trdp-<trdp functionality>-<owner>-<trdp functionality attributes list>
                - type diverso da [trdp] e livello [2wrpr]
                    - mpfw_fw2-res-2wrpr-sdk -> mpfx_fw2-<type>-<functionality>-2wrpr-<trdp functionality>-<trdp functionality attributes list>
                    - mpfw_fw2-res-2wrpr-sdk-usart -> mpfx_fw2-<type>-<functionality>-2wrpr-<trdp functionality>-<trdp functionality attributes list>
                - type uguale a [trdp] e livello [1trdp]
                    - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-1trdp-usart  -> mpfx_fw2-<type>-<functionality>-<owner>-<functionality attributes list>-1trdp-<level functionality attributes list>
:::::::::::::::::::

---

Last login: Mon Nov 17 05:37:52 on ttys010
Restored session: Sun Nov 16 19:46:52 CET 2025

- gestione della seriale
    - si potrebbe pensare di attivare un funzionalità [trdp] in particolare della seriale
        - quindi avere 
            - [trdp/rs232/virtual_rs232]
            - [trdp/rs232/real_rs232]
                - [mpfw_fw2-trdp-sdk-mac-1trdp-virtual_usart]
                - [mpfw_fw2-trdp-sdk-mac-1trdp-real_usart]
                - oppure
                - [mpfw_fw2-trdp-usart-0trdp-virtual_usart]
                - [mpfw_fw2-trdp-usart-0trdp-real_usart]
- analisi dllo schema/pattern che sa alla base della gestione della seriale per mezzo del modulo uyProtocol
    - ci sono due "attori"  posti alla base che non si conoscono tra loro ma forniscono un servizio
        - entrambi richiedono che vengano definite delle funzione di [callback] con le quali forniscono un servizio
    -  non è del tutto vero il servizio implementato nel modulo di estensione dell'sdk conosce l'esistenza del modulo uyProtocol
        - questa dipendenza ha origine nel moulo di "connessione" [rsSerialConnection.cpp]
            - il modulo di "connessione" lo si potrebbe separare dal modulo di estensione sdk
            - ed il modulo che lo conterrebbe sarebbe un [wrapper]
    - analisi del modulo [uyProtocol]
        - è la parte di codice che gestisce lo stato del bufer di comunicazione 
        - e mette a disposizione le routine di alto livello, indipenednti dalla piattaforma (è un modulo wrapper come si dicea sopra) per leggere e scrivere sulla seriale
    - analisi del modulo [1trdp-sdk-usart]
        - è la parte di codice che gestisce "fisicamente" il buffer di comunicazione 
            - in particolare fa da ponte tra 
                - la memoria riservata a bufer di comunicazione e gestita, a sua insaputa, dal modulo [uyProtocol]
                - i registri del modulo hardware che gestisce la comunicazione fisica
            - ovvero
                - legge dal buffer di memoria e scrive nei registri hw
                - legge dai registri hardware e scrive nel buffer di memoria
        - il processo che gestisce il trasfeerimento dati tra le due memorie quella RAM e quella dei registri della periferica USART
        - ha bisogno di conoscere lo stato del buffer di memoria RAM per potervi leggere e scrivere
            - se vogliamo ci sono due processi che leggono e scrivono su una stessa porzione di memoria (il modulo [uyProtocol] e il modulo [1trdp-sdk-usart])
            - è quindi c'è bisogno di una procedura di sincronizzazione
                - questa procedura viene implementata attraverso delle opportune funzioni di callback
                    - le funzioni di callback sono funzioni che enono eseguite da un processo di "servizio"
        - in particolare
            - quando il contenuto del bufer è pronto per essere inviato sul canale fisico di comunicazione?
            - quando considero terminata la ricezione di un buffer dal canale fisico di comunicazione?
        - queste informazione gliele fornisce indirettamente il modulo [uyProtocol] con delle opportune funzioni di callback che il presente mdulo chiede di implementare
            - la funzione di callback è un metodo per trasformare una dipendenza "diretta" in "indiretta"
            - con i seguenti vantaggi
                - la dipendenza "indiretta" permette di rendere indipendente il modulo che ne è soggetto
                - si ha un solo modulo per più situazione/"use case"
            - e l'unica limitazione
                - per usare il modulo bisogna implementare del codice non è sufficente usare le funzioni 


---

Last login: Thu Nov  6 05:48:47 on ttys009
Restored session: Wed Nov  5 19:21:18 CET 2025

- aggiornare il codice cmake dei seguenti moduli
    - base
        - mpfw_fw2_fnct_base
    - hw/layer
        - mpfw_fw2_fnct_hw_0abst
        - mpfw_fw2_fnct_hw_1trdp_sdk  
        - mpfw_fw2_fnct_hw_2wrpr
        - mpfw_fw2_fnct_hw_3real
    - tui/layer
        - mpfw_fw2_fnct_tui_0abst
        - mpfw_fw2_fnct_tui_2wrpr
        - mpfw_fw2_fnct_tui_3real

- rivedere e documentare in una nota le regole per assegnare i nomi ai moduli
    - 

---

Friday, 31st October 2025

Last login: Fri Oct 31 13:51:25 on console
Restored session: Thu Oct 30 18:32:08 CET 2025

- sembrerebbe che il modulo [uyProtocol] svolga la funzione di servizio e in particolare di wrapper
    - la cosa interessante è che si può evitare di implementare un <modulo wrapper> con il codice diviso tra <common> e <platform> 
        - tutto sta nel impostare il modulo [rsSerialConnection] che si può fare in un modulo a livello di [sdk/driver]
        - considerare che
            - il modulo [uyProtocol] non vede i moduli utilizzatori del servizio
        - alla luce di tutto questo sarebbe da rinominare il modulo [uyProocol] in [svSerialCom]
- per unire il vecchio con il nuovo sarebbe da fare quanto segue
    - premessa:
        - il modulo <wrapper> [mcuUssart] non ha motivo di esserci
            - come accennato sopra questa funzione la svolge il modulo [uyProtocol]/[svSerialCom]
    - il modulo [mcuUsart] va spostato dal modulo  <wrapper>/[mpfw_fw2_fnct_hw_2wrpr] nel modulo <sdk>/[mpfw_fw2_fnct_hw_1trdp_sdk]
    - il "nuovo" modulo [mcuUsart](sposato come sabilito al punto precedente) conterrà il modulo [rsSerialConnection]

---

Last login: Thu Oct 30 04:48:07 on console
Restored session: Wed Oct 29 19:02:56 CET 2025

- si deve capire come
    - implementare le funzioni pubbliche definite nel modulo [mcuUsart] per le piattaforme reali in particolare <nxp> e <stm32f769_disco>
        - **bool tx_fifo_full           (void);**
            - TRUE
                - si deve inviare il contenuto del buffer
            - FALSE
                - nessun byte da inviare
        - **void tx_fifo_empty_out      (void);**
            - dopo aver inviato il contenuto del buffer si pulisce il buffer ovvero si cambia lo stato del buffer
        - **void tx_fifo_write          (char c);**
            - quando il buffer è pieno (vedere funzione **tx_fifo_full**) si invia il contenuto del buffer

        - **bool rx_fifo_full           (void);**
        - **uint16_t rx_fifo_read       (void);**
        - **bool check_read_write       (void);**
        - **uint16_t read               (void);**

        - **void chEnable               (void);**
    - l'idea dell'impostazione "vecchia" parte con l'analizzare cio che l'sdk della piataforma fornische e aggiorna le routine dell'sdk
        - forse questa è la strategia più corettadal momento che la gestione del buffer di comunicazione se lo si vuole fare in maniera modulare ha un po' di partcolarità da rispettare
            - funzioni aggiornate
                - **void USART_TransferHandleIRQ(USART_Type *base, usart_handle_t *handle)**
                - **status_t USART_TransferReceiveNonBlocking(USART_Type *base,**
                - **status_t USART_TransferSendNonBlocking(USART_Type *base, usart_handle_t *handle, usart_transfer_t *xfer)**
            - funzioni aggiunte
                - void buffer_init(callback_protocol_functions_t* p_ptrCallbacks)  {
                - void    USART_reg_write(void* p_ptrData, char p_data)	{
                - uint8_t USART_reg_read(void* p_ptrData)	{
                - void USART_tx_disable(void* p_ptrData)	{
                - void USART_rx_disable(void* p_ptrData)	{
                - status_t USART_tx_enable(USART_Type *base)
                - status_t USART_rx_enable(USART_Type *base)
        - l'aspetto principale che "obbliga" ad usare questo approccio è la gestione del buffer di comunicazione in Tx e in Rx ed in particolare la sua lunghezza
            - la lunghezza del buffer dipende dal protocollo usato nel costruire il buffer
            - c'è una dipendenza 



---

Wed Oct 29 08:28:40 CET 2025

- eseguire il build delle applicazioni
    - scripts a disposizione
        - eseguire l'intero build (cmake & c++)
            - creazione/compilazione cmake files
            - esecuzione del build con i cmake files creati al passo precedente
        - eseguire solo "compilazione" cmake files
            - creazione/compilazione cmake files
        - eseguire solo il build del codice sorgente dell'applicazione
            - esecuzione del build del codice sorgente


- gestione della seriale multipiataforma
    - nel modulo wrapper ci deve essere nel common/src un file header (.h) con le funzioni comuni da essere implementate
        - nmon è proprio del tutto correto avere file header differenti con lo stesso contenuto

- due aspetti da completare
    - aggiornare i moduli
        - fnct/hw
            - mpfw_fw2_fnct_hw_0abst
            - mpfw_fw2_fnct_hw_1trdp_sdk
            - mpfw_fw2_fnct_hw_2wrpr
            - mpfw_fw2_fnct_hw_3real
        - alla nuova impostazione del codice cmake
    - integrare la gestione della seriale tra il vecchio ed il nuovo
        - i file oggetto di studio sono
            - impostazione vecchia
                - moduli
                    - **mpfw_fw2-fnct-res-2wrpr-sdk**
                        - platform
                            - mac
                                - [rsSerial]
                                    - [sdkUsart]
                                - <rsSerialConnection>
                                - dipendenze
                                    - comuni a tutte le piataforme
                                        - **mpfw_fw2-fnct-core-3real** 
                                            - [uyProtocol]
                                        - **mpfw_fw2_fnct_base**
                                            - [container]
                                    - specifiche della piattaforma
                                        - **mpfw_fw2-trdp-sdk-mac-0trdp**
                            - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-1trdp-usart / mpfw_fw2-fnct-res-1trdp-sdk-stm-stm32f769_disco
                            - mpfw_fw2-trdp-sdk-nxp-1trdp-usart / mpfw_fw2-fnct-res-1trdp-sdk-nxp
            - impostazione nuova
                - moduli
                    - **mpfw_fw2_fnct_hw_2wrpr**
                        - dipendenze
                            - comuni
                            - specifiche
                                - **mpfw_fw2_fnct_hw_1trdp_sdk**
                            - **mpfw_fw2_fnct_hw_0abst**
                                - **mpfw_fw2_fnct_base**