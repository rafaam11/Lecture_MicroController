#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/camera.h>
#include <webots/utils/system.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define TIME_STEP 64

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SPEED 4
enum BLOB_TYPE { RED, GREEN, BLUE, NONE };

int main(int argc, char **argv) {

  double pi = 3.14159265358979;
  double g = 9800;
  double step = 40;

  double l2 = 120;
  double l3 = 140;

  double hf = 30;

  double Ltot = l2 + l3;
  double L0 = Ltot - hf;
  double w = sqrt(g / L0);

  double f = w / (2 * pi);
  double Ts = (1 / f);



  double amp = 20;

  double LFth2value = 0, LFth3value = 0, RFth2value = 0, RFth3value = 0, LRth2value = 0, LRth3value = 0, RRth2value = 0, RRth3value = 0;
  double xLF = 0; double xRF = 0; double xLR = 0; double xRR = 0;
  double zLF; double zRF; double zLR; double zRR;
  double dLF; double dRF; double dLR; double dRR;
  double t, tloop;

  double x0, xv0;
  x0 = (-step / 2);
  xv0 = (1 + exp(w * Ts)) / (1 - exp(w * Ts)) * w * x0;

  double c1, c2;
  c1 = 0.5 * (x0 + (1 / w) * xv0);
  c2 = 0.5 * (x0 - (1 / w) * xv0);

  double u[0];

  WbDeviceTag camera;

  int width, height;
  int pause_counter = 0;
  int left_speed, right_speed;
  int i, j;
  int red, blue, green;
  const char *color_names[3] = {"red", "green", "blue"};
  const char *ansi_colors[3] = {ANSI_COLOR_RED, ANSI_COLOR_GREEN, ANSI_COLOR_BLUE};
  const char *filenames[3] = {"red_blob.png", "green_blob.png", "blue_blob.png"};
  enum BLOB_TYPE current_blob;

  wb_robot_init();

  const int time_step = wb_robot_get_basic_time_step();
  camera = wb_robot_get_device("camera");
  wb_camera_enable(camera, time_step);
  width = wb_camera_get_width(camera);
  height = wb_camera_get_height(camera);
  WbDeviceTag LRth2 = wb_robot_get_device("left back motor2");
  WbDeviceTag LRth3 = wb_robot_get_device("left back motor1");
  WbDeviceTag RRth2 = wb_robot_get_device("right back motor2");
  WbDeviceTag RRth3 = wb_robot_get_device("right back motor1");
  WbDeviceTag LFth2 = wb_robot_get_device("left front motor2");
  WbDeviceTag LFth3 = wb_robot_get_device("left front motor1");
  WbDeviceTag RFth2 = wb_robot_get_device("right front motor2");
  WbDeviceTag RFth3 = wb_robot_get_device("right front motor1");

  while (wb_robot_step(40) != -1) { //시뮬레이션을 사용자가 끝을 낼때까지 진행
    printf("Ltot=%f\nL0=%f\nw=%f\nf=%f\nTs=%f\n", Ltot, L0, w, f, Ts);

    const unsigned char *image = wb_camera_get_image(camera);

    u[0] = wb_robot_get_time(); //시뮬레이션 시간을 얻어오기(리커다인에서 u[0]를 대체)
    printf("u[0]=%f\n", u[0]);
    if (u[0] >= 0 && u[0] < Ts / 2) {

      printf("u[0]>0&&u[0]<Ts/2\n");
      zLF = (l2 + l3) + (2 * (L0 - l2 - l3) / Ts) * u[0];
      dLF = (xLF * xLF + zLF * zLF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      zRF = (l2 + l3) + (2 * (L0 - l2 - l3) / Ts) * u[0];
      dRF = (xRF * xRF + zRF * zRF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      zLR = (l2 + l3) + (2 * (L0 - l2 - l3) / Ts) * u[0];
      dLR = (xLR * xLR + zLR * zLR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      zRR = (l2 + l3) + (2 * (L0 - l2 - l3) / Ts) * u[0];
      dRR = (xRR * xRR + zRR * zRR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      printf("zLF=%f\ndLF=%f\nzRF=%f\ndRF=%f\nzLR=%f\ndLR=%f\nzRR=%f\ndRR=%f\n",
             zLF, dLF, zRF, dRF, zLR, dLR, zRR, dRR);


      if (dRF >= -1 && dRF <= 1) {
        LFth3value = -atan2(-sqrt(1 - dLF * dLF), dLF); //LFth3가 리커다인과 다른방향으로 작용하여 -를 추가하여 반대방향으로 작용하도록 설정.
        LFth2value = (atan2(zLF, xLF) - atan2(l3 * sin(LFth3value), (l2 + l3 * cos(LFth3value))) - pi / 2);
        LRth3value = -atan2(sqrt(1 - dLR * dLR), dLR); //LRth3가 리커다인과 다른방향으로 작용하여 -를 추가하여 반대방향으로 작용하도록 설정.
        LRth2value = atan2(zLR, xLR) - atan2(l3 * sin(LRth3value), (l2 + l3 * cos(LRth3value))) - pi / 2;
        RFth3value = atan2(sqrt(1 - dRF * dRF), dRF);
        RFth2value = atan2(zRF, xRF) - atan2(l3 * sin(RFth3value), (l2 + l3 * cos(RFth3value))) - pi / 2;
        RRth3value = atan2(-sqrt(1 - dRR * dRR), dRR);
        RRth2value = (atan2(zRR, xRR) - atan2(l3 * sin(RRth3value), (l2 + l3 * cos(RRth3value))) - pi / 2);
        printf("LFth2=%f\nLFth3=%f\nLRth2=%f\nLRth3=%f\nRFth2=%f\nRFth3=%f\nRRth2=%f\nRRth3=%f\n",
               LFth2value, LFth3value, LRth2value, LRth3value, RFth2value, RFth3value, RRth2value, RRth3value);
      }
      wb_motor_set_position(LFth2, LFth2value);
      wb_motor_set_position(LFth3, LFth3value);
      wb_motor_set_position(LRth2, LRth2value);
      wb_motor_set_position(LRth3, LRth3value);

      wb_motor_set_position(RFth2, RFth2value);
      wb_motor_set_position(RFth3, RFth3value);
      wb_motor_set_position(RRth2, RRth2value);
      wb_motor_set_position(RRth3, RRth3value);

      wb_motor_set_velocity(LFth2, 1);
      wb_motor_set_velocity(LFth3, 1);
      wb_motor_set_velocity(LRth2, 1);
      wb_motor_set_velocity(LRth3, 1);
      wb_motor_set_velocity(RFth2, 1);
      wb_motor_set_velocity(RFth3, 1);
      wb_motor_set_velocity(RRth2, 1);
      wb_motor_set_velocity(RRth3, 1);


    }

    else if (u[0] > Ts / 2 && u[0] < Ts) {
      t = u[0] - Ts / 2;
      printf("u[0]>Ts/2&&u[0]<Ts\n");
      xLF = (c1 * exp(w * (t + Ts / 2)) + c2 * exp(-w * (t + Ts / 2))) * -1;
      xRF = (-step / Ts) * t;
      xLR = xRF * -1;
      xRR = (c1 * exp(w * (t + Ts / 2)) + c2 * exp(-w * (t + Ts / 2)));

      zLF = L0;
      zRF = L0 - amp * 0.5 * sin(w * t);
      zLR = zRF;
      zRR = zLF;

      dLF = (xLF * xLF + zLF * zLF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      dRF = (xRF * xRF + zRF * zRF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      dLR = (xLR * xLR + zLR * zLR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
      dRR = (xRR * xRR + zRR * zRR - l2 * l2 - l3 * l3) / (2 * l2 * l3);

      if (dLF >= -1 && dLF <= 1) {
        LFth3value = -atan2(-sqrt(1 - dLF * dLF), dLF);
        LFth2value = atan2(zLF, xLF) - atan2(l3 * sin(LFth3value), (l2 + l3 * cos(LFth3value))) - pi / 2;
      }

      if (dRF >= -1 && dRF <= 1) {
        RFth3value = atan2(sqrt(1 - dRF * dRF), dRF);
        RFth2value = atan2(zRF, xRF) - atan2(l3 * sin(RFth3value), (l2 + l3 * cos(RFth3value))) - pi / 2;
      }

      if (dLR >= -1 && dLR <= 1) {
        LRth3value = -atan2(sqrt(1 - dLR * dLR), dLR);
        LRth2value = atan2(zRF, xLR) - atan2(l3 * sin(LRth3value), (l2 + l3 * cos(LRth3value))) - pi / 2;
      }

      if (dRR >= -1 && dRR <= 1) {
        RRth3value = atan2(-sqrt(1 - dRR * dRR), dRR);
        RRth2value = atan2(zRR, xRR) - atan2(l3 * sin(RRth3value), (l2 + l3 * cos(RRth3value))) - pi / 2;
      }
      printf("LFth2=%f\nLFth3=%f\nLRth2=%f\nLRth3=%f\nRFth2=%f\nRFth3=%f\nRRth2=%f\nRRth3=%f\n",
             LFth2value, LFth3value, LRth2value, LRth3value, RFth2value, RFth3value, RRth2value, RRth3value);

      wb_motor_set_position(LFth2, LFth2value);
      wb_motor_set_position(LFth3, LFth3value);

      wb_motor_set_position(LRth2, LRth2value);
      wb_motor_set_position(LRth3, LRth3value);

      wb_motor_set_position(RFth2, RFth2value);
      wb_motor_set_position(RFth3, RFth3value);
      wb_motor_set_position(RRth2, RRth2value);
      wb_motor_set_position(RRth3, RRth3value);

      wb_motor_set_velocity(LFth2, 1);
      wb_motor_set_velocity(LFth3, 1);
      wb_motor_set_velocity(LRth2, 1);
      wb_motor_set_velocity(LRth3, 1);
      wb_motor_set_velocity(RFth2, 1);
      wb_motor_set_velocity(RFth3, 1);
      wb_motor_set_velocity(RRth2, 1);
      wb_motor_set_velocity(RRth3, 1);

    }

    else if (u[0] >= Ts) {
      tloop = fmod((u[0] - Ts), Ts * 2);

      if (tloop >= 0 && tloop < Ts) {
        t = tloop;
        xRF = (c1 * exp(w * t) + c2 * exp(-w * t));
        xLF = -((step / Ts) * t - (step / 2)); //LF움직임이 반대로 움직여서 -를 추가하여 반대방향으로 움직이도록 설정.
        xRR = xRF * -1;
        xLR = (c1 * exp(w * t) + c2 * exp(-w * t)) * -1;
        zRF = L0;
        zLF = L0 - amp * sin(w * t * 0.5);
        zRR = zLF;
        zLR = zRF;
        dLF = (xLF * xLF + zLF * zLF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dRF = (xRF * xRF + zRF * zRF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dLR = (xLR * xLR + zLR * zLR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dRR = (xRR * xRR + zRR * zRR - l2 * l2 - l3 * l3) / (2 * l2 * l3);

        if (dLF >= -1 && dLF <= 1) {
          LFth3value = atan2(sqrt(1 - dLF * dLF), dLF);
          LFth2value = (atan2(zLF, xLF) - atan2(l3 * sin(LFth3value), (l2 + l3 * cos(LFth3value))) - pi / 2);

        }
        if (dRF >= -1 && dRF <= 1) {
          RFth3value = atan2(sqrt(1 - dRF * dRF), dRF);
          RFth2value = (atan2(zRF, xRF) - atan2(l3 * sin(RFth3value), (l2 + l3 * cos(RFth3value))) - pi / 2);
        }

        if (dLR >= -1 && dLR <= 1) {
          LRth3value = -atan2(sqrt(1 - dLR * dLR), dLR);
          LRth2value = atan2(zRF, xLR) - atan2(l3 * sin(LRth3value), (l2 + l3 * cos(LRth3value))) - pi / 2;
        }

        if (dRR >= -1 && dRR <= 1) {
          RRth3value = atan2(-sqrt(1 - dRR * dRR), dRR);
          RRth2value = (atan2(zRR, xRR) - atan2(-l3 * sin(-RRth3value), (l2 + l3 * cos(RRth3value))) - pi / 2);
        }
        printf("LFth2=%f\nLFth3=%f\nLRth2=%f\nLRth3=%f\nRFth2=%f\nRFth3=%f\nRRth2=%f\nRRth3=%f\n",
               LFth2value, LFth3value, LRth2value, LRth3value, RFth2value, RFth3value, RRth2value, RRth3value);

        wb_motor_set_position(LFth2, LFth2value);
        wb_motor_set_position(LFth3, LFth3value);


        wb_motor_set_position(LRth2, LRth2value);
        wb_motor_set_position(LRth3, LRth3value);

        wb_motor_set_position(RFth2, RFth2value);
        wb_motor_set_position(RFth3, RFth3value);

        wb_motor_set_position(RRth2, RRth2value);
        wb_motor_set_position(RRth3, RRth3value);

        wb_motor_set_velocity(LFth2, 1);
        wb_motor_set_velocity(LFth3, 1);
        wb_motor_set_velocity(LRth2, 1);
        wb_motor_set_velocity(LRth3, 1);
        wb_motor_set_velocity(RFth2, 1);
        wb_motor_set_velocity(RFth3, 1);
        wb_motor_set_velocity(RRth2, 1);
        wb_motor_set_velocity(RRth3, 1);
      }

      else if (tloop >= Ts && tloop < 2 * Ts) {
        t = tloop - Ts;
        xRR = (c1 * exp(w * t) + c2 * exp(-w * t));
        xLR = -((step / Ts) * t - (step / 2)); //LR움직임이 반대로 움직여서 -를 추가하여 반대방향으로 움직이도록 설정.
        xRF = xRR * -1;
        xLF = (c1 * exp(w * t) + c2 * exp(-w * t)) * -1;
        zLF = L0;
        zRF = L0 - amp * sin(w * t * 0.5);
        zLR = zRF;
        zRR = zLF;
        dLF = (xLF * xLF + zLF * zLF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dRF = (xRF * xRF + zRF * zRF - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dLR = (xLR * xLR + zLR * zLR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        dRR = (xRR * xRR + zRR * zRR - l2 * l2 - l3 * l3) / (2 * l2 * l3);
        if (dLF >= -1 && dLF <= 1)
        {
          LFth3value = -atan2(-sqrt(1 - dLF * dLF), dLF);
          LFth2value = atan2(zLF, xLF) - atan2(l3 * sin(LFth3value), (l2 + l3 * cos(LFth3value))) - pi / 2;
        }
        if (dRF >= -1 && dRF <= 1)
        {
          RFth3value = atan2(sqrt(1 - dRF * dRF), dRF);
          RFth2value = atan2(zRF, xRF) - atan2(l3 * sin(RFth3value), (l2 + l3 * cos(RFth3value))) - pi / 2;
        }

        if (dLR >= -1 && dLR <= 1)
        {
          LRth3value = -atan2(sqrt(1 - dLR * dLR), dLR);
          LRth2value = atan2(zRF, xLR) - atan2(l3 * sin(LRth3value), (l2 + l3 * cos(LRth3value))) - pi / 2;
        }

        if (dRR >= -1 && dRR <= 1)
        {
          RRth3value = atan2(-sqrt(1 - dRR * dRR), dRR);
          RRth2value = atan2(zRR, xRR) - atan2(l3 * sin(RRth3value), (l2 + l3 * cos(RRth3value))) - pi / 2;
        }

        wb_motor_set_position(LFth2, LFth2value);
        wb_motor_set_position(LFth3, LFth3value);

        wb_motor_set_position(LRth2, LRth2value);
        wb_motor_set_position(LRth3, LRth3value);

        wb_motor_set_position(RFth2, RFth2value);
        wb_motor_set_position(RFth3, RFth3value);
        wb_motor_set_position(RRth2, RRth2value);
        wb_motor_set_position(RRth3, RRth3value);

        wb_motor_set_velocity(LFth2, 1);
        wb_motor_set_velocity(LFth3, 1);
        wb_motor_set_velocity(LRth2, 1);
        wb_motor_set_velocity(LRth3, 1);
        wb_motor_set_velocity(RFth2, 1);
        wb_motor_set_velocity(RFth3, 1);
        wb_motor_set_velocity(RRth2, 1);
        wb_motor_set_velocity(RRth3, 1);
      }

    }

  }

























  wb_robot_cleanup();
  return 0;

}
