#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include <inttypes.h>


#include "spvm_compiler.h"
#include "spvm_array.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_my_var.h"
#include "spvm_var.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_name_info.h"
#include "spvm_type.h"
#include "spvm_bytecode_builder.h"
#include "spvm_op_checker.h"
#include "spvm_switch_info.h"
#include "spvm_descriptor.h"
#include "spvm_compiler_allocator.h"
#include "spvm_limit.h"
#include "spvm_extention.h"
#include "spvm_extention_bind.h"

const char* const SPVM_OP_C_CODE_NAMES[] = {
  "IF",
  "ELSIF",
  "ELSE",
  "FOR",
  "WHILE",
  "NULL",
  "LIST",
  "PUSHMARK",
  "GRAMMAR",
  "NAME",
  "PACKAGE",
  "MY_VAR",
  "MY_VAR_INIT",
  "FIELD",
  "SUB",
  "ENUM",
  "DESCRIPTOR",
  "ENUMERATION_VALUE",
  "BLOCK",
  "ENUM_BLOCK",
  "CLASS_BLOCK",
  "TYPE",
  "CONSTANT",
  "PRE_INC",
  "POST_INC",
  "PRE_DEC",
  "POST_DEC",
  "COMPLEMENT",
  "NEGATE",
  "PLUS",
  "EQ",
  "NE",
  "LT",
  "LE",
  "GT",
  "GE",
  "ADD",
  "SUBTRACT",
  "MULTIPLY",
  "DIVIDE",
  "BIT_AND",
  "BIT_OR",
  "BIT_XOR",
  "BIT_NOT",
  "REMAINDER",
  "LEFT_SHIFT",
  "RIGHT_SHIFT",
  "RIGHT_SHIFT_UNSIGNED",
  "AND",
  "OR",
  "NOT",
  "ARRAY_ELEM",
  "ASSIGN",
  "CALL_SUB",
  "CALL_FIELD",
  "USE",
  "RETURN",
  "LAST",
  "NEXT",
  "LOOP",
  "VAR",
  "CONVERT",
  "POP",
  "UNDEF",
  "MALLOC",
  "ARRAY_LENGTH",
  "CONDITION",
  "DIE",
  "SWITCH",
  "CASE",
  "DEFAULT",
  "SWITCH_CONDITION",
  "VOID",
  "TRY",
  "CATCH",
  "DEC_REF_COUNT",
  "INC_REF_COUNT",
  "FORMAL_ARGS",
  "BLOCK_END",
  "RETURN_PROCESS",
  "LEAVE_SCOPE",
  "DIE_PROCESS",
  "STORE",
  "LAST_PROCESS",
  "NEXT_PROCESS",
};

SPVM_OP* SPVM_OP_new_op_use_from_package_name(SPVM_COMPILER* compiler, const char* package_name, const char* file, int32_t line) {

  SPVM_OP* op_name_package = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, package_name, 1);
  op_name_package->uv.name = package_name;
  SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_USE, package_name, 1);
  SPVM_OP_sibling_splice(compiler, op_use, NULL, 0, op_name_package);
  
  return op_use;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_INT;
  constant->uv.long_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
  constant->type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_LONG;
  constant->uv.long_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "long", strlen("long"));
  constant->type = SPVM_HASH_search(compiler->type_symtable, "long", strlen("long"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_FLOAT;
  constant->uv.float_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "float", strlen("float"));
  constant->type = SPVM_HASH_search(compiler->type_symtable, "float", strlen("float"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_DOUBLE;
  constant->uv.double_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "double", strlen("double"));
  constant->type = SPVM_HASH_search(compiler->type_symtable, "double", strlen("double"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_var_from_op_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var) {
  (void)compiler;
  
  SPVM_VAR* var = SPVM_VAR_new(compiler);
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_my_var->file, op_my_var->line);
  
  SPVM_MY_VAR* my_var = op_my_var->uv.my_var;
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_my_var->file, op_my_var->line);
  op_name->uv.name = my_var->op_name->uv.name;
  var->op_name = op_name;
  var->op_my_var = op_my_var;
  op_var->uv.var = var;
  
  return op_var;
}

SPVM_OP* SPVM_OP_get_op_block_from_op_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub) {
  (void)compiler;
  
  SPVM_OP* op_block = op_sub->last;
  
  if (op_block->code == SPVM_OP_C_CODE_BLOCK) {
    return op_block;
  }
  else {
    return NULL;
  }
}

SPVM_OP* SPVM_OP_build_try_catch(SPVM_COMPILER* compiler, SPVM_OP* op_try, SPVM_OP* op_try_block, SPVM_OP* op_catch, SPVM_OP* op_var, SPVM_OP* op_catch_block) {
  
  // Create op_my_var from op_var
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_var->file, op_var->line);
  op_type->uv.type = SPVM_HASH_search(compiler->type_symtable, "byte[]", strlen("byte[]"));
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_var->file, op_var->line);
  op_name->uv.name = op_var->uv.var->op_name->uv.name;
  my_var->op_name = op_name;
  my_var->op_type = op_type;
  SPVM_OP* op_my_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR, op_var->file, op_var->line);
  op_my_var->uv.my_var = my_var;
  
  // Create op store
  SPVM_OP* op_store = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_STORE, op_var->file, op_var->line);
  SPVM_OP_sibling_splice(compiler, op_store, op_store->last, 0, op_my_var);
  
  // insert var declaration into catch block top
  SPVM_OP_sibling_splice(compiler, op_catch_block->first, op_catch_block->first->first, 0, op_store);
  
  // try block
  op_try_block->flag |= SPVM_OP_C_FLAG_BLOCK_TRY;
  
  // Add block
  SPVM_OP_sibling_splice(compiler, op_try, op_try->last, 0, op_try_block);
  SPVM_OP_sibling_splice(compiler, op_try, op_try->last, 0, op_catch);
  SPVM_OP_sibling_splice(compiler, op_try, op_try->last, 0, op_catch_block);
  
  return op_try;
}

SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_term_condition, SPVM_OP* op_block) {
  
  SPVM_OP* op_switch_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SWITCH_CONDITION, op_term_condition->file, op_term_condition->line);
  SPVM_OP_sibling_splice(compiler, op_switch_condition, op_switch_condition->last, 0, op_term_condition);
  
  SPVM_OP_sibling_splice(compiler, op_switch, op_switch->last, 0, op_switch_condition);
  SPVM_OP_sibling_splice(compiler, op_switch, op_switch->last, 0, op_block);
  
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_SWITCH;
  
  SPVM_SWITCH_INFO* switch_info = SPVM_SWITCH_INFO_new(compiler);
  op_switch->uv.switch_info = switch_info;
  op_switch->uv.switch_info->op_cases = compiler->cur_op_cases;
  
  op_switch_condition->uv.switch_info = switch_info;
  switch_info->op_term_condition = op_term_condition;
  
  compiler->cur_op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return op_switch;
}

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term) {
  
  SPVM_OP_sibling_splice(compiler, op_case, NULL, 0, op_term);
  
  op_term->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  assert(compiler->cur_op_cases->length <= SPVM_LIMIT_C_CASES);
  if (compiler->cur_op_cases->length == SPVM_LIMIT_C_CASES) {
    SPVM_yyerror_format(compiler, "Too many case statements at %s line %d\n", op_case->file, op_case->line);
    return NULL;
  }

  SPVM_ARRAY_push(compiler->cur_op_cases, op_case);
  
  return op_case;
}

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_FOR, SPVM_OP* op_statement_init, SPVM_OP* op_term_condition, SPVM_OP* op_term_next_value, SPVM_OP* op_block) {
  
  // Outer block for initialize loop variable
  SPVM_OP* op_block_outer = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_FOR->file, op_FOR->line);
  SPVM_OP_sibling_splice(compiler, op_block_outer, op_block_outer->last, 0, op_statement_init);
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LOOP, op_FOR->file, op_FOR->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term_condition->file, op_term_condition->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  SPVM_OP_sibling_splice(compiler, op_condition, op_condition->last, 0, op_term_condition);
  
  // Set block flag
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_LOOP;
  
  // Push next value to the last of statements in block
  SPVM_OP* op_statements = op_block->first;
  if (op_term_next_value->code != SPVM_OP_C_CODE_NULL) {
    SPVM_OP_sibling_splice(compiler, op_statements, op_statements->last, 0, op_term_next_value);
  }

  SPVM_OP_sibling_splice(compiler, op_loop, op_loop->last, 0, op_block);
  SPVM_OP_sibling_splice(compiler, op_loop, op_loop->last, 0, op_condition);
  
  SPVM_OP_sibling_splice(compiler, op_block_outer, op_block_outer->last, 0, op_loop);
  
  return op_block_outer;
}

SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_WHILE, SPVM_OP* op_term, SPVM_OP* op_block) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LOOP, op_WHILE->file, op_WHILE->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term->file, op_term->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  SPVM_OP_sibling_splice(compiler, op_condition, op_condition->last, 0, op_term);
  
  // Set block flag
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_LOOP;
  
  SPVM_OP_sibling_splice(compiler, op_loop, op_loop->last, 0, op_block);
  SPVM_OP_sibling_splice(compiler, op_loop, op_loop->last, 0, op_condition);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block_if, SPVM_OP* op_block_else) {
  
  if (op_if->code == SPVM_OP_C_CODE_ELSIF) {
    op_if->code = SPVM_OP_C_CODE_IF;
  }

  if (op_block_if->code != SPVM_OP_C_CODE_BLOCK) {
    SPVM_OP* op_term = op_block_if;
    op_block_if = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_term->file, op_term->line);

    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_term->file, op_term->line);
    SPVM_OP_sibling_splice(compiler, op_list, op_list->first, 0, op_term);

    SPVM_OP_sibling_splice(compiler, op_block_if, NULL, 0, op_list);
  }
  
  if (op_block_else->code == SPVM_OP_C_CODE_IF) {
    SPVM_OP* op_if = op_block_else;
    op_block_else = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_term->file, op_term->line);
    
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_term->file, op_term->line);
    SPVM_OP_sibling_splice(compiler, op_list, op_list->first, 0, op_if);
    
    SPVM_OP_sibling_splice(compiler, op_block_else, NULL, 0, op_list);
  }
  else if (op_block_else->code != SPVM_OP_C_CODE_BLOCK && op_block_else->code != SPVM_OP_C_CODE_NULL) {
    SPVM_OP* op_term = op_block_else;
    op_block_else = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_term->file, op_term->line);
    
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_term->file, op_term->line);
    SPVM_OP_sibling_splice(compiler, op_list, op_list->first, 0, op_term);
    
    SPVM_OP_sibling_splice(compiler, op_block_else, NULL, 0, op_list);
  }
  
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term->file, op_term->line);
  SPVM_OP_sibling_splice(compiler, op_condition, NULL, 0, op_term);
  
  op_block_if->flag |= SPVM_OP_C_FLAG_BLOCK_IF;
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_IF;
  if (op_block_else->code == SPVM_OP_C_CODE_BLOCK) {
    op_block_else->flag |= SPVM_OP_C_FLAG_BLOCK_ELSE;
  }
  
  SPVM_OP_sibling_splice(compiler, op_if, NULL, 0, op_condition);
  SPVM_OP_sibling_splice(compiler, op_if, op_condition, 0, op_block_if);
  SPVM_OP_sibling_splice(compiler, op_if, op_block_if, 0, op_block_else);
  
  if (op_block_else->code == SPVM_OP_C_CODE_BLOCK) {
    op_block_if->flag |= SPVM_OP_C_FLAG_BLOCK_HAS_ELSE;
  }
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term) {
  
  SPVM_OP_sibling_splice(compiler, op_array_length, NULL, 0, op_term);
  
  return op_array_length;
}

