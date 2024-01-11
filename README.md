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
`./ltab` has the following syntax:
```
ltab <integer> <m|p>
```

## Arguments

<table>
  <tr>
    <td><b>&lt;integer&gt;</b></td>
    <td>Size of the linking table (divisor)</td>
  </tr>
  <tr>
    <td><b>&lt;m|p&gt;</b></td>
    <td><b>Operator</b><br>
      <ul>
        <li><b>m</b>: Multiplication</li>
        <li><b>p</b>: Addition</li>
      </ul>
    </td>
  </tr>    
</table>

## Example
```
./ltab 7 m
```
Will output the linking table for **7** in case of **multipication**.
