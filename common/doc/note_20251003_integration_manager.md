
---

Last login: Wed Oct 29 05:13:00 on console
Restored session: Tue Oct 28 18:45:13 CET 2025



---

Last login: Fri Oct 10 09:01:51 on console
Restored session: Thu Oct  9 19:34:33 CEST 2025

    - cose da vedere ed eventualmente fare
    - gestione synchro locale
        - nel caso di repository pubblica su web come github.com permettere la synchrnonizzazione in locale senza doversi collegare su internet

---

Last login: Thu Oct  9 08:41:14 on console
Restored session: Wed Oct  8 19:11:50 CEST 2025

- gestione scenari tra "[repos_sync].sh" & "[repos_list_sync].sh"
    - analisi dei "casi d'uso" [use_case]
        - per decidere gli [use_case] fa testo la repository public dello sviluppatore quindi
            - scenario di [test]
                - nello scenario [test] non si lavora con le repository che risiedono in  mypass2
                    - quindi ci dovrà essere, oltre la repo pubblica dello sviluppatore, una repository locale dello sviluppatore necessaria per generare i commit da scaricare nella sua repo publica
                - c'è un solo caso d'uso quello di test
                    - <repo pubblica (github)>
                    - <repo pubblica locale dello sviluppatore>
                    - <repo di lavoro principale locale dello sviluppatore>
                    - <repo di lavoro si servizio locale dello sviluppatore>
                    - <repo locale integration manager>
            - scenario [reale]
                - nello scenario [reale] c'è una situazione di test in cui l'url di [github] è simulato con una directory locale
                - ci saranno quindi due possibilità/stati
                    - [reale/github]
                        - scripts
                            - </scrp/intgrm/scrp/repos_list_sync.sh --public-intgrm local --public-dvlpr real --create-local-public-repos>
                            - </scrp/intgrm/scrp/repos_sync.sh --scn-intgrm reale --ws-intgrm github --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/(module_name).git" --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/(module_name).git" --rel-name First_Release --rel-null 1 3  --rel-inc 2>
                        - repos
                            - <repo pubblica (github)>
                                - "https://github.com/MuraDaco/<module name>.git"
                            - <repo pubblica locale dello sviluppatore>
                                - "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/<module name>.git"
                            - <repo locale integration manager>
                                - /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[reale]/manager/intgrm_[github]
                    - [reale/locale]
                        - scripts
                            - </scrp/intgrm/scrp/repos_list_sync.sh --public-intgrm local --public-dvlpr real --create-local-public-repos>
                            - </scrp/intgrm/scrp/repos_sync.sh --scn-intgrm reale --ws-intgrm test1 --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/(module_name).git" --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/(module_name).git" --rel-name First_Release --rel-null 1 3  --rel-inc 2>
                        - repos
                            - <repo pubblica (github)>
                                - "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/<module name>.git"
                            - <repo pubblica locale dello sviluppatore>
                                - "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/<module name>.git"
                            - <repo locale integration manager>
                                - /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[reale]/manager/intgrm_[test1]
    - quando in [repos_list_sync] 
        - è attiva l'opzione  [--public-dvlpr] con parametro [real]
        - e
        - case 1
            - è attiva l'opzione  [--public-intrm] con parametro [local]
                - allora quando viene eseguito lo script [repos_sync] si devono impostare le opzioni 
                    - [--scn-intgrm]    con parametro [reale] 
                    - [--ws-intgrm]     con parametro [test1]
                - .
                - in questo modo la repository locale (di lavoro) dell'integration manager sarà
                    - [intgrm_local_repo]/[intgrm_working_repo] = /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[reale]/manager/intgrm_[test1]
                - altrimenti sarà
                    - [intgrm_local_repo]/[intgrm_working_repo] = /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[1]/manager/intgrm_[ws2]
        - case 2
            - è attiva l'opzione  [--public-intrm] con parametro [github]
                - allora quando viene eseguito lo script [repos_sync] si devono impostare le opzioni 
                    - [--scn-intgrm]    con parametro [reale] 
                    - [--ws-intgrm]     con parametro [github]
                - .
                - in questo modo la repository locale (di lavoro) dell'integration manager sarà
                    - [intgrm_local_repo]/[intgrm_working_repo] = /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[reale]/manager/intgrm_[github]
                - altrimenti sarà
                    - [intgrm_local_repo]/[intgrm_working_repo] = /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_[1]/manager/intgrm_[ws2]
