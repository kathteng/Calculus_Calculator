#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Function
{
	struct Term
	{
		std::string term;
		int coefficient;
		int varIndex;
		int power;
		int powerSignIndex;
		bool hasVariable;

		Term();
		Term(std::string term_);
	private:
		void FindCoefficient();
		void FindPower();
	};
public:
	char variable;
	std::string function;
	int numTerms;
	std::vector<Term> terms;

	Function();
	Function(std::string function_);
	void UpdateTerms();
	void UpdateFunction();
private:
	void SeparateTerms();
	void FindVariable(std::string equation);
};