SPVM_OP* SPVM_OP_build_malloc_object(SPVM_COMPILER* compiler, SPVM_OP* op_malloc, SPVM_OP* op_type) {
  
  SPVM_OP_sibling_splice(compiler, op_malloc, NULL, 0, op_type);
  
  return op_malloc;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->code) {
    case SPVM_OP_C_CODE_ARRAY_LENGTH:
      type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
      break;
    case SPVM_OP_C_CODE_ARRAY_ELEM: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      type = SPVM_HASH_search(compiler->type_symtable, first_type->name, strlen(first_type->name) - 2);
      break;
    }
    case SPVM_OP_C_CODE_ADD:
    case SPVM_OP_C_CODE_SUBTRACT:
    case SPVM_OP_C_CODE_MULTIPLY:
    case SPVM_OP_C_CODE_DIVIDE:
    case SPVM_OP_C_CODE_REMAINDER:
    case SPVM_OP_C_CODE_PRE_INC:
    case SPVM_OP_C_CODE_POST_INC:
    case SPVM_OP_C_CODE_PRE_DEC:
    case SPVM_OP_C_CODE_POST_DEC:
    case SPVM_OP_C_CODE_LEFT_SHIFT:
    case SPVM_OP_C_CODE_RIGHT_SHIFT:
    case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED:
    case SPVM_OP_C_CODE_BIT_XOR:
    case SPVM_OP_C_CODE_BIT_OR:
    case SPVM_OP_C_CODE_BIT_AND:
    case SPVM_OP_C_CODE_PLUS:
    case SPVM_OP_C_CODE_NEGATE:
    case SPVM_OP_C_CODE_ASSIGN:
    case SPVM_OP_C_CODE_MALLOC:
    {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_CODE_RETURN: {
      if (op->first) {
        type = SPVM_OP_get_type(compiler, op->first);
      }
      break;
    }
    case SPVM_OP_C_CODE_CONVERT: {
      SPVM_OP* op_type = op->last;
      type = SPVM_OP_get_type(compiler, op_type);
      break;
    }
    case SPVM_OP_C_CODE_TYPE: {
      if (op->uv.type) {
        type = op->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_SWITCH_CONDITION : {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_CODE_UNDEF : {
      type = NULL;
      break;
    }
    case SPVM_OP_C_CODE_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_CODE_VAR: {
      SPVM_VAR* var = op->uv.var;
      if (var->op_my_var->uv.my_var->op_type) {
        type = var->op_my_var->uv.my_var->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_MY_VAR: {
      SPVM_MY_VAR* my_var = op->uv.my_var;
      if ( my_var->op_type) {
        type = my_var->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_CALL_SUB: {
      SPVM_NAME_INFO* name_info = op->uv.name_info;
      const char* abs_name = name_info->resolved_name;
      SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, abs_name, strlen(abs_name));
      SPVM_SUB* sub = op_sub->uv.sub;
      if (sub->op_return_type->code != SPVM_OP_C_CODE_VOID) {
        type = sub->op_return_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_CALL_FIELD: {
      SPVM_NAME_INFO* name_info = op->uv.name_info;
      const char* abs_name = name_info->resolved_name;
      SPVM_OP* op_field = SPVM_HASH_search(compiler->op_field_symtable, abs_name, strlen(abs_name));
      SPVM_FIELD* field = op_field->uv.field;
      type = field->op_type->uv.type;
      break;
    }
  }
  
  return type;
}

void SPVM_OP_convert_and_to_if(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  /* before
    AND
      x
      y
  */
  
  /* after 
    IF
      x
      IF
        y
        1
        0
      0
  */
  
  SPVM_OP* op_first = op->first;
  SPVM_OP* op_last = op->last;
  
  // Constant false 1
  SPVM_OP* op_constant_false1 = SPVM_OP_new_op_constant_long(compiler, 0, op->file, op->line);
  
  // Constant false 2
  SPVM_OP* op_constant_false2 = SPVM_OP_new_op_constant_long(compiler, 0, op->file, op->line);
  
  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_long(compiler, 1, op->file, op->line);
  
  // if
  SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op->file, op->line);
  
  // and to if
  op->code = SPVM_OP_C_CODE_IF;
  op->first = NULL;
  
  op_if = SPVM_OP_build_if_statement(compiler, op_if, op_last, op_constant_true, op_constant_false2);
  
  op_first->sibparent = op_if;
  
  op_if->sibparent = op_if;
  
  SPVM_OP_sibling_splice(compiler, op, op_if, 0, op_constant_false1);
}

void SPVM_OP_convert_or_to_if(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  // before
  //  OR
  //    x
  //    y
  
  // after 
  //  IF
  //    x
  //    1
  //    IF
  //      y
  //      1
  //      0
  
  SPVM_OP* op_first = op->first;
  SPVM_OP* op_last = op->last;
  
  // Constant true 1
  SPVM_OP* op_constant_true1 = SPVM_OP_new_op_constant_long(compiler, 1, op->file, op->line);
  
  // Constant true 2
  SPVM_OP* op_constant_true2 = SPVM_OP_new_op_constant_long(compiler, 1, op->file, op->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_long(compiler, 0, op->file, op->line);
  
  // if
  SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op->file, op->line);
  
  // or to if
  op->code = SPVM_OP_C_CODE_IF;
  op->first = NULL;
  
  op_if = SPVM_OP_build_if_statement(compiler, op_if, op_last, op_constant_true2, op_constant_false);
  
  op_first->sibparent = op_constant_true1;
  
  SPVM_OP_sibling_splice(compiler, op, op_constant_true1, 0, op_if);
}

void SPVM_OP_convert_not_to_if(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  // before
  //  NOT
  //    x
  
  // after 
  //  IF
  //    x
  //    0
  //    1
  
  SPVM_OP* op_first = op->first;
  
  // Constant true 1
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_long(compiler, 1, op->file, op->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_long(compiler, 0, op->file, op->line);
  
  // If
  op->code = SPVM_OP_C_CODE_IF;
  op->first = NULL;
  op = SPVM_OP_build_if_statement(compiler, op, op_first, op_constant_false, op_constant_true);
}

void SPVM_OP_resolve_sub_name(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name) {
  
  SPVM_NAME_INFO* name_info = op_name->uv.name_info;
  
  const char* sub_abs_name = NULL;
  if (name_info->code == SPVM_NAME_INFO_C_CODE_VARBASENAME) {
    const char* package_name = name_info->op_var->uv.var->op_my_var->uv.my_var->op_type->uv.type->name;
    const char* sub_name = name_info->op_name->uv.name;
    sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
  }
  else if (name_info->code == SPVM_NAME_INFO_C_CODE_ABSNAME) {
    sub_abs_name = name_info->op_name->uv.name;
  }
  else if (name_info->code == SPVM_NAME_INFO_C_CODE_BASENAME) {
    const char* package_name = op_package->uv.package->op_name->uv.name;
    const char* sub_name = name_info->op_name->uv.name;
    sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
  }
  
  name_info->resolved_name = sub_abs_name;
}

void SPVM_OP_resolve_field_name(SPVM_COMPILER* compiler, SPVM_OP* op_field) {
  
  SPVM_OP* op_term_invoker = op_field->first;
  SPVM_OP* op_name = op_field->last;
  
  SPVM_TYPE* invoker_type = SPVM_OP_get_type(compiler, op_term_invoker);
  const char* package_name = invoker_type->name;
  const char* field_name = op_name->uv.name;
  const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
  
  op_field->uv.name_info->resolved_name = field_abs_name;
}

SPVM_OP* SPVM_OP_build_array_elem(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_term) {
  
  SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ARRAY_ELEM, op_var->file, op_var->line);
  SPVM_OP_sibling_splice(compiler, op_array_elem, NULL, 0, op_var);
  SPVM_OP_sibling_splice(compiler, op_array_elem, op_array_elem->last, 0, op_term);
  
  return op_array_elem;
}

SPVM_OP* SPVM_OP_build_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_name_field) {
  SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_FIELD, op_var->file, op_var->line);
  SPVM_OP_sibling_splice(compiler, op_field, NULL, 0, op_var);
  SPVM_OP_sibling_splice(compiler, op_field, op_var, 0, op_name_field);
  
  SPVM_NAME_INFO* name_info = SPVM_NAME_INFO_new(compiler);
  
  if (strchr(op_name_field->uv.name, ':')) {
    SPVM_yyerror_format(compiler, "field name \"%s\" can't contain :: at %s line %d\n",
      op_name_field, op_name_field->file, op_name_field->line);
  }
  
  name_info->code = SPVM_NAME_INFO_C_CODE_VARBASENAME;
  name_info->op_var = op_var;
  name_info->op_name = op_name_field;
  op_field->uv.name_info = name_info;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term) {
  
  SPVM_OP* op_convert_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONVERT, op_type->file, op_type->line);
  SPVM_OP_sibling_splice(compiler, op_convert_type, NULL, 0, op_term);
  SPVM_OP_sibling_splice(compiler, op_convert_type, op_term, 0, op_type);
  
  op_convert_type->file = op_type->file;
  op_convert_type->line = op_type->line;
  
  return op_convert_type;
}

SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_packages) {
  
  SPVM_OP* op_grammar = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_GRAMMAR, op_packages->file, op_packages->line);
  SPVM_OP_sibling_splice(compiler, op_grammar, NULL, 0, op_packages);
  
  compiler->op_grammar = op_grammar;
  
  // Check types
  SPVM_OP_CHECKER_check(compiler);

  if (compiler->fatal_error) {
    return NULL;
  }
  
  // Create bytecodes
  if (compiler->error_count > 0) {
    return NULL;
  }
  
  SPVM_BYTECODE_BUILDER_build_bytecode_array(compiler);
  
  return op_grammar;
}

const char* SPVM_OP_create_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "%s::%s", package_name, name);
  
  return abs_name;
}