- gestione repository locale dell'integration manager            


---

Last login: Wed Oct  8 08:38:37 on console
Restored session: Tue Oct  7 19:39:06 CEST 2025

- automatizzare la procedura di sncronizzazione in locale  poi in https
    - via pipe
    - via file
- come implementare lo script
    - parametri in ingresso
    - gestione della lista dei moduli
        - via pipe
        - direttamente sulla directory contenente le repositorie dei moduli ma solo nel caso l'opzione --developer è real
    - capire se può essere utile usare un file di configurazione usando 
        - il comando git config
        - oppure un semplice file di testo sfruttando il comando bash "cut"
    - gestione delle repositories pubbliche nel caso l'opzione --public-intgrm sia local
        - verificare che esistano in caso contrario crearle se è presente l'opzione --create-local-public-repos
    


${BASH_SOURCE[0]} --public-intgrm https/file --public-dvlpr real/test
--public-intgrm
    github -> --publc "https://github.com/MuraDaco/$item.git"
    local  -> --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/public/https/github/$item.git"
--public-dvlpr
     real  -> --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/$item.git"
     test  -> --dvlpr "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/developer/mypass2_repo/$item.git"
do not allow ( --protocol https --developer test ) therefore when --protocol is equal to https, the--developer option is set to real     

     ./scrp/intgrm/scrp/repos_sync.sh 
     --scn-intgrm <scenario  name> 
     --ws-intgrm <workstation name> 
     --publc "<repo of step_1, remote public (github simulation)>" 
     --dvlpr "<repo of step_1, remote public developer (mypass2 simulation)>" --rel-name First_Release --rel-null 1 3  --rel-inc 2
 
 ls "/Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs" | grep "mpfw_code_"
 ls "/Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs" | grep "mpfw_fw2"  
 ./scrp/intgrm/scrp/repos_sync.sh 
     --scn-intgrm reale 
     --ws-intgrm ws_reale
     --publc "https://github.com/MuraDaco/$item.git" 
     --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/$item.git" 
     --rel-name First_Release --rel-null 1 3  --rel-inc 2

************

work@umtiefs-Mac-mini mpfw_code % ./scrp/intgrm/scrp/repos_list_sync.sh --public-intgrm local --public-dvlpr real --create-local-public-repos
READING "/Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs" folder ... 
Reading input parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PERFORMING synchro command ...
START ...
get_input_params ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
chk_input_params ...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INFO - Protocol about "github" repo is file
INFO - "DVLPR" repository exists.
INFO - Protocol about "github" repo is file
INFO - "GITHUB" repository exists.
INFO - "PUBLC" repository exists.
INFO - "Integration Manager workstation" folder exists.
INFO - "developer" and "public" module names match and it is "mpfw_code_apps_tst_20221206"
get_input_params ... step_result: 0
INFO - "/Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/manager/intgrm_ws2/mpfw_code_apps_tst_20221206" folder already exists
INFO - git repository is already initialized
INFO - the curent local repository is NOT empty, there are already some files
INFO - the current repo has already some commits. These commits may be local and/or remote, for an info more precise another check step is necessary
INFO - the current branch is different from 'main' branch therefore "public & developer main" branches should be already initialized but to be secure about it another check step is necessary
INFO - "publc" remote repo is NOT configured yet
INFO - Configuring "publc" remote repo ...
error: remote github already exists.
ERROR - The 'git remote add  github "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/mpfw_code_apps_tst_20221206.git"' command FAILED.
|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|
Global variables summary ...
|~~~~~
repo_publc: file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/mpfw_code_apps_tst_20221206.git
repo_dvlpr: file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/mpfw_code_apps_tst_20221206.git
release_name: First_Release
release_null_field_1: yes
release_null_field_3: yes
release_inc_field_2: yes
protocol_repo_dvlpr: file
path_repo_dvlpr: /Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/mpfw_code_apps_tst_20221206.git
protocol_repo_publc: file
path_repo_publc: /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/remote/public/https/github/mpfw_code_apps_tst_20221206.git
scenario_intgrm: scenario_1
workstation_intgrm: intgrm_ws2
path_repo_intgrm_root_folder_default: /Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/manager/intgrm_ws2
repo_publc_nick_name: github
|^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^|
Global variables summary ...
|~~~~~
public_intgrm: local
public_dvlpr: real
create_local_public_repos: yes
work@umtiefs-Mac-mini mpfw_code % 

