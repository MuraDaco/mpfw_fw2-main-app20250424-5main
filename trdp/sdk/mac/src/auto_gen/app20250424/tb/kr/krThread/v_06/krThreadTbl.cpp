//  *******************************************************************************
//  
//  mpfw / fw2 - Multi Platform FirmWare FrameWork 
//      library that contains the "main" entry point and, 
//      eventualy, application code that is platform dependent
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
 * krThreadTbl.cpp
 *
 *  Created on: Jul, 30 2025 (Wed)
 *      Author: Marco Dau
 */

#include "krThreadTbl.h"

// lib include
// ->> #include modules here ... <<-
#include "krTimerManager.h"
#include "svStateMachineManager.h"
#include "app_ManagerCmmn.h"
#include "app_Manager.h"

namespace fw2 {namespace wrapper {namespace core	{

krThreadTbl::ThreadLoopFunction_t krThreadTbl::LoopFunctionArray[] = {

    // ->> list of pointer function here ... <<-
        PTR_TASK_OF_krThread_000_APPL_APP20250424_4APPL_thread_interrupt,
        PTR_TASK_OF_krThread_000_APPL_APP20250424_4APPL_thread_loopApp0,
        PTR_TASK_OF_krThread_001_APPL_APP20250424_4APPL_thread_loopApp1,
        PTR_TASK_OF_krThread_001_FNCT_CORE_3REAL_KR_TIMER_LoopCheck,
        PTR_TASK_OF_krThread_001_FNCT_CORE_3REAL_KR_TIMER_LoopUpdate,
        PTR_TASK_OF_krThread_002_APPL_APP20250424_4APPL_thread_loopApp2,
        PTR_TASK_OF_krThread_002_FNCT_CORE_3REAL_SV_STATE_MACHINE_LoopUpdate,

    nullptr
};

} } } // namespace fw2::wrapper::core

