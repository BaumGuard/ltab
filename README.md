# ltab
Displaying linking table (discrete maths) in the terminal

# Description
`ltab` displays the linking table of a given size in the terminal window. It supports **multiplication** and **addition**

# Compiling
Compile:
```
make
```

# Usage
## Syntax
```
ltab <divider> <m|p> [ -xs <number> | -xe <number> | -ys <number> | -ye <number> ]
```

## Arguments

<table>
  <tr>
    <td><code>&lt;integer&gt;</code></td>
    <td>Size of the linking table (divisor)</td>
  </tr>
  <tr>
    <td><code>&lt;m|p&gt;</code></td>
    <td><b>Operator</b><br>
      <ul>
        <li><b>m</b>: Multiplication</li>
        <li><b>p</b>: Addition</li>
      </ul>
    </td>
  </tr>

  <tr>
    <td><code>-xs &lt;number&gt;</code><br><i>optional</i></td>
    <td><b>x</b> <b>s</b>tart<br>Horizontal start of output section</td>
  </tr>
    <td><code>-xe &lt;number&gt;</code><br><i>optional</i></td>
    <td><b>x</b> <b>e</b>nd<br>Horizontal end of output section</td>
  </tr>
  <tr>
    <td><code>-ys &lt;number&gt;</code><br><i>optional</i></td>
    <td><b>y</b> <b>s</b>tart<br>Vertical start of output section</td>
  </tr>
  <tr>
    <td><code>-ye &lt;number&gt;</code><br><i>optional</i></td>
    <td><b>y</b> <b>e</b>nd<br>Vertical end of output section</td>
  </tr>
</table>

## Example
```
./ltab 7 m -xs 2 -xe 5 -ye 4
```
Will output the section of the linking table (divider **7**) from **2 to 5 (horizontally)** and **0 to 4 (vertically)** in case of **m**ultiplication.
