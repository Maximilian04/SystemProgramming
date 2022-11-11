static const wchar_t graphHead[] = L""
"digraph {\n"
"    rankdir = LR;\n"
"    node [shape = record; style = \"filled\";];\n"
"    splines = ortho;\n"
;

static const wchar_t graphTail[] = L""
"}\n"
;

// "    element_%d [label = <<FONT COLOR=\"cyan\">%p</FONT> | nil | 0x603000000040>; fillcolor = \"palegreen\"; color = \"green\";];\n"

#define ELEM_NODE_DEF \
"    element_%p [label = <<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n"

#define ELEM_PTR_SECTION(name, ...) \
"        <tr><td port=\"" #name "\">" __VA_OPT__("[") "<FONT COLOR=\"cyan\">%p</FONT>" __VA_OPT__("]") "</td></tr>\n"

#define ELEM_VALUE_SECTION(name) \
"        <tr><td port=\"" #name "\">%S</td></tr>\n"

#define ELEM_NODE_END \
"        </table>>;shape = \"none\";margin = \"0\";fillcolor = \"MistyRose\";color = \"green\";];\n"

#define ELEM_ARROW(nameSrc, nameDst, color) \
"    element_%p:" #nameSrc " -> element_%p:" #nameDst " [color = \"" #color "\";  constraint = false;];\n"

#define ELEM_WEIGTH_ARROW \
"    element_%p -> element_%p [style = invis; weight = 100;];\n"

static const wchar_t graphElemTemplate[] = L""

ELEM_NODE_DEF
ELEM_PTR_SECTION(head, yesplease)
ELEM_VALUE_SECTION(value)
ELEM_PTR_SECTION(next)
ELEM_PTR_SECTION(prev)
ELEM_NODE_END
ELEM_WEIGTH_ARROW
ELEM_ARROW(next:e, prev:w, coral)
ELEM_ARROW(prev:w, next:e, indigo)
;

#define GRAPH_ELEM_BODY(token, nextToken, prevToken, header, valueStr) \
    /* wString */ graphElemTemplate,                                    \
    /* DEF */ token,                                                     \
    /* PTR */ header,                                                     \
    /* VALUE */ valueStr,                                                  \
    /* PTR */ nextToken,                                                    \
    /* PTR */ prevToken,                                                     \
    /* WEIGTH_ARROW */ token, nextToken,                                      \
    /* ARROW        */ token, nextToken,                                       \
    /* ARROW        */ token, prevToken

#undef ELEM_NODE_DEF
#undef ELEM_PTR_SECTION
#undef ELEM_VALUE_SECTION
#undef ELEM_NODE_END
#undef ELEM_ARROW
#undef ELEM_WEIGTH_ARROW
