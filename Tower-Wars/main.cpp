#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>

using namespace std;

ifstream f("date.in");

/// Level 3 Catalysts-Contest ...

struct alienInfo{
  int x_position;
  int y_position;
  double speedAlien;
  int timeUntilSpawn;
  int directionToMove;
};
vector < alienInfo > aliensInformation;
int wx, wy; /// Matrix max dimension;
int x, y; /// Alien spawn position;

vector <string> Movement_Sequence;

double speed;
int numberOfAliens;

vector < int > timeUntilSpawn_Aliens;

int querries;

void rotate(int steps, int &direction)
  {
    direction += steps;
  }

void forward_move(int steps, int &x_pos, int &y_pos, int &direction, int &totalTime)
{
  if ( direction % 4 == 0 )
    if ( x_pos + steps <= wx )
      x_pos += steps;
    else
      {
        x_pos = wx;
        totalTime += (steps - wx);
      }
  if ( direction % 4 == 1 )
    if ( y_pos + steps <= wy )
      y_pos += steps;
    else
      {
        y_pos = wx;
        totalTime += (steps - wy);
      }
  if ( direction % 4 == 2 )
    if ( x_pos - steps >= 0)
      x_pos -= steps;
    else
      {
        totalTime += ( steps - x_pos );
        x_pos = 0;
      }
  if ( direction % 4 == 3 )
    if ( y_pos - steps >= 0 )
      y_pos -= steps;
    else
      {
        totalTime += ( steps - y_pos );
        y_pos = 0;
      }
}
void readDataAndResolve(){
  f >> wx >> wy >> x >> y;
  f.ignore();
  for(string aux; f >> aux; )
  {
    Movement_Sequence.push_back(aux);
    if(f.peek() == '\n')break;
  }
  f >> speed;
  f >> numberOfAliens;
  for ( int i = 0 ; i < numberOfAliens ; ++i )
  {
    int aux;
    f >> aux;
    alienInfo data;
    data.speedAlien = speed;
    data.x_position = x;
    data.y_position = y;
    data.timeUntilSpawn = aux;
    data.directionToMove = 0;
    aliensInformation.push_back(data);
  }

  f >> querries;

  for ( int i = 0 ; i < querries ; ++i )
  {
    int timeGiven, id;
    f >> timeGiven >> id;

    int totalTime_forAction = (timeGiven - aliensInformation[id].timeUntilSpawn) * aliensInformation[id].speedAlien;
    cin.get();
    int x_position = x;
    int y_position = y;
    int iterator = 0;
    while ( totalTime_forAction > 0 && iterator != Movement_Sequence.size())
    {
      //cout << id << " " << aliensInformation[id].x_position << " " << aliensInformation[id].y_position << endl << totalTime_forAction << endl;
      //cin.get();

        if (Movement_Sequence[iterator] == "F" )
        {
          if (totalTime_forAction -  stoi (Movement_Sequence[iterator+1]) >= 0 )
          {
            forward_move(stoi (Movement_Sequence[iterator+1]), aliensInformation[id].x_position, aliensInformation[id].y_position, aliensInformation[id].directionToMove, totalTime_forAction );
            totalTime_forAction -= stoi (Movement_Sequence[iterator+1]);
          }
          else
          {
            forward_move(totalTime_forAction, aliensInformation[id].x_position, aliensInformation[id].y_position, aliensInformation[id].directionToMove,totalTime_forAction);
            totalTime_forAction = 0;
          }
        }
        else
        {
          rotate(stoi (Movement_Sequence[iterator+1]), aliensInformation[id].directionToMove);
        }
        iterator += 2;
    }

    cout << timeGiven << " " << id << " " <<  aliensInformation[id].x_position << " " << aliensInformation[id].y_position << endl;
    aliensInformation[id].x_position = x;
    aliensInformation[id].y_position = y;
    aliensInformation[id].directionToMove = 0;
  }


}
int main()
{
  readDataAndResolve();
}