************

---

Last login: Mon Oct  6 04:39:51 on console

- gestione degli scenai e delle workstation
    - --scenario "real"
    - --workstation "ws2"

- selezione degli scenari
    - --real-local
    - --real-https
    - --test-local
    - --test-https
    - lo si porebbe ricavare anche dal protocollo della repository remota pubblica
        - se il protocollo è "https" lo scenario viene posto come real

./scrp/intgrm/scrp/repos_sync.sh --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/public/https/github/Module_yy.git" --dvlpr "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/developer/mypass2_repo/Module_yy.git" --rel-name Second_Release --rel-null 1  --rel-inc 3

./scrp/intgrm/scrp/repos_sync.sh --publc "file:///mpfw_code_apps_tst_20221206.git" --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/mpfw_code_apps_tst_20221206.git" --rel-name Second_Release --rel-null 1  --rel-inc 3

./scrp/intgrm/scrp/repos_sync.sh --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/public/https/github/mpfw_code_apps_tst_20221206.git" --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/mpfw_code_apps_tst_20221206.git" --rel-name First_Release --rel-null 1  --rel-inc 3

./scrp/intgrm/scrp/repos_sync.sh --env-intgrm "intgrm_ws2" "mpfw_code_apps_tst_20221206"

https://github.com/MuraDaco/mpfw_code_apps_tst_20221206.git

./scrp/intgrm/scrp/repos_sync.sh --publc "https://github.com/MuraDaco/mpfw_code_apps_tst_20221206.git" --dvlpr "file:///Volumes/mypass2/ObsiDataRemote/Year_2023/repo__prjs/mpfw_code_apps_tst_20221206.git" --rel-name First_Release --rel-null 1 2  --rel-inc 3


---

Last login: Fri Oct  3 06:46:51 on console

