#include "Condition.h"

Condition::Condition(){
	
}

Condition::Condition(table& t, string op){
	data_table = t;
	operation = op;
}

void Condition::addFirstOperand(Condition* c){
	operand_one_code = CONDITION;
	op_one_cond = c;
}

void Condition::addFirstOperand(string attribute_type){
	operand_one_code = TYPE;
	op_one_type = attribute_type;
}

void Condition::addFirstOperand(attribute a){
	operand_one_code = ATTR;
	op_one_attr = a;
}

void Condition::addSecondOperand(Condition* c){
	operand_two_code = CONDITION;
	op_two_cond = c;
}

void Condition::addSecondOperand(string attribute_type){
	operand_two_code = TYPE;
	op_two_type = attribute_type;
}

void Condition::addSecondOperand(attribute a){
	operand_two_code = ATTR;
	op_two_attr = a;
}

//assumption: operations && and || will only be used on two conditions
//may want to add error handling on this
bool Condition::result(int row_num){
	if(operand_one_code == TYPE){
		int col_index = data_table.getAttributeColumn(op_one_type);
		op_one_attr = data_table.getEntityAt(row_num).getAttribute(col_index);
	}

	if(operand_two_code == TYPE){
		int col_index = data_table.getAttributeColumn(op_two_type);
		op_two_attr = data_table.getEntityAt(row_num).getAttribute(col_index);
	}

	if(operation.compare("&&")){
		return (op_one_cond->result(row_num) && op_two_cond->result(row_num));
	}

	else if(operation.compare("||")){
		return (op_one_cond->result(row_num) || op_two_cond->result(row_num));
	}

	else if(operation.compare("==")){
		return (op_one_attr.get_string_value() == op_two_attr.get_string_value());
	}

	else if(operation.compare("!=")){
		return (op_one_attr.get_string_value() != op_two_attr.get_string_value());
	}

	else if(operation.compare(">")){
		return (op_one_attr.get_string_value() > op_two_attr.get_string_value());
	}

	else if(operation.compare("<")){
		return (op_one_attr.get_string_value() < op_two_attr.get_string_value());
	}

	else if(operation.compare("<=")){
		return (op_one_attr.get_string_value() <= op_two_attr.get_string_value());
	}

	else if(operation.compare(">=")){
		return (op_one_attr.get_string_value() >= op_two_attr.get_string_value());
	}
	return false;
}