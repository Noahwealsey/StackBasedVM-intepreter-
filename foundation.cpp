#include <iostream>
#include <cassert>
#define STACK_MAX 256

enum ValueType{
  INT_VAL,
  STRING_VAL,
  DOUBLE_VAL
};

struct Value{
    ValueType value;
    union{
        int intval;
        char* stringval;
        double douval;
    };
};

struct VM{
    int stackPointer;
    Value stack[STACK_MAX];
};

void push(VM* vm, Value &val){
   if(vm->stackPointer < STACK_MAX){
        vm->stack[vm->stackPointer++] = val;
   }
}

Value pop(VM *vm){
    assert(vm->stackPointer != 0 && "Stack is empty ");
    return vm->stack[--vm->stackPointer];
}

typedef enum {
    OP_PUSH_INT,
    OP_PUSH_FLOAT,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_PRINT,
    OP_HALT
} OpCode;

void run(VM* vm, uint8_t* bytecode, int length){
    int ip = 0;
    while(ip < length){
       OpCode op = static_cast<OpCode>(bytecode[ip++]);
       switch(op){
           case OP_PUSH_INT: {
                int value = static_cast<OpCode>(bytecode[ip++]);
                Value val = {INT_VAL, .intval = value};
                push(vm , val);
                break;
            }
           case OP_ADD:{
                Value a = pop(vm);
                Value b = pop(vm);
                Value val = {INT_VAL, .intval = a.intval + b.intval};
                push(vm, val);
                break;
            }
            case OP_PRINT:{
                Value out = pop(vm);
               // i still have to figure this out 
                break;
            }

        
       }
    }
}

int main(){
   OpCode bytcode[STACK_MAX] = [ 
        OP_PUSH_INT , 4,
        OP_PUSH_INT , 3,
        OP_ADD,
        OP_PRINT
    ]
    
    return 0;
}
