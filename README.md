<!DOCTYPE html>
<html>
<body>

<h2>Local Interpolation Using Lagrange Polynomials</h2>

<h2>Description</h2>
<p>This C++ program builds a local interpolation of the function f(x) = sin(x) on the interval [a, b] using piecewise polynomial Lagrange interpolation. The interval is divided into K equal subintervals; on each subinterval an interpolation polynomial of degree (N‑1) is constructed using N equally spaced nodes. The absolute and relative errors are computed in the L1, L2, and L∞ norms on a grid with step size h/100. Visualisation is performed with Python (matplotlib). Instructor requirements for the task: the use of std::vector is not allowed; manual memory management and OOP practices must be employed.</p>

<h2>Project Structure</h2>
<pre>
local_lagrange/
├── src/               # C++ source files (main.cpp, functions.cpp)
├── include/           # header files (functions.h)
├── scripts/           # Python script create_plot.py
├── data/              # output data parameters.txt (created at runtime)
├── docs/              # assignment task2.pdf
├── requirements.txt   # Python dependencies
├── Makefile           # build configuration
└── README.md          # this file
</pre>

<h2>Requirements</h2>
<ul>
<li>A C++17 compatible compiler (g++, clang++)</li>
<li>Python 3.6 or higher</li>
<li>Python libraries: <code>matplotlib</code> (install with <code>pip install -r requirements.txt</code>)</li>
</ul>

<h2>Building</h2>
<pre>
make clean   # clean previous build (optional)
make         # compile
</pre>

<h2>Running</h2>
<pre>
make run
</pre>
<p>Or manually:</p>
<pre>
bin/lagrange
</pre>

<h2>Cleaning</h2>
<pre>
make clean
</pre>
<p>Removes object files and the executable.</p>

<h2>What Happens When You Run the Program</h2>
<ol>
<li>A uniform grid of M interpolation nodes is generated (M = K*(N-1)+1).</li>
<li>For each of the K subintervals, a Lagrange interpolation polynomial is built using N nodes.</li>
<li>The values of the polynomial are evaluated at M_viz points for visualisation.</li>
<li>Errors are computed on a finer grid (step size h/100):</li>
<ul>
  <li>Absolute and relative errors in the L1 norm (sum of absolute values)</li>
  <li>Absolute and relative errors in the L2 norm (square root of the sum of squares)</li>
  <li>Absolute and relative errors in the L∞ norm (maximum absolute value)</li>
</ul>
<li>The error results are printed to the console.</li>
<li>Plot data is saved to <code>data/parameters.txt</code>.</li>
<li>The Python script <code>scripts/create_plot.py</code> is automatically launched, producing graphs of f(x) and L(x).</li>
</ol>

<h2>Example Console Output</h2>
<pre>
Absolute error  (1)  = 0.0234567
Absolute error  (2)  = 0.0032109
Absolute error (inf) = 0.0012345
Relative error  (1)  = 0.0015678
Relative error  (2)  = 0.0002123
Relative error (inf) = 0.0000821
</pre>

<h2>Visualisation</h2>
<p>After the computations a window appears with two plots: the original function f(x) as a blue dashed line, and the interpolation L(x) as a solid black line. Interpolation nodes are marked with circles. A grid and legend are included.</p>

<h2>Example Visualisation Result</h2>
https://github.com/g30613740/local_lagrange/blob/master/interpolation_plot.png

<h2>Notes</h2>
<ul>
<li>The function f(x) is defined in <code>src/functions.cpp</code> and can be replaced with any other function.</li>
<li><code>long double</code> is used to improve numerical accuracy.</li>
<li>If you see an error "Python not found", make sure the <code>python3</code> command is available on your system. If necessary, modify the script invocation in the <code>Makefile</code> (the line that runs the script).</li>
</ul>

<h2>License</h2>
<p>This project is distributed under the MIT License. See the <code>LICENSE</code> file for details.</p>

</body>
</html>