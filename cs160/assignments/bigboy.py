############################################################################
#Function: get_initial_input
#Description: get a positive integer amount of each category: assignments, labs, exercises, and tests. Final is automatically assumed to be locked at 1.
#Pre-conditions: none. This is the first function call in the main function.
#Post-conditions: output an array of positive integer values in the following order: assignments, labs, exercises, tests, final.
############################################################################
def get_initial_input():
   list_stuff = [0] * 5;
   num_assignments = input("Enter the number of assignments: ");
   while True:
      not_okay = check_lies(num_assignments);
      if(not_okay == False):
         break;
      else:
         num_assignments = input("Enter the number of assignments: ");
         continue;
   num_labs = input("Enter the number of labs: ");
   while True:
      not_okay = check_lies(num_labs);
      if(not_okay == False):
         break;
      else:
         num_labs = input("Enter the number of labs: ");
         continue;
   num_exercises = input("Enter the number of exercises: ");
   while True:
      not_okay = check_lies(num_exercises);
      if(not_okay == False):
         break;
      else:
         num_exercises = input("Enter the number of exercises: ");
         continue;
   num_tests = input("Enter the number of tests: ");
   while True:
      not_okay = check_lies(num_tests);
      if(not_okay == False):
         break;
      else:
         num_tests = input("Enter the number of tests: ");
         continue;
   
   list_stuff[0] = int(num_assignments);
   list_stuff[1] = int(num_labs);
   list_stuff[2] = int(num_exercises);
   list_stuff[3] = int(num_tests);
   list_stuff[4] = 1;
   return list_stuff;
############################################################################
#Function: check_lies
#Description: test user inputs for being positive integer numbers.
#Pre-conditions: the function is being passed a string.
#Post-conditions: the function returns a boolean value, depending on the identity of the string.
############################################################################
def check_lies(string_num):
   broke = False;
   if(not string_num.isnumeric()):
      broke = True;
      print("Wrong.");
   elif(int(string_num) < 0 or int(string_num) > 100):
      broke = True;
      print("Wrong.");
   else:
      print("Correct.");
   return broke;
############################################################################
#Function: get_scores
#Description: computes a total score for each category and returns the values in a list.
#Pre-conditions: the function is being passed a list of integers.
#Post-conditions: returns a list of positive integer values.
############################################################################
def get_scores(a_list):
   total_a_score = 0;
   total_l_score = 0;
   total_e_score = 0;
   total_t_score = 0;
   total_f_score = 0;
   score_list = [0] * 5;
   for a in range(a_list[0]):
      a_score = input("Enter the percent score of assignment " +str(a+1)+ ": ");
      while True:
         not_okay = check_lies(a_score);
         if(not_okay == False):
            break;
         else:
            a_score = input("Enter the percent score of assignment " +str(a+1)+ ": ");
            continue;
      total_a_score += int(a_score);
   score_list[0] = total_a_score;
   
   for b in range(a_list[1]):
      l_score = input("Enter the percent score of lab " +str(b+1)+ ": ");
      while True:
         not_okay = check_lies(l_score);
         if(not_okay == False):
            break;
         else:
            l_score = input("Enter the percent score of lab " +str(b+1)+ ": ");
            continue;
      total_l_score += int(l_score);
   score_list[1] = total_l_score;
   
   for c in range(a_list[2]):
      e_score = input("Enter the percent score of exercise " +str(c+1)+ ": ");
      while True:
         not_okay = check_lies(e_score);
         if(not_okay == False):
            break;
         else:
            e_score = input("Enter the percent score of exercise " +str(c+1)+ ": ");
            continue;
      total_e_score += int(e_score)
   score_list[2] = total_e_score;
   
   for d in range(a_list[3]):
      t_score = input("Enter the percent score of test " +str(d+1)+ ": ");
      while True:
         not_okay = check_lies(t_score);
         if(not_okay == False):
            break;
         else:
            t_score = input("Enter the score of test " +str(d+1)+ ": ");
            continue;
      total_t_score += int(t_score)
   score_list[3] = total_t_score;

   total_f_score = input("Enter the final test score percentage: ");
   while True:
      not_okay = check_lies(total_f_score);
      if(not_okay == False):
         break;
      else:
         total_f_score = input("Enter the final test score percentage: ");
         continue;
   score_list[4] = int(total_f_score);

   return score_list;
