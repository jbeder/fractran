#pragma once

typedef unsigned long long Register;
typedef Register& Param;

void Move(Param p0, Param p1);
void SubtractFrom(Param p0, Param p1);
void Duplicate(Param p0, Param p1, Param p2);
void Set(Param p0, Param p1);
void True(Param p0);
void One(Param p0);
void Two(Param p0);
void Three(Param p0);
void Not(Param p0);
void Add(Param p0, Param p1, Param p2);
void Zero(Param p0);
void Copy(Param p0, Param p1);
void Replace(Param p0, Param p1);
void MoveReplace(Param p0, Param p1);
void FixedAdd(Param p0, Param p1, Param p2);
void Mult(Param p0, Param p1, Param p2);
void FixMult(Param p0, Param p1, Param p2);
void Mod(Param p0, Param p1, Param p2, Param p3);
void FixMod(Param p0, Param p1, Param p2, Param p3);
void IsPrime(Param p0, Param p1);
void IsGreater(Param p0, Param p1, Param p2);
void IsEqual(Param p0, Param p1, Param p2);
void IsNotMultipleOfAndIncrement(Param p0, Param p1, Param p2);
void NextPrime(Param p0);
void IsPrimeAndIncrement(Param p0, Param p1);
void SimplifyFraction(Param p0);
void SimplifyAndIncrementPrimes(Param p0, Param p1, Param p2, Param p3,
                                Param p4);
void IncrementPrimes(Param p0, Param p1);
void ClearDivisor(Param p0, Param p1);
void ClearSingleDivisor(Param p0, Param p1, Param p2);
void ClearOfAndIncrementPrimes(Param p0, Param p1, Param p2);
void CopyToAndDivideBy(Param p0, Param p1, Param p2, Param p3);
void IsInteger(Param p0, Param p1);
void IsIntegerAndIncrementPrimes(Param p0, Param p1, Param p2, Param p3,
                                 Param p4, Param p5);
void IntegerLog(Param p0, Param p1, Param p2);
void DivideByAndIncrement(Param p0, Param p1, Param p2, Param p3);
void Interpret(Param p0, Param p1);
void InterpretOnce(Param p0, Param p1, Param p2);
void InterpretSingleFraction(Param p0, Param p1, Param p2, Param p3, Param p4);
void InterpretGivenFraction(Param p0, Param p1, Param p2);
