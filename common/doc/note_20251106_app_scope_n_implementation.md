
---

Tue  7 Jul 2026 15:27:58 CEST



---

Mon  6 Jul 2026 10:29:30 CEST

- implementazione della USART-RS485 per la piattaforma nxp
    - gestione dei pin di enable/disable
        - init
            - al momento i pin non sono stati parametrizzati quindi la funzione di init dovrà essere implementata in una funzione di un modulo a livello applicativo
            - [to_do]
                - parametrizzare i pin coinvolti nella configurazione della USART/RS485
        - enable/disable function
            - si devono implementare le funzioni di eneable/disable del canale RS485
                - queste funzioni sono
                - 
    - gestione pin rx/tx usart
        - init


- Scrivere la fiaba della tua vita. Storytelling per cambiare positivamente la tua vita.
    - Alison Davies
    - EIFIS editore
    - 2017 / 2020 luglio
    - ISBN 978.88.7517.139.1
- Il mondo incantato. Uso, importanza e significati psicoanalitici delle fiabe.
    - Bettelheim Bruno
    - Feltrinelli 2013

---

Sun  5 Jul 2026 16:01:24 CEST

- sembrerebbe che la classe [hw2ManagerCmmn_t] sia inutile
    - non ha nessuna funzione implementata
    - si potrebbe eliminarla
- ènecessario fafre chiarezza su quali funzione il wrapper debba implementare per ciscuna piattaforma


---

Sat  4 Jul 2026 15:02:28 CEST

- problema con il roll-down del mouse
    - su catalina, ma non su sonoma, il roll-down del mouse risulta lento
        - questa lentezza sembra sia dovuta al fatto che
            - l'evento di roll-down viene segnalato solo quando il movimento si ferma
                - questo non accade con il roll-up
        - per conseguenza, al momento, si pensa sia un problema della libreria ncurses
            - controllare le versioni di ncurses in sonoma ed in catalina

---

Fri 26 Jun 2026 09:43:43 CEST

- gestione di un input e di un output digitali
    - 

