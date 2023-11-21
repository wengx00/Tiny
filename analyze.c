#include "parse.h"
#include "util.h"
#include <stdio.h>

/* allocate global variables */
int lineno = 0;
char *sourcePath = "TinySourceCode";
char *resPath = "TinyResult";

FILE *source;
FILE *listing;
FILE *code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;

int Error = FALSE;

void analyzeCode() {
  TreeNode *syntaxTree;
  source = fopen(sourcePath, "r");
  if (source == NULL) {
    fprintf(stderr, "File %s not found\n", sourcePath);
    exit(1);
  }
  listing = fopen(resPath, "w"); /* send listing to screen */
  fprintf(listing, "\nTINY COMPILATION: %s\n", sourcePath);
  syntaxTree = parse();
  if (TraceParse) {
    fprintf(listing, "\nSyntax tree:\n");
    printTree(syntaxTree);
  }
  fclose(source);
  fclose(listing);
}
