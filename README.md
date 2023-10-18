# ProcessManager

ProcessManager is a project designed to simulate a process manager for a multitasking operating system. Its primary goal is to ensure the smooth operation of the system by efficiently handling the demands of all users. It creates the illusion that a greater number of processes are running simultaneously than there are actual processors in the computer. Each process is allocated a time slice, and the switching between various processes occurs rapidly enough to give users the impression of simultaneous execution. The system employs specific algorithms to commands for determine which process to execute at a given moment and for how long. Process requests arrive constantly and must be processed based on their arrival time and priority.

## Getting Started

To use ProcessManager, follow the instructions below:

### Prerequisites

- GCC (GNU Compiler Collection)
- Make

### Installation

1. Clone the repository

    ```bash
    git clone https://github.com/lfelipediniz/ProcessManager.git
    ```

2. Navigate to the project directory

    ```bash
    cd ProcessManager
    ```

### Usage

1. Compile and run the program using the provided Makefile

    ```bash
    make
    ```

2. Execute the program (with either of the two commands)

    ```bash
    make run
    ```

3. To delete the generated files run

    ```bash
    make clean
    ```

### Explaining the use in more detail

The program input is structured by specifying the operation to be performed, followed by one or two strings of characters, depending on the required operation. Operations should adhere to the following input configuration

1. Adds a process to the list of processes to be executed

    ```bash
    add (priority) 'time' 'description'
    ```

- priority: Int between 1 and 99
- time: hh:mm:ss
- description:  Is a character chair with  maximum size of 50

2. Execute a process with the option

    ```bash
    exec 'option'
    ```
    Options
    
    - **-p**: run a process with higher priority
    - **-t**: run a process with lower time  

3. Shows a process according to the option

    ```bash
    next 'option'
    ```
    Options
    
    - **-p**: Shows all process information with highest priority
    - **-t**: Shows all the process information with the lowest time
  
4. Modifies information about a process according to the option

    ```bash
    change 'option''previous'|'new'
    ```
    Options
    
    - **-p**: Changes the prior field with the previous value to the new value
    - **-t**: Changes the time field with the previous value to the new value, using the format *hh:mm:ss*

5. Prints all processes to be executed according to the option

    ```bash
    print 'option'
    ```
    Options
    
    - **-p**: Prints the processes in descending order of priority
    - **-t**: Prints processes in ascending order of times
  
6. Exit the program
  
    ```bash
    quit
    ```


## Test case

<table align="center">
<thead>
<tr>
<th>Input</th>
<th>Output</th>
</tr>
</thead>
<tbody>
<tr>
<td>
add 9 11:05:41 firefox <br>
add 14 06:15:02 openoffice<br>
add 5 05:26:18 xterm<br>
add 7 10:44:34 emacs<br>
add 16 05:43:21 gdb<br>
add 11 22:47:56 garbage-collector<br>
add 8 08:06:09 xfig<br>
add 12 06:21:59 bash<br>
add 13 04:11:20 nautilus<br>
add 6 04:37:34 gnome<br>
add 4 16:19:47 gcalc<br>
add 17 22:40:32 x-session<br>
add 1 07:33:25 printer-deamon<br>
add 3 03:53:17 gimp<br>
next -p<br>
next -t<br>
exec -p<br>
exec -p<br>
change -t 06:21:59|02:22:19<br>
change -p 6|10<br>
exec -t<br>
print -p<br>
print -t<br>
quit<br>
</td>
<td> 
17 22:40:32 x-session<br>
03 03:53:17 gimp<br>
14 06:15:02 openoffice<br>
13 04:11:20 nautilus<br>
11 22:47:56 garbage-collector<br>
10 04:37:34 gnome<br>
09 11:05:41 firefox<br>
08 08:06:09 xfig<br>
07 10:44:34 emacs<br>
05 05:26:18 xterm<br>
04 16:19:47 gcalc<br>
03 03:53:17 gimp<br>
01 07:33:25 printer-deamon<br>
03 03:53:17 gimp<br>
13 04:11:20 nautilus<br>
10 04:37:34 gnome<br>
05 05:26:18 xterm<br>
14 06:15:02 openoffice<br>
01 07:33:25 printer-deamon<br>
08 08:06:09 xfig<br>
07 10:44:34 emacs<br>
09 11:05:41 firefox<br>
04 16:19:47 gcalc<br>
11 22:47:56 garbage-collector<br>
</td>
</table>

## Authors

| Names                           | USP Number |
| :----------------------         | ---------- |
| Luiz Felipe Diniz Costa         | 13782032   |
| Nicolas Carreiro Rodrigues      | 14600801   |
| Henrique Drago                  | 14675441   |
| João Pedro Boiago Gomes Santana | 14747211   |
| Murilo Fonseca de Matos         | 13719065   |
| Arthur Trottmann Ramos          | 14681052   |

Project for the course ["Introduction to Computer Science II"](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=SCC0201) at the Institute of Mathematics and Computer Science, University of Sao Paulo



