struct Word {
   char* letters;
   char unique[5];
   int counts[5];
   char* hint1;
   char* hint2;
} word;  


Word dictionary[30] = {
    {(char*)"frame", {'f','r', 'a', 'm', 'e'}, {1,1,1,1,1}, (char*)"activation ___", (char*)"helpful pointer"},
    {(char*)"stack", {'s', 't', 'a', 'c', 'k'}, {1,1,1,1,1}, (char*)"push and pop", (char*)"computer storage"},
    {(char*)"addiu", {'a','d', 'i', 'u', '!'}, {1,2,1,1,0}, (char*)"unsigned add", (char*)"(in MIPS)"},
    {(char*)"array", {'a', 'r', 'y', '!', '!'}, {2,2,1,0,0}, (char*)"instantiate", (char*)"with brackets"},
    {(char*)"fault", {'f','a', 'u', 'l', 't'}, {1,1,1,1,1}, (char*)"segmentation", (char*)"bad memory"},
    
    {(char*)"heaps", {'h','e', 'a', 'p', 's'}, {1,1,1,1,1}, (char*)"storage", (char*)"by coder"},
    {(char*)"bytes", {'b','y', 't', 'e', 's'}, {1,1,1,1,1}, (char*)"binary groups", (char*)"4 bits"}, 
    {(char*)"input", {'i','n', 'p', 'u', 't'}, {1,1,1,1,1}, (char*)"with function call", (char*)"goes into function"}, 
    {(char*)"error", {'e','r', 'o', '!', '!'}, {1,3,1,0,0}, (char*)"code fail", (char*)"stops running"}, 
    {(char*)"jumps", {'j','u', 'm', 'p', 's'}, {1,1,1,1,1}, (char*)"moves", (char*)"to different line"}, 

    {(char*)"types", {'t','y', 'p', 'e', 's'}, {1,1,1,1,1}, (char*)  "describes value", (char*) "in C."},
    {(char*)"alloc", {'a', 'l', 'o', 'c', '!'}, {1,2,1,1,0}, (char*) "reserves space", (char*) "in MIPs"},
    {(char*)"shift", {'s','h', 'i', 'f', 't'}, {1,1,1,1,1}, (char*)  "moves bits over", (char*) "left or right"},
    {(char*)"loops", {'l', 'o', 'p', 's', 'x'}, {1,2,1,1,0}, (char*) "runs many times", (char*) ""},
    {(char*)"while", {'w','h', 'i', 'l', 'e'}, {1,1,1,1,1}, (char*)  "continues until", (char*) "condition false"},

    {(char*)"short", {'s','h', 'o', 'r', 't'}, {1,1,1,1,1}, (char*)  "ends before ", (char*) "checking all"},
    {(char*)"break", {'b', 'r', 'e', 'a', 'k'}, {1,1,1,1,1}, (char*) "stops running", (char*) "loop early"},
    {(char*)"print", {'p','r', 'i', 'n', 't'}, {1,1,1,1,1}, (char*)  "writes it to", (char*) "console"},
    {(char*)"local", {'l', 'o', 'c', 'a', '!'}, {2,1,1,1,0}, (char*) "within a lower", (char*) "scope"},
    {(char*)"index", {'i','n', 'd', 'e', 'x'}, {1,1,1,1,1}, (char*)  "location in an", (char*) "array"},

    {(char*)"label", {'l','a', 'b', 'e', '!'}, {2,1,1,1,0}, (char*)  "where code", (char*) "jumps to."},
    {(char*)"align", {'a', 'l', 'i', 'g', 'n'}, {1,1,1,1,1}, (char*) "how memory stores", (char*) "values"},
    {(char*)"chars", {'c','h', 'a', 'r', 's'}, {1,1,1,1,1}, (char*)  "data type for", (char*) "letters"},
    {(char*)"slack", {'s', 'l', 'a', 'c', 'k'}, {1,1,1,1,1}, (char*) "empty memory spots", (char*) "for align"},
    {(char*)"sizes", {'s','i', 'z', 'e', '!'}, {2,1,1,1,0}, (char*)  "xxxxx", (char*) "xxxxx"},

    {(char*)"point", {'p','o', 'i', 'n', 't'}, {1,1,1,1,1}, (char*)  "references a var", (char*) "address"},
    {(char*)"refer", {'r', 'e', 'f', '!', '!'}, {2,2,1,0,0}, (char*) "points to memory", (char*) ""},
    {(char*)"files", {'f','i', 'l', 'e', 's'}, {1,1,1,1,1}, (char*)  "MIPs storage", (char*) "holds numbers"},
    {(char*)"nodes", {'n', 'o', 'd', 'e', 's'}, {1,1,1,1,1}, (char*) "holds data and", (char*) "points to nodes."},
    {(char*)"frees", {'f','r', 'e', 's', '!'}, {1,1,2,1,0}, (char*)  "removes heap", (char*) "memory"}
    };
    