static const wchar_t graphHead[] = L""
"digraph {\n"
"    rankdir = LR;\n"
"    node [shape = record; style = \"filled\";];\n"
"    splines = ortho;\n"
;

static const wchar_t graphTail[] = L""
"}\n"
;

static const wchar_t graphElemTemplate[] = L""
"    element_%d [label = \"nil| 0x603000000040\"; fillcolor = \"palegreen\"; color = \"green\";];\n"
"    element_%d -> element_%d [style = invis; weight = 100;];\n"
"    element_%d -> element_%d [color = \"coral\";  constraint = false;];\n"
"    element_%d -> element_%d [color = \"indigo\"; constraint = false;];\n"
;

#define GRAPH_ELEM_BODY(token, nextToken, prevToken) graphElemTemplate, token, token, nextToken, token, nextToken, token, prevToken
