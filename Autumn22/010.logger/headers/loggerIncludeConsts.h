#include <colors.settings.h>

static const char logFileName[] =
"log1.html"
;

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
"</body>\n"
"</html>\n"
;

static const char htmlStrTemplate[] =
"    <div style=\"margin-left:%dch; margin-top:%dem\">%s</div>\n"
"    <div style=\"margin-top:%dem\"></div>\n"
;

static const char htmlCyanColorStart[] =
"<font color=\"" COLORS_SETTINGS_ADDRPOINTER_TEXTCOLOR "\">"
;

static const char htmlCyanColorStop[] =
"</font>"
;

static const char htmlCyanPointer[] =
"<font color=\"" COLORS_SETTINGS_ADDRPOINTER_TEXTCOLOR "\">%p</font>"
;

static const char htmlLogicalPointer[] =
"<font color=\"" COLORS_SETTINGS_LOGICPOINTER_TEXTCOLOR "\">%u</font>"
;

static const char htmlCrimsonColorStart[] =
"<font color=\"" COLORS_SETTINGS_BADDATA_TEXTCOLOR "\">"
;

static const char htmlCrimsonColorStop[] =
"</font>"
;

static const char htmlEmergencyColorStart[] =
"<font color=\"" COLORS_SETTINGS_EMERGANCYMSG_TEXTCOLOR "\">"
;

static const char htmlEmergencyColorStop[] =
"</font>"
;

static const char htmlImageHead[] =
"<img src=\""
;

static const char htmlImageTail[] =
"\" style=\"margin-top:0.5em; margin-bottom:-0.5em\" alt=\"Я не могу понять, где мне искать обман. Страницы прочь - читаю только по губам. Три, две, одна, ноль строк, как безупречен слог! Ещё одна глава из жизни за порог...\">\n"
;
