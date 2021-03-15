#include "AST/ConstantValue.hpp"

// VER.Heart-Under-Blade
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col, const char *v_const, short int c_type)
    : ExpressionNode{line, col}, value(v_const), ConstType(c_type) {}