############################################################################
#Function: get_weights()
#Description: get the weight value of each category in percentages and convert the percentages into floats.
#Pre-conditions: none.
#Post-conditions: returns a list of float values in order of assignments, labs, exercises, tests, and final.
############################################################################
def get_weights():
   list_weights = [0] * 5;
   while True:
      weight_assignments = input("Enter the percentage weight of assignments: ");
      while True:
         not_okay = check_lies(weight_assignments);
         if(not_okay == False):
            break;
         else:
            weight_assignments = input("Enter the percentage weight of assignments: ");
            continue;
   
      weight_labs = input("Enter the percentage weight of labs: ");
      while True:
         not_okay = check_lies(weight_labs);
         if(not_okay == False):
            break;
         else:
            weight_labs = input("Enter the percentage weight of labs: ");
            continue;
   
      weight_exercises = input("Enter the percentage weight of exercises: ");
      while True:
         not_okay = check_lies(weight_exercises);
         if(not_okay == False):
            break;
         else:
            weight_exercises = input("Enter the percentage weight of exercises: ");
            continue;
   
      weight_tests = input("Enter the percentage weight of tests: ");
      while True:
         not_okay = check_lies(weight_tests);
         if(not_okay == False):
            break;
         else:
            weight_tests = input("Enter the percentage weight of tests: ");
            continue;

      weight_final = input("Enter the percentage weight of the final: ");
      while True:
         not_okay = check_lies(weight_final);
         if(not_okay == False):
            break;
         else:
            weight_final = input("Enter the percentage weight of the final: ");
            continue;

      weights = int(weight_assignments) + int(weight_labs) + int(weight_exercises) + int(weight_tests) + int(weight_final);
      if(weights > 100):
         print("Total inputed weight greater than 100%. Please rework addition and enter a total weight of 100%.");
         continue;
      elif(weights < 100):
         print("Total inputed weight less than 100%. Please rework addition and enter a total weight of 100%.");
         continue;
      else:
         break;
   list_weights[0] = float(weight_assignments)/100;
   list_weights[1] = float(weight_labs)/100;
   list_weights[2] = float(weight_exercises)/100;
   list_weights[3] = float(weight_tests)/100;
   list_weights[4] = float(weight_final)/100;

   return list_weights;
############################################################################
#Function: calc_weight_avg
#Description: calculates the average score of each category, then multiplies by the percentage weight of each category.
#Pre-conditions: passed 3 lists of numbers, in order of assignments, labs, exercises, tests, and final. The first two lists are of integer values, the third is of float values.
#Post-conditions: returns a list of float values in order of assignments, labs, exercises, tests, and final.
############################################################################
def calc_weight_avg(list_nums, list_scores, list_weights):
   weighted_stuff = [0] * 5;
   avg_assigns = list_scores[0] / list_nums[0];
   avg_labs = list_scores[1] / list_nums[1];
   avg_exercises = list_scores[2] / list_nums[2];
   avg_tests = 0;
   if(list_nums[3] > 0):
      avg_tests = list_scores[3] / list_nums[3];
   
   weighted_assigns = avg_assigns * list_weights[0];
   weighted_labs = avg_labs * list_weights[1];
   weighted_exercises = avg_exercises * list_weights[2];
   weighted_tests = avg_tests * list_weights[3];
   weighted_final = list_scores[4] * list_weights[4];

   weighted_stuff[0] = weighted_assigns;
   weighted_stuff[1] = weighted_labs;
   weighted_stuff[2] = weighted_exercises;
   weighted_stuff[3] = weighted_tests;
   weighted_stuff[4] = weighted_final;

   return weighted_stuff;
############################################################################
#Function: calc_grade()
#Description: calculate the final grade using the weighted average scores of each individual category.
#Pre-conditions: a list of weighted average scores in order of assignments, labs, exercises, tests, and final has been provided.
#Post-conditions: returns a single float value.
############################################################################
def calc_grade(list_averages):
   grade = 0;
   for x in range(len(list_averages)):
      grade += list_averages[x];
   return grade;
#THIS IS THE MAIN FUNCTION#
def main():
   num_list = get_initial_input();
   scores_list = get_scores(num_list)
   weight = get_weights();
   avg = calc_weight_avg(num_list, scores_list, weight);
   final_score = calc_grade(avg);
   print(final_score);

main();
