#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
   int choice;
   srand(time(NULL));

   cout<<"Welcome to this awesome adventure game! \n"<<"You open your eyes and find yourself alone on a picturesque white sand beach. Behind you is a dense and forboding jungle. As you have no options other than starve, you walk towards the jungle. Press 1 to forage for food; Press 2 to search for fresh water; Press 3 to look for civilization: "<<endl;
   cin>>choice;

   switch(choice)
   {
      case 1:
         cout<<"Near the top of a tree you spot a bunch of ripe bananas! Press 1 to climb the tree; Press 2 to move on: "<<endl;
         cin>>choice;
         if(choice == 1)
         {
            if(rand()%10 < 7)
            {
               cout<<"You managed to climb up the tree! As you reach for the bananas, however, you hear a faint rattling noise. Suddenly, a snake lunges out of the banana bunch and bites you on the arm. Shocked, you tumble off of the tree branch all the way to the ground where you break your neck and die. Sorry."<<endl;
            }
            else
            {
               cout<<"You're almost to the top! So excited by the bananas you don't notice the patch of moss underneath your foot. Your foot slips on the moss and you fall to the bottom of the tree and break your neck and die. Sorry."<<endl;
            }
         }
         else
         {
            cout<<"Like a coward you decide the tree is too tall to climb safely, and you turn to move on. Suddenly, you notice a violent rustling in the undergrowth. You back up slowly as a rather angry bear crashes out of the brush and mauls you. You have been eaten by a bear. Sorry."<<endl;
         }
         break;
      case 2:
         cout<<"You spot a clearing in the trees not far ahead! In the clearing a crystal clear stream bubbles cheerfully along. Press 1 to stop and drink at the stream; Press 2 to move on: "<<endl;
         cin>>choice;
         if(choice == 1)
         {
            if(rand()%10 < 5)
            {
               cout<<"As you take your first draft you hear a violent rustling in the brush behind you. Suddenly a rather angry bear comes crashing out of the bush and mauls you, staining the water of the stream red. You have been eaten by a bear. Sorry."<<endl;
            }
            else
            {
               cout<<"Off in the distance you hear a deep rumbling. The sky darkens in the middle of the day as ash from the island's volcano settles over the land. You have been suffocated. Sorry."<<endl;
            }
         }
         else
         {
            cout<<"Yeah, this clearing seems a little sketchy. However, just as you cross the stream there is a violent rustling in the brush in front of you. Suddenly, a rather angry bear comes crashing out of the bush and mauls you. You have been eaten by a bear. Sorry."<<endl;
         }
         break;
      case 3:
         cout<<"You walk forward for what seems like hours. Gradually the canopy above grows thinner and more light shines through, and then you break out of the forest near the base of a mountain. You see a collection of huts, and the faint sounds of life come from the village. Press 1 to approach; Press 2 to move on: "<<endl;
         cin>>choice;
         if(choice == 1)
         {
            if(rand()%10 < 7)
            {
               cout<<"As you approach the village the natives spot you. They begin to get excited and dance around, and you feel joy in seeing people. The next thing you know you're wrapped up in ropes and dumped down a dark hole, and you hear something sniffing deeper in the cave. Then, a roar and... nothing. You have been eaten by a bear. Sorry."<<endl;
            }
            else
            {
               cout<<"As you step out from the shade of the forest, you hear a violent rustling in the brush behind you. Suddenly, a rather angry bear comes crashing out of the bush and mauls you. You have been eaten by a bear. Sorry."<<endl;
            }
         }
         else
         {
            cout<<"You've heard all those stories about cannibals on tropical islands, so yeah, a village seems a little too good to be true. You prepare to skirt around the village when suddenly there is a violent rustling in the underbrush behind you. Suddenly, a rather angry bear comes crashing out of the bush and mauls you. You have been eaten by a bear. Sorry."<<endl;
         }
      default:
         cout<<"Error: Invalid input."<<endl;
         break;
   }
   return 0;
}
