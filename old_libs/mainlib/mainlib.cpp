#include <mainlib.h>


double getDoublePercent(const double value, const double min, const double max) {
    return (value / (max-min)) * 100.0;
};
double getDoublePercent(const double value, const double max) {
    return (value / max) * 100.0;
};

float getFloatPercent(const float value, const float min, const float max) {
    return (value / (max-min)) * 100.0f;
};
float getFloatPercent(const float value, const float max) {
    return (value / max) * 100.0f;
};

int getIntPercent(const int value, const int min, const int max) {
    return (float(value) / (float(max)-float(min))) * 100.0f;
};
int getIntPercent(const int value, const int max) {
    return (float(value) / float(max)) * 100.0f;
};


int getTempCelsiusFromAnalog(const int value) {
    return (((double(value) * 5.0) / 1024.0) - 0.5) * 100.0;
};