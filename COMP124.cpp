#include <stdio.h>
#include <stdlib.h>

int main(void)

{
	// Initialising 
	char NoPension[] = "No Pension Payable\n";
	char Hundred[] = "You are entitled to $100\n";
	char HundredTwenty[] = "You are entitled to $120\n";
	char ProgramEnd[] = "End of program\n";
	char stats[] = "A total of $%d has been paid out to %d people\n";
	char LineSpacing[] = "\n";
	int pension = 0;
	int payment = 0;
	int age;
	char InputQuestion[] = "Enter age: ";
	char input[] = "%d";

	_asm

	{
		Start:
			// Jumping to the start of the physical program so there is no space at the start
			jmp AfterSpace

		MainLoop :
			// Adding a line spacing after each run of the program
			lea eax, LineSpacing
			push eax
			call printf
			pop eax
			jmp AfterSpace

		AfterSpace :
			// Adding the input question into the eax and printing it so the user can see.
			lea eax, InputQuestion
			push eax
			call printf
			pop eax

			// Capturing the age inputted by pushing the age and the input into the eax and calling scanf
			lea eax, age
			push eax
			lea eax, input
			push eax
			call scanf
			// Popping the eax so that it is empty to be used again
			pop eax
			pop eax

			// moving age into eax to then compare with 0. If it is smaller than 0, we jump to the end of the program.
			mov eax, age
			cmp eax, 0
			mov age, eax
			jl End
			// Comparing the age with 65 now, if it is less than 65 we jump to the LessThan statement.
			mov eax, age
			cmp eax, 65
			mov age, eax
			jl LessThan

			// Greater than or equal to 65 at this point.
			// We now move pension into the eax and add 100. 
			mov eax, pension
			add eax, 100
			mov pension, eax

			// We also increment payment to 1.

			inc payment

			// We then need to check if the age is greater than or equal to 80, if it is, we jump to Eighty.
			mov eax, age
			cmp eax, 80
			mov age, eax
			jge Eighty

			// Now we know it is less than 80 but higher than 65, we print you get $100.
			lea eax, Hundred
			push eax
			call printf
			pop eax
			// Restart the loop
			jmp MainLoop

			// Greater than or equal to 80 at this point

		Eighty :
			// We now add the extra $20 that was needed
			mov eax, pension
			add eax, 20
			mov pension, eax

			// We also need to print that the user gets $120
			lea eax, HundredTwenty
			push eax
			call printf
			pop eax
			// Restart the loop
			jmp MainLoop

		LessThan :
			// As it is less than 65 but greater than or equal to 0. We add a message to tell the user they get no pension
			lea eax, NoPension
			push eax
			call printf
			pop eax
			// Restart the loop
			jmp MainLoop

		End:
			// Here we push the message that the program has ended
			lea eax, ProgramEnd
			push eax
			call printf
			pop eax

			// Final Output

			// Here we push in the parameters we need to print out and then call printf. We then pop eax to evacuate the parameters used.
			push payment
			push pension
			lea eax, stats
			push eax
			call printf
			pop eax
			pop eax
			pop eax

	}

	return 0;

}