#include <assert.h>

#include "logger\loggerMem.h"
#include "Mem.h"

namespace mem {
    /**
     * @brief Returns pointer to register with **code**
     *
     * @param mem Mem object
     * @param [in] code Code
     * @return AsmCode_t* Pointer to register or **nullptr** if it is incorrect
     */
    AsmCode_t* getRAM(Mem* mem, size_t addr) {
        if (addr > mem->size)
            return nullptr;
        return mem->RAM + addr;
    }

#ifdef MEM_DEBUG
    Error ctor(Mem* const mem, DEBUGINFO_CTOR_ARGS_H, size_t size) {
#else // !MEM_DEBUG
    Error ctor(Mem* const mem, size_t size) {
#endif // MEM_DEBUG
        assert(mem != nullptr);

#ifdef MEM_DEBUG
        mem->debugInfo.objName = objName;
        mem->debugInfo.ctorCallLine = ctorCallLine;
        mem->debugInfo.ctorCallFile = ctorCallFile;
        mem->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // MEM_DEBUG

        mem->size = size;
        mem->RAM = (AsmCode_t*)calloc(size, sizeof(AsmCode_t));
        if (mem->RAM == nullptr)
            return Error::CALLOC;

        return Error::OK;
    }

    Error dtor(Mem* const mem) {
        assert(mem != nullptr);

        free(mem->RAM);

        return Error::OK;
    }

    Error dump(Mem* const mem, LOGFUNCHEAD_ARGS_H) {
        assert(mem != nullptr); //TODO Dump (nullptr)
        assert(funcName != nullptr);
        assert(fileName != nullptr);
        logger::openLogFile();

        logger::logHtmlHead();
        logger__logFuncHead());
        if (mem == nullptr) {
            logger::emergencyLog("Mem is nullptr");
            assert(false);
        } else {
#ifdef MEM_DEBUG
            logger::logStructHeadDebug("Mem", mem, &mem->debugInfo);
#else // !MEM_DEBUG
            logger::logStructHead("Mem", mem);
#endif // MEM_DEBUG
            logger::logMem(mem);
        }
        logger::logHtmlTail();

        logger::closeLogFile();

        return Error::OK;
    }
}
