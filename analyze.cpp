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

TreeNode* analyzeCode(const char *sourcePath, const char *errPath) {
  reset();
  TreeNode *syntaxTree;
  source = fopen(sourcePath, "r");
  //    listing = fopen(resPath, "w"); /* send listing to screen */
  listing = fopen(errPath, "w"); /* send listing to screen */
                                 //  listing = stdout;
  if (source == NULL) {
    fprintf(stderr, "File %s not found\n", sourcePath);
    exit(1);
  }
  syntaxTree = parse();
  fclose(source);
  fclose(listing);
//  if (TraceParse)
//    printTree(syntaxTree);
  return syntaxTree;
}
