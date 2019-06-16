cont = 1;

while(cont == 1):
	while True:
		try:
			num1 = int(input("Enter an integer: "));
			break;
		except ValueError:
			print("Not a real integer.");
	
	while True:
		try:
			num2 = int(input("Enter another integer: "));
			break;
		except ValueError:
			print("Not a real integer.");

	notnum = input("Enter an operator (+, -, *, /, **, %): ");

	if(notnum == "+"):
		print(num1 + num2);
	elif(notnum == "-"):
		print(num1 - num2);
	elif(notnum == "*"):
		print(num1 * num2);
	elif(notnum == "/"):
		print(num1 / num2);
	elif(notnum == "**"):
		print(num1 ** num2);
	elif(notnum == "%"):
		print(num1 % num2);
	else:
		print("Invalid operator.");
	
	while True:
		try:
			cont = int(input("If you wish to continue, enter 1. If finished, enter any other number: "));
			break;
		except ValueError:
			print("Sorry, try again.");

print("Thank you, come again!");
