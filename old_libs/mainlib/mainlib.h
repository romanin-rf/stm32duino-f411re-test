#pragma once


/// @brief Getting the exact percentage of three numbers.
/// @param value The number from which to calculate the percentage.
/// @param min The minimum value of the number.
/// @param max The maximum value of the number.
/// @return The percent.
double getDoublePercent(const double value, const double min, const double max);
/// @brief Getting the exact percentage of three numbers. The minimum value is 0.
/// @param value The number from which to calculate the percentage.
/// @param max The maximum value of the number.
/// @return The percent.
double getDoublePercent(const double value, const double max);

/// @brief Getting a less accurate percentage of the number.
/// @param value The number from which to calculate the percentage.
/// @param min The minimum value of the number.
/// @param max The maximum value of the number.
/// @return The percent.
float getFloatPercent(const float value, const float min, const float max);
/// @brief Getting a less accurate percentage of the number. The minimum value is 0.
/// @param value The number from which to calculate the percentage.
/// @param max The maximum value of the number.
/// @return The percent.
float getFloatPercent(const float value, const float max);

/// @brief Getting an integer percentage from a value.
/// @param value The number from which to calculate the percentage.
/// @param min The minimum value of the number.
/// @param max The maximum value of the number.
/// @return The percent.
int getIntPercent(const int value, const int min, const int max);
/// @brief Getting an integer percentage from a value. The minimum value is 0.
/// @param value The number from which to calculate the percentage.
/// @param max The maximum value of the number.
/// @return The percent.
int getIntPercent(const int value, const int max);

/// @brief Calculating the temperature (in celsius) from an analog value.
/// @param value Analog value (0 <= value < 1024).
/// @return The temperature is in Celsius.
int getTempCelsiusFromAnalog(const int value);