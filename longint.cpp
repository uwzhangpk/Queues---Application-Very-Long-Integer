/*
* -------------------------------------------------------
* Copyright (c) 2019, Pengkun Zhang
* All rights reserved.
* 
* FileName：longint.cpp
* Description：cpp for very long integer
* History：
* 3/20/2019         Pengkun Zhang               
* -------------------------------------------------------
*/
#include "longint.h"
LongInt::LongInt() {
	negative = false;
	digits.clear();
}

LongInt::LongInt(const string str)
{
	digits.clear();

	// check for sign 
	int i = 0;
	if (str[0] == '-')
	{
		negative = true;
		i++;
		while (i < str.length())
		{
			// ASCII for '0' is 48
			// if str[i] is '1' which is 49, 
			// so when str[i] greater than 48('0'), and less than 57('9')
			//add the str[i] to back of digits
			if (str[i] >= 0 + '0' && str[i] <= 9 + '0')
				digits.addBack(str[i]);

			i++;
		}
	}
	else {
		i = 0;
		negative = false;

		while (i < str.length())
		{			
			if (str[i] >= 48 && str[i] <= 57)
				digits.addBack(str[i]);

			i++;
		}
	}
} // end of constructor
LongInt::LongInt(const LongInt & rhs)
{	
	digits.clear();
	negative = rhs.negative;
	digits = rhs.digits;
}


LongInt::~LongInt()
{
	digits.clear();
	
}
#include "longint.h"


LongInt LongInt::operator+(const LongInt & rhs) const
{
	LongInt tmpRhs;
	tmpRhs.operator=(rhs);
	LongInt result;
	LongInt tmpLhs;
	tmpLhs.operator=(*this);
	int carry = 0;
	//make size equal
	if (tmpLhs.digits.size() > tmpRhs.digits.size()) {
		for (int i = 0; i < digits.size() - tmpRhs.digits.size();i++) {
			tmpRhs.digits.addFront(0);
		}
	}
	else if (tmpLhs.digits.size() < tmpRhs.digits.size()) {
		for (int i = 0; i < tmpRhs.digits.size() - digits.size();i++) {
			tmpLhs.digits.addFront(0);
		}
	}

	if (tmpLhs.negative == false && tmpRhs.negative == false) {

		//positive lhs + positive rhs
		//use this formula below

		while (tmpRhs.digits.size() != 0) {
			char aTmp = tmpLhs.digits.removeBack();
			int a = aTmp - '0';
			char bTmp = tmpRhs.digits.removeBack();
			int b = bTmp - '0';
			int resultTmp1 = (a + b + carry) / 10;		//ans[i] = (lhs[i] + rhs[i] + carry) % 10;
			carry = (a + b + carry) % 10;				//carry = (lhs[i] + rhs[i] + carry) / 10;
			char resultTmp = (char)resultTmp1;
			//make the sum of back from lhs and rhs into the front of result
			result.digits.addFront(resultTmp);
		}

		result.remove0s();
		return result;
	}
	else if (tmpLhs.negative == false && tmpRhs.negative == true) {
		//if lhs is positive, rhs is negative
		//we call lhs - |rhs|
		tmpRhs.negative = false;
		result = tmpLhs.operator-(tmpRhs);

		result.remove0s();
		return result;

	}

	else if (tmpLhs.negative == true && tmpRhs.negative == false) {
		//if lhs is negative, rhs is positive
		// return rhs-|lhs|
		tmpLhs.negative = false;
		result = tmpRhs.operator-(tmpLhs);

		result.remove0s();
		return result;
	}
	else if (tmpLhs.negative == true && tmpRhs.negative == true) {
		//if they are both negative
		//we reutn -(lhs+rhs)

		tmpRhs.negative = false;
		tmpLhs.negative = false;

		result = tmpRhs.operator+(tmpLhs);
		result.negative = !result.negative;

		result.remove0s();
		return result;
	}

	else
		cerr << "something wrong with the operator +";
}

