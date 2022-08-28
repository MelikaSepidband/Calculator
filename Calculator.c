#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void getInput(char * in) {
 fgets(in, 256, stdin);
}

int isLeftParantheses(char p) {
if (p == '(') return 1;
else return 0;
}

int isRightParantheses(char p) {
if (p == ')') return 1;
else return 0;
}

int isOperator(char p) {
if (p == '+' || p == '-' || p == '*' || p == '/' || p == '%' || p == '^' ) return p;
else return 0;
}
int performOperator(int a, int b, char p) {
 switch(p) {
    case '+': return a+b;
    case '-': return a-b;
    case '*': return a*b;
    case '/':
        if (b == 0) { printf("Can't divide by 0.\n"); exit(1); }
        return a/b;
    case '^': return pow(a,b);
    case '%': return a%b;
    default:
       puts("Bad value in switch.\n");
       break;
 }
return 0;
 }

char isDigit(char p) {
if (p >= '0' && p <= '9') return 1;
else return 0;
}

int charToDigit(char p) {
if (p >= '0' && p <= '9') return p - '0';
else return 0;
}

int isNumber(char * p) {
while(*p) {
    if (!isDigit(*p)) return 0;
    p++;
}
return 1;
}

int len(char * p)
{
 return (int) strlen(p);
}
int numOfOperands(char * p) {
int total = 0;
while(*p) {
    if (isOperator(*p)) total++;
    p++;
}
return total+1;
}
int isPGRoup(char *p)
{
for(; *p; p++) 
{
    if (!isDigit(*p) && *p != '^') return 0;
    }
return 1;
}
int isMDGRoup(char *p)
{

for(; *p; p++) 
{
    if (!isDigit(*p) && *p != '*' && *p != '/' && *p != '%') return 0;
    }
return 1;
}
int getLeftOperand(char * p, char * l) {
int i = 0;
if (isPGRoup(p))
{
    while(1) {
        if (*p == '^') break;
        l[i++] = *p++;
    }
    return i;	
}

if (isMDGRoup(p)) {
    while(1) {
        if (*p == '*' || *p == '/' || *p == '%') break;
        l[i++] = *p++;
    }
    return i;
    }

if(isLeftParantheses(*p)) {
    int LeftParantheses = 1;
    int RightParantheses= 0;
    p++;
    while(1) {
        if (isLeftParantheses(*p))  LeftParantheses++;
        if (isRightParantheses(*p)) RightParantheses++;

        if (isRightParantheses(*p) && LeftParantheses == RightParantheses)
            break;
        l[i++] = *p++;
    }
    l[i] = '\0';
    return i+2;
}

while (1) {
    if (!isDigit(*p)) break;
    l[i++] = *p++;
}
l[i] = '\0';
return i;
}

int getOperator(char * p, int index, char * op) {
*op = p[index];
return index + 1;
}

int getRightOperand(char * p, char * l) {
while(*p && (isDigit(*p) || isOperator(*p) ||
             isLeftParantheses(*p) || isRightParantheses(*p))) {
    *l++ = *p++;
}
*l = '\0';

return 0;
}

int isEmpty(char * p) {

if (len(p) == 0) return 1;
else return 0;
}

int calcExpression(char * p) {

if (isNumber(p)) return atoi(p);

char leftOperand[256] = ""; char rightOperand[256]= "";
char op;

int leftOpIndex   = getLeftOperand(p, leftOperand);
int operatorIndex = getOperator(p, leftOpIndex, &op);
int rightOpIndex  = getRightOperand(p+operatorIndex, rightOperand);

if (isEmpty(rightOperand)) return calcExpression(leftOperand);

return performOperator(
    calcExpression(leftOperand),
    calcExpression(rightOperand),
    op
);
}

int main()
{
char in[256];
while(1) {
    getInput(in);
    if (strncmp(in, "quit", 4) == 0) break;
    int result = calcExpression(in);
    printf("%d\n", result);
}
}
