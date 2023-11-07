/*
 	 Calculator.cpp 
   ������, ���������� �� ���������� ���������.
   ������ ��������� ������� � ������� evaluate_expression.
   ��� ������������� ���������� � ���������� � ������� float.
 
   ������ ��������:
      � ������ ������������� ������ ������������� ���������� ���� 
    const char *
*/

#include "stdafx.h"
#include <cmath>
#include <string>

#include "calculator.h"
#include "name_table.h"

// ������ ���������� - �.�. ���������� ���������� �������� ���������
float prim(Parser& parser) {
	parser.get_lexem();

	switch (parser.get_last().type) {
		case LT_Number: {
			const float val = parser.get_last().value;
			parser.get_lexem();
			return val;
		}
		case LT_Identifier: {
			std::string name(parser.get_last().name);
			parser.get_lexem();
			return NT.GetVariable(name);
		}
		case LT_Delimiter:
			switch (parser.get_last().delimiter) {
				case '-':
					return -prim(parser);
				case '(': {
					const float val = evaluate_expression(parser);
					if (parser.get_last().type == LT_Delimiter && parser.get_last().delimiter == ')') {
						parser.get_lexem();
						return val;
					}
					throw R"(')' expected)";
				}
				default: {
					throw "primary expected";
				}
			}
		default: {
			throw "primary expected";
		}
	}
}

// ������������ ��������� � �������
float term(Parser& parser) {
	float left = prim(parser);

	while (true) {
		if (parser.get_last().type == LT_Delimiter) {
			switch (parser.get_last().delimiter) {
				case '*':
					left *= prim(parser);
					break;
				//TODO: ������� ����� �������
				case '^':
					left = pow(left, prim(parser));
					break;
				case '/': {
					constexpr float precision = 1.0e-5f;
                    const float d = prim(parser);
					//TODO: ������� ����
					if (fabs(d) > precision) {
						left /= d;
					} else {
						throw "Divide by zero";
					}
				}
				break;
				default:
					return left;
			}
		} else {
			return left;
		}
	}
}

// ������������ �������� � ���������
float plus_minus(Parser& parser) {
	float left = term(parser);

	while (true) {
		if (parser.get_last().type == LT_Delimiter) {
			switch (parser.get_last().delimiter) {
				case '+':
					left += term(parser);
					break;
				case '-':
					left -= term(parser);
					break;
				default:
					return left;
			}
		} else {
			return left;
		}
	}
}


// ��������� ���������
float evaluate_expression(Parser& parser) {
	float left = plus_minus(parser);

	while (true) {
		if (parser.get_last().type == LT_Delimiter) {
			switch (parser.get_last().delimiter) {
				case '<':
					left = left < plus_minus(parser);
					break;
				case '>':
					left = left > plus_minus(parser);
					break;
				case '=':
					left = left == plus_minus(parser);
					break;
				default:
					return left;
			}
		} else {
			return left;
		}
	}
}