LongInt LongInt::operator-(const LongInt & rhs) const
{
	LongInt tmpRhs;
	tmpRhs.operator=(rhs);
	LongInt result;
	LongInt tmpLhs;
	tmpLhs.operator=(*this);

	int borrow = 0;
	if (digits.size() > rhs.digits.size()) {
		for (int i = 0; i < digits.size() - rhs.digits.size();i++) {
			tmpRhs.digits.addFront('0');
		}
	}
	else if (digits.size() < rhs.digits.size()) {
		for (int i = 0; i < rhs.digits.size() - digits.size();i++) {
			tmpLhs.digits.addFront('0');
		}
	}

	
	
	if (tmpLhs.negative == false && tmpRhs.negative == false) {
		//lhs is postive, rhs is positive
		//use formulas below to get answer
		while (tmpRhs.digits.size() != 0) {
			char aTmp = tmpLhs.digits.removeBack();
			int a = aTmp - '0';
			char bTmp = tmpRhs.digits.removeBack();
			int b = bTmp - '0';
			int diff = 0;

			diff = a - b - borrow;				//result[i] = lhs[i] - rhs[i] - borrow
			borrow = 0;							//reset borrow = 0
			if (diff < 0) {						//if result < 0, we make result+10
				diff += 10;						//then borrow is set to 1 for the next loop
				borrow = 1;						
			}
			char diffTmp = (char)diff;
			result.digits.addFront(diffTmp);
		}
		if (borrow == 1) {
			//if borrow still not be 0, meaning this should be a negative number
			//we will need to invert each digit in the result
			//for example 4 into 6, 8 into 2
			//and change the sign
			LongInt resultTmp;
			resultTmp.negative = !result.negative;

			while (result.digits.size() != 0) {
				char tmp = tmpLhs.digits.removeBack();
				int tmpNum = tmp - '0';
				tmpNum = 10 - tmpNum;
				tmp = (char)tmpNum;
				resultTmp.digits.addFront(tmp);
			}

			resultTmp.remove0s();
			return resultTmp;
		}
		//borrow = 0;
		else {
			result.remove0s();
			return result;
		}

	}
	else if (tmpLhs.negative == false && tmpRhs.negative == true) {
		//if lhs is negative, rhs is positive
		//we call (lhs + |rhs|)
		tmpRhs.negative = false;
		result = tmpRhs.operator+(tmpLhs);


		result.remove0s();
		return result;
	}

	else if (tmpLhs.negative == true && tmpRhs.negative == false) {
		//if lhs is negative, rhs is positive
		//we return -(lhs+rhs)
		tmpLhs.negative = false;

		LongInt result = tmpLhs.operator+(tmpRhs);
		result.negative = !result.negative;

		result.remove0s();
		return result;
	}

	else if (tmpLhs.negative == true && tmpRhs.negative == true) {
		//if lhs is negative(-|lhs|), rhs is negative(-|rhs|)
		//we return -(|lhs| - |rhs|)
		tmpLhs.negative = false;
		tmpRhs.negative = false;
		LongInt result = tmpLhs.operator-(tmpRhs);
		result.negative = !result.negative;

		result.remove0s();
		return result;
	}
	else
		cerr << "operator - has errors";
}


const LongInt & LongInt::operator=(const LongInt & rhs)
{
	negative = rhs.negative;
	Deque<char> tmpRhs = rhs.digits;
	while (tmpRhs.size() != 0) {
		digits.addFront(tmpRhs.removeBack());
	}

	return *this;
}

bool LongInt::operator<(const LongInt & rhs) const
{

	if (*this == rhs)                   // Lhs == Rhs
		return false;
	else if (!negative && rhs.negative) // Lhs > -Rhs
		return false;
	else if (negative && !rhs.negative) // -LHS < Rhs
		return true;
	else if (negative && rhs.negative || !negative && !rhs.negative)                          // when both signs are same
	{
		if (negative == false)        // when they are both positive
		{
			if (digits.size() < rhs.digits.size())
				return true;
			else if (digits.size() > rhs.digits.size())
				return false;
			else if (digits.size() == rhs.digits.size()) {			//if lhs - rhs >0
				LongInt tmpLhs = *this;								// lhs > rhs, vice versa
				LongInt tmpRhs = rhs;
				LongInt result = tmpLhs.operator-(tmpRhs);
				if (result.negative)
					return true;
				else
					return false;

			}
		}
		else if (negative == true)                                // when they are both negative
		{
			if (digits.size() < rhs.digits.size())
				return false;
			else if (digits.size() > rhs.digits.size())
				return true;
			else if (digits.size() == rhs.digits.size()) {		//if lhs - rhs >0
				LongInt tmpLhs = *this;							// lhs > rhs, vice versa
				LongInt tmpRhs = rhs;
				LongInt result = tmpLhs.operator-(tmpRhs);
				if (result.negative)
					return true;
				else
					return false;

			}
		}
		

	}
	else
		cerr << "these two variables cant be compared (operator<)";
}

