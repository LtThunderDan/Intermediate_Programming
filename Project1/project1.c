/*
  Created by: Daniel Williamson
  Due: Friday, 10 2017
  gcc project1.c -o p1 -lm

  This project takes three values. A height, initial velocity and a fireing angle.
  Using physics, it calculates the time and distance the projectile covers.
*/

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main(){
  //all variables used.
  double getHeight;
  double fireAngle;
  double getVelocity;
  double xVector;
  double yVector;
  double getDegrees;
  double getTime;
  double getDistance;
  double t1;
  double t2;
  char continueLoop = 'y';

  //Welcome message. As per assignment.
  printf("\n\nHello World!\n\n");
  printf("Welcome to my first project in EE 222\n");
  printf("This project will take in an initial height, firing angle and velocity\n");
  printf("and tell you how long and far the projectile went.\n");
  printf("----------------------------------------------------------------------\n");

  //keeps the project going unless user wants to exit, by !pressing y.
  while(continueLoop == 'y')
  {
    //obtains the height for firing from the user.
    printf("Please enter the height, between 0 - 1000m, you want to fire at: ");
    scanf("%lf", &getHeight);
    //uses a while loop to make sure they enter a number between 0 and a mile.
    while(getHeight < 0 || getHeight > 1000)
    {
      printf("Please enter a height between 0 - 1000m: ");
      scanf("%lf", &getHeight);
    }
    //lets print out what they put in
    printf("\nThe height you entered is: %.2f m\n\n", getHeight);

    //now lets obtain the fire angle.
    printf("Please enter a firing angle, between -90 degrees to 90 degrees: ");
    scanf("%lf", &fireAngle);
    //use a while loop to make sure they enter a number between -90 to 90
    while(fireAngle < -90 || fireAngle > 90)
    {
      printf("Please enter an angle between -90 to 90: ");
      scanf("%lf", &fireAngle);
    }
    //lets print out what they put in
    printf("\nThe angle you entered is: %.2f degrees\n\n", fireAngle);

    //now lets obtain the velocity
    printf("Please enter your initial velocity, it must be greater than zero: ");
    scanf("%lf", &getVelocity);

    //use a while loop to make sure they enter something larger then 0.
    while(getVelocity < 0)
    {
      printf("Please enter a velocity equal to or greater than zero: ");
      scanf("%lf", &getVelocity);
    }
    //lets print out what they put in
    printf("\nThe velocity you entered is: %.2f m/s\n\n", getVelocity);

    //now lets do some math to find our x and y vector.
    getDegrees = PI / 180.0;
    xVector = (cos(fireAngle*getDegrees)*getVelocity);
    printf("Your xVector is: %.2f\n", xVector);

    yVector = (sin(fireAngle*getDegrees)*getVelocity);
    printf("Your yVector is: %.2f\n", yVector);

    //next lets do some math to find our time traveled.
    //if height is positve set t1..
    if(fireAngle > 0)
    {
      t1 = ((2 * yVector)/9.8);
    }
    //else set it equal to 0..
    else
    {
      t1 = 0;
    }
    t2 = ((getHeight*16)/(getVelocity*15));
    //add those together to get overall time.
    getTime = (t1+t2);

    printf("\nThe time it took to land was: %.2f s\n", getTime);

    //lastly lets do some math to find our distance traveled.
    getDistance = getTime * xVector;
    printf("\nThe distance traveled was: %.2f m\n\n", getDistance);

    //attempt to make it re-doable.
    printf("Would you like to try again? y/n : ");
    scanf(" %c", &continueLoop);

    //input must be lowercase y or n.
    if(continueLoop == 'y')
    {
      continue;
    }
    else
    {
      break;
    }
  }
  return 0;
}