- sequenza per creare l'ambiente di test
    - l'ambiente di test è costituito dai seguenti elementi
        - repository remota pubblica
            - https://github.com
            - può essere simulata con una repository remota che risisede in un harddisk anche interno
            - può accedervi in scrittura solo l'integration manager
            - può essere letta da chiunque
        - repository remota (pubblica nel senso che è condivisa tra sviluppatore e integration manager) dello sviluppatore
            - puo risiedere in un harddisk esterno accessibile via rete
                - esempio: mypass1 o mypass2
            - può essere simulata sitandola in un harddisk interno alla workstation
            - può accedervi in scrittura solo lo sviluppatore
            - viene letta dall'integration manager e solo il branch "main" che verrà collegato al branch "dvlpr_main"
        - repository locale dello sviluppatore PRINCIPALE
            - esempio: [.../mpfw_code/main/app20240619_new_bis/layer/mpfw_fw2-main-app20240619_new_bis-5main]
                - sarà situata
                    - nello scenario reale
                        - .../mpfw_code/main/app20240619_new_bis/layer/mpfw_fw2-main-app20240619_new_bis-5main
                    - nello scenario di test
                        - [$HOME/ObsiData/distributed_git/integration_manager_workflow/scenario_test/developers/dvlpr1_ws1]
        - repository locale dello sviluppatore DI SERVIZIO
            - esempio: puo riisiedere ina "dvlpr_ws2" se la repository qualunque locazione
            - usata solo nello scenario di test nel caso si voglia avere una repository remota non vuota
            - scopo
                - accedere alla repository pubblica di test (github) per poter inserire dei commit nel branch main
                    - per simulare una repository remota pubblica non vuota
            - sarà situata nella directory 
                - [$HOME/ObsiData/distributed_git/integration_manager_workflow/scenario_test/developers/dvlpr1_ws2]
                    - N.B.: la directory è diversa da quella principale che risiede in [.../dvlpr1_ws1] mentre questa in [.../dvlpr1_ws2]
        - repository locale dell'integration manager
            - le opzioni usate sono
                - --env-intgrm
                    - usata per verificare lo stato della repository dell'integration manager
                    - altre opzioni sono
                        - --scenario <scenario name>
                        - --ws-intgrm
            - avrà due branch indipendenti 
                - branch "[github_main]" collegato con il branch "main" della repository pubblica (situata ad esempio in https://github.com)
                - branch "[dvlpr_main]" collegato con il branch "main" della repository "pubblica" dello sviluppatore (situata ad esempio in mypass2)
            - sarà situata nella directory 
                - nello scenario reale
                    - [$HOME/ObsiData/distributed_git/integration_manager_workflow/scenario_reale/manager/intgrm_ws1]
                - nello scenario di test
                    - [$HOME/ObsiData/distributed_git/integration_manager_workflow/scenario_test/manager/intgrm_ws1]
    - scenario di test
        - preparazione ambiente di test
            - [nota] verranno usate le opzioni [--env-...]
            - [step_1] creare le repository
                - remote
                    - Pubblica che simula quella su githuib
                        - </scrp/intgrm/scrp/repos_sync.sh --env-publc-remote "github" "Module_xx">
                    - dello sviluppatore che simula quella su hdd esterno ad esempio mypass1/2
                        - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr-remote "mypass2_repo" "Module_xx">
                - locali
                    - dello sviluppatore
                        - principale
                            - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws1" "Module_xx">
                        - di servizio
                            - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws2" "Module_xx">
                    - dell'integration manager
                        - verrà creata non attaverso i comandi "--env-..."
            - [step_2] configurare le repository remote nelle repository locali con il comando "git remote add"
                - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws1" "Module_xx" remote_config:mypass2_repo>
                - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws2" "Module_xx" remote_config:public:github>
            - [step_3] generare i commit (nelle repositories locali) e trasferirli, via il comando "git push" nelle repositories remote
                - [step_3_1] generare il primo commit
                    - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws1" "Module_xx" upd_files:commit:First_commit>
                    - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws2" "Module_xx" upd_files:commit:First_commit_from_developer>
                - [step_3_2] eseguire il primo push con il parametro [--set-upstream] necessario per il track ai branch [main] delle repo remote
                    - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws1" "Module_xx" git:push:set-upstream>
                    - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws2" "Module_xx" git:push:set-upstream:public>
            - [step_4] aggiornare i files e poi sincronizzarsi con le repo remote
                    - </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws1" "Module_xx" upd_files:commit:Second_commit:push>
                    - [facoltativo] </scrp/intgrm/scrp/repos_sync.sh --env-dvlpr "dvlpr1_ws2" "Module_02" upd_files:commit:Second_commit_from_developer:push>
        - passi comuni allo scenario reale
            - eseguire la sincronizzazione con il comando
            - </scrp/intgrm/scrp/repos_sync.sh --publc "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/public/https/github/Module_xx.git" --dvlpr "file:///Users/work/ObsiData/distributed_git/integration_manager_workflow/scenario_1/remote/developer/mypass2_repo/Module_xx.git" --rel-name Second_Release --rel-null 1  --rel-inc 3 --scenario reale --ws-intgrm ws1 >
    - scenario reale