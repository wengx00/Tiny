#include "parse.h"
#include "util.h"
#include <stdio.h>

/* allocate global variables */
FILE *source;
FILE *listing;
FILE *code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = TRUE;

int Error = FALSE;

void analyzeCode(const char *sourcePath, const char *resPath) {
    reset();
    TreeNode *syntaxTree;
    source = fopen(sourcePath, "r");
    listing = fopen(resPath, "w"); /* send listing to screen */
                                   //  listing = stdout;
    if (source == NULL) {
      fprintf(stderr, "File %s not found\n", sourcePath);
      exit(1);
  }
//  fprintf(listing, "\nTINY COMPILATION: %s\n", sourcePath);
  syntaxTree = parse();
  if (TraceParse) {
    fprintf(listing, "\nSyntax tree:\n");
    printTree(syntaxTree);
  }
  fclose(source);
  fclose(listing);
}