- problemi di ottimizzazione con il compilatore GCC/NXP
    - sembra sia costretto a chiamare una variabile statica nella stessa libreria in cui questa variabile statica è definita, diversamente questa variabile statica non viene linkata nella libreria
        - in particolare mi riferisco al vettore/array degli elementi [pph] [hwManagerTbl_t::UnitPtrArray] che è definito nel file [app_hwManagerTbl.cpp] del mdoulo [mpfw_fw2-appl-app20250424-4appl] del gruppo [appl] ma vengono chiamati, indirettamente attraverso la chiamata alla funzione [hwManager::init], nel modulo del gruppo [main]
        - il compilatore esclude dalla fase di link la definizione dell'array
    - per risolvere questo problema ho duvuto definire una funzione [optimize_func] nel file [app_init.cpp] del modulo [mpfw_fw2-appl-app20250424-4appl] in cui viene chiamato/letto l'array [hwManagerTbl_t::UnitPtrArray]
        - la funzione [optimize_func] non è chiamata da nessuno quindi per evitare che il compilatore la ignori ho usato dei [#pragma] di ottimizzazione
    - in questo modo l'array viene usato nella fase di link e quindi ho "risolto" il problema

---

Last login: Wed Nov 19 06:13:49 on ttys003

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

Last login: Thu Nov 13 06:02:54 on console
Restored session: Wed Nov 12 19:21:38 CET 2025

- compilazione di moduli
    - con la versione [03] del codice cmake per eseguire il build si devono passare allo script due parametri quello della piattaforma e quello del [trdp]
        - ad esempio
            - $ build_platform_cmake.sh mac "mac"
            - $ build_platform_cmake.sh mac "mac;ncurses"
                - N.B.: il primo parametro indica la piattaforma, il secondo la lista dei [trdp]
                    - bisogna riconoscere che questa modalità di gestire i [trdp] e le piattaforme non è molto corretta
                        - le cose da migliorare potrebbero essere le seguenti
                            - la pattaforma non ha senso definirla perche è un doppione del sdk
                            - per i moduli [wrpr] ricavare la funzionalità dal nome del modulo
                            - gestire in modo esplicito il propreitario della libreria esterna
                                - se il modulo trdp ha un solo proprietario non serve specificarlo nel comando di build
                            - stabilire delle regole per la struttura delle directories che si trovano sotto la directory [trdp]
                                - naturalmente devono essere coerenti anche con la codifica dei nomi dei moduli si vedano ad esempio i moduli [trdp/sdk]
    


- gestione TRDP 
    - N.B.: il codice presente nella directory/sezione [trdp] è quello che usa funzioni di librerie esterne
    - la presenza dei [trdp] è presente
        - nei moduli
            - [2wrpr]
                - sarà presente un solo [trdp] qello associato appunto al [wrpr]
            - [4appl] e [5main]
                - può avere più [trdp]
                    - anche se sarebbe da averne al massimo uno solo quello relativo alla piattaforma e poi usare degli opportuni [wrpr]
                    - tuttavia per una questione pratica, e comunque corretta, è giusto pensare alla presenza di più [trdp]
                    - la presenza di più [trdp] all'interno di questi moduli è dovuta al fatto che 
                        - ad esempio gestire più piattaforme può portare ad avere esigenze diverse ed in particolare per implementare certe funzionalità alcne piataforme possono richiedere del codice di terze parti (ad esempio la comunicazione via USB oppure la gestione dell'interfaccia di debug per le piattaforme virtuali come mac, linux e windows si pensi alle librerie ncurses, anche se in questo caso è presente un modulo wrpr deidicato a questa libreria di terze parti si vedano i mdouli [tui])


---

Last login: Wed Nov 12 10:05:29 on ttys007


- gestione TRDP 
    - la lsita dei trdp dorebbe essere passaa come parametro di build
        - già questo viene fatto con l'sdk ma va esteso a tutti i [trdp]
        - notare infatti che la gestione dei trdp presuppone anche la presenza di un eventuale proprietario dal momento che ce ne possono essere più di uno come nel caso dell'sdk
        - pensare anche al caso della funzionaità usb 
            - questa può essere integrata nell'sdk
            - ma anche resa disponibile da terzi
                - in queso caso sarebbe da portare la parte di sdk che rigaurda l'usb come libreria esterna e trattatrla a parte, 
                    - da capire se fattibile questa cosa
                        - è molto probabile chee lo sia!!!
                            - la filosfia di fondo è che tutti i file possono messere messi ovunque
                                - il fatto poi che il codice relativo all'sdk-usb sia separato dall'altro codice già è di default

---

Last login: Tue Nov 11 05:59:56 on ttys007
Restored session: Mon Nov 10 19:07:55 CET 2025

- gestione dei file header di configurazione
    - OSSERVAZIONE: un modo di vedere i file di configurazione:
        - SE pensiamo ad un modulo come ad una funzione con parametri
        - ALLORA il file di configurazione può essere visto come lo strumento che permette di passare i parametri al modulo
        - INOLTRE il fatto che il modulo metta a disposizione dei parametri può essere visto come un servizio 
            - e quindi c'è la presenza di una dipendenza indiretta del modulo proprietario del file di config con i suoi "utilizzatori"
            - in questo caso lo strumento che permette di rendere indipendente il modulo che da il servizio è quello della registrazione
                - la registrazione consiste di una variabile cmake pubblica messa a disposizione del modulo proprietario del config file
                - che gli utilizzatori del servizio possono impostare/"registrare" e non solo "leggerla"
            - il modulo proprietario al momento di impostare la directory dove risiede il file di configurazione (contenuta nella variabile pubblica di cui al punto precedente) come "include" directory da inserire nel comando di compilazione
            - esegue un controllo per vedere se qualche modulo l'abbia impostata (quindi se la variabile pubblica non sia vuota) in caso contrario (la variabile pubblica è vuota) la impostera al suo valore di default

- gestione dei file delle dipendenze
    - codifica delle variabili che definiscono la lista delle dipendenze
        - 3 tipi possibili di codifica
            - ${MOD_NAME}_DEPS_LIST
            - ${MOD_NAME}_cmmn_DEPS_LIST
            - ${MOD_NAME}_<trdp nikname>_DEPS_LIST
    - di seguitop la spiegazione del motivo di questa codifica
        - vedere maco [get_files_list_macro] 
            - N.B.: nonostante il nome è specifica per i file delle dipendenze dal momento che analizza la variabile _DEPS_LIST definita in essi
        - step della procedura per ottenere la lsita delle dipendenze
            - step 1
                - viene fatta una ricerca all'interno della directory del modulo
                    - per avere la lista di tutti i file "set_dependencies_list.cmake"
            - step 2
                - vengono "letti" tutti i file trovati questo significa che viene eseguito l'include (istruzione del cmake)
                    - di segutio l'estrattop del codice dalla macro
                        - foreach(item IN LISTS files_list)
                        -     ## message("DEBUG - get_files_list_macro - item:      ${item}")
                        -     string(STRIP ${item} item )
                        -     if(item)
                        -         include("${item}")
                        -     endif()
                        - endforeach()
                - in questo modo vengono impostate tutte le variabili con postfisso _DEPS_LIST, in particolare
                    - set(${MOD_NAME}_DEPS_LIST  ${${MOD_NAME}_DEPS_LIST}   ${${MOD_NAME}_cmmn_DEPS_LIST} )
                    -  e postfisso "_${item}_DEPS_LIST" con item il codice della funzionalità TRDP che possomno essere "sdk, "
                        - di seguito si riporta estratto del codice
                            - foreach(item IN LISTS ${MOD_NAME}_TRDP_FNCT_LIST)
                            -     ## ## message("DEBUG - get_files_list_macro - ${MOD_NAME}_${item}_DEPS_LIST:      ${${MOD_NAME}_${item}_DEPS_LIST}")
                            -     set(${MOD_NAME}_DEPS_LIST  ${${MOD_NAME}_DEPS_LIST}   ${${MOD_NAME}_${item}_DEPS_LIST} )
                            - endforeach()



---

Last login: Mon Nov 10 05:36:34 on ttys007
Restored session: Sun Nov  9 18:03:01 CET 2025

- gestione file sorgenti di configurazione
    - l'impostazione del file di configurazione consiste di tre step
        - step 1: impostazione del percorso relativo, rispetto la directory "mpfw_code"
            - eseguita dai moduli NON-propietari del file di configurazione
                - i moduli che dipendono dal modulo proprietario del file di configurazione se non modificano il file di configurazione ma si limitano solo a leggerlo
                - non devono fare niente
            - se ci sono più moduli che modificano il file di configurazione si genererà un conflitto in fase di build del progetto
        - step 2: impostazione del path assoluto da parte del modulo propretario
            - il modulo poprietario per impostare la directory in cui si trova il file di configurzione segue la seguene procedura
                - 1. controlla il contenuto della variabile che ha il path relativo
                    - se questa variabile è vuota
                        - ovvero nessun modulo l'ha impostata
                    - allora la imposta al valore di default passato dal modulo proprietario
                    - se NON è vuota non fa niente
                - 2. imposta il path assoluto della directory che contiene il file di configurazione usando il path relativo ed il path assoluto della directory "mpfw_fw2"
        - step 3: il modulo proprietario inserisce la varibile impostata al punto precedente nel file proprio file "include_files.cmake"
            - si ricorda che nel file "include_files.cmake" vengono definite le directory dove risiedono il file heder ".h" del codice sorgente
    - dettagli degli steps
        - step 1
            - l'impostazione del percorso relativo viene eseguita per mezzo della macro [RegisterConfigRpath]
            - flusso delle chiamate
                - CMakeLists.txt
                    - step_all.cmake
                        - init_var_macro: eseguita una sola volta dal modulo che avvia la procedura di build
                            - set_public_rpath_macro
                                - set_public_rpath.cmake
                                    - RegisterConfigRpath
                            - ...
                            - set_public_config_rpath_macro
                                - set_public_config_rpath.cmake
                                    - [RegisterConfigRpath]
            - il modulo che vuole modificare il percorso del file di configurazione deve conoscere il nome della variabile che contiene il percorso relativo
                - questa variabile la si trova nei file [set_public_rpath.cmake] o [set_public_config_rpath.cmake] del modulo proprietario
                    - N.B. il nome della variabile non ha una codifica tuttavia per possibili sviluppi futuri del codice cmake è consigliabile seguire la seguente codifica
                        - <owner module name without prefix "mpfw_fw2" in uppercase>_<riferimento config file>_<CONFIG_RPATH>
                            - example:
                                - <TRDP-SDK-STM-STM32F769_DISCO-0TRDP>_<FREERTOS>_<CONFIG_RPATH>
                        - nel caso il modulo abbia un solo file di configurazione la parte <riferimento al config file> può essere omessa
                            - example: 
                                - <FNCT_HW_0ABST>_<CONFIG_RPATH>
            - N.B.:  [set_public_rpath_macro] & [set_public_config_rpath_macro] sono procedure ricorsive sull'albero delle dipendenze che eseguono prima il codice del padre e poi a cascata quello dei figli
        - step 2
            - l'impostazione del percorso assoluto viene eseguita per mezzo della macro [RegisterConfigDir]
            - flusso delle chiamate
                - CMakeLists.txt
                    - step_all.cmake
                        - set_public_dirs_macro
                            - set_public_dirs.cmake
                                - [RegisterConfigDir]


---

Last login: Sun Nov  9 08:05:04 on ttys007

- gestione file sorgenti di configurazione
    - premessa
        - fase di inizializzazione
            - step 1: esecuzione dello script [init_step_0.cmake]
            - step 2: esecuzione dello script 
                - [step_all_exec.cmake] (eseguito solo dai moduli [main]: i moduli che generano l'eseguibile)
                    - esecuzione della macro [init_var_macro]
                - [step_all.cmake] (eseguito dai moduli di libreria)
                    - esecuzione della macro [init_var_macro] 
                        - eseguito solo in caso del build della libreria
                        - non eseguito nel caso il CMakeLists.txt del modulo venga chiamato dal CMakeLists.txt di un altro modulo
        - il codice dove viene impostata la directory di configurazione è conntenuto nelle due seguenti macro
            - set_public_rpath_macro
            - set_public_dirs_macro
        - queste macro contengono un codice ricrorsivo
        - il codice ricorsivo chiama i file [set_public_rpath.cmake] e [set_public_dirs.cmake] di ciascun modulo iniziando dal padre e poi a scendere i figli ed i loro discendenti    
            - (non più valida questa considerazione) N.B.: questo è un dettaglio importante per capire come viene gestita l'impostazione del file di configurazione
            - i file [set_public_rpath.cmake] vengono eseguiti una sola volta (vedere la funzione [include_guard()] contenuta in ognuno di essi) ed in particolare dal modulo che si trova all'inizio dell'albero delle dipendenze ovvero quello che avvia la procedura di build con tutte le sue dipendenze a cascata
    - l'impostazione del file di configurazione consiste di due step tra loro indipendenti, uno facoltativo l'altro necessario
        - step necessario: impostazione del file di configurazione da parte del proprietario
            - flusso delle chiamate
                - set_public_dirs_macro
                    - includ(.../set_public_dirs.cmake)
                        - impostazione path relativo (rispetto la direcory "mpfw_code") della directory di configurazione di default
                        - RegisterConfigDir
                            - questa macro esegue la seguente procedura
                                - controlla il contenuto della variabile che deve contenere il path relativo (rispetto la direcory "mpfw_code")
                                    - se è vuota allora imposta questa variabile al valore di default
                                    - se NON è vuota non fa niente, significa che già qualche altro modulo ha impostato questa variabile
        - step facoltativo: impostazione del file di configurazione da parte del NON-proprietario
            - flusso delle chiamate
                - set_public_rpath_macro or set_public_dirs_macro
                    - include(.../set_public_rpath.cmake) or include(.../set_public_config_rpath.cmake)
                        - RegisterConfigRpath
                            - questa macro può essere usata/inserita nel file "set_public_rpath.cmake" o nel file "set_public_config_rpath.cmake"
                                - N.B.: nel caso venga insieria nel file "set_public_rpath.cmake" se il file di configurazione viene sottoposto a versionamento si verificherà un errore nella fase di build, quindi questa macro deve essere spostata nel file "set_public_config_rpath.cmake"
                                - questo accade perchè nella fase di inizializzazione in cui viene chiamato il file "set_public_rpath.cmake" le variabili di versionamento devono ancora essere disponibili
                                    - N.B.: l'impostazione dei path relativi definiti nel file  "set_public_rpath.cmake" non può essere sottoposta a versionamento
                                    - N.B.: evitare di insierire la definizione degli rpath nel file "set_public_dirs.cmake", infatti
                                        - si può pensare infatti che venendo prima chiamati i files "set_public_dirs.cmake" dei moduli che si trovano più in alto nell'albero delle dipendenze allora
                                            - questo fatto assicura che non venga ignorata la variabile impostata
                                        - ATTENZIONE!!!!
                                            - tuttavia c'è una situazione in cui l'impostazione del file di configurazione da parte di un altro modulo venga ignorata 
                                                - accade quando ci sono più moduli che dipendono dal modulo proprietario dl file di config ma ad esempio solo uno imposta il file di configurazione
                                                    -  la soluzione è qella di definire il file di configurazion nel file "init/set_public_config_rpath.cmake"
                                                        - quando questo file viene letto/eseguito sono gia disponoibili le variabili di versionamento del codice
                                                        - si veda il flusso di isruzioni della macro "init_var_macro"
                            - questa macro esegue la seguente procedura
                                - controlla il contenuto della variabile che deve contenere il path relativo (rispetto la direcory "mpfw_code")
                                    - se NON è vuota genera un errore che interrompe la procedura di build avvisando che c'è un conflitto perche ci sono due moduli che stanno impostando lo stesso file o meglio un percorso diverso per uno stesso file
                                    - se è vuota allora imposta questa variabile al valore che gli è statio passato
    - utilizzo del file di configurazione
        - questo viene fatto dal modulo proprietario/owner
            - è lui che si incarica di segnalare al compilatore dove trovare il file di configurazione
            - questo significa che le variabili che definiscono le directories di configurazioni le ritroviamo nel file [include_files.cmake] del modulo proprietario
                - N.B.: in una precedente versione (ver < 03) del codice cmake questa cosa non è vera mentre è valida dalla versione 03 in poi



..............

    [from note_20240621_ncurses.md -> Wednesday, 21st May 2025]


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

    [from note_20240621_ncurses.md -> Monday, 19th May 2025]

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

    [from note_20240621_ncurses.md -> Monday, 5th May 2025]

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
..............


---

Friday, 2nd May 2025

- gestione file di configurazione dei moduli
    - ci dovrebbe essere un modulo [super_visor] che può essere visto/contatto da tutti i moduli e a sua volta può vedere tutti i moduli
        - un'applicazione/funzionalità si deve registrare quando si registra deve dire quali sub-funzionalità intende configurare
            - la funzionalità oggetto di configurazione  se non c'è nessuna super-funzionalità che la configura avrà al sua configurazione di default
            - la funzionalità oggetto della configurazione avra il suo spazio/directory nel mdulo [super-visor] all'interno di questo spazio ci saranno i vari moduli che la configurano
    

---

Last login: Thu Nov  6 05:48:47 on ttys009
Restored session: Wed Nov  5 19:21:18 CET 2025

- scopo della presente applicazione
    - implementare
        - il nuovo codice cmake,
        - le nuove librerie
    - nell'applicazione "mpfw_code_main_tst_20230810main"

- per raggiungere lo scopo si devono seguire i seguenti
    - steps
        - [1] 
        - [2] aggiornare le librerie delle directories
            - fnct/base
            - fnct/hw
            - fnct/tui
        - [c] al nuovo codice cmake
            - questo significa rivedere anche i nomi da assegnare ai moduli
        - [3] aggiornare la gestione dei moduli che interessano la comunicazione seriale
            - per tutte le piattaforme
        - [4] aggiornare il modulo [main] e la gestione del punto di accesso della funzione  [main()]
            - per tutte le piattaforme
        
- aggiornmanto del modulo al nuovo codice cmake
    - mpfw_fw2_fnct_base
        - mpfw_fw2-fnct-base-0abst
            - 

- come creare un nuovo modulo
    - come implementare i files di progetto/workspace (vedere directory [/wsp])
        - cpp_files.camke
            - la directory dei sorgenti (la [/src]) è contenuta nella seguente variabile
                - ${CURR_MOD_NAME}_cmmn_SRC_DIR
            - l'insieme dei files sorgenti deve essere posto nella seguente variabile
                - set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_CPP
        - include_files.camke
            - ${CURR_MOD_NAME}_cmmn_SRC_DIR
            - set(${CURR_MOD_NAME}_cmmn_SOURCE_FILES_H
        - le variabili di cui sopra vengono definite nei seguenti files 
            - "cmake/mpfw_fw2_cmake/v_03/includes/set_public_dirs.cmake"
            - "cmake/mpfw_fw2_cmake/v_03/includes/set_public_rpaths.cmake"
        - le variabili
            - _cmmn_SOURCE_FILES_CPP
            - _cmmn_SOURCE_FILES_H
        - [C] vengono usate nel seguente file
            - cmake/mpfw_fw2_cmake/v_03/macro/macro_init.cmake

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
