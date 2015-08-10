/***************************************
Program Filename: Tournament.cpp
Author: Philip Jones
Date: 7/27/2015
Description:
Input:
Output:
****************************************/

#include "heads.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Queue team1, team2;
	Stack losers;
	int teamsize, i, choice;
	int dam, def, att, spec;
	int points, life;
	int rank1, rank2, rank3, temporary;
	std::string ranked1, ranked2, ranked3, tempname;
	std::string name, garbage;
	Creature fighter[2];
	std::vector<int> standings;
	std::vector<Creature> standees;
	
	cout <<"How many fighters will each team have?" <<endl;
	cin >> teamsize;
	
	if (teamsize == 0)
	{
		cout <<"Then there won't be a tournament!" <<endl;
		return 0;
	}
	
	for (i = 0; i<teamsize; i++)
	{
		cout <<"Please add a fighter to team 1." <<endl;
		cout <<"1. Barbarian" <<endl;
		cout <<"2. Goblin" <<endl;
		cout <<"3. Reptile Person" <<endl;
		cout <<"4. Blue Man" <<endl;
		cout <<"5. The Shadow" <<endl;
		cin >> choice;
		cout <<"What is its name?" <<endl;
		cin >> name;
	
		if (choice == 1)
		{
			Barbarian ao(2, 6, 2, 0, 12, name, 1);
			team1.addBack(ao);
		}
		else if (choice == 2)
		{
			Goblin ao(2, 6, 1, 3, 8, name, 2);
			team1.addBack(ao);
		}
		else if (choice == 3)
		{
			Reptilian ao(3, 6, 1, 7, 18, name, 3);
			team1.addBack(ao);
		}
		else if (choice == 4)
		{
			BlueMan ao(2, 10, 3, 3, 12, name, 4);
			team1.addBack(ao);
		}
		else if (choice == 5)
		{
			Shadow ao(2, 10, 1, 0, 12, name, 5);
			team1.addBack(ao);
		}
		else
		{
			cout << "That's not one of your choices!" <<endl;
			return 0;
		}
	}
	cout <<"Now for the second team." <<endl;
	for (i = 0; i<teamsize; i++)
	{
		cout <<"Please add a fighter to team 2." <<endl;
		cout <<"1. Barbarian" <<endl;
		cout <<"2. Goblin" <<endl;
		cout <<"3. Reptile Person" <<endl;
		cout <<"4. Blue Man" <<endl;
		cout <<"5. The Shadow" <<endl;
		cin >> choice;
		cout <<"What is its name?" <<endl;
		cin >> name;
	
		if (choice == 1)
		{
			Barbarian bo(2, 6, 2, 0, 12, name, 1);
			team2.addBack(bo);
		}
		else if (choice == 2)
		{
			Goblin bo(2, 6, 1, 3, 8, name, 2);
			team2.addBack(bo);
		}
		else if (choice == 3)
		{
			Reptilian bo(3, 6, 1, 7, 18, name, 3);
			team2.addBack(bo);
		}
		else if (choice == 4)
		{
			BlueMan bo(2, 10, 3, 3, 12, name, 4);
			team2.addBack(bo);
		}
		else if (choice == 5)
		{
			Shadow bo(2, 10, 1, 0, 12, name, 5);
			team2.addBack(bo);
		}
		else
		{
			cout << "That's not one of your choices!" <<endl;
			return 0;
		}
	}
	
	//teams are now fully formed
	
	while ((team1.isEmpty() == false) && (team2.isEmpty() == false))
	{
		
		fighter[0] = team1.getFront();
		team1.removeFront();
		fighter[1] = team2.getFront();
		team2.removeFront();
		
		while (fighter[0].getHP() > 0)
		{
		//Player 1 attacks, Player 2 defends.
			att = fighter[0].attack();		//calculates attack
			def = fighter[1].defend();		//calculates defense
			dam = att - def;				
		
			if (fighter[0].getType() == 1)		//checks for Achilles attack
			{
				if (fighter[1].getType() != 1)
				{
					if (att == 12)
					{
						spec = fighter[1].getAttackDiceSides();
						if (spec >= 4)
						{
//							cout << "Achilles hit!" <<endl;
							spec = (spec/2);
							fighter[1].setAttackDiceSides(spec);
					}
				}
			}
		}
		
		if (fighter[1].getType() == 5)	//checks for Shadow special miss
		{
			spec = fighter[1].roll(2);
			if (spec == 1)
			{
				dam = 0;
//				cout << fighter[1].getName() <<" wasn't there!" <<endl;
			}
		}
		
		if (dam < 0)					//checks for negative damage
			{
				points = fighter[1].getPoints();
				points = (points + 5);
				fighter[1].setPoints(points);
//				cout << fighter[1].getName() << " takes 0 damage!" <<endl;
			}
		else
			{
				points = fighter[0].getPoints();
				points = (points + (dam * 2));
				fighter[0].setPoints(points);
//				cout << fighter[1].getName() << " takes " << dam << " damage!" <<endl;
			}
		if (!fighter[1].damage(dam))
		{
			cout << fighter[1].getName() << " is dead!" <<endl;
			cout << fighter[0].getName() << " wins!" <<endl;
			cout <<endl;
			
			points = fighter[0].getPoints();
			points = (points + 50);
			fighter[0].setPoints(points);
			
			if ((fighter[0].getType() == 1) || (fighter[0].getType() == 4) || (fighter[0].getType() == 5))
			{
				life = (fighter[0].getHP() + 6);
				if (life>12)
				{
					fighter[0].setHP(12);
				}
				else
				{
					fighter[0].setHP(life);
				}
			}
			else if (fighter[0].getType() == 2)
			{
				life = (fighter[0].getHP() + 4);
				if (life>8)
				{
					fighter[0].setHP(8);
				}
				else
				{
					fighter[0].setHP(life);
				}
			}
			else
			{
				life = (fighter[0].getHP() + 9);
				if (life>18)
				{
					fighter[0].setHP(18);
				}
				else
				{
					fighter[0].setHP(life);
				}
			}
			
			losers.push(fighter[1]);
			team1.addBack(fighter[0]);
				
			break;
		}
		else
		{
//			cout << fighter[1].getName() << " has " << fighter[1].getHP() << " HP left!" <<endl;
//			cout << endl;
		}
		
		//Player 2 attacks, Player 1 defends.
		att = fighter[1].attack();		//calculates attack
		def = fighter[0].defend();		//calculates defense
		dam = att - def;
		
		if (fighter[0].getType() == 1)		//checks for Achilles attack
		{
			if (fighter[1].getType() != 1)
			{
				if (att == 12)
					{
						spec = fighter[0].getAttackDiceSides();
						if (spec >= 4)
						{
//							cout << "Achilles hit!" <<endl;
							spec = (spec/2);
							fighter[0].setAttackDiceSides(spec);
						}
					}
				}
			}
		
			if (fighter[0].getType() == 5)	//checks for special Shadow miss
			{
				spec = fighter[0].roll(2);
				if (spec == 1)
				{
					dam = 0;
//					cout << fighter[0].getName() << " wasn't there!" <<endl;
				}
			}
		
			if (dam < 0)					//checks for negative damage
				{
//					cout << fighter[0].getName() << " takes 0 damage!" <<endl;
					points = fighter[0].getPoints();
					points = (points + 5);
					fighter[0].setPoints(points);
				}
			else
				{
//					cout << fighter[0].getName() << " takes " << dam << " damage!" <<endl;
					points = fighter[1].getPoints();
					points = (points + (dam * 2));
					fighter[1].setPoints(points);
				}
			
			if (!fighter[0].damage(dam))
			{
				cout << fighter[0].getName() << " is dead!" <<endl;
				cout << fighter[1].getName() << " wins!" <<endl;
				cout <<endl;
				
				points = fighter[1].getPoints();
				points = (points + 50);
				fighter[1].setPoints(points);
				
				if ((fighter[0].getType() == 1) || (fighter[0].getType() == 4) || (fighter[0].getType() == 5))
				{
					life = (fighter[0].getHP() + 6);
					if (life>12)
					{
						fighter[0].setHP(12);
					}
					else
					{
						fighter[0].setHP(life);
					}
				}
				else if (fighter[0].getType() == 2)
				{
					life = (fighter[0].getHP() + 4);
					if (life>8)
					{
						fighter[0].setHP(8);
					}
					else
					{
						fighter[0].setHP(life);
					}
				}
				else
				{
					life = (fighter[0].getHP() + 9);
					if (life>18)
					{
						fighter[0].setHP(18);
					}
					else
					{
						fighter[0].setHP(life);
					}
				}
				
				losers.push(fighter[0]);
				team2.addBack(fighter[1]);
				
				break;
			}
			else
			{
//				cout << fighter[0].getName() << " has " << fighter[0].getHP() << " HP left!" <<endl;
//				cout << endl;
			}
		}
	
	}

	//tournament is over, time for awards!
	cout << "The tournament is over!" <<endl;
	if (team1.isEmpty())
	{cout << "Team 2 wins!" <<endl;}
	else
	{cout << "Team 1 wins!" <<endl;}
	
	while (team1.isEmpty() == false)
	{
		fighter[0] = team1.getFront();
		losers.push(fighter[0]);
		team1.removeFront();
	}
	while (team2.isEmpty() == false)
	{
		fighter[0] = team2.getFront();
		losers.push(fighter[0]);
		team2.removeFront();
	}
	
	rank1 = 0;
	rank2 = 0;
	rank3 = 0;
	
	while (losers.isEmpty() == false)
	{
		fighter[0] = losers.peek();
		temporary = fighter[0].getPoints();
		tempname = fighter[0].getName();
		losers.pop();
		
		if (temporary > rank3)
		{
			rank3 = temporary;
			ranked3 = tempname;
			if (rank3 > rank2)
			{
				temporary = rank2;
				tempname = ranked2;
				rank2 = rank3;
				ranked2 = ranked3;
				rank3 = temporary;
				ranked3 = tempname;
				
				if (rank2 > rank1)
				{
					temporary = rank1;
					tempname = ranked1;
					rank1 = rank2;
					ranked1 = ranked2;
					rank2 = temporary;
					ranked2 = tempname;
				}
				
			}
		}
	}
	cout <<"First Place: " << ranked1 << " with " << rank1 << " points." <<endl;
	cout <<"Second Place: " << ranked2 << " with " << rank2 << " points." <<endl;
	if (teamsize > 1)
	{
		cout <<"Third Place: " << ranked3 << " with " << rank3 << " points." <<endl;
	}
	
return 0;
}