SPVM_OP* SPVM_OP_build_package(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name_package, SPVM_OP* op_block) {
  
  SPVM_OP_sibling_splice(compiler, op_package, NULL, 0, op_name_package);
  SPVM_OP_sibling_splice(compiler, op_package, op_name_package, 0, op_block);
  
  const char* package_name = op_name_package->uv.name;
  SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
  
  // Redeclaration package error
  SPVM_OP* found_op_package = SPVM_HASH_search(op_package_symtable, package_name, strlen(package_name));
  if (found_op_package) {
    SPVM_yyerror_format(compiler, "redeclaration of package \"%s\" at %s line %d\n", package_name, op_package->file, op_package->line);
  }
  else {
    // Package
    SPVM_PACKAGE* package = SPVM_PACKAGE_new(compiler);
    package->op_name = op_name_package;
    
    // Type(type is same as package name)
    SPVM_TYPE* type = SPVM_TYPE_new(compiler);
    type->code = SPVM_TYPE_C_CODE_NAME;
    type->uv.op_name = op_name_package;
    
    // Type OP
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name_package->file, op_name_package->line);
    op_type->uv.type = type;
    
    // Add type
    package->op_type = op_type;
    SPVM_ARRAY_push(compiler->op_types, op_type);
    
    SPVM_ARRAY* op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_ARRAY* op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    // Fields
    SPVM_OP* op_decls = op_block->first;
    SPVM_OP* op_decl = op_decls->first;
    while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
      if (op_decl->code == SPVM_OP_C_CODE_FIELD) {
        SPVM_OP* op_field = op_decl;
        SPVM_FIELD* field = op_field->uv.field;
        const char* field_name = field->op_name->uv.name;
        
        const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
        SPVM_OP* found_op_field = SPVM_HASH_search(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name));
        
        assert(op_fields->length <= SPVM_LIMIT_C_FIELDS);
        
        if (found_op_field) {
          SPVM_yyerror_format(compiler, "redeclaration of field \"%s::%s\" at %s line %d\n", package_name, field_name, op_field->file, op_field->line);
        }
        else if (op_fields->length == SPVM_LIMIT_C_FIELDS) {
          SPVM_yyerror_format(compiler, "too many fields, field \"%s\" ignored at %s line %d\n", field_name, op_field->file, op_field->line);
          compiler->fatal_error = 1;
        }
        else {
          SPVM_ARRAY_push(op_fields, op_field);
          
          const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
          field->abs_name = field_abs_name;
          
          // Add op field symtable
          SPVM_HASH_insert(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name), op_field);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_SUB) {
        SPVM_OP* op_sub = op_decl;
        SPVM_SUB* sub = op_sub->uv.sub;
        
        SPVM_OP* op_name_sub = sub->op_name;
        const char* sub_name = op_name_sub->uv.name;
        const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
        
        SPVM_OP* found_op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name));
        
        assert(op_subs->length <= SPVM_LIMIT_C_SUBS);
        if (found_op_sub) {
          SPVM_yyerror_format(compiler, "Redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, op_sub->file, op_sub->line);
        }
        else if (op_subs->length == SPVM_LIMIT_C_SUBS) {
          SPVM_yyerror_format(compiler, "too many subroutines at %s line %d\n", sub_name, op_sub->file, op_sub->line);
          compiler->fatal_error = 1;
        }
        // Unknown sub
        else {
          // Bind standard functions
          if (sub->is_native) {
            SPVM_EXTENTION_BIND_bind_core_extentions(compiler, sub, sub_abs_name);
          }
          
          sub->abs_name = sub_abs_name;
          
          assert(op_sub->file);
          
          sub->file_name = op_sub->file;
          
          SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
          SPVM_ARRAY_push(op_subs, op_sub);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_ENUM) {
        SPVM_OP* op_enumeration = op_decl;
        SPVM_OP* op_enumeration_block = op_enumeration->first;
        
        // Starting value
        int64_t start_value = 0;
        SPVM_OP* op_enumeration_values = op_enumeration_block->first;
        SPVM_OP* op_enumeration_value = op_enumeration_values->first;
        
        int32_t constant_code = SPVM_CONSTANT_C_CODE_LONG;
        while ((op_enumeration_value = SPVM_OP_sibling(compiler, op_enumeration_value))) {
          SPVM_ENUMERATION_VALUE* enumeration_value = SPVM_ENUMERATION_VALUE_new(compiler);
          enumeration_value->op_name = op_enumeration_value->first;
          if (op_enumeration_value->first != op_enumeration_value->last) {
            enumeration_value->op_constant = op_enumeration_value->last;
          }
          
          SPVM_OP* op_constant;
          if (enumeration_value->op_constant) {
            op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_enumeration_value->file, op_enumeration_value->line);
            op_constant->uv.constant = enumeration_value->op_constant->uv.constant;
            
            if (op_constant->uv.constant->code == SPVM_CONSTANT_C_CODE_INT) {
              constant_code = SPVM_CONSTANT_C_CODE_INT;
            }
            else if (op_constant->uv.constant->code == SPVM_CONSTANT_C_CODE_LONG) {
              constant_code = SPVM_CONSTANT_C_CODE_LONG;
            }
            else {
              assert(0);
            }
            start_value = op_constant->uv.constant->uv.long_value + 1;
          }
          else {
            if (constant_code == SPVM_CONSTANT_C_CODE_INT) {
              op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)start_value, op_enumeration_value->file, op_enumeration_value->line);
            }
            else if (constant_code == SPVM_CONSTANT_C_CODE_LONG) {
              op_constant = SPVM_OP_new_op_constant_long(compiler, start_value, op_enumeration_value->file, op_enumeration_value->line);
            }
            else {
              assert(0);
            }
            enumeration_value->op_constant = op_constant;
            
            start_value++;
          }
          
          // sub
          SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, op_enumeration_value->file, op_enumeration_value->line);
          op_sub->file = op_enumeration_value->file;
          op_sub->line = op_enumeration_value->line;
          
          // Type
          SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_enumeration_value->file, op_enumeration_value->line);
          op_return_type->uv.type = op_constant->uv.constant->type;

          // Name
          SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_enumeration_value->file, op_enumeration_value->line);
          op_name->uv.name = enumeration_value->op_name->uv.name;
          
          // Return
          SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_enumeration_value->file, op_enumeration_value->line);
          SPVM_OP_sibling_splice(compiler, op_return, NULL, 0, op_constant);
          
          // Create sub information
          SPVM_SUB* sub = SPVM_SUB_new(compiler);
          sub->op_name = op_name;
          sub->op_return_type = op_return_type;
          sub->op_block = op_constant;
          sub->is_constant = 1;

          // Create absolute name
          const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, op_name->uv.name);
          sub->abs_name = sub_abs_name;
          sub->file_name = op_enumeration_value->file;
          
          // Set sub
          op_sub->uv.sub = sub;
         
          SPVM_OP* found_op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name));
          
          if (found_op_sub) {
            SPVM_yyerror_format(compiler, "redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, op_sub->file, op_sub->line);
          }
          // Unknown sub
          else {
            SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
            SPVM_ARRAY_push(op_subs, op_sub);
          }
        }
      }
    }
    package->op_fields = op_fields;
    package->op_subs = op_subs;
    
    // Add package
    op_package->uv.package = package;
    SPVM_ARRAY_push(compiler->op_packages, op_package);
    SPVM_HASH_insert(compiler->op_package_symtable, package_name, strlen(package_name), op_package);
  }
  
  return op_package;
}

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_package) {
  
  SPVM_OP_sibling_splice(compiler, op_use, NULL, 0, op_name_package);
  
  const char* package_name = op_name_package->uv.name;
  SPVM_OP* found_op_use = SPVM_HASH_search(compiler->op_use_symtable, package_name, strlen(package_name));
  
  if (!found_op_use) {
    SPVM_ARRAY_push(compiler->op_use_stack, op_use);
    SPVM_HASH_insert(compiler->op_use_symtable, package_name, strlen(package_name), op_use);
  }
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_term) {
  
  // Stab
  SPVM_OP* op_my_var_parent = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR_INIT, op_my_var->file, op_my_var->line);
  
  // Create my var information
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);
  my_var->op_type = op_type;
  
  // Name OP
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_var->file, op_var->line);
  op_name->uv.name = op_var->uv.var->op_name->uv.name;
  my_var->op_name = op_name;

  // Add my_var information to op
  op_my_var->uv.my_var = my_var;
  
  // Add my_var op
  SPVM_OP_sibling_splice(compiler, op_my_var_parent, NULL, 0, op_my_var);
  
  // Assign
  if (op_term) {
    SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_my_var->file, op_my_var->line);
    
    op_var->uv.var->op_my_var = op_my_var;
    
    SPVM_OP_sibling_splice(compiler, op_assign, NULL, 0, op_var);
    SPVM_OP_sibling_splice(compiler, op_assign, op_var, 0, op_term);
    
    SPVM_OP_sibling_splice(compiler, op_my_var_parent, op_my_var, 0, op_assign);
    
    // Type assumption
    my_var->op_term_assumption = op_term;
  }
  
  // Type is none
  if (!op_type && (!op_term || op_term->code == SPVM_OP_C_CODE_UNDEF)) {
    SPVM_yyerror_format(compiler, "\"my %s\" can't detect type at %s line %d\n", my_var->op_name->uv.name, op_my_var->file, op_my_var->line);
  }
  
  return op_my_var_parent;
}

