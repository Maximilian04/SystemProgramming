#include <assert.h>

#include "logger.h"

static const char htmlHead[] =
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"    <title>Log</title>\n"
"\n"
"    <style>\n"
"        body {\n"
"            font-family: 'Roboto Mono', monospace;\n"
"            line-height: 0%;\n"
"        }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"\n"
;

static const char htmlTail[] =
"\n"
"</html>\n"
"</body>\n"
;

static const char htmlBeginBlock[] =
"<p> <div style=\"margin-left:%dch\">{</div>\n"
;

static const char htmlEndBlock[] =
"<p> <div style=\"margin-left:%dch\">}</div>\n"
;

static const char htmlStrTemplate[] =
"<p> <div style=\"margin-left:%dch\">%s</div>\n"
;

namespace logger {
    static int marginCounter = 0;

    void logHtmlHead(FILE* logFile) {
        assert(logFile != nullptr);
        fprintf(logFile, "%s",
            htmlHead);
    }

    void logHtmlTail(FILE* logFile) {
        assert(logFile != nullptr);
        fprintf(logFile, "%s",
            htmlTail);
    }

    void beginBlock(FILE* logFile) {
        assert(logFile != nullptr);
        ++marginCounter;
        fprintf(logFile, htmlBeginBlock,
            marginCounter * 4);
    }

    void endBlock(FILE* logFile) {
        assert(logFile != nullptr);
        fprintf(logFile, htmlEndBlock,
            marginCounter * 4);
        --marginCounter;
    }

    void logStr(FILE* logFile, const char* const str) {
        assert(logFile != nullptr);
        fprintf(logFile, htmlStrTemplate,
            marginCounter * 4, str);
    }
}
