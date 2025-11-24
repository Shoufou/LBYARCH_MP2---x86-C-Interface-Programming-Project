# LBYARCH_MP2---x86-C-Interface-Programming-Project
MP2 Output for LBYARCH course

### GROUP MEMBERS
- Rivera, Paolo
- So, Jazlyn

# Specs
![specs](https://github.com/user-attachments/assets/2e53b89f-089a-438e-bf71-64f383c25c44)


# How to Compile:
1. Open the final_project folder
2. Open the .sln file with visual studio
3. Run the soruce.c file

# Time comparison and explanation
<table>
  <tr>
    <th></th>
    <th colspan="2">Average time over 30 function calls</th>
  </tr>
  <tr>
    <th>Number of Inputs</th>
    <th>Assembly</th>
    <th>C</th>
  </tr>
  <tr>
    <td>2^20</td>
    <td>0.0008 seconds</td>
    <td>0.0013 seconds</td>
  </tr>
  <tr>
    <td>2^24</td>
    <td>0.014767 seconds</td>
    <td>0.020367 seconds</td>
  </tr>
  <tr>
    <td>2^28</td>
    <td>0.2468 seconds</td>
    <td>0.353633 seconds</td>
  </tr>
</table>

As can be seen in the table, the Assembly kernel is consistently faster than the C kernel. One of the reasons why this is true is because of the nature of the languages themselves, specifically how these two languages are translated into machine code. While C is a compiled language, Assembly is an <i> assembled </i> language. This means that Assembly is closer to the hardware compared to C, meaning its easier to translate Assembly code into its machine code counterpart. This leads to slightly faster times which can especially be seen in computation heavy programs such as this one.
# Screenshots:
### Sample program output with a check for both x86-64 and C
<img width="1601" height="821" alt="image" src="https://github.com/user-attachments/assets/3bd3ea85-0915-4138-8a88-bf8324f9f6dc" />

# Video Demo:
https://drive.google.com/file/d/1lASJ8DCoC9GnmOtkSaPyNCFxATjd8TrZ/view?usp=sharing