SPVM_OP* SPVM_OP_build_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_type) {
  
  // Build OP
  SPVM_OP_sibling_splice(compiler, op_field, NULL, 0, op_name_field);
  SPVM_OP_sibling_splice(compiler, op_field, op_name_field, 0, op_type);
  
  // Create field information
  SPVM_FIELD* field = SPVM_FIELD_new(compiler);
  
  // Name
  field->op_name = op_name_field;
  
  // Type
  field->op_type = op_type;
  
  // Set field informaiton
  op_field->uv.field = field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_name_sub, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_type_or_void, SPVM_OP* op_block) {
  
  // Build OP_SUB
  SPVM_OP_sibling_splice(compiler, op_sub, NULL, 0, op_name_sub);
  SPVM_OP_sibling_splice(compiler, op_sub, op_name_sub, 0, op_args);
  SPVM_OP_sibling_splice(compiler, op_sub, op_args, 0, op_descriptors);
  SPVM_OP_sibling_splice(compiler, op_sub, op_descriptors, 0, op_type_or_void);
  if (op_block) {
    op_block->flag = SPVM_OP_C_FLAG_BLOCK_SUB;
    SPVM_OP_sibling_splice(compiler, op_sub, op_type_or_void, 0, op_block);
  }
  
  // Create sub information
  SPVM_SUB* sub = SPVM_SUB_new(compiler);
  sub->op_name = op_name_sub;
  
  // Descriptors
  SPVM_OP* op_descriptor = op_descriptors->first;
  while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
    if (op_descriptor->code == SPVM_DESCRIPTOR_C_CODE_NATIVE) {
      sub->is_native = 1;
    }
    else {
      SPVM_yyerror_format(compiler, "invalid descriptor %s", SPVM_DESCRIPTOR_C_CODE_NAMES[op_descriptor->code], op_descriptors->file, op_descriptors->line);
    }
  }
  
  // Native subroutine can't have block
  if (sub->is_native && op_block) {
    SPVM_yyerror_format(compiler, "Native subroutine can't have block", op_block->file, op_block->line);
  }
  
  // subargs
  {
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_ARRAY_push(sub->op_args, op_arg->first);
    }
  }
  
  // Add my declaration to top of block
  if (op_block) {
    SPVM_OP* op_list_statement = op_block->first;
    SPVM_OP* op_formal_args = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_FORMAL_ARGS, op_list_statement->file, op_list_statement->line);
    for (int32_t i = 0; i < sub->op_args->length; i++) {
      SPVM_OP* op_arg = SPVM_ARRAY_fetch(sub->op_args, i);
      SPVM_OP* op_my_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR, op_arg->file, op_arg->line);
      op_my_var->uv.my_var = op_arg->uv.my_var;
      SPVM_OP* op_my_var_parent = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR_INIT, op_arg->file, op_arg->line);
      SPVM_OP_sibling_splice(compiler, op_my_var_parent, op_my_var_parent->last, 0, op_my_var);
      
      SPVM_OP_sibling_splice(compiler, op_formal_args, op_formal_args->first, 0, op_my_var_parent);
    }
    SPVM_OP_sibling_splice(compiler, op_list_statement, op_list_statement->first, 0, op_formal_args);
  }
  
  // return type
  sub->op_return_type = op_type_or_void;
  
  // Save block
  sub->op_block = op_block;

  op_sub->uv.sub = sub;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block) {
  
  // Build OP_SUB
  SPVM_OP_sibling_splice(compiler, op_enumeration, NULL, 0, op_enumeration_block);
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_name_sub, SPVM_OP* op_terms) {
  
  // Build OP_SUB
  SPVM_OP* op_call_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_SUB, op_name_sub->file, op_name_sub->line);
  SPVM_OP_sibling_splice(compiler, op_call_sub, NULL, 0, op_name_sub);
  SPVM_OP_sibling_splice(compiler, op_call_sub, op_name_sub, 0, op_terms);
  
  SPVM_NAME_INFO* name_info = SPVM_NAME_INFO_new(compiler);
  
  const char* sub_name = op_name_sub->uv.name;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_invocant->file, op_invocant->line);
  
  // Normal call
  if (op_invocant->code == SPVM_OP_C_CODE_NULL) {
    // Absolute
    // P::m();
    if (strstr(sub_name, ":")) {
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
    // Base name
    // m();
    else {
      name_info->code = SPVM_NAME_INFO_C_CODE_BASENAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
  }
  // Method call
  else if (op_invocant->code == SPVM_OP_C_CODE_VAR) {
    // Absolute
    // $var->P::m();
    if (strstr(sub_name, ":")) {
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
    // Base name
    // $var->m();
    else {
      name_info->code = SPVM_NAME_INFO_C_CODE_VARBASENAME;
      name_info->op_var = op_invocant;
      name_info->op_name = op_name_sub;
    }
    SPVM_OP_sibling_splice(compiler, op_terms, op_terms->first, 0, op_invocant);
  }
  // Method call
  else if (op_invocant->code == SPVM_OP_C_CODE_NAME) {
    // Absolute
    // P->Q::m;
    if (strstr(sub_name, ":")) {
      SPVM_yyerror_format(compiler, "package name is ambiguas %s line %d\n", op_invocant->file, op_invocant->line);
    }
    // Base name
    else {
      const char* package_name = op_invocant->uv.name;
      const char* name = op_name_sub->uv.name;
      
      // Create abs name
      const char* abs_name = SPVM_OP_create_abs_name(compiler, package_name, name);
      
      // Create op abs name
      SPVM_OP* op_abs_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_invocant->file, op_invocant->line);
      op_abs_name->uv.name = abs_name;
      
      // Set abs name
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      name_info->op_name = op_abs_name;
    }
  }
  
  op_call_sub->uv.name_info = name_info;
  
  return op_call_sub;
}

SPVM_OP* SPVM_OP_build_unop(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_sibling_splice(compiler, op_unary, NULL, 0, op_first);
  
  return op_unary;
}

SPVM_OP* SPVM_OP_build_binop(SPVM_COMPILER* compiler, SPVM_OP* op_bin, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_sibling_splice(compiler, op_bin, NULL, 0, op_first);
  if (op_last) {
    SPVM_OP_sibling_splice(compiler, op_bin, op_first, 0, op_last);
  }
  
  return op_bin;
}

SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  // 
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_NAME;
  type->uv.op_name = op_name;

  SPVM_OP* op_type_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  SPVM_OP_sibling_splice(compiler, op_type_name, NULL, 0, op_name);
  
  op_type_name->uv.type = type;
  op_type_name->file = op_name->file;
  op_type_name->line = op_name->line;

  SPVM_ARRAY_push(compiler->op_types, op_type_name);
  
  return op_type_name;
}

SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_term) {
  
  SPVM_OP* op_sub_end_process = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN_PROCESS, op_return->file, op_return->line);
  
  SPVM_OP* op_leave_scope = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LEAVE_SCOPE, op_return->file, op_return->line);
  
  if (op_term) {
    SPVM_OP_sibling_splice(compiler, op_return, NULL, 0, op_term);
  }
  
  SPVM_OP_sibling_splice(compiler, op_sub_end_process, op_sub_end_process->last, 0, op_leave_scope);
  SPVM_OP_sibling_splice(compiler, op_sub_end_process, op_sub_end_process->last, 0, op_return);
  
  return op_sub_end_process;
}

SPVM_OP* SPVM_OP_build_die(SPVM_COMPILER* compiler, SPVM_OP* op_die, SPVM_OP* op_term) {
  
  SPVM_OP* op_die_process = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_DIE_PROCESS, op_die->file, op_die->line);
  
  SPVM_OP* op_leave_scope = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LEAVE_SCOPE, op_die->file, op_die->line);
  
  if (op_term) {
    SPVM_OP_sibling_splice(compiler, op_die, NULL, 0, op_term);
  }
  
  SPVM_OP_sibling_splice(compiler, op_die_process, op_die_process->last, 0, op_leave_scope);
  SPVM_OP_sibling_splice(compiler, op_die_process, op_die_process->last, 0, op_die);
  
  return op_die_process;
}

