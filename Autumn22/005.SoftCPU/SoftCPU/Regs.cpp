#include <assert.h>

#include "logger\loggerRegs.h"
#include "Regs.h"

namespace regs {
    /**
     * @brief Returns pointer to register with **code**
     *
     * @param regs Regs object
     * @param [in] code Code
     * @return AsmCode_t* Pointer to register or **nullptr** if it is incorrect
     */
    AsmCode_t* getReg(Regs* regs, AsmCode_t code) {
        switch (code) {
        case asmLang::RAX_CODE:
            return &regs->a;
        case asmLang::RBX_CODE:
            return &regs->b;
        case asmLang::RCX_CODE:
            return &regs->c;
        case asmLang::RDX_CODE:
            return &regs->d;
        default:
            return nullptr;
        }
    }

#ifdef REGS_DEBUG
    Error ctor(Regs* const regs, DEBUGINFO_CTOR_ARGS_H) {
#else // !REGS_DEBUG
    Error ctor(Regs* const regs) {
#endif // REGS_DEBUG
        assert(regs != nullptr);

        regs->a = 0;
        regs->b = 0;
        regs->c = 0;
        regs->d = 0;

#ifdef REGS_DEBUG
        regs->debugInfo.objName = objName;
        regs->debugInfo.ctorCallLine = ctorCallLine;
        regs->debugInfo.ctorCallFile = ctorCallFile;
        regs->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // REGS_DEBUG

        return Error::OK;
    }

    Error dtor(Regs* const regs) {
        assert(regs != nullptr);
        
        return Error::OK;
    }

    Error dump(Regs* const regs, LOGFUNCHEAD_ARGS_H) {
        assert(regs != nullptr); //TODO Dump (nullptr)
        assert(funcName != nullptr);
        assert(fileName != nullptr);
        logger::openLogFile();

        logger::logHtmlHead();
        logger__logFuncHead());
        if (regs == nullptr) {
            logger::emergencyLog("Mem is nullptr");
            assert(false);
        } else {
#ifdef REGS_DEBUG
            logger::logStructHeadDebug("Regs", regs, &regs->debugInfo);
#else // !REGS_DEBUG
            logger::logStructHead("Regs", regs);
#endif // REGS_DEBUG
            logger::logRegs(regs);
        }
        logger::logHtmlTail();

        logger::closeLogFile();

        return Error::OK;
    }
}
