#include "game.h"
#include "constants.h"
#include <stdint.h>

//All game code goes here

int p1 = 0;
int p2 = 25;
int bx = 10;
int by = 10;

int pos_velocity_x = 32768; // (1 << 15)
int pos_velocity_y = 32768;
int neg_velocity_x = 32768; // (1 << 15)
int neg_velocity_y = 32768;// subtract negative velocities

uint8_t velocity_flag = 3; //(xxxx xx(x)(y)
//0 is neg x, neg y
//1 is neg x, pos y
//2 is pos x, neg y
//3 is pos x, pos y
int real_bx = bx * (1 << 16);
int real_by = by * (1 << 16);

uint8_t button_status = 0;
//would like an byte
//xxxx (p1Up)(p2Up)(p1Down)(p2Down)


void update_movement(){
  if((button_status & (1 << 3)) && p1 >= 0){
    p1 = p1 - 1;
  }
  if((button_status & (1 << 1)) && p1 < B_HEIGHT - P_HEIGHT ){
    p1 = p1 +1;
  }
  if((button_status & (1 << 2)) && p2 >= 0){
    p2 = p2-1;
  }
  if((button_status & 1) && p2 < P_HEIGHT - P_OFFSET){
    p2 = p2 +1;
  }
}
void run_deflection(bool is_player1){
  velocity_flag ^= 2;
}
int tempx;
void update_ball_position(){
  switch(velocity_flag){
    case 0:
      real_bx = real_bx - neg_velocity_x;
      real_by = real_by - neg_velocity_y;
      break;
    case 1:
      real_bx = real_bx - neg_velocity_x;
      real_by = real_by + pos_velocity_y;
      break;
    case 2:
      real_bx = real_bx + pos_velocity_x;
      real_by = real_by - neg_velocity_y;
      break;
    case 3:
      real_bx = real_bx + pos_velocity_x;
      real_by = real_by + pos_velocity_y;
      break;
  }
  tempx = bx;
  bx = real_bx >> 16;
  by = real_by >> 16;
  //check deflection
  if(tempx >= P_OFFSET && bx <= P_OFFSET && by>= p1 && by <= p1+P_HEIGHT ){
    run_deflection(true);
    return;
  }
  if(tempx >= B_WIDTH - P_OFFSET && bx <= B_WIDTH && by>= p2 && by <= p2+P_HEIGHT ){
    run_deflection(false);
    return;
  }
  
}

void update_ball_velocity(){
  if(by < 0 || by >30){
    velocity_flag ^= 1;
  }
  if(bx < 0 || by > 30){
    velocity_flag ^= 2;
  }
  
}
void game_init() {
  p1 = 15;
  p2 = 15;
   
}

void game_update() {
    update_movement();
    update_ball_velocity();
    update_ball_position();
}