SPVM_OP* SPVM_OP_build_last(SPVM_COMPILER* compiler, SPVM_OP* op_last) {
  
  SPVM_OP* op_last_process = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LAST_PROCESS, op_last->file, op_last->line);
  
  SPVM_OP* op_leave_scope = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LEAVE_SCOPE, op_last->file, op_last->line);
  
  SPVM_OP_sibling_splice(compiler, op_last_process, op_last_process->last, 0, op_leave_scope);
  SPVM_OP_sibling_splice(compiler, op_last_process, op_last_process->last, 0, op_last);
  
  return op_last_process;
}

SPVM_OP* SPVM_OP_build_next(SPVM_COMPILER* compiler, SPVM_OP* op_next) {
  
  SPVM_OP* op_next_process = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEXT_PROCESS, op_next->file, op_next->line);
  
  SPVM_OP* op_leave_scope = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LEAVE_SCOPE, op_next->file, op_next->line);
  
  SPVM_OP_sibling_splice(compiler, op_next_process, op_next_process->last, 0, op_leave_scope);
  SPVM_OP_sibling_splice(compiler, op_next_process, op_next_process->last, 0, op_next);
  
  return op_next_process;
}

SPVM_OP* SPVM_OP_build_type_array(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_ARRAY;
  type->uv.op_type = op_type;
  
  // Type OP
  SPVM_OP* op_type_array = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type->file, op_type->line);
  SPVM_OP_sibling_splice(compiler, op_type_array, NULL, 0, op_type);
  
  if (op_term_length) {
    SPVM_OP_sibling_splice(compiler, op_type_array, op_type_array->last, 0, op_term_length);
  }
  else {
    SPVM_OP* op_null = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, op_type->file, op_type->line);
    SPVM_OP_sibling_splice(compiler, op_type_array, op_type_array->last, 0, op_null);
  }
  
  op_type_array->uv.type = type;
  op_type_array->file = op_type->file;
  op_type_array->line = op_type->line;
  
  SPVM_ARRAY_push(compiler->op_types, op_type_array);
  
  return op_type_array;
}

