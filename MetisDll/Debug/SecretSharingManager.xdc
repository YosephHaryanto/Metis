<?xml version="1.0"?><doc>
<members>
<member name="M:MetisDll.Image.getHeight" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="21">
<summary>
Gets the height of the image.
</summary>
<returns>Image height</returns>
</member>
<member name="M:MetisDll.Image.getWidth" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="27">
<summary>
Gets the width of the image.
</summary>
<returns>Image width</returns>
</member>
<member name="M:MetisDll.Image.getN" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="33">
<summary>
Gets the n value of the shadow.
</summary>
<returns>n</returns>
</member>
<member name="M:MetisDll.Image.setHeight(System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="39">
<summary>
Sets the image height.
</summary>
<param name="value">The value of height.</param>
</member>
<member name="M:MetisDll.Image.setWidth(System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="45">
<summary>
Sets the image width.
</summary>
<param name="value">The valueof width.</param>
</member>
<member name="M:MetisDll.Image.setN(System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="51">
<summary>
Sets the n value of the shadow.
</summary>
<param name="N">n</param>
</member>
<member name="M:MetisDll.Image.ModifyPixel(System.Int32,System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="57">
<summary>
Modifies the value of pixel positioned in x and y.
</summary>
<param name="x">x</param>
<param name="y">y</param>
<param name="value">The pixel value.</param>
</member>
<member name="M:MetisDll.Image.getPixel(System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="65">
<summary>
Gets the value of pixel positioned in x and y.
</summary>
<param name="x">x</param>
<param name="y">y</param>
<returns>Value of pixel</returns>
</member>
<member name="M:MetisDll.Image.InsertPixel(System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="73">
<summary>
Inserts the pixel at last index of pixel.
</summary>
<param name="value">The pixel value.</param>
</member>
<member name="M:MetisDll.Image.getImageData" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="79">
<summary>
Gets the raw image data.
</summary>
<returns>Collection of pixel (Vector) </returns>
</member>
<member name="F:MetisDll.Image._imageData" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="88">
<summary>
The raw image data
</summary>
</member>
<member name="F:MetisDll.Image._height" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="93">
<summary>
The image height
</summary>
</member>
<member name="F:MetisDll.Image._width" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="98">
<summary>
The image width
</summary>
</member>
<member name="F:MetisDll.Image._N" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\image.h" line="103">
<summary>
The n value of shadow corresponding to f(n) in polynomial reconstruction
</summary>
</member>
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
<member name="M:MetisDll.ImageHelper.RGBtoint(System.Int32,System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\imagehelper.h" line="9">
<summary>
Converting the value of Red, Green, and Blue into pixel value
</summary>
<param name="R">The red value.</param>
<param name="G">The green value.</param>
<param name="B">The blue value.</param>
<returns>The pixel value in integer </returns>
</member>
<member name="M:MetisDll.SecretSharingManager.CreateShadow(MetisDll.Image,System.Int32,System.Int32)" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\secretsharingmanager.cpp" line="17">
<summary>
Create the shadows asynchronously.
</summary>
<param name="imageData">The original image data that designed as the secret</param>
<param name="n">Number of shadow created</param>
<param name="r">Number of minimum shadow to reconstruct.</param>
<returns>
Task of Image list
</returns>
</member>
<member name="M:MetisDll.SecretSharingManager.CreateSecret(Windows.Foundation.Collections.IVector`1{MetisDll.Image^})" decl="false" source="e:\yoseph haryanto\documents\project\thesis\code\metis\metis\metisdll\secretsharingmanager.cpp" line="131">
<summary>
Retrieve the secret.
</summary>
<param name="shadows">The shadows.</param>
<param name="n">The n.</param>
<param name="r">The r.</param>
<returns></returns>
</member>
</members>
</doc>