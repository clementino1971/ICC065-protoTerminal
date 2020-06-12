# ICC065-protoTerminal
* **Developers**:
  * Marcos Paulo Lopes ([@Marcoszz](https://github.com/Marcoszz)) - 21850690
  * Fernando Neves Nogueira ([@foolnando](https://github.com/foolnando)) - 21853994
  * Felipe Pereira Franco ([@felipovysk](https://github.com/felipovysk)) - 21851567
  * Thailsson Clementino ([@clementino1971](https://github.com/clementino1971)) - 21850695
  
  ***
  
  ### Project
 * This project was proposed in the subject of Operational Systems in Universidade Federal do Amazonas and consists in the implementation of a simple shell that supports a few commands and modifiers like: **ls, cd, pwd, >, <, |, &**. You can also run a mix of them.
  
  ***
  ### Running
  
 * After downloading the repository, run `make` in it to generate a compiled file to build. After this you might see a `protoTerminal.o` file in repository.
 * To start the shell, just type `build/protoTerminal` then your terminal it's ready to use.
 * After this your terminal will open in the current path and it's ready to use.
 
 ***
 ### Testing
 
 * You can type any commands executable in the shell. If it doesn't recognize the arguments or that's a missing parameter of the function it'll show the expectated parameters likewise the normal shell.
   * Test cd .. or a directory name
   * Test pwd to see the whole current path.
   * Test ls to see all rep/files in in the current path.
   * Test a ./program and transfer the output with >.
   * Test a ./program and transfer the input from a file with <.
   * Test a ./program and & to run in the background.
   * Test a ./program1 and | other ./program2 to transfer the output from 1 to be the input from 2.
 
 
