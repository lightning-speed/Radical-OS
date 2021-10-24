#pragma once

void Sleepd(double seconds);
void Sleep(long long milliseconds);

void SetDivisor(int divisor);
long long GetFrequency();
void SetFrequency(long long frequency);
void Tick();
void timer_handler();
double get_time_since_boot();
