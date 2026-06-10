
---

Last login: Wed Sep  3 04:28:24 on ttys006


---

Last login: Fri Aug 29 05:53:58 on ttys006


---

Last login: Thu Aug 28 04:24:00 on ttys006

- c'è un problemino nella gestione dei file di configurazione
    - quando un modulo imposta un file di configurazione di una'altro modulo lo fa nel file "set_public_rpath.make"
        - il file "set_public_rpath.make" ha la caratterisitica che viene chiamato solo nella fase di init in un punto in cui le versioni del codice sorgente non sono ancora state definite
            - una possibile soluzione è quella di creare un file "set_config_files.make" e chiamarlo sempre nella fase di init ma dopo aver impostato le configurazione dei file del codice sorgente
                
---

Last login: Wed Aug 27 03:04:16 on ttys006


---

Last login: Tue Aug 26 2025 04:28:32


---

Monday, 25th August 2025 - Last login: Mon Aug 25 05:15:29


---

Sunday, 24th August 2025 - clock: 13:18


---

Saturday, 23rd August 2025 - clock: 04:58

- gestione dei file .cpp e .h
    - ci sono tanti file "cpp_files.cmake" quanti sono i moduli [trdp] + 1 che saerebbe il modulo [common]/[cmmn]
        - il nome delle liste dei file .cpp da compilare sono codificati nel modo seguente
            - <nome del modulo>_<nome del trdp/cmmn>_SOURCE_FILES_CPP
                - [FNCT_CORE_2WRPR]_[sdk]_SOURCE_FILES_CPP
            - <nome del modulo>_<nome del trdp/cmmn>_SOURCE_FILES_CPP_WDEP
                - [FNCT_CORE_2WRPR]_[sdk]_SOURCE_FILES_CPP_WDEP
    - la lista XXX_SOURCE_FILES_CPP è definita in questo modo
        - [XXX]_SOURCE_FILES_CPP = [XXX]_cmmn_SOURCE_FILES_CPP + Summ([XXX]_[id]_SOURCE_FILES_CPP; id IN LIST [XXX]_TRDP_LIST)
    - la lista XXX_SOURCE_FILES_CPP_WDEP è definita in questo modo
        - [XXX]_SOURCE_FILES_CPP_WDEP = [XXX]_SOURCE_FILES_CPP_WDEP + [XXX]_SOURCE_FILES_CPP
    - quidi la rourine ricorsiva che si dovrà implementare avrà i seguente schema
        * function set_ccp_files_list(_module_) -> OUT _module_/_SOURCE_FILES_CPP & _module_/_SOURCE_FILES_CPP_WDEP
            * loop _item_ IN LIST _module_/_DEPS_LIST
                * set_ccp_files_list(_item_)
                * _module_/_SOURCE_FILES_CPP_WDEP = _module_/_SOURCE_FILES_CPP_WDEP + _item_/_SOURCE_FILES_CPP_WDEP
            * end loop
            * _module_/_SOURCE_FILES_CPP        = _module_/_cmmn_SOURCE_FILES_CPP + Sum(_module_/_[id]_SOURCE_FILES_CPP; [id] IN LIST _module_/_TRDP_LIST)
            * _module_/_SOURCE_FILES_CPP_WDEP   = _module_/_SOURCE_FILES_CPP_WDEP + _module_/_SOURCE_FILES_CPP


/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/trdp/sdk/stm/stm32f769_disco/layer/mpfw_fw2-trdp-sdk-stm-stm32f769_disco-0trdp/build_main/stm32f769_disco/CMakeFiles/_trdp-sdk-stm-stm32f769_disco-0trdp.out.dir/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/trdp/sdk/stm/stm32f769_disco/layer/mpfw_fw2-trdp-sdk-stm-stm32f769_disco-0trdp/src/v_07/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang

---

Thursday, 21st August 2025 - clock: 05:14

- decidere 
    - come
    - dove
    - impostare gli rpath e dirs dei [trdp]
    - per gestire i [trdp] forse è meglio usare una matrice

---

Wednesday, 20th August 2025 - clock: 04:30 circa


- cose da fare
    - per gestire il codice [trdp]
        - step 1
            - aggiornare lo script di bash per insierire non solo la piattaforama ma anche altro codice [trdp] come ad esempio la gestione dell'USB oppure il file system, etc.
                - 


---

Tuesday, 19th August 2025 - clock: 10:15 circa

- MODULE_RPATH_PART1_TYPE_FNCT1
- MODULE_RPATH (with functionality attribute if it is)

- MODULE_NAME_PREFIX
- MODULE_NAME_STEP1_TYPE_FNCT1
- MODULE_NAME_STEP2_TYPE_FNCT (with functionality attribute if it is)

- MODULE_NAME_PART1_TYPE -> MODULE_TYPE
- MODULE_NAME_PART2_FNCT (with functionality attribute if it is) -> MODULE_0NAME


- MODULE_NAME_PART1_LAYER_PREFIX
- MODULE_NAME_PART2_LAYER_DESC
- MODULE_NAME_LAYER

- MODULE_TYPE
- MODULE_0NAME
- MODULE_RPATH
- MODULE_LAYER
- MODULE_NAME_COMPLETE_WO_PREFIX -> MODULE_NAME


---

Monday, 18th August 2025 - clock: 13:47

- gestione cambio di piattaforma o in generale di codice [trdp]
    - non è vero che per pasare ad una nuova piattaforma basta creare il codice di livello [2wrpr] e [1trdp] per la piattaforma
        - anche il codice dei moduli con livello superiore al 2 possono avere del codice sipendente dalla piattaforma
            - si tratta di sub-funzionalità specifiche di alcune piattaforme
                - un esempio è la sub-funzionalità di [service]
                    - questa al momento è pensata solo per la piattaforma si simulazione [mac]
                    - naturalmente se questo codice (il codice della sub-funzionalità) non ha dipendenze con il codice della sezione [common] del suo stesso modulo di appartenenza (in questo caso il modulo sarà un modulo [4appl])
                    - allora questo codice può essere riportato all'esterno in un modulo specifico che potrebbe essere posizionato ad un [livello_3]
        - al momento per quanto riguarda il codice dipendente da [trdp] in moduli con livello superiore al 2 mi viene in mente solo la situazione di sub-funzionalità
            - ci sarebbero anche i file di configurazione ma questo è codice che non viene compilato sebbene vemnga usato nella procedura di build/compilazione



---

Sunday, 17th August 2025

- corrispondenza biunivoca tra [sdk] e [platform]
- gestione dei trdp
    - la cosa comoda da fare è gestire i trdp in modo "modulare"
        - senza usare particolari file .cmake di configurazione
    - certamente i [trdp] che si devono usare in un progetto devono essere passati al comando di build
        - i dati passati al comando di build devono essere sufficenti per gestire i [trdp] all'interno del codice cmake
            - da questi dati si ricava la lista dei trdp [TRDP_FNCT_ATTR_LIST]
                - che viene usata quando si devono chiamare gli include per i file header .h e .cpp
    - la cosa principale è quella di definire per ciascun modulo le directory di
        - [ROOT]
        - [WSP]
        - [BUILD] ma solo per il common e l'sdk
        - [include_H_files]
        - [source_CPP_files]
            - al solito i file di configurazione sono trattati a parte anche qui però dipendono dal trdp usato
        - per questi ultimi due file i moduli con layer [2wrpr] devono controllare solo il proprio [trdp]
            - o forse è meglio subordinarlo alla presenza del [common]
                - ma forse questo è un altro aspetto


---

Saturday, 16th August 2025

- stabilire quando determinare l'owner ed in quale posizione si trova
- gli attributi delle funzionalità a livello di modulo e di layer sono opzionali ovvero possono essere presenti come possono non esserlo
    - il nome [MODULE_0NAME] è composto da
        - funzionalità [MODULE_FNCT]
        - owner [MODULE_OWNER] quando presente
            - presente quando (obbligatorio)
                - [MODULE_TYPE] = [trdp]
                    - esempio
                        - trdp
                            - sdk
                                - stm
        - attributi della funzionalità [MODULE_FNCT_ATTR] quando presenti (non sono subordinati alla presenza dell'owner)
            - al momento presenti solo quando
                - [MODULE_TYPE] = [trdp]
                    - esempio
                        - trdp
                            - sdk = [MODULE_FNCT]
                                - stm = [MODULE_OWNER]
                                    - stm32f769_disco = [MODULE_FNCT_ATTR]
    - il layer [MODULE_LAYER] è composto da
        - codice base che riporta all'inizio il numero del livello [MODULE_LAYER_0NAME] ([0abst], [0trdp], [1trdp], [2wrpr], etc.)
        - funzionalità del layer [LAYER_FNCT], quando presente
            - presente quando
                - [MODULE_LAYER_0NAME] = [2wrpr] oppure [1trdp] (obbligatorio in entrambe i casi)
                    - esempio
                        - 2wrpr-sdk
                        - 1trdp-sdk-stm
        - owner del layer [LAYER_OWNER], quando presente
            - presente quando
                - ([MODULE_TYPE] != [trdp]) && ([MODULE_LAYER_0NAME] = [1trdp]) (obbligatorio)
                    - esempio
                        - 1trdp-sdk-stm
        - attributi della funzionalità del layer [LAYER_FNCT_ATTR], quando presente ma subordinato alla presenza del [LAYER_FNCT]
            - esempio
                - 2wrpr-sdk-usart
                - 1trdp-sdk-stm-usart
    - il nome completo del modulo sarà
        - "mpfw_fw2-${MODULE_TYPE}-${MODULE_0NAME}-${MODULE_LAYER}"

---

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
    


- per la gestione del nome/path dei moduli si è deciso di dare la precedenza alla funzionalità al posto dell'origine/owner, quindi
    - nello schema 2 avremo
        - trdp
            - <sub-functionality>, i.e. sdk
                - <owner>, i.e. stm
                    - stm32f769_disco
                        - src
                        - wsp
                            - c_<configruazine del codice sorgente>
                            - v_<name version>
                                - cmake
                                - stm
                                    - stm32f769_disco
    - stessa cosa per le directories del [type] [trdp], avremo quindi
        - trdp
            - sdk
                - mac
                - nxp
                - stm


- trdp/sdk/stm/stm32f769_disco/layer/mpfw_fw2-trdp-sdk-stm-1trdp-stm32f769_disco-usart/wsp/cmake/v_32stm0

- fnct/res/layer/mpfw_fw2-fnct-res-1trdp-sdk-stm-stm32f7_disco-usart/wsp/cmake/v_32stm0
- fnct/res/layer/mpfw_fw2-fnct-res-1trdp-sdk-mac-usart/wsp/cmake/v_32stm0

- fnct/res/layer/mpfw_fw2-fnct-res-2wrpr-sdk-stm-stm32f7_disco-usart/wsp/cmake/v_32stm0

- dare la precedenza al livello quindi il nome principale del modulo ([0name]) è bene porlo uguale alla funzionalità
    - il nome associato al livello conterrà eventualmente
        - sub-funzionalità nel caso di [2wrpr]
        - sub-funzionalità, owner
- trdp
    - sdk
        - mac
            - mpfw_fw2-trdp-sdk-mac-0trdp
            - mpfw_fw2-trdp-sdk-mac-1trdp-usart
        - nxp
            - mpfw_fw2-trdp-sdk-nxp-0trdp
            - mpfw_fw2-trdp-sdk-nxp-1trdp-usart
        - stm
            - stm32f769_disco
                - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-0trdp
                - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-1trdp-usart

- fnct
    - res
        - mpfw_fw2-fnct-res-1trdp-sdk-stm-stm32f7_disco-usart
        - mpfw_fw2-fnct-res-1trdp-sdk-mac-usart
        - mpfw_fw2-fnct-res-1trdp-sdk-nxp-usart
        - mpfw_fw2-fnct-res-2wrpr-sdk-usart

- MODALITA' DI PARSING DEL NOME/PATH DI UN MODULO
    - modalità per type [trdp]
        - path
            - esempio
                - trdp/sdk/stm/stm32f769_disco -> <type>/<functionality>/<owner>/<functionality attributes list>
                    - standard
                        - <type>/<functionality>/<owner>
                    - optional
                        - <functionality attributes list>
        - nome
            - esempio
                - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-0trdp -> mpfx_fw2-<type>-<functionality>-<owner>-<functionality attributes list>-0trdp
                    - standard
                        - <type>/<functionality>/<owner>
                    - optional
                        - <functionality attributes list>
                - mpfw_fw2-trdp-sdk-stm-stm32f769_disco-1trdp-usart  -> mpfx_fw2-<type>-<functionality>-<owner>-<functionality attributes list>-1trdp-<level functionality attributes list>
                    - standard
                        - <type>/<functionality>/<owner>
                    - optional
                        - <functionality attributes list>
                        - <level functionality attributes list>
    - modlaità per type [fnct], [appl] & [main]
        - path
            - esempio
                - fnct/res/ -> <type>/<functionality>
                    - standard
                        - <type>/<functionality>
        - nome
            - esempio
                - mpfw_fw2-res-1trdp-sdk-stm-stm342f769_disco -> mpfx_fw2-<type>-<functionality>-1trdp-<trdp functionality>-<owner>-<trdp functionality attributes list>
                    - standard
                        - <type>/<functionality>
                    - optional
                        - <trdp functionality attributes list>
    

- nel nome dei moduli  e/o nel loro path mettere prima l'owner e poi la sub-functionality ha dei
    - pro
        - è più modulare
    - contro
        - forse (da verificare) meno pratico nella gestione del codice 
            - nel senso che ad esempio è più "semplice" durante l'implementazione avere gli sdk tutti in una stessa directory
            - invece che andarli a ricercare i directory diverse

- struttura delle directroy dei mdouli
    - schema 1 - più semplice per i moduli al livello 0 e livello 1, questi non dovranno gestire la piattaforma ed in generale moduli [trdp]
        - mpfw_fw2-...
            - build
            - build_main
            - src
            - wsp
                - c_<configruazine del codice sorgente>
                - v_<name version>
                    - cmake
                    - stm
                        - stm32f769_disco
                    - nxp
                        - lpc54608
                        - lpc54628
    - schema 2 - più complesso per i moduli a livello superiore al primo, questi dovranno gestire la piattaforma ed in generale moduli [trdp]
        - mpfw_fw2-...
            - common
                - build
                - build_main
                - src
                - wsp
                    - c_<configruazine del codice sorgente>
                    - v_<name version>
                        - cmake
                            - init
                            - CMakeLists.txt
                        - stm
                            - stm32f769_disco
            - trdp
                - <owner>, i.e. stm
                    - <sub-functionality>, i.e. sdk
                        - stm32f769_disco
                            - src
                            - wsp
                                - c_<configruazine del codice sorgente>
                                - v_<name version>
                                    - cmake
                                    - stm
                                        - stm32f769_disco


---

Thursday, 14th August 2025

- sideve ricavare l'owner dei trdp

- ottenere la lista dei  moduli [trdp] con i loro proprietari e relative funzionalità (i.e. sdk) e sub-funzionalità (i.e. sdk/usart)
    - FNCT_LIST
        -


- quali sono i dati/parametri che si devono ricavare dal paresing del nome di un modulo?
    - <type>                            : there four (4) type
        - [main], [appl], [fnct]/[libs] & [trdp]
    - <module name>                     : it becomes the [application] functionality name in case of "fnct" type while the [trdp] functionality name in case of [trdp] type
        - i.e.: [core], [res], etc.
    - <layer>                           : every module can have some or all of the following layers; there are seven (7) layer; some layer, as i.e. [2wrpr] or [1trdp], can have more than one "instance"
                                          in this cases the layer name will have an extension that will specify the sub-functionality; typically sub-functionality refers to [trdp] modules;
                                          [trdp] modules have: (1) owner, (2) functionality & (3) sub-functionality
                                          
        - [5main], [4appl], [4test], [3real], [2wrpr], [1trdp] & [0abst]/[0trdp]
    - <layer functionality name>        : there is a standard layer functionality and these one are typically [2wrpr] or [1trdp] functionalities
                                          these modules can be subordinate to a higher level application functionality and located with the other layer of this functionality
                                            i.e.:   mpfw_fw2-fnct-res-2wrpr-sdk (the [trdp] owner is not specified in the name because it is used inside the module to differentiate it from the other functionalities that belong to other owners)
                                          or it can be a general [trdp] functionality, used by more than one application functionality, in this case it is located in the [trdp] functionality directory with the [0bast] layer
                                            i.e.:   mpfw_fw2-trdp-sdk_stm32f769_disco-1trdp-sdk
                                                    or 
                                                    mpfw_fw2-trdp-sdk_stm32f769_disco-1trdp-sdk-usart
        - [trdp_sdk], 
        - [trdp_file_system] & [trdp_ethernet]
    - <owner layer functionality name>  : 

- ci sono due tipologie di librerie
    - principali
        - quelle cha hanno il file [CMakeLists.txt]
    - subordinate
        - tipicamente aggiunte realtive
            - alla piattaforma
            - o più in generale al software di terze parti
        - hanno le directory [src] e [wsp], certamente la esp opzionale la src, ma il wsp non contiene il file [CMakeLists.txt] e quindi non si possono compilare
            - questo accade nel caso ci sia una dipendenza reciproca tra il codice comune ed il codice specifico
            - in caso contrario si può creare una libreria
        - devono essere installate ovvero copiate in precise locazioni nel modulo di cui sono una "dipendenza"
- gestire le funzionalità dell'applicazione come si gestiscono le piattaforme
    - nel senso che per agiungere delle funzionalità basta mettere un parametro quando si chiama il comando cmake di build
        - da capire se fattibile

---

Wednesday, 13th August 2025

- iniziare a rivedere tutti i nomi dei moduli

- schemi di directories
    - attuale
        - schema [multi_layer]
            - in un unico modulo vengono riuniti più layer
                - pro
                    - si ha un solo CMakeLists.txt per più layer
                    - gestione più semplice in fase di sviluppo del codice sorgente
                - contro
                    - gestione un po' più complessa in fase di configurazione di build
                - applicabile: non si possono unire layer senza piattaforma [4appl]/[3real] con quelli con piattaforma [5main]/[2wrpr]
        - schemi [single_layer]
            - un modulo gestisce un solo layer
            - pro
                - molto modulare 
                - a livello di architettura dell'applifcazione permette una maggiore flessibilità 
            - contro
                - per ogni strato si ha un CMakeLists.txt
                - a livello di architettura dell'applifcazione la configurazione delle dipendenze diventa più complessa
                    - si deve star dietro a più moduli con le rispettive versioni
            - schema [4appl]/[3real]
                - non gestisce le piataforme
                - non fa nessun riferimento diretto alle funzioni contenute in un qualunque layer [trdp]
                    - ma usa solo i wrapper [wrpr]
                        - questo permette di lasciare il modulo inalterato cambiando la configurazione [trdp]
            - schema [0abst]
                - è indipendente 
            - schema [5main]/[2wrpr]
                - gestisce le piattaforme
                - pro
                    - maggiore flessibilità nella gestione delle piattaforme
                        - che forse non è neanche necessaria
                - contro
                    - per ogni piattaforma c'è un CMakeLists.txt
    - aggiornato
        - politiche generali
            - tutti i moduli gestiscono un solo layer
                - pro
                    - più flessibile a livello di architettura dell'applicvazione
                    - minore complessita nel codice cmake di congigurazione di build
                - contro
                    - maggiore complessityà nella gestione delle dipendnze
                    - maggore laboriosità nella gestione del codice sorgente dell'applicazione dovendo suddividerlo in più moduli e quindi avere più [wsp]
        - schema [abst]
        - schema [trdp]
            - (se) si pensa che venga sviluppato dal proprietario del software [trdp]
                - quindi
                    - non ci sarà nessuna parte comune e neppure altri [trdp]/[sdk]
                    - infatti
                        - non ha senso ad esempio gestirte più [sdk] diversi insieme
                    - ci saranno due layer
                        - layer [0abst] quello dell'[sdk] "base" fornito dal produttore del [trdp]/[sdk]
                        - layer [1trdp]
                            - aggiorna o modifica il suo layer [0abst]
                            - fa riferimento/usa ad altre funzionalità delle librerie [mpfw]
                                - ecco il motivo di un layer [1trdp] altrimenti sarebbe un layer [0abst]
                            - tipicamente sviluppato dal proprietario dell'applicazione nel caso abbia a disposizione i sorgenti del [trdp]/[sdk]
            - (se invece) si pensa che venga sviluppato dal proprietario dell'applicazione che ha i sorgenti del codice [trdp]
                - nel caso, abbastanza probabile, che questo modulo si associato ad un modulo [wrpr] si potranno avere più sotto-moduli ognuno per ogni proprietario del modulo [trdp]
                    - un esempio di questo caso èp
                        - aggiornamento delle funzioni [USART] dell'[sdk]
                    - in questo caso si avranno comunque tanti CMakeLists.txt quanti i proprietari del [trdp]/[sdk]
                - adesso mi chiedo:
                    - ma ha senso fare questa cosa?
                        - non è meglio avere due moduli ben separati?
                            - credo proprio di si
                - impostazione di nomi
                    - fnct
                        - res
                            - layer
                                - fnct_res_2wrpr_sdk
                                - fnct_res_1trdp_sdk_mac
                                - fnct_res_1trdp_sdk_nxp
                                - fnct_res_1trdp_sdk_stm32f769_disco
                - ci sono funzionalità dell'applicazione [appl_fnct] 
                    - sono implementate dal proprietario dell'applicazione
                - e funzionalità di terze parti 
                    - ad esempio
                        - [trdp_sdk]
                        - [trdp_file_system]
                        - [trdp_ethernet]
                        - [trdp_usb]
                    - sono implementate dal proprietario del software di terze parti
        - schema [wrpr]
            - si pensa che venga sviluppato dal proprietaro dell'applicazione, quindi dall'utilizzatore dei software [trdp]
                - infatti
                    - è il proprietario dell'applicazione che decide come impostare, in particolare quale interfaccia usare tra i livelli/layer più alti ed il livello [1trdp], l'implementazione dei sorgenti del layer [wrpr]
                - quindi
                    - ci sarà una parte comune nella quale sarà posizionato il file CMakeLists.txt
            - fa riferimento ad una sola tipologia di [trdp]
        - schema [ownr]
            - come il precedente [wrpr] ma più generale
                - avrà una parte comune
                - potrà non avere tutti i [trdp]/[sdk]
                - potrà avere più tipologie di [trdp] ad esempio [sdk], [file_system], [ethernet_protocol], etc.

- come comporre il nome di un modulo
    - deve essere presente
        - la tipologia
        - nome della funzionalità
        - il layer
        - nel caso di layer [2wrpr] si deve specificare anche a quale [trdp] si riferisce
- quindi come eseguirne il parsing
    - mpfw_fw2_<type>_<name about type = application functionality name if type = "fnct">_<layer>_<layer functionality name; i.e.: sdk>_<owner layer functionality name; i.e.: stm32f769_disco>
    - mpfw_fw2_[appl]_[20250813]_[4appl]
    - mpfw_fw2_[fnct]_[res]_[1trdp]_[sdk]_[mac]
    - mpfw_fw2-<type>-<name about type>-<layer>-<functionality name>-<functionality owner name>
    - mpfw_fw2-[appl]-[20250813]-[4appl]
    - mpfw_fw2-[fnct]-[res]-[1trdp]-[sdk]-[mac]
- caratteri separatori tra le parti del nome di un modulo
    - "_": può essere usato all'interno dei nomi; ad esempio: stm32f769_disco; quindi è meglio evitare
    - "-": qualche problemino potrebbe crearlo: da evitare come carattere inziale perche può essere interpretato in linux come parametro all'interno di un comando shell
        - dal momento che viene utilizzato in linux per i nomi dei pacchetti, ad esempio, direi che si potrebbe optare per questa scelta
    - ".": naturalmente da non usare all'inzio del file; forse nella fase di parsing può causare qualche problemino, da verificare
    - "~": usasto da windows con un significato particolare, meglio evitare per essere sicuri

- git ed il carattere "-" nel nome dei files
    - sembra non ci sia nessun problema quindi direi di procedere con il carattere "-" (hypen)
 
- <type>                            : there four (4) type
    - [main], [appl], [fnct] & [trdp]
- <name about type>                 : there are a lot of type
    - i.e.: [core], [res], etc.
- <layer>                           : there are seven (7) standard layer but there can be others
    - [5main], [4appl], [4test], [3real], [2wrpr], [1trdp] & [0abst]
- <layer functionality name>        : there is a standard layer functionality and these one are typically [2wrpr] or [1trdp] functionalities
                                      these modules can be subordinate to a higher level application functionality and located with the other layer of the functionality or it can be a general [trdp] functionality, useed by more than one application functionality, in this case it is located 
    - [trdp_sdk], 
    - [trdp_file_system] & [trdp_ethernet]
- <owner layer functionality name>  : 

- trdp <type>
    - stm <trdp owner>
        - sdk <functionality>
            - stm32f769_disco <functionality specification>
                - mpfw_fw2-trdp-sdk_stm32f769_disco-0abst
                - mpfw_fw2-trdp-sdk_stm32f769_disco-1trdp-usart <usart sub-functionality>
- oppure
- trdp <type>
    - stm <trdp owner>
        - sdk_stm32f769_disco <functionality> (N.B.: the name has to contain some ref to the owner to make it different from other same functionality of other owners)
            - mpfw_fw2-trdp-sdk_stm32f769_disco-0abst
            - mpfw_fw2-trdp-sdk_stm32f769_disco-1trdp-usart <usart is a sub-functionality>
- fnct
    - res
        - mpfw_fw2-fnct-res-2wrpr-sdk_stm32f769_disco-usart

---

Tuesday, 12th August 2025

- cose da fare
    - gestire i file di configurazione dipendenti dal software di terze parti e quindi anche dall'sdk
        - aggiornare la procedura di controllo della versione del codice cmake da eseguire all'inzio
    - gestione dei messaggi di debug in cmake

- gestione software di terze parti [trdp]
    - l'impostazione dei [trdp] e tra questi naturalmente la piattaforma viene fatta usando i parametri di [build]
        - però i moduli devono sapere quali [trdp] gestire
            - in quest'ottica ci deve essere una lista che definisce quali sono i [trdp] da gestire
                - questa lita dovrebbe essere definita a livello di applicazione [4appl]
                    - il livello [5main] non deve definire questa lista ma la leggerà dal livello sottostante
        - l'SDK ha la caratteristica di essere un [TRDP] sempre presente quindi non serve parametrizzarlo

- si deve trovare lo schema e stabilire quando applicarlo
    - capire anche quali sono gli alrri schemi per fare un po di ordine

---

Monday, 11th August 2025

- cose da fare
    - far eun controllo della configurazione dei sorgenti
        - forse non è possibile dato che viene impostata nel bash script

- organizzare il codice
    - influenza l'implementazione del codice perche pone dei vincoli
        - certe cose devono essere fatte in un certo modo e non in altri
- implementare il codice
- gestione dei file di configurazione presenti nei moduli di terze parti/platform
    - se questi file dipendono dall'applicazione dovranno essere inserite nel modulo di tipologia [appl]
        - ma a quale livello?
            - forse e in teoria, i file di configurazione 
                - non dovrebbero fare riferimento a files [#include]/[.h] dipendenti dal codice di terze parti
                - dovrebbero contenere solo le impostazioni delle [#define] dhe definiscono il codice da compilare o il valore iniziale/di default di varaibili
                - si dovrebbero trovare al livello 0 nel senso che non sono al corrente della presenza di alcun file
                    - i file di configurazione hanno la caratteristica, dal punto di vista delle dipendenze, di elemento terminatore, 
                        - tutti gli altri file del codice di terze parti lo vedono 
                        - mentre lui non vede "sotto" (nel senso della sequeza delle dipendenze) nessun file eccetto altri possibili file di configurazione
                - in questi casi i file di configurazione possono essere inseriti in moduli di livello 3 come il [3real] o livello di livello 4 come [4appl] o [4test]
                - ad esempio il file di configurazione del freertos [FreeRTOSConfig.h] rispetta queste condizioni
                - questa proprietà che dovrebbero avere i files di configureazione permetterebbe di evitare i poco ortodossi loop nella sequena delle dipendenze dei file [.h] di una libreria
                - tuttavia
                    - i file di configurazione
                        - [sdk_uart_conf.h]
                        - [stm32f7xx_hal_conf.h]
                        - non rispettano questa regola
                - comunque
                    - trattandosi solo di file header direi che si possono inserire in moduli di livello 3 e 4 nel caso non ci sia il modulo wrapper di livello 2 [2wrpr] per il modulo [appl] o [fnct]




---

Sunday, 10th August 2025

- gestione dei file di configurazione speciifica per la piattaforma all'interno di moduli indipendenti dalla piattaforma come il livello [3real]
- c'è del codice che viene eseguito per tutte le piattaforme (codice indipendente dalla piattaforma -> codice wrapper per tutte le piattaforme) 
    - ed altro codice eseguito solo per specifiche piattaforme (codice indipendente dalla piattaforma -> codice wrapper solo per specifiche piattaforme)
- per il primo si devono avere i wrapper per ogni piattaforma
    - per il secondo solo per le specifiche piattaforme
- anche per i moduli indipendenti dalla piattaforma in modo indiretto come il livello [3real] si dovrebbe avere la suddivisione tra [common] e [platform]
    - il CMakeLists.txt rimarrebbe nel [common]
    - però si devono crere le due directory [common] e [platform]
- c'è poi anche la questione delle dipendenze che possono essere differenti a seconda della piataforma/codice di terze parti
- NON SI DEVE RAGIONARE IN TERMINI DI [PIATTAFORMA]  MA IN TERMINI DI [SOFTWARE_DI_TERZE_PARTI] 
    - la piattaforma è un caso particolare se pur il più importante
- POLITICHE DI ORGANIZZAZIONE DEL CODICE DA SEGUIRE:
    - non si deve mischiare il codice comune con quello di terze parti
        - quindi si devono creare le directory [common] e [trdp]/[patform], [trdp]/[file_system], etc.
- NOTARE che se il codice presente nelle directory [trdp] non fa chiamate al codice [common] le si possono racchiudere in librerie

---

Saturday, 9th August 2025


 
---

Friday, 8th August 2025

- cose da fare
    - verificare la procedura auot-gen anche per le piattaforme nxp e stm
    - verificare la procedura di init per la riduzione dei file di configurazione per tutti 
    - iniziare a vedere di come unificare le due versioni del codice
        - in particolare riscrivere il modulo rsSerial pe renderlo compatibile con la nuova gestione dell'hw
    - VERIFICARE LA SIMULAZIONE  della vecchia applicazione 20230810 la cui copia dovrebbe essere l'applicazione vecchia 20240619 (da non confondere con quella nuov che appunto deve essere testata)


---

Thursday, 7th August 2025

- step da seguire
    - aggiornare il nome della #define dei service task
    - aggiornare lo script [get_deps_list] per gestire la ricerca dei task in base al servizio selezionato
        - si deve inserire un altro parametro in ingresso che sarà il nome del servizio i cui task si vogliono ricercare
 

---

Wednesday, 6th August 2025

- c'è una situazione che aggiungendo un nuovo task non viene ricreata la tabella
    - questo accade se il nuovo task è definito in una classe in cui non era definito nessn task
        - in questo caso verrà ricompilato  il solo file modificato e non  aggiornata la tabella dei task
            - in questo caso si deve ripetere la procedura di configurazione manualmente non viene fatta in automatico
- se un task viene aggiunto forse si dovrebbe rieseguire la fase di configurazione altrimenti quel task non viuene aggiunto alla sua tabella
    - questo accade perche la procedura di ricerca dei task usa il [process_execution] statement/command che non viene eseguito in fase di build
- la procedura per gestire la lista dei service è quella di ottenere prima la lista dei services
    - e poi per ciascun service ottenere la lista dei task

- creazione automatica delle variabili
    - CPP_<service>_TBL_TEMPLATE
    - CPP_<service>_TBL
    - CPP_<service>_TBL_TEMPLATE_FROM_BUILD
    - CPP_<service>_TBL_FROM_BUILD
- selezionare tutti i file [*Tbl_template.cpp]
    - ciascun di questi file contiene tutte le informazioni per ottenere le variabili di cui sopra
        - si ricava 
            - il nome del servizio
            - il path del file tb_template.cpp
                - necessario nella creazione del file [*Tbl.cpp]
            - il path relativo della folder che contiene il file di cui sopra
                - necessario per determinare la locazione dove creare il file [*Tbl.cpp]


/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/src/auto_gen/tb/kr/krInitStatic/v_01/krInitStaticTbl.cpp;
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/src/auto_gen/tb/kr/krTimer/v_04/krTimerTbl.cpp;
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/src/auto_gen/tb/sv/svStateMachine/v_04/svStateMachineTbl.cpp;
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/src/auto_gen/tb/kr/krThread/v_05/krThreadTbl.cpp


---

Tuesday, 5th August 2025

- gestione dei file autogenerati relativi alle tabelle dei servizi
    - inserire i file template nei proprietari dei servizi
    - le tabelle verranno definite nel main e per ciascuna piattaforma dal momento che certamente la lista dei task sarò differente tra le piattaforme in particolare tra quelle reali e quelle virtuali
        - la versione di questi file autogenerati sarà la stessa di quella dei template
    - implementazione
        - nell'immediato
            - implementare i due punti pecedenti per un solo servizio
        - nell'immediato dopo
            - eseguire il loop dei servizi
                - definire la matrice dei servizi
                    - stabilire dove localizzarla
                        - eventualmente la si potrebbe ricavare
                            - usare lo stesso metodo usato per ricercare i task e autogenerare i file [tbl]
                    - stabilire i campi che ciascun recors/servizio dovrà avere

---

Monday, 4th August 2025

        ## determine module names
            string(REGEX MATCHALL "[^/]+/" OCCURENCES_LIST ${SUBSTRING_current_source_RPATH} )
            message("DEBUG - STEP 0 - OCCURENCES_LIST: ${OCCURENCES_LIST}")

            set(MPFW_CODE_DIR "..")
            set(MPFW_CODE_DIR_LEVEL 1 )
            foreach(item IN LISTS OCCURENCES_LIST)
                if(NOT item STREQUAL "/")
                    set(MPFW_CODE_DIR "${MPFW_CODE_DIR}/.." )
                    math(EXPR MPFW_CODE_DIR_LEVEL "${MPFW_CODE_DIR_LEVEL}+1")
                endif()
            endforeach()

- solo i moduli con layer possono avere anche la piattaforma
    - si pensi ai livelli 2wrpr, 1trdp_sdk e 5main che la hanno
    - ci sono pero livelli che non la hanno il ilvello 0abst e i livelli  3real, 4appl

..........................

work@umtiefs-Mac-mini v_11main % build_platform_cmake.sh mac
CMake Warning at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:42 (message):
  CMAKE_CURRENT_SOURCE_DIR:
  /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


DEBUG - STEP 0 - SUBSTRING_mpfw_code_POS: 72
DEBUG - STEP 0 - STRING_current_source_dir_LENGTH: 159
DEBUG - STEP 0 - SUBSTRING_current_source_RPATH: /main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
DEBUG - STEP 0 - OCCURENCES_LIST: /;main/;app20240619/;layer/;mpfw_fw2_main_app20240619_5main/;platform/;mac/;wsp/;cmake/
DEBUG - STEP 0 - MPFW_CODE_DIR: ../../../../../../../../..
CMake Warning at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:68 (message):
  DEBUG - STEP 0 - MPFW_CODE_DIR: ../../../../../../../../..  IS CORRECT
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


DEBUG - STEP 0 - OCCURENCES_LIST: ../;../;../;build/
DEBUG - STEP 0 - STEP_FOLDER_COUNTER: -1
DEBUG - STEP 0 - MPFW_CODE_DIR_FROM_BUILD_LEVEL: 8
DEBUG - STEP 0 - MPFW_CODE_DIR_FROM_BUILD: ../../../../../../../..
DEBUG - STEP 0 - OCCURENCES_LIST: ;main;app20240619;layer;mpfw_fw2_main_app20240619_5main;platform;mac;wsp;cmake;v_11main
DEBUG - STEP 0 - layer has been found - break
DEBUG - STEP 0 - item: mpfw_fw2_main_app20240619_5main -> item_state: STATE_LAYER 
DEBUG - STEP 0 - item: platform -> item_state: STATE_PLATFORM 
DEBUG - STEP 0 - item: mac -> item_state: STATE_PLATFORM_OK 
DEBUG - STEP 0 - item: wsp -> item_state: STATE_CHECK_WSP_FOLDER 
DEBUG - STEP 0 - TEST_MODULE_TYPE:         main
DEBUG - STEP 0 - TEST_MODULE_RPATH:        main
DEBUG - STEP 0 - TEST_MODULE_0NAME:        app20240619
DEBUG - STEP 0 - TEST_MODULE_LAYER:        5main
DEBUG - STEP 0 - TEST_MODULE_PLATFORM:     mac
DEBUG - STEP 0 - TEST_MODULE_NAME:                 MAIN_APP20240619_5MAIN
DEBUG - STEP 0 - MAIN_APP20240619_5MAIN_TYPE_UP:      MAIN
DEBUG - STEP 0 - MAIN_APP20240619_5MAIN_RPATH:        main
DEBUG - STEP 0 - MAIN_APP20240619_5MAIN_0NAME_UP:     APP20240619
DEBUG - STEP 0 - MAIN_APP20240619_5MAIN_LAYER_UP:     5MAIN
DEBUG - STEP 0 - MAIN_APP20240619_5MAIN_PLATFORM:     mac
CMake Error at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:252 (message):
  DEBUG - STEP 0 - MPFW_CODE_DIR is not set
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


-- Configuring incomplete, errors occurred!

"mac" platform selected
MPFW_CODE_CMAKE_DIR:      /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01
PLATFORM_NAME:    mac
SRC_CFG:          38
PATH:             /Users/work/.cabal/bin:/Users/work/.ghcup/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Applications/Little Snitch.app/Contents/Components:/Applications/VMware Fusion.app/Contents/Public:/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/scrp:/Users/work/Applications/CMake.app/Contents/bin

PWD:              /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
work@umtiefs-Mac-mini v_11main % build_platform_cmake.sh mac
CMake Warning at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:42 (message):
  CMAKE_CURRENT_SOURCE_DIR:
  /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


DEBUG - STEP 0 - SUBSTRING_mpfw_code_POS: 72
DEBUG - STEP 0 - STRING_current_source_dir_LENGTH: 159
DEBUG - STEP 0 - SUBSTRING_current_source_RPATH: /main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
DEBUG - STEP 0 - OCCURENCES_LIST: /;main/;app20240619/;layer/;mpfw_fw2_main_app20240619_5main/;platform/;mac/;wsp/;cmake/
DEBUG - STEP 0 - MPFW_CODE_DIR: ../../../../../../../../..
CMake Warning at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:68 (message):
  DEBUG - STEP 0 - MPFW_CODE_DIR: ../../../../../../../../..  IS CORRECT
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


DEBUG - STEP 0 - OCCURENCES_LIST: ../;../;../;build/
DEBUG - STEP 0 - STEP_FOLDER_COUNTER: -1
DEBUG - STEP 0 - MPFW_CODE_DIR_FROM_BUILD_LEVEL: 8
DEBUG - STEP 0 - MPFW_CODE_DIR_FROM_BUILD: ../../../../../../../..
DEBUG - STEP 0 - OCCURENCES_LIST: ;fnct;abcd;efgh;base;mpfw_fw2_fnct_base;wsp;cmake;v_00base
DEBUG - STEP 0 - TEST_MODULE_TYPE:         fnct
DEBUG - STEP 0 - TEST_MODULE_RPATH:        fnct/abcd/efgh
DEBUG - STEP 0 - TEST_MODULE_0NAME:        base
DEBUG - STEP 0 - TEST_MODULE_LAYER:        
DEBUG - STEP 0 - TEST_MODULE_PLATFORM:     
DEBUG - STEP 0 - TEST_MODULE_NAME:                 FNCT_BASE
DEBUG - STEP 0 - FNCT_BASE_TYPE_UP:      FNCT
DEBUG - STEP 0 - FNCT_BASE_RPATH:        fnct/abcd/efgh
DEBUG - STEP 0 - FNCT_BASE_0NAME_UP:     BASE
DEBUG - STEP 0 - FNCT_BASE_LAYER_UP:     
DEBUG - STEP 0 - FNCT_BASE_PLATFORM:     
CMake Error at /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01/CMakeLists_steps/init_step_0.cmake:252 (message):
  DEBUG - STEP 0 - MPFW_CODE_DIR is not set
Call Stack (most recent call first):
  CMakeLists.txt:37 (include)


-- Configuring incomplete, errors occurred!

"mac" platform selected
MPFW_CODE_CMAKE_DIR:      /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/cmake/mpfw_fw2_cmake/v_01
PLATFORM_NAME:    mac
SRC_CFG:          38
PATH:             /Users/work/.cabal/bin:/Users/work/.ghcup/bin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Applications/Little Snitch.app/Contents/Components:/Applications/VMware Fusion.app/Contents/Public:/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/scrp:/Users/work/Applications/CMake.app/Contents/bin

PWD:              /Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main
work@umtiefs-Mac-mini v_11main % build_platform_cmake.sh mac

..........................

---

Sunday, 3rd August 2025

- cose da fare
    - spostare il [tbl_template.cpp] nei moduli proprietari
    - spostare i [tbl.cpp] nel modulo [main/platform], adesso sono in [main/common]
    - aggiungere alle dipendenze del [add_custom_command] i file [tbl_template]
    - usare [execution_process] per eliminare i file [set_module_names.cmake] e [set_root_dir,cmake] e ottenere la variabile [MPFW_CODE_CMAKE_DIR]
    - ottenere la versione del wsp in modo automatico e con lunghjezza variabile e non fissa a 6 caratteri come adesso

##     set(MAIN_APP20240619_5MAIN_TYPE_UP          MAIN        )
##     set(MAIN_APP20240619_5MAIN_LAYER_UP         5MAIN       )
##     set(MAIN_APP20240619_5MAIN_0NAME_UP         APP20240619 )
##     set(MAIN_APP20240619_5MAIN_RPATH            main        ) 
##     set(MAIN_APP20240619_5MAIN_PLATFORM         mac         )

## macro(set_modules_names_macro MOD_NAME)
##     include(${MPFW_CODE_DIR}/${${MOD_NAME}_INIT_RURL}/set_module_names.cmake)
##     ## name_up / name_lw
##         set(name_up     ${${MOD_NAME}_0NAME_UP} )
##         string(TOLOWER  ${name_up}  name_lw)
##         message("DEBUG - set_modules_names_macro - name_up/name_lw:     ${name_up}/${name_lw}")
##     ## name_layer_up
##         set(name_layer_up        ${name_up} )
##         if(${MOD_NAME}_LAYER_UP)
##             set(name_layer_up        ${name_up}_${${MOD_NAME}_LAYER_UP} )
##         endif()
##         message("DEBUG - set_modules_names_macro - name_layer_up:       ${name_layer_up}")
##     ## type_name_up
##         set(type_name_up         ${${MOD_NAME}_TYPE_UP}_${name_layer_up} )
##         message("DEBUG - set_modules_names_macro - type_name_up:        ${type_name_up}")
##     ## complete_name_lw
##         string(TOLOWER  ${MODULE_PREFIX_UP}_${type_name_up}  complete_name_lw)
##         message("DEBUG - set_modules_names_macro - complete_name_lw:    ${complete_name_lw}")
##     ## rpath_mod
##         set(rpath_mod            ${${MOD_NAME}_RPATH} )
##         message("DEBUG - set_modules_names_macro - rpath_mod:           ${rpath_mod}")
## 
## endmacro()


##    if(${type_name_up}_LAYER_UP)
##        set(${type_name_up}_ROOT_RPATH              ${rpath_mod}/${name_lw}/layer/${complete_name_lw} )
##    else()
##        set(${type_name_up}_ROOT_RPATH              ${rpath_mod}/${name_lw}/${complete_name_lw} )
##        set(${type_name_up}_0ABST_ROOT_RPATH        ${${type_name_up}_ROOT_RPATH}/layer/0abst )
##        set(${type_name_up}_4APPL_ROOT_RPATH        ${${type_name_up}_ROOT_RPATH}/layer/4appl )
##    endif()

- tra il [main] e il [nome] si ottiene il percorso [rpath]
    - dal nome del modulo mpfw_fw2_<type>_<name>_<layer>

---

Friday, 1st August 2025

- i file auto-generati possono essere insieriti in ununico punto e fose conviene inserirli nella sotto directory dipendente dalla piattaforma perche i task possono esseere differenti a seconda della piattaforma
    - creare una macro per creare la lista dei file auto-generati da compilare 
    - compilare il file [auto_generated_files.cmake]
        - con la lista dei servizi di cui ricercare i task e creare i rispettivi file tbl
    - i file include non è necessario definirli


COMMAND cat "${CPP_INIT_STATIC_TBL_TEMPLATE_FROM_BUILD}" | ${MPFW_CODE_DIR_FROM_BUILD}/cmake/mpfw_fw2_cmake/v_01/scripts/create_tbl_cpp.sh "${task_include}" "${task_define}" > "${CPP_INIT_STATIC_TBL_FROM_BUILD}"

COMMAND cat "${CPP_INIT_STATIC_TBL_TEMPLATE_FROM_BUILD}" | ${MPFW_CODE_DIR_FROM_BUILD}/cmake/mpfw_fw2_cmake/v_01/scripts/create_tbl_cpp.sh "${task_include}" "${task_define}" > "${CPP_INIT_STATIC_TBL_FROM_BUILD}"

COMMAND ${MPFW_CODE_DIR}/cmake/mpfw_fw2_cmake/v_01/scripts/get_deps_list.sh "${${MODULE_NAME}_SOURCE_FILES_H_WDEP}" |  ${MPFW_CODE_DIR_FROM_BUILD}/cmake/mpfw_fw2_cmake/v_01/scripts/create_tbl_cpp.sh "${CPP_INIT_STATIC_TBL_TEMPLATE_FROM_BUILD}" | > "${CPP_INIT_STATIC_TBL_FROM_BUILD}"
COMMAND ${get_deps_list_CMD} "${${MODULE_NAME}_SOURCE_FILES_H_WDEP}" |  ${create_tbl_cpp_CMD} "${CPP_INIT_STATIC_TBL_TEMPLATE_FROM_BUILD}" | > "${CPP_INIT_STATIC_TBL_FROM_BUILD}"

........ sezione [get_deps_list] / configuring ste3p .........


    ## questa variabile verrà definita nel file [auto_generated_files.cmake] verrà impostata dall'utilizzatore
    SERVICE_TASK_MATRIX

        set(SERVICE_TASK_LIST   )
        set(item_id 0 )
        foreach(item IN LISTS SERVICE_TASK_MATRIX)
            math(EXPR COL_LIST "${item_id} % 3")

            if(COL_LIST EQUAL 0)
                set(service_name            ${item} )
                set(SERVICE_TASK_LIST       ${SERVICE_TASK_LIST} ${item} )
            endif()
            if(COL_LIST EQUAL 1)
                set(SERVICE_${service_name}_RPATH           ${item} )
            endif()
            if(COL_LIST EQUAL 2)
                set(SERVICE_${service_name}_MODULE_NAME     ${item} )

                set(${SERVICE_${service_name}_OWNER}_SRC_DIR_FROM_BUILD        ${MPFW_CODE_DIR_FROM_BUILD}/${SERVICE_${service_name}_OWNER}_SRC_RPATH) )

                set(CPP_${service}_TBL_PARTIAL_NAME             ${SERVICE_${service_name}_RPATH}/${SERVICE_${service_name}_MODULE_NAME}/${SERVICE_${service_name}_MODULE_NAME}Tbl    )

                set(CPP_${service}_TBL_TEMPLATE                 ${MODULE_NAME}_SRC_DIR)/${CPP_${service}_TBL_PARTIAL_NAME}_template.cpp    )
                set(CPP_${service}_TBL_TEMPLATE_FROM_BUILD      ${MODULE_NAME}_SRC_DIR_FROM_BUILD)/${CPP_${service}_TBL_PARTIAL_NAME}_template.cpp    )
                set(CPP_${service}_TBL                          ${MODULE_NAME}_SRC_DIR)/${CPP_${service}_TBL_PARTIAL_NAME}.cpp    )
                set(CPP_${service}_TBL_FROM_BUILD               ${MODULE_NAME}_SRC_DIR_FROM_BUILD)/${CPP_${service}_TBL_PARTIAL_NAME}.cpp    )

            endif()

            math(EXPR item_id "${item_id} + 1")

        endforeach()


    COMMAND_get_deps_list       ${MPFW_CODE_CMAKE_DIR}/scripts/get_deps_list.sh
    COMMAND_create_tbl_cpp      ${MPFW_CODE_CMAKE_DIR}/scripts/create_tbl_cpp.sh

    COMMAND_create_tbl_cpp_FROM_BUILD      ${MPFW_CODE_CMAKE_DIR_FROM_BUILD}/scripts/create_tbl_cpp.sh

    if(NOT EXISTS ${COMMAND_get_deps_list)
        message(FATAL_ERROR "The \"${COMMAND_get_deps_list}\" script file does not exist or is not recognized")
    else()
        message("DEBUG - auto-generate procedure - OK - The \"${COMMAND_get_deps_list}\" file exists")

        foreach(item IN LISTS SERVICE_TASK_LIST)

            set(SERVICE_${service}_MODULE_NAME     ${service} )
            execute_process(
                COMMAND     ${COMMAND_get_deps_list} ${service} "${${MODULE_NAME}_SOURCE_FILES_H_WDEP}"
                OUTPUT_VARIABLE     get_deps_list_${service}_output
                RESULT_VARIABLE     get_deps_list_result
            )

            set(task_${service}_desps       )
            set(task_${service}_include     )
            set(task_${service}_define      )
            set(task_${service}_pointer     )
            set(item_id 0)
            foreach(item IN LISTS get_deps_list_${item}_output)
                math(EXPR COL_LIST "${item_id} % 4")
                string(STRIP ${item} item)
                if(COL_LIST EQUAL 0)
                    set(task_${service}_desps          ${task_${service}_desps} ${item})
                endif()
                if(COL_LIST EQUAL 1)
                    set(task_${service}_include        ${task_${service}_include} ${item})
                endif()
                if(COL_LIST EQUAL 2)
                    set(task_${service}_define         ${task_${service}_define} ${item})
                endif()
                if(COL_LIST EQUAL 3)
                    set(task_${service}_pointer        ${task_${service}_pointer} ${item})
                endif()
        
                math(EXPR item_id "${item_id} + 1")
            endforeach()

            execute_process(
                COMMAND     ${COMMAND_create_tbl_cpp} "${task_${service}_include}" "${task_${service}_define}"
                INPUT_FILE          "${CPP_${service}_TBL_TEMPLATE}"
                OUTPUT_FILE         "${CPP_${service}_TBL}"
                RESULT_VARIABLE     create_tbl_cpp_result
            )

            add_custom_command(
                OUTPUT ${CPP_${service}_TBL_FROM_BUILD}
                COMMENT "Creating ${CPP_${service}_TBL_FROM_BUILD} file ..."

                COMMAND cat "${CPP_${service}_TBL_TEMPLATE_FROM_BUILD}" | ${COMMAND_create_tbl_cpp_FROM_BUILD} "${task_${service}_include}" "${task_${service}_define}" > "${CPP_${service}_TBL_FROM_BUILD}"

                ## sembrerebbe che la directory di riferimento sia quella del wsp (dove presente il file CMakeLists.txt) e non quella di build
                DEPENDS ${COMMAND_get_deps_list}  ${COMMAND_create_tbl_cpp} "${CPP_INIT_STATIC_TBL_TEMPLATE_FROM_BUILD}" ${task_${service}_deps}
                VERBATIM

            )

        endforeach()
    endif()

..........................................

........ sezione [create_tbl_cpp] / building steps ([compling_linking]) .........


..........................................

---

Thursday, 31st July 2025

- gestione dei sorgenti indipendenti dalla piattaforma ma da compilare solo per specifiche piattafortme
    - si possono scegliere due modlaità
        - 1. modalità semplice e veloce ma non modulare
            - adatta per includere nei sorgenti in modo selettivo rispetto la piattaforma pochi file
                - inserire il file cpp_files_platform/<platform name>/cpp_files.cmake
                    - i file sorgenti definiti in questo file verranno aggiunti al file cpp_files.cmake valido per tutte le piattaforme
        - 2. modalità più elaborata ma modulare
            - adatta per un insieme di file che possono essere racchiusi all'interno di una libreria
                - sviluppare una libreria
                - inserire il file set_dependecies_list_platform/<platform name>/set_dependecies_list.cmake


---

Wednesday, 30th July 2025

work@umtiefs-Mac-mini scripts % cat krInitStaticTbl_template.cpp | ./create_tbl_cpp.sh "#include \"Xtest1.h\";#include \"Xtest2.h\";#include \"Xtest3.h\";" "PTR_TASK_OF_krThread_000_task0;PTR_TASK_OF_krThread_001_task1;PTR_TASK_OF_krThread_002_task2;PTR_TASK_OF_krThread_003_task3" > krInitStaticTbl.cpp

.......

work@umtiefs-Mac-mini scripts % ( cd  ../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/mac/wsp/cmake/v_11main; ../../../../../../../../../cmake/mpfw_fw2_cmake/v_01/scripts/get_deps_list.sh  `cat ../../../../../../../../../cmake/mpfw_fw2_cmake/v_01/scripts/file_deps.txt`  )
../../../../../../../../../fnct/core/layer/mpfw_fw2_fnct_core_3real/src/kr/krTimer/v_04/krTimerManager.h; #include "krTimerManager.h"; PTR_TASK_OF_krThread_001_FNCT_CORE_3REAL_KR_TIMER_LoopUpdate; &fw2::core::core::krTimerManager::LoopUpdate; ../../../../../../../../../fnct/core/layer/mpfw_fw2_fnct_core_3real/src/kr/krTimer/v_04/krTimerManager.h; #include "krTimerManager.h"; PTR_TASK_OF_krThread_001_FNCT_CORE_3REAL_KR_TIMER_LoopCheck; &fw2::core::core::krTimerManager::LoopCheck; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/kr/krThread/v_06/ap/ap_krThread02.h; #include "ap/ap_krThread02.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_TaskTest0; &mpfw::apps::ap_krThread02::TaskTest0; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/kr/krThread/v_06/ap/ap_krThread02.h; #include "ap/ap_krThread02.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_TaskTest1; &mpfw::apps::ap_krThread02::TaskTest1; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/sv/svState/v_02/mg/tt_mg_StateManager.h; #include "mg/tt_mg_StateManager.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_tt_mg_StateManager_ThreadUnitLoop; &mpfw::apps::tt_mg_StateManager::ThreadUnitLoop; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/sv/svSync/v_05/mg/tt_mg_SyncManager_2.h; #include "mg/tt_mg_SyncManager_2.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_tt_mg_SyncManager_2_ThreadUnitLoop; &mpfw::apps::tt_mg_SyncManager_2::ThreadUnitLoop; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/sv/svSync/v_05/mg/tt_mg_SyncManager_3.h; #include "mg/tt_mg_SyncManager_3.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_tt_mg_SyncManager_3_ThreadUnitLoop; &mpfw::apps::tt_mg_SyncManager_3::ThreadUnitLoop; ../../../../../../../../../appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src/sv/svSync/v_05/mg/tt_mg_SyncManager.h; #include "mg/tt_mg_SyncManager.h"; PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_tt_mg_SyncManager_ThreadUnitLoop; &mpfw::apps::tt_mg_SyncManager::ThreadUnitLoop;
work@umtiefs-Mac-mini scripts % 

.......

re.me.nis.sen.sis

---

Tuesday, 29th July 2025

cat krThreadTbl_template.cpp | create_tbl_cpp.sh "lista include" "lista task pointer define"

---

Monday, 28th July 2025

rememimsensis

re-me-nim-sences
reminescenze
re.mi.ne.sens

grep -rnw 'appl/app20240619/mpfw_fw2_appl_app20240619/layer/4appl/src' -e 'MAKE_svState_Group

sed -i '' "s|input|ingresso|g" | head -4

---

Friday, 25th July 2025

- cose da fare
    - aggiornare la gestione della versione del codice cmake
        - eloiminare il file init/cmake_set_src_ver.cmake
        - passare come parametro di build la versione del codice cmake

- uso dell'istruzione cmake [add_custom_command]
    - il problema sta nel suo parametro [DEPENDS]
        - proprio l'esecuzione del comando darà la conoscenza di questo parametro
    - si potrebbe sdoppiare il comando in due step
        - nel primo si determina la lista delle directories dove sono presenti le definizioni dei task
        - nel secondo si determinano
            - la lista degli include
            - la lista dei task
          da inserire nel file .cpp, della tabella dei task, da compilare

...........

    set(CLEAN_FS_IMG ${CMAKE_CURRENT_BINARY_DIR}/clean-fs.img)
    add_custom_target(CleanFsImage DEPENDS ${CLEAN_FS_IMG})
    add_custom_command(
        OUTPUT ${CLEAN_FS_IMG}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/fsformat ${CLEAN_FS_IMG} 1024 ${FS_IMG_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS fsformat ${FS_IMG_FILES}
        VERBATIM
    )

...........

---

Thursday, 24th July 2025


../../../layer/4appl/src/kr/krThread/v_05/ap/ap_krThread02.h

- cose da risolvere
    - determinare la riga dove è presente una stringa
        - OK 
            - il comando seguente (opzione -n) indica anche la riga in cui sono presenti le occorrenze
                - grep -n .... ....
    - insert a string at a specific row number
        - da vedere
    - remove all text from line (a) to line (b)
        - da vedere
    - gestione degli include da inserire
        - da capire quale path debba avere il file header presente nell'istruzione di include 
            - la directory fornita dal comando grep la da rispetto la directory del workspace dove il comando di build è stato eseguito
                - forse la si può inserire così come è, sarebbe da fare delle prove
                    - non è possibile
            - the differences  in include define between "." and <.> / capire la differenza tra 
                - #include "file.h"
                - #include <file.h>
        - ci possono essere duie strade
            - 1. 
                - aggiornare la lista delle directory di include del moduilo [main] inserendo la directory [mpfw_code]
                - nel file auto-generato [...tbl.cpp] il file include avra il percorso relativo [RPATH] quindi rispetto la directory [mpfw_code]
                    - per far questo dal path del file .h si dovra eliminare la parte iniziale quella con [../]
            - le cose invece sono un po più complicate e ormai è chiaro che per non avere dubbi
                - si devono contrtollare tutte le directory della lista degli [include_file.cmake], 
                    - il problema che obbliga a seguire questa via risiede nel fatto che si hanno più versioni di uno stesso modulo
                    - la procedura quindi se volgiamo è semplice sebbene forse un po dispendiosa
                        - prendere la lista degli [include_files] di tutte le dipendenze
                            - per ogni directory controllare (non serve assolutamente, anzi da evitare, la ricerca ricorsiva) la presenza di file con la stringa "#define PTR_TASK_OF_krThread_" (PTR_TASK_OF_krThread_000_APPL_APP20240619_4APPL_TaskTest1)
                            - se l'esito è positivo
                                - ottenere il percorso relativo del file da inserire nella lista degli include_file per le tabelle usando la directory impiegata nel path di ricerca del file
                                - ottenere il define da insierire nella lista dei task





---

Wednesday, 23rd July 2025

- come ottenere la lista dei puntatoiri da inserire nella lista delle tabelle dei servizi?
    - REGISTER_SERVICE(<service name>, <pointer name>)


- gestione della creazione delle tabelle solo quando cambiano i sui elementi costitutivi
    - file di template
    - lista delle funzioni deell'array
- dagli elementi costitutivi si genera il file "tbl"
    - in 
        - krInitStaticTbl_template.cpp
        - krInitStaticIncFnctTbl.cpp.in
        - krInitStaticPtrFnctTbl.cpp.in
    - out
        - krInitStaticTbl.cpp
- procedura
    - 1. generazione delle due liste:
        - quella degli include [LIST_INC_FROM_FILE] dove sono definiti gli oggetti di cui al punto successivo
            - file(READ "${${type_name_up}_SRC_CMMN_DIR}/tb/kr/krInit/v_${VER_krInit}/${type_name_up}/krInitStaticIncFnctTbl.cpp.in" LIST_INC_FROM_FILE)
        - quella dei puntatori [LIST_PTR_FROM_FILE] agli oggetti di cui eseguire la funzione loop
            - file(READ "${${type_name_up}_SRC_CMMN_DIR}/tb/kr/krInit/v_${VER_krInit}/${type_name_up}/krInitStaticPtrFnctTbl.cpp.in" LIST_PTR_FROM_FILE)
    - 1. check degli elementi costitutivi per vedere se è necessario generare di nuovo il file "krInitStaticTbl.cpp"
    - 2. generazione/update del file "krInitStaticTbl.cpp"
        - 2. 1. gestione lista degli include
            - eseguire il loop ricorsivo sulle dipendenze leggendo i files
                - krInitStaticIncFnctTbl.cpp.in
                - krInitStaticPtrFnctTbl.cpp.in
              per generare le due liste:
                - degli include dove sono definiti gli oggetti di cui al punto successivo
                - dei puntatori agli oggetti di cui eseguire la funzione loop
        - 2. 2. eseguire il replace del carattere delle liste ottenute al punto precedente 
        - 2. 2. 


---

Tuesday, 22nd July 2025


- gestionee namespaces
- gestione automatizzata delle tabelle
    - creare la lista da inserire nell'array di funzionoi
    - creare la lista degli include dove sono presenti i file header in cui sono definite le funzioni di cui al punto precedente


---

Monday, 21st July 2025

- terminologia
    - modulo elementare
    - modulo funzionale parziale/totale
        - i moduli funzionali sono un insieme di tanti moduli elementari

- gestione tabelle dei pricessi (thread/init/timer/state_machine/etc.)
    - ogni modulo funzionale deve definire la sua tabella
        - come?
            - 1. avere due files
                - uno che elenca i puntatori a funzione da inserire nella tablella
                    - tb/krInit/v_xx/<module name>/krInit/ptrFnctTbl.h
                    - krTimer/ptrFnctTbl.h
                    - etc.
                - l'altro associato al precedente che definisce gli include
                    - krInit/incFnctTbl.h
            - 2. le proprietà che devono avere questi files è la ricorsivita in rispetto le proprie dipendenze
            - 2. questo file deve contenere gli include corrispondenti ai moduli da cui dipende direttamente
            - 3. 


---

Friday, 18th July 2025

- gestione riferimenti incrociati/split sdk modules
    - Domanda: perche eseguire lo split?
        - Risposta: per evitare i riferimenti incrociati!
            - i riferimenti incrociati non permettono una perfetta "sequenza lineare" nella fase di linking
                - è questo complica la gestione delle dipendenze, infatti queste devono essere ripetute 
                    - si pensi al caso della gestione della UART appartenente al modulo [trdp_sdk]
                        - si è costretti ad avere una lista delle dipendenze nel modulo [main] non ortodossa essendo costretti a inserire delle ripetizioni
    - modalità di modifica & compatibilità verso il basso
        - la compatibilità verso il basso significa che il codice già presente prima della modifica che dipende dal codice che verrà modificato deve continuare a funzionare
        - modalità e loro pro&contro
            - lasciare inalterato il codice "di terze parti" [trdp]
                - non credo sia sempre possibile dipende 
                    - se lo sviluppatore del codice [trdp] ha impostato il suo codice in modo da poterlo modificare "da fuori"
                        - mi riferisco in particolare alle strutture dati che vengono utilizate nell'imnplementazione delle funzioni
                            - è molto probabile che ci sia la necessità di aggiungere altre informazioni ovvero altre sotto-strutture dati
                                - in questo caso la struttura originaria è bene che abbia ad esempio un puntatore a dato generico [void] che possa essere impostato dall'utilizzatore "esterno" del codice
                        - in caso affermativo è possibile "isolare" l'implentazione del codice (presente nel file [.cpp]) dalla sua interfaccia (presente nel file [.h])
                            - quindi in questo caso si può anche riscrivere totalmente l'implementazione
                                - per concludere: lo [split] del codice [trdp] è compiuto lasciando [inalterato] il codice [trdp]
                        - in caso negativo si è costretti a modificare il codice originario di [trdp]
                            - la cosa che secondo me risulta più conveninte è quella di
                                - modificare il file [.h] del codice [trdp]
                                    - e quindi creare una nuova versione del codice [trdp]
                                - portare fuori il suo corrispondente file [.cpp] 
                                    - per concludere: lo [split] del codice [trdp] è compiuto, putroppo, modificando il codice [trdp] in particolare il file [.h] ma, e qui la cosa è positiva, del solo modulo oggetto della nostra modifica ovvero
                                        - quanto da noi modificato non implica dover aggiornare altre parti del codice [trdp] per adattarlo agli aggiornamenti apportati
            - modificare il codice "di terze parti" [trdp]
    - come modificare il file [.cpp]
    - come modificare il file [.h]




---

Thursday, 17th July 2025

- cose da fare
    - gestione tabelle
    - gestione riferimenti incrociati/split sdk modules
    - memorizzare la configurazione del progetto al termine del build
        - stessa configurazione deve dare identico risultato nel build
            - file eseguibili identici
            - identica occupazione di ROM & RAM


---

Wednesday, 16th July 2025


set(LIBS_SDK_PLATFORM_OBJ_LIB_DIR__FROM_BUILD        ${CODE_DIR__FROM_BUILD}/libs/mpfw_code_libs_sdk_nxp/src/v_${SDK_PLATFORM_LIB_VER}                  )
set(TRDP_NXP_0ABST_EXT_LIB_RPATH                ${TRDP_NXP_0ABST_SRC_RPATH}/v_${SDK_PLATFORM_LIB_VER}/libs     )
set(TRDP_NXP_0ABST_EXT_LIB_DIR_FROM_BUILD       ${MPFW_CODE_DIR_FROM_BUILD}/${TRDP_NXP_0ABST_EXT_LIB_RPATH}    )


set(MPFW_CODE_CMAKE_LINK_SCRIPT_DIR     ${MPFW_CODE_DIR_FROM_BUILD}/cmake/mpfw_fw2_cmake/v_${CMAKE_SRC_VER}/toolchain/${PLATFORM_NAME} )

../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/common/src/tb/kr/krInit/v_01/main/krInitStaticTbl.cpp;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/common/src/tb/kr/krThread/v_01/main/krThreadTbl.cpp;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/common/src/tb/kr/krTimer/v_01/main/krTimerTbl.cpp;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/common/src/tb/sv/svStateMachine/v_01/main/svStateMachineTbl.cpp;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/startup/startup_stm32f769xx.s;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/main/main.cpp;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/freertos/freertos.c;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/interrupt/stm32f7xx_hal_timebase_tim.c;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/interrupt/stm32f7xx_it.c;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/sdk_conf/system_stm32f7xx.c;
../../../../../../../../../main/app20240619/layer/mpfw_fw2_main_app20240619_5main/platform/stm32f769_disco/src/uart/stm32f7xx_hal_msp.c


---

Tuesday, 15th July 2025

- come usare la registrazione dei file di configurazione
    - il modulo utilizzatore userà la funzione [RegisterConfigRpath]
    - il modulo proprietario usera la funzione [RegisterConfigDir]
        - nel caso  [Rpath] risulti non impostato (stringa vuota) imposterà il suo file di default
    - entrambe le funzioni di registrazione possono essere inserite nel file [set_public_dirs.cmake] anche per la funzione [RegisterConfigRpath]
        - nel caso la funzione [RegisterConfigRpath] venga inserita nel file e il file di configurazione è sottoposto a versionamento la versione non verrà letta e quindi si avrà errore


---

Monday, 14th July 2025

- 07.30 - 11.00 = 3.30
- 11.45 - 15.45 = 4.00
- 16.15 - 


- rsSerial
    - uyProtocol
    - sdk


- gestione tabelle dei processi (krTimer, krInit, etc. )
    - iomplementare delle tabelle ricorsive

---

Monday,  7th July 2025

- inizializzazione
    - sequenza delle procedure 
        - step 0
            - add new module as submodule to git local repository of mpfw_code module
        - step 1
            - gmmg config files
                - crea la directory [gmmg] con i due file di configurazione
        - step 2
            - creare il branch [owner] 
                - crea il branch owner in base ai dati impostati nei due file di configurazioni creati al punto precedente
            - checkout nel branch [owner]
                - tipicamente ci si trova nel branch [main] quando viene eseguita l'inizializzazione con il [git]
        - step 3 (creazione repository remota e push del branch ownwer)
            - step 3.1
                - creazione della reepository remota
            - step 3.2
                - push del modulo
        - step 4 (creazione del branch [main] in remoto e contemporaneo push)
        - step 5 opzionale (controlli vari)
            - eseguire i vari controlli
    - add new module
        - sequenza comandi [1](New: New module ...)->[3](Adb: Add & Absorb an existing one)
    - gmmg config files
        - sequenza comandi [4](Branch: Create, Checkout, ... branch)->[10](BFI: Branch configuration File Initialization)
        - development branch
            - creation
                - sequenza comandi [4](Branch: Create, Checkout, ... branch)->[9](BCr: Branch Creation)->...->[1](BcOw: Branch owner)
            - checkout
                - sequenza comandi [4](Branch: Create, Checkout, ... branch)->[3](BcC: Branch Checkout)->...->[1](BcOw: Branch owner)
        - "main" branch
            - checkout
                - sequenza comandi [4](Branch: Create, Checkout, ... branch)->[3](BcC: Branch Checkout)->...->[2](BcMn: Branch main)
            - push (esegue il push anche se il branch non è ancora presente nella repository remota)
                - sequenza comandi [3](Push_Pull: Push & Pull procedures)->[1](Psh: $ git push)
                    - N.B.: eseguire prima il checkout sul "main" branch e poi eseguire questa procedura
    - remote repository
        - creation
            - sequenza comandi [2](URL: Set remote repository URL)->[2](SUP: Set new url and then push)


---

Thursday,  3rd July 2025

- cmake
    ## dove si trova il file cmake
    -S .
    ## dove creare il file risultao del build
    -B main/mpfw_code_main_$main_name/wsp/cmake/build_as_lib/$platform/$build_type 
    -G "Unix Makefiles" 
    $toolchain_cmake  = "-DCMAKE_TOOLCHAIN_FILE=./cmake/arm-none-eabi-gcc.cmake"
    $platform_cmake <it is unuseful>
    -DWP_PLATFORM_STR=$platform 
    -DMAIN_NAME=$main_name 
    -DAPP_NAME=$apps_name 
    $build_type_cmake  = "-DCMAKE_BUILD_TYPE=Release" / "-DCMAKE_BUILD_TYPE=Debug"
    $verbose_cmake 
    $cmake_trace_files && {

- eseguire il build dei nuovi moduli 
    - nelle varie piattaforme
        - impostare il [PATH] per indirizzare il [toolchain] della piattaforma opportuna
    - creare uno scrièt semplice
- implementare uno script per compilare le librerie e l'applicazione
    - eliminare il parametro
        - MAIN_NAME
        - APP_NAME

## cmake -S . -B ../../../build -G "Unix Makefiles" -DEXTNL_LIB=N -DPLATFORM_NAME=mac             -DMAIN_NAME=app20250424       -DAPP_NAME=app20250424    -DFNCT_HW_2WRPR_SRC_CFG=00
## cmake -S . -B ../../../build -G "Unix Makefiles" -DEXTNL_LIB=Y -DPLATFORM_NAME=mac             -DMAIN_NAME=app20250424       -DAPP_NAME=app20250424    -DFNCT_HW_2WRPR_SRC_CFG=00
## cmake --build ../../../build -j 1


---

Tuesday,  1st July 2025

- riorganizzare i moduli
    - fnct
        - mpfw_fw2_fnct_core
            - mpfw_fw2_fnct_core_0abst / mpfw_fw2_fnct_core_3real
                - libs/mpfw_code_libs_fw2_core_core
            - mpfw_fw2_fnct_core_2wrpr
                - libs/mpfw_code_libs_fw2_wrapper_core
        - mpfw_fw2_fnct_hw
            - mpfw_fw2_fnct_hw_2wrpr
                - libs/mpfw_code_libs_fw2_wrapper_resources
    - trdp
        - sdk
            - mpfw_fw2_trdp_sdk_mac
                - libs/mpfw_code_libs_sdk_mac
            - mpfw_fw2_trdp_sdk_nxp
                - libs/mpfw_code_libs_sdk_nxp
            - mpfw_fw2_trdp_sdk_stm32f769_disco
                - libs/mpfw_code_libs_sdk_stm32f769_disco
                - libs/mpfw_code_libs_sdk_stm32f769_disco_mod
                    - mpfw_fw2_fnct_hw_2wrpr
                        - ./platform/stm32f769_disco



- utilities: programmi / scripts utili per la gestione di moduli
    - eseguire i vari tipi di build per tutti i moduli di una applicazione o per un singolo modulo
    - cancellare il contenuto delle directory build e build_main di ciascun modulo o di un modulo specifico



main/app20250424/layer/mpfw_fw2_main_app20250424_5main/platform/mac/wsp/cmake/v_09main
/Users/work/ObsiData/repo__main/smdl/repo__prjs/smdl/mpfw/code/mpfw_code/main/app20250424/layer/mpfw_fw2_main_app20250424_5main/platform/mac/build

---

Monday,  23rd June 2025


MAIN_APP20250424_5MAIN_SOURCE_FILES_CPP_WDEP: 
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_0abst/src/dty/cntnr/dtyCntnr1StreamUnitShmProx/v_00/dtyCntnr1StreamUnitShmProx.cpp;

../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/dty/intfc/cntnr/dtyCntnr1ArrayTuiList.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/dty/intfc/cntnr/dtyCntnr1ArrayTuiMap.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/dty/intfc/cntnr/dtyCntnr1StreamList/v_12/dtyCntnr1StreamList.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/dty/intfc/cntnr/dtyCntnr1StreamListX.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/dty/intfc/cntnr/dtyCntnr1StreamUnitStringV1.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctAbstUnit0.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctAbstUnit1Cntnr.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctAbstUnit1Map.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1Button.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1Debug.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1Ebox.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1FormattedString.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1FormattedStringCntnr.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1Map.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit1MmyInt.cpp;
../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/fnct/tuiFnctRealUnit2Cntnr.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/grph/tuiGrphAbstUnit0.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/grph/tuiGrphAbstUnit1State.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/grph/tuiGrphAbstUnit2Coord.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_0abst/src/grph/tuiGrphAbstUnit3Event.cpp;

../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_2wrpr/platform/mac/src/grph/tuiGrphAbstUnit4InOut/v_04/tuiGrphAbstUnit4InOut.cpp;

../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/cntnr/dtyCntnr0BaseUnit/v_00/dtyCntnr0BaseUnit.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyBaseArray.cpp;../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyBaseUnit.cpp;../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyString.cpp;../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/unit/dtyUnit0Base.cpp;../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/unit/dtyUnit1MmyInt32.cpp;

../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/clipboard/sdkClipboard.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/port/sdkPortDef.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmBase/v_01/shmBase.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmManager.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmMcuPinPort.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmMcuUsart.cpp;

../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuBase/v_04/mcuBase.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuPinPort.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuPinPort2.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuUsart.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuManager.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/sys/sysTimer.cpp;

../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphButton.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphLed.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphManager/v_05/pphManager.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphRely.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphSwitch.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphUsart.cpp;../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_3real/src/pph/pphWired.cpp;

../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/fnct/tuiFnctRealCplx3McuUsart.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/fnct/tuiFnctRealCplx3McuUsartX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/fnct/tuiFnctRealCplx3McuUsartXX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/fnct/tuiFnctRealUnit3McuUsart.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/fnct/tuiFnctRealUnit3McuUsartX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/grph/tuiGrphRealUnit5Base.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/grph/tuiGrphRealUnit5Root/v_02/tuiGrphRealUnit5Root.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/grph/tuiGrphRealUnit5Win.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCplt_0dtyCntnr2StreamListFStr.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCplt_dtyCntnr2StreamListFStr.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCplt_dtyCntnr2StreamListFStrX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCplt_dtyCntnr2StreamListShmProxX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltCplx3McuUsartX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltCplx3McuUsartXX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltCplx4McuUsartUU.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltCtnr2StreamFormattedString.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltCtnr2StreamFormattedStringX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1Button.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1Debug.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1DgtInOut.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1Ebox.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1FormattedStringCntnr.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit1MmyInt.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/cplt/tuiCpltUnit3ShmProxX.cpp;../../../../../../../../../fnct/tui/layer/mpfw_fw2_fnct_tui_3real/src/mngr/tuiManager.cpp;

../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/instances/platform/mac/hw/pph/app_pphDef_Leds.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/instances/platform/mac/hw/pph/app_pphDef_Buttons.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/instances/platform/mac/hw/pph/app_pphDef_Mod1.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/instances/platform/mac/hw/pph/app_pphManagerTbl.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/appWindow/platform/mac/app_tuiMainWindow/v_13/app_tuiMainWindow.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/manager/app_tuiManager.cpp;../../../../../../../../../appl/app20250424/mpfw_fw2_appl_app20250424/layer/4appl/src/manager/appManager.cpp;

../../../../../../../../../main/app20250424/layer/mpfw_fw2_main_app20250424_5main/platform/mac/src/vhwMain/v_24/vhwMain.cpp

mpfw_fw2_fnct_hw_0abst

mpfw_fw2_fnct_tui_0abst
mpfw_fw2_fnct_tui_2wrpr

mpfw_fw2_fnct_base
mpfw_fw2_fnct_hw_1trdp_sdk
mpfw_fw2_fnct_hw_2wrpr
mpfw_fw2_fnct_hw_3real

mpfw_fw2_fnct_tui_3real
mpfw_fw2_appl_app20250424

---

Friday,  20th June 2025

- ulteriori possibili semplificazioni per la gestione degli script cmake
    - standardizzare l'impostazione delle [dirs] e degli [rpaths]
        - questa cosa è utile perche significa anche standardizzare la struttura delle directory
        - usare delle macro con parametri
            - module name
            - oppure
            - module name & platform

---

Monday,  16th June 2025


FNCT_HW_2WRPR_SOURCE_FILES_CPP_WDEP: 
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/cntnr/dtyCntnr0BaseUnit/v_00/dtyCntnr0BaseUnit.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyBaseArray.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyBaseUnit.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/general/dtyString.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/unit/dtyUnit0Base.cpp;
../../../../../../../../../fnct/base/mpfw_fw2_fnct_base/layer/0abst/src/dty/intfc/unit/dtyUnit1MmyInt32.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_0abst/src/dty/cntnr/dtyCntnr1StreamUnitShmProx/v_00/dtyCntnr1StreamUnitShmProx.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/clipboard/sdkClipboard.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/port/sdkPortDef.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmBase/v_01/shmBase.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmManager.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmMcuPinPort.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_1trdp_sdk/platform/mac/src/shm/shmMcuUsart.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuBase/v_04/mcuBase.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuPinPort.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuPinPort2.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuUsart.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/mcu/mcuManager.cpp;
../../../../../../../../../fnct/hw/layer/mpfw_fw2_fnct_hw_2wrpr/platform/mac/src/sys/sysTimer.cpp

---

Thursday,  12th June 2025

- gestione automatizzata degli include/header file dei sorgenti

- analisi del [path] per ricavare
    - [type]
    - [layer]
    - [platform]
    - [version]
    - [nome_completo]   = [git_module_name] = [prefix]+[nome_abbreviato]
    - [nome_abbreviato] = [tipologia]+[nome_semplice]
    - [nome_semplice]   = [nome_base]+[layer]
    - [nome_base]

- schemi possibili di 

- mpfw_code/<type>/<nome_base>/layer/<nome_completo>/platform/<nome_platform>/wsp/cmake/<version>
- mpfw_code/<type>/<nome_base>/layer/<nome_completo>/wsp/cmake/<version>

- mpfw_code/<type>/<nome_base>/<nome_completo>/<nome_layer>/platform/<nome_platform>/wsp/cmake/<version>
- mpfw_code/<type>/<nome_base>/<nome_completo>/<nome_layer>/wsp/cmake/<version>
- mpfw_code/<type>/<nome_base>/<nome_completo>/wsp/cmake/<version>
- mpfw_code/<type>/<nome_base>/<nome_completo>/wsp/cmake/<version>

- mpfw_code/<type>/<app20250424>/layer/<mpfw_fw2_main_app20250424_5main>/platform/<mac>/wsp/cmake/<v_09main>
- mpfw_code/  main/  app20250424/layer/  mpfw_fw2_main_app20250424_5main/platform/  mac/wsp/cmake/ v_09main


---

Wednesday,  11th June 2025

- codifica del nome di un modulo
    - un [modulo] che è anche [layer]
    - un [modulo] che contiene più [layer]

- mpfw_fw2_<nome del modulo>_<layer(facoltativo)>
    - [mpfw]: rappresenta il nome dell'ambiente di sviluppo
        - questo ha come codice sorgente principale il modulo [cmake]
    - [fw2] rappresenta il nome della libraria costituito dall'insieme di tutti i sub-moduli
        - coinvolge tutti moduli della libreria
    - [nome_del_modulo] = <tipologia>_<nome_semplice>_<layer>
        - <tipologia>, le tipologie possibili sono
            - <base> -> 
                - nessuna dipendenza con moduli delle altre tipologie
            - <trdp> -> codice di terze parti
                - sdk
                - fatfs
                - lwip
                - freertos
            - <fnct> -> functionalities
            - <appl> -> applicazione
            - <main> -> punto di avvio del codice

- [nome_completo]   = [prefix]+[nome_abbreviato]
- [nome_abbreviato] = [tipologia]+[nome_semplice]
- [nome_semplice]   = [nome_base]+[layer]
- [nome_base]
- [prefix]
    - **MPFW_FW2**
- [tipologia]
    - 0base
        - dty (Data utiliTY)
        - mlg (Multi LanGuages)
    - 1trdp
        - sdk (Software Development Kit)
        - gui (Graphical User Interface)
        - fsy (File SYstem)
        - eth (ETHernet)
        - eos (Embedded Operative System)
    - 2wrpr
        - sdk
        - gui
        - fsy
        - eth
        - eos
    - 3fnct
    - 4appl
    - 5main 
- [layer]
    - 0abst
        - 0abst_dty (Data utiliTY)
        - 0abst_mlg (Multi LanGuages)
    - 1trdp
        - 1trdp_sdk
        - 1trdp_gui
        - 1trdp_fsy
        - 1trdp_eth
        - 1trdp_eos
    - 2wrpr
        - 2wrpr_sdk
        - 2wrpr_gui
        - 2wrpr_fsy
        - 2wrpr_eth
        - 2wrpr_eos
    - 3real
    - 4appl
    - 5main


- esempi
    - [base]
    - [trdp]
        - [sdk]
            - [nxp]
                - [lpcxpresso54628]/[OM13098UL]
            - [mac]
            - [stm]
                - [stm32f769_disco]
        - [fatfs]
        - [lwip]
        - [freertos]
        - [gui]
            - [emWin]
        - [segger]
            - [modBus]
            - [gui]


---

Thursday,  5th June 2025

- implementazione funzione di set e stampa delle [wsp_ver] e [src_cfg] di tutti i moduli
    - set_wsp_ver_funct(${MODULE_NAME})
        - dal ${MODULE_NAME} ottengo la lista delle dipendenze 
            - nella lista delle dipenendenze ho tre campi
                - nome del modulo -> ${MODULE_NAME}
                - [WSP_VER]
                - [SRC_CFG]
        - esempio di lista delle dipenednze
Dati in ingresso
set(FNCT_HW_3REAL_DEPS_LIST 
    ### name            wsp_ver     src_cfg
        FNCT_HW_2WRPR   01          03    
        FNCT_HW_0ABST   02          01
)

Dati in uscita

set(FNCT_HW_2WRPR_WSP_VER           01  )
set(FNCT_HW_2WRPR_SRC_CFG           03  )

set(FNCT_HW_0ABST_WSP_VER           02  )
set(FNCT_HW_0ABST_SRC_CFG           01  )

set(FNCT_HW_3REAL_DEPS_NAME_LIST    
        FNCT_HW_2WRPR    
        FNCT_HW_0ABST
)

set(PROPAGATE_VAR_LIST
    FNCT_HW_2WRPR_WSP_VER
    FNCT_HW_2WRPR_SRC_CFG    
    FNCT_HW_0ABST_WSP_VER
    FNCT_HW_0ABST_SRC_CFG
    FNCT_HW_3REAL_DEPS_NAME_LIST
)

- steps
    - step 1
        - analoisi della liosta delle dipendenze per ottenere i dati di uscita riporati sopra
    - step 2
        - 

FNCT_HW_0ABST_WSP_VER;
FNCT_HW_0ABST_SRC_CFG;
FNCT_HW_1TRDP_DEPS_NAME_LIST;

FNCT_BASE_WSP_VER;
FNCT_BASE_SRC_CFG;
FNCT_HW_0ABST_DEPS_NAME_LIST;

FNCT_BASE_DEPS_NAME_LIST        

---

Wednesday, 28th May 2025

- gestione delle versioni dei workspaces [wsp]
    - l'idea sarebbe quella di far euna cosa ricorsiva come per gli init
    - si vuole parametrizzare la versione
        - quindi nasce il problema di impostare il parametro [par_ver] per ogni [wsp] di ogni modulo
            - dove impostarlo?
            - chi lo deve impostare?
                - direttamente il modulo [user]
                - o indirettamente il modulo [user] demandando l'impostazione allo [used] attraverso un eventuale file di configurazione
            - prima di impostare la versione sarebbe da controllare che non sia gia stata impostata da un'altro modulo con un valore diverso

include(set_depenedencies_wsp_ver.cmake)
    include_guard()
    set_ver(<user/project_name>     FNCT_HW_0ABST_WSP_VER      00)
    include(set_modules_rurl.cmake)
    include(<dependecy module>/set_depenedencies_wsp_ver.cmake)


---

Tuesday, 27th May 2025

- modules_address_info.cmake
    - servono per 
        - chiamare gli [init] delle dipendenze (ed in particolare  del [set_public_rpath.cmake])
            - che incidono sul
                - eventuale comando di sub-directory


---

Wednesday, 21st May 2025

- gestione files di configurazione dei moduli
    - il modulo proprietario esegue la REGISTRAZIONE della directory in cui è localizzato il file di configurazione
    - impostare il percorso relativo RPATH del file di configurazione
        - procedura
            - 1. si imposta la variabile di configurazione del tipo
                - FW2_FNCT_HW_0ABST_TEST1_CONFIG_RPATH

set(FNCT_HW_0ABST_DEFAULT_CONFIG_RPATH  ${FNCT_HW_0ABST_SRC_RPATH}/config)
set(VAR_FNCT_HW_0ABST_CONFIG_RPATH   FNCT_HW_0ABST_DEFAULT_CONFIG_RPATH )

set(FNCT_HW_1SDK_CONFIG_HW_0ABST_RPATH  ${FNCT_HW_1SDK_SRC_RPATH}/config/hw0abst)
set(VAR_FNCT_HW_0ABST_CONFIG_RPATH   FNCT_HW_1SDK_CONFIG_HW_0ABST_RPATH )
include(${MPFW_CODE_CMAKE_DIR}/init/default/hw/0abst/reg_config_rpath.cmake)        

// config rpath registration, file presente nella directory del proprietario del file di configurazione
include_guard()
set(FNCT_HW_0ABST_CONFIG_RPATH  ${${VAR_FNCT_HW_0ABST_CONFIG_RPATH}})

// ISTRUZIONE DA ESEGUIRE UNA SOLA VOLTA CON LA PRECEDENZA DI CHI LA IMPOSTA PRIMA
set(FW2_FNCT_HW_0ABST_TEST1_CONFIG_RPATH  ${${VAR_HW_0ABST_TEST1_CONFIG_RPATH}}/config)


---

Tuesday, 20th May 2025

- step 1
    - creare [rpath] recursive delle dipendenze
- step 2
    - creare le [dir] no-recursive delle dipendenze

---

Monday, 19th May 2025

- dipendenze
    - dirette
    - indirette
    - classiche
    - inverse

- i file [set_include_dirs.cmake], necessari per conoscere le locazioni degli header file dei moduli da cui si dipende, si deve chiamarli all'interno dei file [include_files.cmake]

- gestione config directories
    - prima definire le directories di default e le directories diverse da quelle di default se ci sono
        - quindi è necessario prima impostare i path di tutti i moduli
            - da cui si dipende
            - e a cui si fornisce un servizio (è il caso dei file include di configurazione)
    - poi eseguire l'assegnamento alla variabile che contiene la directory di config "scelta" e che verrà letta da tutti i moduli

---

Saturday, 17th May 2025


- gestione modulo CMAKE e dipendenze dei moduli
    - il modulo CMAKE forse si potrebbe anche eliminare
        - la sua presenza è legata principalmente o forse anche esclusivamente alla gestione delle dipendenze tra moduli
            - forse è possibile modularizzare anche questo aspetto ovvero spostare il codice cmake presente nel modulo [cmake] distribuendolo in modo selettivo tra i vari moduli
    - organizzazione della directory [wsp]
        - wsp
            - private
                - CMakeLists.txt
                - cpp_files.cmake
            - public
                - include_files.cmake
                - header_files.cmake
                - set_public_dirs.cmake
                    - dove si possono trovare i files cmake che contengono la lista 
            - dep
                - s1_set_modules_root_dir.cmake
                    - chiama/include i files "set_public_dirs.cmake" di ciascun modulo da cui si dipende

---

Saturday, 17th May 2025

- organizzazione delle directories del modulo [mpfw_code]
    - mpfw_code
        - libs
            - 0_base
            - 1_trdp
            - 2_fnct
            - 3_appl
            - 4_main
        - wsp
            - cmake
            - stm
            - nxp


---

Thursday, 15th May 2025


- fnct
    - tui
        - smod
            - mpfw_fw2_fnct_tui_0abst
            - mpfw_fw2_fnct_tui_3real
    - base
        - mpfw_fw2_fnct_base
            - smod
                - 0abst
                - 1trdp_sdk
                    - common
                    - platform
                        - mac
                - 3real

---

Wednesday, 14th May 2025

- gestione delle funzionalità, applicazioni, entry-point, e librerie di terze parti
    - <main>: directory contenente i moduli della funzionalità di <entry_point> che possono essere utilizzati per più applicazioni
        - gli strati presenti in questa classe di moduli sono
            - [5main] (favoltativo): questo strato può anche non esserci nel caso non sia stato deciso di sfruttare uno strato [5main] standard quindi usato da altre applicazioni
            - [1trdp] (facoltativo): questo strato può riguardare nel caso dell'SDK l'implementazione degli interrupt
    - <appl>: directory contenente i moduli delle applicazioni; 
        - un'applicazione è un insieme di funzionalità; un'applicazione è caratterizzata da un 
            - FRONT-END
                - necessaria per l'interazione con l'utente
                - sfrutta gli oggetti/funzioni/servizi offerti dalla funzionalità GUI 
            - BACK-END che sfrutta gli oggetti/funzioni/servizi offerti da funzionalità che gestiscono l'hardware della piattaforma per poter svolgere quelle aività per cui è stata creata
                - necessaria per svolgere le attività ad esempio di controllo, super visione, gestione periferiche hardware, etc. per cui è stata creata 
                - notare che un stessa applicazione può "diventare" o "essere vista come" una funzionalità; importante in questo caso è dotare l'applicazione di opportuni oggetti (funzioni, classi, servizi) da poter mettere a disposizione di altri moduli <appl> o <fnct>, l'insieme di questi oggetti può essere chiamato INTERFACE
            - INTERFACE è l'insieme di oggetti/funzioni/servizi creati per poter permettere ad altri moduli di usufruire delle funzionalità presenti nell'applicazione 
        - gli strati presenti in questa classe di moduli sono
            - [5main] (favoltativo): questo strato può anche non esserci nel caso non sia stato deciso di sfruttare uno strato [5main] standard quindi usato da altre applicazioni
            - [4appl] (necessario): questo strato si riferisce tipicamente ad applicazioni di esempio o di test della funzionalità
            - [1trdp] (facoltativo): questo strato può riguardare nel caso dell'SDK l'implementazione degli interrupt
    - <fnct>: directory contenente i moduli delle funzionalità quindi di quei moduli in cui sono presenti gli strati
        - [5main] (favoltativo): questo strato può anche non esserci nel caso non sia disponibile una applicazione di test o di esempio della funzionalità
        - [4appl] (favoltativo): questo strato si riferisce tipicamente ad applicazioni di esempio o di test della funzionalità
        - [3real] (necessario): contiene le interfacce che possono essere usate da altri moduli o strati posti a livello più alto per poter usufruire dei servizi forniti dalla funzionalità
        - [2wrpr] (molto probabile): contiene i wrapper delle librerie di terze parti necessari per poter rendere gli strati superiori indipendenti dalla specifica implementazione delle funzionalità fornite dalla libreria; questo modulo deve dipendere esclusivamente dai seguenti moduli
            - libreria [trdp] originale
            - strato [1trdp]
            - strato [0abst]
        - [1trdp] (facoltativo): questo strato contiene eventuali e/o possibili modifiche/aggiornamenti/adattamenti delle librerie di terze parti i cui moduli si trovano nella directory <trdp>
        - [0abst] (necessario): questo strato contiene principalmente le strutture dati necessarie per implementare le funzioni ed i servizi forniti dalla funzionalità 
    - <trdp>: directory contenente i moduli riguardanti le librerie di terze parti prima tra tutte la libreria dell'SDK associato alla piattaforma, altre possibili librerie possono essere FatFS, lwip, GUI, etc. 
        - gli strati presenti in questa classe di moduli son
            - [1trdp] (obbligatorio)
            - [0abst] (facoltativo)
    - <base>: contine moduli aventi un solo strato quello più basso ovvero quello astratto
        - gli strati presenti in questa classe di moduli son
            - [0abst]


---

Sunday, 11th May 2025

- build di un'applicazione
    - gli elementi necessari per il build di un'applicazione sono i seguenti:
        - strato [5main]: dove è presente l'entry point ed è quindi il modulo da cui si ottiene l'eseguibile
        - strato [1trdp_sdk]: implementazione degli handler degli interrupt
        - strato [4appl]: dove vengono istanziati gli oggetti  che concorrono alla generazione delle varie sub-funzionalità necessarie per sviluppare/implementare l'applicazione
    - i suddetti elementi possono essere "inglobati" all'interno di una funzionalità
        - in questo caso lo strato [4appl] molto probabilmente sarà un applicazione di esempio o di test della funzionalitù stessa
    - altrimenti possono avere questi tre strati riuniti all'interno di un modulo "applicazione"
        - ad esempio
            - <appXxx202505>
                - smod
                    - [mpfw_fw2_mainYyy_5main]
                        - notare che la parte del nome che precede lo strato è diversa dal nome dell'applicazione infatti questo modulo può essere utilizzato anche in altre applicazioni
                            - per questo motivo bisogna capire come configurare questo modulo per poterlo usare con il modulo applicazione desiderato di volta in volta
                                - per risolvere questa questione forse è sufficente parametrizzare il nome dell'applicazione 
                                    - forse no purtroppo, infatti ...
                                        - dall'applicazione dipendono le librerie utilizzate quindi bisognerebbe parametrizzare anche le librerie
                                    - o forse SI,
                                        - si potrebbe linkare le librerie nello strato [4appl] invece che nello strato [5main]
                    - [mpfw_fw2_appXxx202505_4appl]
                        - la parte del nome che precede lo strato deve essere uguale al nome dell'applicazione
                    - [mpfw_fw2_sdkZzz_1trdp_sdk]
                        - per il nome di questo strato si veda quanto detto per lo strato [main] questo modulo può essere utilizzato anche in altre applicazioni
- tui
    - smod
        - [mpfw_fw2_libs_tui_4appl_example1]


---

Saturday, 10th May 2025


- gestione applicazioni
    - gestione strato [4appl]
        - ci possono essere più strati [4appl] e solo uno di essi può essere attivo nella fase di build
        - dovrebbe essere selezionato attraverso paramatro da passare al [cmake]
        - lo schema del nome potrebbe essere [4app_<nome applicazione>]
            - ad esempio
                - [4app_example1]
                - [4app_example2]
                - [4app_test1]
                - etc., etc.
        - può accadere ad esempio che due applicazioni di una stessa funzionalità possano avere esigenze diverse per la configurazione degli interrupt
            - questo significa che anche lo strato [1sdk] dipenderà dall'applicazione e quindi il suop nome dovra essere del tipo
                - [1sdk_example1]
                - [1sdk_example2]
                - [1sdk_test1]
                - etc., etc.
        - parte del codice del modulo trasversale [sdk] dipende dall'applicazione/funzionalità un esempio è la implementazione degli handler degli interrupt
    - N.B.: il modulo associato ad una funzionalità può avere più submoduli dello strato [4appl] associato a questo strato ci sono altri due strati
        - [5Mmain]
        - [1trdp_sdk]
    - come assegnare i nomi agli strati 
        - [5main] dovrebbe andare in coppia con [1trdp_sdk] per formare un modoulo unico e prendere un nome anche diverso da quello dello strato [4appl]
        - [4appl] -> può essere "functionality free" (libero dall'essere associato ad una funzionalità perchè può riguardare un applicvazione che coinvolge più funzionalità in questo caso associate alle funzionalità ci sarebbero i quattro strati più bassi ovvero [3real],[2wrpr], [1trd_sdk/rtos/fatfs/etc.]) oppure associato al modulo di una funzionalità (può essere il caso di applicazioni di test o di esempio di utilizzo di una fiunzionalità)
            - nel primo caso si avrà una "funzionalità" con un solo strato ovvero [4appl] 
                - il nome dell'applicazione sarà costituito da un solo nome
            - nel secondo caso si avrà una "funzionalità" con anche gli strati più bassi dal 3 allo 0
                - il nome dell'applicazione sarà composto dal nome della funzionalità + nome della sub-applicazione associata alla funzionalità
        - [1trdp_sdk] -> vedi [5main] e [4appl]

---

Thursday, 7th May 2025


- gestione file source/cpp e source/h
    - file coinvolti
        - <include(${MPFW_CODE_CMAKE_MODULES_DIR}/libs/mpfw_fw2_libs_base/set_include_dir.cmake)>
            - imposta la variabile
                - [MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR]
        - <include(${MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR}/include_files.cmake)>
            - imposta la variabile

    - questo significa che eseguendo degli opportuni include avremo l'informazione che desideriamo nelle variabili ad esempio
        - <include(${MPFW_CODE_CMAKE_MODULES_DIR}/libs/mpfw_fw2_libs_base/set_include_dir.cmake)>
        - [MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR]
        - <include(${MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR}/include_files.cmake)>


../../../libs/mpfw_fw2_libs_base/smod/0abst/src/dty/intfc/cntnr;
../../../libs/mpfw_fw2_libs_base/smod/0abst/src/dty/intfc/general;
../../../libs/mpfw_fw2_libs_base/smod/0abst/src/dty/intfc/unit;
../../../libs/hw/smod/mpfw_fw2_libs_hw_0abst/src/dty/cntnr;
../../../libs/hw/smod/mpfw_fw2_libs_hw_0abst/src/dty/general;
../../../libs/hw/smod/mpfw_fw2_libs_hw_0abst/src/dty/port;
../../../libs/hw/smod/mpfw_fw2_libs_hw_1sdk/platform/mac/src/config/hw0abst;
../../../libs/hw/smod/mpfw_fw2_libs_hw_1sdk/platform/mac/src/clipboard;
../../../libs/hw/smod/mpfw_fw2_libs_hw_1sdk/platform/mac/src/port;
../../../libs/hw/smod/mpfw_fw2_libs_hw_1sdk/platform/mac/src/shm;
../../../libs/hw/smod/mpfw_fw2_libs_hw_2wrpr/platform/mac/src/mcu;
../../../libs/hw/smod/mpfw_fw2_libs_hw_2wrpr/platform/mac/src/sys;
../../../libs/hw/smod/mpfw_fw2_libs_hw_3real/src/pph;
../../../libs/tui/smod/mpfw_fw2_libs_tui_0abst/src/dty/intfc/cntnr;
../../../libs/tui/smod/mpfw_fw2_libs_tui_0abst/src/dty/intfc/unit;
../../../libs/tui/smod/mpfw_fw2_libs_tui_0abst/src/fnct;
../../../libs/tui/smod/mpfw_fw2_libs_tui_0abst/src/grph;
../../../libs/tui/smod/mpfw_fw2_libs_tui_2wrpr/platform/mac/src/grph;
../../../libs/tui/smod/mpfw_fw2_libs_tui_3real/src;
../../../libs/tui/smod/mpfw_fw2_libs_tui_3real/src/cplt;
../../../libs/tui/smod/mpfw_fw2_libs_tui_3real/src/fnct;
../../../libs/tui/smod/mpfw_fw2_libs_tui_3real/src/grph;
../../../libs/tui/smod/mpfw_fw2_libs_tui_3real/src/mngr

---

Wednesday, 7th May 2025

- ricordarsi di usare i [namesapce]


---

Tuesday, 6th May 2025

- gestione strato/livello [main] e [trdp_sdk]
    - notare che il modulo [main] potrebbe essere uguale per molte applicazioni cosi come il modulo [trdp_sdk] per quanto concerne la configurazione degli interrupt
    - si potrebbe quindi considerare una funzionalità del tipo "utility" in cui come strati avremo [main] e [trdp] che però saranno staccati
- modalità di utilizzo delle classi presenti nello strato/livello [wrapper]/[wrpr]
    - sarebbe da rendere privato il modulo [wrpr] all'interno del modulo funzionale nel senso che i moduli funzionali esterni non possono accedervi ma solo gli strati [3real] o superiore del modulo funzionale a cui appartiene
        - questa potrebbe essere una direttiva e non una regola rigida
- si potrebbe pensare quindi allo strato [wrapper]/[wrpr] come l'interfaccia verso i moduli [trdp] per gli strati dal [3real] in su
- mentre lo strato [3real] può essere visto come l'interfaccia verso le funzionalità del modulo per gli altri moduli funzionali

- differenze tra applicazione e funzionalità

---

Monday, 5th May 2025

- albero degli strati all'interno di un modulo che implementa una funzionalità/applicazione
    - main -> il modulo [main] potrebbe essere uguale per tutte o gran parte di esse le funzionalità come 
        - app -> è l'insieme di classi che usano gli oggetti delle classi del modulo real ma anche di altre funzionalità (e quindi ci saranno anche delle directories in cui si istanierano gli oggetti appartenenti ad altri moduli funzionali) per sviluppare un applicazione di <ESEMPIO>
            - real -> è l'insieme di classi da cui istanziare gli oggetti che verranno usati per implementare la specifica applicazione
                - wrpr
                    - sdk
                        - abst
                - abst
            - wrpr
            - abst
        - test -> come il modulo "fratello" [app] ma con lo scopo focalizzato sul <TEST> delle classi del modulo [real]; qui ci saranno delle directories 
            - real
                - wrpr
                    - sdk
                        - abst
                - abst

- gestione file di configurazione
    - files coinvolti
        - localizzati nel modulo "CMAKE"
            - [mpfw_code/cmake/mpfw_fw2_cmake/functions/function_register.cmake]
            - [mpfw_code/cmake/mpfw_fw2_cmake/init/default/s2_set_modules_config_dirs.cmake]
                - chiama i files "config_dirs.cmake" dei vari moduli per impostare le variabili che contengono le directories di configurazione di ciacun modulo
                - lo schema del nome delle variabili di cui sopra è:
                    - per la directory di configurazione di default
                        - LIBS_<nome del modulo "proprietario">_DEFAULT_CONFIG_DIR
                    - per la directory di configurazione situata in un modulo diverso da quello "proprietario" del file di configurazione, questa directory sostituirebbe quella di default
                        - LIBS_<nome del modulo "utilizzatore" del file di config>_CONFIG_<nome del modulo "proprietario" del file di config>_DIR
            - [mpfw_code/cmake/mpfw_fw2_cmake/ver/v_00/libs/hw/smod/mpfw_fw2_libs_hw_0abst/set_config_dir.cmake]
                - questo file viene chiamato all'interno dei file <include_files.cmake> dei moduli che gestiscono file di configurazione
                - qui, in questo file, si devono "registrare" i moduli di livello superiore al presente che vogliono modificare il file di configurazione
                - imposta la variabile che contiene la directory del file di configurazione
                - lo schema del nome della variabile che contiene il path della directory di configurazione è
                    - LIBS_<nome del modulo "proprietario">_CONFIG_DIR
        - localizzati nei moduli di libreria dei singoli moduli "livello/funzionali"
            - [mpfw_code/libs/hw/smod/mpfw_fw2_libs_hw0abst/wsp/config_dirs.cmake]
            - [mpfw_code/libs/hw/smod/mpfw_fw2_libs_hw1sdk/wsp/config_dirs.cmake]
            - ...
            - [mpfw_code/libs/hw/smod/mpfw_fw2_libs_<nome del modulo>/wsp/config_dirs.cmake]
                - imposta la propria directory di default se è presente
                - imposta le directories per i file di configurazione di altri moduli se presenti
                - esempio:
                    - mpfw_code/libs/hw/smod/mpfw_fw2_libs_hw_0abst/wsp/config_dirs.cmake
                        - imposta la variabile relativa alla propria directory di configurazione che si considera come quella di default
                    - mpfw_code/libs/hw/smod/mpfw_fw2_libs_hw_1sdk/platform/mac/wsp/config_dirs.cmake
                        - imposta la variabile relativa alla directory di configurazione, da sostituire a quella di default, del modulo <mpfw_fw2_libs_hw_0abst>
        - sequenza delle chiamata o flusso di programma
            - <CMakeLists.txt>
                - <s2_set_modules_config_dirs.cmake>
                    - <config_dirs.cmake del modulo XXX>
                    - <config_dirs.cmake del modulo YYY>
                    - etc., etc., ...
                - <include_files.cmake>
                    - <set_config_dir.cmake>
                - [risultato_finale]
                    - impostata la variabile 
                        - LIBS_<nome del modulo "proprietario">_CONFIG_DIR
                            - il contenuto di questa variabile farà parte della lista dei file include del modulo
        - procedura per aggiungere un file di configurazione
        - ovvero quali file modificare / sequenza di implementazione
            - impostazione delle variabili che contenogono il path della directory di configurazione
                - file interessati alla modifica
                    - <s2_set_modules_config_dirs.cmake>
                        - si trova nel modulo [CMAKE] nella directory <mpfw_code/cmake/mpfw_fw2_cmake/init/default>
                        - aggiungere le chiamate ai files <config_dirs.cmake> con l'istruzione include
                    - <config_dirs.cmake> di tutti i moduli che vogliono usare i propri partametri di configurazione
                        - si trovano nelle directory [wsp] di ciascun modulo
                        - impostazione del path della directory di configurazione
                            - seguire lo schema del nome della variabile riportato in un punto precedente
            - registrazione dei moduli interessati ad impostare i parametri di configurazione di n modulo da cui dipendono in modo diretto o indiretto
                - file interessati alla modifica
                    - <set_config_dir.cmake> del modulo proprietario del file di configurazione
                        - si trova  nel modulo [CMAKE] nella directory <mpfw_code/cmake/mpfw_fw2_cmake/ver/v_00/libs/hw/smod/mpfw_fw2_libs_(nome_del_modulo) >
                        - usare la funzione [Register] per registrare la variabile che contine il path alternativo a quello di default
                            - ci possono essere più registrazioni ma quando viene eseguito il build solo un modulo, di quelli registrati. può essere attivo altrimenti si verifichera un errore di conflitto

- cose da fare
    - impostazione 
        - nome applicazione
        - platform
        - versione
- creare una variabile per la directory "wsp" dei moduli


---

Friday, 2nd May 2025

- gestione file di configurazione dei moduli
    - ci dovrebbe essere un modulo [super_visor] che può essere visto/contatto da tutti i moduli e a sua volta può vedere tutti i moduli
        - un'applicazione/funzionalità si deve registrare quando si registra deve dire quali sub-funzionalità intende configurare
            - la funzionalità oggetto di configurazione  se non c'è nessuna super-funzionalità che la configura avrà al sua configurazione di default
            - la funzionalità oggetto della configurazione avra il suo spazio/directory nel mdulo [super-visor] all'interno di questo spazio ci saranno i vari moduli che la configurano
    

---

Thursday, 1st May 2025

- lo strato [13RDP_SDK] del modulo applicazione riguarda la configurazione degli interrupt ad esempio ed in generale la configurazione dell'hardware

---

Tuesday, 29th April 2025

- albero delle dipendenze tra le sezioni dei moduli
    - [4MAIN]
        - [3REAL]
            - [2WRPR]
                - [1THRDP]
                - [0ABST]
            - [0ABST]
    - [4TEST]
        - [3REAL]
            - [2WRPR]
                - [1THRDP]
                - [0ABST]
            - [0ABST]

- dipendenza tra funzionalità e dipendanza tra strati
    - ci sono funzionalita che sono tra loro indipendenti e c'è anche una gerarchia (un albero delle dipendenze tra funzionalità)
    - ciascuna funzionalità è implementata attraverso moduli che possono essere divisi in strati per organizzare il codice e poter lavorare in astratto rispetto eventuali sub-funzionalita da cui dipenderà (per esempio una di queste sub-funzionalità è rappresentata dallo strato SDK e quindi dipendente dalla piattaforma )
    - le funzionalità per la loro implementazione lavorano in astratto
    - una funzionalità per essere implementata ha bisogno 
        - di un supporto fisico (la piattaforma e quindi routine [1SDK])
        - di librerie di terze parti ad esempio (FatFS, FreeRTOS, lwip, etc.)
        - di una struttura dati (quindi lo strato astratto [0ABST])
        - organizzazione efficente del codice, quindi
            - separazione degli strati superiori in modo da renderli indipendenti da
                - codice di terze parti tra queste naturalmente l'SDK
            - creazione di altri due strati
                - [2WRPR_SDK], [2WRPR_FAT_FS], [2WRPR_FREERTOS], [2WRPR_LWIP]
                - [3REAL]
        - per una maggiore trasportabilità (quindi livello wrapper [2WRPR])
        - per una maggiore facilità di uso (quindi livello real [3REAL])
            - lo strato [3REAL] non deve dipendere direttamente,  ma solo indirettamente attraverso lo strato [2WRPR_SDK], dallo strato [1SDK]
    - gli ultimi due strati servono per organizzare il software in modo da renderlo più manutenibile e più facilmente e velocemente usabile

- [1THRD_SDK], [1THRD_LWIP], [1THRD_FREERTOS], [1THRD_FAT_FS], etc
    - questi moduli devono essere visti come delle possibili estensioni alle librerie originali 
        - un esempio può essere l'aggiornamento delle funzioni per la gestione della comunicazionee seriale attraverso USART, le funzioni che fornisce il produttore sono un po limitate quindi nasce la necessità di doverle estendere la cosa più pulita è quella di lasciare inalterate le funzioni originaliu e semplicemnte
            - 1. aggiornare i file cmake relativi all'SDK per escluderee dalla compilazione il file che contiene la funzione che si vuole modificare
            - 2. creare un nuovo modulo in cui si copia il file escluso dalla compilazione di cui sopra e si implementa la modifica della funzione  in oggetto

---

Sunday, 27th April 2025

- un modulo per interagire con gli altri moduli da cui dipende in modo diretto (chiamandone le funzioni) o indiretto (leggendo i propri file di configurazione localizzati esternamente alla propria directory) ha bisogno di alcune informazioniche saranno contenute in specifiche variabili globali

- <set(MPFW_CODE_DIR ../../../../.. )>
- <set(MPFW_CODE_CMAKE_DIR ${MPFW_CODE_DIR}/cmake/mpfw_fw2_cmake )>
- <include(${MPFW_CODE_CMAKE_DIR}/config/apps/(app name)/set_cmake_ver_dir.cmake)>
    - imposta la versione della configurazione dei file cmake del modulo [mpfw_fw2_cmake]
        - eseguite le seguenti istruzioni
            - <set(CMAKE_VER    05)>
            - <set(CMAKE_VER_DIR    v_${CMAKE_VER})>
    - imposta il percorso relativo di dove sono localizzate le informazioni per l'ambiente cmake di tutti i moduli
        - <set(MPFW_CODE_CMAKE_MODULES_RPATH        cmake/mpfw_code_cmake/${CMAKE_VER_DIR} )>
        - <set(MPFW_CODE_CMAKE_MODULES_DIR      ${MPFW_CODE_DIR}/${MPFW_CODE_CMAKE_MODULES_RPATH} )>
- ora conoscendo il percorso a cui riferirsi per leggere le informazioni pubblicate da tutti i moduli possiamo conoscere anche i percorsi delle directories [wsp] di ciascun modulo
    - questo significa che eseguendo degli opportuni include avremo l'informazione che desideriamo nelle variabili ad esempio
        - <include(${MPFW_CODE_CMAKE_MODULES_DIR}/libs/mpfw_fw2_libs_base/set_include_dir.cmake)>
        - [MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR]
        - <include(${MPFW_FW2_LIBS_(module_name)_INCLUDE_DIR}/include_files.cmake)>
## dependencies
set(LIBS_BASE_ROOT_DIR ${LIBS_ROOT_DIR}/mpfw_fw2_libs_base )
include("${LIBS_BASE_ROOT_DIR}/smod/0abst/wsp/include_files.cmake")
    
    - 
- <include(set_cmake_path.cmake)>

- un modulo ha bisogno di conoscere la variabile
    - <set(MPFW_FW2_LIBS_(module name) ...)>
        - questa informazione la trova nel modulo [cmake] <MPFW_CODE_CMAKE_DIR>
            - qui gli "viene data"/"viene impostata" la variabile [MPFW_FW2_LIBS_(module_name)] ovvero eseguita l'istruzione <set(MPFW_FW2_LIBS_(module name) ...)>
            - ma in quale sotto directory

- gerarchia delle variabili cmake
    - 


---

Saturday, 26th April 2025

- programmazione [CMake]
    - step 1
        - cosa fare
            - impostare le directories presenti nel modulo radice [cmake] servono a far conoscere ad un modulo le locazioni/directories pubbliche dei moduli da cui dipende
                - in questo modulo radice ci sono i riferimenti pubblici (ovvero le directories pubbliche) di tutti i moduli
        - come farlo
            - nel CMakeLists.txt radice ovvero quello che risiede nella directory [mpfw_code]
            - nel CMakeLists.txt di ciascun modulo
                - impostare le seguenti variabili
                    - [MPFW_CODE_DIR]: directory dell'ambiente di sviluppo (directory "mpfw_code") con un path realtivo rispetto la propria locazione
                        - per esempio:
                            - <set(MPFW_CODE_DIR ../../../../.. )>
                            - N.B.: questa variabile è diversa per ogni modulo o meglio ogni modulo la deve impostare perche non è uguale per tutti i moduli più che essere diversa per ciascun modulo, volendo essere precisi!!!
                    - [MPFW_CODE_CMAKE_DIR]: directory del modulo radice [cmake] con un path realtivo rispetto la propria locazione, sfruttando la variabile, MPFW_CODE_DIR, definita sopra
                        - per esempio:
                            - <set(MPFW_CODE_CMAKE_DIR ${MPFW_CODE_DIR}/cmake/mpfw_fw2_cmake )>
                - impostare il path alla directory dei file cmake dove i moduli "pubblicano" in particolare il path alla propria directory di workspace la directory [wsp]
                    - step 1: impostare la versione della directory
                        - chiamare il file include <include(${MPFW_CODE_CMAKE_DIR}/config/apps/(app name)/set_cmake_ver_dir.cmake)>: questo imposta la versione della directory dei file cmake corrispondente all'applicazione <app name>; qui già si possono vedere quali sono i moduli coinvolti nell'applicazione
                            - per esempio
                                - <include(${MPFW_CODE_CMAKE_DIR}/config/apps/(app name)/set_cmake_ver_dir.cmake)>
                                    - è bene mettere il nome dell'applicazione per un discorso di compatibilità tra versioni dei moduli, ad esempio la versione "03" del modulo (A) usa la versione "06" del modulo (B); questa informazione/configurazione dipenderà dalla applicazione e sarà presente in modo più o meno esplicito nei sui files cmake
                    - step 2: impostare il path relativo della dirtectory conoscendone già la versione (trovata al passo precedente)
                        - <set(CMAKE_MODULE_RPATH      cmake/mpfw_code_cmake/${CMAKE_VER_DIR} )>
                            - N.B.: il path è relativo alla directory radice dell'ambiente di sviluppo quindi sarà contenuto nella variabile 
                                - set(CMAKE_MODULE_DIR  ${MPFW_CODE_DIR}/${CMAKE_MODULE_RPATH}) impostata per ogni modulo


- algebra è calcolo simbolico è astrazione lavora con oggetti che hanno specifiche proprietà, l'algebra si preoccupa di sviluppare queste proprietà per ottenerene di nuove; algebra è astazione, lavora con oggetti astratti; come siano definiti, come siano fatti questi oggetti all'algebra non interesse, non riguarda il suo campo di studi
                            


---

Thursday, 24th April 2025

- i moduli [wrapper] sono quei moduli implementati solo in determinate piattaforme che fanno chiamate dirette alle funzioni dei moduli [sdk]
- per i moduli adatti per tutte le piattaforme ma in specifiche applicazioni utilizzati solo per alcune piattaforme la locazione rimane sempre la [0abst] o la [3real] (anche se si potrebbe pensare di inserirli nella directory [2wrapper]) in questi due moduli si creeranno tante directories quante le piattaforme in cui verranno usati i suddetti moduli; per gestire la compilazione di questi moduli si sfrutterà l'istruzione if(EXIST <PATH/TO/PLATFORM DIRECTORY>) del cmake per includere o meno nella compilazione i file dei moduli appena citati in questo modo solo le piattaforme interessate compileranno i mouli in oggetto



---

Wednesday, 23rd April 2025

- notare come il codice implementato nei moduli [real] può essere portato nei moduli [abst] implementando delle opportune interfacce

---

Tuesday, 22nd April 2025

- l'albero delle dipendenze tra sezioni unito all'albero delle dipendenze tra moduli permette di individuare i loop di chiamate
    - esempio
        - modulo_A.wrapper -> modulo_B.sdk -> modulo_C.sdk
        - modulo_B.wrapper -> modulo_A.sdk
    - se i moduli sdk non hanno loop anche i due moduli A e B non avranno loop
        - si possono avere dipendenze solo tra sezioni identiche o di livello inferiore
    - consideriamo il caso del protocollo per gestire la comunicazion seriale
        - sdkProtocol (f1) -> sdkUart (g1) -> sdkProtocol (f2) -> sdkUart (g2) -> ... [LOOP]
            - la soluzione sarebbe dividere il modulo sdkUart oppure il modulo sdkProtocol in due moduli in questo modo si può spezzare il [LOOP] tra librerie

- albero delle dipendneze tra le sezioni dei moduli
    - real
        - wrapper
            - sdk
            - abstract
        - abstract


- mpfw_code
    - cmake
    - libs
        - apps
            - <mpfw_fw2_app20250203>
                - smod
                    - <mpfw_fw2_app20250203_abst>
                    - <mpfw_fw2_app20250203_sdk>
                    - <mpfw_fw2_app20250203_wrapper>
                    - <mpfw_fw2_app20250203_real>
            - <mpfw_fw2_app20250327>
            - <mpfw_fw2_app20250423>
        - base
            - <mpfw_fw2_base>
                - smod
                    - <mpfw_fw2_base_abst>
                    - <mpfw_fw2_base_sdk> -> aggiornamenti/modifiche all'sdk del produttore
        - data
            - <mpfw_fw2_dty>
                - <mpfw_fw2_dty_abst>
                    - build
                    - src
                        - [data]
                            - [cntnr]
                            - [general]
                            - [unit]
                        - [hw]
                            - [cfg]
                            - [com]
                            - [general]
                            - [port]
                        - [tui]
                    - wsp
        - core
            - <mpfw_fw2_core>
                - build
                - src
                    - <mpfw_fw2_core_abst>
                        - build
                        - src
                            - kr
                                - krEvent
                                - krInit
                                - krTimer
                            - sv
                                - svState
                                - svSync
                                - svStateMachine
                                - svMutex
                        - wsp
                            - cmake
                            - nxp
                            - stm
                            - infineon
                            - microchip
                            - elektronika
                    - <mpfw_fw2_core_sdk>
                        - platform
                            - mac
                                - build
                                - src
                                - wsp
                            - nxp
                                - build
                                - src
                                - wsp
                            - stm32f769_disco
                                - build
                                - src
                                - wsp
                    - <mpfw_fw2_core_wrapper>
                        - common
                            - src
                            - wsp
                        - platform
                            - mac
                                - build
                                - src
                                - wsp
                            - nxp
                                - build
                                - src
                                - wsp
                            - stm32f769_disco
                                - build
                                - src
                                - wsp
                    - <mpfw_fw2_core_real>
                        - build
                        - src
                        - wsp
        - hw
            - <mpfw_fw2_hw>
                - build
                - src
                    - <mpfw_fw2_hw_abst>
                        - build
                        - src
                            - [dty]
                        - wsp
                    - <mpfw_fw2_hw_sdk>
                        - platform
                            - mac
                                - build
                                - src
                                    - [shm]
                                    - [clipboard]
                                - wsp
                            - nxp
                            - stm32f769_dico
                    - <mpfw_fw2_hw_wrapper>
                        - common
                        - platform
                            - mac
                                - build
                                - src
                                    - [mcu]
                                - wsp
                            - nxp
                            - stm32f769_dico
                    - <mpfw_fw2_hw_real>
                        - build
                        - src
                            - [pph]
                        - wsp
        - tui
            - <mpfw_fw2_tui>
                - src
                    - <mpfw_fw2_tui_abst>
                        - build
                        - src
                            - [dty]
                            - [fnct]
                            - [grph]
                        - wsp
                    - <mpfw_fw2_tui_wrapper>
                        - common
                        - platform
                            - mac
                                - build
                                - src
                                    - [fnct]
                                - wsp
                            - nxp
                            - stm32f769_disco
                    - <mpfw_fw2_tui_real>
                        - build
                        - src
                            - [cplt]
                            - [fnct]
                            - [grph]
                        - wsp
    - exec
        - main
    - CMakeLists.txt
    
- core
    - <mpfw_fw2_core>
        - abst
            - <mpfw_fw2_core_abst>
        - sdk
            - <mpfw_fw2_core_sdk>
        - wrapper
            - <mpfw_fw2_core_wrapper>
        - real
            - <mpfw_fw2_core_real>

- wrapper
    - <macro_module_name>
        - common
            - build
            - src
            - wsp
        - platform
            - hw
                - nxp
                    - build
                    - src
                    - wsp
                - stm32f769_disco
                    - build
                    - src
                    - wsp
                - ...
                    - build
                    - src
                    - wsp
            - sw
                - mac
                    - build
                    - src
                    - wsp
                - lnx
                    - build
                    - src
                    - wsp
                - win
                    - build
                    - src
                    - wsp
                - web
                    - build
                    - src
                    - wsp
                - ...
                    - build
                    - src
                    - wsp

---

Monday, 21st April 2025

- pulizia per eliminare i file non utilizzati (file [xxx_<>.cpp/.h]) e poi eseguire il commit
    - OK
- correggere il baco che manda in crash l'applicativo quando all'iniziosi preme sunbito il tasto enter
    - OK

- aggiornare la struttura (organizzazione dlle directories) dei moduli per poi inseirli nelle librerie MPFW/FW2
- la struttura dei moduli con i relativi sotto sub-moduli è la seguente
    - <modulo>
    - <gruppi di moduli>

- hw
    - abst
        - intfc
            - mcu_interfaces
            - pph_interfaces
    - sdk
        - shm
    - wrapper
        - mcu
    - real
        - pph
- tui
    - abst
        - mpfw_lib_fw2_tui_abst
            - fnct
            - grph
    - sdk
        - mac
            - mpfw_lib_tui_sdk_mac
            - mpfw_lib_fw2_tui_sdk_mac
                - sdkClipboard
        - nxp
        - stm32f769_disco
    - wrapper
        - mpfw_lib_fw2_tui_wrpr
            - tuiWrpr<file_name>.cpp/.h
        - common
        - platform
            - mac
                - build
                - src
                    - cplt
                        - usart
                - wsp
            - nxp
            - stm32f769_disco
    - real
        - build
        - src
            - cplt
            - fnct
            - grph
        - wsp

- app
- core


- [moduli_funzionali] e [moduli_sezione]

- le sezioni che ogni modulo o gruppo di moduli ha, sono
    - abstract
        - sono tutti i moduli che non dipendono ne direttamente ne indirettamente dalla piattaforma e quindi dai moduli sdk
        - lavorano con strutture dati che dipendono dalle librerie standard del linguaggio
        - sono ad esempio i file di configurazione
    - sdk
        - sono tutti i moduli che dipendono dalla piattaforma ed eventualmente dai moduli [abstract]
    - wrapper
        - sono tutti i moduli che dipendono dai moduli sdk e abstract
    - real
        - sono tutti i moduli che dipendono DIRETTAMENTE dai moduli wrapper (e quindi INDIRETTAMENTE dai moduli sdk) e abstract 
        - sono quindi i moduli che sono INDIPENDENTI dalla piattaforma ma, da essa, dipendenti indirettamente attraverso i moduli wrapper 
- con questa suddivisione l'implementazione dei moduli real ed abstract rimane invariata al variare della piattaforma
    - quindi per passare da una piattaforma ad un altra sono i moduli sdk e wrapper a dover essere creati, modificati o aggiornati

- albero delle dipendenze delle
    - real
        - wrapper
            - sdk
            - abstract
        - abstract
            
- dipendenze dall'applicazione

http://help.org/1_2_3_4 -{123}

---

Saturday, 19th April 2025

- i moduli che fanno riferimento diretto, quindi fanno chiamate dirette, a funzioni SDK devono risiedere in un modulo radice [wrapper]
    - se per qualche modtivo non si vuole inserire il modulo in esame in un modulo radice wrapper si deve crare un interfaccia per quelle funzioni e creare un modulo wrapper che implementi quelle funzioni per la piattaforma desiderata

---

Friday, 18th April 2025

- un modulo wrapper
    - gestisce le platform
        - ha tante directories quante sono le piuattaforme
    - fa riferimento ad un modulo radice che fornisce le interfaccie come ad esempio il modulo radice [dty]
- un modulo sdk
    - ha il nome dipendente dalla piattaforma

- tui_abst
    - tui_dty
- tui_sdk
- tui_wrapper
- tui_real

- hw_abst
    - hw_dty
- hw_sdk
    - clipboard
    - shm
- hw_wrapper
    - mcu
- hw_real
    - pph

---

Monday, 14th April 2025

- principale scopo della particolare attenzione che si dedica all'analisi e "progetto" delle dipendenze è che non ci siano loop nei file include quando si lavora con i moduli o in un contesto di programmazioone modulare
- analisi dei tipi di dipendenze e di come si denotano
    - si ha una dipendenza diretta [DPN_D] quando un modulo di livello più alto fa riferimento ("usa" un file include oppure "chiama" una funzione ) ad un elemento (file o funzione) presente in un modulo di livello più basso
    - si ha una dipendenza indiretta [DPN_I] quando un modulo di livello più basso fa riferimento ("usa" un file include oppure "chiama" una funzione ) ad un elemento(file o funzione) presente in un modulo di livello più alto
    - si ha una dipendenza debole [W_DPN] quando un modulo si limita ad "usare"/"chiamare" un file di intestazione (file header .h) di un altro modulo per "leggerne" una struttura dati (caso tipico di una [W_DPN_D]) o dei parametri di configurazione che lo riguardano (caso tipico di una [WDPN_I])
- esempi di dipendenze nel mondo reale
    - relazione tra una persona ed una istituzione pubblica (comune, agenzia delle entrate, INPS, etc.) o privata (azienda di cui si è dipendenti, istituto di credito, etc.)
        - l'istituzione pubblica o privata è una classe di elementi/oggetti che si trova ad un livello più basso di una persona nella gerarchia delle dipendenze, la persona è un elemento che "usa" una precisa [istanza] di una istituzione pubblica/privata mentre l'istituzione pubblica/privata conosce solo un [modello]/[interfaccia] di persona (ovvero una descrizione generale di cosa sia una persona e di quali proprietà essa sia provvista)
            - una classe persona ha al suo interno una sezione  relativa a istituzione pubblica/privata in cui ad esempio si trovano i documenti del contratto  con la banca
                - notare che i documenti del contratto con la banca sono documenti della banca che però risiedono a casa della persona
                    - in questo caso i documenti caratterizzano una relazione [W_DPN_I] tra l'istituzione pub/prv e la persona
- come impostare le directory di un modulo
    - un modulo dovrà avere delle sezioni non solo all'interno del codice e quindi dei file sorgenti ma anche delle directory per poter configurare i servizi usati nell'implementazione delle funzionalità del modulo stesso
        - consideriamo il caso dei moduli [dty]
            - il [modulo-radice] base [dty_base] riguarda/descrive strutture dati generali usate da qualunque applicazione e naturalmente da [moduli-radice] [dty], ad esempio [dty_App_XXX], di livello più alto
                -  che dipendono solo da [moduli-radice] [dty] di livello più basso 
                - ci possono essere però anche
---

Sunday, 13th April 2025

- principale scopo della particolare attenzione che si dedica all'analisi e "progetto" delle dipendenze è che non ci siano loop nei file include quando si lavora con i moduli o in un contesto di programmazioone modulare
- analisi dei tipi di dipendenzae e di come si denotano
    - [WDPN_I]/Weak DePeNdence Indirect 
        - si ha una dipendenza indiretta [_I] quando un modulo di livello più basso fa riferimento ("usa" un file include oppure "chiama" una funzione ) ad un elemento (file o funzione) presente in un modulo di livello più alto
        - si ha una dipendenza debole [WDPN_] quando la relazione di dipendenza consiste solo nell'usare/chiamare un file di intestazione (file header .h) presente in un altro modulo 
            - nella presenza di file di intestazione nella direttiva [#include] e a sua volta il file di intestazione in oggetto non fa riferimento a nessun file di intestazione di altri moduli (questa più che una definizione è una regola che un programmatore si da per sviluppare il proprio codice)
            - questo avviene quando
                - si usano delle strutture dati o interfacce ([WDPN_D] dipendenza debole diretta)
                - o si "leggono" i valori di parametri di configurazione del codice sorgente ([WDPN_I] dipendenza debole indiretta)
    - [WDPN_D]/Weak DePeNdence Direct 

---

Friday, 11th April 2025

- alla luce di come si gestiscono i file di configurazione si può pensare di suddividere i moduli in sotto-moduli
    - i sotto moduli devono avere delle caratteristiche
        - un sottomodulo utile potrbbe essere quello delle interfacce e delle base dati
            - la caratteristica di questo sotto-modulo è che non deve avere nessuna dipendenza con altri moduli eccetto che con il modulo [dty] o i moduli [dty]6 questo modulo contiene le definizioni delle strutture dati generali adatte per tutti i moduli
- [<MODULE_NAME>_WDPN_D_INTFC_RPATH] / [<MODULE_NAME>_WDPN_D_INTFC_DIR]
- [<MODULE_NAME>_WDPN_I_CONF_RPATH]  / [<MODULE_NAME>_WDPN_I_CONF_DIR]

- gestione [dipendenze_deboli]/[weak_dependencies] & cmake files
    - cmake/mpfw_code_cmake/v_05/main/[set_public_include_src_ver_prj_dir.cmake]
        - dove viene impostata la variabile [MAIN_CMAKE_PUBLIC_CONF_RPATH]
            - si è visto che non c'è nessun riferimento a questa variabile e quindi forse può anche essere eliminata
    - cmake/mpfw_code_cmake/v_05/main/tst_20240619main/src_conf/mac/[set_conf_inc_dirs.cmake]
    - cmake/mpfw_code_cmake/v_05/main/tst_20240619main/src_conf/nxp/[set_conf_inc_dirs.cmake]
    - cmake/mpfw_code_cmake/v_05/main/tst_20240619main/src_conf/stm32f769_disco/[set_conf_inc_dirs.cmake]
        - dove viene impostata la variabile [..._CONF_RPATH]
        - dove viene impostata la variabile [..._CONF_DIR]  in funzione della [..._CONF_RPATH]
    - libs/mpfw_code_libs_sdk_stm32f769_disco_mod/wsp/cmake/project/v_00/public/[03_set_inc_dirs.cmake]
        - dove viene usata la variabile [..._CONF_DIR]
    - libs/mpfw_code_libs_fw2_wrapper_core/common/wsp/cmake/project/public/[03_include_ver_set_inc_dirs.cmake]
        - dove viene usata la variabile [..._CONF_DIR]
    - main/mpfw_code_main_tst_20240619main/wsp/cmake/project/common/v_02/[03_set_inc_dirs.cmake]
        - dove viene usata la variabile [..._CONF_DIR]
    - main/mpfw_code_main_tst_20240619main/wsp/cmake/project/common/v_02/[03_set_inc_dirs.cmake]
        - dove viene usata la variabile [..._CONF_DIR]

---

Thursday, 10th April 2025

- gestione file di configurazione
    - caratteristiche di un file di configurazione
        - è un file .h che deve poter essere visto da tutti i moduli
        - non deve dipendere da nessun modulo
    - quindi ogni modulo radice deve avere una sezione nel modulo [dty] in cui sono presenti le strutture dati pubbliche
        - le interfacce, definite in un file pubblico a cui possono accedere tutti, permettono di dipendere da un modulo ma di non "ereditare" le dipendenze di quel modulo
    - un modulo di livello (a) legge un file di configurazione che è impostato da un modulo di livello (b) con (a) < (b)
        - la condizione naturalmente è quella che il modulo del livello (a) non deve essere a conoscenza del modulo del livello (b)
        - come fare?
            - 1) il modulo (a) deve chiamare un file .h che è gestito dal modulo (b) 
            - 2) il modulo (a) può chiamare un file presente nel modulo (0) (un modulo generale diviso in sezioni ciascuna associata ad uno ed un solo modulo radice)
                - 2.1) la caratteristica del modulo (0) è che non dipende da nessun modulo nonostante sia a conoscenza della presenza di tutti i moduli radice (ingloba infatti i file di configurazione di tutti i moduli radice)
                    - in questo modulo tutti i moduli radice dipendono da questo modulo radice di configurazione
                - 2.2) ogni applicazione ha un modulo (0) diverso, quindi questo modulo dipenderà dalla applicazione
    - ci sono due tipologie di file di configurazione
        - 1) quelli che "conviene"/"è comodo" aggiornarli in base all'applicazione
            - in questo caso il file di configurazione risiedera nel modulo radice "main" oppure "apps"
        - 2) quelli che "conviene"/"è bene/consigliabile" associarli alla versione del modulo a cui appartengono
            - in questo caso il file di configurazione risiedera nel modulo a cui appartiene
    - concetto di dipendenza debole e dipendenza forte
        - la [dipendenza_debole] è quella in cui il modulo "richiedente" si limita a leggere i file include del modulo "offerente" che non hanno dipendenze con altri moduli, tipicamente questi file sono dei file di configurazione ovvero non chiama nessuna funzione del modulo "offerente" oppure anche il file include che definiscopno le [classi_interfaccia]
            - vedendo la cosa da un altro punto di vista si può dire che un modulo ha una [dipendenza_debole] quando nel suo file di progetto cmake si imposta una directory include che non è una sottodirectory della directory radice del modulo ma risiede in un altro modulo
            - i file di configurazione di un modulo dipendono dall'utilizzo che si fa di quel modulo quindi è giusto che tali file risiedano non nel modulo che li definisce ma in quello che li usa
                - se vogliamo quella dei file di configurazione è una [dipendenza_debole_indiretta] mentre quella dei file include delle [classi_inetrfaccia] è una [dipendenza_debole_diretta]
        - la [dipendenza_forte] è quella in cui il modulo "richiedente" dipende interamente dal modulo "offerente" nel senso che ne chiama anche le funzioni, non si limita a "leggerne", come avviene nel caso della [dipendenza_debole], i file include




---

tuesday, 8th April 2025

- gestione dei file diconfigurazione
    - dipendono da
        - applicazione
        - modulo specifico
            - generale
            - quindi ce ne possono essere molti di moduli che hanno una loro configurazione
        - generale
    - ogni modulo radice può avere un file di configurazione

---

monday, 7th April 2025

- importante è distinguere tra dipendenza dalla piattaforma e dipendenza dall'SDK e quindi dalla piattaforma
    - un qualche modulo può dipendere dalla piattaforma ma non dipendere dal suo SDK questo ad esempio è il caso delle strutture dati ovvero i moduli contenuti nel modulo radice [dty] che comunque sono indipendenti dall'sdk
        - da capire quindi come sia più conveniente organizzare il modulo radice [dtym] eventualmente in sub-modules identificati attarverso la loro applicazione più specifica;
            - l'applicazione più specifica è quella che riguarda i moduli [Apps] ci sono poi applicazione meno specifiche e quindi riutilizzabili da moduli con un lòivello di applicazione più elevato
                - più il livello di applicazione è alto più i moduli si specializzano
                - il codice delle applicazioni può essere suddiviso in [front-end] & [back-end] il front-end può essewre visto come un punto di arrivo mentre il back-end come un modulo che può essre utilizzato da altri front-end
                    - fatto in un certo modo anche il front-end può essere riutilizzato da altre applicazioni
                        - in particolare si può creare  un componente grafico caratterizzato quindi da una sua finestra ed eventualmente dotarlo di funzioni di interfaccia affinche possa essere usato da moduli di più alto livello e quindi incorporato in altre finestre
                            - un esempio semplice può essere il modulo [tuiCpltCplx3McuUsartXX]
    - ([complete_modules] & [sub-modules]): ragionando si capisce che un "modulo completo" che lo si voglia riustilizzare in più applicazioni è costituito da più sotto-moduli che a loro volta dovranno essere propriamente installati ovvero collocati nei moduli radice opportuini
        - i vari [sub-modules] di un [complete_module] possono essere viste come delle sezioni
            - sezioni/[sub-modules]
                - [data_struct]
                - [parameters]
                - [timers]
        - sembrerebbe che un [complete_module] sia un modulo radice [root_module]



---

sunday, 6th April 2025

- classe interfaccia per l'hardware
    - ./src/dty/common/src/hw/port
        - dtyHwPort0AbstIntfc.cpp/.h


---

wednesday, 2nd April 2025

- tuiCpltUnit3ShmProx.md
    - description:
        - questo modulo grafico permette di visualizzare gli array dei processi attivi che condividono una porzione di memoria necessaria a simulare il canale di comunicazione e i collegamento tra le periferiche hardware virtuali
        - questo è un modulo grafico contenitore nel senso che deriva dalla classe interfaccia  [tuiFnctRealUnit2Cntnr_t]
            - questo significa che al suo interno, quindi {inside_par}, definira un oggetto derivato dalla classe interfaccia [dtyCntnr0BaseUnit_t], ncessario per inizializzare la classe derivata [tuiFnctRealUnit2Cntnr_t]
                - il modulo derivato da [dtyCntnr0BaseUnit_t] sarà il modulo specifico [tuiCplt_dtyCntnr2StreamListShmProxX]
                    - il modulo [tuiCplt_dtyCntnr2StreamListShmProxX] "completa" (ovvero crea gli oggetti necessari all'inizializzazione e ne passa i puntatori alla classe da cui deriva) la classe [dtyCntnr1ArrayShmProxListX] da cui deriva
                        - in questo caso significa che [tuiCplt_dtyCntnr2StreamListShmProxX] al suo interno definirà un'oggetto della classe [dtyCntnr1StreamUnitShmProx] ovvero un oggetto derivato dalla classe interfaccia [dtyCntnr0StreamUnitIntfc_t]
                        - è un oggetto [tui] della classe [tuiCpltUnit1MmyInt]
                        - la classe [dtyCntnr1ArrayShmProxListX] lavora con i puntatori ai seguenti oggetti
                            - oggetto derivato dall'interfaccia [dtyCntnr0StreamUnitIntfc_t]


---

tuesday, 1st April 2025

- [tuiCpltCplx3McuUsartXX]
    - <input_par><box_t>
        - destination
            - parent class initialization [tuiGrphRealUnit5Base_t]
    - <input_par><margins_t>
        - destination
            - parent class initialization [tuiGrphRealUnit5Base_t]
    - <input_par><pphUsart_t*>
        - destination
            - parent class initialization [tuiFnctRealCplx3McuUsartXX_t]
    - {inside_par}{tuiCplt_dtyCntnr2StreamListFStrX_t}      -> {dtyCntnr1StreamListX_t} -> {g_dty_recevingDataCntnr}
        - destination:
            - parent/deriving class initialization [tuiFnctRealCplx3McuUsartXX_t]
            - inside [g_tui_receivingDataBox] class initialization
    - {inside_par}{tuiCpltCtnr2StreamFormattedStringX_t}    -> {dtyIntfcAbstractUnitGraphic_t} -> {g_tui_receivingDataBox}
        - destination:
            - inside [g_boxesArray[3]] array
    - {inside_par}{char[]}                                  -> {char*} -> {g_char_sendingDataBuffer[300]}
    - {inside_par}{tuiCpltUnit1Ebox_t}                      -> {tuiFnctRealUnit1Ebox_t} -> {g_tui_sendingDataBox}
        - destination:
            - parent/deriving class initialization [tuiFnctRealCplx3McuUsartXX_t]
            - inside [g_boxesArray[3]] array
    - {inside_par}{dtyIntfcAbstractUnitGraphic_t[]}         -> {} -> {g_boxesArray[3]}
        - destination:
            - parent/deriving class initialization [tuiFnctRealCplx3McuUsartXX_t]
            - inside [g_dty_boxesCntnr] container class
    - {inside_par}{dtyCntnr1ArrayTuiList_t}                 -> {} -> {g_dty_boxesCntnr}
        - destination:
            - parent/deriving class initialization [tuiFnctRealCplx3McuUsartXX_t]
    - [der]->[tuiFnctRealCplx3McuUsartXX_t]
        - <input_par><pphUsart_t*>
        - <input_par><dtyCntnr1StreamListX_t*>  <- &<g_dty_recevingDataCntnr>
        - <input_par><char*>                    <- <g_char_sendingDataBuffer>
        - <input_par><tuiFnctRealUnit1Ebox_t*>  <- &<g_tui_sendingDataBox>
        - <input_par><dtyCntnr1ArrayTuiList_t*> <- &<g_dty_boxesCntnr>
        - {inside_par}{pphUsart_t*}
        - {inside_par}{uint8_t*}
        - {inside_par}{dtyCntnr1StreamListX_t*}
        - {inside_par}{char*}
        - {inside_par}{tuiFnctRealUnit1Ebox_t*}
        - [der]->[tuiFnctRealUnit2Cntnr_t]
            - <input_par><dtyCntnr0BaseUnit_t*> <- <dtyCntnr1ArrayTuiList_t*> <- &<g_dty_boxesCntnr>
            - {inside_par}{class}
            - [der]->[class]
    - [der]->[tuiGrphRealUnit5Base_t]
        - <input_par><class>
        - {inside_par}{class}
        - [der]->[class]

- [tuiCplt_dtyCntnr2StreamListShmProxX]
    - <input_par><no parameters>
    - {inside_par}{tuiCpltUnit1MmyInt}/{dtyIntfcAbstractUnitFunctional_t*}/{dtyIntfcAbstractUnitGraphic_t}
    - [der]->[dtyCntnr1ArrayShmProxListX]
        - <input_par><dtyCntnr0StreamIntfc_t*>/<dtyCntnr1StreamUnitShmProx>
        - <input_par><dtyIntfcAbstractUnitFunctional_t*>/<tuiCpltUnit1MmyInt>
            - {inside_par}{dtyUnit1MmyInt32_t}
            - [der]->[tuiFnctRealUnit1MmyInt]
                - <input_par><dtyUnit1MmyInt32_t*>
            - [der]->[tuiGrphRealUnit5Base]
                - <no parameters>
        - dtyIntfcAbstractUnitGraphic_t*
            - ->[tuiCpltUnit1MmyInt]

- [class]
    - <input_par><class interface>/<class real>
    - {inside_par}{class}
    - [der]->[class]
        - <input_par><class interface>/<class real>
        - {inside_par}{class}
        - [der]->[class]

---

monday, 31st March 2025

- tuiCplt
    - tuiFnct
        - dtyCntnr
            - dtyCntnrUnit (protocollo)
            - tuiCplt
                - tuiFnct
                    - dty<Data>
                - tuiGrph
    - tuiGrph


---

friday, 28th March 2025

- [cosa] trasferire
    - trasferire una stringa
        - [come] trasferire
            - ci possono essere più modi
                - [modo_1]
                    - descrizione:
                        - viene definita una variabile di appoggio nel modulo [manager] che conterrà il puntatore ai dati dello [streamBuffer]
                        - questa variabile di appoggio verrà aggiornata ad ogni ciclo di loop (loop sullo [streamBuffer])
                        - questa modalità ha necessità di chiamare una sola volta la funzione [tuiFnct->setPtrData(&g_str)]
                        - però dovrò chiamare ad ogni ciclo di loop (sullo [streamBuffer]) la funzione [tuiFnct->updData(&g_str)]
                    - [manager]
                        - il manager definisce una variabile puntatore a stringa, che chiamiamo [g_str] 
                            - definita ad esempio come (char* g_str)
                        - il manager chiama la funzione di [tuiFnct] per impostare il puntatore ai data in particolare
                            - [tuiFnct->setPtrData(&g_str)]
                        - quando il manager esegue il loop sullo stream buffer ad esempio per visualizzare i data chiamerà una funzione del modulo [streamBuffer] ad esempio
                            - g_str = [streamBuffer->getPtraData(g_loopId)]
                    - [unit]/[tuiFnct]
                        - [setPtrData]
                            - definita come 
                                - void setPtrData(void* p_pData)
                            - implementata a seconda del modulo [tuiFnct] che deve combaciare con il tipo di dati, in particolare
                                - ad esempio se il modulo [tuiFnct] è [tuiFnctString] avremo che
                                    - setPtrData(void* p_pData) { g_pStr = static_cast<char**> (p_pData); ... }
                    - [unit]/[streamBuffer]
                        - [getPtrData(g_loopId)]
                            - definita come 
                                - void* getPtrData(uint32_t p_loopId) { ... ; return &str[p_loopId]}
- come trasferire


---

thursday, 27th March 2025


- trasferire i dati da [streamBuffer] al componente [tuiFnct] e viceversa
    - g_loopTuiUnit->cntnrInit(&g_loopPString, &g_loopPStringInfo);
    - g_loopTuiUnit->setCntnrData(&g_loopPString, &g_loopPStringInfo);
- il modulo [cntnrUnitXXX] deve fornire le funzioni di [get] e [set] dei [data] e degli [infoData]
    - oppure fornire semplicemente il puntatore ai data [getPtrData] e agli infoData [getPtrInfoData]
- è il modulo [cntnrManager] che gestisce
    - il componente [tuiFnct]
    - e il mdoulo [cntnrUnit]
    - e quindi è lui che mette in comunicazione i due moduli [tuiFnct] e [cntnrUnit] che entrambi non sanno della presenza uno dell'altro
        - quindi necessariamente anche il modulo [tuiFnct] deve avere le medesime funzioni di [get] e [set] dei [data] e degli [infoData] oppure [getPtrData] e agli infoData [getPtrInfoData]




---

monday, 23rd March 2025

- implementazione interfaccia  per il modulo [dtyCntnr0Stream]
    - analisi del unità base di uno stream ovvero il pacchetto dati (intestazione + data)
        - l'elemento di riferimento sono gli indici che indicano l'[header] e i [data]
            - di base sostituiscono i puntatori, si è ritenuto più conveniente usare gli uint32_t piuttosto che un puntatore alla memoria
            - tuttavia si deve prevedere un puntatore alla stringa del buffer [data]
                - lo scopo è quello di visualizzare il buffer [data]
                    - se poi si vogliono visualizzare nello specifico i vari campi del buffer data necessariamente si dovrà fare riferimento ad una classe specifica e quindi sarà necessarioo abbinare per la parte grafica un elemnto custom/specifico
        - gli indici "standard" ovvero quelli presenti nell'interfaccia sono l'id iniziale [idFirst] e quello finale [idLast] che indica la fine dello stream

---

sunday, 23rd March 2025

- aspetti da migliorare
    - gestione dello stream container [dtyCntnr1StreamList] in moduli
        - invece di passargli il buffer dei dati come un puntatore a uint8_t passargli il untatore ad un oggetto con una precisa interfaccia
    - creare un interfaccia per gli elementi hardware seguendo quanto fatto per gli elementi grafici della user interface
        - il risultato più utile di questo aggiornamento è quello di avere i moduli [tuiFnct] totalmente astratti ed in particolare indipendenti dalle librerie [sdk] delle piattaforme


---

tuesday, 18th March 2025

- dove collocare i file .h di configurazione
    - forse la cosa più giusta e che ogni modulo radice abbia i sui file di configurazione

---

monday, 17th March 2025

- sezione 
    - [struttara_dati]
        - le strutture dati di un modulo possono essere richieste da altri moduli che fornire dei servizi come quello della visualizzazione
    - [interfaccia]



---

sunday, 16th March 2025

- si puo mantenere i moduli [tuiFnct] indipendenti dall'hardware creando delle opportune interfacce dell'hardware
    - in questo modo saranno i moduli [tuiCplt] a dipendere direttamente dall'hardware

- lavorare in astratto quindi
    - usando intyerfacce e punatatori
    - ha il vantaggio di poter riutilizzare il codice

---

saturday, 15th March 2025


- si deve creare unn modulo tui [shmProxList] eliminarlo dallo [shmManger]

- quali potrebbero essere le sezioni di un progwetto
    - data -> [dty]
        - ci sono dati generali e dati specifici
    - display -> [tui]
        - ci sono compoenti standard
        - ci sono componenti specifici per certi tipi di applicazione
            - ed in particolare specifici per la visualizzazione dell'hardware
    - hardware -> [hw]
        - ci sono elementi generici come 
            - le porte
            - protocollo i2c 
        - e piu specifici come la usart


- un elemento dell'hardware nella sua interezza può essere caratterizzata da vari moduli
    - esempio
        - consideriamo i moduli [shm] ed in particolare il [container] del buffer dei processi
            - il buffer dei processi
                - deve essere gestito
                    - aggiungere/eliminare processi
                        - implementazione nei moduli [shm]
                    - visualizzarlo
                        - implementazione nei moduli [dty] e [tui]
            - questo [container] dipende dalla struttrura dati del buffer dei processi (struttura dati specifica e non generale)
                - ora si pone il quesito: dove collocare i files .h e .cpp che definiscono questa struttura?
                    - in una prima analisi ci sono due risposte plausibili: collocare i files
                        - nel modulo radice [shm]
                            - conseguenza:
                                - il modulo radice [dty] per implmentare completamente il modulo container dovra dipendere dal modulo [shm]
                        - oppure
                        - nel modulo radice [dty]
                            - conseguenza:
                                - il modulo radice [shm] perderebbe la sua modularità nel senso che i suoi "pezzi" risulterebbero saprsi in più punti del progetto rendendo difficoltosa la sua gestione
                    - dopo questa prima analisi si ottiene il seguente quesito: alle "esigenze" di quale mdoulo dare la priorità?
                        - entrambe le regole, 1) quella di rispettare la gerarchia delle dipendenza e 2) quella di mantenere la modularità del codice, semplificano ed aiutano lo sviluppo e la manutenzione del codice
                            - ad ogni modo non è pensabile che un modulo "operativo" come può essere il modulo [shm] non abbia dipendenze quindi dipendenza più, dipendenza meno non fa la differenza e quindi il modulo [shm] conviene scinderlo tra sezione implementativa e sezione struttura dati
                                - la sezione strutura dati verrà inserita nel modulo radice [dty]
                            - eventualmente per salvare "capra e cavoli" si può pensare di fare un sunto dei moduli e sub-moduli di un modulo operativo e riportarli/raggrupparli in un package che può essere visto come un modulo, non integrato nelle librerie mpfw/fw2, che però ha tutte le informarmazioni per essere installato, in particolare le informazioni di dove collocare tutti suoi moduli e sottomoduli

---

friday, 14th March 2025


- si ricade sul discroso delle installazioni
    - il motivo
        - per procedere ad una programmazione modulare accade che i mdouli stessi devono essere suddivisi in sottomoduli e poi essere posizionatri negli opportuni moduli radici per permette ad altri moduli di poterli usare 
        - scopo: programmazione modulare
            - come procedere: suddividere i moduli in sotto-moduli
                - conseguenza: i sotto-moduli devono essere installati
                    - perché: per permettere ad altri moduli di ususfruire del modulo 
            - conseguenza: dare priorità alla gerarchia delle dipendenze ed alla coerenza/buon senso delle dipendenze
                - conseguenza:
                    - suddividere i moduli in sotto-moduli
                        - questi sotto-moduli dei moduli rappresentano delle [sezioni]
                            - vengono suddivisi per poterli gestire meglio e metterli a disposizione in una libreria di moduli adatta
                        - una esempio di [sezione] è quella rappresentata dal modulo radice [dty] (data utility)
                            - il modulo [dty] per sua natura è un modulo che deve essere indipendente da tutti gli altri moduli radice
                                - tuttavia per gestire la moltitudine di strutture dati che possono essere presenti in una applicazione questo stesso modulo, sempre per sua natura, dovrebbe essere soddiviso in più sotto-moduli primo dei quali [dty-base] ovvero un modulo che non ha nessuna dipendenza e da cui, bene o male, tutti gli altri sottomoduli dovranno dipendere
                                - i sotto-moduli di cui dovrebbe essere composto questo modulo [sezione]/[radice]

- quindi si sta prefigurando una classificazione di moduli
    - moduli
        - [radice]: libreria/raccolta di moduli che hanno le stesse dipendenze oppure, più precisamente, che appartengono ad una stessa sezione
        - [classe]: i moduli che sono anche tipicamente delle classi nel senso tecnico di un linguaggio ad oggetti, ad es. il linguaggio C++.
        - [sezione]: i moduli di cui possono essere composti o da cui dipendono i moduli [classe]
            - esempio di moduli sezione sono i moduli [dty] raccolti nell'omonima classe radice


- raccolta di moduli [sezione]
    - [dty]: data utility
    - [hw]: riguarda l'hardware

---

Wednesday, 12th March 2025

- dtyCntnr1StreamList_t
    - sarebbe da aggiornare per gestire anche gli array in modo da gestire ad esempio il buffer dei pid dei processi attivi
        - in STRUCT_&_DATA_MANAGEMENT passare il puntatore ad un oggetto [cntnrX] con una precisa interfaccia
            - l'istanziazione dell'oggetto [cntnrX] comporta il passaggio di un puntatore ad un buffer di dati

    - shmManager
        - note
            - non si vuole che il modulo [shm] sia a conoscenza dei moduli relativi all'interfaccia grafica [tui]
            - i moduli [shm] DEVONO essere INDIPENDENTI dai moduli [tui] in modo diretto ed indiretto
        - dipendenze
            - ==> dty
                - ==> dtyIntfcTui
        - pensare ad una applicazione/finestra che visualizza i dati di elementi/moduli che si vuole siano indipendenti dai moduli [tui]
            - quindi si dovrebbe avere un modulo [tui] ad esempio dal nome
                - [tuiFnctShmProx]
                    - questo modulo dipenderà naturalmente dai moduli [shm]
                        - i moduli [shm] sono moduli propri delle piattaforme di simulazione [mac]/[windows]/[linux]
                - bisogna pensare a dei moduli [tui] di più alto livello in cui c'è una dipendenza da altri moduli
                    - nel caso dei moduli [shm] che riguardano la piattaforma si può usare un nuovo modulo radice [debug], quindi
                        - [mpfw_code_libs_fw2_sdk_mac_debug]
                            - ==> [mpfw_code_libs_fw2_sdk_mac_ext]
                        - [mpfw_code_libs_fw2_sdk_mac_debug]
                            - [tui]
                                - [debug]
                                    - [mac]
                        - [mpfw_code_libs_fw2_tui]
                            - [base]
                                - [cplt]
                                - [fnct]
                                - [grph]
- il modulo [mpfw_code_libs_sdk_mac_ext] dovrebbe essere rinominato in
    - [mpfw_code_libs_fw2_sdk_mac_ext]

---

Sunday, 2nd March 2025

- gestione delle librerie software
    - ci sono tre modalità
        - compilazione singola
            - ogni libreria ha la sua directory di build
        - compilazione come sotto progetto di un progetto più grande
            - la directory di build della libreria è una sotto directory della directory di build del progetto più grande


---

Tuesday, 25th February 2025

- gestione delle dipendenze
    - distinguere le dipendenza da
        - micro
            - impostazione del clock
            - impostazione degli interrupt del timer
        - motherboard
            - impostazione dei pin per 
                - ingressi digitali/analogici
                - canali di comunicazione
                    - usart
                    - i2c
                    - spi
                    - etc.


---

Tuesday, 25th February 2025


- gestione dell'hardware attarverso i modulio tui
    - i moduli [tuiFnct] dovendo essere totalmente indipendenti da librerie legate alla piattaforma devono fare riferimento, devono poter lavorare con le interfacce
        - si dovranno quindi creare delle opportune interfacce
            - una per ciscuna tipologia di hardware
                - digital pin port
                - analogic pin port
                - communication channel
                    - spi
                    - usart
                    - i2c
                    - etc.
- istanze del modulo [mcuUSART]/[mcuCom] dovrebbero poter usare più tipologie di canali
    - usart
    - spi
    - i2c
    - wireless
        - wifi
        - bluetooth
        - 433 Mhz
        - 866 Mhz
        - ethernet
        - etc.
    - quindi il modulo [mcuUSART] forse è più corretto rinominarlo come [mcuCom]

---

Tuesday, 18th February 2025

- gestione dei puntatori degli oggetti [tuiGrph]
    - si potrebbe definire tutte le istanze degli oggetti [tuiGrph] a monte 

---

Monday, 17th February 2025

- se si vuole creare un istanza di un oggetto (A) all'interno di un altro oggetto (B)
    - l'istanza di (A) dovrà avere un nome che dipenda dal nome dell'istanza dell'oggetto (B)
        - il nome di un oggetto a livello globale è costituito dal nome della classe di cui è istanza e dal proprio nome

- pensare anche alle strutture annidate dei moduli [tuiCplt]
    - pensare ai due moduli
        - [tuiFnctRealCplx3McuUsart]
            - [tuiFnctRealUnit1FormattedStringCntnr]
- gli elementi [tui] sono divisi in tre differenti librerie
    - livello astratto
        - dipendenza solo dalle struttire dati ovvero i moduli [dty]
    - livello reale
        - dipendenza dai [wrapper] e quindi dai [driver]
        - questo livello e suddiviso 

- [tuiCplt]
    - [tuiGrphReal]
        - [platform]/[SDK]
            - [tuiGrphAbst]
                - [dtyIntfc]
    - [tuiFnct]
        - [tuiFnctRealUnit]
            - [tuiFnctAbstUnit]
                - [dtyIntfc]
        - [tuiFnctRealCplx]
            - [tuiFnctRealUnit]
                - ...

- i moduli [tuiCplt] possono essere implementati in due modi diversi
    - attraverso [macro_define]
    - attraverso classi derivate dalla coppia di moduli [tuiGrphReal]/[tuiFnctReal]
- i moduli [tuiFnct] ed in particolar modo mi riferisco ai moduli [tuiFnctRealCplx] lavorano solo sui puntatori dei moduli [tuiGrph] e non sulle loro istanze/reference
    - si veda come esempio il modulo [tuiFnctRealUnit3McuUsart]
        - questo modulo dovrebbe essere rinominato come [tuiFnctRealCplx3McuUsart]
            - i moduli [tuiFnctRealCplx] sono quesi moduli che nella loro implementazione gestiscono 
    - le istanze dei moduli [tuiGrph] gli vengono passate dai moduli [tuiCplt] al momento della istanzizione di questi ultimi

---

Sunday, 16th February 2025

dtyCntnr1StreamList_t   (p_pBuf, p_bufSize, g_initUsartTextCntnr, sizeof(g_initUsartTextCntnr), &g_unit, &g_graphic)


---

Saturday, 15th February 2025

- la definzione dei puntatori agli oggetti [tui] è identica per tutti quindi si può usare una sola define

---

Tuesday, 11th February 2025

- pensare alla simulazione dei tasti di un sistema embedded
    - i tasti dovrebbero essere degli elementi [tui] non selezionabili che possono interagire solo con il clock del mouse oppure essere associati direttamwente ad alcuni tasti della tastiera come FRECCIA SU/GIU/DX/SX

- tipologie di oggetti [tui]
    - [tuiGrph]: oggetti grafici
    - [tuiFnct]: oggetti funzionali
- le due tipologie di oggetti [tui] agiscono insieme e uno non può svolgere il suo compito se non è associato all'altro
    - ovvero l'oggetto [tui] compelto e operativo è una coppia costituita da un oggetto grafico ed uno funzionale
        - gliu oggetti funzionali sono totalmente indipendenti dall'hardware quindi non hanno alcuna dipendenza dai moduli [wrapper]/[driver]
        - gli oggetti grafici hanno due livelli
            - livello astratto: indipendente dall'hardware
            - livello concreto/reale: dipendente dall'hardware/piattaforma quindi dai moduli [wrapper]/[driver]
                - i moduli [wrapper] fanno da ponte tra i moduli dell'ambiente [mpfw]/[fw2] e le librerire [sdk] fornite dal costruttore dei microcontroller o della piattaforma di simulazione (quindi dei sistemi operativi [mac]/[linux]/[window] o altro)
- gli oggetti [tui] compelti possono essere suddivisi nelle seguwenti categorie
    - [window]/[wind]
        - sono quei moduli che contengono altri oggetti [tui]
            - la lista di oggetti [tui] è fornita a livello applicativo quindi fa parte dell'applicazione specifica
            - non c'è interazione con gli oggetti [tui] figli
            - questo modulo permette solo di navigare sulla lista degli oggetti figli è un semplice contenitore, infatti ...
            - il modulo funzionale associato è un modulo [container] ovvero un istanza della classe [tuiFnctReal2Cntnr]
    - [container]/[cntr]
        - sono quei moduli che contengono sequenze di oggetti [no-tui] sotto forma di array o buffer di dati strutturati secondo uno specifico (dipendente da una tipologia di applicazioni e che possono essere inseriti in librerie specifiche) protocollo
    - [complex]/[cmpx]
        - sono quei moduli che contengono altri oggetti [tui]
        - la lista di oggetti [tui] è fissa ovvero è impostata a livello indipendente dalla applicazione e quindi per istanziare l'oggetto non cè bisogno di fornirla, ce l'ha lui al suo interno, è una parte della sua implementazione
        - in questo caso c'è interazione con gli oggetti figli, in particolare legge ionformazioni da essi o imposta i parametri a seconda delle sistuazioni e dei compiti che deve svolgere questo elemento complesso
        - questo modulo è un [container] con funzioni estese, non solo permette la navigazione tra i suoi elementi ma li fa interagire insieme, non ha caso ...
        - il moduolo funzionale associato è un istanza di una classe derivata dalla classe [tuiFnctReal2Cntnr]
    - [unit]/[unit]
        - sono quei moduli base che non contengono altri moduli, infatti ...
        - il loro modulo funzionale associato non deriva dalla classe [tuiFnctReal2Cntnr]
        - tipicamente sono 

---

Wednesday,  5th February 2025

- rinominare
    - [dtyCntnr1ArrayList] in [dtyCntnr1ArrayTuiList]
    - [dtyCntnr1ArrayMap] in [dtyCntnr1ArrayTuiMap]
    - [dtyCntnrBufferShmProx] in [dtyCntnr1ArrayDataList] viene dato un array di una struttura definita dall'utente
    - [dtyCntnr1StreamList] in [dtyCntnr1StreamStringList] 
        - nell'istanziazione viene dato un buffer di [uint8_t]
        - all'oggetto [tuiFnct] viene passato un parametro stringa ovvero [dtyString]
        - accetta/gestisce un solo tipo di stream inoltre "comunica" con il modulo [tui] attarverso la struttura dati di una stringa [dtyString]
    - [dtyCntnr1StreamList] in [dtyCntnr1StreamDataList]
        - nell'istanziazione
            - viene dato un buffer di [uint8_t]
            - viene data la struttura dati dello stream ovvero
                - un modulo che ha come interfaccia [dtyUnit0StreamIntfc]
                - ad esempio
                    - [dtyUnit2StreamAppX]
        - all'oggetto [tuiFnct] viene passato un parametro [void*]
            - l'oggetto [tuiFnct] è associato anche alla struttura dati dello stream
        - questo modulo lavora solo con interfacce/classi astratte quindi è molto generale, può accettare tutti i tipi di stream ovvero tutti i mdouli ch hanno l'interfaccia [dtyUnit0StreamIntfc]


- gestione moduli [dty]
    - [dty] moduli indipendenti
    - [dtyX] moduli dipendenti da altri moduli e che quindi non possono essere collocati nello stesso modulo radice dei moduli [dty]
        - questi moduli conviene che vengano inseiriti nei moduli radice in cui si trovano i moduli da cui essi dipendono

- schema di funzionamento/configurazione dei container e della visualizzazione del loro contenuto
    - elementi in giuoco
        - ci sono due moduli [tui]
            - uno che riguarda la gestione del buffer degli elementi
                - uno degi compiti principali e quello di gestire la modalità di navigazione tra gli elementi
                - è un istanza del modulo [tuiFnctRealUnit2Cntnr]
                - [dipendenze]
                    - questo modulo richiede per la sua istanziazione il puntatore ad un modulo derivato dalla classe astratta [dtyCntnr0Base]
            - l'altro che riguarda il singolo elemento
                - gestisce la visualizzazione del singolo elemento
        - ci sono due moduli [dty]
            - uno che si riferisce/che è associato al buffer degli elementi
                - deriva da [dtyCntnr0Base]
                    - in particolare il modulo [dtyCntnr1StreamList]
                        - può essere utilizzato in modo generico ma accetta solo moduli [tui] che abbiano l'interfaccia [dtyIntfcUiData]
                - moduli [dtyCntnr]
                - questi moduli gestiscono le singole tipologie di contenitori e la loro modalità visualizzazione
                    - tipologie di contenitori sono
                        - [array]
                            - [dtyCntnr1ArrayTuiList]
                            - [dtyCntnr1ArrayTuiMap]
                            - [dtyCntnr1ArrayDataList]
                        - [stream]
                            - [dtyCntnr1StreamList]
                            - [dtyCntnr1StreamAppXList]
                            - [dtyCntnr1StreamStringList]
                    - modalità di visualizzzione
                        - [map]
                            - come elementi di una mappa che possono essere posizionati senza nessun ordine all'interno di un quadrato
                        - [list]
                            - come elmenti di una lista che sono posizionati in verticale uno di seguito all'altro
                - [dipendenze]
                    - questi moduli per lavorare hanno bisogno di avere il puntatore ad un oggetto [tui] derivato dalla classe  [dtyIntfcUiData] o più nello specifico [dtyIntfcUiStream]
                        - in quest'ultimo caso non si avrà il modulo [dtyCntnr1StreamList]
                        - l'interfaccia [dtyIntfcUiData] ha due scopi
                            - trasmettere al modulo [tuiUnit] il puntatore ai dati da visualizzare
                                - i dati possono essere trasmessi in modo del tutto generale attraverso un puntatore a void [void*]
                                - oppure usando una struttura dati specifica
                                    - ad esempio
                                        - [dtyUnit2StreamAppX]
                                    - in questo caso anche 
                                        - il modulo container dovrà essere specifico ovvero
                                            - [dtyCntnr1StreamAppXList]
                                        - l'interfaccia del modulo [tuiUnit] dovrà essere specifica
                                            - [dtyIntfcUiStreamAppX]
                                        - e il suo modulo derivato [tuiUnit]
                                - il modulo [tuiUnit] 
                                    - potrà essere generico [tuiFnctRealUnit1StreamStd]/[tuiFnctRealUnit1Stream]
                                        - in questo caso il blocco dati verrà visualizzato come una singola stringa
                                    - oppure specifico [tuiFnctRealUnit1StreamAppx]
                                        - in questo caso il blocco dati verrà analizzato in dettaglio e i dati in esso contenuti verranno visualizzati specificandone il nome 
                            - dare il comando di aggiornamento della visualizzazione dei dati al modulo [tui]
            - l'altro che si riferisce alla singola unità, al singolo elemento
                - deriva da [dtyUnit0Base]
                - moduli [dtyUnit]
                - è associato ai tipi di dati 
                    - elementari 
                        - come gli interi (le stringhe sono considerate dei contenitori)
                    - definiti dall'utente 
                        - ad esempio
                            - le strutture degli header/dati degli stream
                            - la gestione dei processi per la memoria condivisa

---

tuesday,  4th February 2025

- per differenziare la modalità di impacchettamento dai dati è bene creare due strutture separate una per l'header e l'altra per i dati

- l'idea è quella in cui
    - il modulo [dtyCntnrStreamList] gestisce qualunque tipo di protocollo di streaming 
        - quindi userà semplicemente le interfacce
    - il protocollo di streaming specifico, dipendente dall'applicazione, verrà rappresentato da tre moduli
        - modulo [manager]/[dtyAppXStream]
            - insieme con il modulo [header] definisce la modalità di impacchettamento
        - modulo [header]/[dtyAppXStreamHeader]
            - insieme con il modulo [manager] definisce la modalità di impacchettamento
        - modulo [dati]/[dtyAppXStreamData]
            - porta le informazioni
        - [dtyIntfcStream]
    - nomi
        - stream = block1 + block2 + .... + block(n) + ...
        - block = header + data
        - header
        - data

---

monday, 3rd February 2025

- la struttura degli oggetti stream può essere inizializzata dandogli il puntatore allo stream buffer
    - all'oggetto stream dovrebbe essere associato un [idObjStream]
    - gli viene dato il puntatore all'buffer stream ed in cambio si possono richiedere informazioni sui vari blocchi
        - getBlockNext()/Prev()
        - getBlock(idObjStream)
        - getBlockIdCurrent()
        - getBlockDataBubfferPtr
        - getBlockType
        - getLastBlock
    - oppure eseguire delle azioni
        - goToBlock(idObjStream)
        - addBlock

- il modulo [dtyCntnrStream] gestisce oggetti o meglio una lista di oggetti del tipo [dtyObjStream]
    - il modulo [dtyObjStream] verrà gestito anche dai moduli [tui] per la loro visualizzazione in particolare i sui moduli reali da lui derivati
        - il modulo [dtyObjStream] è un interfaccia o classe astratta
        - possibili oggetti specifici, classi derivate di questa classe astratta, possono essere i moduli
            - [dtyObjStreamNetwork]
            - [dtyObjStreamStored]
    - il modulo [dtyCntnrStream] può lavorare sull'interfaccia ovvero sul modulo [dtyObjStream] non ha bisogno delle classi reali specifiche
    - cosa diversa invece per i moduli [tui] che devono visualizzare tutti i dettagli degli oggetti stream 
    - e quindi i moduli [tui] devono lavorare con il oggetti specifici
        - in questo caso per ogni modulo [dtyObjStream] specifico si avra il corrispondente modulo [tui]
            - questi moduli [tui] dovranno implementare le interfacce/funzioni virtuali
                - [initObjStream] / [initFnctData]
                - [updTuiUnitDepOnObjStream] / [updTuiUnitDepOnFnctData]
    - considerare anche che gli oggetti stream si differenziano per 
        - [modalità] di "impacchettamento"
        - [informazione] che portano/contengono


- gestione moduli [dty] e [tuiFnctUnit]
    - stream [stored_stream]
        - elementi base
            - [header]
                - [source]
                - [destination]
                - [checksum]
                - [data_length]
                - [data_pointer]
                - [properties]
            - [data]
    - [protocollo] / [network_stream]
        - elementi base
            - [header]
                - [start_code]
                - [source]
                - [destination]
                - [type]
                - [data_length]
            - [footer]
                - [checksum]
            - [data]
    - stringhe formattate
        - elementi base
            - [string_pointer]
            - [string_format_info]

- [dtyCntnrStreamNetwork]
    - [dtyStructStreamNetwork]
- [dtyCntnrStreamStored]
    - [dtyStructStreamStored]
- [dtyCntnrStreamStoredString]
    - [dtyStructStreamStored]

- i moduli [dtyStructStream] avranno un interfaccia comune per
    - inizializzare la struttura
        - [initHeader]
            - fornire il puntatore all'inizio dello stream buffer affinchè la struttura dati possa impostare il puntatore al primo header
    - navigare da un header all'altro
        - [getHeaderNext]
        - [getHeaderPrev]
    - ottenere il puntatore al buffer dei dati
        - [getDataPtr]

- [dtyStructStreamHeader]
- [dtyStructStreamData]

---

monday, 27th January 2025


- [tuiGraphicUnit_t] & [dtyCntnr]
    - bNotNull
        - tuiGraphicAbstract:               define & implemented
    - init
        - tuiGraphicProcessInterface:       virtual def
    - initRelCoordS
        - tuiGraphicCoord_t:                define & implemented
    - updParamsAfterParentMod
        - tuiGraphicCoord_t:                virtual def
    - getDimH
        - tuiGraphicCoord_t:                virtual def
    - bMouseClickInsideBounds
        - tuiGraphicCoord_t                 define & implemented
    - incRelCoordY
        - tuiGraphicCoord_t:                define & implemented
    - display
        - tuiGraphicDisplayInterface        virtual def
    - selectByMouse
        - tuiGraphicState                   virtual def
    - getDistanceFromBound
        - tuiGraphicCoord_t                 define & implemented
    - deselctBackNselect
        - tuiGraphicState                   define & implemented
    - loop
        - tuiGraphicProcessInterface:       virtual def
    - bVisibleCompletely
        - tuiGraphicCoord_t                 define & implemented

    - bNotNull
        - tuiGraphicAbstract:               define & implemented
    - initRelCoordS
        - tuiGraphicCoord:                define & implemented
    - updParamsAfterParentMod
        - tuiGraphicCoord:                virtual def
    - getDimH
        - tuiGraphicCoord:                virtual def
    - bMouseClickInsideBounds
        - tuiGraphicCoord                 define & implemented
    - incRelCoordY
        - tuiGraphicCoord:                define & implemented
    - getDistanceFromBound
        - tuiGraphicCoord                 define & implemented
    - bVisibleCompletely
        - tuiGraphicCoord                 define & implemented
    - display
        - tuiGraphicDisplayInterface        virtual def
    - selectByMouse
        - tuiGraphicState                   virtual def
    - deselctBackNselect
        - tuiGraphicState                   define & implemented
    - init
        - tuiGraphicProcessInterface:       virtual def
    - loop
        - tuiGraphicProcessInterface:       virtual def

- interfaces
    - [dtyCntnrUnit]/[tuiGraphicAbstract]
    - [dtyProcess]/[tuiGraphicProcessInterface]
    - [dtyUiState]/[tuiGraphicState]
    - [dtyUiCoord]/[tuiGraphicCoord]

    - [tuiGraphicUnit]
        - [tuiGraphicDriver]
            - [tuiGraphicState]
                - [tuiGraphicCoord]
                    - [dtyGrphUiAbstractUnit]
                        - [dtyIntfcCntnrUnit]
                        - [dtyIntfcProcess]
                        - [dtyIntfcGrphUiState]
                        - [dtyIntfcGrphUiCoord]
                        - [dtyIntfcGrphUiDispl]
                        - [dtyIntfcGrphUiInOut]
                    - [dtyFnctUiAbstractUnit]
                        - [dtyFnctUiEvent]
                            - [key]
                            - [mouse]
                        - [dtyFnctUiCntnr]
                        - [dtyFnctUi]
[dtyFnctUiEvent]/[tuiUnitEvent]
[dtyFnctUiDsply]/[tuiUnitDisplayInterface]
[dtyFnctUiState]/[tuiUnitStateInterface]
[dtyFnctUiProxs]/[tuiUnitProcessInterface]
[dtyFnctUiCntnr]/[tuiUnitCntnrInterface]

[dtyGrphUiProxs]/[tuiGraphicProcessInterface]
[dtyGrphUiCoord]/[tuiGraphicCoord]
[dtyGrphUiState]/[tuiGraphicState]
[dtyGrphUiDsply]/[tuiGraphicDisplayInterface]
[dtyGrphUiInOut]/[tuiGraphicDriverInOutInterface]

[dtyIntfcUiCntnr]/[tuiUnitCntnrInterface]
[dtyIntfcUiProxs]/[tuiGraphicProcessInterface]
[dtyIntfcUiCoord]/[tuiGraphicCoord]
[dtyIntfcUiState]/[tuiGraphicState]
[dtyIntfcUiDsply]/[tuiGraphicDisplayInterface]
[dtyIntfcUiInOut]/[tuiGraphicDriverInOutInterface]


- modules list
    libs_sdk_mac_ext || libs_fw2_wrapper_sdk => sdkPortDef.cpp        

    libs_sdk_mac_ext    => shmBase.cpp     
    libs_sdk_mac_ext    => shmMcuPinPort.cpp     
    libs_sdk_mac_ext    => shmMcuUsart.cpp       
    libs_sdk_mac_ext    => shmManager.cpp        

    libs_fw2_wrapper_sdk    =>  mcuBase.cpp
    libs_fw2_wrapper_sdk    =>  mcuPinPort.cpp        
    libs_fw2_wrapper_sdk    =>  mcuPinPort2.cpp        
    libs_fw2_wrapper_sdk    =>  mcuUsart.cpp          
    libs_fw2_wrapper_sdk    =>  ## mcuUsartTbl.cpp          
    libs_fw2_wrapper_sdk    =>  ## mcuUsartManager.cpp
    libs_fw2_wrapper_sdk    =>  mcuManager.cpp

    libs_fw2_sdk    =>  pphButton.cpp
    libs_fw2_sdk    =>  pphLed.cpp
    libs_fw2_sdk    =>  pphRely.cpp
    libs_fw2_sdk    =>  pphSwitch.cpp
    libs_fw2_sdk    =>  pphWired.cpp
    libs_fw2_sdk    =>  pphUsart.cpp
    libs_fw2_sdk    =>  pphManager.cpp
    
    main_<app_name>/common          =>  pphManagerAppTbl.cpp
    main_<app_name>/<platform>      =>  pphManagerSvcTbl.cpp

    - le definizioni si possono suddividere tra quelle associate all'applicazione [app] e quindi comune a tutte le piattaforme e quelle associaate l service [svc] e quindi specifiche per ciascuna piattaforma
    main_<app_name>/common          =>  pphDef_appLeds.cpp
    main_<app_name>/<platform>      =>  pphDef_svcLeds.cpp
    main_<app_name>/<platform>      =>  pphDef_Buttons.cpp
    main_<app_name>/<platform>      =>  pphDef_Mod1.cpp


- aspetti da migliorare
    - i moduli
        - [dtyCntnrArrayList]
        - [dtyCntnrArraySet]
        - [dtyCntnrBufferMmyInt32]
        - ...
    - dovrebbero essere indipendenti dal modulo [tuiDrvGraphic]
    - mentre possono essere dipendenti da un modulo [ui] astratto da cui dipenderanno sia i moduli [dty] sia i moduli [tui]
    - il modulo [ui] astratto può essere inserito in un modulo radice [mpfw_fw2_libs_types_defs] oppure anche nel modulo radice [mpfw_fw2_libs_dty] dove [dty] sta per [Data_utiliTY] ed essere chiamato [dtyUiAbstract]
    - stessa cosa dicasi per i moduli associati ai protocolli
        - in questo caso si dovrebbero definire delle funzioni standard ovvero un interfaccia comune a tutti i protocolli
            - [dtyPrtclAbstract] potrebbe essere il nome da associare ad un interfaccia comune per i vari protocolli
                - gli elementi base in un protocollo sono
                    - [headerBlock]
                        - [getDataPtr]
                        - [getDataLenght]
                        - [getIdBlock]/[getIdSource]/[getAddrSource]
                        - [getIdDestination]/[getAddrDestination]
                        - [getChksum]
                        - [getHeaderNext]
                    - [footerBlock]
                    - [dataBlock]
    - pensare anche ad un modulo [dty] per la gestione della formattazione di stringhe
        - [dtyFrmtStr] potrebbe essere il suo nome
            - questo modulo/classe avra le informazioni su come formattare una stringa quindi
                - [colore]
                - [evidenziazione]
                    - [bold]
                    - [italic]
                    - [underline]
                - [justify]
                - etc.
    - il debug
        - sfruttare i moduli [dtyCntnr] per poter inserire del codice di debug e tale per cui sia agevole disabilitarlo ed eliminarlo dal codice da inseire nel firmware


    - dtyBaseArray.cpp
        - dtyBuffer.h
        - uyTypesDefs.h / [dtyTypesDefs.h]
    - dtyBaseUnit.cpp / [dtyMmyBase.cpp]
        - uyTypesDefs.h / dtyTypesDefs.h
    - dtyCntnrArrayList.cpp / [tuiDtyCntnrArrayList.cpp]
        - dtyCntnrBaseUnit.cpp
    - dtyCntnrArraySet.cpp / [tuiDtyCntnrArraySet.cpp]
        - dtyCntnrBaseUnit.cpp
    - dtyCntnrBaseUnit.cpp
    - dtyCntnrBufferMmyInt32.cpp
    dtyCntnrBufferShmProx.cpp
    dtyCntnrStreamList.cpp
    dtyCntnrStreamOfFormattedString.cpp
    dtyMmyBool.cpp
    dtyMmyInt32.cpp
    dtyProtocolData.cpp
    dtyString.cpp
    dtyTuiGraphic.cpp
    dtyUint8.cpp

    tuiDrvGraphic.cpp
    tuiGraphicCoord.cpp
    tuiGraphicState.cpp
    tuiGraphicAbstract.cpp
    tuiGraphicAppMain.cpp
    tuiGraphicUnit.cpp
    tuiGraphicUnitRoot.cpp
    tuiGraphicUnitWin.cpp
    tuiGraphicUnitBase.cpp
    
    tuiUnitAbstract.cpp
    tuiUnitButton.cpp
    tuiUnitCntnrAbstract.cpp
    tuiUnitCntnrList.cpp
    tuiUnitEbox.cpp
    tuiUnitDebug.cpp
    tuiUnitFormattedString.cpp
    tuiUnitFormattedStringCntnr.cpp
    tuiUnitListAbstract.cpp
    tuiUnitListDebug.cpp
    tuiUnitMmyInt.cpp
    tuiUnitMcuDgtInOut.cpp
    tuiUnitMcuUsart.cpp
    tuiUnitProtocolData.cpp
    tuiUnitSet.cpp
    
    tuiManager.cpp
    tuiManagerApp.cpp

    vhwManager.cpp
    vhwMain.cpp


---

Saturday, 25th January 2025

- pensare a come inserire la gestione dell'hardware reale/virtuale nel [krThread] in modo da uniformare la gestione tra piattaforma virtuale e reale
    - ci si può focalizzare sul modulo [pph] questo poi a cascata gestirà i moduli [mcu] e [shm], quest'ultimo in caso  di pattaforma mac
        - i moduli [pph] sono presenti in entrambe i tipi di piattaforma , sia in quella reale che in quella virtuale,

- tracciare il flusso delle chiamate 
    - [krInitStaticManager::LoopOnUnits()]
        - vengono chiamate le funzioni inserite negli array
            - [krInitStaticPtrArray]
                - i suoi elementi sono funzioni ovvero elementi del tipo [InitFunction_t]
                - questo array è definito nel modulo radice [fw2_wrapper_core]
                    - vedere il file .h [krInitStaticTbl.h]
                - la sua implementazione, ovvero l'inserimento del suo contenuto, avviene nello stesso modulo radice
                    - vedere il file .cpp [krInitStaticTbl.cpp]
                    - il suo contenuto è rappresentato da funzioni che si trovano all'interno del proprio modulo radice ovvero [fw2_wrapper_core]
            - [krInitStaticPtr2Array]
                - è un array di array
                - i suoi elementi sono array del tipo [InitFunction_t*] o
                - questo array è definito nel modulo radice [fw2_wrapper_core]
                - mentre la sua implementazione, ovvero il suo contenuto, avviene a livello applicativo nel modulo radice [main]
                    - questo perchè il suo contenuto è costituito da array che sono definiti al di fuori del modulo [fw2_wrapper_core] e che non gli è dato di conoscere per il suo basso livello di visione (si rammento che è di un un solo livello superiore ai driver/sdk)
            - quindi ogni modulo radice [mpfw_] ha array del tipo [InitFunction_t*]
                - i puntatori a questi array verranno inseriti nell'array di array [krInitStaticPtr2Array] a livello applicativo nel modulo radice [main]
                - questi array sono definiti nelle folder/directory [tb]
            - tutti i moduli che gestiscono array associati alle [istanze] dei loro sub-moduli [unit] avranno una directory [tb] dove definiranno questi array
                - inoltre se ci sono dei moduli a livello più alto che definiscono questi stessi array (si rammenta che questi array forniscono un servizio come ad esempio quello di [init] o di  una macchina a stati [stateMachine]) ci sarà anche
                    - una directory [stateMachine]  nel modulo radice [main] sotto la directory [tb/tb] in cui si definirà l'array di questi array come nel caso degli array visti sopra associati al servizio di [init]

- i moduli [tui] sono sullo stesso livello dei moduli [timer] anche se di questi ultimi possono usare il servizio e quindi ne dipendono, stesso dicasi per i moduli [pph] anche questi possono usare il servizio [timer]


---

Friday, 24th January 2025


- integrazione dei moduli [pph] & co, [tui] & [dty] nei moduli radice [mpfw]
    - come prima cosa si devono classificare i vari moduli in modo da collocarli negli appropriati moduli radice
        - suddividere i moduli [tui] in [extended]/[plus] e in [standard]/[minimal]
            - [plus] sono quelli utilizzati per la [simulazione] e vengono compilati nelle sole piattaforme di simulazione che al momento si riducono ad una unica quella [mac]/[-nix]
            - [minmal] sono quelli utilizzati nel [firmware] che quindi verranno compilati per tutte le piattaforme
    - rivedere anche il modulo radice [main] in particolare di come impostare il file/modulo entry [main.cpp] per la piattaforma di simulazione 

- gestione files cmake
    - gestione tabelle all'interno di tabelle ovvero tabelle annidate
        - si vedano
            - main/mpfw_code_main_tst_20240619main/wsp/cmake/project/common/v_02/public/src_ver_modules/apps/mpfw_code_apps_tst_20240619app/set_class_src_ver.cmake
            - main/mpfw_code_main_tst_20240619main/src/common/tb/tb/kr/krThread/v_01/krThreadTbl.cpp
            - apps/mpfw_code_apps_tst_20240619app/src/tb/kr/krThread/v_03/app/krThreadTbl.cpp
        - queste sono tabelle che possono essere compilate all'interno dei propri moduli radice 
            - ma che vengono inserite all'interno di un altro modulo in particolare il modulo radice [main]

- gestione fase di inizializzazione del micro reale/virtuale
    - dove inserire il loop del [service]/[debug] ovvero i moduli [tui] associati alla simulazione
    - gestione dei thread reali/virtuali
    - gestione interrupt

    libs_sdk_mac_ext || libs_fw2_wrapper_sdk => sdkPortDef.cpp        

    libs_sdk_mac_ext    => shmBase.cpp     
    libs_sdk_mac_ext    => shmMcuPinPort.cpp     
    libs_sdk_mac_ext    => shmMcuUsart.cpp       
    libs_sdk_mac_ext    => shmManager.cpp        

    libs_fw2_wrapper_sdk    =>  mcuBase.cpp
    libs_fw2_wrapper_sdk    =>  mcuPinPort.cpp        
    libs_fw2_wrapper_sdk    =>  mcuPinPort2.cpp        
    libs_fw2_wrapper_sdk    =>  mcuUsart.cpp          
    libs_fw2_wrapper_sdk    =>  ## mcuUsartTbl.cpp          
    libs_fw2_wrapper_sdk    =>  ## mcuUsartManager.cpp
    libs_fw2_wrapper_sdk    =>  mcuManager.cpp

    libs_fw2_sdk    =>  pphButton.cpp
    libs_fw2_sdk    =>  pphLed.cpp
    libs_fw2_sdk    =>  pphRely.cpp
    libs_fw2_sdk    =>  pphSwitch.cpp
    libs_fw2_sdk    =>  pphWired.cpp
    libs_fw2_sdk    =>  pphUsart.cpp
    libs_fw2_sdk    =>  pphManager.cpp
    
    main_<app_name>/common          =>  pphManagerAppTbl.cpp
    main_<app_name>/<platform>      =>  pphManagerSvcTbl.cpp

    - le definizioni si possono suddividere tra quelle associate all'applicazione [app] e quindi comune a tutte le piattaforme e quelle associaate l service [svc] e quindi specifiche per ciascuna piattaforma
    main_<app_name>/common          =>  pphDef_appLeds.cpp
    main_<app_name>/<platform>      =>  pphDef_svcLeds.cpp
    main_<app_name>/<platform>      =>  pphDef_Buttons.cpp
    main_<app_name>/<platform>      =>  pphDef_Mod1.cpp


- aspetti da migliorare
    - i moduli
        - [dtyCntnrArrayList]
        - [dtyCntnrArraySet]
        - [dtyCntnrBufferMmyInt32]
        - ...
    - dovrebbero essere indipendenti dal modulo [tuiDrvGraphic]
    - mentre possono essere dipendenti da un modulo [ui] astratto da cui dipenderanno sia i moduli [dty] sia i moduli [tui]
    - il modulo [ui] astratto può essere inserito in un modulo radice [mpfw_fw2_libs_types_defs] oppure anche nel modulo radice [mpfw_fw2_libs_dty] dove [dty] sta per [Data_utiliTY] ed essere chiamato [dtyUiAbstract]
    - stessa cosa dicasi per i moduli associati ai protocolli
        - in questo caso si dovrebbero definire delle funzioni standard ovvero un interfaccia comune a tutti i protocolli
            - [dtyPrtclAbstract] potrebbe essere il nome da associare ad un interfaccia comune per i vari protocolli
                - gli elementi base in un protocollo sono
                    - [headerBlock]
                        - [getDataPtr]
                        - [getDataLenght]
                        - [getIdBlock]/[getIdSource]/[getAddrSource]
                        - [getIdDestination]/[getAddrDestination]
                        - [getChksum]
                        - [getHeaderNext]
                    - [footerBlock]
                    - [dataBlock]
    - pensare anche ad un modulo [dty] per la gestione della formattazione di stringhe
        - [dtyFrmtStr] potrebbe essere il suo nome
            - questo modulo/classe avra le informazioni su come formattare una stringa quindi
                - [colore]
                - [evidenziazione]
                    - [bold]
                    - [italic]
                    - [underline]
                - [justify]
                - etc.
    - il debug
        - sfruttare i moduli [dtyCntnr] per poter inserire del codice di debug e tale per cui sia agevole disabilitarlo ed eliminarlo dal codice da inseire nel firmware


    - dtyBaseArray.cpp
        - dtyBuffer.h
        - uyTypesDefs.h / [dtyTypesDefs.h]
    - dtyBaseUnit.cpp / [dtyMmyBase.cpp]
        - uyTypesDefs.h / dtyTypesDefs.h
    - dtyCntnrArrayList.cpp / [tuiDtyCntnrArrayList.cpp]
        - dtyCntnrBaseUnit.cpp
    - dtyCntnrArraySet.cpp / [tuiDtyCntnrArraySet.cpp]
        - dtyCntnrBaseUnit.cpp
    - dtyCntnrBaseUnit.cpp
    - dtyCntnrBufferMmyInt32.cpp
    dtyCntnrBufferShmProx.cpp
    dtyCntnrStreamList.cpp
    dtyCntnrStreamOfFormattedString.cpp
    dtyMmyBool.cpp
    dtyMmyInt32.cpp
    dtyProtocolData.cpp
    dtyString.cpp
    dtyTuiGraphic.cpp
    dtyUint8.cpp

    tuiDrvGraphic.cpp
    tuiGraphicCoord.cpp
    tuiGraphicState.cpp
    tuiGraphicAbstract.cpp
    tuiGraphicAppMain.cpp
    tuiGraphicUnit.cpp
    tuiGraphicUnitRoot.cpp
    tuiGraphicUnitWin.cpp
    tuiGraphicUnitBase.cpp
    
    tuiUnitAbstract.cpp
    tuiUnitButton.cpp
    tuiUnitCntnrAbstract.cpp
    tuiUnitCntnrList.cpp
    tuiUnitEbox.cpp
    tuiUnitDebug.cpp
    tuiUnitFormattedString.cpp
    tuiUnitFormattedStringCntnr.cpp
    tuiUnitListAbstract.cpp
    tuiUnitListDebug.cpp
    tuiUnitMmyInt.cpp
    tuiUnitMcuDgtInOut.cpp
    tuiUnitMcuUsart.cpp
    tuiUnitProtocolData.cpp
    tuiUnitSet.cpp
    
    tuiManager.cpp
    tuiManagerApp.cpp

    vhwManager.cpp
    vhwMain.cpp


---

Thursday, 23rd January 2025

- gestione [usart]
    - <bool pphUsart_t::txBuff_send (uint8_t* p_pTxBuff, uint8_t p_txBuffSize) {>
        - questa funzione viene usata dal modulo [tui] oppure dal modulo [app]
            - la chiamata a questa funzione può avvenire iun qualunque funzione [evento] o [loop]
                - tipicamante avviene in una funzione associata ad un evento




- gestione [hardware]
    - gestione delle modalita [app] e [service]/[debug]/[simulation]
        - i componenti/moduli hardware quindi i moduli [pph] e [mcu] avranno comportamenti diversi a seconda che si imposti una modalità [app] oppure [service]
            - si pensi ad esempi ad i moduli [port] e [usart], in particolare [usart]


---

Wednesday, 22nd January 2025

- gestione [usart]
    - ricezione
        - il modulo [pphUsart] deve restituire il numero di byte ricevuto, in base al protocollo del messaggio
        - il buffer dove verranno memorizzati i dati è da capire chi lo debba definire
            - colui che usa il modulo [pph]
            - oppure
            - il modulo [pph] stesso
        - io propenderei per la seconda opzione in modo da rendere più snello l'uso del modulo [pph]
            - in questo caso però nella fase di inizializzazione  del modulo utilizzatore quindi il modulo [tui] si dovrà ottenere il puntatore al buffer
                - non ha senso chiedere il puntatore ogni volta che si deve visualizzare il buffer di ricezione, è sufficente impostarlo una sola volta ovvero nella fase di init oppure anche nel costruttore del modulo [tui]
        
        



---

Tuesday, 21st January 2025

- gestione [usart]
    - ricezione
        - periodicamente si controlla se è stato ricevuto qualche byte
            - dove?
                - nel [loop]/[body] del modulo 
                    - [tui] oppure nel modulo [app]
                    - oppure
                    - [app]
                    - oppure
                    - [pph]/[mcu]
                - io direi per il momento di usare il modulo [pph] che poi può essere usato a sua volta dai moduli [app]/[tui]
                    - il  modulo [pph] potrebbe essere anche il modulo che gestisce il protocollo di comunicazione
        - ogni byte ricevuto viene copiato in un buffer definito nel modulo [pph] (chiamiamolo [g_rxBuff])
        - quando il buffer è completato (questo dipende dal tipo di protocollo) la funzione del modulo [pph] [rxBufferReady] resituisce il valore true oppure il puntatore al buffer [pph:g_rxBuff]
            - la funzione [pph::rxBufferReady] viene continuamente controllata nel [loop] dei moduli [app]/[tui]
        - il puntatore al buffer [pph::g_rxBuff] viene dato alla funzione [g_recevingDataCntnr->add]/[dtyCntnrStreamOfFormattedString_t::add] che lo visualizza
    - trasmissione
        - un evento richiede che venga inviato un messaggio
            - come?
                - usando la funzione del modulo [pph] [send]
                    - verranno dati come parametri il puntatore al buffer che contiene il messaggio [tuiUnitUsart::g_sendingDataBuffer] e la lunghezza in bytedel messaggio
        - periodicamente si controlla lo stato del buffer di trasmissione [g_txBuff] fornito dal modulo [pph]
            - dove?
                - nel modulo [pph]
        - quando il buffer di trasmissione [pph::g_txBuff] è pieno
            - quale condizione?
                - semplicemente chiamando la funzione [pph::send] che nel suo corpo avrà un istruzione che impostato lo stato del buffer di trasmissione [pph::g_txBufferReady] a true
            - cosa si fa?
                - si inizia un loop non bloccante che ad ogni passo, equivalente ad ogni ciclo di [loop], invia un byte sul canale di comunicazione usando la funzione [mcu::tx_fifo_write] del modulo [mcuUsart]
                    - dove?
                        - nel modulo [pph]
                    - come?
                        - si dovrebbe tenere un contatore dei byte inviati quando uguaglia la lunghezza del messaggio ci si ferma
                        - quindi il buffer [pph::g_txBuff] rimarrà nello stato di pronto/ready fin quando il contatore di byte non eguaglia la lunghezza del messaggio poi verrà rersettato, ovvero
                            - al termine della procedura
                                - il contatore dei byte spediti verrà posto = 0
                                - [pph::g_txBufferReady] verrà posta a false


---

Sunday, 19th January 2025


- cose da fare
    - rivedere, migliorare il nome delle funzioni virtuali dei moduli [dtyCntnr]
    - fare un buffer di log per messaggi di debug

---

Sunday, 19th January 2025


- cose da fare
    - implementare i componenti [pphRelay]/[pphWired]
    - ordinare i file dei moduli in base a sezioni
    - implementare i moduli [usart]
        - [pphUsart]
        - [mcuUsart]
        - [shmUsart]
    - implementare il modulo/i moduli dei processi dell'applicazione ovvero il modulo/moduli [app]
        - ncessario per fare un test 
    - capire come distribuire tra i vari tra i modulio radice
        - [apps]
        - [main]
        - [libs]
            - [sdk]/[driver]
            - [wrapper]
            - [fw2]

---

Friday, 17th January 2025

- flusso delle chiamate per la funzione [loop]
    - [vhwManager_t::loop] from [vhwMain]
        - [tuiManager_t::body()]
            - [tuiGraphicUnitRoot_t::loop] -> [tuiManager_t::g_baseMainWin->loop()]
                - [tuiUnitSet_t::loop] -> 
                    - [tuiGraphicUnitBase_t]
                    - or
                    - [tuiGraphicUnitWin_t]
                        - [tuiUnitCntnrList_t]
                            - [dtyCntnrArraySet_t]
                                - [tuiGraphicUnitBase_t]
                                    - [tuiUnitCntnrList_t]
                                        - [dtyCntnrArraySet_t]
                                            - ...
                                        - or
                                        - [dtyCntnrArrayList_t]/[dtyTuiGraphic_t]
                                            - ...
                            - or
                            - [dtyCntnrArrayList_t]/[dtyTuiGraphic_t]
                                - [tuiGraphicUnitBase_t]
                                    - [tuiUnitCntnrList_t]
                                        - [dtyCntnrArraySet_t]
                                            - ...
                                        - or
                                        - [dtyCntnrArrayList_t]/[dtyTuiGraphic_t]
                                            - ...
        - [pphManager_t::body()]

- albero genealogico delle classi
    - [tuiUnitAbstract_t]
        - [tuiUnitCntnrAbstract_t]
            - [tuiUnitCntnrList_t]
        - [tuiUnitListAbstract_t]
            - [tuiUnitSet_t]

    - [tuiGraphicUnit_t]
        - [tuiGraphicUnitBase_t]
        - [tuiGraphicUnitRoot_t]
        - [tuiGraphicUnitWin_t]


---

Thursday, 16th January 2025


- gestione del componente [tuiUnitEbox]
    - analisi dei possibili stati
        - [use_case]
            - [primo_utilizzo]
            - [pressione_enter]
                - nel caso in cui
                    - [g_func] == [nullptr]
                        - azzerare il contenuto
                    - [g_func] != [nullptr]
                        - non fare niente al contenuto
                        - il contenuto verrà azzerato attraverso un comando dato dal proprietario della [g_func]
                        - un utilizzo è quello di usare il contenuto (,essaggio appena scritto) per inviarlo sul canale di comunicazione ad esempio
                            - quando è stato iniviata la stringa si può azzerare il contenuto del box
            - [perdita_del_focus]
                - quando il componente non gestisce più gli eventi a causa di 
                    - un click del mouse
                        - non cancellare il contenuto (la stringa che è stata scritta)
                        - quando torna il focus fare come se ninete fosse successo
                    - aver premuto il tasto home/inizio
                        - si potrebbe azzerare il contenuto e impostare lo stato in [init]/[new]

- implementare la funzione [loop] nel modulo [tuiUnitMcuUsart]


---

Tuesday, 14th January 2025

- albero genealogico dei moduli

- [tuiUnitSet_t]
    - [tuiUnitListAbstract_t]
        - [tuiUnitAbstract_t]
            - [tuiUnitEvent_t]
            - [tuiUnitDisplayInterface_t]
            - [tuiUnitStateInterface_t]
            - [tuiUnitProcessInterface_t]
            - [tuiUnitCntnrInterface_t]
- [tuiUnitCntnrList_t]
    - [tuiUnitCntnrAbstract_t]
        - [tuiUnitAbstract_t]



- [tuiGraphicUnitRoot_t] (è associato al [stdscr] di [ncurses])
    - [tuiGraphicUnit_t]
- [tuiGraphicUnitWin_t] (sono associati alle [subwindows] di [ncurses]; nella funzione di [init] crea una [subfinestra] con la funzione [newwin] di [ncurses])
    - [tuiGraphicUnit_t]
- [tuiGraphicUnitBase]
    - [tuiGraphicUnit_t]

- [tuiUnitCntnrList_t]
    - questo modulo gestisce [container]
        - ci sono vari tipi di [container] che però hanno tutti la stessa interfaccia

- [tuiUnitCntnrList_t]
    - [dtyCntnrStreamList_t]
        - [tuiUnitFormattedStringCntnr_t]: viene usato dal modulo [dtyCntnrStreamList_t] per visualizzare i dati del buffer stream
    - [dtyCntnrStreamOfFormattedString_t] deriva da
        - [dtyCntnrStreamList_t]


---

Monday, 13th January 2025

- gestione della memoria condivisa che simula il buffer della comunicazione seriale
    - dovrebbe anche simulare un interrupt
    - come impostare l'applicazione
        - ci sono due [use_case]
- [use_case]
    - buffer di comunicazione con un solo elemento
    - buffer di comunicazoine con n elementi
- io direi di cominciare con il buffer di un solo elemento
    - gli elementi [tuiUnit] ncessari
        - immettere i byte che si vogliono inviare
        - visualizzare tutti i byte passati per il canale di comunicazione
            - ci sarà un processo nel [loop] che controlla il buffer di comunicazione e copia i nuovi byte in un [stream_buffer] che verrà visualizzato con l'appropriato modulo [tui] ovvero il modulo [tuiUnitCntnrList_t]
            - il modulo [tuiUnitEbox_t] può essere usato per inviare i messaggi

- analisi flusso delle [istruzioni]/[eventi]
    - premere invio
    - si deve inserire la stringa nel buffer di comunicazione
        - qui si deve attendere che il processo corrente diventi attivo
            - per evitare l'attesa e quindi avere uno stop nel flusso di istruzioni
                - si deve creare un funzione nel modulo [mcuUsart] che accetta o meno la stringa da inviare
                    - la stringa da inviare [str_send] è contenuta nel buffer del modulo [tuiUnitEbox_t]
                    - quindi il modulo [mcuUsart] si deve dotare di un proprio buffer [usart_buf] che al momento opportuno (quando il proceeo divent attivo) ne trasferisce il suo contenuto nel buffer della memoria condivisa [shm_buf
    - gestione dei messaggi da console/terminale di debug [cnslDbg]
        - analisi del processo di ricezione [procRx]
            - si controlla [shmBuf] se è presente qualche messaggio
                - per sapere se è presente qualche messaggio da leggere si controlla il parametro [gDataWriterPid]
                    - nel caso sia diverso dal proprio si deve leggere e processare il buffer
                    - nel caso sia uguale
                        - e sia la [cnslDbg] e non l'applicazione [app] ad ever inserito il messaggio, il processamento consiste nel trasferirlo nel componente [tuiUnitEbox_t]
                        - e sia lìapplicazione ad aver inserito il messaggio, il processamento dipende dalle procedure dell'applicazione
                        - inoltre l'elemento che ha inserito il messaggio [cnslDbg] o [app] si occuperà di azzerare il parametro [gDataWriterPid]


---

Sunday, 12th January 2025


- gestione della funzione [loop] nei moduli [tui]
    - [tuiGraphicUnitRoot_t]
    - [tuiUnitSet_t]
        - [tuiGraphicUnitWin_t]
        - [tuiGraphicUnitBase_t]
    - [tuiUnitCntnrList_t]
    - [dtyCntnrArraySet_t]
    - [dtyTuiGraphic_t]

---

Friday, 10th January 2025

- gestione visualizzazione moduli [pph]
    - per visualizzare lo stato di un componente dei moduli [pph] si deve effettuare una traduzione del codice dello stato in modalità di visualizzazione (colore, normale/italic/bold)
        - di questa traduzione si deve fare carico il modulo [tui]
        - ci possono essere esigenze di visualizzazione diverse per i moduli [pph] a seconda che siano [tasti], [switch], [led] o [relay] sebbene tutti siano associati a porte digitali

    - ci sono situazioni in cui sono presenti esigenze di visualizzazione diverse in base alla piattaforma
        - nel caso particolare delle piattaforme di simulazione, come ad esempio il mac, le [porte_digitali] come anche la [usart] sono caratterizzate dalla presenza della memoria condivisa ncessaria per simulare l'interazione tra schede elettroniche via porte digitali/analogiche o attraverso un canale di comunicazione seriale
        - stringa extra  da visualizzare e colore
            - per la gestione del colore ci deve essere un riferimento "neutro", indipendente dalla piattaforma che definisce i codici del colore 
                - la traduzione di questo codice del colore nel codice usato dalla piattaforma verrà implementato nel wrapper in particolare nel modulo [tuiDrvGraphic]


---

Thursday, 9th January 2025


- come visualizzare gli ingressi/uscite digitali
    - mostrare lo stato dei pin
    - mostrare lo stato della memoria condivisa
        - memoria base dei processi
        - memoria delle porte

- pensare alla gestione delle stringhe dei messaggi per ciascun modulo
    - ci dovra comunque essere un riferimento base comune a tutti i moduli
        - si dovrà fissare il numero di lingue
            - con relativo codice associato alla lingua
        - ci sarà anche il codice associato al modulo
    - quindi per estrapolare una stringa si dovrà fornire
        - codice del modulo
            - assegnato a livello applicazione
        - codice della lingua
            - assegnato a livello applicazione
        - codice del messaggio
            - assegnato a livello applicazione

- pensare ad una struttura di stringa formattata in cui c'è il puntatore alla stringa e le modalità di visualizzazione
    - modalità di visualizzazione
        - stato (selected, deselected, enabled, disabled)
            - selezionato
                - abilitato in verde grassetto 
                    - print()
                - disabilitato in rosso grassetto
            - de-Selezionato
                - abilitato in verde normale
                - disabilitato in rosso debole


---

Tuesday, 7th January 2025

- gestire i parametri da passare al [loop] del firmware usando una struttura che può variare in base alla piattaforma
    - la struttura la definirebbe il modulo [mcu] che è un modulo wrapper
        - i moduli [pph] che sono moduli indipendenti dalla piattaforma non gestirebbero il contenuto della struttura quindi non conoscono i campi della struttura, semplicemente si limitano a passare il puntatore/reference ai livelli sotto stanti che dipendono dalla piattaforma come i moduli [mcu] e a cascata i moduli [shm]

---

Monday, 6th January 2025

- pensare anche alla gestione del protocollo [i2c]

---

Sunday, 5th January 2025

- creare due finestre
    - una con il nome [SIMULATION]
        - in questa finestra si interagisce direttamente con i moduli [pph] e in particolare, di questi, si usano le funzioni di simulazione, ovvero
            - nel caso dei [button]/[key] o degli [switch] è possibile cambiarne lo stato
    - una con il nome [APPLICATION_TEST]
        - in questa finestra si interagisce con i moduli [app] che agiscono sui moduli [pph] usando le funzioni "standard"
            - 
- creare il componente
    - [tuiUnitDgtInOut]
        - che riceverà nell'istanziazione il puntatore all'istanza di un oggetto [mcuPinPort]
            - le funzioni che verranno usate saranno
                - [mcuPinPort->getPort(on/off)]
                - [mcuPinPort->svcSetPort(on/off)]
        - questa modulo può essere ripreso dai due seguenti moduli
            - [tuiUnitButton]
            - [tuiUnitMmyInt]
            - questo modulo non ha bisogno di acquisire  gestione degi eventi come i due moduli sopra citati
                - quindi  la sua funzione [eventOn] deve restituire il controllo degli eventi al padre e poi eseguire il [toggle] dello stato

    - [mcuPinPortBase] è una classe astratta che fornisce l'interfaccia alle classi utilizzatrici per gestire leggere/scrivere i pin delle porte
        - avrà un sezione [service] in cui ci sono le funzioni usate per la [simulazione]

---

Saturday, 4th January 2025

- creazione componenti [tuiUnitLed]/[tuiUnitButton]/[tuiUnitSwitch]
    - sono componenti che si possono far derivare da un componente [tuiUnitBoolean] dal momento che possiedono uno stato con solo due possibili 0/1, on/off
        - notare che il componente [tuiUnitLed] ha uno stato in sola lettura gli altri due in lettura e scrittura 

- interazione tra moduli [pph]/[mcu] e moduli [tui]
    - creare un componente [tuiUnitLed] da associare al modulo [pphLed]
    - creare un componente [tuiUnitButton] da associare al modulo [pphButton]
    - creare un componente [tuiUnitSwitch] da associare al modulo [pphSwitch]
    - creare un componente [tuiUnitRely] da associare al modulo [pphRely]
    - creare un semplice processo [app] che colleghi lo stato dello switch ad un led

- pensare ad un modulo indipendente dai moduli [tui], che chiameremo [app], e che possa controllare ed agire sullo stato dei moduli [pph]
    - la gearachia delle dipendenze sarebbe quindi
        - [tui] +-> [app] +-> [pph]
                +---------+
        - quindi i moduli [tui] possono agire direttamente o indirettamente attraverso i moduli [app] sui moduli [pph]



---

Friday, 3rd January 2025

- gestione accessi alla shared memory
    - ci possono essere accessi contemporanei soltanto da parte di un solo processo già registrato e di (n) processi che richiedono la registrazione

- pensare anche alle priorita di esecuzione
    - tutti i processi dei moduli ad esempio [tui], [pph] devo conoscere i livelli di priorità
    - per eseguire ad esempio la procedura di [end] il modulo [pph] deve attendere che la esegua prima il modulo [tui]
        - il motivo è dovuto al fatto che i moduli [tui] devono ripristinare la modalità classica dell'output su terminale
    - livelli di priorità divisi per gruppi
        - probabilmente si possono crere di conflitti quindi capire anche come venire a conoscenza di qesti conflitti e come risolverli
    - le priorità probabilmente hanno senso per le procedure di [init] e di [end] non dovrebbero valere invece per le procedure di [body]
        - si dovranno assegnare le priorità a ciscun processo
        - ci sarà poi la priorità corrente che può essere aggiornata solo quando tutti i processi che hanno quella priorità daranno il loro consenso
            - ovvero la priorità corrente sara aggiornata dall'ultimo processo che darà il consenso
    - pensandoci bene la priorità dovrebbe essere associata ad ogni singolo [processo_trasversale] ovvero un processo che passa per più moduli
        - bisognerebbe quindi determinare quali siano questi [processi_trasversali]
    - forse la cosa più generale è quella di pensare alla priorità  come uun grafo ad albero in cui le varie foglie sono occupate dai vari moduli 
        - inoltre un modulo può comparire anche in più foglie
            - questa cosa mi fa pensare inevitabilmente ai [processi_paralleli]



---

Thursday, 2nd January 2025

- procedura di cancellazione dei processi non più esistenti
- procedura di aggiunta oltre il limite di nuovi processi
    - il problema sta nel comunicare al nuovo processo che vuole essere aggiunto al buffer che non è stato accettato
    - ho due processi/[init_loop_end]
        - processo dei moduli [tui]
        - processo dei moduli [pph]
    - questi due processi possono girare uno indipendentemente dall'altro
        - comunicano attraverso dei parametri in particolare la gerarchia di visibilità è a senso unico ovvero
            - [tui] -> [pph] 
                - i moduli [tui] possono vedere i moduli [pph] ma non viceversa
        - nel caso il modulo [pph] è bloccato sulla inizializzazione male che vada i parametri non saranno visualizzati nei moduli [tui]
        - nel caso il moduoo [tui] è bloccato sulla inizializzazione come prima cosa non si vedrà niente e comunque i moduli [pph] gireranno normalmente anche se con poca utilità dal momento che non si possono gestire
            

- dare un margine di 2 a tutte le finestre principali e poi anche int32_t buffer

---

Wednesday, 1st January 2025

- gestione moduli [dtyCntnrBufferMmyInt32] e [dtyCntnrBufferShmProcess] e 

---

Saturday, 28th December 2024

- gestione della documentazione
    - nei moduli [tui] sarebbe utili inserire nella documentazione e in particolare nella descrizione anche le modalità di utilizzo
        - quindi fare degli esempi su come usare il modulo

- [tuiUnitCntnrList]
    - [dtyCntnrBufferMmyInt32]
        - int32_t g_buffer[4]
        - **[tuiUnitMmyInt]**
        - **[tuiGraphicUnitBase]**

---

Friday, 27th December 2024

- gestione moduli [dtyCntnr]
    - ha poco senso non voler far dipendere i moduli [dtyCntnr] dal modulo [tuiGraphicUnit] e di conseguenza dal modulo [tuiDrvGraphic] in cui ci sono riferimenti ai driver della piattaforma
        - il motivo è semplice: ai moduli [dtyCntnr] inevitabilmente è stato deciso di demandare anche il compito della visualizzazione e quindi necessariamente dovranno dipendere dai driver della piattaforma
            - o forse la gerarchia delle classi con  l'interfaccia delle funzioni di visualizzazione dovrebbe essere rivista e migliorata

---

Thusday, 26th December 2024

- gestione dei container e della lora associazione con i moduli grafici [tuiUnit] e [tuiGraphic]
    - [stream_container] ad ogni blocco di dati possono essere associate delle proprietà
        - le proprietà del blocco sono caratteristiche degli [stream_container] che non valgono pr altri container come gli [array_container] quindi non è giusto inserirle nel [tuiUnitAbstract]
    - quindi un elemento grafico [tuiUnit] se lo si vuole associare ad uno [stream_container] deve erditare l'interfaccia specifica per i container o ancora meglio per gli [stream_container]
        - quindi l'idea di utilizzare un elemento grafico [tuiUnit] standard è un po' difficile da applicare
        - considerare che l'elemento grafico [tuiUnit] che si vuole usare con il container non sa dell'esistenza del container
        - lo scopo ultimo di questi ragionamenti è quello di evitare da parte dei componenti/moduli [dty] di avere dipendenze con la parte driver e se nel caso specifico del [dtyCntnrStreamList] questi dipendesse dal modulo [tuiUnitFormattedStringCntnr] e non dal modulo più generale [tuiUnitAbstract] allora questi dipenderebbe indirettamente anche dal [tuiDrvGraphic]
            - l'idea è quella di far dipendere i moduli [dty] soltanto da moduli che riguardano i tipi di dati in astratto senza nessun riferimento all'hardware/piattaforma
            - una soluzione accettabilmente pulita sarebbe quella di
                - creare la classe interfaccia [stream_container] in cui si definisce la funzione che permette di impostare i puntatori dei parametri [dtyString] e [dtyStringInfo]
                - usare lo [recast] del puntatore all'istanza [tuiUnitFormattedStringCntnr] alla classe interfaccia [stream_container]
                - derivare la classe [tuiUnitFormattedStringCntnr] dalla classe [tuiUnitAbstract] e dalla classe interfaccia [stream_container]

- si deve testare la componente [tuiUnitButton]
    - la si potrebbe usare per eseguire il refresh della lista dei processi
        - per la lista dei processi ho bisogno dei seguenti componenti
            - [tuiUnitBuffer]
                - [dtyCntnrBufferMmyInt32]: questo modulo verrà istanziato dal modulo [shmManager]
                    - [tuiUnitMmyInt32]
                        - [dtyMmyInt32]
- testare [tuiUnitMmyInt32] & [dtyMmyInt32]
    - si potrebbe usare l'id del processo attivo

- pensare anche a fare un componente "semplice" [tuiUnitBufferInt32] dando in input semplicemente un array di [int32]
    - creare delle routine per la conversione da intero a stringa e viceversa a parte come [utility]



---

Wednesday, 25th December 2024

- gestione container
    - cercare di aggiungere un po di commenti per chiarire il significato delle funzioni e dei parametri
        - [dtyCntnrArraySet]
            - il parametro g_y0r associato al container serve esclusivamente per capire quando si è giunti all'inizio o alla fine della lista infatti viene utilizzato solo nella funzione 

---

Tuesday, 24th December 2024

- lista di cosa si deve implementare
    - tuiUnitButton
        - per eseguire il refresh dei parametri che possono cambiare
    - tuiUnitLabel
        - semplice visualizzazione di una stringa 
            - non dovrebbe essere selezionabile
    - tuiUnitParInt32
        - permette di modificare i parametri oppure
        - solo visualizzarli
    - container di array di interi
        - ad esempio: visualizzazione della lista dei [pid] dei processi attivi
        

---

Monday, 23rd December 2024

- da analizzare il progetto dec per come ho gestito la visualizazione e la modifica di parametri [uint]
- gestione del flusso di istruzioni
    - init
    - loop
    - end
- gestione visualizzazione parametri del modulo [shm]
    - la cosa migliore è quella di prendere una finestra ed inserire i parametri
        - g_pidActive
            - creare un componente unit/func per gestire la visualizzazione di parametri uint32_t che occupi una sola riga
                - si può riprendere tuiButtonn
        - lista dei processi / g_pid attivi
            - creare un componente per visualizzare una lista di stringhe
            - oppure
            - usare il componente creato al punto precedente e metterlo in una sub-finestra
                - non è possibile farlo dovendo usare un buffer
            - oppure 
                - sfruttare i container e quindi creare un nuovo container con una lista di semplici uint32_t
- visualizzazione parametri dei moduli [mcu]
    - creare un componente per visualizzare i pin delle porte che occupi una sola riga
        - gestione pin di input/output
    - creare un componente per visualizzare lo stato di un'intera porta
    


- pensare se
    derivare la classe [mcuPinPort] dalla classe [shmPinPort] può abbia un senso

- gestione del parametro [g_mcuId] delle pinPort
    - se non viene assegnato al momento dell'istanziazione si imposta l'[mcuId] di default
        - questo significa che le azioni su questo pin vengono fatte senza nessun filtro sul [mcuId] 
            - invece quando [mcuId] è impostato, ovvero diverso dal valore di default, le azioni vengono attuate solo se il suo valore coincide con quello dell'[mcuId] della macchina virtuale che sta girando

- pensare anche a come risparmiare memoria (nel caso virtuale non ha molta rilevanza ma nel caso reale si)
    - avere un istanza per ogni pin può diventare oneroso molto più economico invece avere un istanza solo per ogni porta
    - invece di creare la classe [mcuPinPort] si dovrebbe creare la classe [mcuPort] e poi lavorare con le define e i file di configrazione dei pin che possono appartenere a diversi moduli

---

Sunday, 22nd December 2024

- come gestre i modulo wrapper
    - una delle principali problematiche dei moduli wrapper è quella di dover far coesistere sub-moduli sviluppati da persone diverse
        - per far questo senza causare conflitti si potrebbe pensare ad una politica di questo tipo
            - la sezione [common] dei moduli wrapper è suddivisa per versioni
            - quando si inserisce una nuova piattaforma e si deve modificare la sezione [common] invece di apportare una modifica ad una delle versioni presenti se ne crea una nuova
            - la versione della sezione common la può modificare solo chi la ha creata o una persona del suo gruppo
            


- sarebbero da rinominare 
    - vhwMain       -> hwMain       -> mpfw_code_libs_fw2_core_core
    - vhwManager    -> hwManager    -> mpfw_code_libs_fw2_core_core    
    - pph           -> hwMbd        -> mpfw_code_libs_fw2_core_core
        - [pphDef_<group_name>.cpp]     -> mpfw_code_apps_<application code>
        - [vhwPphTbl.cpp/h]             -> mpfw_code_apps_<application code>
    - mcu           -> hwMcu        -> mpfw_code_libs_fw2_wrapper_resources
        - [mcuPinPortDefineConfig.h]    -> mpfw_code_main_<application code>/<platform>
    - shm           -> hwShm        -> mpfw_code_libs_sdk_mac_ext


- i moduli wrapper hanno la caratteristica di
    - avere delle interfacce comuni
    - avere dei sottomoduli corrispondenti alle varie piattaforme


---

Saturday, 21st December 2024

- gerarchia di moduli
    - [vhwMain]
        - [vhwManager]
            - [pphManager]
                - [loop] on [pph] array moudles
                - [mcuManager]
                    - [loop] on [mcu] array modules (forse questo array non è necessario, è da capire meglio)
                    - [shmManager] presente nel caso di piattaforma virtuale
                        - [loop] on [shm] array modules

    - [vhwMain]
        - [vhwManager]
            - [init]
            - [loop]
            - [end]
        - [pphManager]
            - [init]
            - [loop]
            - [end]
        - [mcuManager]
            - [init]
            - [loop]
            - [end]
        - [shmManager] presente nel caso di piattaforma virtuale
            - [init]
            - [loop]
            - [end]

- pensare alla gestione del bus i2c
    - come chiamare i moduli che dipendono dal protocollo i2c
        - [pphRTC_i2c]
        - [pphTmprt_i2c]
    - o è meglio non fare nessun riferimento del protocollo e rendere trasparente l'utilizzo dei protocolli i2c o altri simili?
        - se un elemento [pph] dipende da un certo bus/protocollo credo sia in funzione della piattaforma 
        - quindi  l'utilizzo del protocollo deve essere rimandato al livello [wrapper]
        - ed inoltre sarebbe da parametrizzare  e quindi renderlo dipendente d un parametro che veràà impostato nei file di configurazione
    - rimane valido, credo, il fatto di creare comunque un modulo [pphI2c] 
- i file di configurazione e le tabelle dell'hardware (ovvero l'array dele istanze dei moduli [pph]) saranno localizzati nel modulo [main] e nella folder corrispondente alla piattaforma
    - si ricorda che 
        - i file di configurazione sono
            - [mcuPinPortDefineConfig.h]
            - [pphDef_<group_name>.cpp]
        - i file di tabelle/array sono
            - [vhwPphTbl.cpp/h]


            
---

Friday, 20th December 2024

- lo schema della gerarchia dei moduli è il seguente
    - [pph]       -> [mcu]            -> [shm]
       core/core  | wrapper/resources | sdk
    - si dovrebe cercare di uniformare la gestione delle periferiche tra le piattaforme virtuali e reali
        - si potrebbe pensare alla sezione [service]/[srv] all'interno di ciscun modulo [pph] che
            - nel caso viruale
                - si occupa di gestire l'hardware virtuale ovvero avere la possibilità di cambiare lo stato del pin di una porta configurata in ingresso
            - nel caso reale
                - si occupa di gestire il debug usando una seriale/usart di servizio se presente e quindi avere la possiilità di agire direttamente sui pin del micro con dei comandi via seriale

- file di configurazione delle periferiche
    - definizioni
        - [pphMacroDefine.h]
            - creazione delle [#define] delle periferiche della motherboard relative 
                - alle istanze
                - ai puntatori delle istanze
        - [mcuPortDef.h/cpp]
            - definizione dell'array di porte 
    - configurazioni
        - [mcuPinPortDefineConfig.h]
            - configurazione delle porte e dei pin associati alle periferiche esterne quali possono essere 
                - leds, buttons, switch, etc
                - seriale
                - bus i2c
                - etc.
        - pphDef_<group name>.cpp
            - [pphDef_Buttons.cpp]
            - [pphDef_Leds.cpp]
            - [pphDef_Mod1.cpp]
            - PPH_DEF_CPP
                - è una define che crea i nomi delle istanze delle periferiche in modo appropriato
            - PPH_DEF_CPP_LINK
    - tabelle
        - [vhwPphTbl.cpp/h]

- collocazione dei file i configurazione
    - moduli apps/main
        - [mcuPinPortDefineConfig.h]
        - [pphDef_<group_name>.cpp]
            - [pphDef_Buttons.cpp]
            - [pphDef_Leds.cpp]
            - [pphDef_Mod1.cpp]
        - [pphManagerTbl.cpp]
    - moduli libs/fw2/core/core
        - [pph]
            - [pphManagerTbl.h]
            - [pphManager.h/cpp]
    - moduli libs/fw2/wrapper/resources
        - [shm]
        - [mcu]

- i moduli [pph]/[PeriPHerals] possono essere rinominati in [mbd]/[MotherBoarD]
    - i moduli della mother board viene più spontaneo pensarli indipendenti dalla [micro]/[piattaforma] mentre i moduli associati al microcontrollore viene spontaneo pensarli platform dependent
    - è quasi sconato dire che non ci deve essere nessun riferimento diretto al modulo [shm] nei moduli [pph]
        - se si vogliono chiamare le funzioni del modulo [shm] si deve creare un interfaccia appropriata nel modulo [mcu]
            - pensare alla possibilità di associare (creare una dualità) al modulo [shm] caratteristico delle piattaforme virtuali [mac] il modulo [dbg] delle piattaforme reali
                - il modulo [dbg] sfrutterebbe se presente una seriale di servizio

- vediamo adesso di ricordare cosa viene fatto
    - nella fase di istanziazione 
        - e quindi nella funzione [costruttore]
            - vengono inizializate le variabili del modulo [mcuPinPort]
                - compreso il puntatore relativo alla memoria condivisa [shm] nel caso delle piattaforme virtuali ponendo uguale al puntatore nullo [nullptr]
    - nella fase di inizializzazione
        - e quindi nella funzione [init]
            - viene completata l'inizializzazione del modulo [mcuPinPort] impostando il puntatore della [shm] al suo valore opertivo
                - notare che questa operazione può essere fatta solo a [runtime]
        
- il modulo [mcuPinPort2] viene usato per gestire i collegamenti/componenti di collegamento tra due board virtuali
    - quindi viene usato nei moduli [pphRelay] e [pphWired]


---

Thursday, 19th December 2024


- i moduli [pph] sono dei moduli che dovrebbero essere indipendenti dalla piattaforma
    - dipendono dai moduli [mcu]
        - i moduli [mcu] sono moduli [wrapper] quindi che dipendono dalla piattaforma
            - infatti ogni piattaforma/microcontrollore hanno le loro modalita di configurazione, inizializzazione e gestione delle periferiche interne come le porte, la USART, etc.
    - quindi in generale la procedura per attivare le periferiche della motherboard è quella di concentrarsi sui moduli [pph]
        - i moduli [mcu] si trovano "sotto" i moduli [pph] e dovrebbero essere sconosciuti all'"utilizzatore finale" colui che deve semplicemente associare/collegare gli elementi/periferiche della mother board agli appropriati pin del micro virtuale (piattaforma mac) o reale (piattaforma stm32f769, nxp-lpc54608) che sia

- pensare anche alla simulazione del [bus] [i2c]

- come viene fatta l'inizializzazione delle periferiche quindi delle istanze dei moduli [pph]?

-  gestione della partenza del micro virtuale/reale
    - inizializzazione dell'hardware [hwInit]
        - configurazione [MCU]
            - configurazione dei registri [CPU]
                - clock
                - modalità di esecuzione
                - etc.
            - configurazione dei registri delle [Ports]
                - in/out
                - USART
                - i2c
                - etc.
            - configurazione dei registri delle [Peripherals]
                - USART
                - i2c
                - etc.
        - mbrMCU
        - mbrSerial1
        - mbrButtons
            - mbrButton1
            - mbrButton2
            - mbrButton3
        - mbrLeds
            - mbrLeds1
            - mbrLeds2
        - mbrBlock1
            - mbrLeds3
            - mbrKeybd
                - mbrButtonUp
                - mbrButtonDw
                - mbrButtonLf
                - mbrButtonRg
                - mbrButtonEn
            - mbrSerial2
            - mbrHumty
                - mcuI2C
            - mbrTmprt
                - mcuI2C
            - mbrRTC
                - mcuI2C
            - mbrADC
                - mcuI2C
            - mbrDAC
                - mcuI2C


---

Wednesday, 18th December 2024

- gestione dell'hardware reale e virtuale
    - caso reale
        - configurazione pin del micro
        - collegamento fisico tra i pin del micro e le periferiche presenti nella mother board: buttons, leds, relays, etc.
    - caso virtuale / simualzione dell'hardware
        - configurazione pin del micro
        - definizione / istanziazione delle periferiche virtuali, quelle che siumulano le periferiche reali della mother board: leds, buttons, relays, etc.

- vedere
    - Wednesday, 10th July 2024


---

Saturday, 23rd November 2024

- gestione dei movimenti delle sotto finestre di ncurses
    - hanno due insiemi di parametri
        - quelli verso il padre
        - quelli verso i figli


---

Wednesday, 20th November 2024

- dtyCntnrArraySet implementation
    - determinare l'altezza [g_h] "totale" (visibile e non visibile) della finestra ospitante l'insieme delle sotto finestre
        - è necessario per poter avre un limite sullo scroll up/down
            - determinare la coordinata [g_y0r] con valore minore tra tutte le sotto finestre
            - determinare [g_y0r_+_g_h] con valore più alto fra tutte le sotto finestre
    - nella fase di inizializzazione [init] non viene cambiata la coordinata relativa di nessuna sotto finestra
    - le coordinate relative delle sotto finestre vengono cambiate solo attraverso incrementi 
        - quindi la posizione relativa tra le sotto finestre non cambia
    

---

Tuesday, 19th November 2024

- graphic
- process

---

Sunday, 17th November 2024


- sarebbe da aggiungere 
    - gli elementi [tuiUnit] con interfaccia container
        - in particolare devono avere la funxzione di [updParams]
            - dato che i dati potrebbero essere diversi da elemento a elemento si dovrà utilizzare il puntatore generico [void*]
            - inoltre la gestione della determinazione delle dimensioni dell'oggetto in base al contenuto da visualizzare dovrebbero essere demandate all'elemento del container ovvero all'elemento [tuiUnit]
                - e non all'elemento [dtyCntrStream] come succede adesso
                    - quindi il modulo [dtyCntrStream] 
                        - ottiene i [data] dallo [stream]
                        - li insierisce/aggiorna nell'elemento [tuiUnit] 
                        - e poi all'emento [tuiUnit]/[tuiGraphic] chiede i dati che gli servono in particolare l'altezza del box

---

Tuesday, 12th November 2024

- gestione dei container
    - gli elementi in gioco nella gestione dei container sono
        - tuiUnitCntnrList/set
            - è l'elemento [tui] che gestisce gli oggetti dtyCntnrUnitAbstract
            - forse non è necessario creare due classi 
                - una per la gestione stile [lista] ovvero gli elementi si trovano disposti in verticale o in orizzontale
                - e l'altra per la gestione stile [set] ovvero gli elementi si trovano in ordine sparso 
            - per la gestione dei due stili credo che si stabilisce tutto nei moduli dtyCntnr
        - moduli [dtyCntnr<container_type>]
            - dtyCntnrArrayList/Set
            - dtyCntnrStreamList/ProtocolList
            - dtyCntnrStreamSet/ProtocolSet
        - tuiUnit<container element>
            - l'elemento del contrainer può essere un qualunque elemento [tuiUnit] e quindi anche [tuiUnitCntnrList/set]
            - tuttavia per poter gestire/implementare al meglio i moduli [dtyCntnr<container_type>] si dovranno creare delle classi "interfaccia"
                - in cui si definisco le interfacce/funzioni necessarie per gestire le peculiarità di alcuni moduli [tuiUnit]
                    - un esempio possono essere la visualizzazione di stringhe aventi una particolare formattazione
                - il motivo è semplice
                    - i moduli [dtyCntnr<container_type>] avranno delle informazioni su come visualizzare gli elementi del contenitore 
                        - e naturalmente queste informazioni possono essere diverse da elemento a elemento
                    - inoltre è bene che i moduli [dtyCntnr<container_type>] lavorino con elementi [tuiUnit], e a cascato [tuiGraphic], astratti
                - tuiUnit
                - string
                - formatted string
                - etc
---

Friday, 25th October 2024

- visualizzzione del frame
    - usare la funzione [box] di [ncurses] per fare anche un clear oltrre a disegnare il frame
    - negli altri casi non serve
    - quindi sarebbe da creare una funzione del tipo
        - [clearNframe]

- come gestire le dimensioni e le posizioni orizzontali in funzione della dimensione orizzontale della finestra root
- oppure gestire anche qui lo scorrimento in orizzontale come si è fatto per lo scorrimento in verticale
- e poi aggiungere anche il ridimensionamento automatico


selectElements() -> eventOnClickedElementNslectItsAnchestors() -> selectingElement()

initElementsList();
displayElements(true); // "true" means that the elements are displayed recursively
selectElements(); -> eventOnClickedChildNselectItsAnchestors() -> clickingChild()
refreshElements();


---

Thursday, 24th October 2024


tuiDrvGraphic   
|
tuiGraphicAbstract_t    /   uiUnitAbstract
|                           |
uiUnitAbstract              tuiGraphicAbstract_t


- FERMI TUTTI!!!!!! di nuovo
    - non sono d'accordo per quanto pensato ieri
        - ovvero
            - la classe [tuiGraphUnit] non ha bisogno di essere derivata, aggiornata o quant'altro!!!!
        - oggi la penso in questo modo
            - la classe [tuiGraphUnit] ingloba in se le caratteristiche grafiche di un elemento tenedole separate da altri di di funzione
                - quindi quando queste proprietà grafiche cambiano come nel caso dell'elemento [root] e dell'elemento [window] è giusto creare degli elementi grafici specifici
        - e le motivazioni sono le seguenti
            - notare che ragionando come ieri si va in  contro ai seguenti problemi
                - si complica il codice inutilmente
                    - si pensi alla funzione di [init] e di [loop]
                        - qui si farebbero eseguire certe funzione al modulo [tuiUnit] proprie del modulo [tuiGraphicUnit] con dispendio inutile di codice
                            - invece di chiamare direttamente la funzione [initGraphEnv] e nella funzione [init] del modulo [tuiGraphic]
                            - dovrei chiamarla nel metodo [init] della classe [tuiUnit] attraverso il puntatore [p_this->initGraphEnv]
                - a livello logico-funzionale è come dire
                    - io (modulo [tuiUnit]) sono un modulo che non si occupa e non sa niente della parte grafica e delle sue procedure ma, cosa assurda, devo io implementare la procedura di [init] del mio "associato" elemento grafico
                    - io invece dovrei usare le funzioni del modulo [tuiGraphic] a me associato semplicemente per mostrare i miei contenuti, 
                        - queste sono le uniche funzioni che io devo essere a conoscienza
                    - inoltre si perderebbe l'indipendenza dalla piattaforma dato che le procedure di inizilizzazione per la parte grafica possono variare in base alla piattaforma
- in base a quanto esposto sopra la nuova struttura delle derivazioni e delle dipendenze è la seguente


- [tuiGraphicUnit] (implemenat le funzioni dell'interfaccia [tuiGraphicEvent])
    - [derived] [tuiGraphicEvent] <da capire bene come gestire gli eventi>
    - [derived] [drvTuiGraphic] (implementa le funzioni virtuali dell'interfaccia [tuiGraphicInOutInterface] che verranno usate dai moduli [tuiUnit] associati)
    - [depend] [tuiUnitAbstract]


- [tuiUnit<name>] (i.e. [tuiUnitWin]/[tuiUnitDgtInOut])
    - [tuiUnitAbstract]
        - [tuiGraphicEvent] <da capire bene come gestire gli eventi>
            - [depend] [tuiGraphicAbstract]
        - [tuiUnitStateInterface]
            - [depend] [tuiGraphicAbstract]
        - [tuiUnitDisplayInterface]
            - [depend] [tuiGraphicAbstract]
        - [tuiUnitProcessInterface]
            - [depend] [tuiGraphicAbstract]

[tuiGraphicBoxRoot] (implementa le funzioni dell'interfaccia [tuiGraphicProcessInterface] la funzione [init] e [loop] in particolare)
[tuiGraphicBoxWind] (implementa le funzioni dell'interfaccia [tuiGraphicProcessInterface] la funzione [init] e [loop] in particolare)
[tuiGraphicBoxWindow] (implementa le funzioni dell'interfaccia [tuiGraphicProcessInterface] la funzione [init] e [loop] in particolare)
[tuiGraphicBoxBase] (implementa le funzioni dell'interfaccia [tuiGraphicProcessInterface] la funzione [init] e [loop] in particolare)
[tuiGraphicBoxSimply] (implementa le funzioni dell'interfaccia [tuiGraphicProcessInterface] la funzione [init] e [loop] in particolare)
- [tuiGraphicBox] (implementa le funzioni dell'interfaccia [tuiGraphicEvent])
    - [derived] [tuiGraphicEvent] <da capire bene come gestire gli eventi>
    - [derived] [tuiGraphicProcessInterface]
    - [derived] [drvTuiGraphic] (implementa le funzioni virtuali dell'interfaccia [tuiGraphicInOutInterface])
        - [tuiGraphicAbstract] (riunisce le tre parti/sezioni che compongono la struttura dell'elemento grafico generico necessaria per generare le dipendenze)
            - [derived] [tuiGraphicCoord] (acquisisce una parte delle funzioni e variabili contenute nel modulo [tuiBaseDrawer])
                - [derived] [tuiGraphicParent]
            - [derived] [tuiGraphicState] (sostituisce il modulo [tuiBaseAction] e sono le funzioni che devono implmentare i componenti, gestisce lo stato di visualizzzazione degli oggetti grafici ([select]/[deselect]/[eventOn]))
                - [derived] [tuiGraphicParent] (fornisce il puntatore all'oggetto grafico genitore del corrente oggetto grafico)
                - [derived] [tuiGraphicStateInterface] (l'imlementazione di queste funzioni conterrà le funzioni dell'interfaccia [tuiGraphicInOutInterface])
            - [derived] [tuiGraphicDisplayInterface] <forse per i moduli graphic non serve questa interfaccia>
            - [derived] [tuiGraphicDriverInOutInterface] (rappresenta l'interfaccia delle funzioni necessarie per visualizzare gli elementi grafici come [box]/[frame] [text], l'implementazione di queste funzioni conterrà le funzioni dei driver associati alla piattaforma)
        - [depend] [ncurses]
    - [depend] [tuiUnitAbstract]



---

Wednesday, 23rd October 2024


- vediamo come gestire l'entry point ed in particolare gli elementi radice dei moduli [tuiGraphicUnit] e [tuiUnitWin]
    - il modulo [tuiUnitWinRoot] dovrà essere contenuto in un istanza della classe [tuiGraphUnit]
        - probabilmente anche in questo caso la cosa opportuna è derivare dalla classe [tuiGraphicUnit] la classe singletone [tuiGraphicUnitRoot]
            - da capire se deve essere fatta la stessa cosa per il modulo [tuiUnitWinRoot]
            - la classe [tuiGraphicUnitRoot] implementarà la funzione loop()
        - FERMI TUTTI!!!!
            - la classe [tuiGraphUnit] non ha bisogno di essere derivata, aggiornata o quant'altro!!!!
            - la sua caratteristica è che da un "involucro" grafico ai vari componenti
            - certamente si dovrà creare una istanza "con nome" ovvero non anonima da fornire al modulo [tuiManager]

---

Tuesday, 22nd October 2024


- [tuiUnit<name>] (i.e. [tuiUnitWin]/[tuiUnitDgtInOut])
    - [tuiUnitAbstract]
        - [tuiGraphicEvent]
            - [depend] [tuiGraphicAbstract]
        - [tuiUnitStateInterface]
            - [depend] [tuiGraphicAbstract]
        - [tuiUnitDisplayInterface]
            - [depend] [tuiGraphicAbstract]
- [tuiGraphicUnit] (implemenat le funzioni dell'interfaccia [tuiGraphicEvent])
    - [derived] [tuiGraphicEvent]
    - [derived] [drvTuiGraphic] (implementa le funzioni virtuali dell'interfaccia [tuiGraphicInOutInterface])
        - [tuiGraphicAbstract] (riunisce le tre parti/sezioni che compongono la struttura dell'elemento grafico generico necessaria per generare le dipendenze)
            - [derived] [tuiGraphicEvent]
            - [derived] [tuiGraphicCoord] (acquisisce una parte delle funzioni e variabili contenute nel modulo [tuiBaseDrawer])
                - [derived] [tuiGraphicParent]
            - [derived] [tuiGraphicState] (sostituisce il modulo [tuiBaseAction] e sono le funzioni che devono implmentare i componenti, gestisce lo stato di visualizzzazione degli oggetti grafici ([select]/[deselect]/[eventOn]))
                - [derived] [tuiGraphicParent] (fornisce il puntatore all'oggetto grafico genitore del corrente oggetto grafico)
                - [derived] [tuiGraphicStateInterface] (l'imlementazione di queste funzioni conterrà le funzioni dell'interfaccia [tuiGraphicInOutInterface])
            - [derived] [tuiGraphicDisplayInterface]
            - [derived] [tuiGraphicDriverInOutInterface] (rappresenta l'interfaccia delle funzioni necessarie per visualizzare gli elementi grafici come [box]/[frame] [text], l'implementazione di queste funzioni conterrà le funzioni dei driver associati alla piattaforma)
        - [depend] [ncurses]
    - [depend] [tuiUnitAbstract]


---

monday, 21st October 2024


- il modulo sarà chiamato [tuiGraphic] e la sua struttura sarà
    - [tuiUnitGraphic] (è l'elemento grafico reale, quello che gestisce la tabella eventi e lo smista agli elementi grafici "astratti" e "specifici" come i moduli [tuiWin], [tuiEbox], [tuiLbox], etc.)
        - [tuiGraphicDriver] (è l'elemento che implementa le funzioni dell'interfaccia [tuiGraphicInOut])
            - [tuiGraphicReal] deriva da (sostituisce il modulo [tuiBaseDrawer] e ha diretto accesso alle funzioni per la gestione dell'input/output relative alla piattaforma)
                - [tuiGraphicEvent] (rappresenta l'interfaccia delle funzioni associate agli eventi da tasti/tastiera e mouse che verranno implementate dai moduli grafici "specifici": [tuiWin], [tuiEbox], [tuiLbox], etc.)
                    - [tuiGraphicAbstract] deriva da (sostituisce il modulo [tuiBase]; 
                        - [tuiGraphicCoord] (acquisisce una parte delle funzioni e variabili contenute nel modulo [tuiBaseDrawer])
                        - [tuiGraphicSelect] (sostituisce il modulo [tuiBaseAction] e sono le funzioni che devono implmentare i componenti)
                        - [tuiGraphicInOut] (rappresenta l'interfaccia delle funzioni necessarie per visualizzare gli elementi grafici come [box]/[frame] [text])
                - [ncurses]

- [tuiUnitWin], [tuiUnitEbox], etc. 
    - derivano da
        - [tuiGraphicEvent]
        - e ne implementano le funzioni
    - dipendono da (ovvero conoscono) gli elementi derivati dalla classe
        - [tuiGraphicVirtualUnit]
        - infatti possono essere proprietari di contenitori che contengono elementi derivati dalla classe [tuiGraphicVirtualUnit]
- [tuiGraphicReal] 
    - implementa le funzioni dell'interfaccia [tuiGraphicInOut]
        - usando le funzioni/driver fornite dalla piattaforma
- [tuiGraphicUnit] 
    - implementa le funzioni dell'interfacccia [tuiGraphicEvent]



- la parte [driver] ovvero quella che usa la libreria grafica/[GUI] della piattaforma per 
    - [visualizzare] contenuti
    - [ricevere] comandi dall'utente (gestione [tastiera]/[mouse])
    - i moduli interessati saranno così strutturati
        - [drvTui] deriva da (implementa le funzioni della classe virtuale [tuiGraphic])
            - [drvTuiOut]
            - [drvTuiIn]
            - [tuiGraphicDriver]


---

Friday, 18th October 2024


- come riordinare e riorganizzare la struttura degli elementi/moduli [tui]
    - usare un interfaccia comune per tutti i tipi di [container]
        - [dtyBaseCntrUnitX]
    - il modulo [tuiDrawer] deve essere suddiviso in due parti
        - la parte [grafica_astratta], da cui dipendono le funzioni [GUI] di in/out, che gestisce le coordinate degli elementi grafici
            - deve essere indipendente dalla piattaforma
            - gestisce
                - coordinate 
                    - elementi grafici
                    - sistemi di puntamento (ad esempio [mouse])
                - dimensione
                    - elementi grafici
            - fornisce un interfaccia per le funzioni di visualizzazione
                - questa parte sostuirebbe l'attuale modulo [tuiBaseAction]
            - il modulo sarà chiamato [tuiGraphic] e la sua struttura sarà
                - [tuiGraphicDriver]
                    - [tuiGraphicVirtual] deriva da (sostituisce il modulo [tuiBase])
                        - [tuiGraphicCoord] (acquisisce una parte delle funzioni e variabili contenute nel modulo [tuiBaseDrawer])
                        - [tuiGraphicInterface] (sostituisce il modulo [tuiBaseAction] e sono le funzioni che devono implmentare i componenti)
                    - [tuiGraphicDriverInterface] (sono le funzioni che devono essere implementate dal modulo [drvTui])
                        - qui viene definito l'array degli eventi da tastiera e da mouse che verranno gestiti dagli oggetti [tuiGraphicDriver]
                        - qui si gestiscono gli elementi [selected]/[eventOn] che sono proprio i soggetti di un implementazione reale
        - la parte [driver] ovvero quella che usa la libreria grafica/[GUI] della piattaforma per 
            - [visualizzare] contenuti
            - [ricevere] comandi dall'utente (gestione [tastiera]/[mouse])
            - i moduli interessati saranno così strutturati
                - [drvTui] deriva da (implementa le funzioni della classe virtuale [tuiGraphic])
                    - [drvTuiOut]
                    - [drvTuiIn]
                    - [tuiGraphicDriver]
    - gestione dei moduli grafici [tui]
        - alcuni esempi si moduli grafici
            - [tuiBaseWin] 
                - deriva da [tuiGraphicVirtual]
                - gestisce oggetti/istanze di [tuiGraphicDriver]
                    - però è da vedere può essere sufficente che gestisca istanze di opggetti [tuiGraphicVirtual] del suo stesso tipo
            - [tuiBaseSubWin]
            - [tuiBaseLboxX]
            - [tuiBaseEboxX]
            - etc.
        - questi moduli dovranno essere rivisti in modo da 
            - renderli indipendenti dalla piattaforma
            - renderli indipendenti dalle coordinate "reali"
                - in modo da usare una stessa istanza in finsetre/container differenti
                - ma come assegnare le coordinate
                    - si crea l'istanza dell'oggeto grafico
                        - si assegna la coordinata solo quando lo si aggiunge al container 
            - e saranno gli ospiti delle istanze del modulo [tuiDrvUnit]
    - tipologie di elementi [tui]
        - l'insieme degli elementi grafici che lavorano in "astratto"
        - la classe di oggetti che si interfaccia con i driver della piattaforma


---

Thursday, 17th October 2024

- componente textX
    - come sincronizzare lo start della stringa con la riga che gli corrisponde e anche con il boundUp
        - quindi sincronizzare il [boundUp] con la [string_id]
        - e poi far eil loop tra [UpperBound] e [LowerBound]

- gestione della selezione attaverso mouse di un elemento parzialmente visibile come anche alcuni dei suoi genitori/antenati
    - ci sono due modi per procedere
        - 1. aggiornare la poszione nel processo di "andata", nel flusso che porta il segnale del mouse, a cascata, dalla finestra root fino all'ultimo elemento selezionato
        - 2. aggiornare la posizione a ritroso in particoare partendo dall'elemento foglia selezionato e procedendo in dietro/in su verso i propri antenati
    - dei due sistemi certamente quello più lineare è il primo quindi direi di procedere con questo

---

Wednesday, 16th October 2024

- implementare una funzione initRelCoord();
- e poi chiamare la funzione di init del componente

---

Tuesday, 15th October 2024

- ragionamenti sulla gestione del componente [tuiBaseLboxX]
    - quando si shifta il DisplayBox non ha senso cambiare le coordionate di tutti i componenti
        - ma solo di quelli che si trovano all'interno della finestra di visualizzazione ovvero del displayBox
            - questa distinzione puo essere fatta se i compnenti, come in un ListBox, sono allineati in un certo modo
            - ma nel caso di una finestra in cui gli elementi hanno le loro coordinare bisogna passarli tutti
        - notare poi che l'oggetto DisplayBox dovrebbe essere un oggetto di interesse del solo contenitoree e non di tutti gli elementi in esso contenuti
    - conviene invece considerare una finestra associata ad esempio al contenitore
        - il contenitore ha le sue coordinate e sono queste che cambiano
        - il delta della posizione iniziale con quella all'n-esimo step è datat proprio dalla coordinata del contenitore
            - le coordinate del contenitore cambiano quando
                - con il tasto up/down si seleziona un elemento fuori dal displyBox
                - con il mouse si esegue il roll up/down

- ritorna adesso il problema di come gestire la fase di [deSelect] di un elemento
- analisi degli use case
    - mouse selection
        - 1. deselect item in un altra finestra
        - 2. deselect item è il genitore
        - 3. deselect item è un fratello visualizzabile
        - 4. deselect item è un fratello parzialmente visualizzabile
        - 5. deselect item è un fratello non visualizzabile
            - questa è la sola condizione in cui la funzione di deselect non deve visualizzare niente ma cambiare solo il suo stato di visualizzazione 

- pensare di mettere un parametro per abilitare o meno il refresh della finestra dopo un comando di visualizzazione
    - serve a non appesantire eccessivamante il flusso di codice
- ragionando sembra si arrivi sempre alla conclusione che convenga metter eil controllo di visualizzabilità all'interno della funzione di display
- IMPORTANTE!!!!
    - la funzione di [deselect] deve essere chiamata solo dai componenti che sono nello stato di select
        - la funzione [deselect] va usata in modo oculato e non in modo indiscriminato

- portare in alto il contenuto significa dimnuirGli/decrementarGli le coordinate

g_boundLower - (g_lvl1Y0a + g_h - 1) + g_lvl1Y0a = g_boundLower - (g_h - 1) = g_lvl1Y0a(new)

g_lvl1Y0a(new) + g_h = g_boundLower + 1

---

Monday, 14th October 2024

- gestione del [deSelect] a livello grafico
    - il problema si presenta quando si ha a che fare con liste di elementi che possono cambiare la loro posizione relativa all'interno di una finestra che li ospita
        - vari aspetti da considerare
            - eseguire la funzione [deSelect] solo per elementi [selected]
            - vedere la possibilità di eseguire sotto condizione la funzione di refresh all'interno delle funzioni di [select]/[deSelect]/[eventOn]
            - eseguire la funzione di [deSelect] solo nel caso l'elemento sia visibile
            - non usare la variabile [g_status]/[g_mode] per tener traccia della modialità in cui si trova l'elemento [tui]

- quando c'è un roll su una finestra prima di eseguire il repaint si deve ripulire tutta la finestra quindi avere una funzione di [clean] che eventualmente non chiamerà la funzione di [refresh]
- da capire bene e quindi da decidere
    - come gestire la visualizzabilità di un elemento [tui]
        - implementare il controllo all'interno delle funzioni [tuiDrawer] oppure fuori da esse?
            - quindi eseguire il controllo prima di chiamare la funzione display di [tuiDrawer]
            - probabilmente inserire il controllo all'interno delle funzioni [tuiDrawer] implicherebbe un maggior numero di chiamate alla funzione di [check]
                - ma forse a livello di implementazione del codice sarebbe la cosa più lineare e pulita
                    - consideraimo come esempio l'utilizzo della funzione [rowPrintX] usata nel modulo [tuiData]
                        - a posteriori 
                            - una critica negativa che può essere mossa è che la gestione della visualizzabilità delle righe è praticamente spezzata in due
                                - quindi se si analizza solo la funzione [rowPrintX] nasce il dubbio di
                                    - come mai non viene fatto un controllo per sapere se anche un solo ciclo di loop sia possible?
                            - una critica positiva è quella che si risparmia nell'esecuzione di una chiamata ad una funzione quindi circa una qualche decina di istruzioni macchina credo
                    - tuttavia per un elemento [tui] che contiene altri elementi sarebbe altamente opportuno evitare di attivatre la "catena" delle ricorsioni in basso verso i figli se l'elemento non è visualizzabile
                        - eventualmente questo controllo lo si può demandare al contenitore che decide se iniziare la ricorsione/il ciclo sugli elementi in base allo stato di visualizzazione del componente a cui lui appartiene



---

Friday, 11th October 2024

- come gestire i parametri

    // display box
    // - display box dimensions
    uint16_t g_dspBoxW;     // set by the container where the current instance is located
    uint16_t g_dspBoxH;     // set by the container where the current instance is located
    void setDspBoxDimW      (uint16_t p_dspBoxW);
    uint16_t getDspBoxDimW  (void);
    void setDspBoxDimH   (uint16_t p_dspBoxH);
    uint16_t getDspBoxDimH  (void);
    void setDspBoxDims   (uint16_t p_dspBoxW, uint16_t p_dspBoxH);
    // - display box absolute coordinates
    uint16_t g_dspBoxAbsRefX, g_dspBoxAbsRefY;  // set by the container that the current instance belongs to
    void setDspBoxAbsolutRefX   (uint8_t p_x);
    void setDspBoxAbsolutRefY   (uint8_t p_y);
    void setDspBoxAbsolutRefs   (uint8_t p_x, uint8_t p_y);

    // mouse
    // - mouse absolute coordinates
    uint16_t g_mouseAbsRefX,  g_mouseAbsRefY;   // set by the container that the current instance belongs to


---

Thursday, 10th October 2024

- come suddividere l'implementazione del codice
    - i contenitori non dovrebbero interessarsi della fase visualizzazione relativa agli elementi ma solo dei loro aspetti grafici
        - in pratica questo significa che 
            - i contenitori devono gestire liste di elementi [tuiBaseGraphic]
                - quindi come si diceva in prec
            - mentre gli elementi [tui] sono quelli che possono accedere alle funzioni driver di visualizzazione ovvero sono i derivati del modulo [drvTui] (<drv> sta per [driver] e non per derived)

- il modulo [tuiBaseEbox] può essere visto alla stessa stregua del modulo [tuiTextUsartX] ovvero
    - proprietario di un contenitore
- sarebbe quindi da aggiornare il modulo [tuiBaseEbox] aggiornando a sua volta il modulo [dtyBaseArray] facendolo derivare dal modulo [dtyBaseCntnrUnitX]
    - in questo modo si può pensare di uniformare la funzione di [init] dei moduli [tui] anche per i moduli che sono proprietari di contenitori

- come gestire l'inizializzazione "grafica" dei moduli [tui]
    - le coordinate di un modulo tui possono essere 
        - dati alla sua istanziazione
        - oppure dati dal contenitore che li contiene che li ha come "figli"
    - per fare questo si dovrebbe assegnare alle coordinate e alle dimensioni (altezza [H] e larghezza [W]) anche dei valori [undefined]
        - per le coordinate i valori possono essere il massimo valore assegnabile al tipo di dato a cui appartengono ovvero [7f.ff.ff.ff] [int32_t]
            - se [X] e/o [Y] = [7f.ff.ff.ff] allora il il contenitore che li contiene deve assegnargli i valori oppurtuni
            - se le coordinate hanno valori indefiniti non possono essere visualizzabili
        - per le dimensioni semplicemente [0]
            - se [W] = 0; allora [W] = g_dispalyBoxW;
            - se [H] = 0; allora [H] = ? (al momento non saprei dirlo)
    - è da capire bene però quando gestire l'inizializzzazione delle coordinate
        - nel senso che ci possono essere varie situazioni in particolare due
            - [tuiBaseWin]
                - in questo caso la posizione dei componenti all'interno della [tuiBaseWin] devono essere impostati al momento dell'istanziazione
            - [tuiBaseLbox]
                - in questo caso la posizione dei componenti all'interno della [tuiBaseLbox] devono essere impostati dal contenitore ignorando le coordinate dei componenti
                - ma chi lo dice al contenitore di inizializzare le coordinate dei componenti mettendoli "in fila" ad esempio?
                    - naturalmente il proprietario del contenitore!!
                        - quindi la funzione 

- cercando di ragionare bene e quindi di implementare il codice altrettanto bene
    - l'impostazione dei riferimenti assoluti per ciascun elemento non dovrebbe essere fatto nel modulo [tuiBase]
    - e tanto meno dal [figlio] che deve andare a leggere i parametri del [padre] P_PO_FATHER->getRefX0()
    - se possibile sarebbe da fare a meno per quanto riguarda il modulo base [tuiBaseGraphic] di usare il parametro [g_poFather] dal momento che non lo si conosce
        - l'unica cosa permessa dal figlio è assegnare la gestione eventi al padre
            - per evitare di fare anche questa cosa sarebbe da introdurre un puntatore a funzione che il [figlio] chiama per rinunciare alla gestione eventi
    - quindi 
    - l'impostazione dei riferimenti assoluti per ciascun elemento dovrebbe essere fatto nel modulo [container] ovvero dal padre
        - che "sa" di avere figli e che si deve preoccupare quindi di inizializzare
        - certamente però il modulo [dtyBaseCntnrUnitX] non può usarlo perche non può e non deve conoscere, quindi dipendere, dal modulo [tuiBase] da cui deriva il suo proprietario
        - lo puo conoscere il suo derivato [dtyTuiBase]
        - considerare che questo modulo [dtyTuiBase] dovrebbe lavorare solo con il modulo [tuiBaseGraphic]
            - stessa cosa anche per il modulo [dtyStufX] anche se questo 
                - non è un contenitore di elementi grafici [tui]
                - ma in ogni caso si preoccupa delle problematiche della visualizzazione
                    - non ha caso ieri o due giorni fa si diceva che questo modulo si dovrebbe derivare dal modulo [tuiBaseGraphic] oltre naturalmente al modulo [dtyBaseCntnrUnitX]
                        - considerazione a latere
                            - quando possibile si dovrebbe privilegiare il passaggio di variabili a funzione invece di usare delle variabili globali
                                - questo permetterebbe di risparmiare memoria perche i paramteri di funzione occupano solo temporaneamente la memoria
                                - invece le variabili globali occupano memoria in modo permanente
                                    - l'inconveninete del passaggio di parametri sono
                                        - più codice per la chiamata della funzione
                                        - e quindi meno velocità
                                        - e un po' più laborioso da implementare
                                        


- sarebbe poi da semplificare lo schema
    - adesso è il seguente ad esempio
        - [tuiBaseLbox] derived from [tuiBaseCntnrX]
        - [dtyTuiBase] derived from [dtyBaseCntnrUnitX]
    - sarebbe da avere invece
        - [tuiBaseLbox]
        - [dtyTuiBase] derived from [dtyBaseCntnrUnitX]
            - quindi il modulo [tuiBaseLbox] chiama direttamente il container [dtyTuiBase]




---

Wednesday, 9th October 2024

- [tuiDriver] -> [drvTui] 
    - -> [drvTuiIn]
    - -> [drvTuiOut]
- pensare ai driver di secondo livello
    - quelli che dipendono sia dai driver di primo livello che da librerie indipendenti dalla piattaforma
    - infatti il modulo [drvTui] oltre che derivare dai [drvTuiIn] e [drvTuiOut] deriva anche dal modulo [tuiBaseGraphic] indipendente dalla piattaforma

dpdbqbdpdbqbdpdbqbdpdbqbdpdbqbdpdbqbdpdbqb

dpdbqbqpdpdbqbqpdpdbqbqpdpdbqbqpdpdbqbqp

dbqbqp

dbqpdbqpdbqpdbqpdbqpdbqpdbqpdbqpdbqpdbqp

---

Tuesday, 8th October 2024


- ragionamenti sui contenitori
    - ci sono aspetti generali e specifici
        - gli aspetti generali sono trattati nei moduli
            - [tuiBaseCntnrX]
                - da i comandi ai singoli elementi visti come oggetti [tuiBase] come
                    - init
                    - select
                    - display
            - [dtyBaseCntnrUnitX]
                - fornisce l'interfaccia al modulo di cui sopra per interagire con un qualunque contenitore
                    - funzioni di navigazione sugli elementi
                        - selectUp / selectDown
                    - funzioni di visualizzazione
        - gli aspetti specifici sono trattati nei moduli
            - modulo che gestisce un contenitore di dati (ovvero un buffer di blocchi di dati) strutturato in un certo modo specifico
                - [tuiTextUsartX]
                    - [dtyStufX]
                        - [tuiData] (importante!! questo modulo non deve dipendere, non deve fare alcun riferimento al modulo [dtyStufX])
            - modulo [tui] che gestisce liste di elementi [tui]
                - [tuiBaseWin]
                    - [dtyTuiBase]
- all'interno dei moduli specifici
    - [dtyStufX]
    - [dtyTuiBase]
- ci sono aspetti generali quali
    - [insierimento]/[eliminazione]
    - [selezione]/[navigazione]
        - è un aspetto indipendente da parametri grafici
        - riguarda i comandi di navigazione
        - quindi si implementano le funzioni virtuali / le intertfacce fornite dal modulo [dtyBaseCntnrUnitX]
    - [visibilità]
        - è inevitabilmente dipendendente da parametri grafici come
            - coordinate relative
            - dimensioni
                - dell'oggetto "contenuto" da visualizzare
                - dell'oggetto contenitore, l'oggetto che è proprietario del contenitore
            - da notare però che non sono richieste funzioni di visualizzazione
                - quindi sono indipendenti dai driver legati al device preposto alla visualizzazione
        - per implementare questo aspetto è inevitabile dipendere dal modulo [tuiBaseGraphic]
- a questo punto sembrerebbe molto opportuno
    - scindere il modulo [tuiBaseDrawer] in due parti
        - [tuiBaseGraphic]
            - dedicata esclusivamente ai paramertri grafici
                - coordinate assolute e relative
                - dimensioni dell'oggetto
        - [tuiDriver] derived from [tuiBaseGraphic], [tuiDriverOut], [tuiDriverIn]
            - [tuiDriverOut]
                - dedicato alle funzioni di visulalizzzazione quindi dipendente
                    - dalla piattaforma ovvero dal dispositivo usato per la visualizzazione
                    - e dalla parte grafica citata al punto precedente
                        - in particolare questa parte grafica la si acquisisce derivandola
            - [tuiDriverIn]
                - dedicato alle funzioni di input da tastiera e/o da mouse
- i moduli che si trovano più in alto nella gerarichia ovvero
    - [tuiTextUsartX] / [tuiBaseWin] sono quelli che dipendono dal modulo [tuiDriver] e che ne possono chiamare le funzioni pubbliche
        - sono i moduli che chiamano le funzioni di visualizzazione più o meno direttamente


---

Monday, 7th October 2024

- gestione marker
    - la cosa più corretta da fare
        - per poter essere più generali possibili 
    - è quella di definire e gestire i marker all'interno della classe [tuiBase]
- per quanto riguarda la gestione delle funzioni di display quindi dipendenti dal modulo [tuiBaseDrawer]
    - si dovrebbero gestire solo nei moduli tui
    - i moduli dty eventiulamente possono lavoarare con dei puntatori generici [void*]
        - in particolare per i blocchi di dati
            - verrà fornito il container [fisico] (ad esempio il file o il buffer) e poi anche il puntatore all'istanze del modulo [tui]
                - che però verrà fornita come puntatore generico
                    - in questo modo si prendono due piccioni con una fava
                        - il modulo [dty] è indipendente dai moduli [tui]
                        - al container fisico è associato uno specifico modulo [tui], specifico per le sue esigenze
                            - quindi quando fornisco un container fisico come un buffer o un file devo associargli anche un appropriato modulo [tui] di visualizzazione


---

Saturday, 5th October 2024

- le coordinate relative delle windows di primo livello sono svincolate da quelle della finestra root
    - in particolare 

---

Thursday, 3rd October 2024

- qual'è il modo migliore per passare le coordinate del box entro cui i sub elementi di un elemento possono essere visualizzati?
    - questa proprietà interviene solo quando l'elemento ha dei sub elementi
        - quindi il boxChildsDisplay dovrebbe essere associato al container
        - tuttavia per una questione di "ordine" tutto quanto concerne e riguardi le coordinate dovrebbe essere messo nella classe tuiDrawer
            - io propenderei per il momento per quest'ultima impostazione
                - inolre le dimensione del box dedicato ai sub elementi li insierirei in modo inidiretto attarverso i margini
                    - marginTop
                    - marginBottom
                    - marginLeft
                    - marginWrite

---

Wednesday, 2nd October 2024

- separare quella parte di un oggetto tui che riguarda l'appartenenza a qualche altro oggetto tui
    - queste proprietà sono
        - g_poFather
        - coordinate
    - un oggetto/istanza tui per poter essere posizionato in qualunque finestra e quindi appartenere a più oggetti tui
        - si deve preoccupare solo di eseguire azioni in base agli stimoli esterni che gli arrivano quindi attraverso gli handler degli eventi
            - però quando chiama le funzioni di visualizzazione ha bisogno delle coordinate
                - quindi si pone il problema come può ottenere le coordinate adatte per quell'evento
                    - è chiaro a questo punto che la gestione degli eventi ovvero l'intercettazione dell'evento non spetta a lui ma al suo "associato" 
                    - o al suo "proprieatario" che gli dice cosa fare, che gli impartisce il comando chiamando una funzione che lui gli mette a disposizione


---

Tuesday, 1st October 2024


- sequenza delle chiamate quando con un evento da tastiera o del mouse gli elementi all'interno di una finestra vengono spostati
    - evento roll up/down del mouse con la finestra tuiWindowX attiva
        - tuiWindowX::rollUp() => g_cntnr->shiftLoopElementBySelect()
            - dtyBaseCntnrUnitX::loop over all elements
                - dtyBaseCntnrUnitX::shiftLoopElementBySelect() => 
                    - l_delta = tuiElement->getDistanceFromBound()
                    - tuiElement->updCoordNbounds(l_delta)
        - tuiWindowX::rollUp() => g_cntnr->shiftLoopElementRollUp()
            - dtyBaseCntnrUnitX::loop over all elements
                - dtyBaseCntnrUnitX::shiftLoopElementRoll() => 
                    - tuiElement->updCoordNbounds(+/-1)

- la variazione dei limiti può influire sulle coordinate relative quando il limite superiore cambia
    - si considera la coordinata relativa zero in corrispondenza del limite superiore
        - quindi quando il limite superiore cambia, cambierà anche la coordinata relativa
            - ma rimarrà invariata la cooridnata assoluta
    - ASSOLUTAMENTE NO E POI ANCORA NO!!!!
        - la coordinata relativa uguale a zero NON corrisponde al limite superiore queste due caratteristiche sono tra loro indipendenti

- g_displayBoxH e g_displayBoxW sono i parametri del box padre ma si deve aggiungere anche il riferimento assoluto del padre ovvero g_poFather->g_y0Win
    - nell'elemento tuiData gli estremi di visulaizzazione sono 
        - upper bound e lower bound, ciò che interessa sono le coordinate relative rispetto il tuiData (l'elemento, il blocco dati, il record del container), da non confondersi con 
          il display box rappresentato dal tuiTextUsartX ovvero coloi che possiede il contenitore, colui che ospita il contenitore, il proprietaro del contenitore, di questi limiti che sono in coordinate assolute
            - quindi 
                - relBoundUpper = g_y0Win - BoundUpper;
                    - N.B.: per come è definito il BoundUpper avremo che
                    - 0 <= relBoundUpper
                    - inoltre affinchè l'elemento tuiData possa visaulizzare qualcosa del suo contenuto il BoundUpper deve soddisfare la condizione
                    -      relBoundUpper <= g_h-1
                - relBoundLower = g_y0Win - BoundLower;
                    - N.B.: per come è definito il BoundLower avremo che
                    -      relBoundLower <= g_h-1
                    - inoltre affinchè l'elemento tuiData possa visaulizzare qualcosa del suo contenuto il BoundLower deve soddisfare la condizione
                    - 0 <= relBoundLower


---

Friday, 28th September 2024


- g_cntnr.init(g_poFather)

---

Thursday, 26th September 2024

- all'istanza [tuiData] bisogna passargli i seguenti parametri
    - riferimenti al buffer dei dati
        - idStart
        - size
    - riferimenti necessari per la visualizzazione
        - coordinate
            - g_y0Win: coordinata assoluta begin
            - g_h 
        - limiti di visualizzazione
            - g_boundUpper
            - g_boundLower
- getTuiDataInstance(idSelected)
- getTuiDataInstance(idBegin++)
- initTuiDataInstance();

- se il displayBegin è fuori box ovvero
    - bottom < 0
    - oppure
    - y0r > 0
- allora deve cedere il suo posto al 
    - successivo se
        - bottom = y0r + g_h < 0 ovvero g_h < abs(y0r)
    - precedente se
        - y0r > 0
- lo shift UP non può avvenire se 
    - l'ultimo elemento è tale che
        - y0r + g_h < boxH
- lo shift DOWN non può avvenire se
    - se il begin è tale che
        - y0r
        - e
        - lui è il rpimo elemento del container


---

Wednesday, 25th September 2024


- gestione dei blocchi di dati di un container/stream
    - ogni blocco ha una size che ne determina la dimensione all'interno del display-box
- ad un blocco viene assegnata la posizione essendo la struttura sequenziale è possibile conoscere automaticamente la posizione di tutti gli altri
- si deve quindi sempre avre la posizione di un blocco
    - per comodità si può tenere 
        - la posizione del blocco in fondo al display-box e 
        - la posizione del blocco in cima al display-box
- nel caso dello [stream-container]qui si deve definire anche la modalità di visualizzazione o meglio
    - il loop che fornisce ciascuna riga da visualizzare
        - questo è il compito della funzione [setDisplayBoxNextRow]
- ci sono due tipologie di funzioni
    - una e quella che ha lo scopo di aggiornare le cooridinate di ciascuno modulo/blocco
        - naturalmente per il [stream-container] è sufficente aggiornare la coordinata di un singolo blocco
            - per poi ottenere le coordinate di tutti gli altri
        - diversa la cosa è per i moduli/elementi grafici
            - ognuno di questi può essere disposto in modo casuale
                - questo però non è vero per il moculo ListBox
    - l'altra è quella che ha lo scopo di visualizzare gli elementi
        - la funzione di visualizzazione degli elementi
- nel caso dello [stream-container] il modulo corrispondente ovvero il [tuiCntr] si deve occupare anche della visualizzazione diretta dei singoli elementi
    - dal momento che i singoli elementi sono parte integrante dello [stream-container]
    - si dovrebbe creare un componente grafico che eredita solo la classe [tuiDrawer] perchè non ha eventi da gestire quelli li avra solo il componente grafico che lo ospita
    

---

Monday, 23rd September 2024


- la modifica delle coordinate relative [coordY0r] di un oggetto avviene sempre attraverso un [delta]
    - quindi per aggiornare la coordinata relativa di un elemento si usa la funzione [coordYplusDelta(p_delta)]
        - a seguito di questa chiamata se l'elemento ha dei sub elelementi per ciascuno dei sub-elementi chiamerà la funzione [coordYnewFather(p_newFather_y0Win)]
            - a seguito di questa chiamata se l'elemento ha dei sub elelementi per ciascuno dei sub-elementi chiamerà la medesima funzione ovvero  [coordYnewFather(p_newFather_y0Win)]
    - in questo modo tutti gli elementi figli hanno le coordinate aggiornate
- veniamo adesso all'aggiornamento dei [bounds]
    - tutto parte dalla modifica delle coordinate relative [coordY0r]
        - quando vengono modificate le [coordY0r] allora immediatamente devono essere aggiornati anche i limiti [bounds] PRIMA di chiamare le funzioni dei propri sub-elementi
            - l'aggiornamento dei limiti segue due procedure diverse a seconda che sia chiamata la funzione
                - [coordYplusDelta(p_delta)]
                    - in questo caso quello che cambia è la posizione relativa dell'elemento
                - oppure la funzione
                - [coordYnewFather(p_newFather_y0Win)]
                    - in questo caso quello che può cambiare sono i limite del padre dell'elemento
- inizializzazione dei limiti [bounds]
    - si determinano i propri bounds in funzione di quelli del padre

- gestione della visibilità degli elementi 
    - quando c'è una variazione nella posizione degli elementi ovvero quando c'è un roll del mouse
        - come riadattare le coordinate di ciascuno dei sub elementi diretti e nidificati?
        - come definire la visibilità di un elemento?

- main dindow
    - passa ai suoi sub-elementi (level 1) i [bounds_upper_lower]
    - a sua volta i sub-elementi passeranno ai loro sub-elementi (level 2) i [bounds_upper_lower] ma aggiornati con i proprio bounds
        - la regola che viene applicata è la seguente
            - [upper_bound] = MAX([upper_bound_father], [origin_win])
            - [lower_bound] = MIN([lower_bound_father], [origin_win+H/W])
        - è chiaro che quando le coordinate di un elemento cambianno [origin_win] cambieranno anche i suoi limiti [bounds]

- #define MAX(a,b) (a > b) ? a : b


---

Friday, 20th September 2024


- forse il [dtyBaseCntnrUnit_t] non ha bisogno di avere il puntatore al buffer dei dati può lavorare semplicemente sugli indici
    - deve avere tutto quanto necessario per un contenitore
- iniziare ad implementare pensando ad un caso concreto
    - un list box di elementi eventualmente con altezza degli elementi variabile
    - secondo me si può lavorare tutto in astratto nel [dtyBaseCntnrUnit_t] usando solo gli indici, non scordiamoci che questa rimane una classe astratta
        - è la classe concreta che eredita questa che richiderà eventualmente il buffer degli elementi siano essis blocchi di dati o elementi grafici
    - sarebbe quindi da "riscrivere" la classe [dtyBaseCntnrUnit_t] con le indicazioni appena menzionate

- contenitore di elementi [tui]
    - è lui che gestisce la selezione
- un elemento tui inserito in un Lbox 
    - viene selezionato
        - poi per la visualizzazione non è necessario deselezionare graficamante perchè verranno visualizzati di nuovo tutti gli elementi
- [use_case]
    - analis delle possibili situazioni
        - enter su un elemento selezionato non visibile
        - up/down su un elemento selezionato non visibile
- il puntatore all'array di elementi dovrebbe essere sostituito con un oggetto [container] di elementi [tui]
    - questo [container] non non dovrebbe gestire nessun evento non dovrebbe essere a conoscenza degli elementi grafici reali (ovvero non deve dipendere da [tuiBaseDrawer])
    - questo container fa parte dei moduli [dty]
        - quest è però una contraddizione nel momento in cui questo container deve gestire elementi [tui]



- gestione del cursore o della selezione all'interno di un container o di un list box (e forse anche di un edit box, qui infatti la finestra si sposta in modo orizzontale invece che verticale)

- premessa generale
    - la particolarità della selezione ad esempio nel listbox è che il componente selezionato può non essere visibile
    - si devono separare la tabella eventi del mouse da quella dei tasti
        - vedere quanto è problemeatico implementare due tabelle di eventi
- list box
    - spostare la selezione 
        - sel up

---

Monday, 16th September 2024



            // ... -> [CA] -> ... -> [Cur] -> ... -> [selected & start deselectBack procedure]
                // ... -> [CA & eON next] -> [Cur] -> ... -> [eOn] -> [selected & start deselectBack procedure]
                    // ... -> [CA & eON next] -> [Cur & eON] -> [selected & start deselectBack procedure]
                        // ... -> [CA & eON next & eON] -> [Cur & selected & start deselectBack procedure]
                        // ... -> [CA & eON next] -> [Cur] -> ... -> [eOn] -> [selected & start deselectBack procedure]
                // ... -> [CA] -> [Cur]
                //          \-> ... -> [eON next] or
                //          \-> ... -> [selecting]
-----------------------------                
                // ... -> [CA, eON, Cur & selected, start deselectBack procedure]
                //          \-> ... -> [eON next] or
                //          \-> ... -> [selecting]
                    // ... -> [eventOn] -> [CA, selected, Cur & start deselectBack procedure]
                    //                       \-> ... -> [eON next] or
                    //                       \-> ... -> [selecting]
            // ... -> [CA, eventOn, Cur] -> [selected & start deselectBack procedure]
            //          \-> ... -> [eON next] or
            //          \-> ... -> [selecting]
                // ... -> [CA, eventOn, Cur] -> [selected & start deselectBack procedure]
                //          \-> ... -> [eON next] or
                //          \-> ... -> [selecting]
                // ... -> [CA, eventOn, eON next, Cur] -> [selected & start deselectBack procedure]
                // already managed above, 
                // that is
                // ... -> [CA & eON next & eON] -> [Cur & selected & start deselectBack procedure]






- ottenere lo stato di un elemento che deve essere deselezionato
    - it is not [CA] & it is [selected]
        - // ... -> [CA] -> ... -> [Cur_&_selected_&_start_deselectBack_procedure]
    - it is not [CA] & it is not [selected]
        - // ... -> [CA] -> ... -> [Cur] -> ... -> [selected_&_start_deselectBack_procedure]
    - it is [CA] & its own father is [eventOn]
        - [eventOn]->[Cur_&_CA]
    - it is [CA] & it is [selected]
        - [eventOn]->[Cur_&_CA_&_selected]
    - its own father is the common ancestor element and is acquiring the event management
        - // ... -> [CA_eON_next] -> [Cur] -> ... -> [selected_&_start_deselectBack_procedure]
    - its own father is the common ancestor element only (another element is acquiring the event management)
        - that is, the element is on a different branch than the element that is acquiring the event management or is being selected
            - // ... -> [CA] -> [Cur] -> ... -> [selected_&_start_deselectBack_procedure]

    - it is [CA] & it is [selected]
        - ci possono essere due casi
            - [eventOn] -> [CA]
            - [eventOn_&_CA]
    - it is [CA]


- l'elemento che sta per essere selezionato/acquisendo la gestione eventi si trova in un branch diverso da quello dell'elemento selezionato
    - allora il ... -> [CA] -> ... -> [eventOn] -> [selected]
        - tutto passa a [deselect]
- l'elemento che sta per essere selezionato/acquisendo la gestione eventi si trova nello stesso branch di quello dell'elemento selezionato
    - allora il ... -> [CA_&_eventOnNext] -> ... -> [eventOn] -> [selected]
        - caso particolare
            - ... -> [CA_&_eventOnNext] -> [eventOn] -> [selected]
                - [eventOn] passa a [selecting]
            - ... -> [CA_&_eventOnNext_&_eventOn] -> [selected]
                - tutto rimane invariato
    - oppure
    - allora il ... -> [eventOn] -> [CA_&_selected] -> ... -> [eventOnNext]
        - [eventOn] passa [select]
        - caso particolare
            - ... -> [eventOn] -> [CA_&_selected_&__eventOnNext]
                - [eventOn] passa a [select]



- se l'antenato comune è sia eventOn e selected e quindi viene mostrato eventOn lo devo considerare come elemento primo elemento da non deselezionare oppure no?

- use case
    - eON (eventOn Next), eOC (eventOn Current), sN (selectiNg), sD (selecteD), sDA (selecteD Ancestor), sDC (selecteD Common ancestor), rW (root Window)
    - 
- condizioni
    - la root window non può mai essere deselezionata

[rW] -> ... -> [sDC] -> ... -> [sDA] -> [eOC] -> [sD]
                     \  ... -> [eON_sN]  

[rW_eOC_sD] -> [eOC] -> [sD]

[rW_sDA] -> [eOC] -> [sD]

- mi fermo a deselezionare il padre di chi è correntemente selezionato perchè è un antenato comune
    - ma questo antenato comune non può essere più giovane dell'elemento eON e quindi
        - il padre di sD sarà proprio eON e anche sN e quindi
            - SD non deve essere deselezionato

---

Friday, 13th September 2024

- i possibili stati
    - [deselect]
    - [deselect] & [select_graphic_mode]
        - it is a parent of [selected] or [eventOn] element
    


- passaggi tra i vari stati
    - [deSelect]            -> [select]
    - [deSelect]            -> [select] & [eventOn]
        - questo passaggio può essere compiuto solo attraverso il mouse in particolare nella funzione
            - <selectByMouse>
    - [select]              -> [select] & [eventOn]
    - [select]              -> [deSelect]
        - le condizioni in cui NON si deve eseguire il [deselect]
            - se l'elemento che si sta deselezionando è il figlio di quello che si sta selezionando
                - ci si deve però accertare che l'elemento che chiama la deselezione è l'elemento che sta per essere selezionato
                    - se questo non è verificato la deselezione deve essere eseguita
    - [select] & [eventOn]  -> [select]
        - mouse/tasto[home] -> accade quando un elemento cede il controllo degli eventi al padre attraverso 
            - la pressione del tasto [home] 
            - oppure con un click del mouse sul padre
    - [select] & [eventOn]  -> [eventOn]
        - mouse/tasti [up]/[down] -> accade quando un elemento con sub elementi ne seleziona uno per mezzo 
            - dei tasti direzionali 
            - o attraverso il mouse
        - ma questo passaggio non può avvenire per un elemento che non ha sub elementi
            - infatti prima si deve eseguire un [deEventOnNeventOn] e poi [deselectBackNselect]
                - però se l'elemento che si sta deselezionando è il figlio di quello che si sta selezionando questa operazione dovrebbe essere evitata
    - [eventOn]             -> [select]
        - accade quando un elemento con sub elementi restituisce la gestione degli eventi al padre 
            - tasto -> [home]
            - mouse -> l'elemento [eventOn] ha degli elementi e uno dei quali è stato selezionato, avviene un click sul padre dell'elemento [eventOn]
    - [eventOn]             -> [select] & [eventOn]
        - non so se questo passaggio possa mai accadere

- regole per la gestione degli stati di [select], [eventOn] & [deSelect] dei componenti grafici
    - più elementi possono essere nello stato di [select] ma questi elementi deveono essere legati dal vincolo di parentela
        - ovvero se un elemento è [select] allora suo padre deve essere [select]
    - un solo elemento può essere nello stato di [eventOn]
    - non sempre accade che un elmento nello stato di [eventOn] si trovi anche nello stato di [select]
        - questo può essere valido per gli elementi che non hanno sub-elementi da gestire
        - la gestione degli stati di [select] e [eventOn] è diversa per
            - gli elementi che hanno sub-elementi
                - come [tuiBaseWin]
                - come [tuiBaseLbox]
            - gli elementi che non hanno sub-elementi
                - come [tuiBaseEbox]
                - come [tuiBaseDgtInOut]
        - gli elementi che hanno sub elementi
            - possono trovarsi nei seguenti stati
                - [eventOn] & [select]
                - [eventOn]
                - [select]
        - gli elementi che <NON> hanno sub elementi
            - possono trovarsi nei seguenti stati
                - [eventOn] & [select]
                - [select]
        - come si vede gli elementi che <NON> hanno sub elementi
            - quando si trovano nello stato [eventOn] devono trovarsi necessariamente anche nello stato di [select]
            - questa cosa non accade invece per gli elementi con sub-elementi
        - la funzione di [deSelect] <NON> è quella funzione che fa passare un elemento dallo stato di [eventOn]/[select] allo stato di [deSelect]
            - ma è quella funzione che <ELIMINA> lo stato di [select] di un elemento
                - questo significa se un elemento era nello stato di [eventOn] & [select] passa allo stato di [eventOn]
                    - quindi a livello grafico non cambia niente
        - la funzione di [deEventOn]/[deEventOnNeventOn] non ha bisogno del <back>
            - però quando si fa il [deEventOn] di un elemento che non è [select]
                - allora questo elemento si deve preoccupare anche del [deSelect] per poi eseguire su se stesso il [select]
                - un elemento [eventOn] non può passare direttamente allo stato di [deSelect], prima deve passare per lo stato di [select]
        - quando un elemento passa dallo stato di [deSelect] a quello di [select] 
            - deve usare la funzione [deselectBackNselect]
        - quando un elemento passa dallo stat
                

---

Wednesday, 11th September 2024

- non si può
    - NON deselezionare un elemento selezionato e poi selezionarne un altro perche poi chi lo deseleziona
- se è il padre del po_selected a chiamare la funzione di deselezione allora non deselezionare
    - come posso sapere chi ha chiamato la funzione di deselezione?
        - il [p_poDeselectEnd] può essere 
            - il padre dell'elemento che sta per essere selezionato
                - p_poDeselectEnd (= po_selecting->po_Father) == po_selected->po_Father
                    - po_selectNext->po_Father == po_selected->po_Father
                        - deseleziona
                    - altrimenti NON deselezionare
            - oppure l'elemento che sta per essere selezionato
                - se p_poDeselectEnd (= po_selecting) == po_selected->po_Father
                    - allora non devi deselezionare


---

Tuesday, 10th September 2024


- linee di sviluppo
    - creare il componente [tuiBaseButton]
        - poi eseguire i test di 
            - aggiungere blocchi dati al container [tuiTextUsart]/[dtyStuf] prendendoli dal [tuiBaseEbox]/[dtyBaseArray]
            - leggere blocchi dati dal container [tuiTextUsart]/[dtyStuf] trasferendoli al [tuiBaseEbox]/[dtyBaseArray]
    - pensare a come gestire le finestre di messaggi o di immissione dati
        - far comparire una finestra a centro schermo
            - la particolarità di questa finestra è che
                - non fa parte della lista degli elementi di nessun componente quindi in teoria non visibile
                    - ma viene chiamata all'abbisogna
            - la finestra può essere istanziata all'interno della classe del componente che la chiama
                - può anche essere una finestra single-tone istanziabile 
                - quindi una classe statica
            - l'attivazione della tabella eventi viene eseguita al solito nella funzione [eventOn] della finestra
                - quando la finestra di messaggi viene choamata bisogna passargli
                    - il puntatore di colui che la chiama
                    - il puntatore dell'istanza della classe [dtyBaseArray] in cui verrà messo il testo
                - quando la finestra si chiude deve
                    - cancellare se stessa
                    - restituire il controllo al suo chiamante
                        - verrà chiamata una funzione membro del chiamante fatta specificatamente, in particolare
                            - eseguirà la funzione di repaint
                                - la funzione repaint vuole come parametro il [box_t]
                                    - il parametro [box_t] contine l'informazione della posizione e delle dimensioni della finestra che si è appena chiusa
                                    - con il parametro [box_t] è possibile eseguire un [repaint] dei componenti mirato 
                                        - nel senso che il [repaint] verrà eseguito solo dai componenti interessati
                            - eseguirà la funzione di eventOn per riprendere il controllo degli eventi
            - per la gestione degli eventi di mouse
                - sarbbe da fare un aggiornamento all'attuale gestione
                    - la modifica in teoria non dovrebbe essere troppo sconvolgente
                        - si tratta di dare in pasto le coordinate del mouse prima al componente attivo
                            - questo lo si conosce attraverso la varibaile g_poEventOn
                        - e poi eventualmente scorrere tutto l'albero derivante dalla lista degli elementi di ciascun sub-componente
                    - inoltre sarebbe da disabilitare l'attivazione degli altri componenti

---

Saturday, 7th September 2024

- come gestire dei componenti costituiti da più componenti
    - creare i componente base
        - [tuiSubWindow]/[tuiSubWin]
            - questo componente è identico al [tuiBaseWin] eccetto per il fatto che non crea una nuova finestra [ncurses]
        - [tuiButton]
    - e poi creare 
        - [tuiUSART]
    - o aggiornare il componente
        - [tuiAppUSART]

---

Tuesday, 3rd September 2024

- se si può dimostare matematicamente che la scimmia infinita possa realizzare prima o poi ad esempio tutte le opere di shakespeare allora è possibile mettere in discussioni le leggi della termodinamica in particolare quelle che riguardano l'entropia?

- uint16_t g_dsplyBegin;
- uint8_t  g_dsplySize;

- g_dsplyBegin <= [g_position] < (g_dsplyBegin + g_dsplySize);

- [g_position] <= [g_lenght] < (g_dsplyBegin + g_dsplySize)

---

Sunday, 1st September 2024

- dtyString
    - dtyBaseArray
        - le azioni/eventi sono
            - digitare un carattere
                - (g_position == (g_length-1))
                    - update g_str[g_position]; <goForW> (increment [g_position]); increment [g_length]; 
                - (g_position <  (g_length-1))
                    - <shiftAhead> the string at the right of the [g_position] (i.e. g_str[g_position+n+1] = g_str[g_position+n], n >= 0); update g_str[g_position]; <goForW> (increment [g_position]); increment [g_length]; 
            - comando da tastiera
                - up
                    - goToBegin
                - down
                    - goToEnd
                - left
                    - goBackW
                - right
                    - goForW
                - del
                    - (g_position <  (g_length-1))
                        - (<shiftBack> the string at the right of the position (N.B.: [g_position] does not change); decrement [g_length];)
                - backspace
                    - (g_position == (g_length-1))
                        - (<goBackW> (increment [g_position]); decrement [g_length];)
                    - (g_position <  (g_length-1))
                        - (decrement [g_position] & <shiftBack> the string at the right of the [g_position] (i.e. g_str[g_position+n] = g_str[g_position+n+1], n >= 0); decrement [g_length];)
            - comando da mouse
                - select
                    - start select
                    - end select
                - click on component
        - le variabili sono
            - [g_length]:   lunghezza della stringa
            - [g_position]: posizione corrente



---

Friday, 30th August 2024

- gestione della finestra mobile nella visualizzazione delle righe
    - le funzioni da implementare sono le seguenti
        - bEmptyCntnr()
        - displayBeginUp & displayEndUp
            - g_idDisplayDataBegin = getPrevData
        - displayEndDown & displayBeginDown

displayDataBegin = getDisplayBoxNextData(Header, displayDataBegin);


---

Wednesday, 28th August 2024


0x0F4240 -> 1.000.000
                    -> 156 -> 78
0x0f41a4 ->   999.844
                    -> 156
0x0f4108 ->   999.688



0x0F4240 -> 1.000.000
                    -> 18
0x0F422E ->   999.982

0x0F4240 -> 1.000.000
                    -> 40
0x0F4218 ->   999.960   -> nel primo box, quello + piccolo, 



---

Tuesday, 27th August 2024


box_t testLboxBox0 =    {14,30,2,5};
box_t testLboxBox1 =    {14,30,2,45};
                        {5,40,2,85}
                        7, 140, 16, 5
tuiAppUSART_1_t::g_box =        {25, 150, 33,  5};
box_t tuiAppPinPort_t::g_box =  {25,  75,  8, 80};
box_t tuiAppBoard_t::g_box =    {25,  75,  8,  5};
---

Friday, 23rd August 2024


- si dovrebbe creare un modulo [tuiStufBlock] e poi passare al [tuiStuf], in particolare per ogni sua istanza, una lista di [tuiStufBlock]
    - questa lista sarà vuota e verrà inizializzata all'interno della funzione [init] di [tuiBaseCntnrUnit]
    - questo significa dover gestire degli elementi della lista con ampiezza variabile

- si dovrebbe fare un sunto dei puntatori necessari per la gestione della visualizzazione del contenuto dei blocchi di dati
    - visualizzazione degli elementi
        - ci dovrebbe essere un puntatore dedicato per questa funzione
            - si deve tener traccia
                - della riga da visualizzare
                - del limite superiore del blocco dati a cui appartiene la riga
                - del limite inferiore del blocco dati a cui appartiene la riga
            - in pratica
                - del blocco selezionato
                - e all'interno del blocco la porzione di stringa da visualizzare
                - quindi
                    - g_pDisplayBlock
                        - conoscendo il blocco possono conoscere
                            - g_pDisplayDataBegin
                            - g_pDisplayDataSize / g_pDisplayDataEnd
                    - g_pDisplayRow
                - e quindi ci dovrà essere
                    - g_pDisplayBlockCurrent
                    - g_pDisplayBlockBegin
                    - g_pDisplayBlockEnd
                    - g_pDisplayDataCurrent
                    - g_pDisplayDataBegin
                    - g_pDisplayDataEnd
            - nella fase di inizializzazione si dovrà impostare
                - l'origine della finestra
                    - lo si dovrebbe mettere in fondo alla lista
                - il size della finestra
                    - viene dato come parametro nell'inizializzazione dell'istanza
            - e si dovrà determinare
                - la lista di blocchi che rientrano nella finestra di visualizzazione del componente grafico
                    - in particolare il primo blocco da visualizzare
                        - g_pDisplayBlock
    - generale
        - g_pBuf
        - g_bufSize
    - scrittura
        - g_writeBlockCurrent
        - g_writeDataCurrent
    - selezione elemento
        - g_selectBlockCurrent
        - g_selectDataCurrent
    - visualizzazione
        - g_pDisplayBlockCurrent
        - g_pDisplayBlockBegin
        - g_pDisplayBlockEnd
        - g_pDisplayDataCurrent
        - g_pDisplayDataBegin
        - g_pDisplayDataEnd

    


- ricordarsi anche di come gestire la visualizzazione di un blocco che occupa tutto il box escludendo il suo inizio e la sua fine
    - in questo caso il codice del blocco dove lo metto?
        - forse non è necessario mettere il blocco è sufficente gestire i colori associati al marker
    - il blocco è necessario metterlo per differenziare due blocchi eventualmente con lo stesso marker

---

Thursday, 22nd August 2024

- quindi lo schema della struttura potrebbe essere il seguente
    - [buffer] data block container is a bare metal array of uint8_t data type
    - [dtyStuf]([buffer]) -> [dtyBaseCntrUnit]
    - [tuiText] -> [tuiBaseCntrUnit] ([dtyBaseCntrUnit]) -> [tuiBase]



- considerare che il modulo [utyStuf] può essere visto come un contenitore con le caratteristiche di una lista
    - quindi dovrebbe essere un componente che si può confrontare con una lista 
        - a sua volta una lista può contenere varie tipologie di oggetti
            - quindi lo si può considerare una classe template
        - il fatto che si possa confrontare con una lista significa che può ereditare l'interfaccia di una lista
- il modulo  [utyStuf] può tranquillamente sostituire un array di oggetti

- ad esempio la funzione "displayElements" quale modulo dovrebbe implementarla?
    - parto con l'idea che il modulo [utyStuf] si limita a fornire il buffer/stringa della riga selezionata
        - ovvero il modulo [utyStuf] deve essere indipendente dai moduli riguardanti la visualizzazione su supporti fisici quali possono essere LCD, stampanti o altro
            - nel modulo [tuiBaseLbox] chi gestisce l'array di [unitElement] è il modulo [tuiBaseListUnitY]
                - la visualizzazione è demandata all'elemento della lista e quindi è l'elemento della lista che usa le funzioni del modulo [tuiDrawer]
                    - ora nel caso del modulo simil-string [utyStuf], che è un contenitore di dataBlock, è un po' un problema
                    - le possibilità potrebbero essere le seguenti
                        - demandare la visualizzazione delle stringhe allo stesso componente [tuiText] che prenderà come paramatro un oggetto [utyStuf]
                        - creare un modulo [tuiStuf] che eredita da [utyStuf] e [tuiBaseDrawer] sarà poi questo modulo [tuiStuf] ad essere passato al modulo [tuiText]
                            - questa soluzione è da scartare perchè l'oggetto [utyStuf] deve essere definito in altri moduli che non vogliono avere nessuna dipendenza diretta o indiretta con i moduli [tui]
                        - creare un modulo [tuiStuf] che prende come parametro un oggetto [utyStuf] e eredita da [tuiDrawer] 
                            - in questo modo si ritorna alla prima soluzione perche in questo modo [tuiStuf] sarebbe un doppione di [tuiText]
                            - però si potrebbe vedere la cosa in questo modo
                                - [tuiStuf] potrebbe essere l'equivalente del modulo [tuiBaseListUnitY] e
                                - [tuiText] potrebbe essere l'equivalente del modulo [tuiBaseLboxY]
- a questo punto emerge il pensiero, la domanda di
    - come strutturare il codice per gestire i blocchi di dati annidati in altri blocchi di dati?


---

Wednesday, 21st August 2024

- implementare la funzione 
    - void        search          (uint32_t p_pDataStart, uint16_t p_rowSize);

- i vari step di dati dal [bufferone] alle righe del [tuiText]
    - [bufferone]
    - <inputs: origin-row*row_length> -> [block_data_list]
    - <inputs: block_data_list> -> [tuiText_rows_list]

- il [tuiDrawer] chiede al [utyStuf] di fornirgli la lista dei blocchi dati da visualizzare
- il [tuiDrawer] ha bisogno di conoscere il marker associato a ciascun blocco dati
    - il blocco dati dovrà fornire
        - marker
        - puntatore ai dati
        - size
- utyStuf.Search(origin, rowSize)
- utyStuf.nextRow()
- utyStuf.getRowMarker()
- utyStuf.getRowData()
- utyStuf.getRowInfo()


---

Tuesday, 20th August 2024

- probabilmente la classe statica [utyFrmtUsart] può venire sostituita dalla classe dinamica del "tipo" [std::string] che si può chiamare [utyFrmtBuffer]/[utyTermBuf]
    - [utySTBuf]/[utyStuf] -> Serial Terminal bUFfer
    - [utyStuf] -> Serial Terminal bUFfer
    - [utyScuf] -> Serial Comunication bUFfer

- il modulo [utyStuf] forse sarebbe bene suddividerlo in due
    - una parte che gestisce il [bufferone] e l'altra che definisce la struttura del blocco dati
    - perche c'è anche il discorso di ottenere la lista dei blocchi da visdualizzare dati un puntatore e un size

---

Monday, 19th August 2024

- definire i [marker] per [utyFrmtUsart]
    - dobbiamo considerare l'origine
    - quali possibilità ci sono?
        - intanto sarebbe utile distinguere tra
            - i messaggi inviati dal device
                - quindi nella funzione di invio dei messaggi ci dovrà essere una funzione che insierisce nel [logBuffer] il messaggio che si sta inviando o che è stato appena inviato
            - i messaggi ricevuti dal device
                - i messaggi ricevuti nel canale di comunicazione sia esso reale o virtuale
                - nella funzione di ricezione si dovrà inserire una funzione che dopo aver letto quanto ricevuto lo inserisca nel [logBuffer]
            - i messaggi di test inviati sul canale virtuale, come se fosse un terminale esterno, al device
                - ci sarà un componente grafico del tipo textBox che permetta di inserire un buffer di dati nel canale di comunicazione virtuale o reale

- per ogni buffer con una specifica formattazione <XXX> sono associate le classi
    - [tuiText_XXX]
        - eredita [tuiDrawer_XXX]
        - può avere dei comandi specifici per il tipo di formattazione come ad esempio
            - visualizzare alcune informazioni relative ai [marker]
            - aggiornare dei parametri riguardanti la visualizzazione dei dati
                - in formato binario o in formato testo
    - [utyPrtcl_XXX]
        - input
            - stringa/buffer dati "puro"
        - output
            - stringa/buffer dati "formattato"
    - [tuiDrawer_XXX]
        - funzioni di print specifiche per gestire la formattazione <XXX>
- [use_case]
    - [usart]/[serialCom]
    - [testingLog]/[debugLog]
- avremo quindi
    - [tuiTextUsart]
    - [tuiDrawerUsart]
    - [utyFrmtUsart]/[utyPrtclUsart]
        - questa classe è una classe statica e semplicemente fornisce delle funzioni
        - le più importanti delle quali sono le funzioni 
            - di [format]/[inserimento] della formattazione predefinita/cablata all'interno di una stringa
                - <addFormatted>(ptrBufferInput, &textBufferOutput[currentPointer])
            - di [get_format]&[get_string] / [lettura] di una stringa formattata per ottenere 
                - ncursAttribute = arrayAttributeVsMarker[<getMarker>( &textBufferOutput[displayingPointer] )]
                - le informazioni di formattazione
                - i dati / la stringa da visualizzare opportunamente formattata
        - questa classe potrebbe essere una classe <buffer> tipo <string>
            - la sua istanza sarebbe un buffer
                - rxUsart.addFormatted(&textBuffer[currentPointer])


---

Sunday, 18th August 2024

- invece dei [marker] perchè non usare il formato/protocollo [json]?
    - questo va bene solo per i file di testo
        - però perche non portare i file binari in file di testo?
            - l'inconveniente è che si occupa il doppio dello spazio
- vediamo di passare in rassegna tutto il flusso dei dati e delle istruzioni
    - partiamo da un file che vogliamo visualizzare
        - al momento supponiamo in modo del tutto generale che il file sia binario
    - 1. il file verrà caricato in un unico buffer
        - in questa fase di caricamento non viene fatto nessun [parsing]
    - 2. nel sistema si verifica un evento che porta ad inserire dei dati nel buffer
        - l'evento può essere
            - start block
            - add data
            - stop block
        - il [marker] verrà inserito dal gestore dell'evento, colui che legge i dati associati all'evento, attraverso una funzione del modulo [utyPrtcl]
            - in questa fase di inserimento 
                - se i dati sono binary
                    - se i dati [NON] sono inseriti a blocchi (con i blocchi identificati dai [marker])
                        - si dovrà controllare che i dati che si stanno inserendo non contengano il [marker] che si sta inserendo
                            - se lo contengono si dovrà far precedere questa sequenza di dati da un carattere/codice di [esc]
                                - a sua volta il codice di [esc] può essere utilizzato per precedere un carattere di [esc]
                                - il codice di [esc] può essere lo stesso [marker]
                            - questa procedura può essere saltata se si conosce in anticipo la lunghezza dei dati da inserire
                                - in questo modo infatti nel [marker] di inizio si può aggiungere l'informazione della lunghezza dei dati
                    - se invece i dati sono inseriti a blocchi
                        - non c'è bisogno di fare l'analisi dei dati
                    - oppure
                        - per evitare dubbi e rendere forse le cose più semplici possibili
                            - si può pensare di codificare i dati in formato [bcd-hex_ascii] 
                                - in questo caso forse l'unico svantaggio è quello di occupare il doppio dello spazio
    - 3. quando si inseriscono i dati 
        - è bene tenere un contatore in modo da sapere quanti dati contiene un blocco
            - in questo modo nella fase di visualizzazione si può sfruttare questa cosa per essere più veloci
        - sarebbe comando anche avere nel [marker] l'informazione di che tipo di dati siano: binari o testuali
    - 4. i dati adesso devono essere visualizzati
        - colui che gestisce la visualizzazione ovvero il modulo [tuiText] ha i seguenti dati
            - input
                - riferimento della [finestra-mobile] [row_origin]
                - numero di righe da visualizzare [row_number]
                    - numero di caratteri per ciascuna riga [row_lenght]
            - cosa fa la funzione del [utyPrtcl]
                - certamente deve fare un parsing dei dati dall'inizio fino a quando trova un primo [marker]
                - trovato il primo [marker] poi i successivi si ricavano sfruttando l'informazione del blocco dati dal marker
                - come determinare il numero di righe
                    - la prima fase di parsing mantiene il conto dei byte/caratteri analizzati [data_first_num] prima di incontrare il primo [marker]
                        - [row_first_parsing] = [data_first_num] / [row_lenght]
                        - if([data_first_num] % [row_lenght]) [row_first_parsing] + 1;
                    - è anche vero che già nella fase di parsing si può cominciare ad inserire i puntatori delle stringhe da visualizzare
                        - si può tenere un contatore e quando il contatore raggiunge il valore di [row_number] abbiamo finito il lavoro
                    - poi i successivi puntatori saranno
                        - [ptrString]/[n]   = [ptrMarker]+[markerDataInfo]
                        - [ptrString]/[n+1] = [ptrString]/[n] + [row_lenght]
                            - eseguire questa operazione fin quando [ptrString]/[n+1] >= [ptrMarker]/[k+1]
                                - qui bisogna calcolare quanti caratteri stampare per la [ptrString]/[n]
                                    - che sarà uguale a [stringLenght]/[n] = [ptrMarker]/[k+1] - [ptrString]/[n]
                            - oppure fin quando [ptrMarker]/[k+1] - [ptrString]/[n] >= [row_lenght]
                - credo sia necessario fare la copia delle stringhe per poter sfruttare [vwprint] di [ncurs]
                    - questa cosa è necessaria perchè non c'è una funzione [ncurs] che permetta di impostare il numero di caratteri da stampare
                        - ma forse invece c'è
                        - da verificare le seguenti funzioni
                            - mvwadd_wchnstr [curs_add_wchstr])
                                - These functions work faster than waddnstr [curs_addstr].  On the other hand: ...
                            - mvwaddnstr [curs_addstr] 
                            - mvwaddchnstr [curs_addchstr]
                                -  These functions work faster than waddnstr [curs_addstr].  On the other hand: ...
            - [tuiDrawer_printFormattedData(dtyTextXXX.ptrStr)]
                - tutti i parametri grafici
                    - [row_origin]
                    - [row_number]
                    - [row_lenght]
                - sono definiti in [tuiDrawer]
                    - quindi viene proprio naturale demandare l'interazione con [utyPrtcl] al [tuiDrawer]
                        - è giusto però che il [tuiDrawer] non conosca il modulo [dtyText] lui deve gestire solo stringhe che poi è quella che deve passare alle funzioni del modulo [utyPrtcl]
                - come visualizzare la formattazione?
                    - ci deve essere una consocenza a priori
                        - si potrebbe voler visualizzare i marker con colori differenti
                            - ci dovrà quindi essere una [tabella] di corrispondenza tra [colori] e [marker]
                                - quindi i [marker] devono essere "cablati" in modo da permettere di fare questa associazione
                        - usare enum/define per definire i [marker] di una particolare registrazione






'A' = 0x41 -> 0x37 + 0xA
'a' = 0x61 -> 0x57 + 0xA

- conversion
    - from binary to hex-ascii
        - input
            - data
        - output
            - data_ch[0] = (data >> 4) & 0x0F; data_ch[0] += ( data_ch[0] < 0x0A ? 0x30 : 0x37);
            - data_ch[1] =  data       & 0x0F; data_ch[1] += ( data_ch[1] < 0x0A ? 0x30 : 0x37);
    - from hex-ascii to binary
        - input
            - data_ch[0]
            - data_ch[1]
        - output
            - data = nibHi + nibLo;
                - con
                    - nibHi = data_ch[0]; nibHi -= (nibHi < 0x3A ? 0x30 : 0x37); nibHi <<= 4; 
                    - nibLo = data_ch[1]; nibLo -= (nibLo < 0x3A ? 0x30 : 0x37); 


- vediamo di implementare il protocollo per la gestione di file di testo
    - gestione CR/LF
        - [posix] oriented
        - [macOS]
        - [linux]
            - LF
        - [windows]
            - CR.LF
        - [old_macOS] very old
            - CR


---

Saturday, 17th August 2024

- da capire come organizzare il modulo di protocollo [utyPrtcl] e le interazioni con i moduli [dtyText] e [tuiBaseDrawer]
    - inserire dei [marker] all'interno di una stringa 
        - inputs
            - tipo di evento [event_type], stringa
                - al [event_type] deve essere associato 
                    - un codice 
                    - delle informazioni
                        - come ad esempio data/ora dell'evento
                - descrizione della categoria degli eventi
                    - ci possono essere degli eventi
                        - con solo un inizio
                        - con solo una fine
                        - con inizio e fine
                    - come gestire il modulo [utyPrtcl] in modo che sia modulare rispetto l'inserimento di nuovi [marker]/[eventi]?
                        - ci dovrebbe essere una base comune a tutti
                            - <un protocollo di protocollo>
                        - ogni [marker] dovrebbe avere
                            - un [marker_code]
                            - o in alternativa una funzione di [check]
                                - importante però è che i marker non si sovrappongano
                                - quindi ci dovrebbe essere un distributore comune oppure
                                    - ogni [marker] si può auto assegnare un codice ma il gestore lo integra ad esempio con unn numero progressivo
                                    - il gestore fissa anche la lunghezza del [marker]
                    - come visualizzare le informazioni proprie di ciscun [marker]?
                        - certamente il [marker] avrà il suo [parser] (la funzione che eseguirà il parsing della stringà che gli verrà passata)
                            - da cui ricaverà
                                - le informazioni supplementari
                                - la stringa da visualizzare/inserire
            - stringa
- [use_case]
    - visualizzare/scrivere file di testo
    - gestire (visualizzare/scrivere) buffer il cui contenuto sono blocchi di dati/byte racchiusi tra [marker]
        - è il caso 
            - del comunicazione seriale
            - log degli eventi hardware
                - comunicazione seriale
                - stato dei din/dout/ain/aout
                - etc.
- gli utilizzatori più ad alto livello "impongono" ([rsSerial] / [tuiTxtTgd]) i tipi di dati da "registrare" 
    - ad esempio
        - inizio/fine blocco di ricezione
        - inizio/fine blocco di trasmissione
- in base allo [use_case] gli utilizzatori faranno riferimento ad un diverso gestore di [marker]
    - poi creando più gestori si vedra se c'è la possibilità di compattarli
        - solo passando per l'implementazione "reale"ci si può rendere conto di come implementre l'ottimizzazione del codice e delle procedure




---

Friday, 16th August 2024

- è da capire bene come organizzare la struttura dati che conterrà i messaggi arrivati sul canale di comunicazione
    - l'ideale sarebbe assegnare ad ogni elemento il blocco dati che inizia con un marker
        - ancora meglio
            - pensare ad un protocollo
    - quindi in generale la struttura dati sarà una lista di stringhe di lunghezza variabile ed arbitraria

- bisogna capire bene cosa esattamente si vuole far fare al componente che visualizzza i messaggi del canale di comunicazione seriale e possibilmente anche altre cose
    - 1. se devo solo visualizzare
        - significa che 
            - non devo fare nessun inserimento di caratteri e tantomeno di righe all'interno del blocco dati
            - devo avere la possibilità di andare su è giu per le righe
    - 2. devo però aggiungere dati
    - 3. se i riferimenti sono solo quelli dei due punti precedenti allora credo sia possibile e forse anche auspicabile usare un array unico e gigantesco anche di parecchi mega di size
    - effettivamente conviene tener separata ed indipendente la parte di parsing da eseguire in altre situazioni o componenti
    - insieme con il blocco dati ci deve anche essere l'informazione relativa alla posizione dell'ultimo carattere/byte da visualizzare che non è il size del buffer che come si diceva può essere anche dell'ordine delle decine di megabyte
    - modalità di visualizzazione
        - parsing del protocollo
        - visualizzazione in ascii e visualizzazione dei caratteri [.]
        - per il parsing dei dati si potrebbe usare una via di mezzo
        - nella visualizzazione dei messaggi provenienti dalla seriale sarebbe comodo usare il [cr/lf] e questo scombina la gestione della visualizzazione che costringe ad eseguire il parsing
        - il [cr/lf] può essere visto come unn [marker] e quindi vediamo di generalizzare la gestione dei marker
            - a questo punto si può eseguire un parsing nell'ambito della finestra di visualizzazione
                - quindi prendendo il blocco dati che aderisce alla finestra di visualizzazione 
                    - gli si deve fare il parsing per vedere se ci sono dei [marker] che indicano una nuova linea
                    - quindi il componente avrà una lista di stringhe che avrà un numero di elementi uguale a numero di righe - 2 della altezza del componente
                        - queste stringhe non saranno fisse ma dinamiche
                    - sarebbe utile anche avere la segnalazione a quale marker la riga selezionata appartiene
                        - si potrebbe mettere un simbolo sulla prima colonna a sinistra

- cerchiamo adesso di fare un sunto del flusso di istruzioni e di iinterazione tra oggetti
    - partiamo dal basso
        - [tuiBaseDrawer]
            - non deve gestire lui gli oggetti [dty]
                - per i seguenti motivi
                    - ci possono essere più tipologie di [dty]
                        - [dty_container]
                        - [dty_string]
                        - [dty_number]
            - ci deve essere una funzione che abbia le seguenti proprietà
                - input
                    - lista di stringhe
                    - numero di stringhe
                    - origine da cui iniziare a visualizzare le stringhe
                - cosa fa
                    - visualizza le stringhe in base ai parametri passati
        - [tuiBaseText]
            - è lui che definisce il puntatore all'oggetto [dty] e che ne gestisce l'interazione 
            - [use_case] & modalità di interazione
                - 1. devo visualizzare le righe
                    - fornisco 
                        - il numero di righe che voglio visualizzare 
                            - che naturalmente sarà uguale all'altezza del componente , ma questo non sempre è detto
                        - l'origine da cui partire
                        - modalità di codifica ascii
                    - mi attendo che 
                        - venga restituita una lista di stringhe 
                            - che poi darò in pasto all'opportuna funzione del modulo [tuiBaseDrawer]
                                - questo significa che il modulo [dty] si occuperà del parsing e che quindi definirà la lista di stringhe da passare poi alla funzione del [tuiBaseDrawer]
                        - ma anche il puntatore all'ultimo elemento dell'ultima stringa
                    - ora se si vuole anche [formattare] il testo delle stringhe in base ai [marker]
                        - bisogna capire
                            - come passare le informazioni di formattazione al modulo [tuiBaseDrawer] 
                                - ci dovrà essere un "linguaggio comune"
                                - probabilmente la cosa più corretta è quella di far eseguire questo lavoro direttamente al modulo [tuiBaseDrawer]
                                    - si potrebbe pensare ad una classe derivata che gestisce il protocollo e quindi il "linguaggio comune" e questa classe verrà ereditata dai moduli 
                                        - [dty] 
                                        - e [tuiBaseDrawer]
                                            - e quindi a cascata dal modulo [tuiText]
                        
                



---

Thursday, 15th August 2024

- elemento [tuiBaseScroll]
    - partire dai moduli
        - [tuiBaseLboxY]
        - [tuiBaseListElem]
        - [tuiBaseListUnitY]
    - pensando al compnente [scrollable] della [borland] mi fa pensare che possa essere associato al modulo [tuiBaseListElem] o forse [tuiBaseListUnitY]
        - dico [tuiBaseListElem] perchè, come pure questo elemento, il componente [scrollable] non viene derivato ma viene aggiunto come elemento o meglio come lista di elmenti
    - il nocciolo della questione è la gestione della visualizzazione degli elementi aventi un ampiezza variabile
    - dobbiamo anche pensare a come organizzare le [variabili]/[stringhe] da visualizzare nel componente [tuiBaseScroll]
    - gli aspetti di riferimento sono
        - gestione di liste di stinghe di lunghezza variabile
            - queste stringhe non sono date staticamente, conosciute a compile time
            - ma sono ottenute dinamicamnete
                - come?
                    - ad esempio dal parsing di un file
                    - dal parsing di una stringa di lunghezza potenzialmente infinita
        - come usare il componente o meglio i componenti
            - [use_case]
                - visualizzare i messaggi provenienti dal canale di comunicazione seriale sia esso reale o virtuale
                    - quindi il contenuto di un buffer arbitrariamente lungo
                        - oppure una serie di tanti buffer sempre di lunghezza arbitraria ma lunghi al massimo 255 byte
                        - in questo caso bisogna capire bene quale sarà la procedura più conveniente da seguire
                            -  si avrà 
                                - il buffer di comunicazione
                                    - il buffer di comunicazione non deve sapere dell'esistenza di un oggetto che visualizzi il suo contenuto
                                    - colui che legge il buffer di comunicazione è quello che si prende l'impegno di visualizzarlo
                                        - è quindi è quello che gestirà o avrà un contatto con il componente [tuiBaseScroll]
                                        - il componente [dty] deve essere una lista di stringhe quindi [dtyStringList]
                                        - quindi questo componente è quello che legge il [buffer_di_com] ed anche quello che definisce il componente [dtyStringList] e lo aggiorna
                                        - quindi il componente [tuiBaseText]/[tuiScroll] dovrà implementare la funzione [loop] che controlla lo stato del componente [dtyStringList] e se questo risulta modificato attiva la procedura di visualizzazione dell'aggiornamento
                                - la lista di stringhe da visualizzare
                - visualizzare un file di testo
            - cosa devo riscire a fare con questo elemento che visualizza imessaggi sul canale seriale
                - navigare sul testo con anche la possibilità di usare il mouse
                    - [up]/[down] delle righe
                    - [left]/[right] sulla riga selezionata
                    - [scroll] con la rotella del mouse
                - quindi la cosa migliore è quella di crare un elemento della tipologia [uty] specifico per le liste con elmento base [dtyBaseListUnit]
                    - si rammenta che il [dtyBaseUnit] è specifico per i parametri
                    - quindi avremo l'accoppiata [tuiText]/[dtyBaseListUnit] che si confronta con l'accoppiata [tuiBaseDgtInOut]/[dtyBaseUnit]


---

Wednesday, 14th August 2024

- per il momento il componente [tuiBaseLboxY] con i suoi "derivati" lo si può considerare OK
    - anche se si potrebbe pensare ad imploementare l'evento rotella del mouse
        - in questo caso la cosa corretta è quella di rendere indipendenti 
            - current element
            - selected element
            - si dovrà aggiungere le informazioni relative alla posizione della finestra di visualizzazione
            - quando invece l'elemento selezionato è anche attivo lo scroll via mouse è disabilitato
- adesso dobbiamo cominciare a pensare
    - al componente per inserire delle stringhe e quindi dei messaggi da inviare sulla seriale reale/virtuale
    - al componente per visualizzare le stringhe che arrivano dalla seriale
        - qui si dovrà usare un componente [scrollable]
            - lo si può pensare come una lista però non statica ma dinamica
                - in questo caso conviene usare i contenitori del c++
                - direi inoltre di tenere separati i due componenti [tuiBaseLbox]/[tuiBaseListUnitY] e [tuiBaseScroll]
                    - 


---

Tuesday, 13h August 2024


- [origin] dove va definito?
    - [origin] ha le seguenti caratteristiche
        - non è una proprietà di tutti i componenti ma specifiche per i componenti che gestiscono liste di elementi
            - quindi
                - NON VA definita in [tuiBase]
                - NON CONVIENE definirla nel componente che sta in cima come il [tuiBaseLbox] o il [tuiWin]
                - non rimane altro che defnirla in [tuiBaseListUnit]
- può aver senso un elemento selezionato non visibile?
    - perchè no?
        - si potrebbe rendere queste due proprietà tra loro indipendenti
- la fase di [init] dei [sub-element] deve essere separata da quella della loro [visualizzazione]/[display]


---

Monday, 12th August 2024

- improvement of BaseLbox
    - elements without origin coordinate but only high
    - nested Lbox to test
    
- tuiBaseLboxY
    - come gestire la visualizzazione degli elementi in uno spazio limitato
        - deve essere possibile visualizzarli gli elementi, quindi ...
            - la dimensione degli elementi deve essere all'interno delle dimensioni del box del componente [LboxY]
                - in particolare è importante l'altezza ovvero il numero di righe occupate dal sub-elemento
                - per quanto riguarda la lunghezza questa comunque viene preventivamante tagliata e comunque reimpostata
                - per quanto riguarda le coordinate dell'origine anche queste non sono necessarie perchè vengono date in base all'ordine di inserimento all'interno della lista
                    - quindi in linea di principio nel costruttore è sufficente dare solo le altezze (numero di righe occupate) dei sub-elementi
    - ci dovrebbero essere due box
        - un box di dimensione infinita 
        - ed un altro di dimensione finita che è quello che viene visualizzato
            - il box di dimensione finita viene spostato
                - ogni volta che viene spostato deve essere ridisegnato
    - per la visualizzazione degli elementi ci dovrebbe essere una funzione simile a quella del [mouseClicked]
        - si potrebbepensare anche alla modalità [tuiMode_t::notVisible]
        - il mouse è un punto mentre la finestra è un rettangolo anche se ...
            - lo si può ridurre ad una linea se si considera solo lo scorrimento veriticale e non anche quello orizzontale
            - inoltre si inverte la situazione è l'elmento che può essere visto come un punto o più precisamente come un carattere
                - se l'elemento ha un altezza di una riga soltanto!!
            - la posizione degli elementi varia quindi ...
                - ognivolta che si muove il [Lbox] si deve ridisegnre il [Lbox] e quindi i suoi elementi
    - nell'inizializzazione agli elementi viene assegnata la coordinata verticale
        - quando il [Lbox] deve visualizzare gli elementi
            - prima gli chiede se sono visibili, quindi ...
                - prima gli passa l'origine della [finestra-mobile] e la sua dimensione
                - poi chiede al sub-elemento se si trova entro la finestra 
            - se l'elemento è visualizzabile allora viene chiamata la funzione per disegnarlo
                - il sub-elmento è anche in grado di calcolare la coordinta relativa in cui deve essere disegnato
        - la [finestra-mobile] deve essere sincronizzata con l'indice del sub-elemento selezionato e viceversa
            - il [Lbox] tiene attualmente l'indice/puntatore dell'elemento selezionato [g_pCurrentElement]
                - dovrebbe tenere anche l'indice relativo alla [finestra-mobile]
                    - ma forse questo lo può fare il sub-elemento
                        - infatti il sub elemento sa di essere selezionato ed inoltre ha le coordinate relative
                            - quando l'elemento selezionato ha la coordinata relativa al massimo significa che è alla fine della finestra
                            - quando viene selezionato un nuovo elemento
                                - si deve controllare se ridisegnare tutti gli elementi
                                    - l'elemento deselezionato deve diventare non visibile
                                        - gli elementi non visibili sono quelli che hanno una coordinata negativa o superiore al massimo
            - nella fase di init il [Lbox] deve far conoscere al sub-elmento l'ampiezza della [finestra-mobile]
                - questa cosa è giusta?
                    - forse no
                - [Lbox] deve avere dal componente il suo stato in particolare sapere se è selezionato
                    - lui sa anche chi è l'elemento corrente che sarebbe l'elemento selezionato o potenzialmente selezionato
                        - quindi dall'elelmento corrente può conoscere le coordinate relative e quindi è in grado di sapere se l'elemento è visibile o meno
                        - [Lbox] è colui che deve assegnare le coordinate relative ai suoi sub-elementi
                        - in base all'indice del sub-elemento selezionato
                        - [Lbox] deve avere anche la posizione della [finestra-mobile]
                            - il componente [scrollable-pannel] è probabilmente la [finestra-mobile]
                            - quindi la [finestra-mobile] non è una variabile è proprio un oggetto
                                - indice dell'oggetto selezionato - ampiezza della [finestra-mobile] = origine della [finestra-mobile] = indice del primo sub-elemento da visualizzare nella [finestra-mobile]
                                    - se il risultato è minore o uguale a zero signifca che 
                                        - l'origine della [finestra-mobile] è zero
                                        - l'indice del sub-elemento da visualizzare è uguale alla sua coordinata relativa
                    - riassumendo i parametri in gioco sono
                        - [origine] [finestra-mobile]
                        - [ampiezza] [finestra-mobile]
                        - [indice] [sub-elemento]
                        - [coordinate-realtive] [sub-elemento]
                            - quando vengono cambiate le coordinate relative si devono aggiornare anche quelle assolute
                    - si parte con
                        - fase [init]
                            - origine = 0
                            - indice = 0
                            - quando gli elementi vengono visualizzati, quindi nella funzione di init, gli si deve impostare le coordinate realtive
                    - si continua con
                        - fase [next] element
                            - il sub-elemento corrente cambia e quindi anche l'elemento selezionato cambierà
                                - se [id-sub-element-selected]-[ampiezza] < [origine]
                                - allora 
                                    - nessuna procedura di [re-paint] è necessaria
                                    - è sufficente aggiornare lo stato di selezione/deselezione
                                - altrimenti 
                                    - si deve eseguire la procedura di [re-paint]
                                    - si devono visualizzare di nuovo tutti i sub-elementi della finestra-mobile
                                        - si inizia con l'elemento che ha [indice-first-sub-element] = [id-sub-element-selected] - [ampiezza] + 1 = [origin]
                                        - [origine] dovrà anch'essa essere aggiornata
                                        - nella visualizzazione si potrebbe andare a ritroso
                                            - la [coordinata-relativa-to-show] = [id-sub-element-to-show] - [origin]
                                            - ci si ferma quando [id-sub-element-to-show] - [origin] < 0
                                                - se [id-sub-element-to-show] - [origin] = 0 l'elemento è da visualizzare
                        - fase [previous] element
                            - il sub-elemento corrente cambia e quindi anche l'elemento selezionato cambierà
                                - se [id-sub-element-selected] >= [origine]
                                - allora
                                    - nessuna procedura di [re-paint] è necessaria
                                    - è sufficente aggiornare lo stato di selezione/deselezione
                                - altrimenti
                                    - si deve eseguire la procedura di [re-paint]
                                    - si devono visualizzare di nuovo tutti i sub-elementi della finestra-mobile
                                        - si inizia con l'elemento che ha [indice-first-sub-element] = [id-sub-element-selected] - [ampiezza] + 1 = [origin]
                                        - [origine] dovrà anch'essa essere aggiornata
                                        - nella visualizzazione si va in avanti
                                            - la [coordinata-relativa-to-show] = [id-sub-element-to-show] - [origin]
                                            - ci si ferma quando [id-sub-element-to-show] - [origin] = [ampiezza]
                                                - se [id-sub-element-to-show] - [origin] = [ampiezza] l'elemento NON è da visualizzare
                                                    - ma questo elemento è da [resettare] nel senso che deve essere posto non visualizzabile
                                                        - ma ha senso fare questa operazione di reset????
                                                            - forse no
                                                            - quindi nella visualizzazione dei sub-elementi è [tuiBaseListUnitY] che si deve preoccupare della loro visualizzabilità dal momento che ha tutti i dati per farlo e non i componenti stessi anche perchè si sarebbe costretti a passarli tutti in rassegna cosa che richiederebbe più risorse
                                                                - [origin]
                                                                - [ampiezza]
                                                                - [id-sub-element-to-show]


                - non dimenticare che in [Delphi]/[Builder] della [borland] c'era un  componente [scrollable-panel] che permetteva di avere una finestra scrollabile
                    - quindi significa che era un componente di [Lbox] o di [Win]
                        - i sub-elementi poi venivano assegnati al [scrollable-panel] quindi è lo scrollable che è derivato del [tuiBaseListUnitY]
                

---

Sunday, 11th August 2024

- mouse on mainWin
    - enter
        - down
    - enter
        - enter
            - mouse on main    
- gestione degli stati di un componente
    - deselect
    - select
    - eventOn


---

Saturday, 10th August 2024

- gestione degli stati di un componente
    - deselect
    - select
    - eventOn


---

Thursday, 8th August 2024

- [tuiBaseEvents] / [tuiBaseInputs]
- [tuiBaseDrawer] / [tuiBasePrinter] / [tuiBaseOutputs]


---

Wednesday, 7th August 2024

- selextX() sarebbe da rinominarlo in deselectRecursiveNselect() / deselectBackNselect
- deselectX() sarebbe da rinominare in deselectRecursive() / deselectBack

---

Tuesday, 6th August 2024

- gestione eventi mouse nei componenti con lista di lementi
    - il controllo della posizione del mouse all'interno della propria area deve essere aggiornata

---

Sunday, 4th August 2024

- ogni componente [tui] ha le sue caratteristiche "grafiche"
    - e quindi le sue modalità di visualizzazione
        - tutti però hanno
            - [nome]
            - [status]
                - alcuni componenti possono avere più di uno stato
- il problema nasce 
    - dalla gestione delle coordinate di riferimento del [box]
    - e dal disallinemento che c'è con le funzioni di [print]
    - quindi
        - conviene che il box con eventuali suoi [sotto-box] conosca le coordinate assolute del suo riferimento di origine
            - quindi al momento dell'inizializzazione gli devono essere passate queste sue coordinate
- è anche vero però che se si deve visualizzare qualcosa c'è bisogno
    - delle coordinate
    - della modalità select/deselect
    - della stringa da visualizzare

- le tipologie di box possono essere quelle
    - con frame
        - quindi con almeno 3 righe di altezza
        - le funzioni possono essere
            - drawName
                - i parametri potrebbero essere:
                    - coordinate
                    - modalità: select/deselct
            - drawStatus
            - drawInfo
            - draw
                - sarebbe una funzione wrapper delle funzioni 
            - clear
                - all
                - only inside frame
    - senza frame
        - quindi con una o due righe di altezza

- alla fine ad ogni componente [tui] che al momento sono
    - [tuiWin]
    - [tuiDigitalInOut]
    - [tuiLbox]
- sono associati i relativi [box]/[frame]

---

Thursday, 1st August 2024

- come gestire il deSelect degli elementi
    - quando si hanno elmenti annidati ci sono tanti elementi selezionati quanto è il livello di annidamento dell'ultimo elmento selezionato
        - quindi quando, con un evento mouse, si seleziona un elemento di un'altra finestra tutti questi elementi dovrebbero essere deselezionati
            - quindi per gestire la deSelezione sono due le possibilità
                - 1. avere un buffer di elementi selezionati e non un singolo elemento come abbiamo ora
                    - il vantaggio di questo approccio è che il gestore della lista elementi può evitare di preoccuparsi della deselezione
                    - però se invece di avere una variabile statica globale utilizzassimo il passaggio dei parametri quindi
                        - la funzione di deselect ha un parametro in ingresso
                    - usare anche la tecnica/il meccanismo del deSelectBack ovvero quando un elemento viene deselezionato allora a cascata lui chiama anche la funzione di deselect del padre, ci si ferma quando l'elemento che si sta selezionando è uguale all'elementodi cui viene chiamata la funzione di ddeSelect
                        - però questa funzione quando viene chiamata?
                            - a questo punto mi sembra evedente che la funzione di select deve avere due tipologie di comporatmento
                                - uan per gli eventi mouse
                                - un'altra per gli eventi da tastiera
                - 2. evitare la gestione dei buffer e gestire in modo differente un evento mouse da un'evento tastiera
                    - con l'evento tastiera il manager della lista degli elementi si preoccupa della deselezione
    - sarebbe comodo per il manager della lista non occuparsi della deselezione
        - tuttavia a complicare le cose c'è anahce la gestione degli eventi mouse
- la cosa ideale è quella di riuscire ad implementare le funzioni di [select] e [deSelect] a livello del componente [tuiBaseUnit]
    - vediamo come gestire/implementare le funzioni di [select]/[deSelect]
        - vedere la nota corrispondente alla presente ma con estensione .cpp

- la lista dei comonenti [tuiPinPort] tiene memoria dell'ultima selezione fatta con il mouse
    - tiene memoria non solo della selezione da un punto di vista grafico ma anche di variabile interna
    - questo problema emerge quando viene selezionata la finestra

- sarebbe opportuno assegnare ad ogni elemento la finestra su cui deve scrivere è poco pratico usare una variabile globale
    - quindi sostiruire la variabile [statica] [g_ncursWinSelected] con una [non_statica] per ogni istanza
- a pensarci bene si potrebbe creare a compile-time le varie finestre e poi ai componenti [tuiWin] non passargli il parametro [box_t] ma proprio la finestra

---

Wednesday, 31st July 2024

- il current_element non viene gestito correttamente con il moude

- gestione della selezione/deselezione dei componenti
    - a causa della presenza del mouse
        - la deselezione degli elementi selezionati deve essere fatta dall'elemento che è viene selezionato e che quindi sotituisce il precedente
            - per questo motivo è stata introdotta la variabile statica [g_poSelected]
        - forse questa impostazione non serve e poi ha un qualche problema
        - invece si può pensare ad una gestione "partendo dalla radice" però anche con questa si può sfruttare la tecnica del [g_poSelected] che diventerbbe del [g_pWinSelected]
            - e poi eseguire il deselect di tutti i [CurrentElement] in cascata
        - questo lo si fa con gli eventi da [mouse]

- gestione del layout della simulazione 
    - winBoard
    - winPinPort
    - winUSART

    +------------------+ +------------------+
    |    winBoard      | |    winPinPort    |
    |                  | |                  |
    |                  | |                  |
    |                  | |                  |
    +------------------+ +------------------+
    +---------------------------------------+
    |               winUSART                |
    |                                       |
    |                                       |
    |                                       |
    +---------------------------------------+

---

Tuesday, 30th July 2024

- rule management for [tuiWin] objects/instancies
    - qunado una finestra fine selezionata con il mouse allora acquisisce anche la gestione degli eventi da tastiera
    - gli eventi da mouse li gestisce esclusivamante la [winMain]
        - i motivi di questa regola sono i seguenti
            - gli eventi mouse, ragionando bene, sono eventi globali che riguardano sempre la finestra intera
                - non a caso le coordinate vengono date rispetto l'origine della finestra principale
            - infatti anche se è selezionata una sub-finestra, che chiameremo A, il mouse può selezionare un'altra sub-finestra, che chiamaeremo B, di pari livello e della cui esistenza la precedente finestra A non è tenuta ad esserne al corrente
    - la funzione di [eventOn] riguarda esclusivamante la gestione degli eventi da tastiera
        - gli eventi da tastiera 
            - interessano sempre e solo un solo oggetto/istanza
            - non sono condivisi con da più oggetti
        - la funzione [eventOn] imposta
            - la tabella/array degli eventi dell'oggetto attivo
            - il puntatore dell'oggetto attivo che è una variabile statica della classe base, e che quindi può agire sugli handler degli eventi da tastiera
- stati dei componenti/oggetti [tui]
    - deSelect
    - select & inActive
    - select & active

---

Monday, 29th July 2024


- [use_case] nella gestione dei componenti [tui] che fanno uso delle routine [ncurses]
    - inizializzazione
    - selezionare la [main_win] 
    - selezionare una qualunque [sub_win]
    - selezionare un elemento di una qualunque [sub_main]

---

Saturday, 27th July 2024

- gestione delle istanze degli oggetti appartenenti ai moduli
    - [pph]
    - [mcu]
    - [tui]
- ci saranno dei "moduli" (coppie di file .h e .cpp) in cui vengono definite le istanze dei moduli [pph]
    - la definizone delle istanze è una procedura che rigurda il livello applicativo quindi si toveranno nei moduli [apps] o [main]
- potrebbe essere comodo avere la massima libertà di decidere dove definire queste istanze
    - se in un file unico o in file separati
        - se uno decide di usare file separati probabilmente perche vuole o ha bisogno di creare dei moduli
    - rimane comunque ferma la struttura in cui la gestione delle istanze avviene in modo centralizzato con i moduli [manager]

/Users/work/ObsiData/repo__main/notes/docs/cppman/html-book-20230810/reference/en/cpp/language/classes.html
---

Friday, 26th July 2024

- sarebbe utile fare l'elenco di tutte le [regole] che mi sto imponendo di rispettare nel creare la struttura del firmware
    - ottimizzare il codice
    - le librerie hanno al loro interno moduli solo con un certo tipo di dipendenze
    


- la derivazione è un qualcosa di più rigido ma molto più "compattante"
    - nel senso che permette di compattere di più il codice riducendo al minimo le [ridondanze]

- ripensando agli estratti riportati di seguito si potrebbe pensare di
    - derivare certi moduli [pph], quali [pphLed], [pphButton], etc. dai moduli [mcuPinPort] 
        - infatti c'è una corrispondenza biunivoca tra moduli [pph] e moduli [mcuPinPort]
            - anche se questo è vero solo per i moduli [din], [dout], [ain], [aout]
                - non è valido per esempio per il modulo [pphUsart]
                    - sarebbe da distinguere questi due gruppi di moduli
    - poi, per quanto riguarda i collegamenti tra i dispositivi virtuali 
        - si dovrebbe creare un componente specifico, 
            - [pph_wired]
                - questo componente dovrebbe poter connettere anche direttamente due elementi [mcuPinPort]
                - questo elemento lo si potrebbe strutturare in questo modo
                    - creare un calsse che non deriva da [mcuPinPort] ma che ha come parametri due puntatori agli oggetti [mcuPinPort]
                    - oppure creare una classe [mcuPinPort2] in cui si considera una coppia di porte
                        - questa classe, per poter ottimizzare il codice, dovrebbe essere derivata dalla classe [mcuPinPort] 

- estratto del <Sunday, 14th July 2024>
- processes that run
    - [app] <-> [pph] <-> [mcu] <-> [shm]
    - [vhw] <-> [pph] <-> [mcuVhw] <-> [shm]
    - [vhw] <-> [pph] <-> [mcuTui] <-> [ncurses]
    - [vhw] <-> [mcuTui] <-> [ncurses]
                          |  
    -    x               <-> [pph]

- estratto del <Tuesday, 10th July 2024>
    - riassumendo quanto pensato ieri
        - 1. i  moduli [pph] sono quelli che stanno in cima, a più alto livello (quelli che hanno una visione più ampia, che "vedono" più oggetti), rispetto ai moduli [mcu] (i [pinPort], i [usart], etc.)
            - 1. 1. i moduli [mcu] sono subordinati ai moduli [pph] nel senso che vengono usati da questi ultimi ma non sono a conoscenza della loro esistenza
        - 2. i moduli [pph] sono collocati nella libreria [wrapper] questo significa che per ogni piattaforma hanno una diversa implementazione ma hanno un interfaccia comune per tutte le piattaforme
            - 2. 1. i moduli [pph] nelle piattaforme virtuali ([mac]) hanno le funzioni dedicate per la gestione della simulazione identificate con il prefisso [vhw]
                - quasi quasi sarebbe da provare a fare dei moduli a parte e poi integrarli nel modulo [pph] principale attraverso l'operazione di derivazione
            - 2. 2. quest funzioni dedicate sono gestite da un modulo [vhwManager] che naturalmente è presente solo per le piattaforme di simulazione
                - 2. 2. 1. questo modulo gestirà la lista dei moduli [pph], anche questa lista è necessaria solo per le piattaforme di simulazione
            - 2. 3. altri moduli presenti solo nelle piattaforme virtuali sono i moduli [shm]
                - 2. 3. 1. i moduli [shm] stanno alla base ovvero vengono usati senza sapere di esserlo dai moduli [mcu] e [pph]
                - 2. 3. 2. il flusso delle istruzioni è il seguente
                    - [app] <-> [pph] <-> [mcu] <-> [shm]
                    - [vhw] <-> [pph] <-> [shm]
                    - come si vede ci sono due "origini"
                        - una è quella rappresentata dall'applicazione
                        - l'altra è quella rappresentata dalla simulazione
                        - è quasi inutile dire che le due "origini" sono tra loro indipendenti e sono collegate indirettamente attraverso la memoria condivisa ovvero attraverso i moduli [shm]
- estratto del <Tuesday, 9th July 2024>
    - l'operazione/define di [WIRED] sarebbe meglio inglobarla nell'inizializzazione del elemento [pph]
    - veniamo ai link virtuali
        - link tra device virtuali
        - link di più led collegati ad una stessa (dout)
        - link di uno switch collegato a più (din)
    - quando si crea un oggetto [pph] si diceva di eseguire anche il link /l'operazione di wiring con il corrispondente elemento [pinPort]
        - per fare questo collegamento si possono seguire più strade
            - 1. creare l'oggetto mcuPinPort e poi passargli il puntatore
                - tener presente che nel codice dell'applicazione non deve comparire l'oggetto [mcuPinPort] bensi l'oggetto [pph]
                    - quindi volendo non è strettamente necessario collocare gli oggetti [mcu] nella libreria [wrapper_reources]
                    - inoltre gli oggetti [pph] dovrebbero essere collocati nella libreria [wrapper_reources]
                        - ad esempio rsSerial potrebbe essere un elemento della classe [pph]
    - per far "girare" la parte virtuale dei moduli [pph] è necessario aggiungere un processo in background che gestisca opportunamente le funzioni [vhw] dei moduli [pph]
        - questo processo sarebbe implementato nel modulo vhwManager
    - da capire se per collegare gli oggetti [pinPort] al corrispondente oggetto [pph] convenga usare 
        - l'ereditarietà ovvero la classe [pph] deriva dalla classe [pinPort]
        - oppure il puntatore all'oggetto [pinPort] precedentemente definito
            - io direi di prendere questa strada per il momento anche se pensandoci bene la strada dell'ereditarietà sarebbe quella ortodossamente più corretta
                - considerare però che nel caso della [usart] ci sono associati due [pinPort] quello di TX e quello di RX
                    - quindi si dovrebbe fare una doppia derivazione il che può portare a qualche problemino, quindi attenzione
                - vedere adesso come definire al meglio le istanze con i vari parametri di configurazioni non solo per i [pinPort] ma anche per gli [usart]
    - gli oggetti [pph] possono essere categorizzati ad esempio il [led] è un [dout], il [button] è un [din], il [temperature_sensor] è un [ain] e così via
    - bisogna pensare anche alla lista dei [pph] forse è necessario che sia presente solo per la piattaforma di simulazione per le piattaforme reali non credo  necessaria
    - l'idea sarebbe quella di uniformare la configurazione dei [pinPort] per tutte le piattaforme
        - questo forse significa avere il modulo [pinPort] non nelle librerie [sdk] ma in quelle [wrapper]
        - infatti uniformare significa come minimo creare delle interfacce comuni


---

Thursday, 25th July 2024

- l'operazione/define di [WIRED] sarebbe meglio inglobarla nell'inizializzazione del elemento [pph]

- per gestire la configurazione hardware di una piattaforma reale si potrebbero proporre due approcci
    - uno che fa riferimento ai pin del micro con i moduli [mcu]
    - e l'altro che fa riferimento alle periferiche con i moduli [pph]
    - in entrambe gli approcci i moduli sarebbero dei [wrapper]
        - pensare ad una gerarchia di dipendenza in cui/tale che i moduli [pph] dipendano dai moduli [mcu] sarebbe un impostazione un po' ridondante in cui si sprecherebbe del codice
            - l'impostazione [pph] -> [mcu] è da evitare perche ridondante
- gestione moduli [hardware]
    - i moduli hardware sono
        - [mcu] -> si riferiscono al mocrocontrollore
            - questi moduli sono inglobati nell'[SDK] ma volendo si potrebbe portarli ad un livello più alto ovvero all livello dei moduli [wrapper]
        - [pph] -> si riferiscono alle periferiche presenti nella [mother_board] ma anche esterni
            - questi moduli sono 
                - indipendenti dalla [piattaforma] e dalla [applicazione]
            - inoltre ad essi sono associate le varie tabelle per
                - [configurazione_hardware]
                - [configurazione_interfaccia]
        - questi moduli si trovano allo stesso livello di [visibilità] nel senso che
            - rappresentano la stessa tipologia di elemento ovvero [componente_hardware]
                - non a caso sono entrambe derivati dalla classe [vhwUnit]
            - e quindi la cosa corretta è che non devono dipendere l'uno dall'altro
        - questi due gruppi di moduli 
            - nel caso della [simulazione] ovvero della gestione dell'[hardware_virtuale] sono necessari
                - dal momento che una funzione dei moduli [pph] è quella di interfacciarsi con i moduli [tui]
            - però nel caso reale forse questi due gruppi di moduli si sovrappongono
                - tuttavia è bene fare un'analisi più approfondita
                    - i moduli [pph] possono essere usati ad un livello/strato [platform_independent]
                    - mentre i moduli [mcu] necessariamente al massimo possono essere dei [wrapper]
                        - caso [wrapper]
                            - quindi interfaccia comune per tutte le piattaforme
                                - in questo caso i moduli [pph] diventerebbero ridondanti all'interno dell'[applicazione_firmware] e quindi la loro presenza riguarderà solo la piattaforma di [simulazione]
                        - caso [sdk]
                            - quindi interfaccia diversa per ogni piattaforma 
                            - in questo caso i moduli [pph] diventerebbero i [wrapper]
        - nella situazione attuale questi due gruppi di moduli sono tra loro indipendenti
            - quindi la presenza dei moduli [pph] ha il solo scopo di gestire la simulazione relativa all'interfaccia
            - mentre i moduli [mcu] si interfacciano con la i moduli [shm] della shared memory


---

Tuesday, 23rd July 2024

- io direi di procedre come segue
    - implementare il componente [tuiDigitalInOut] come se fosse il componente [tuiPar]
        - alla fine ripensando al progetto dcu il modulo [uiPar] gestisce più tipologie di dati perchè tutti hanno la stessa interfaccia
            - quindi sarebbe da riprendere quel codice è riaggiornarlo eventualmente con una nuova nomenclatura

- sequenza di istanziazione dell'oggetto [tuiDigitalInOut]
    


---

Monday, 22nd July 2024

- gestione componente [tuiDigitalInOut]
    - gestione delle zone
        - alla fine però le zone sono esse stesse dei componenti
            - a questo punto mi viene da pensare a questo componente come un [container]
                - tipo una [listBox] ma con gli elementi in numero prefissato ed in posizione fissa come una [tuiWin] con la differenza che questa può annoverare tra i suoi elementi altre finestre mentre il [container] non può contenere altri [containers] -> [tuiCntnr]
                    - e perchè no?
                - per non complicare troppo le cose è bene che ci sia una gerarchia dei componenti
            - ma allora le zone ha senso pensarle?
                - le zone devono essere viste come elementi che ci si arriva solo via mouse
                    - questa cosa però è un po' bruttina
                        - però a ripensarci bene ... mica tanto
                            - potrebbero essere delle "scorciatoie" di cose che si possono fare con i tasti per altre vie
                                - ad esempio con delle voci di menu oppure ancora meglio con una combianzione di tasti
                    - il principio che deve rimanere fermo è che quello che faccio con il mouse devo riuscire a farlo anche con i tasti e viceversa
                        - eventualmente con una combinazione di tasti e non arrivarci con i tasti direzionali
    - un componente [tuiDigitalInOut] potrebbe essere pensato come un componente derivato del componente [tuiPar] con l'aggiunta della parte "grafica"
        - questo componente può avere tre configurazioni
            - in : sono associati agli input digitali del micro
                - pensare agli [switch], [button]
                - ci deve essere la possibilità di modificarne il valore
            - out: sono associati agli output digitali del micro
                - pensare ai [led], [buzzer]
                - lo stato non può essere modificato dal momento che è impostato dall'applicazione embedded
            - in-out: possono essere associati agli input o agli output del micro
                - pensare al [relay]
                    - è rappresentato da due parametri digitali collegati tra loro da una "regola"/"funzione"
                    - ha anche un parametro che definisce la relazione tra in e out ovvero NormalOpen, NormalClose

---

Sunday, 21st July 2024

- vedere se possibile eseguire l'operazione di deSelect in modo automatico
    - un problema potrebbe essere quando si seleziona un elemento all'interno di una finestra
        - anche la finestra è un elemento che rimane selezionato fintanto che almeno uno dei suoi elementi risulta selezionato
        - c'è anche il discorso della multiselezione
            - ma questa forse fa parte di un'altra parrocchia
    - ci dovrebbe essere una variabile statica anzi due
        - g_pSelected
        - g_pSelectedOld    
    - avere anche due variabili
        - WINDOW* g_ncursWinSelected;
        - WINDOW* g_ncursWinSelectedOld;



---

Thursday, 18th July 2024

- gestione e origanizzazione dei moduli [tui]
    - principi base
        - i moduli [tui] e [pph] non devono conoscersi
        - per far comunicare questi moduli si può usare il metodo dei [tipi_di_dato]/[dataType]
            - quindi la procedura diventerebbe la seguente
                - i moduli [pph] istanziano dei [dataType] che contengo i loro parametri che si vuole rendere "pubblici"
                - le istanze create al punto precedente vengono date, in fase di istanziazione, agli oggetti grafici [tui] che gestiscono i corrispondenti [dataType]
            - quindi il flusso delle dipendenze diventerebbe
                - [pph] -> [dty] object creation
                - [tui] -> [dty] object manipolation (show/modify)
    - ci sono due tipologie di moduli [tui]
        - generale
            - gestisce i componenti grafici classici
                - windows
                - listBox
                - editBox
                - label
                - etc.
        - specifica
            - per il tipo di applicazione
                - questi moduli necessariamente dovranno dipendere dai moduli [pph]
                    - però questa dipendenza la si può evitare creando degli appositi [tipi_di_dato]
                        - che sono del tutto generali
    - i [dataType] possono essere i seguenti
        - [dtyDigitalIn]
        - [dtyDigitalOut]
        - [dtyDigitalInOut]
        - [dtyAnalogIn]
        - [dtyAnalogOut]
        - [dtyAnalogInOut]
        - [dtyText]
        - [dtyUint8]
        - [dtyUint16]
        - [dtyUint32]
        - [dtyInt8]
        - [dtyInt16]
        - [dtyInt32]



---

Tuesday, 16th July 2024

- gestione delle finestre modulo [tuiManager] e [tuiWin]
    - per avere le cose belle "compatte" senza ripetere codice inutilmente 
    - si potrebbe pensare di fondere la classe [tuiManager] e [tuiWin]
        - per capire se questa sia una buona idea la cosa migliore da fare è
            - implementare le due classi suddette e vedere poi se è possibile fonderle insieme
- gestione click del mouse            
    - per gestire gli eventi mouse ogni componente deve avere la lista delle zone in cui è "sensibile" al click del mouse
        - ad ogni zona è associata una funzione che deve essere eseguita quando il mouse ci clicca sopra


---

Monday, 15th July 2024

- gestione moduli [tui]
    - per me ormai è chiaro
        - devono essere creati dei componenti grafici appunto i [tui] 
            - che gestiranno i tipi di dati rappresentati dai moduli [pph]
            - quindi ci dovrà comunque essere una lista dei componenti grafici
                - eventualmente se uno vuole ottimizzare le cose
                    - questa lista può essere creata a runtime leggendola dalla lista degli elementi [pph]
    - a questo punto bisogna cominciare a pensare alla gestione degli eventi di sistema
        - in cui si inseriranno gli eventi da tastiera e da mouse gestiti dai compnenti [tui]
    - i moduli principali sono
        - [tuiUnit]
        - [tuiMain]
        - [tuiWinPage]
            - [tuiMainMenu]
            - [tuiWinBoardLcd]
            - [tuiWinPinPort]
            - [tuiWinUSART]
    - c'è un fattore aggiuntivo che può scombinare i piani
        - la presenza del mouse
            - il [tuiManager] avrà i seguenti compiti
                - leggere/monitorare lo stato di input della [TUI]
                - chiamare la funzione evento dell'elemento correntemente attivo
                - si potrebbe pensare a creare le seguenti finestre
                    - tra parentesi: sono le finestre i contenitori dei vari oggetti
                    - [tuiMenu]
                    - [board]
                    - [pinPort]
                        - avrà la lista di tutti i componenti [pph]
                    - [USART]
                        - per questo tipo di componente sarebbe da assegnare una intera finestra
                - si può anche pensare di avere una lista di finestre
                    - per ciascuna finestra ci sarà 
            - ci possono essere degli eventi generali come ad esempio il focus acquisito da una finestra
                - al momento quello che mi viene in mente è quello di aggiungere un evento [escape] per ogni componente [tui]
            - ad ogni finestra verrà inviato il codice evento della tastiera/mouse
                - ciascuna finestrà deciderà se restituire il codice oppure farlo proprio
            - si dovranno poi aggiornare i dati in tempo reale per ciascun componente
                - per far questo ogni componente avrà una funzione [loop]
                    - compresa la finestra
                        - il [tuiManger] eseguirà ad ogni ciclo la funzione [loop] di ogni finestra a sua volta la finestra eseguira la funzione [loop] di tutti gli elementi di cui è composta
            - la filosofia è quella delle "scatole cinesi"
                - il [tuiManager] gestisce solo i moduli [tuiWin]
                    - i moduli [tuiWin] gestiscono i moduli [tuiUnit]




---

Sunday, 14th July 2024

- per gestire la [TUI] dei singoli moduli [pph] conviene creare una classe [tuiPinPort] e [tuiUSART]
    - questi moduli sono quelli che si interfacciano con la libreria [ncurses]
    - i moduli [tui] necessitano di informazioni che riguardano i moduli [pph]
        - [tuiInit]
            - visualizza il componente
        - [tuiUpdate]
            - aggiorna lo stato del componente
            - controlla gli input per la modifica dello stato dei componenti
    - le variabili/parametri sono
        - [riga]->[tuiVariable] dove visualizzare i parametri del componente
            - questa verrà passata al componente dal [tuiManager]
        - [component_name]->[tuiVariable]
        - [device_id], [port], [pin], in/out
    - forse i moduli [tui] devono satre ad un layer più alto dei [pph] e quindi questi non devono essere a conoscenza dei moduli [tui]
        - ci dovrebbero essere due tipologia di moduli [tui]
            - [tuiPinPort]
                - questi moduli per lavorare con i moduli [pph] richiedono ai moduli [pph] di ereditare un interfaccia comune [tuiUnit] come nel caso dell [vhwUnit]
                - come istanziare i moduli [tui]
                    - c'è qualche problemino di fare le cose due volte e non va bene
                        - è sufficente avere una sola lista dei componenti [pph]
                            - [vhw] -> back-end  process -> [vhwUnit]
                            - [tui] -> front-end process -> [tuiUnit]
            - [tuiUSART]
    - forse, e ripeto forse, la procedura più lineare da seguire è quello di creare una classe singleTone [tuiPinPortManager]
        - è fare ereditare ad ogni modulo [pph] l'interfaccia (classe virtuale) [tuiPinPortUnit] o forse ampliare l'interfaccia rappresentata dalla classe [vhwUnit]
    - ci sarà quindi anche un modulo [tuiManger]
- analisi della classe [tuiPinPortManager]
    - funzione [plotElement]
        - dall'elemento [pph] attraverso l'interfaccia comune [tuiPinPortUnit] ottiene
            - i dati da visualizzare
                - [id_device]
                - [pin], [port], in/out, digital/analog
                - [status]/[value]
    - funzione [updateStatus]
        - analizza gli ingressi che l'utente immette con le funzioni di [ncurses]
            - usa le funzioni dell'interfaccia [vhw] per aggiornare lo stato del componente



- processes that run
    - [app] <-> [pph] <-> [mcu] <-> [shm]
    - [vhw] <-> [pph] <-> [mcuVhw] <-> [shm]
    - [vhw] <-> [pph] <-> [mcuTui] <-> [ncurses]
    - [vhw] <-> [mcuTui] <-> [ncurses]
                          |  
    -    _               <-> [pph]

- procedura di inserimento nuovo device per la gestione della memoria condivisa
    - sarebbe bene accertarsi che l'identificativo del device sia diverso da tutti gli altri
        - nel caso sia uguale a qualcuno visualizzare un messaggio

- gestione della GUI per ciascun elemento
    - Led
        - |<led name>| (on/off)
            - descrizione dello stato
                - cambiare colore della scritta in base allo stato
    - Button
        - |<button name>| (pressed/released)
            - descrizione dello stato
                - cambiare colore della scritta in base allo stato
            - modifica dello stato
                - ci sono due possibilità
                    - clickare sul nome
                    - associare al button un tasto della tastiera del pc
    - Rely
        - |<rely name>|(in: high/low; out: close/open)
    - Switch
        - |<switch name>|(on/off)
            - descrizione dello stato
                - cambiare colore della scritta in base allo stato
            - modifica dello stato
                - cliccare sul nome 
                - oppure selezionare il nome 
                    - e poi usare ad esempio 
                        - il tasto up per impostare lo stato su on 
                        - il tasto down per impostare lo stato su off
    - USART
        - per la gestione della USART credo convenga considerare due finestre una per la parte di [device_input/debug_send] e l'altra per la parte di [device_output/debug_received]
        - 
~-~-~-~-~-~-~-
|    ON    | <from id device output> |<led name>         |<towards id device input>|          |
_    ON    _ <from id device output> |<led name>         _<towards id device input>_          _
|          | <from id device output> |<button name>      |<towards id device input>| released |
|   high   | <from id device output> |<rely name>        |<towards id device input>|  closed  |
|          | <from id device output> |<switch name>      |<towards id device input>|    ON    |
|   24,7   | <from id device output> |<temp sensor name> |<towards id device input>|          |
|    56    | <from id device output> |<humy sensor name> |<towards id device input>|          |
|          | <from id device output> |<level name>       |<towards id device input>|   2,5  V |
~-~-~-~-~-~-~-
| <message to send/sended>         | <message received>       |
| clear                            | 
| send                             | 
| new message                      | 
| send byte after byte             | 
~-~-~-~-~-~-~-

p

---

Friday, 12th July 2024

- continuiamo con l'implementazione delle classi statiche [manager]
    - io direi di partire dall'inizio con il 
        - [vhwManager]

- pensare a come gestire l'interfaccia utente per gestire i moduli relativi all'hardware virtuale
    - capire come simulare
        - button
        - led
        - rely
        - switch

~-~-~-~-~-~-~-
LED

| L1 | L2 |
| O  | O  |
~-~-~-~-~-~-~-

~-~-~-~-~-~-~-
RELAY

| RLY1    | RLY2    | 
| IN  OUT | IN  OUT |
| L/H O/C | L/H O/C |
   x         x
~-~-~-~-~-~-~-

~-~-~-~-~-~-~-
SWITCH

| SW1    | SW2    | 
| ON/OFF | ON/OFF | 
   x        x
~-~-~-~-~-~-~-

---

Thursday, 11th July 2024

- iniziamo ad implementare la classe [pphRely]
    - iniziamo a definire le macro per la definizione delle istanze
    - implementazione delle funzioni
        - [vhwInit]
            - chiama la funzione [vhwInit] relativa ai due oggetti [mcuPinPort]
                - questa funzione inizializza la shared memory
                    - si diceva però che per il momento sarebbe meglio inizializzare i moduli [shm] a parte
                    - la cosa ideale è quella di usare una classe singleton con un costruttore privato
        - [vhwLoop]

---

Wednesday, 10th July 2024

- per quanto riguarda la gestione dei collegamenti tra due device virtuali si può procedere come segue
    - usare il [pphRely] 
        - il [pphRelay] ha due collegamenti uno in ingresso l'altro in uscita
- funzionamento interno del modulo [pphRely]
    - <use case>
        - 1. nel processo dell'applicazione ad un certo punto c'è un istruzione che chiama [pphRelyAlarm->Close()]
            - device A
                - il modulo [pphRely] aggiornerà lo status
                    - si rammenta che non c'è bisgno di chiamare nessuna funzione del modulo subordinato [shmPinPort] dal momento che la variabile che contiene il valore dello [status] è stata [linkata] in fase di inizializzazione alla shared memory
                - nel frattempo anche il processo parallelo di virtualizzazione sta girando e periodicamente 
                    - chiama la funzione [pphRelyAlarm->vhwStatusGet()] per aggiornare lo stato sulla [dashboard] del componente virtuale [pphRelyAlarm]
                        - sulla [dashboard] del componente comparirà lo stato sia dell'ingresso che dell'uscita in particole gli stati dell'ingresso saranno [high]/[low] gli stati di uscita saranno [open]/[close]
                    - inoltre eseguirà anche l'aggiornamento dello stato in uscita del componente virtuale [pphRelyAlarm] quello che poi verrà letto nel device B
                        - naturalmente questo aggiornamento non verrà fatto nel device B dal monento che il segnale sul relè è in uscita
            - device B
                - il processo dell'applicazione periodicamente chiama la funzione [pphRelyAlarm->StatusGet()]
                - il processo di virtualizzazione sta girando e periodicamente esegue le seguenti procedure
                    - aggiornamento [dashboard]
                    - impostazione [status]
                        - nel caso il puntatore all'oggetto [mcu] di input al rely è nullo allora
                            - si da la possibilità all'utente attraverso la [dashboard] di modificare lo stato del rely
                        - in caso contario come il presente in cui l'output del rele è collegato ad un altro device la possibilità di modificare lo stato deve essere disabilitata perchè lo modificherà l'altro device
    - per poter far girare quanto descritto nello <use case> [1] si dovrebbe
        - avere la lista di tutti i moduli [pph]
        - questa lista sarà "spazzolata" 
            - all'inizio eseguendo le funzioni [vhwInit] di tutti i sui elementi
            - e poi periodicamante all'interno della funzione [loop] del modulo [vhwManager] eseguendo le funzioni [vhwLoop] di tutti i suoi elementi
        - questa lista andrà compilata in fase di configurazione dell'applicazione e quindi dovrà essere localizzata nel modulo [main_app]
            - questa lista sarà comodo collocarla  nello stesso file della definzione delle istanze dei moduli [pph]


- riassumendo quanto pensato ieri
    - 1. i  moduli [pph] sono quelli che stanno in cima, a più alto livello (quelli che hanno una visione più ampia, che "vedono" più oggetti), rispetto ai moduli [mcu] (i [pinPort], i [usart], etc.)
        - 1. 1. i moduli [mcu] sono subordinati ai moduli [pph] nel senso che vengono usati da questi ultimi ma non sono a conoscenza della loro esistenza
    - 2. i moduli [pph] sono collocati nella libreria [wrapper] questo significa che per ogni piattaforma hanno una diversa implementazione ma hanno un interfaccia comune per tutte le piattaforme
        - 2. 1. i moduli [pph] nelle piattaforme virtuali ([mac]) hanno le funzioni dedicate per la gestione della simulazione identificate con il prefisso [vhw]
            - quasi quasi sarebbe da provare a fare dei moduli a parte e poi integrarli nel modulo [pph] principale attraverso l'operazione di derivazione
        - 2. 2. quest funzioni dedicate sono gestite da un modulo [vhwManager] che naturalmente è presente solo per le piattaforme di simulazione
            - 2. 2. 1. questo modulo gestirà la lista dei moduli [pph], anche questa lista è necessaria solo per le piattaforme di simulazione
        - 2. 3. altri moduli presenti solo nelle piattaforme virtuali sono i moduli [shm]
            - 2. 3. 1. i moduli [shm] stanno alla base ovvero vengono usati senza sapere di esserlo dai moduli [mcu] e [pph]
            - 2. 3. 2. il flusso delle istruzioni è il seguente
                - [app] <-> [pph] <-> [mcu] <-> [shm]
                - [vhw] <-> [pph] <-> [shm]
                - come si vede ci sono due "origini"
                    - una è quella rappresentata dall'applicazione
                    - l'altra è quella rappresentata dalla simulazione
                    - è quasi inutile dire che le due "origini" sono tra loro indipendenti e sono collegate indirettamente attraverso la memoria condivisa ovvero attraverso i moduli [shm]

- iniziamo a impostare le interfacce dei moduli [pph], [mcu] e [shm]
    - gli elementi chiave sono
        - <constructor> function
            - tipicamente agisce a compile-time invece che a run-time dal momento che ove possibile si preferisce istanziare gli oggetti staticamente e non dinamicamnete attarverso l'istruzione <new>
        - <init> function
            - per i moduli [pph] e [mcu] ci dovrebbero essere due funzioni di init
                - uno per il flusso proveniente dal layer [app]
                - l'altro per il flusso proveniente dal layer [vhw]
        - <loop> function
            - questa funzione è presente solo per le piattaforme di simulazione

---

Tuesday, 9th July 2024

- diciamo che per la progettazione dei wrapper non sarebbe necessario definire un interfaccia comune per la gestione dei pinPort
    - importante invece è definire un interfaccia comune per le periferiche che ad essi sono collegati come ad esempio led, switch, button
        - consideriamo il caso di una piattaforma reale si può procedere come segue
            - definire i due oggetti [pph] e [pinPort] separatamente e poi unirli per mezzo di una tabella
            - definire "solamente" l'oggetto [pph], all'interno del modulo [pph] verrà implementatala parte relativa alla gestione dei [pinPort]
- [LED_ALARM_PORT], [LED_ALARM_PIN]

- pph(<mcuID>,<name>, <pinPort>)
- pph(<mcuID>,<name>), pinPort(<mcuID>,<PORT>,<PIN>)
- attualmente la configurazione e definizione dei pin relativi all'applicazzione avviene all'interno di funzioni quindi con modifica del codice sorgente
    - potrebbe essere utile definire i pinPort attraverso istanze di una classe pinPort
        - quindi la fase di inizializzazione della board consisterebbe nella definizione di istanze e non nella mdoifica di codice
        - potrebbe comunque esssere utile avere una lista di tutte le configurazioni dei [pinPort]
            - questo può essere fatto definendo una classe pinPort e creando le istanze a questa classe
                - poi si può fare una ricerca di dove sono definite tutte le istanze
                - quindi conviene definire le istanze dei piPort all'interno dei mdouli [pph] che le usano
                    - per l'implementazione delle [pph]
                        - la definizione dei [pinPort] deve avvenire in file [Tbl] localizzati nel modulo [main_app]
                            - questa definizione però deve essere diversa per ciascuna piattaforma quindi non andra sotto la directory common

- vediamo come procedere
    - cosa mi piacerebbe avere come oggetti da usare per gestire l'hardware di una piattaforma reale o virtuale?
        - nel codice dell'applicazione dovrei avere le seguenti funzioni
            - definizione
                - pphLed led_pippo = {pinPort}
            - all'interno dell'init
                - led_pippo->init()
            - all'interno del loop
                - led_pippo->on() / led_pippo->off()
                - led_pippo_status = led_pippo->vhwStatus()
                - switch_status = switch_pluto->status();
                - switch_pluto->vhwOn() / switch_pluto->vhwOff()
                    - queste funzioni sono quelle legate all'hardware virtuale e saranno presenti solo nel caso di piattaforme virtuali di simulazione
                - led_pippo->loop()
                    - questa funzione è presente solo nel caso di hardware virtuale e interagisce con le funzioni di shared memory ovvero del modulo [shmPinPort]
                        - la shared memory è legata al [pinPort] fa parte del pinPort e viene poi "linkata" all'elelemnto [pph]
                        - l'inizializzazione del pphLed consiste anche ed in special modo nel link al [pinPort] e quindi, nel caso di hardware virtuale, nel link "indiretto" al [shmPinPort]
                - l'operazione/define di [WIRED] sarebbe meglio inglobarla nell'inizializzazione del elemento [pph]
                - veniamo ai link virtuali
                    - link tra device virtuali
                    - link di più led collegati ad una stessa (dout)
                    - link di uno switch collegato a più (din)
                - quando si crea un oggetto [pph] si diceva di eseguire anche il link /l'operazione di wiring con il corrispondente elemento [pinPort]
                    - per fare questo collegamento si possono seguire più strade
                        - 1. creare l'oggetto mcuPinPort e poi passargli il puntatore
                            - tener presente che nel codice dell'applicazione non deve comparire l'oggetto [mcuPinPort] bensi l'oggetto [pph]
                                - quindi volendo non è strettamente necessario collocare gli oggetti [mcu] nella libreria [wrapper_reources]
                                - inoltre gli oggetti [pph] dovrebbero essere collocati nella libreria [wrapper_reources]
                                    - ad esempio rsSerial potrebbe essere un elemento della classe [pph]
                - per far "girare" la parte virtuale dei moduli [pph] è necessario aggiungere un processo in background che gestisca opportunamente le funzioni [vhw] dei moduli [pph]
                    - questo processo sarebbe implementato nel modulo vhwManager
                - da capire se per collegare gli oggetti [pinPort] al corrispondente oggetto [pph] convenga usare 
                    - l'ereditarietà ovvero la classe [pph] deriva dalla classe [pinPort]
                    - oppure il puntatore all'oggetto [pinPort] precedentemente definito
                        - io direi di prendere questa strada per il momento anche se pensandoci bene la strada dell'ereditarietà sarebbe quella ortodossamente più corretta
                            - considerare però che nel caso della [usart] ci sono associati due [pinPort] quello di TX e quello di RX
                                - quindi si dovrebbe fare una doppia derivazione il che può portare a qualche problemino, quindi attenzione
                            - vedere adesso come definire al meglio le istanze con i vari parametri di configurazioni non solo per i [pinPort] ma anche per gli [usart]
                - gli oggetti [pph] possono essere categorizzati ad esempio il [led] è un [dout], il [button] è un [din], il [temperature_sensor] è un [ain] e così via
                - bisogna pensare anche alla lista dei [pph] forse è necessario che sia presente solo per la piattaforma di simulazione per le piattaforme reali non credo sia necessaria
                - l'idea sarebbe quella di uniformare la configurazione dei [pinPort] per tutte le piattaforme
                    - questo forse significa avere il modulo [pinPort] non nelle librerie [sdk] ma in quelle [wrapper]
                    - infatti uniformare significa come minimo creare delle interfacce comuni
                    
---

Monday, 8th July 2024

- gestione delle inizializzazioni
    - potrebbe essere utile uno schema/struttura di questo tipo
        - dei moduli (A) dipendono da altri moduli (B) che possono essere delle classi singletone ovvero totalmente statiche
            - i moduli (B) devono essere inizializzati
                - più moduli (A) chiamano un preciso modulo singletone (B)
                    - l'ideale sarebbe che
                        - quando un modulo (A) chiama il modulo sigletone (B) e nel caso questo non sia inizializzato fare in modo di eseguire la procedura di inizializzazione
                        - se poi arriva un altro modulo (A) che chiama il modulo singletone (B) naturalmente non deve ripetere la procedura di inizializzazioe
                    - questa cosa la si potrebbe realizzare usando lo statagemma di crere un costruttore della classe (B) privato e chiamarlo in modo indiretto

- analizzare il wrapper per la gestione delle porte
    - il modulo potrebbe essere hwPinPort
    - ci dovrebbe essere una lista delle istanze con tutti i pin configurati
        - compresi i pin per la comunicvazione
    - le tabelle contenenti le istanze dei pinPort devono essere necessariamente diverse tra le piattaforme reali e quelle simulate
        - in quelle reali è sufficente avere la lista dei pinPort
        - nella piattaforma simulata è conveniente avere oltre le istanze dei pinPort anche quelle delle periferiche hardware virtuali
            - quindi la tabella diventa una specie di matrice
                - questa matrice dipende dall'applicazione e dalla piattaforma quindi dovrà essere localizzata nel modulo main
- in cosa consiste la configurazione della piattaforma
    - configurare il microcontrollore
        - configurazione dei registri interni
            - clock
            - memoria
            - etc
        - configurazione delle periferiche del micro quelle che si interfacciano con l'esterno
            - GPIO
            - USART
            - i2c
            - spi
            - lcd
- come organizzare i moduli nel caso di una piattaforma "reale"
    - [hwManager]
        - [mcu]
            - clock
            - thread
        - [pph]
            - pin port
            - usart
            - i2c
            - spi
            - lcd
    - configurazione dei registri del micro e delle sue periferiche per poter gestire i componenti presenti nella mother board e quelli esterni ad essa
        - modulo [usart]
            - quando lo si configura bisogna sapere quali sono i pin del micro da usare per il canale USART
                - [pinPort_Configuration] si deve decidere come inizializzare i pin del micro
                    - se gestirli in modo centralizzato o distribuito e quindi configurarli nei mdouli che li utilizzano
                        - potrebbe essere interessante  organizzarsi in questo modo
                            - focalizzare l'attenzione non sui pinPort ma sulle periferiche hw ad essi associate
                                - in questo modo si riuscirebbe ad unire le piattaforme virtuali con quelle reali
                                    - questo significa che i moduli che devono essere in cima ovvero quelli che vedono gli altri ma che dagli altri non vengono visti sono i moduli [pph]
                                        - la "matrice" dei collegamenti dovrà essere rivista
                                        - sarà sostituita dalla più semplice tabella delle periferiche del tipo [wired] ovvero quelle che sono collegate e gestite attraverso i pin del micro
                                            - questa tabella conterrà la lista delle periferiche e queste poi inizializzeranno i pinPort
- point of view
    - old
        - [mcu]
            - [pph]
            - [shm]
    - new
        - [pph]
            - [mcu]
            - [shm]


---

Sunday, 7th July 2024

- c'è 
    - il virtual hardware rappresentato dai moduli
        - [pph] e [shm]
- e c'é
    - l'sdk rappresentato dai moduli
        - [mcu]

- ribadisco che i moduli [mcu], [pph] devono essere tra loro indipendenti
    - la loro interazione deve avvenire solo per mezzo dei moduli
        - [vhw]
            - questo modulo si preoccupa della
                - inizializzazione dei tre sotto-moduli [shm], [mcu] e [pph]
                    - l'inizializzazione consiste
                - esecuzione delle funzioni "loop" dei tre sotto-moduli appena citati
        - [shm]

---

Saturday, 6th July 2024


- analisi dei moduli
    - [vhwManager]
        - probelmatiche da gestire
            - chi, e quindi come, deve inizializzare i sotto-moduli [shm], [mcu] e [pph]
                - una possibile e interessante risposta è
                    - ciascun modulo [shmManager], [mcuManager] e [pphManager] eseguendo il parsing della matrice dei collegamenti
                - un altra possibile alternativa è quella di 
                    - prima inizializzare la base ovvero i moduli [shm]
                    - e poi inizializzare i moduli [mcu] e [pph] che si appoggiano sui moduli base [shm]
            - moduli [USART]
                - come impostare il canale di comunicazione quando ci sono pià canali attivi
                    - il modulo [mcuUSART]
        - [shmManager]
            - scopo: fornire ai due seguenti mdouli un mezzo che gli permetta di interagire, anche in  modo inconsapevole, l'uno con altro;
                - questo mezzo è la memoria condivisa
                - per gestire la memoria condivisa, ed in  partcolare gli aspetti di "semaforizzazione", è importante conoscere il [pid] associato a ciascun processo che sta "girando" e che userà (leggerà/scriverà) la memoria condivisa; questo parametro, il [pid], lo deve conoscere il modulo [mcuManager] che lo passerà in particolare al modulo 
                - nel particolare il modulo [shmManager] gestisce la "semaforizzazione" dei processi che gli permetteranno di leggere e scrive nella memoria condivisa in modo indisturbato
        - [mcuManager]
            - scopo: simulare il comportamento di un microcontrollore
            - sotto-moduli: ne avrà tanti quante sono le periferiche del microcontrollore
            - implementazione
                - gestione dei sotto-moduli
                    - i sotto-moduli sono gestiti in modo anonimo nel senso che
                        - il modulo manager legge una tabella i cui elementi sono istanze di oggetti aventi tutti un interfaccia comune definita dal modulo [vhwUnit]
                    - i sotto-moduli [mcu] dipendono dai corrispettivi sotto-moduli [shm] nel senso che faranno uso di alcune delle funzioni che questi ultimi mettono a disposizione di tutti ovvero definiti nella sezione public della corrispondente classe
                        - questa affermazione è valida in particolare per il modulo [mcuUSART] ma non per esempio per il modulo [mcuPinPort]
                        - il motivo di questo differente comportamento sta nel fatto di una differente natura dell'informazione che "transita" sul canale di comunicazione seriale o sul pin di una porta
                            - affinche la simulazione del canale possa funzionare è necessario che l'informazione, ovvero nello specifico un byte, inserita nel canale di comunicazione da un processo venga letta da tutti gli altri processi che in quel momento sono collegati a quel canale
                                - quindi si deve avere la certezza della ricezione
                                - infatti in un canale reale in condizioni ottimali quanto viene inviato un byte questo è anche certamente ricevuto da tutti; che poi questo byte venga processato o meno da coloro che lo hanno ricevuto questo è un aspetto che riguarda i layer del codice a più alto livello
                            - nel caso invece della simulazione del pin di una porta, configurato come segnale digitale, non è necessario che il cambio di stato del pin venga letto da tutti gli altri processi
                                - tuttavia si può pensare a due alternative di implementazione della simulazione del pin di una porta configurato come segnale digitale ovvero
                                    - incertezza nel sapere da parte di chi imposta lo stato che questo sia stato letto da tutti gli altri processi
                                        - in questo caso il modulo [mcuPinPort] <NON avrà> necessità di chiamare alcuna funzione del modulo [shmMcuPinPort] e quindi di fatto <NON dipenderà> da questo modulo
                                    - certezza nel sapere da parte di chi imposta lo stato che questo sia stato letto da tutti gli altri processi
                                        - in questo caso il modulo [mcuPinPort] <avrà> necessità di chiamare opportune funzioni del modulo [shmMcuPinPort] e quindi risulterà <dipendere> da questo modulo
                                        - a pensarci bene però non so se questa modalità si possa implementare dal momento che implicherebbe anche la gestione nei layer a più alto livello dello stack fifo cosa che nella realta non avviene per il pin di una porta digitale.
        - [pphManager]
            - scopo: simulare il comportamento degli oggetti che sono collegati alle porte del microcontrollore ci sranno tanti sotto-moduli quanti saranno i sensori o dispositivi atti ad interfacciarsi con il microcontrollore
        - questi moduli, sebbene nell'implementazione risultino indipendenti uno dall'altro (ovvero nei file .h non c'è nessun include che fa riferimento all'include dell'altro) in realtà interagiscono attraverso alcuni paramteri che sono gestiti dal modulo radice [vhwManager]

---

Friday, 5th July 2024

****----

#include <iostream>
#define quote(x) #x
class one {};
int main(){
    one A;
    std::cout<<typeid(A).name()<<"\t"<< quote(A) <<"\n";
    return 0;
}

****----

#include <typeinfo>

std::cout << typeid(obj).name() << "\n";

****----

If you just want to check if it's certain class, then

typeid(obj) == typeid(CSubClass)

****----

- scopo della modularizzazione è che quando si deve insierire un nuovo modulo
    - 1. non si deve modificare il codice esistente
    - 2. si deve aggiungere solo delle "informazioni" in una tabella
        - queste informazioni possono essere le istanze ad oggetti puntatori a funzione o puntatori ad altre tabelle
- per una gestione modulare questa è la gerarchia
    - vhwManager
        - shmManager
        - mcuManager
            - analisi e gestione della tabella dei moduli [mcu]
                - questi moduli sarebero
                    - DgtPort
                    - AngPort
                    - USART
                    - LCD
                    - SPI
                    - i2c
                    - etc.
            - mcuDgtPortManager
                - analisi della tabella dei collegamenti e dei moduli attivi
                    - in questa tabella sono riportate liste di liste di oggetti 
                        - di questa lista di oggetti si deve conoscere la classe di cui gli oggetti sono le istanze
                - mcuPinPort
                    - vhwUnit
                - shmMcuPinPort
                    - vhwUnit
                - pphButton
                    - vhwUnit
                - pphLed
                    - vhwUnit
                - pphSwitch
                    - vhwUnit
            - mcuAngPortManager
                - mcuAngPinPort
                - pphTempSensor
                - pphHumySensor
                - pphVoltMeter
                - pphAmpMeter
            - mcuUSARTManager
                - analisi della tabella dei canali di comunicazione che sono attivi
                - mcuUSART
                    - vhwUnit
                - shmMcuUSART
                    - vhwUnit
        - pphManager

- inizializzazione USART
    - si deve creare  prima l'istanza della shared memory e poi l'istanza della mcu
- inizializzazione della Port
    - si deve creare n istanza statica del Port da usare poi per eseguire l'init dei pin
        - ma forse l'init lo si può eseguire a copile time non è ncessario a run-time
- per la gestione dei wrapper sarebbe da pensare ad un interfaccia comune rappresentata da una classe virtuale posta nella directory "common"

- il modulo wrapper rsSerial fa da collegamento tra il modulo "[uyProtocol]" e i modulo "[sdk]" delle varie piattaforme
    - mcuUSART per la piattaforma mac
- i moduli
    - [uyProtocol]
    - [sdk]
    - sono tra loro indipendenti
- per gestire due canali seriali conviene sempre considerare un interfaccia statica e poi mdoificare una variabile globale all'interno dell sdk_usart che attiva il preciso canale

- converrebbe gestire i moduli [mcu] come segue
    - i moduli [mcu] sono delle classi dinamiche ovvero si usano attraverso le loro istanze di oggetti
    - i moduli [shm] sono delle classi statiche ovvero delle classi singletone
    - quindi in fase di configurazione dell'hardware
        - a compile-time  vengono create le istanze delle classi [mcu]
            - queste vengono insierite in tabelle e gestite con i moduli [manager]
        - a run-time vengono inizializzate con i puntatori alla 
            - shared memory / memoria condivisa
            - oppure
            - local memory / memoria locale
            - a seconda che la procedura di inizializzazione della [shm] sia positiva or negativa

---

Tuesday, 2nd July 2024

- i moduli [mcu] e [pph] devono essere indipendenti, l'uno non deve conoscere l'esistenza dell'altro
- entrambe i moduli [mcu] e [pph] dipendono dai moduli [shm]
- i sottomodulo [manager] dei moduli [mcu], [pph] e [shm] gestiscono gli aspetti generali di ciscun gruppo di moduli
- c'è poi il modulo [vhwManager] che gestisce i sottomoudli [manager] dei moduli [mcu], [pph] e [shm]

- i sotto moduli manager dei [mcu], [pph] e [shm] sono delle classi singletone ovvero sono delle classi statiche quindi
    - tutte le variabili sono statiche
    - tutte le funzioni sono statiche
    - non è definito nessun costruttore

- gestione dei byte destinati alle porte
    - ci dovrà essere un file di configurazione delle porte in cui si definiscono
        - i nomi delle porte (1, 2, .., A, B, C, etc. )

- [vhwManager]
    - description
        - manage the loop functions of manager sub-modules of [mcu], [pph] end [shm] modules
        - loop function
            - <loop>
    - [mcuManager]
        - [mcuPort]
            - [shmPort]
        - [mcuUSART]
            - description:
                - check the virtual channel communication represented by shared memory
                - manage the buffer status
                - loop functions
                    - <sdk_process::check_read_write>
                - call functions
                    - <sdk_usart::reg_write>
                    - <sdk_usart::reg_read>
                    - <sdk_usart::tx_enable>
                    - <sdk_usart::rx_enable>
            - <public> (routines used by modules with higher level)
                - <void sdk_usart::reg_write                (void* p_ptrData, char c)>
                - <uint8_t sdk_usart::reg_read              (void* p_ptrData)>
                - <void sdk_usart::tx_enable                (void* p_ptrData)>
                - <void sdk_usart::rx_enable                (void* p_ptrData)>
                - <bool sdk_process::check_read_write       (void)>
            - <private> (routines that interact with [shmUSART] module)
                - <callback_protocol_functions_t g_callback_protocol_functions>
                - <bool sdk_process::rx_fifo_full           (void)>
                - <bool sdk_process::tx_fifo_full           (void)>
                - <void sdk_process::tx_fifo_empty_out      (void)>
            - [shmUSART]
                - description
                    - manage the read/write status of buffer
    - [pphManager]
        - description
            - manage the [ncurses] environment
                - init
                - start
                - end
            - it shows the processes involved in shared memory use
            - loop functions
                - <loop>
                    - update the status of the processes list
                    - their pid
        - functions
            - <void sdk_usart::start                    (std::string p_param)>
            - <bool sdk_usart::loop                     (void)>
            - <void sdk_usart::end_0                    (void)>
            - <void sdk_usart::end                      (void)>
            - <bool sdk_usart::check_loop_end           (void)>
            - <void sdk_usart::rx_stop                  (void)>
        - [shmManager]
        - [pphButton]
            - [shmPort]
        - [pphSwitch]
            - [shmPort]
        - [pphLed]
            - [shmPort]
        - [pphUSART]
            - [shmUSART]
    - [shmManager]
        - description
            - loop functions
                - <sdk_process::check_process(void)>
                    - manage the list of processes that use the shared memory
                        - update list (<check_process> function)
            - call functions
                - implement the add & deletion process procedures
                - implement the active process update (<next> function)
                - implement the semaphore function
        - functions
            - <bool sdk_process::check_process(void)>
            - <bool sdk_process::add_0(std::string p_param)>
            - <bool sdk_process::add_2(void)>
            - <bool sdk_process::del_0(void)>
            - <bool sdk_process::del_2(void)>
            - <void sdk_process::next(void)>
            - <void sdk_process::start(void)>
        - [shmPort]
        - [shmUSART]

---

Monday, 1st July 2024

- per quanto riguarda il canale di comunicazione dato che può accadere che ci possano essere attive due UART si potrebbe pensare di non creare una classe statica 
    - gli elementi non statici dovrebbero essere i due byte di memria condivisa 
        - sono due byte perche
            - [buffer] uno riguarda il dato
            - [gDataWriterPid] l'altro riguarda il controllo dello stato di lettura/scrittura riferito al dato
- vediamo come distribuire il codice presente nei moduli
    - [sdk_process]
        - <bool sdk_process::check_process(void)>
        - <bool sdk_process::add_0(std::string p_param)>
        - <bool sdk_process::add_2(void)>
        - <bool sdk_process::del_0(void)>
        - <bool sdk_process::del_2(void)>
        - <void sdk_process::next(void)>
        - <void sdk_process::start(void)>
            - [vhwManager]
        - <bool sdk_process::check_read_write(void)>
        - <bool sdk_process::rx_fifo_full           (void)>
        - <bool sdk_process::tx_fifo_full           (void)>
        - <void sdk_process::tx_fifo_empty_out      (void)>
        - <bool sdk_process::check_start            (void)>
        - <uint16_t sdk_process::get_pid            (uint8_t p_id)>
        - <uint16_t sdk_process::get_pid_enabled    (void)>
        - <void     sdk_process::tx_fifo_write      (char c)>
        - <uint16_t sdk_process::rx_fifo_read       (void)>
        - <uint16_t sdk_process::read               (void)>
        - <uint8_t  sdk_process::error_get          (void)>
        - <char     buffer>
        - <uint16_t gDataWriterPid>
            - [mcuUSART]
    - [sdk_uart]
        - <void sdk_usart::reg_write(void* p_ptrData, char c)>
        - <uint8_t sdk_usart::reg_read(void* p_ptrData)>
        - <void sdk_usart::tx_enable(void* p_ptrData)>
        - <void sdk_usart::rx_enable(void* p_ptrData)>
        - <callback_protocol_functions_t g_callback_protocol_functions;>
            - [mcuUSART]
        - <void     start                    (std::string p_param)>
        - <bool     loop                     (void)>
        - <void     end_0                    (void)>
        - <void     end                      (void)>
        - <bool     check_loop_end           (void)>
        - <void     rx_stop                  (void)>
            - [pphManager]


- notare che nei moduli [mcu] e nei moduli [pph] non ci dovrebbe essere nessun riferimento agli oggetti della memoria condivisa
    - i riferimenti alla memoria condivisa si dovrebbero trovare nel modulo [vhwManager]
        - questo accade perchè la memroia condivisa viene "condivisa" con piu oggetti 
            - si pensi agli ingressi digitali
                - un ingresso digitale è associato ad un solo bit di un byte
    - in questo modo uno stesso byte di memoria condivisa può essere "usato" da più oggetti ciascuno dei quali è interessato ad un solo singolo bit
- nella gestione della memoria condivisa capire come procedere
    - creare un oggetto unico dove c'è "tutto"
    - oppure creare i vari oggetti singolarmente
    - riportiamo di seguito l'elenco degli oggeti da istanziare
        - memoria per il controllo
            - aggiungere o eliminare processi che condividono la memoria
                - cosa necessaria per la gestione del canale di comunicazione
        - memoria per il buffer di comunivazione
            - uart
            - spi
            - etc.
        - memoria associata agli input e output digitali
        - memoria associata agli input e output analogici
- capire come organizzare il codice
    - quello relativo alla simulazione con ncurses -> pph module
    - quello relativo alla simulazione dei regsitri del MCU -> mcu module

---

Saturday, 29th June 2024

- definizione delle porte della mcu e successivi collegamenti
    - ci possono essere due modi di procedure
        - 1) quello più vicino alla realtà
            - si definiscono le porte utilizzate e a cosa sono destinate
                - quindi ad esempio per gestire un led
                    - ci saranno delle [#define] del tipo
                        - #define VHW_SENSOR_LED_PORT   1
                        - #define VHW_SENSOR_LED_PIN    4
                    - da queste define si definiranno le relative istanze dei pin con la define
                        - #define DEF_MCU_PORT_PIN_TEST(a, name)       mcuPort_t mcu_##a##_func_##name       (a, ##VHW_##name##_PORT, ##VHW_##name##_PIN);
                    - usando questa define definiremo in modo "automatico", senza "errori di distrazione" e con il "giusto nome" le istanze dei pin
                        - riassumendo la sequenza sarebbe questa:
                            - #define VHW_SENSOR_LED_PORT   1
                            - #define VHW_SENSOR_LED_PIN    4
                            - DEF_MCU_PORT_PIN_TEST(<id device>, SENSOR_LED)
                                - si otterrà un'istanza della classe [mcuPort_t] con il seguente nome
                                    - mcu_<id device>_SENSOR_LED
                                        - la cui definizione è
                                            - mcuPort_t mcu_<id device>_SENSOR_LED(<id device>, VHW_SENOSR_LED_PORT, VHW_SENOSR_LED_PIN)
        - 2) quello più consono all'hardware virtuale
    - considerare poi che se si vogliono collegare due device aventi lo stesso firmware è necessario gestire il file di configurazione dei collegamenti su file e non a compile time
        - forse non è vera questa cosa è sufficente gestire gli id
            - gli id vengono dati a riga di comando come parametri all'avvio del firmware
        - si potrebbe invece gestire l'inizializzazione delle istanze con o senza id nel caso non ci sia l'id viene messo NULLO e poi a runtime verà preso quello di sistema ipostato da linea di comando

---

Thursday, 27th June 2024

- mitmproxy / vedere come usa ncurses

- mpfw_code_libs_sdk_mac_ext
    - nell'albero delle dipendenze si inseirsce come segue
    - [mpfw_code_libs_fw2_wrapper_resources]
        - [mpfw_code_libs_sdk_mac_ext]
            - la dipendenza dal <fw2_core_core> lib serve per dare alle librerie sdk le funzionalità di
                - init
                - timer
                - state_machine & gestione thread
            - [mpfw_code_libs_fw2_core_core]
                - [mpfw_code_libs_sdk_mac]


---

Friday, 21st June 2024

- John Strang, Programming with curses, O'Reilly, ISBN 0-937175-02-1



- gestione delle simulazioni
    - ci possono essere due livelli di simulazione della seriale
        - reale se si usa la seriale vera e propria attraverso un adattatore usb/rs485
        - virtuale se si usa la memoria per simulare il canale di comunicazione
    - ogni periferica ha associato una dashboard
        - periferiche
            - seriale
            - digital in/out
            - analog in/out
            - display/buttons/touchscreen
            - ethernet
            - sdcard/memory card
    - si potrebbe usare la memoria per memorizzare gli stati delle periferiche
        -  e poi con un comando vedere lo stato attuale oppure eseguire un replay
        - le modalità di campionamento potrebbero essere 
            - fisse con un intervallo di tempo fissato 
            - oppure ad evento ogni qual volta ci sia una variazione avviene la registrazione
        - come detto la registrazione avviene in memoria 
            - poi come nel caso delle sdcard si può decidere di eseguire una scrittura su disco
                - ma tenere questi due processi separati
        - si potrebbe pensare anche di usare queste registrazioni come input invece che come output
            - in modo da eseguire una procedura di test automatizzata
    - il buffer di memoria che contiene i dati delle sequenze delle periferiche può essere usato
        - in OUTPUT
            - e quindi avviene la regisrtazione di quanto sta accadendo
        - in INPUT  
            - e quindi siamo nella procedura di test in cui
                - si leggono dal buffer gli input
                    - è poi si introducono nel processo del firmware
                - si leggono i dati di output del processo del firmware 
                    - e poi si confrontano con i dati di output del buffer

- protocollo di registrazione
    - [din.time.data_lenght.status]
    - [dout.time.data_lenght.status]
    - [ain.time.data_lenght.value]
    - [ain.time.data_lenght.value]
    - [sdcard.time.data_lenght.data_lenght_2.path_file.file_content.data_lenght_2.data_lenght.sdcard]
    - [<1>         .<1>            .<1>                .<4>       .<4>   .<1>          .<???>       .<1>          .<1>]
    - [<start code>.<codice device>.<codice periferica>.<sequence>.<time>.<data_length>.<data_block>.<data_length>.<end code>]
    - [<id 0>      .<id 1>         .<id 2>             .<id 3>    .<id 7>.<id 11>      .<id 12>     .<id 12+data> .<id 13+data>]
    - forse lo <start code> non dovrebbe essere necessario si potrebbe usare solo l'<end code> che potrebbe essere un <CR/LF>
        - la memorizzazione del buffer in un file potrebbe essere in formato
            - binario
            - testo preservando gli <end code> o trasformando gli <end code> in <CR/LF>

- i digital input possono essere in modalità
    - polling
        - lo stato dell'ingresso viene controllato periodicamente
    - interrupt (exti)
        - quando l'ingresso è "fisicamente attivato", viene chiamata la "funzione di interrupt" associata all'ingresso

- da capire quali sono i moduli
    - wrapper resources
        - come viene realizzato il modulo con interfaccia comune con tutte le altre piattaforme
    - sdk_<platform>
        - come viene realizzata "fisicamente" la periferica
            - nel caso della piattaforma [mac] e di un ingresso digitale (din) sarà una locazione di memoria
                - si può replicare la struttura delle porte di un microprocessore reale con
                    - i byte di configurazione e i byte data
    - il punto chiave sta nell'ipostare bene le funzioni interfaccia del wrapper perche queste dovranno essere inserite all'interno di un vero micro e quindi ottimizzate
        - in questo caso forse conviene usare delle macro/define vedere l'applicazione tst_20240429

- il buffer dell'virtual hardware dovrebbe essere condiviso tra più processi quindi posto nella memoria condivisa tra processi
    - in questo caso però si perderebbe la velocità di lettura/scrittura nel buffer
- l'idea è anche quella di collegare le uscite di un device alle entrate di un altro device 
    - ci dovrebbe essere un'altro processo che si preoccupa delle interconnessioni tra devices
        - questo processo dovrebbe fare da ponte tra il virtual hardware shared buffer (quindi memoria condivisa tra processi) e il virtual hardware local buffer (quindi memoria locale/proprietaria di uno specifico processo)
        - quando si avvia un processo si può specificare come sono collegate le sue uscite ed i suoi ingressi ad altri dispositivi
- ci devono essere due processi per gestire i collegamenti tra devices e/o [pilot_file]
    - [virtual_hardware_local] process
        - gestisce le relazioni tra il [virtual_hardware_local] buffer e la [TUI]
    - [virtual_hardware_shared] process
        - gestisce le relazioni tra il [virtual_hardware_local] buffer e [virtual_hardware_shared] buffer
- [pilot_file]
    - si potrebbero avere più pilot_file attivi in particolare 
        - si possono avere dei pilot_file 
            - locali
                - per la gestione ad esempio degli input digitali o analogici
            - condivisi
                - per la gestione della comunicazione tra dispositivi oppure per collegare le uscite di un dispositivo agli ingressi di un'altro


- 16byte -> 20byte
    - 20B/s * 3600 -> 72000B/h
- pensare ad una periferica che fornisce i dati della temperatura, la cosa comoda è caricare un file di testo con la sequenza dell'andamento della temperatura che simula un sensore di temperatura/umidità
    - sarebbe compito del [fw2_update_virtual_hardware_TUI] leggere il file ed inserirlo nel <virtual hardware local buffer>
    - nei frame del buffer ci dovrebbero essere dei codici di controllo che dicono quando una periferica è in modalità "pilot/automatica" (ovvero legge da un file) oppure in modalità manuale
- routine per la gestione dei protocolli annidati capire se c'è qualcosa su [boost]
    -

- capire cosa si vuole fare
    - definire bene gli [use_case]
        - impostare in modo automatico seguendo una sequenza riportata in un file gli ingressi digitali o analogici e vedere come si comporta il sistema
            - eventuale attivazione di un uscita digitale / led
            - registrazione su sd_card
            - invio di un messaggio sulla seriale
        - impostare manualmente 
            - gli ingressi
                - digitali
                - analogici
            - inviare un messaggio sulla seriale
        - registrare gli eventi delle periferiche sul virtual_hardware local buffer
            - queste registrazioni poi possono essere utilizzate per eseguire una procedura di test 
        - eseguire le procedure di test per mezzo dei virtual_hardware buffer (local & shared)
        - collegare gli ingressi di un dispositivo alle uscite di un altro e vedere il sistema come reagisce
            - si deve usare un file di configurazione
- [flusso_delle_istruzioni] & [use_case]
    - inizializzazione del [virtual_hardware] e del conseguente [virtual_hardware_buffer]
    - l'utente via TUI attiva un ingresso digitale
        - premo il tasto
        - il TUI legge che è stato premuto un tasto
        - analisi del tasto premuto
            - l'analisi del tasto premuto riguarda la configurazione dell'[hardware_virtuale] e di come sia collegato al [device]
                - [device] e [multiplatform_firmware_app] ([higher_level_firmware], [wrapper_level_firmware] [low_level_firmware]) sono equivalenti
                - tipologie di [hardware_virtuali] che possono essere collegate agli ingressi digitali del device
                    - [buttons]
                        - qui ci sarà la gestione [antirimbalzo] o [debounce]
                    - [switches]/[relay]
            - riguarda l'attivazione di un ingresso digitale
            - si deve aggiornare lo stato del [virtual_hardware]
                - istantaneamente si deve inserire un frame di cambio stato nel [virtual_hardware_buffer]
    - il device attiva un uscita digitale che può essere rappresentata da/collegata a un led (in questo caso il [led] rappresenta la periferica hardware virtuale passiva)
        - il device attiva un uscita digitale collegata ad esempio ad un [led]
            - il collegamento ad un led dovrebbe essere descritto in un file di configurazione come può accadere per collegare l'uscita all'ingresso di un altro device
                - nel caso del led anzichè di un altro dispositivo la gestione/interazione avviene senza passare per lo shared buffer
                    - stssa cosa dovrebbe farsi nel caso del [button]
        - quindi viene chiamata una funzione che aggiorna lo stato del [virtual_hardware]
            - all'interno di questa funzione viene chiamata un'altra funzione che inserisce un frame di cambio stato nel [virtual_hardware_buffer]
            - se configurata
- file di configurazione dei collegamenti tra [device] e [virtual_hardware]
    - vh_button[0] | dv_input[0]
    - vh_led[0]    | dv_output[1]
- da capire se il file di configurazione convenga inserirlo 
    - a compile time e quindi attraverso un un file include
    - a run-time e quindi con un file di testo codificato opportunamente
- per ogni elemento di [virtual_hardware] ci dovranno essere delle routine sdk 
    - queste routine dovranno sfruttare le routine messe a disposizione dalla libreria ncurses nel caso della piattaforma [mac]
    - inoltre su queste routine si appoggeranno routine più ad alto livello come la gestione del [debounce] che verranno poi usate anche per altre piattaforme

- la configurazione dell'hardware_virtuale viene fatta a compile-time e quindi ci saranno dei file include di configurazione 
- sequenza di gestione del [virtual_hardware]
    - viene premuto un tasto 
    - il main loop controlla se nel buffer ci sia un tasto premuto
        - se è stato premuto un tasto inizia l'analisi
            - in base al tasto premuto viene eseguita una routine
                - come prima cosa verrà aggiornato il [virtual_hardware_buffer]
                    - attraverso il file di configurazione si può ottenere il puntatore all'oggetto che è associato al presente tasto
                        - e quindi può essere eseguita la funzione di interrupt associata all'pin della porta virtuale del device
    - il [mcu_virtual_hardware_buffer] da lo stato dell'hardware virtuale del device
    - [log_virtual_hardware_buffer]
    - il [virtual_hardware_manager] è colui che gestisce le interazioni tra i [virtual_hardware] dei vari devices
    - i [devices] sono
        - [mcu]
            - [din]
            - [dout]
            - [serial/USART]
            - [serial/SPI]
            - [i2c]
            - [ain]
            - [aout]
        - [button] / [relay] (output)
            - ncurses.getkey
        - [led] (input)
            - ncurses.printch
        - [analog_sensor] (output) (temperature, humidity sensors, etcs)
            - file.getvalue
                - come potrebbe essere la procedura di lettura della temperatura
                    - lettura dati dal file a tempi prestabiliti, si dovrà usare un timer
                - la simulazione della variazione di temperatura potrebbe essere
                    - automatica via file
                    - manuale attraverso una locazione di memoria associata ad un componente ncurses come se fosse un paramtero da modificare
    - gestione dei [device]
        - ogni device ha un suo main loop
        - ogni device ha una sua locazione di memoria
            - questa locazione di memoria viene letta/scritta dal [virtual_hardware_manager]
            - è la "porta" di comunicazione tra il dispositivo e il momno esterno
                - il [virtual_hardware_manager] farebbe da mediatore nella comunicazione tra i dispositivi 
        - il [devices_manager]
            - analizza il file di configurazione delle connessini tra i devices
            - legge da un device di output 
            - scrive in un device di input 
            - in base a come sono configurati i collegamenti
            - in questo modo ciascun devices non sa, non ha la necessità di conoscere alcunchè degli altri dispositivi con cui è collegato, mi riferico in particolare alle funzioni e quindi ai file header di ciascun device
    - locazioni di memoria associati ai dispositivi e puntatori
        - la cosa ideale di quando si collegano due dispositivi è di fargli condividere la stessa locazione di memoria
            - in questo caso non servirebbe più un processo manager che legge una locazione di memoria e ne copia il contenuto in un'altra
    - come collegare due mcu devices?
        - din/dout
            - usare la [shared_memory]
                - ma come?
                - anche nel caso della shred memory si possono usare i puntatori
                    - nel caso dei din/dou e/o ain/aout la cosa, forse, si può semplificare ulterirormente senza l'uso di semafori perchè un processo solo scrive gli altri leggono!!
        - seriale/USART
            - usare la [shared_memory]
                - ma come?
                - nel caso di comunicazione bidirezionale si dovranno usare delle tecniche tipo semafori/flip/flop
    - ogni device mcu, din, etc. avrà un puntatore ad una locazione di memoria
        - le operazioni di lettura/scrittura su questa memoria potranno essere diverse da dispositivo a dispositivo
            - per i dispositivi din, dout, etc. saranno semplificate dal momento che solo un dispositivo scrive gli altri leggono
            - per i dispositivi [USART] in cui nella locazione di memoria tutti possono scrivere ci dovra essere una gestione a flip/flop
                - in questo caso un dispositivo deve attendere prima di scrivere qualcosa sullo [shared_buffer]
    - il lavoro del [devices_manager], usando i puntatori, si ridurrebbe solo alla fase iniziale di configurazione in cui si assegnano i puntatori ai vari devices 
- l'[sdk_process] potrebbe essere visto 
    - come il [devices_manager]
    - ma anche come [serial_channel_manager] o più in generale come un oggetto che gestisce un buffer di memoria condivisa tra più processi e non tra thread all'interno di uno stesso processo
    - si dovrebbero però separare le routine [add_x], [del_x], [check_process] quelle che aggiungono/eliminano un processo che fa uso della memoria condivisa, da quelle che gestiscono la lettura scrittura nella memoria [check_read_write]
    - [sdk_devices_manager]
    - [sdk_shared_memory]
    - [sdk_UART]
    - [sdk_PORT] -> din (i.e. radar_sensor), dout, ain & aout
    - [sdk_i2cDevice] -> temperature sensor, etc.
- analisi del modulo [sdk_UART] quello che dovrebbe simulare la periferica USART del micro
    - pensare a come aggiornarlo per poter usufruire di un canale di comunicazione reale attraverso un modulo rs232/ttl/rs485-usb 
    - gli elementi sono
        - loop
            - nel loop si controlla
                - se sul canale di comunicazione virtuale sono presenti dei messaggi
                - se si devono inviare dei byte nel canale di comunicazione
                - gestione della dashboard per il debug del modulo
                    - la dash board fa uso diretto delle funzioni della libreria ncurses
            - NOTE: i loop devono avere la caratteristica che possono essere eseguiti un numero indefinito di volte senza alterare il risultato elle operazioni
                - ovvero non devono essere pensati per essere eseguiti un ciclo alla volta, quindi non ci dovrebbe essere nessun contatore del loop che possa influenzare il risultato delle operazioni (pensare alla funzione di sdk_process::next(void))
                - la cosa ideale sarebbe la seguente 
        - funzioni di
            - read / write uart register, quindi lettura e scrittura sul buffer della UART
                - queste funzioni sono usate da moduli a più alto livello
- gestione [sdk_mcus_manager]/[sdk_shared_memory]
    - capire se usare un buffer unico per tutti i devices oppure usare un buffer per tipologia di devices
        - forse conviene separare i dati 
            - relativi alla gestione dei processi che condividono la memoria
                - questa gestione è generale va bene per tutti i devices
            - relativi al buffer dei dati da condividere
    - per una questione di prestazioni/performance sarebbe anche da separare i buffer locali da quelli shared
    - pensare alla registrazione degli eventi per poi poter eseguire un test automatico
- sarebbe da capire bene come funziona [mmap]
- capire se le locazioni di memoria ottenute con mmpap/shm_open sono allineate
    - questo permettere di evitare l'uso dei tipi di dati atomic
- analisi dei moduli di shared memory per ciascuna tipologia di dispositivo
    - modulo [sdk_UART_shm]
        - in questo caso ci dovrà essere un informazione di controllo perche se si vuole simulare un canale di comunicazione dove quando un processo scrive gli altri devono leggere
            - questa informazione di controllo è rappresentata dal codice id del processo che sta scrivendo sul canale
                - per questo motivo a questo modulo è associata una funzione di loop che trasferisce i dati dalla  memoria condivisa del modulo [sdk_UART_shm] al buffer del modulo [sdk_UART]
            - inoltre non è possibile identificare il buffer usato nel modulo [sdk_UART] conil buffer di memoria condivisa
    - modulo [sdk_PORT_shm]
        - in questo caso non è necessaria nessuna informazione di controllo perchè non è importante sapere da parte di chi ha scritto se tutti i dispositivi lo hanno letto
        - per questo modulo è importante la fase di inizializzazione dove vengono assegnati i puntatori ai registri virtuali delle porte
        - il file di configurazione dei collegamenti dovrebbe essere copiato nella memoria condivisa relativa ai processi di modo che tutti i processi condividono la stessa configurazione dei collegamenti
        - per questo modulo non è necessaria nessuna funzione di loop infatti non c'è nessuna variabile di controllo inoltre sul pin di una porta solo un processo scrive gli altri leggono
            - discorso leggermente diverso per le porte analogiche quando i registri sono a due byte in questo caso se il puntatore alla locazione non è allineato ci potrebbero essere dei problemi nella lettura dei registri ad esempio passando da 00ff a 0100 può succedere che la lettura sia uguale a 0 oppure a 01ff a seconda che rispettivamente venga prima scritto il byte meno significativo o più significativo
- file di configurazione dei collegamenti [sdk_devices_links]
    - [0].[0] | vh_button[0] | mcu_input[0].[2]
        - #define BUTTON_1_PORT     0
        - #define BUTTON_1_PIN      2
    - vh_led[0]    | mcu_output[0].[4]
- [virtual_hardware(vhw)] modules
    - modulo [sdk_vhw_manager]
        - dipendenze
            - [ncurses]
            - [sdk_vhw_manager_tbl]
                - dipendenze
                    - [sdk_vhwButton]
                    - [sdk_vhwLed]
                    - ...
                    - [sdk_mcu_port]
                    - [sdk_mcu_uart]
                    - ...
    - modulo [sdk_vhwRelay]
        - elementi
            - loop
                - necessario per controllare lo stato ed aggiornare la [TUI]
        - dipendenze
            - [ncurses]
            - [sdk_wired_shm]
    - modulo [sdk_vhwButton]
        - elementi
            - loop
                - necessario per controllare lo stato ed aggiornare la [TUI]
                    - si controlla se sia stato premuto un tasto
                    - se il tasto è stato premuto si aggiorna la memoria condivisa ed eventualmente se previsto si può aggiornare la [TUI]
        - dipendenze
            - [ncurses]
            - [sdk_wired_shm]
    - modulo [sdk_whwLed]
        - elementi
            - loop
                - necessario per controllare lo stato ed aggiornare la [TUI]
                    - si legge lo stato della memoria condivisa e poi se necessario si aggiorna la [TUI] via [ncurses]
        - dipendenze
            - [ncurses]
            - [sdk_wired_shm]
    - modulo [sdk_vhwTemperatureSensor]
        - dipendenze
            - [ncurses]
- [mcu] modules
    - modulo [sdk_mcu_digital_port]
        - elementi
            - init
                - ci sono due scopi principali
                    - configurare la porta
                        - analogica
                        - digitale
                            - configurare i pin
                                - enable/disable interrupt
                                - porta di in/out
                    - associare al registro la locazione di memoria condivisa attraverso il puntatore di quest'ultima
                - da capire di chi sia il compito di eseguire l'inizializzazione
                    - io direi il modulo [sdk_vhw_manager]
                        - quando questo modulo legge il file di configurazione
                            - sa quali sono i dispositivi che devono essere tra loro collegati
                                - SDK_MCU_PORT.<mcu id>.0.1 | SDK_BUTTON.<mcu id>.<button id>0
                                - SDK_MCU_PORT.<mcu id>.0.2 | SDK_LED.<mcu id>.0
                                - SDK_MCU_PORT.<mcu id>.1.4 | SDK_MCU_PORT.<mcu id>.0.2
                                - SDK_MCU_UART.<mcu id>     
                                - SDK_MCU_UART.<mcu id>
                                - SDK_MCU_UART.<mcu id>
                            - dubbio
                                - è necessario che sappia chi sono (in) e chi sono (out)?
                                    - in teoria NO
                        - sequenza di inizializzazione
                            - lettura file di configurazione
                                - ogni riga del file di configurazione rappresenta il pin di una porta
                                    - quindi, ad esempio, 
                                        - la riga 1 rappresenta il pin 0 della porta 0
                                        - ...
                                        - la riga 7 rappresenta il pin 6 della porta 0
                                        - la riga 8 rappresenta il pin 7 della porta 0
                                        - la riga 9 rappresenta il pin 0 della porta 1
                                - il contenuto viene poi riportato sotto forma di tabella/matrice nella memoria condivisa per i processi/devices
                                    - {<shm_PORT>, <shm_PIN>, <device code id>, <mcu id>, <PORT>, <PIN>}
                                    - {<shm_PORT>, <shm_PIN>, <device code id>, <mcu id>, <PORT>, <PIN>}
                                    - {<shm_PORT>, <shm_PIN>, <device code id>, <mcu id>, <PORT>, <PIN>}
                                    - {<shm_PORT>, <shm_PIN>, <device code id>, <mcu id>, <PORT>, <PIN>}
                            - parsing del file
                                - tabella dei device
                                    - SDK_MCU_PORT  ,init   ,loop
                                    - SDK_BUTTON    ,init   ,loop
                                    - SDK_LED       ,init   ,loop
                                - array of shm_PORT
                                    - port.0
                                        - call shm_PORT.init() -> PORT_shm*
                                            - oppure viene creato l'oggetto che racchiude un buffer di shared memory
                                                - si ottiene il puntatore alla shared memory
                                        - call SDK_MCU_PORT[<port id>].init(PORT_shm*, 1<PIN>)
                                        - creare l'oggetto/istanza della classe SDK_BUTTON
                                            - call SDK_BUTTON[<button id>].init(PORT_shm*, <PIN>)
                                    - NOTE: le istanze degli oggetti SDK_Peripheral (SDK_BUTTON, SDK_LED, etc. ) vengono create a run_time mentre gli oggetti SDK_MCU sono creati a compile_time
            - loop 
                - necessario per simulare l'interrupt exti associato al pin, la funzione di interrupt verrà eseguita solo se il pin è stato configurato con questa opzione
        - dipendenze
            - modulo [sdk_wired_shm]
    - modulo [sdk_mcu_analog_port]
        - dipendenze
            - modulo [sdk_wired_shm]
    - modulo [sdk_mcu_i2c]
        - dipendenze
            - modulo [sdk_chcom_shm]
    - modulo [sdk_mcu_spi]
        - dipendenze
            - modulo [sdk_chcom_shm]
    - modulo [sdk_mcu_uart]
        - dipendenze
            - modulo [sdk_chcom_shm]
- [mcuPort]
- [mcuUART]
- [mcuSPI]
- [pphButton]
- [pphLed]
- [shmWired]
- [shmChCom]
- [vhwManager]
    - l'dea di usare un file di configurazione è buona però per velocizzare il test si potrebbe pensare di eseguire i collegamenti virtuali a compile time invece che a run-time in questo caso 
                    - vhwUnit
