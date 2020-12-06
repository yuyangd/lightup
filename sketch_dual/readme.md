# 2 x ultrasonic sensors at each end of stairs

Assumption, one person pass through the stairs at a time

Sensor 1, 2 -> on

sensor 4, 3 -> on

led 1, 2, 3 on the stairs
ledx indicating someone detected by first sensor

s0

sensor1 detect -> s1

sensor4 detect -> s2

s1
act_timer for sensor1
-> s3

s2
act_timer for sensor4
-> s4

s3
sensor2 detect within timer -> s5
otherwise -> s7

s4
sensor3 detect within timer -> s6
otherwise -> s8
