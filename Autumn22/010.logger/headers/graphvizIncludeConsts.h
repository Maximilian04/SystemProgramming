static const wchar_t graphHead[] = L""
"// negate UTF-8 BOM effect: Я не могу понять, где прекратится круг. Мне не хватает сил, и только сердца стук мне говорит о том, что мир ещё живой, что он не проклят и давно спасён тобой!\n"
"digraph {\n"
"    rankdir = LR;\n"
"    node [shape = record; style = \"filled\";];\n"
"    // splines = ortho;\n"
;

static const wchar_t graphTail[] = L""
"}\n"
;

static const char graphRunCommandTemplate[] =
"D:\\programming\\libraries\\Graphviz\\bin\\dot.exe -Tpng \"%s\" -o\"%s\""
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

static const wchar_t graphElemBodyTemplate[] = L""
    ELEM_NODE_DEF
    ELEM_PTR_SECTION(head, yesplease)
    ELEM_VALUE_SECTION(value)
    ELEM_PTR_SECTION(next)
    ELEM_PTR_SECTION(prev)
    ELEM_NODE_END
;
static const wchar_t graphElemOrderTemplate[] = L""
    ELEM_WEIGTH_ARROW
;
static const wchar_t graphArrow2NextTemplate[] = L""
    ELEM_ARROW(next:e, head:w, coral)
;
static const wchar_t graphArrow2PrevTemplate[] = L""
    ELEM_ARROW(prev:w, head:e, indigo)
;

#define GRAPH_ELEM_BODY(token, nextToken, prevToken, header, valueStr) \
    /* wString */ graphElemBodyTemplate,                                \
    /* DEF */ token,                                                     \
    /* PTR */ header,                                                     \
    /* VALUE */ valueStr,                                                  \
    /* PTR */ nextToken,                                                    \
    /* PTR */ prevToken

#define GRAPH_ELEM_ORDER(token, nextToken) \
    /* wString */ graphElemOrderTemplate,   \
    /* WEIGTH_ARROW */ token, nextToken

#define GRAPH_ARROW_2NEXT(token, nextToken) \
    /* wString */ graphArrow2NextTemplate,   \
    /* ARROW        */ token, nextToken

#define GRAPH_ARROW_2PREV(token, prevToken) \
    /* wString */ graphArrow2PrevTemplate,   \
    /* ARROW        */ token, prevToken

#undef ELEM_NODE_DEF
#undef ELEM_PTR_SECTION
#undef ELEM_VALUE_SECTION
#undef ELEM_NODE_END
#undef ELEM_ARROW
#undef ELEM_WEIGTH_ARROW
