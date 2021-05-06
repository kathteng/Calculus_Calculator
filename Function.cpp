#include "Function.h"

char Function::variable;

Function::Term::Term()
{
	coefficient = 0;
	varIndex = 0;
	power = 0;
	powerSignIndex = 0;
	hasVariable = true;
}
Function::Term::Term(std::string term_)
{
	term = term_;
	hasVariable = true;
	FindCoefficient();
	FindPower();
}
void Function::Term::FindCoefficient()
{
	FindVariable(term);
	varIndex = term.find(variable);
	// If term is a constant, the whole term is a coefficient
	if (varIndex == std::string::npos)
	{
		hasVariable = false;
		coefficient = stoi(term);
	}
	else if (varIndex == 0)
		coefficient = 1;
	else
		coefficient = stoi(term.substr(0, varIndex));
}
void Function::Term::FindPower()
{
	powerSignIndex = term.find('^');
	if (powerSignIndex == std::string::npos)
	{
		if (hasVariable == false)
			power = 0;
		else
			power = 1;
	}
	else
		power = stoi(term.substr(powerSignIndex + 1, term.length() - powerSignIndex + 1));
}

Function::Function()
{
	numTerms = 0;
	variable = 'x';
}
Function::Function(std::string function_)
{
	function = function_;
	SeparateTerms();
	FindVariable(function);
}
void Function::SeparateTerms()
{
	numTerms = 0;
	int startIndex = 0;
	int endIndex;
	std::string tempTerm;
	while (startIndex < function.length())
	{
		endIndex = function.find_first_of("+-", startIndex);
		if (endIndex != std::string::npos)
		{
			tempTerm = function.substr(startIndex, endIndex - startIndex - 1);
			Term t(tempTerm);
			terms.push_back(t);
			numTerms++;
			startIndex = endIndex + 2; // Plus 2 to account for the space after +/-
		}
		else if (endIndex == std::string::npos)
		{
			tempTerm = function.substr(startIndex, function.length() - startIndex);
			Term t(tempTerm);
			terms.push_back(t);
			numTerms++;
			break;
		}
	}
}
void Function::FindVariable(std::string equation)
{
	for (unsigned int i = 0; i < equation.length(); i++)
	{
		if (isalpha(equation[i]))
		{
			variable = equation[i];
			break;
		}
	}
}
void Function::UpdateTerms()
{
	for (unsigned int i = 0; i < terms.size(); i++)
	{
		if (terms[i].hasVariable == true)
		{
			if (terms[i].varIndex == 0)
			{
				terms[i].term.insert(0, std::to_string(terms[i].coefficient));
				terms[i].powerSignIndex = terms[i].term.find('^');
			}
			else
			{
				terms[i].term.replace(0, terms[i].varIndex, std::to_string(terms[i].coefficient));
				terms[i].powerSignIndex = terms[i].term.find('^');
			}
			
			if (terms[i].power == 0)
			{
				if (terms[i].varIndex == 0)
					terms[i].term.replace(0, std::string::npos, "1");
				else
					terms[i].term.erase(terms[i].varIndex, std::string::npos);
			}
			else if (terms[i].power == 1)
				terms[i].term.erase(terms[i].powerSignIndex, std::string::npos);
			else
				terms[i].term.replace(terms[i].powerSignIndex + 1, terms[i].term.length() - terms[i].powerSignIndex, std::to_string(terms[i].power));
		}
	}
}
void Function::UpdateFunction()
{
	UpdateTerms();
	if (numTerms == 1)
	{
		if (terms[0].term.length() == 0)
			function = "0";
		else
			function = terms[0].term;
	}
	else
	{
		int startIndex = 0;
		int index = 0;
		unsigned int i = 0;
		while (startIndex < function.length() && i < terms.size())
		{
			if (terms[i].term.length() == 0)
			{
				function.erase(index, std::string::npos);
				break;
			}
			index = function.find_first_of("+-", startIndex);
			function.replace(startIndex, index - startIndex - 1, terms[i].term);
			index = function.find_first_of("+-", startIndex);
			startIndex = index + 2;
			i++;
		}
	}
}