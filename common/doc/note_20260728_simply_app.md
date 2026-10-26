
---

Sun  9 Aug 2026 13:50:39 CEST

- 00.00 - 04.00 --- dormire
- 04.00 - 12.00 --- lavorare
- 12.00 - 14.00 --- mangiare
- 14.00 - 
- 20.00 - 22.00 --- lavorare
- 22.00 - 00.00 --- mangiare

- *****************

- 00.30 - 03.30 --- lavorare  ~~~~ 21.30 - 00.30  ++++ 19.30 - 22.30
- 03.30 - 05.00 --- mangiare  ~~~~ 00.30 - 02.00  ++++ 22.30 - 00.00 - colazione
- 05.00 - 09.00 --- dormire   ~~~~ 02.00 - 06.00  ++++ 00.00 - 04.00
- 09.00 - 14.00 --- lavorare  ~~~~ 06.00 - 11.00  ++++ 04.00 - 09.00
- 14.00 - 16.00 --- mangiare  ~~~~ 11.00 - 13.00  ++++ 09.00 - 11.00 - pranzo
- 16.00 - 21.00 --- varie     ~~~~ 13.00 - 18.00  ++++ 11.00 - 16.00
- 21.00 - 22.30 --- mangiare  ~~~~ 18.00 - 19.30  ++++ 16.00 - 17.30 - cena
- 22.30 - 00.30 --- dormire   ~~~~ 19.30 - 21.30  ++++ 17.30 - 19.30


---

Tue 28 Jul 2026 16:02:33 CEST

- configurazione dei pin associati ai led e ai tasti



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
