#include "fns.h"
#include <cassert>
#include <iostream>

class Temp {
public:
  Temp(): value(0) {}
  ~Temp() { assert(value == 0); }

  operator Param() { return value; }

private:
  Register value;
};

void Move(Param p0, Param p1)
{
  p1 += p0;
  p0 = 0;
}

void SubtractFrom(Param p0, Param p1)
{
  if(p0 < p1) {
    p1 -= p0;
    p0 = 0;
  } else {
    p0 -= p1;
    p1 = 0;
  }
}

void Duplicate(Param p0, Param p1, Param p2)
{
  p1 += p0;
  p2 += p0;
  p0 = 0;
}

void Set(Param p0, Param p1)
{
  assert(p1 == 0);
  if(p0 != 0) {
    p1 = 1;
    p0 = 0;
  }
}

void True(Param p0)
{
  if(p0 > 0)
    p0 = 1;
}

void One(Param p0)
{
  p0++;
}

void Two(Param p0)
{
  p0 += 2;
}

void Three(Param p0)
{
  p0 += 3;
}

void Not(Param p0)
{
  assert(p0 == 0 || p0 == 1);
  p0 = !p0;
}

void Add(Param p0, Param p1, Param p2)
{
  p2 += p0 + p1;
  p0 = 0;
  p1 = 0;
}

void Zero(Param p0)
{
  p0 = 0;
}

void Copy(Param p0, Param p1)
{
  p1 += p0;
}

void Replace(Param p0, Param p1)
{
  p1 = p0;
}

void MoveReplace(Param p0, Param p1)
{
  p1 = p0;
  p0 = 0;
}

void FixedAdd(Param p0, Param p1, Param p2)
{
  p2 += p0 + p1;
}

void Mult(Param p0, Param p1, Param p2)
{
  p2 += p0 * p1;
  p0 = 0;
  p1 = 0;
}

void FixMult(Param p0, Param p1, Param p2)
{
  p2 += p0 * p1;
}

void Mod(Param p0, Param p1, Param p2, Param p3)
{
  assert(p2 == 0 && p3 == 0);
  p2 = p0 / p1;
  p3 = p0 % p1;
  p0 = 0;
  p1 = 0;
}

void FixMod(Param p0, Param p1, Param p2, Param p3)
{
  assert(p2 == 0 && p3 == 0);
  p2 = p0 / p1;
  p3 = p0 % p1;
}

void IsPrime(Param p0, Param p1)
{
  assert(p1 == 0);
  Temp temp0, temp1;
  One(temp0);
  Two(temp1);
  while(temp0)
    IsNotMultipleOfAndIncrement(p0, temp1, temp0);
  IsEqual(p0, temp1, p1);
  Zero(temp1);
}

void IsGreater(Param p0, Param p1, Param p2)
{
  assert(p2 == 0);
  p2 = (p0 > p1);
}

void IsEqual(Param p0, Param p1, Param p2)
{
  assert(p2 == 0);
  p2 = (p0 == p1);
}

void IsNotMultipleOfAndIncrement(Param p0, Param p1, Param p2)
{
  assert(p2 == 1);
  Temp temp0, temp1, temp2;
  Zero(p2);
  FixMod(p0, p1, temp0, p2);
  Zero(temp0);
  True(p2);
  Copy(p2, temp2);
  Move(temp2, p1);
}

void NextPrime(Param p0)
{
  Temp temp0;
  One(temp0);
  while(temp0)
    IsPrimeAndIncrement(p0, temp0);
}

void IsPrimeAndIncrement(Param p0, Param p1)
{
  assert(p1 == 1);
  Move(p1, p0);
  IsPrime(p0, p1);
  Not(p1);
}

void SimplifyFraction(Param p0)
{
  Temp temp0, temp1, temp2, temp3;
  Copy(p0, temp0);
  One(temp1);
  Two(temp2);
  Three(temp3);
  while(temp1)
    SimplifyAndIncrementPrimes(p0, temp0, temp2, temp3, temp1);
  Zero(temp0);
  Zero(temp2);
  Zero(temp3);
}

void SimplifyAndIncrementPrimes(Param p0, Param p1, Param p2, Param p3, Param p4)
{
  Temp temp0, temp1, temp2, temp3;
  Zero(p4);
  FixMult(p2, p3, temp0);
  FixMod(p1, temp0, temp1, temp2);
  True(temp2);
  if(temp2)
    ClearOfAndIncrementPrimes(p1, p2, p3);
  Not(temp2);
  if(temp2)
    CopyToAndDivideBy(temp1, p1, p0, temp0);
  One(temp3);
  IsGreater(p1, temp3, p4);

  Zero(temp0);
  Zero(temp1);
  Zero(temp2);
  Zero(temp3);
}

void ClearOfAndIncrementPrimes(Param p0, Param p1, Param p2)
{
  ClearDivisor(p0, p1);
  ClearDivisor(p0, p2);
  IncrementPrimes(p1, p2);
}

