static const wchar_t graphHead[] = L""
"// negate UTF-8 BOM effect: Я не могу понять, где прекратится круг. Мне не хватает сил, и только сердца стук мне говорит о том, что мир ещё живой, что он не проклят и давно спасён тобой!\n"
"digraph {\n"
// "    dpi = 200;\n"
"    rankdir = LR;\n"
// "    fontname = \"Mono\"\n"
"    node [shape = record; style = \"filled\";];\n"
"    // splines = ortho;\n"
;

static const wchar_t graphTail[] = L""
"}\n"
;

static const char graphRunCommandTemplate[] =
"D:\\programming\\libraries\\Graphviz\\bin\\dot.exe -Tpng \"%s\" -o\"%s\""
;

#define ELEM_NODE_DEF \
"    element_%p [label = <<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n"

#define ELEM_PTR_SECTION(name, ...) \
"        <tr><td port=\"" #name "\" colspan=\"2\">" __VA_OPT__("[") "<FONT COLOR=\"cyan\">%p</FONT>" __VA_OPT__("]") "</td></tr>\n"

#define ELEM_NULLPTR_SECTION(name, ...) \
"        <tr><td port=\"" #name "\" colspan=\"2\">" __VA_OPT__("[") "<FONT COLOR=\"indianRed\">0 (nullptr)</FONT>" __VA_OPT__("]") "</td></tr>\n"

#define ELEM_VALUE_SECTION(name) \
"        <tr><td port=\"" #name "_1\">[%u]</td><td port=\"" #name "_2\">%S</td></tr>\n"

#define ELEM_NODE_END \
"        </table>>;shape = \"none\";margin = \"0\";fillcolor = \"MistyRose\";color = \"RosyBrown\";];\n"
// "        </table>>;shape = \"none\";margin = \"0\";fillcolor = \"MistyRose\";color = \"green\";];\n"

#define ELEM_ARROW(nameSrc, nameDst, color) \
"    element_%p:" #nameSrc " -> element_%p:" #nameDst " [color = \"" #color "\"; constraint = false;];\n"

#define ELEM_WEIGTH_ARROW \
"    element_%p -> element_%p [style = invis; weight = 100;];\n"

#define graphElemBody__TemplateDEF(token, cmd1, cmd2)          \
    static const wchar_t graphElemBody##token##Template[] = L"" \
        ELEM_NODE_DEF                                            \
        ELEM_PTR_SECTION(head, yesplease)                         \
        ELEM_VALUE_SECTION(value)                                  \
        cmd1(next)                                                  \
        cmd2(prev)                                                   \
        ELEM_NODE_END

graphElemBody__TemplateDEF(PP, ELEM_PTR_SECTION, ELEM_PTR_SECTION);
graphElemBody__TemplateDEF(PN, ELEM_PTR_SECTION, ELEM_NULLPTR_SECTION);
graphElemBody__TemplateDEF(NP, ELEM_NULLPTR_SECTION, ELEM_PTR_SECTION);
graphElemBody__TemplateDEF(NN, ELEM_NULLPTR_SECTION, ELEM_NULLPTR_SECTION);

#undef graphElemBody__TemplateDEF

#define GRAPH_ELEM_BODY(NPtoken, token, index, header, valueStr, ...) \
    /* wString */ graphElemBody##NPtoken##Template,                    \
    /* DEF */ token,                                                    \
    /* PTR */ header,                                                    \
    /* INDEX | VALUE */ index, valueStr                                   \
    /* PTR-s */ __VA_OPT__(, __VA_ARGS__)

static const wchar_t graphElemOrderTemplate[] = L""
ELEM_WEIGTH_ARROW
;
static const wchar_t graphArrow2NextTemplate[] = L""
ELEM_ARROW(next:e, head:w, coral)
;
static const wchar_t graphArrow2PrevTemplate[] = L""
ELEM_ARROW(prev:w, head:e, indigo)
;

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
#undef ELEM_NULLPTR_SECTION
#undef ELEM_VALUE_SECTION
#undef ELEM_NODE_END
#undef ELEM_ARROW
#undef ELEM_WEIGTH_ARROW

static const wchar_t graphHeadTailEgg[] = L""
"    element_tail [label = <tail>;shape = \"egg\";margin = \"0\";fillcolor = \"white\";color = \"black\";];\n"
"    element_head [label = <head>;shape = \"egg\";margin = \"0\";fillcolor = \"white\";color = \"black\";];\n"
"    element_tail -> element_head [style = invis; weight = 100;];\n"
"\n"
"    { rank=same; element_tail; element_%p; }\n"
"    { rank=same; element_head; element_%p; }\n"
"\n"
"    element_tail:s -> element_%p:head:n [color = \"indigo\"; weigth = 200;];\n"
"    element_head:s -> element_%p:head:n [color = \"coral\"; weigth = 200;];\n"
;

#define GRAPH_HEADTAIL_EGG(headToken, tailToken) \
    /* wString */ graphHeadTailEgg,               \
    /* ranking */ tailToken, headToken,            \
    /* arrows */ tailToken, headToken
