
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <sys/timeb.h>
#include <time.h>


		/*
		** Robot functions
		*/



		/* This robot moves randomly */

void RandomRobot(int FoodClosestDistance,	/* input - closest food in pixels */
			int FoodClosestAngle,		/* input - angle in degrees towards closest food */
			int RobotClosestDistance,	/* input - closest other robot, in pixels */
			int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
			int SharkClosestDistance,	/* input - closest shark in pixels */
			int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
			int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
			int *RobotMoveAngle,		/* output - angle in degrees to move */
			int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	if (SharkClosestDistance<50) //A shark is near, speed up
	{
		(*RobotExpendEnergy) = 20;
	}
	else
	{
		if (CurrentRobotEnergy>200)
		{
			(*RobotExpendEnergy) = 20;
		}
		else
		{
			if (CurrentRobotEnergy>120)
			{
				(*RobotExpendEnergy) = 10;
			}
			else
			{
				(*RobotExpendEnergy) = 5;
			}
		}
	}

	//if a shark or other robots are near, run away. else eat food
	if (SharkClosestDistance>50 && ((abs(SharkClosestDistance - FoodClosestDistance))>50))
	{
		if (RobotClosestDistance>20)
			(*RobotMoveAngle) = (FoodClosestAngle);
		else
			(*RobotMoveAngle) = (180 + RobotClosestAngle) % 360;
	}
	else
	{
		(*RobotMoveAngle) = (180 + SharkClosestAngle) % 360;
	}
//(*RobotMoveAngle)=(rand() % 360);
//if (CurrentRobotEnergy > 50)
//  (*RobotExpendEnergy)=(rand() % (CurrentRobotEnergy-50));
//else
//  (*RobotExpendEnergy)=1;
//if ((*RobotExpendEnergy) > 10)
//  (*RobotExpendEnergy)=10;
}



		/* This robot moves towards food, ignoring sharks */

void GreedyRobot(int FoodClosestDistance,	/* input - closest food in pixels */
			int FoodClosestAngle,		/* input - angle in degrees towards closest food */
			int RobotClosestDistance,	/* input - closest other robot, in pixels */
			int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
			int SharkClosestDistance,	/* input - closest shark in pixels */
			int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
			int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
			int *RobotMoveAngle,		/* output - angle in degrees to move */
			int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
	if (SharkClosestDistance < 30){
		(*RobotMoveAngle) = (180 + SharkClosestAngle) % 360;
		(*RobotExpendEnergy) = 20;
	}
	else if (abs(SharkClosestAngle - FoodClosestAngle) > 45){
		(*RobotMoveAngle) = FoodClosestAngle;
		(*RobotExpendEnergy) = 20;
	}
	else
		(*RobotExpendEnergy) = 30 - SharkClosestDistance / 10;
	if ((*RobotExpendEnergy) < 3)
		(*RobotExpendEnergy) = 3;
}



		/* This robot moves away from sharks, ignoring food */

void ScaredRobot(int FoodClosestDistance,	/* input - closest food in pixels */
			int FoodClosestAngle,		/* input - angle in degrees towards closest food */
			int RobotClosestDistance,	/* input - closest other robot, in pixels */
			int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
			int SharkClosestDistance,	/* input - closest shark in pixels */
			int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
			int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
			int *RobotMoveAngle,		/* output - angle in degrees to move */
			int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{
(*RobotMoveAngle)=(180+SharkClosestAngle)%360;
if (SharkClosestDistance < 30)
  (*RobotExpendEnergy)=30;
else
  (*RobotExpendEnergy)=30-SharkClosestDistance/10;
if ((*RobotExpendEnergy) < 3)
  (*RobotExpendEnergy)=3;
}


void PrancingHorse(int FoodClosestDistance,	/* input - closest food in pixels */
	int FoodClosestAngle,		/* input - angle in degrees towards closest food */
	int RobotClosestDistance,	/* input - closest other robot, in pixels */
	int RobotClosestAngle,		/* input - angle in degrees towards closest robot */
	int SharkClosestDistance,	/* input - closest shark in pixels */
	int SharkClosestAngle,		/* input - angle in degrees towards closest shark */
	int CurrentRobotEnergy,		/* input - this robot's current energy (50 - 255) */
	int *RobotMoveAngle,		/* output - angle in degrees to move */
	int *RobotExpendEnergy)		/* output - energy to expend in motion (cannot exceed Current-50) */

{	
	static int previousSharkAngle = 0;
	previousSharkAngle = SharkClosestAngle;

	if (SharkClosestDistance > 40)
	{
		if (abs(previousSharkAngle - FoodClosestAngle) < 20)
		{
			*RobotMoveAngle = (180 + SharkClosestAngle) % 360;
			*RobotExpendEnergy = 30;
		}
		else
		{
			*RobotMoveAngle = FoodClosestAngle;
			*RobotExpendEnergy = 20;
		}
	}
	else
	{
		*RobotMoveAngle = (180 + SharkClosestAngle) % 360;
		*RobotExpendEnergy = 30;
	}
	
	if (CurrentRobotEnergy < 20 && SharkClosestDistance > 50)
	{
		if (previousSharkAngle > 20)
		{
			*RobotMoveAngle = FoodClosestAngle;
			*RobotExpendEnergy = 5;
		}
	}

	if (abs(SharkClosestAngle - FoodClosestAngle) > 50 && CurrentRobotEnergy > 180)
	{
		*RobotMoveAngle = FoodClosestAngle;
		*RobotExpendEnergy = 5;
	}
}