/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

// #include "globals.h"
#include "util.h"
#include "stdio.h"
#include <sstream>

/* Procedure printToken prints a token
 * and its lexeme to the listing file
 */
char *printToken(TokenType token, const char *tokenString) {
  std::stringstream ss;
  switch (token) {
  case IF:
  case ELSE:
  case REPEAT:
  case UNTIL:
  case READ:
  case FOR:
  case TO:
  case DOWNTO:
  case ENDDO:
  case REG:
  case DO:
  case WRITE:
    ss << "reserved word: " << tokenString;
    fprintf(listing, "reserved word: %s\n", tokenString);
    break;
  case ASSIGN:
    ss << ":=";
    fprintf(listing, ":=\n");
    break;
  /* 比较运算符 */
  case LT:
    ss << "<";
    fprintf(listing, "<\n");
    break;
  case LTE:
    ss << "<=";
    fprintf(listing, "<=\n");
    break;
  case GT:
    ss << ">";
    fprintf(listing, ">\n");
    break;
  case GTE:
    ss << ">=";
    fprintf(listing, ">=\n");
    break;
  case EQ:
    ss << "=";
    fprintf(listing, "=\n");
    break;
  case NEQ:
    ss << "<>";
    fprintf(listing, "<>\n");
    break;
  /* 分隔符 */
  case LPAREN:
    ss << "(";
    fprintf(listing, "(\n");
    break;
  case RPAREN:
    ss << ")";
    fprintf(listing, ")\n");
    break;
  case SEMI:
    ss << ";";
    fprintf(listing, ";\n");
    break;
  /* 运算符 */
  case PLUS:
    ss << "+";
    fprintf(listing, "+\n");
    break;
  case MINUS:
    ss << "-";
    fprintf(listing, "-\n");
    break;
  case TIMES:
    ss << "*";
    fprintf(listing, "*\n");
    break;
  case OVER:
    ss << "/";
    fprintf(listing, "/\n");
    break;
  case PLUS_EQ:
    ss << "+=";
    fprintf(listing, "+=\n");
    break;
  case REMAIN:
    ss << "%";
    fprintf(listing, "%%\n");
    break;
  case POWER:
    ss << "^";
    fprintf(listing, "^\n");
    break;
  /* 正则操作符 */
  case UNION:
    ss << "|";
    fprintf(listing, "|\n");
    break;
  case CONCAT:
    ss << "&";
    fprintf(listing, "&\n");
    break;
  case CLOSURE:
    ss << "#";
    fprintf(listing, "#\n");
    break;
  case OPTION:
    ss << "?";
    fprintf(listing, "?\n");
    break;
    /* 位运算 */
  case AND:
    ss << "and";
    fprintf(listing, "and\n");
    break;
  case OR:
    ss << "or";
    fprintf(listing, "or\n");
    break;
  case NOT:
    ss << "not";
    fprintf(listing, "not\n");
    break;

  case ENDFILE:
    ss << "EOF";
    fprintf(listing, "EOF\n");
    break;
  case NUM:
    ss << "NUM, val= " << tokenString;
    fprintf(listing, "NUM, val= %s\n", tokenString);
    break;
  case ID:
    ss << "ID, name= " << tokenString;
    fprintf(listing, "ID, name= %s\n", tokenString);
    break;
  case ERROR:
    ss << "ERROR: " << tokenString;
    fprintf(listing, "ERROR: %s\n", tokenString);
    break;
  default: /* should never happen */
    ss << "Unknown token: " << token;
    fprintf(listing, "Unknown token: %d\n", token);
  }
  return copyString(ss.str().data());
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode *newStmtNode(StmtKind kind) {
  TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
  int i;
  if (t == NULL)
    fprintf(listing, "Out of memory error at line %d\n", lineno);
  else {
    for (i = 0; i < MAXCHILDREN; i++)
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression
 * node for syntax tree construction
 */
TreeNode *newExpNode(ExpKind kind) {
  TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
  int i;
  if (t == NULL)
    fprintf(listing, "Out of memory error at line %d\n", lineno);
  else {
    for (i = 0; i < MAXCHILDREN; i++)
      t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char *copyString(char *s) {
  int n;
  char *t;
  if (s == NULL)
    return NULL;
  n = strlen(s) + 1;
  t = (char *)malloc(n);
  if (t == NULL)
    fprintf(listing, "Out of memory error at line %d\n", lineno);
  else
    strcpy(t, s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/* printSpaces indents by printing spaces */
static void printSpaces(void) {
  int i;
  for (i = 0; i < indentno; i++)
    fprintf(listing, " ");
}

/* procedure printTree prints a syntax tree to the
 * listing file using indentation to indicate subtrees
 */
void printTree(TreeNode *tree) {
  int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind == StmtK) {
      switch (tree->kind.stmt) {
      case IfK:
        fprintf(listing, "If\n");
        break;
      case RepeatK:
        fprintf(listing, "Repeat\n");
        break;
      case AssignK:
        fprintf(listing, "Assign to: %s\n", tree->attr.name);
        break;
      case ReadK:
        fprintf(listing, "Read: %s\n", tree->attr.name);
        break;
      case WriteK:
        fprintf(listing, "Write\n");
        break;
      case ForK:
        fprintf(listing, "For: %s\n", tree->attr.name);
        break;
      case PlusEqK:
        fprintf(listing, "PlusEqual: %s\n", tree->attr.name);
        break;
      case RegK:
        fprintf(listing, "RegExp\n");
        break;
      default:
        fprintf(listing, "Unknown ExpNode kind\n");
        break;
      }
    } else if (tree->nodekind == ExpK) {
      switch (tree->kind.exp) {
      case OpK:
        fprintf(listing, "Op: ");
        printToken(tree->attr.op, "\0");
        break;
      case ConstK:
        fprintf(listing, "Const: %d\n", tree->attr.val);
        break;
      case IdK:
        fprintf(listing, "Id: %s\n", tree->attr.name);
        break;
      default:
        fprintf(listing, "Unknown ExpNode kind\n");
        break;
      }
    } else
      fprintf(listing, "Unknown node kind\n");
    for (i = 0; i < MAXCHILDREN; i++)
      printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}

const char *getTreeNodeInfo(TreeNode *tree) {
  listing = stdout;
  std::stringstream ss;
  if (tree->nodekind == StmtK) {
    switch (tree->kind.stmt) {
    case IfK:
      ss << "If";
      break;
    case RepeatK:
      ss << "Repeat";
      break;
    case AssignK:
      ss << "Assign to: " << tree->attr.name;
      break;
    case ReadK:
      ss << "Read: " << tree->attr.name;
      break;
    case WriteK:
      ss << "Write";
      break;
    case ForK:
      ss << "For: " << tree->attr.name;
      break;
    case PlusEqK:
      ss << "PlusEqual: " << tree->attr.name;
      break;
    case RegK:
      ss << "RegExp";
      break;
    default:
      ss << "Unknown ExpNode kind";
    }
  } else if (tree->nodekind == ExpK) {
    switch (tree->kind.exp) {
    case OpK:
      ss << "Op: " << printToken(tree->attr.op, "\0");
      break;
    case ConstK:
      ss << "Const: " << tree->attr.val;
      break;
    case IdK:
      ss << "Id: " << tree->attr.name;
      break;
    default:
      ss << "Unknown ExpNode kind";
    }
  }
  char *info = ss.str().data();
  return copyString(info);
}
