#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

int lastRegister = 1;
int lastLabel = 0;

// Trata o caso de variável no lado direito.
// Devemos retornar o valor não, o endereço.
int idRhs(nodeType *p, int reg) {
    if (p->type == typeId) {
        printf("\tLOAD r%d, r%d\n", reg - 1, lastRegister++);
        return lastRegister;
    }
    return reg;
}

int ex(nodeType *p) {
    int leftRegister, rightRegister, tempReg;
  
    if (!p) return 0;

    switch(p->type) {
        case typeCon:
            printf("\tLOADI %d, r%d\n", p->con.value, lastRegister++);
            return lastRegister;
            break;
        case typeId:
            printf("\tLOADI @%c, r%d\n", p->id.i + 'a', lastRegister++);
            return lastRegister;
            break;
        case typeOpr:
            switch(p->opr.oper) {
                case WHILE:
                    ;
                    printf("L%d:\n", lastLabel);
                    
                    int startWhileLabel = lastLabel + 1;
                    int endWhileLabel  = startWhileLabel + 1;
                    // lastLabel = endWhileLabel + 1;
                    lastLabel++;
                    tempReg = ex(p->opr.op[0]);
                    
                    printf("\tCBR r%d, L%d, L%d\n", tempReg - 1, startWhileLabel, endWhileLabel);
                    
                    printf("L%d:\n", startWhileLabel);
                    ex(p->opr.op[1]);

                    printf("\tJUMPI L%d\n", lastLabel);
                    printf("L%d:\n", endWhileLabel);

                    break;
                case IF:
                    tempReg = ex(p->opr.op[0]);

                    int thenLabel = lastLabel + 1;
                    int elseLabel  = thenLabel + 1;    
                    int endIfLabel = elseLabel + 1;
                    
                    if (p->opr.nops > 2) {
                        /* if else */
                        printf("\tCBR r%d, L%d, L%d\n", tempReg - 1, thenLabel, elseLabel);
                        printf("L%d:\n", thenLabel);
                        ex(p->opr.op[1]);
                        printf("\tJUMPI L%d\n", endIfLabel);
                        printf("L%d:\n", elseLabel);
                        ex(p->opr.op[2]);
                        printf("L%d:\n", endIfLabel);        
                    } else {
                        /* if */
                        printf("\tCBR r%d, L%d, L%d\n", tempReg - 1, thenLabel, endIfLabel);
                        printf("L%d:\n", thenLabel);
                        ex(p->opr.op[1]);             
                        printf("L%d:\n", endIfLabel);    
                    }      
                    lastLabel = endIfLabel + 1;
                    break;
                case PRINT:
                    printf("\tLOADI 1, rsys\n");
                    tempReg =  ex(p->opr.op[0]);
                    tempReg = idRhs(p->opr.op[0], tempReg);
                    printf("\tCALL_SYS r%d\n", tempReg - 1);
                    

                    break;
                case '=': 
                    leftRegister = ex(p->opr.op[0]);
                    rightRegister = ex(p->opr.op[1]);

                    rightRegister = idRhs(p->opr.op[1], rightRegister);
                    
                    printf("\tSTORE r%d, r%d\n", rightRegister - 1, leftRegister - 1);
                    break;
                case UMINUS:
                    tempReg = ex(p->opr.op[0]);
                    tempReg = idRhs(p->opr.op[0], tempReg);
                    printf("\tLOADI 0, r%d\n", lastRegister);
                    printf("\tSUB r%d, r%d, r%d\n", lastRegister, tempReg - 1, lastRegister + 1);
                    lastRegister++;
                    return lastRegister;
                    break;
                default:
                    leftRegister = ex(p->opr.op[0]);
                    rightRegister = ex(p->opr.op[1]);
                    switch(p->opr.oper) {
                        case '+':
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tADD r%d, r%d, r%d\n", rightRegister - 1, leftRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case '-': 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tSUB r%d, r%d, r%d\n", rightRegister - 1, leftRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case '*': 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tMULT r%d, r%d, r%d\n", rightRegister - 1, leftRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case '/': 
                           leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tDIV r%d, r%d, r%d\n", rightRegister - 1, leftRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case '<': 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_LT r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case '>': 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_GT r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case GE: 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_GE r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case LE: 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_LE r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case NE: 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_NE r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                        case EQ: 
                            leftRegister = idRhs(p->opr.op[0], leftRegister);
                            rightRegister = idRhs(p->opr.op[1], rightRegister);
                            printf("\tCMP_EQ r%d, r%d, r%d\n", leftRegister - 1, rightRegister - 1, lastRegister++);
                            return lastRegister;
                            break;
                    }
            }
    }
    return 0;
}
