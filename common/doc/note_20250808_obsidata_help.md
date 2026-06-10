

smb://192.168.56.2/mypass2

---

Monday,  7th July 2025

- inizializzazione
    - sequenza delle procedure 
        - step 0
            - inizializzare a git le directories dei nuovi moduli
                - $ git init
                - attenzione! 
                    - aggiungere un opportuno .gitignore file per non includere i file di build ed altri files che non interessano
                - $ git add .
                - $ git commit -m "First commit"
                - $ git logpretty / git log --pretty=oneline --decorate --graph --all
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


- comandi associati alle sequenze delle procedure
    - add new module
        - sequenza comandi 
            - [1](New: New module ...)
            - [3](Adb: Add & Absorb an existing one)
                - al prompt **" dbg msg - obdash.sh -> 2. What kind of repo does the module belong to? "**
                    - select **" 3	projects "**
                - al prompt **" dbg msg - obdash.sh -> Where are the remote repositories phisically stored? "**
                    - select **" 5	smb_mypass2 "**
                - al prompt **" dbg msg - obdash.sh -> 2.3. What machine is the remote storage partition mounted on? "**
                    - select **" 1	onglinetsmbmac "**
    - gmmg config files
        - sequenza comandi 
            - [4](Branch: Create, Checkout, ... branch)
            - [10](BFI: Branch configuration File Initialization)
                - poi aggiornare il file "obdash_branches_owner.cfg"
                    - aggiornare la voce "prefix" che all'inizio è posta a "zzz"
                        - impostarla al valore di "dev" (in particolare al valore del parametro "sonomaworkprefix" della sezione "[machine "macmini"]" del file "obdash_branches.cfg" )
    - development branch
        - creation
            - sequenza comandi 
                - [4](Branch: Create, Checkout, ... branch)->
                - [9](BCr: Branch Creation)->...->[1](BcOw: Branch owner)
        - checkout
            - sequenza comandi 
                - [4](Branch: Create, Checkout, ... branch)->
                - [3](BcC: Branch Checkout)->...->[1](BcOw: Branch owner)
        - push (esegue il push anche se il branch non è ancora presente nella repository remota)
            - sequenza comandi 
                - [3](Push_Pull: Push & Pull procedures)->
                - [1](Psh: $ git push)
                - N.B.: eseguire prima il checkout sul "main" branch e poi eseguire questa procedura
    - "main" branch
        - checkout
            - sequenza comandi 
                - [4](Branch: Create, Checkout, ... branch)->
                - [3](BcC: Branch Checkout)->...->[2](BcMn: Branch main)
        - push (esegue il push anche se il branch non è ancora presente nella repository remota)
            - sequenza comandi 
                - [3](Push_Pull: Push & Pull procedures)->
                - [1](Psh: $ git push)
                - N.B.: eseguire prima il checkout sul "main" branch e poi eseguire questa procedura
    - remote repository
        - creation
            - sequenza comandi [2](URL: Set remote repository URL)->[2](SUP: Set new url and then push)
                - i passi successivi sono
                    - selezionare il gruppo di moduli -> scegliere "project"
                    - selezionare il modulo desiderato
                    - selezionare la modalità di come impostare l'URL -> scegliere l'opzione "3	command:SRUc: Storage custom"
                    - se si sta usando il mypassport2 (formattato su linux con ext4 e messo a disposizione con il protocollo samba dalla macchina virtuale archlinux)
                        - selezionare l'opzione "5  smb_mypass2", poi
                        - selezionare l'opzione "1  onglinetsmbmac", poi
                        - ci sono due steps di conferma
                        - poi inizia la procedura
                            - se loa repository remota non esiste viene chiesto se crearla, rispodere si
                        - fine della procedura, tutto dovrebbe essere a posto



