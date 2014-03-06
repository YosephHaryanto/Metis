<?xml version="1.0"?><doc>
<members>
<member name="T:MetisDll.Lagrange" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.h" line="9">
<summary>
The lagrange
</summary>
</member>
<member name="M:MetisDll.Lagrange.lcm(System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.h" line="32">
<summary>
Count the least common multiple of two number
</summary>
<param name="a">First number</param>
<param name="b">Second number</param>
<returns>Least common multiple</returns>
</member>
<member name="M:MetisDll.Lagrange.modInverse(System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="8">
<summary>
Fermat's Little Theorem Implementation on finding modular inverse
</summary>
<param name="a">a</param>
<param name="b">b.</param>
<param name="MOD">mod</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.addition(std.vector&lt;System.Double&gt;,std.vector&lt;System.Double&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="58">
<summary>
Additions the specified poly1.
</summary>
<param name="poly1">The poly1.</param>
<param name="poly2">The poly2.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.PointToVector(MetisDll.Point)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="77">
<summary>
Points to vector.
</summary>
<param name="p">The p.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.multiply(std.vector&lt;System.Double&gt;,std.vector&lt;System.Double&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="90">
<summary>
Multiplies the specified poly1.
</summary>
<param name="poly1">The poly1.</param>
<param name="poly2">The poly2.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.multiply(System.Double,std.vector&lt;System.Double&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="107">
<summary>
Multiplies the specified c.
</summary>
<param name="c">The c.</param>
<param name="poly">The poly.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.denominator(System.Int32,std.vector&lt;MetisDll.Point&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="122">
<summary>
Denominators the specified i.
</summary>
<param name="i">The i.</param>
<param name="points">The points.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.gcd(System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="140">
<summary>
Find the greatest common divisor between two number
</summary>
<param name="a">First number</param>
<param name="b">Second number</param>
<returns>Greatest common divisor</returns>
</member>
<member name="M:MetisDll.Lagrange.maxDenominator(std.vector&lt;MetisDll.Point&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="160">
<summary>
Calculate the maximum number of denominator given points
</summary>
<param name="points">Points.</param>
<returns></returns>
</member>
<member name="M:MetisDll.Lagrange.interpolation_polynomial(System.Int32,std.vector&lt;MetisDll.Point&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="184">
<summary>
Calculate the value of Pk for spesific x in the lagrange interpolation
</summary>
<param name="i">x</param>
<param name="points">Point in form of ( x, f(x) )</param>
<returns>List of coeeficient</returns>
</member>
<member name="M:MetisDll.Lagrange.CountCoefficient(std.vector&lt;MetisDll.Point&gt;)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\lagrange.cpp" line="208">
<summary>
Counts the total coeeficient of given points.
</summary>
<param name="points">Points in (x, f(x) )</param>
<returns>List of coefficient</returns>
</member>
</members>
</doc>