void IncrementPrimes(Param p0, Param p1)
{
  NextPrime(p1);
  Replace(p1, p0);
  NextPrime(p1);
}

void CopyToAndDivideBy(Param p0, Param p1, Param p2, Param p3)
{
  Temp temp0, temp1;
  MoveReplace(p0, p1);
  Mod(p2, p3, temp0, temp1);
  MoveReplace(temp0, p2);
}

void ClearDivisor(Param p0, Param p1)
{
  Temp temp0;
  One(temp0);
  while(temp0)
    ClearSingleDivisor(p0, p1, temp0);
}

void ClearSingleDivisor(Param p0, Param p1, Param p2)
{
  assert(p2 == 1);
  Temp temp0;

  Zero(p2);
  FixMod(p0, p1, temp0, p2);
  True(p2);
  Not(p2);
  if(p2)
    MoveReplace(temp0, p0);
  Zero(temp0);
}

void IsInteger(Param p0, Param p1)
{
  Temp temp0, temp1, temp2, temp3;
  Copy(p0, temp0);
  One(temp1);
  Two(temp2);
  Three(temp3);
  while(temp1)
    IsIntegerAndIncrementPrimes(p0, temp0, temp2, temp3, p1, temp1);
  Zero(temp0);
  Zero(temp2);
  Zero(temp3);
}

void IsIntegerAndIncrementPrimes(Param p0, Param p1, Param p2, Param p3, Param p4, Param p5)
{
  Temp temp0, temp1;
  Zero(p4);
  Zero(p5);
  FixMod(p1, p3, temp0, p4);
  True(p4); // p4 == 0 if it's not an integer, 1 if we don't know yet
  ClearDivisor(p1, p2);
  Zero(temp0);
  One(temp0);
  IsGreater(p1, temp0, temp1);
  FixMult(p4, temp1, p5);
  Zero(temp0);
  Zero(temp1);
  IncrementPrimes(p2, p3);
}

// p0 p1 0 -> p0/p1^a p1 a, where p1^a is the highest power of p1 dividing p0
void IntegerLog(Param p0, Param p1, Param p2)
{
  assert(p2 == 0);
  Temp temp0;
  One(temp0);
  while(temp0)
    DivideByAndIncrement(p0, p1, p2, temp0);
}

// p0 p1 p2 1 -> p0/p1 p1 p2+1 1 if p1 divides p0
//               p0 p1 p2 0 otherwise
void DivideByAndIncrement(Param p0, Param p1, Param p2, Param p3)
{
  assert(p3 == 1);
  Temp temp0;
  Zero(p3);
  FixMod(p0, p1, temp0, p3);
  True(p3);
  Not(p3);
  if(p3)
    MoveReplace(temp0, p0);
  Zero(temp0);
  Copy(p3, p2);
}

// p0 p1 -> p0 (output), where p0 is an encoded program and p1 is the encoded input
void Interpret(Param p0, Param p1)
{
  Temp temp0;
  One(temp0);
  while(temp0)
    InterpretOnce(p0, p1, temp0);
}

// p0 p1 1 -> p0 (output) 0/1, depending on whether the program halted or not (0 == halt)
void InterpretOnce(Param p0, Param p1, Param p2)
{
  assert(p2 == 1);
  Temp temp0, temp1, temp2;
  Copy(p0, temp0);
  One(temp1);
  Two(temp2);
  while(temp1)
    InterpretSingleFraction(temp0, p1, temp2, p2, temp1);
  Zero(temp0);
  Zero(temp2);
}

// p0 p1 p2 1 1 ->
//  (program cut down by prime p2)
//  (product with fraction if integer)
//  (next prime)
//  0/1: 0 if p0 == 1 (it was the last fraction/prime dividing it)
//  0/1: 0 if the result is an integer
void InterpretSingleFraction(Param p0, Param p1, Param p2, Param p3, Param p4)
{
  assert(p3 == 1);
  assert(p4 == 1);
  Temp temp0, temp1;
  IntegerLog(p0, p2, temp0);
  Copy(temp0, temp1);
  True(temp1);
  Replace(temp1, p3);
  Replace(temp1, p4);
  if(temp1)
    InterpretGivenFraction(temp0, p1, p4);
  if(p4)
    NextPrime(p2);
  Zero(temp0);
  Zero(temp1);
}

// p0 p1 1 -> p0 (p0*p1 if it's an integer) 0/1 (0 if it's an integer)
void InterpretGivenFraction(Param p0, Param p1, Param p2)
{
  assert(p2 == 1);
  Temp temp0;
  Zero(p2);
  FixMult(p0, p1, temp0);
  SimplifyFraction(temp0);
  IsInteger(temp0, p2);
  if(p2)
    MoveReplace(temp0, p1);
  Not(p2);
  Zero(temp0);
}