SPVM_OP* SPVM_OP_append_elem(SPVM_COMPILER* compiler, SPVM_OP *first, SPVM_OP *last, const char* file, int32_t line) {
  if (!first) {
    return last;
  }
  
  if (!last) {
    return first;
  }
  
  if (first->code == SPVM_OP_C_CODE_LIST) {
    SPVM_OP_sibling_splice(compiler, first, first->last, 0, last);
    return first;
  }
  else {
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, file, line);
    SPVM_OP_sibling_splice(compiler, op_list, op_list->first, 0, first);
    SPVM_OP_sibling_splice(compiler, op_list, first, 0, last);
    
    return op_list;
  }
}

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  SPVM_OP* op_pushmark = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PUSHMARK, file, line);
  
  SPVM_OP* op_list = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LIST, file, line);
  SPVM_OP_sibling_splice(compiler, op_list, NULL, 0, op_pushmark);
  
  return op_list;
}


SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t code, const char* file, int32_t line) {

  SPVM_OP *op = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_OP));
  
  memset(op, 0, sizeof(SPVM_OP));
  
  op->code = code;
  
  assert(!op->file);
  assert(!op->line);
  
  op->file = file;
  op->line = line;
  
  return op;
}

SPVM_OP* SPVM_OP_sibling_splice(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, int32_t del_count, SPVM_OP* insert) {
  SPVM_OP *first;
  SPVM_OP *rest;
  SPVM_OP *last_del = NULL;
  SPVM_OP *last_ins = NULL;

  if (start) {
    first = SPVM_OP_sibling(compiler, start);
  }
  else if (!parent) {
    goto no_parent;
  }
  else {
    first = parent->first;
  }
  
  if (del_count && first) {
    last_del = first;
    while (--del_count && last_del->moresib)
      last_del = SPVM_OP_sibling(compiler, last_del);
    rest = SPVM_OP_sibling(compiler, last_del);
    SPVM_OP_lastsib_set(compiler, last_del, NULL);
  }
  else {
    rest = first;
  }
  
  if (insert) {
    last_ins = insert;
    while (last_ins->moresib) {
      last_ins = SPVM_OP_sibling(compiler, last_ins);
    }
    SPVM_OP_maybesib_set(compiler, last_ins, rest, NULL);
  }
  else {
    insert = rest;
  }

  if (start) {
    SPVM_OP_maybesib_set(compiler, start, insert, NULL);
  }
  else {
    if (!parent) {
      goto no_parent;
    }
    parent->first = insert;
  }
  
  if (!rest) {
    /* update last etc */
    SPVM_OP *lastop;

    if (!parent) {
      goto no_parent;
    }
    lastop = last_ins ? last_ins : start ? start : NULL;
    parent->last = lastop;

    if (lastop) {
      SPVM_OP_lastsib_set(compiler, lastop, parent);
    }
  }
  return last_del ? first : NULL;

  no_parent:
    fprintf(stderr, "panic: op_sibling_splice(): NULL parent");
    exit(EXIT_FAILURE);
}

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  return op->moresib ? op->sibparent : NULL;
}

void SPVM_OP_moresib_set(SPVM_COMPILER* compiler, SPVM_OP* op, SPVM_OP* sib) {
  (void)compiler;
  
  op->moresib = 1;
  op->sibparent = sib;
}

void SPVM_OP_lastsib_set(SPVM_COMPILER* compiler, SPVM_OP* op, SPVM_OP* parent) {
  (void)compiler;
  op->moresib = 0;
  op->sibparent = parent;
}

void SPVM_OP_maybesib_set(SPVM_COMPILER* compiler, SPVM_OP* op, SPVM_OP* sib, SPVM_OP* parent) {
  (void)compiler;
  op->moresib = sib ? 1 : 0;
  op->sibparent = op->moresib ? sib : parent;
}
