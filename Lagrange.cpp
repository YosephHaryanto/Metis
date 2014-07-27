#include "pch.h"
#include "Lagrange.h"

using namespace MetisDll;
using namespace Platform::Collections;
using namespace std;

/// <summary>
/// Fermat's Little Theorem Implementation on finding modular inverse
/// </summary>
/// <param name="a">a</param>
/// <param name="b">b.</param>
/// <param name="MOD">mod</param>
/// <returns></returns>
int Lagrange::modInverse(int a, int MOD)
{
	int x = 1, y = a, b = MOD -2;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x*y);
			if (x>MOD) x %= MOD;
		}
		y = (y*y);
		if (y>MOD) y %= MOD;
		b /= 2;
	}
	return x;
}

/// <summary>
/// Zeroses the specified length.
/// </summary>
/// <param name="length">The length.</param>
/// <returns></returns>
template <class T>
vector<T> Lagrange::zeros(int length)
{
	std::vector<T> result;
	for (int i = 0; i < length; i++)
		result.push_back(0);
	return result;
}

/// <summary>
/// Zeroses the v.
/// </summary>
/// <param name="length">The length.</param>
/// <returns></returns>
template <class T>
Vector<T>^ Lagrange::zerosV(int length)
{
	Vector<T>^ result = ref new Vector<T>();
	for (int i = 0; i < length; i++)
		result->Append(0);
	return result;
}

/// <summary>
/// Additions the specified poly1.
/// </summary>
/// <param name="poly1">The poly1.</param>
/// <param name="poly2">The poly2.</param>
/// <returns></returns>
vector<double> Lagrange::addition(vector<double> poly1, vector<double> poly2)
{
	if (poly2.size() > poly1.size())
	{
		vector<double> temp = poly1;
		poly1 = poly2;
		poly2 = temp;
	}
	for (int i = 0; i < poly2.size(); i++)
		poly1[i] += poly2[i];
	return poly1;
}

/// <summary>
/// Points to vector.
/// </summary>
/// <param name="p">The p.</param>
/// <returns></returns>
vector<double> Lagrange::PointToVector(Point p)
{
	vector<double> result = zeros<double>(2);
	result[0] = 0 - p.x;
	result[1] = 1;
	return result;
}

/// <summary>
/// Multiplies the specified poly1.
/// </summary>
/// <param name="poly1">The poly1.</param>
/// <param name="poly2">The poly2.</param>
/// <returns></returns>
vector<double> Lagrange::multiply(vector<double> poly1, vector<double> poly2)
{
	vector<double> result = zeros<double>(poly1.size() + poly2.size() -1);
	for (int i = 0; i < poly1.size(); i++)
	{
		for (int j = 0; j < poly2.size(); j++)
			result[i + j] += poly1[i]*poly2[j];
	}
	return result;
}

/// <summary>
/// Multiplies the specified c.
/// </summary>
/// <param name="c">The c.</param>
/// <param name="poly">The poly.</param>
/// <returns></returns>
vector<double> Lagrange::multiply(double c, vector<double> poly)
{
	for (int i = 0; i < poly.size(); i++)
	{
		poly[i] *= c;
	}
	return poly;
}

/// <summary>
/// Denominators the specified i.
/// </summary>
/// <param name="i">The i.</param>
/// <param name="points">The points.</param>
/// <returns></returns>
double Lagrange::denominator(int i, std::vector<Point> points) {
	double result = 1;
	double x_i = points[i].x;
	for (int j = points.size() - 1; j >= 0; j--) 
	{
		if (i != j) {
			result *= x_i - points[j].x;
		}
	}
	return result;
}

 /// <summary>
 /// Find the greatest common divisor between two number
 /// </summary>
 /// <param name="a">First number</param>
 /// <param name="b">Second number</param>
 /// <returns>Greatest common divisor</returns>
 int Lagrange::gcd(int a, int b)
 {
	 if (a < 0) 
		 a = -a;
	 if (b < 0)
		b = -b;
	 if (a < b)
	 {
		 int temp = a; a = b; b = temp;
	 }
	 return a % b == 0 ? b : gcd(b, a % b);
 }


 /// <summary>
 /// Calculate the maximum number of denominator given points
 /// </summary>
 /// <param name="points">Points.</param>
 /// <returns></returns>
 double Lagrange::maxDenominator(vector<Point> points)
 {
	 double resultMax = 1;
	 for (int i = 0; i < points.size(); i++)
	 {
		 double result = 1;
		 double x_i = points[i].x;
		 for (int j = points.size() - 1; j >= 0; j--)
		 {
			 if (i != j) {
				 result *= x_i - points[j].x;
			 }
		 }
		 
		 resultMax = lcm(resultMax, result);
	 }
	 return resultMax;
 }

 /// <summary>
 /// Calculate the value of Pk for spesific x in the lagrange interpolation
 /// </summary>
 /// <param name="i">x</param>
 /// <param name="points">Point in form of ( x, f(x) )</param>
 /// <returns>List of coeeficient</returns>
 vector<double> Lagrange::interpolation_polynomial(int x, vector<Point> points) {
	vector<double> coefficients= zeros<double>(points.size());
	bool first = true;
	for (int j = 0; j < points.size(); j++)
	{
		if (x == j)
			continue;
		if (first)
		{
			first = false;
			coefficients = addition(coefficients, PointToVector(points[j]));
			continue;
		}
		coefficients = multiply(coefficients, PointToVector(points[j]));
	}
	return coefficients;
}

 /// <summary>
 /// Counts the total coeeficient of given points.
 /// </summary>
 /// <param name="points">Points in (x, f(x) )</param>
 /// <returns>List of coefficient</returns>
 Vector<int>^ Lagrange::CountCoefficient(std::vector<Point> points)
 {
	 Vector<int>^ polynomial = zerosV<int>(points.size());
	 vector<double> coefficients = zeros<double>(points.size());
	 int md = maxDenominator(points);
	 for (int i = 0; i < points.size(); ++i)
	 {
		 coefficients = addition
			 (coefficients,
			 multiply(points[i].y * md/ denominator(i,points) , 
			 (interpolation_polynomial(i, points)))
			 );

	 }
	 int mdMod = md < 0 ? -md : md;
	 int x = modInverse(mdMod, 251);
	 x = md < 0 ? -x : x;
	 for (int i = 0; i < polynomial->Size; i++)
	 {

		 coefficients[i] *= x;
		 coefficients[i] = (int)coefficients[i] % 251;
		 if (coefficients[i] < 0)
			 coefficients[i] += 251;
		 polynomial->SetAt(i, (int)coefficients[i]);
	 }
	 return polynomial;
 }