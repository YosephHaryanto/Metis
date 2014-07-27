#pragma once

#include <collection.h>
#include <vector>

#include "Point.h"
namespace MetisDll
{
	/// <summary>
	/// The lagrange
	/// </summary>
	static class Lagrange
	{
	private:
		int modInverse(int a, int MOD);

		template <class T>
		std::vector<T> zeros(int length);
		template <class T>
		Platform::Collections::Vector<T>^ zerosV(int length);

		std::vector<double> addition(std::vector<double> poly1, std::vector<double> poly2);
		std::vector<double> PointToVector(Point p);

		std::vector<double> multiply(std::vector<double> poly1, std::vector<double> poly2);

		std::vector<double> multiply(double c, std::vector<double> poly);

		double denominator(int i, std::vector<Point> points);
			
		int gcd(int a, int b);
		/// <summary>
		/// Count the least common multiple of two number
		/// </summary>
		/// <param name="a">First number</param>
		/// <param name="b">Second number</param>
		/// <returns>Least common multiple</returns>
		int lcm(int a, int b){ return a*b / gcd(a, b); }
		double maxDenominator(std::vector<Point> points);

		std::vector<double> interpolation_polynomial(int i, std::vector<Point> points);
		public :
		Platform::Collections::Vector<int>^ CountCoefficient(std::vector<Point> points);

	}lagrange;

}