bool LongInt::operator<=(const LongInt & rhs) const
{
	bool result = false;
	LongInt tmpLhs = *this;
	LongInt tmpRhs = rhs;

	if (tmpLhs.operator==(rhs))                   // Lhs == Rhs
		return true;
	else {
		
		LongInt tmpRhs = rhs;
		result = tmpLhs.operator<(tmpRhs);

		return result;
	
	}
	cerr << "these two variables cant be compared (operator<=)";
}

bool LongInt::operator>(const LongInt & rhs) const
{
	if (*this == rhs)                   // Lhs == Rhs
		return true;
	else if (!negative && rhs.negative) // Lhs > -Rhs
		return true;
	else if (negative && !rhs.negative) // -LHS < Rhs
		return false;
	else                                  // when both signs are same
	{
		if (negative == false)        // when they are both positive
		{
			if (digits.size() < rhs.digits.size())
				return false;
			else if (digits.size() > rhs.digits.size())
				return true;
			else if (digits.size() == rhs.digits.size()) {			//if lhs - rhs >0
				LongInt tmpLhs = *this;								// lhs > rhs, vice versa
				LongInt tmpRhs = rhs;
				LongInt result = tmpLhs.operator-(tmpRhs);
				if (result.negative)
					return false;
				else
					return true;

			}
		}
		else if (negative == true)                                // when they are both negative
		{
			if (digits.size() < rhs.digits.size())
				return true;
			else if (digits.size() > rhs.digits.size())
				return false;
			else if (digits.size() == rhs.digits.size()) {		//if lhs - rhs >0
				LongInt tmpLhs = *this;							// lhs > rhs, vice versa
				LongInt tmpRhs = rhs;
				LongInt result = tmpLhs.operator-(tmpRhs);
				if (result.negative)
					return false;
				else
					return true;

			}
		}
		else
			cerr << "these two variables cant be compared(operator>)";
	}
	
}

bool LongInt::operator>=(const LongInt & rhs) const
{
	bool result = false;
	LongInt tmpLhs = *this;
	LongInt tmpRhs = rhs;

	if (tmpLhs.operator==(rhs))
		return true;
	else {
		LongInt tmpLhs = *this;
		LongInt tmpRhs = rhs;
		result = tmpLhs.operator>(tmpRhs);

		return result;

	}

}

bool LongInt::operator==(const LongInt & rhs) const
{
	
	
	if (digits.size() != rhs.digits.size()) {	//if not same size
		return false;
	}
	else if (negative && !rhs.negative || !negative && rhs.negative) // if not same sign
		return false;
	else {
		Deque<char> tmpLhs = digits;
		Deque<char> tmpRhs = rhs.digits;

		while (tmpLhs.size() != 0) {
			if (tmpLhs.removeBack() != tmpRhs.removeBack()) {		//if a single char not equal
				return false;										//then return equal is false
			}
		}

		return true;
	}       		
	
}

bool LongInt::operator!=(const LongInt & rhs) const
{
	bool result;
	LongInt tmpLhs = *this;
	LongInt tmpRhs = rhs;

	if (tmpLhs.operator==(tmpRhs))                   // Lhs == Rhs
		return false;
	else
		return true;
}

void LongInt::remove0s()
{
	bool inValid = false;
	Deque<char> tmp = digits;
	int digit = tmp.size();
	int position = 0;
	while (tmp.size() != 0) {
		char tmpChar = tmp.removeBack();
		int tmpNum = tmpChar - '0';
		if (tmpNum == 0) {
			inValid = true;
			position = digit;
		}
		else if (tmpNum != 0) {
			inValid = false;
		}
		digit--;
	}

	if (inValid == true) {
		for (int i = 0; i < position;i++) {
			char willBeDestroyed = digits.removeFront();
		}

	}
}

istream & operator >> (istream & in, LongInt & rhs)
{
	rhs.digits.clear();
	rhs.negative = false;
	char tmp;
	in.get(tmp);
	if (tmp == '-') {
		rhs.negative = true;
	}
	else if(tmp >= 0 + '0' && tmp <= 9 + '0')
		rhs.digits.addBack(tmp);
	
	while (in.get(tmp)) {
		if (tmp >= 0 + '0' && tmp <= 9 + '0') {
			rhs.digits.addBack(tmp);
		}

	}
		
		
	return in;
	
}

ostream & operator<<(ostream & out, const LongInt & rhs)
{
	if (rhs.digits.isEmpty()) {
		out << "The LongInt is empty";
		return out;
	}
	else {
		LongInt tmp = rhs;
		if (tmp.negative) {
			out << "-";
		}
		while (tmp.digits.size() != 0) {
			out << tmp.digits.removeBack();
		}
		return out;
	}



}
