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

static const char htmlBeginBlock[] =
"<p> <div style=\"margin-left:%dch\">{</div>\n"
;

static const char htmlEndBlock[] =
"<p> <div style=\"margin-left:%dch\">}</div>\n"
;

static const char htmlLineTemplate[] =
"<p> <div style=\"margin-left:%dch\">%s</div>\n"
;

static const char htmlStrTemplate[] =
"    <div style=\"margin-left:%dch\">%s</div>\n"
;

static const char htmlCyanColorStart[] =
"<font color=\"cyan\">"
;

static const char htmlCyanColorStop[] =
"</font>"
;

static const char htmlCyanPointer[] =
"<font color=\"cyan\">%p</font>"
;
