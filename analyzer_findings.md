# Static Analyzer (-fanalyzer) Findings Report (Excluding HTTPD)

The static analyzer was run on the ESP32 project using the GCC 12 toolchain. A total of **109** unique warnings were identified in the project's codebase (excluding the HTTPD server library).

## Summary of Warnings by File

| File | Warnings Count |
| --- | --- |
| [FreematicsGPS.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp) | 14 |
| [FreematicsMEMS.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp) | 59 |
| [FreematicsMEMS.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h) | 4 |
| [FreematicsNetwork.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp) | 17 |
| [FreematicsOBD.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp) | 4 |
| [FreematicsOBD.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.h) | 1 |
| [FreematicsPlus.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp) | 2 |
| [ICM_20948_C.c](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c) | 2 |
| [telelogger.ino](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino) | 6 |

## Detailed Findings

### File: [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp)

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 348)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:348](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L348)
- **Column:** 10
- **Analysis Context & Path:**
```text
348 |   if (a2 < 0.0)
|       ~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 350)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:350](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L350)
- **Column:** 8
- **Analysis Context & Path:**
```text
350 |     a2 += TWO_PI;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 393)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:393](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L393)
- **Column:** 40
- **Analysis Context & Path:**
```text
393 |   *latitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lat / 100000.0);
|               ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 394)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:394](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L394)
- **Column:** 41
- **Analysis Context & Path:**
```text
394 |   *longitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lon / 100000.0);
|                ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_altitude()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 417)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:417](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L417)
- **Column:** 44
- **Analysis Context & Path:**
```text
417 |   return _altitude == GPS_INVALID_ALTITUDE ? GPS_INVALID_F_ALTITUDE : _altitude / 100.0;
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_course()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 422)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:422](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L422)
- **Column:** 39
- **Analysis Context & Path:**
```text
422 |   return _course == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : _course / 100.0;
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_speed_knots()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 427)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:427](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L427)
- **Column:** 38
- **Analysis Context & Path:**
```text
427 |   return _speed == GPS_INVALID_SPEED ? GPS_INVALID_F_SPEED : _speed / 100.0;
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_speed_mph()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 433)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:433](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L433)
- **Column:** 78
- **Analysis Context & Path:**
```text
433 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPH_PER_KNOT * f_speed_knots();
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 433)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:433](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L433)
- **Column:** 36
- **Analysis Context & Path:**
```text
433 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPH_PER_KNOT * f_speed_knots();
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_speed_mps()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 439)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:439](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L439)
- **Column:** 78
- **Analysis Context & Path:**
```text
439 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPS_PER_KNOT * f_speed_knots();
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 439)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:439](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L439)
- **Column:** 36
- **Analysis Context & Path:**
```text
439 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPS_PER_KNOT * f_speed_knots();
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'float TinyGPS::f_speed_kmph()':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 445)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:445](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L445)
- **Column:** 79
- **Analysis Context & Path:**
```text
445 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_KMPH_PER_KNOT * f_speed_knots();
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other result of conditional [-Wdouble-promotion] (Line 445)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:445](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L445)
- **Column:** 36
- **Analysis Context & Path:**
```text
445 |   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_KMPH_PER_KNOT * f_speed_knots();
|          ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp: In member function 'bool TinyGPS::encode(char)':
```

---

#### ⚠️ this statement may fall through [-Wimplicit-fallthrough=] (Line 65)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:65](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp#L65)
- **Column:** 13
- **Analysis Context & Path:**
```text
65 |     _parity ^= ',';
|     ~~~~~~~~^~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsGPS.cpp:66:3: note: here
66 |   case '\r':
|   ^~~~
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp)

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 121)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:121](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L121)
- **Column:** 124
- **Analysis Context & Path:**
```text
121 |      ori->yaw  = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]) * 180.0f / PI;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 122)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:122](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L122)
- **Column:** 70
- **Analysis Context & Path:**
```text
122 |      ori->pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2])) * 180.0f / PI;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 123)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:123](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L123)
- **Column:** 125
- **Analysis Context & Path:**
```text
123 |      ori->roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]) * 180.0f / PI;
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'bool MPU9250::initAK8963(float*)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 230)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:230](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L230)
- **Column:** 46
- **Analysis Context & Path:**
```text
230 |   destination[0] =  (float)(rawData[0] - 128)/256. + 1.;   // Return x-axis sensitivity adjustment values, etc.
|                     ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 231)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:231](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L231)
- **Column:** 46
- **Analysis Context & Path:**
```text
231 |   destination[1] =  (float)(rawData[1] - 128)/256. + 1.;
|                     ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 232)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:232](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L232)
- **Column:** 46
- **Analysis Context & Path:**
```text
232 |   destination[2] =  (float)(rawData[2] - 128)/256. + 1.;
|                     ~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'void MPU9250::calibrateMPU9250(float*, float*)':
```

---

#### ⚠️ declaration of 'accelBias' shadows a member of 'MPU9250' [-Wshadow] (Line 246)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:246](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L246)
- **Column:** 58
- **Analysis Context & Path:**
```text
246 | void MPU9250::calibrateMPU9250(float * gyroBias, float * accelBias)
|                                                  ~~~~~~~~^~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:280:9: note: shadowed declaration is here
280 |   float accelBias[3] = {0};      // Bias corrections for gyro and accelerometer
|         ^~~~~~~~~
```

---

#### ⚠️ declaration of 'gyroBias' shadows a member of 'MPU9250' [-Wshadow] (Line 246)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:246](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L246)
- **Column:** 40
- **Analysis Context & Path:**
```text
246 | void MPU9250::calibrateMPU9250(float * gyroBias, float * accelBias)
|                                ~~~~~~~~^~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:279:9: note: shadowed declaration is here
279 |   float gyroBias[3] = {0};
|         ^~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'void MPU9250::MPU9250SelfTest(float*)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 465)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:465](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L465)
- **Column:** 73
- **Analysis Context & Path:**
```text
465 |   factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 466)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:466](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L466)
- **Column:** 73
- **Analysis Context & Path:**
```text
466 |   factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 467)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:467](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L467)
- **Column:** 73
- **Analysis Context & Path:**
```text
467 |   factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 468)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:468](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L468)
- **Column:** 73
- **Analysis Context & Path:**
```text
468 |   factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 469)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:469](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L469)
- **Column:** 73
- **Analysis Context & Path:**
```text
469 |   factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 470)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:470](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L470)
- **Column:** 73
- **Analysis Context & Path:**
```text
470 |   factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation
|                                                      ~~~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 475)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:475](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L475)
- **Column:** 29
- **Analysis Context & Path:**
```text
475 |     destination[i]   = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i];   // Report percent differences
|                        ~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 476)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:476](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L476)
- **Column:** 29
- **Analysis Context & Path:**
```text
476 |     destination[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3]; // Report percent differences
|                        ~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 686)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:686](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L686)
- **Column:** 34
- **Analysis Context & Path:**
```text
686 |     acc[0] = (float)accelCount[0]*aRes; // - accelBias[0];  // get actual g value, this depends on scale being set
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 687)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:687](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L687)
- **Column:** 34
- **Analysis Context & Path:**
```text
687 |     acc[1] = (float)accelCount[1]*aRes; // - accelBias[1];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 688)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:688](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L688)
- **Column:** 34
- **Analysis Context & Path:**
```text
688 |     acc[2] = (float)accelCount[2]*aRes; // - accelBias[2];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 692)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:692](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L692)
- **Column:** 33
- **Analysis Context & Path:**
```text
692 |     gyr[0] = (float)gyroCount[0]*gRes;  // get actual gyro value, this depends on scale being set
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 693)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:693](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L693)
- **Column:** 33
- **Analysis Context & Path:**
```text
693 |     gyr[1] = (float)gyroCount[1]*gRes;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 694)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:694](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L694)
- **Column:** 33
- **Analysis Context & Path:**
```text
694 |     gyr[2] = (float)gyroCount[2]*gRes;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 705)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:705](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L705)
- **Column:** 32
- **Analysis Context & Path:**
```text
705 |     mag[0] = (float)magCount[0]*mRes*magCalibration[0] - magbias[0];  // get actual magnetometer value, this depends on scale being set
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 706)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:706](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L706)
- **Column:** 32
- **Analysis Context & Path:**
```text
706 |     mag[1] = (float)magCount[1]*mRes*magCalibration[1] - magbias[1];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 707)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:707](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L707)
- **Column:** 32
- **Analysis Context & Path:**
```text
707 |     mag[2] = (float)magCount[2]*mRes*magCalibration[2] - magbias[2];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 711)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:711](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L711)
- **Column:** 22
- **Analysis Context & Path:**
```text
711 |     *temp = (float)t / 333.87 + 21;
|             ~~~~~~~~~^~~~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 715)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:715](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L715)
- **Column:** 71
- **Analysis Context & Path:**
```text
715 |     quaterion->MadgwickQuaternionUpdate(acc[0], acc[1], acc[2], gyr[0]*PI/180.0f, gyr[1]*PI/180.0f, gyr[2]*PI/180.0f,  mag[0],  mag[1], mag[2]);
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 836)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:836](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L836)
- **Column:** 34
- **Analysis Context & Path:**
```text
836 |     acc[0] = (float)accelCount[0]*aRes; // - accelBias[0];  // get actual g value, this depends on scale being set
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 837)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:837](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L837)
- **Column:** 34
- **Analysis Context & Path:**
```text
837 |     acc[1] = (float)accelCount[1]*aRes; // - accelBias[1];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 838)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:838](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L838)
- **Column:** 34
- **Analysis Context & Path:**
```text
838 |     acc[2] = (float)accelCount[2]*aRes; // - accelBias[2];
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 843)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:843](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L843)
- **Column:** 33
- **Analysis Context & Path:**
```text
843 |     gyr[0] = (float)gyroCount[0]*gRes;  // get actual gyro value, this depends on scale being set
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 844)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:844](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L844)
- **Column:** 33
- **Analysis Context & Path:**
```text
844 |     gyr[1] = (float)gyroCount[1]*gRes;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 845)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:845](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L845)
- **Column:** 33
- **Analysis Context & Path:**
```text
845 |     gyr[2] = (float)gyroCount[2]*gRes;
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 848)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:848](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L848)
- **Column:** 35
- **Analysis Context & Path:**
```text
848 |     *temp = (float)readTempData() / 132.48 + 25.0;
|             ~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'float ICM_20948::getMagUT(int16_t)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 923)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:923](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L923)
- **Column:** 30
- **Analysis Context & Path:**
```text
923 |     return (((float)axis_val)*0.15);
|             ~~~~~~~~~~~~~~~~~^~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'float ICM_20948::getAccMG(int16_t)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 940)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:940](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L940)
- **Column:** 43
- **Analysis Context & Path:**
```text
940 |         case 0 : return (((float)axis_val)/16.384); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 941)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:941](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L941)
- **Column:** 43
- **Analysis Context & Path:**
```text
941 |         case 1 : return (((float)axis_val)/8.192); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 942)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:942](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L942)
- **Column:** 43
- **Analysis Context & Path:**
```text
942 |         case 2 : return (((float)axis_val)/4.096); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 943)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:943](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L943)
- **Column:** 43
- **Analysis Context & Path:**
```text
943 |         case 3 : return (((float)axis_val)/2.048); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'float ICM_20948::getGyrDPS(int16_t)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 963)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:963](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L963)
- **Column:** 43
- **Analysis Context & Path:**
```text
963 |         case 1 : return (((float)axis_val)/65.5); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 964)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:964](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L964)
- **Column:** 43
- **Analysis Context & Path:**
```text
964 |         case 2 : return (((float)axis_val)/32.8); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 965)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:965](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L965)
- **Column:** 43
- **Analysis Context & Path:**
```text
965 |         case 3 : return (((float)axis_val)/16.4); break;
|                          ~~~~~~~~~~~~~~~~~^~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'float ICM_20948::getTempC(int16_t)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 975)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:975](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L975)
- **Column:** 25
- **Analysis Context & Path:**
```text
975 |     return (((float)val)/333.87) + 21;
|             ~~~~~~~~~~~~^~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'virtual bool ICM_20948_I2C::read(float*, float*, float*, float*, ORIENTATION*)':
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 1559)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:1559](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L1559)
- **Column:** 71
- **Analysis Context & Path:**
```text
1559 |     quaterion->MadgwickQuaternionUpdate(acc[0], acc[1], acc[2], gyr[0]*PI/180.0f, gyr[1]*PI/180.0f, gyr[2]*PI/180.0f,  mag[0],  mag[1], mag[2]);
```

---

#### ⚠️ use of uninitialized value 'data[0]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 290)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:290](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L290)
- **Column:** 33
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
290 |   fifo_count = ((uint16_t)data[0] << 8) | data[1];
|                           ~~~~~~^
'byte MPU9250::_ZN7MPU92505beginEb$part$0(bool)': events 1-4
|
|  659 | byte MPU9250::begin(bool fusion)
|      |      ^~~~~~~
|      |      |
|      |      (1) entry to 'MPU9250::_ZN7MPU92505beginEb$part$0'
|......
|  663 |   for (byte attempt = 0; attempt < 2; attempt++) {
|      |                          ~~~~~~~~~~~
|      |                                  |
|      |                                  (2) following 'true' branch (when 'attempt != 2')...
|......
|  666 |     byte c = readByte(WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
|      |     ~~~~
|      |     |
|      |     (3) ...to here
|  667 |     if (c != 0x68 && c != 0x71) continue;
|  668 |     calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
|      |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                     |
|      |                     (4) calling 'MPU9250::calibrateMPU9250' from 'MPU9250::_ZN7MPU92505beginEb$part$0'
|
+--> 'void MPU9250::calibrateMPU9250(float*, float*)': events 5-7
|
|  246 | void MPU9250::calibrateMPU9250(float * gyroBias, float * accelBias)
|      |      ^~~~~~~
|      |      |
|      |      (5) entry to 'MPU9250::calibrateMPU9250'
|  247 | {
|  248 |   uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
|      |           ~~~~
|      |           |
|      |           (6) region created on stack here
|......
|  288 |   readBytes(FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
|      |   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |            |
|      |            (7) calling 'MPU9250::readBytes' from 'MPU9250::calibrateMPU9250'
|
+--> 'bool MPU9250::readBytes(uint8_t, uint8_t, uint8_t*)': events 8-9
|
|  515 | bool MPU9250::readBytes(uint8_t subAddress, uint8_t count, uint8_t * dest)
|      |      ^~~~~~~
|      |      |
|      |      (8) entry to 'MPU9250::readBytes'
|......
|  525 |   if (ret != ESP_OK) return false;
|      |   ~~
|      |   |
|      |   (9) following 'true' branch...
|
'bool MPU9250::readBytes(uint8_t, uint8_t, uint8_t*)': event 10
|
|cc1plus.exe:
| (10): ...to here
|
<------+
|
'void MPU9250::calibrateMPU9250(float*, float*)': events 11-12
|
|  288 |   readBytes(FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
|      |   ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
|      |            |
|      |            (11) returning to 'MPU9250::calibrateMPU9250' from 'MPU9250::readBytes'
|  289 |
|  290 |   fifo_count = ((uint16_t)data[0] << 8) | data[1];
|      |                           ~~~~~~~
|      |                                 |
|      |                                 (12) use of uninitialized value 'data[0]' here
|
```

---

#### ⚠️ use of uninitialized value 'data[1]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 290)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:290](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L290)
- **Column:** 49
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
290 |   fifo_count = ((uint16_t)data[0] << 8) | data[1];
|                                           ~~~~~~^
'byte MPU9250::_ZN7MPU92505beginEb$part$0(bool)': events 1-4
|
|  659 | byte MPU9250::begin(bool fusion)
|      |      ^~~~~~~
|      |      |
|      |      (1) entry to 'MPU9250::_ZN7MPU92505beginEb$part$0'
|......
|  663 |   for (byte attempt = 0; attempt < 2; attempt++) {
|      |                          ~~~~~~~~~~~
|      |                                  |
|      |                                  (2) following 'true' branch (when 'attempt != 2')...
|......
|  666 |     byte c = readByte(WHO_AM_I_MPU9250);  // Read WHO_AM_I register for MPU-9250
|      |     ~~~~
|      |     |
|      |     (3) ...to here
|  667 |     if (c != 0x68 && c != 0x71) continue;
|  668 |     calibrateMPU9250(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
|      |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                     |
|      |                     (4) calling 'MPU9250::calibrateMPU9250' from 'MPU9250::_ZN7MPU92505beginEb$part$0'
|
+--> 'void MPU9250::calibrateMPU9250(float*, float*)': events 5-7
|
|  246 | void MPU9250::calibrateMPU9250(float * gyroBias, float * accelBias)
|      |      ^~~~~~~
|      |      |
|      |      (5) entry to 'MPU9250::calibrateMPU9250'
|  247 | {
|  248 |   uint8_t data[12]; // data array to hold accelerometer and gyro x, y, z, data
|      |           ~~~~
|      |           |
|      |           (6) region created on stack here
|......
|  288 |   readBytes(FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
|      |   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |            |
|      |            (7) calling 'MPU9250::readBytes' from 'MPU9250::calibrateMPU9250'
|
+--> 'bool MPU9250::readBytes(uint8_t, uint8_t, uint8_t*)': events 8-9
|
|  515 | bool MPU9250::readBytes(uint8_t subAddress, uint8_t count, uint8_t * dest)
|      |      ^~~~~~~
|      |      |
|      |      (8) entry to 'MPU9250::readBytes'
|......
|  525 |   if (ret != ESP_OK) return false;
|      |   ~~
|      |   |
|      |   (9) following 'true' branch...
|
'bool MPU9250::readBytes(uint8_t, uint8_t, uint8_t*)': event 10
|
|cc1plus.exe:
| (10): ...to here
|
<------+
|
'void MPU9250::calibrateMPU9250(float*, float*)': events 11-12
|
|  288 |   readBytes(FIFO_COUNTH, 2, &data[0]); // read FIFO sample count
|      |   ~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
|      |            |
|      |            (11) returning to 'MPU9250::calibrateMPU9250' from 'MPU9250::readBytes'
|  289 |
|  290 |   fifo_count = ((uint16_t)data[0] << 8) | data[1];
|      |                                           ~~~~~~~
|      |                                                 |
|      |                                                 (12) use of uninitialized value 'data[1]' here
|
In file included from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/portable.h:51,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/FreeRTOS.h:63,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h:33,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httppil.h:14,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpd.h:13,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpd.c:24:
```

---

#### ⚠️ use of uninitialized value 'aAvg[0]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 413)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:413](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L413)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
413 |     aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                    ^~~~
|      |                    |
|      |                    (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|  413 |     aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'aAvg[0]' here
|
```

---

#### ⚠️ use of uninitialized value 'aAvg[1]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 414)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:414](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L414)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
414 |     aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                    ^~~~
|      |                    |
|      |                    (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|  413 |     aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|  414 |     aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'aAvg[1]' here
|
```

---

#### ⚠️ use of uninitialized value 'aAvg[2]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 415)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:415](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L415)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
415 |     aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                    ^~~~
|      |                    |
|      |                    (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  415 |     aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'aAvg[2]' here
|
```

---

#### ⚠️ use of uninitialized value 'gAvg[0]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 418)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:418](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L418)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
418 |     gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |           ^~~~
|      |           |
|      |           (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  418 |     gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'gAvg[0]' here
|
```

---

#### ⚠️ use of uninitialized value 'gAvg[1]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 419)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:419](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L419)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
419 |     gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |           ^~~~
|      |           |
|      |           (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  419 |     gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'gAvg[1]' here
|
```

---

#### ⚠️ use of uninitialized value 'gAvg[2]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 420)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:420](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L420)
- **Column:** 11
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
420 |     gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|     ~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-4
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |           ^~~~
|      |           |
|      |           (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  420 |     gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|      |     ~~~~~~~
|      |           |
|      |           (4) use of uninitialized value 'gAvg[2]' here
|
```

---

#### ⚠️ use of uninitialized value 'aSTAvg[0]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 436)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:436](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L436)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
436 |     aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                             ^~~~~~
|      |                             |
|      |                             (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|  436 |     aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'aSTAvg[0]' here
|
```

---

#### ⚠️ use of uninitialized value 'aSTAvg[1]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 437)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:437](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L437)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
437 |     aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                             ^~~~~~
|      |                             |
|      |                             (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|  436 |     aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|  437 |     aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'aSTAvg[1]' here
|
```

---

#### ⚠️ use of uninitialized value 'aSTAvg[2]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 438)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:438](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L438)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
438 |     aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                             ^~~~~~
|      |                             |
|      |                             (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|......
|  438 |     aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'aSTAvg[2]' here
|
```

---

#### ⚠️ use of uninitialized value 'gSTAvg[0]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 441)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:441](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L441)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
441 |     gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                                        ^~~~~~
|      |                                        |
|      |                                        (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|......
|  441 |     gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;  // Turn the MSB and LSB into a signed 16-bit value
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'gSTAvg[0]' here
|
```

---

#### ⚠️ use of uninitialized value 'gSTAvg[1]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 442)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:442](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L442)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
442 |     gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                                        ^~~~~~
|      |                                        |
|      |                                        (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|......
|  442 |     gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'gSTAvg[1]' here
|
```

---

#### ⚠️ use of uninitialized value 'gSTAvg[2]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 443)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:443](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L443)
- **Column:** 13
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
443 |     gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|     ~~~~~~~~^
'void MPU9250::MPU9250SelfTest(float*)': events 1-8
|
|  400 |   int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
|      |                                        ^~~~~~
|      |                                        |
|      |                                        (1) region created on stack here
|......
|  410 |   for( int ii = 0; ii < 200; ii++) {  // get average current values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (2) following 'true' branch (when 'ii != 200')...
|  411 |
|  412 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);        // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (3) ...to here
|......
|  423 |   for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average current readings
|      |                   ~~~~~~
|      |                      |
|      |                      (4) following 'true' branch (when 'ii != 3')...
|  424 |     aAvg[ii] /= 200;
|      |     ~~~~
|      |     |
|      |     (5) ...to here
|......
|  433 |   for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer
|      |                    ~~~~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'ii != 200')...
|  434 |
|  435 |     readBytes(ACCEL_XOUT_H, 6, &rawData[0]);  // Read the six raw data registers into data array
|      |     ~~~~~~~~~
|      |     |
|      |     (7) ...to here
|......
|  443 |     gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
|      |     ~~~~~~~~~
|      |             |
|      |             (8) use of uninitialized value 'gSTAvg[2]' here
|
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp: In member function 'byte ICM_20948_I2C::_ZN13ICM_20948_I2C5beginEb$part$0(bool)':
```

---

#### ⚠️ use of possibly-NULL 'operator new(44)' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument] (Line 1430)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp:1430](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.cpp#L1430)
- **Column:** 21
- **Analyzer Rule:** `-Wanalyzer-possible-null-argument`
- **Analysis Context & Path:**
```text
1430 |     quaterion = new CQuaterion;
|                     ^~~~~~~~~~
'byte ICM_20948_I2C::_ZN13ICM_20948_I2C5beginEb$part$0(bool)': events 1-4
|
| 1429 |   if (fusion && !quaterion) {
|      |   ^~
|      |   |
|      |   (1) following 'true' branch...
| 1430 |     quaterion = new CQuaterion;
|      |     ~~~~~~~~~       ~~~~~~~~~~
|      |     |               |
|      |     |               (3) this call could return NULL
|      |     (2) ...to here  (4) argument 'this' ('operator new(44)') from (3) could be NULL where non-null expected
|
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:226:7: note: argument 'this' of 'constexpr CQuaterion::CQuaterion()' must be non-null
226 | class CQuaterion
|       ^~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp: In member function 'bool FreematicsESP32::begin(bool, bool)':
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsMEMS.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h)

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 234)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.h:234](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h#L234)
- **Column:** 28
- **Analysis Context & Path:**
```text
234 |   float GyroMeasError = PI * (40.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
```

---

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 235)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.h:235](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h#L235)
- **Column:** 28
- **Analysis Context & Path:**
```text
235 |   float GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
In file included from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.h:20:
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.h: In member function 'void COBD::begin(CLink*)':
```

---

#### ⚠️ dereference of possibly-NULL 'operator new(4)' [CWE-690] [-Wanalyzer-possible-null-dereference] (Line 246)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.h:246](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h#L246)
- **Column:** 14
- **Analyzer Rule:** `-Wanalyzer-possible-null-dereference`
- **Analysis Context & Path:**
```text
246 |   MEMS_I2C() {};
|              ^
'void setup()': event 1
|
|C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1382:6:
| 1382 | void setup()
|      |      ^~~~~
|      |      |
|      |      (1) entry to 'setup'
|
'void setup()': event 2
|
|C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common/include/esp_err.h:117:9:
|  117 |         if (unlikely(err_rc_ != ESP_OK)) {                              \
|      |         ^~
|      |         |
|      |         (2) following 'false' branch (when 'err == 0')...
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1397:3: note: in expansion of macro 'ESP_ERROR_CHECK'
| 1397 |   ESP_ERROR_CHECK( err );
|      |   ^~~~~~~~~~~~~~~
|
'void setup()': event 3
|
|C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common/include/esp_err.h:115:28:
|  115 | #define ESP_ERROR_CHECK(x) do {                                         \
|      |                            ^~
|      |                            |
|      |                            (3) ...to here
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1397:3: note: in expansion of macro 'ESP_ERROR_CHECK'
| 1397 |   ESP_ERROR_CHECK( err );
|      |   ^~~~~~~~~~~~~~~
|
'void setup()': event 4
|
| 1417 |   genDeviceID(devid);
|      |   ~~~~~~~~~~~^~~~~~~
|      |              |
|      |              (4) calling 'genDeviceID' from 'setup'
|
+--> 'void genDeviceID(char*)': events 5-7
|
| 1150 | void genDeviceID(char* buf)
|      |      ^~~~~~~~~~~
|      |      |
|      |      (5) entry to 'genDeviceID'
|......
| 1153 |     for (int i = 0; i < 8; i++, seed >>= 5) {
|      |                     ~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'i != 8')...
| 1154 |       byte x = (byte)seed & 0x1f;
|      |       ~~~~
|      |       |
|      |       (7) ...to here
|
<------+
|
'void setup()': events 8-11
|
| 1417 |   genDeviceID(devid);
|      |   ~~~~~~~~~~~^~~~~~~
|      |              |
|      |              (8) returning to 'setup' from 'genDeviceID'
|......
| 1451 | if (!state.check(STATE_MEMS_READY)) do {
|      | ~~                                  ~~
|      | |                                   |
|      | (9) following 'true' branch...      (10) ...to here
| 1452 |   Serial.print("MEMS:");
| 1453 |   mems = new ICM_42627;
|      |              ~~~~~~~~~
|      |              |
|      |              (11) this call could return NULL
|
'void setup()': event 12
|
|C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:246:14:
|  246 |   MEMS_I2C() {};
|      |              ^
|      |              |
|      |              (12) 'operator new(4)' could be NULL: unchecked value from (11)
|
In constructor 'MEMS_I2C::MEMS_I2C()',
inlined from 'ICM_20948_I2C::ICM_20948_I2C()' at C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:404:7,
inlined from 'void setup()' at C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1461:14:
```

---

#### ⚠️ dereference of possibly-NULL 'operator new(60)' [CWE-690] [-Wanalyzer-possible-null-dereference] (Line 246)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsMEMS.h:246](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h#L246)
- **Column:** 14
- **Analyzer Rule:** `-Wanalyzer-possible-null-dereference`
- **Analysis Context & Path:**
```text
246 |   MEMS_I2C() {};
|              ^
'void setup()': event 1
|
|C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1382:6:
| 1382 | void setup()
|      |      ^~~~~
|      |      |
|      |      (1) entry to 'setup'
|
'void setup()': event 2
|
|C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common/include/esp_err.h:117:9:
|  117 |         if (unlikely(err_rc_ != ESP_OK)) {                              \
|      |         ^~
|      |         |
|      |         (2) following 'false' branch (when 'err == 0')...
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1397:3: note: in expansion of macro 'ESP_ERROR_CHECK'
| 1397 |   ESP_ERROR_CHECK( err );
|      |   ^~~~~~~~~~~~~~~
|
'void setup()': event 3
|
|C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/esp_common/include/esp_err.h:115:28:
|  115 | #define ESP_ERROR_CHECK(x) do {                                         \
|      |                            ^~
|      |                            |
|      |                            (3) ...to here
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:1397:3: note: in expansion of macro 'ESP_ERROR_CHECK'
| 1397 |   ESP_ERROR_CHECK( err );
|      |   ^~~~~~~~~~~~~~~
|
'void setup()': event 4
|
| 1417 |   genDeviceID(devid);
|      |   ~~~~~~~~~~~^~~~~~~
|      |              |
|      |              (4) calling 'genDeviceID' from 'setup'
|
+--> 'void genDeviceID(char*)': events 5-7
|
| 1150 | void genDeviceID(char* buf)
|      |      ^~~~~~~~~~~
|      |      |
|      |      (5) entry to 'genDeviceID'
|......
| 1153 |     for (int i = 0; i < 8; i++, seed >>= 5) {
|      |                     ~~~~~
|      |                       |
|      |                       (6) following 'true' branch (when 'i != 8')...
| 1154 |       byte x = (byte)seed & 0x1f;
|      |       ~~~~
|      |       |
|      |       (7) ...to here
|
<------+
|
'void setup()': events 8-15
|
| 1417 |   genDeviceID(devid);
|      |   ~~~~~~~~~~~^~~~~~~
|      |              |
|      |              (8) returning to 'setup' from 'genDeviceID'
|......
| 1451 | if (!state.check(STATE_MEMS_READY)) do {
|      | ~~                                  ~~
|      | |                                   |
|      | (9) following 'true' branch...      (10) ...to here
|......
| 1455 |   if (ret) {
|      |   ~~
|      |   |
|      |   (11) following 'false' branch...
|......
| 1460 |   delete mems;
|      |   ~~~~~~~~~~~
|      |   |
|      |   (12) ...to here
|      |   (13) following 'false' branch...
| 1461 |   mems = new ICM_20948_I2C;
|      |   ~~~~       ~~~~~~~~~~~~~
|      |   |          |
|      |   |          (15) this call could return NULL
|      |   (14) ...to here
|
'void setup()': event 16
|
|C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsMEMS.h:246:14:
|  246 |   MEMS_I2C() {};
|      |              ^
|      |              |
|      |              (16) 'operator new(60)' could be NULL: unchecked value from (15)
|
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp)

#### ⚠️ declaration of 'p' shadows a previous local [-Wshadow] (Line 971)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:971](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L971)
- **Column:** 13
- **Analysis Context & Path:**
```text
971 |       char *p = strstr(m_buffer, "\r\n+CHTTPSRECV: DATA");
|             ^
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:959:11: note: shadowed declaration is here
959 |     char *p = strstr(m_buffer, "RECV EVENT");
|           ^
In file included from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.h:19,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp:25:
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 16)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:16](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L16)
- **Column:** 10
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
16 |   String header;
|          ^~~~~~
'String HTTPClient::genHeader(HTTP_METHOD, const char*, const char*, int)': events 1-2
|
|   14 | String HTTPClient::genHeader(HTTP_METHOD method, const char* path, const char* payload, int payloadSize)
|      |                                                                                                        ^
|      |                                                                                                        |
|      |                                                                                                        (1) region created on stack here
|   15 | {
|   16 |   String header;
|      |          ~~~~~~
|      |          |
|      |          (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 18)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:18](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L18)
- **Column:** 44
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
18 |   header = method == METHOD_GET ? "GET " : "POST ";
|                                            ^~~~~~~
'String HTTPClient::genHeader(HTTP_METHOD, const char*, const char*, int)': events 1-2
|
|   14 | String HTTPClient::genHeader(HTTP_METHOD method, const char* path, const char* payload, int payloadSize)
|      |                                                                                                        ^
|      |                                                                                                        |
|      |                                                                                                        (1) region created on stack here
|......
|   18 |   header = method == METHOD_GET ? "GET " : "POST ";
|      |                                            ~~~~~~~
|      |                                            |
|      |                                            (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 27)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:27](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L27)
- **Column:** 10
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
27 |   return header;
|          ^~~~~~
'String HTTPClient::genHeader(HTTP_METHOD, const char*, const char*, int)': events 1-2
|
|   14 | String HTTPClient::genHeader(HTTP_METHOD method, const char* path, const char* payload, int payloadSize)
|      |                                                                                                        ^
|      |                                                                                                        |
|      |                                                                                                        (1) region created on stack here
|......
|   27 |   return header;
|      |          ~~~~~~
|      |          |
|      |          (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 28)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:28](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L28)
- **Column:** 1
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
28 | }
| ^
'String HTTPClient::genHeader(HTTP_METHOD, const char*, const char*, int)': events 1-2
|
|   14 | String HTTPClient::genHeader(HTTP_METHOD method, const char* path, const char* payload, int payloadSize)
|      |                                                                                                        ^
|      |                                                                                                        |
|      |                                                                                                        (1) region created on stack here
|......
|   28 | }
|      | ~
|      | |
|      | (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 47)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:47](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L47)
- **Column:** 34
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
47 |   return WiFi.localIP().toString();
|                                  ^
'String ClientWIFI::getIP()': events 1-2
|
|   45 | String ClientWIFI::getIP()
|      |                          ^
|      |                          |
|      |                          (1) region created on stack here
|   46 | {
|   47 |   return WiFi.localIP().toString();
|      |                                  ~
|      |                                  |
|      |                                  (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 125)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:125](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L125)
- **Column:** 25
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
125 |   return udpIP.toString();
|                         ^
'String WifiUDP::queryIP(const char*)': events 1-2
|
|  123 | String WifiUDP::queryIP(const char* host)
|      |                                         ^
|      |                                         |
|      |                                         (1) region created on stack here
|  124 | {
|  125 |   return udpIP.toString();
|      |                         ~
|      |                         |
|      |                         (2) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of possibly-NULL 'operator new(36)' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument] (Line 393)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:393](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L393)
- **Column:** 17
- **Analyzer Rule:** `-Wanalyzer-possible-null-argument`
- **Analysis Context & Path:**
```text
393 |           memset(m_gps, 0, sizeof(GPS_DATA));
|           ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~
'virtual bool CellSIMCOM::setGPS(bool)': events 1-6
|
|  384 | bool CellSIMCOM::setGPS(bool on)
|      |      ^~~~~~~~~~
|      |      |
|      |      (1) entry to 'CellSIMCOM::setGPS'
|  385 | {
|  386 |   if (on) {
|      |   ~~
|      |   |
|      |   (2) following 'true' branch (when 'on != false')...
|  387 |     if (m_type == CELL_SIM7070) {
|      |     ~~
|      |     |
|      |     (3) ...to here
|      |     (4) following 'true' branch...
|  388 |       sendCommand("AT+CGNSPWR=1\r");
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |       |          |
|      |       |          (6) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|      |       (5) ...to here
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 7-9
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (7) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (8) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (9) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 10-11
|
|  388 |       sendCommand("AT+CGNSPWR=1\r");
|      |       ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (10) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|  389 |       sendCommand("AT+CGNSMOD=1,1,0,0,0\r");
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (11) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 12-14
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (12) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (13) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (14) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 15-16
|
|  389 |       sendCommand("AT+CGNSMOD=1,1,0,0,0\r");
|      |       ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (15) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|  390 |       if (sendCommand("AT+CGNSINF\r", 1000, "+CGNSINF:")) {
|      |           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (16) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 17-19
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (17) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (18) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (19) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 20-26
|
|  390 |       if (sendCommand("AT+CGNSINF\r", 1000, "+CGNSINF:")) {
|      |       ~~  ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |       |              |
|      |       |              (20) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|      |       (21) following 'true' branch...
|  391 |         if (!m_gps) {
|      |         ~~
|      |         |
|      |         (22) ...to here
|      |         (23) following 'true' branch...
|  392 |           m_gps = new GPS_DATA;
|      |           ~~~~~       ~~~~~~~~
|      |           |           |
|      |           |           (25) this call could return NULL
|      |           (24) ...to here
|  393 |           memset(m_gps, 0, sizeof(GPS_DATA));
|      |           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                 |
|      |                 (26) argument 1 ('operator new(36)') from (25) could be NULL where non-null expected
|
In file included from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h:29:
c:\users\florian\.platformio\packages\toolchain-xtensa-esp32\xtensa-esp32-elf\sys-include\string.h:33:10: note: argument 1 of 'void* memset(void*, int, size_t)' must be non-null
33 | void *   memset (void *, int, size_t);
|          ^~~~~~
```

---

#### ⚠️ use of possibly-NULL 'operator new(36)' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument] (Line 404)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:404](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L404)
- **Column:** 19
- **Analyzer Rule:** `-Wanalyzer-possible-null-argument`
- **Analysis Context & Path:**
```text
404 |             memset(m_gps, 0, sizeof(GPS_DATA));
|             ~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~
'virtual bool CellSIMCOM::setGPS(bool)': events 1-6
|
|  384 | bool CellSIMCOM::setGPS(bool on)
|      |      ^~~~~~~~~~
|      |      |
|      |      (1) entry to 'CellSIMCOM::setGPS'
|  385 | {
|  386 |   if (on) {
|      |   ~~
|      |   |
|      |   (2) following 'true' branch (when 'on != false')...
|  387 |     if (m_type == CELL_SIM7070) {
|      |     ~~
|      |     |
|      |     (3) ...to here
|      |     (4) following 'false' branch...
|......
|  398 |       sendCommand("AT+CVAUXV=61\r", 100);
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |       |          |
|      |       |          (6) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|      |       (5) ...to here
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 7-9
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (7) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (8) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (9) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 10-11
|
|  398 |       sendCommand("AT+CVAUXV=61\r", 100);
|      |       ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (10) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|  399 |       sendCommand("AT+CVAUXS=1\r", 100);
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (11) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 12-14
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (12) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (13) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (14) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 15-18
|
|  399 |       sendCommand("AT+CVAUXS=1\r", 100);
|      |       ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (15) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|  400 |       for (byte n = 0; n < 3; n++) {
|      |                        ~~~~~
|      |                          |
|      |                          (16) following 'true' branch (when 'n != 3')...
|  401 |         if ((sendCommand("AT+CGPS=1,1\r") && sendCommand("AT+CGPSINFO=1\r")) || sendCommand("AT+CGPS?\r", 100, "+CGPS: 1")) {
|      |         ~~   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |         |               |
|      |         (17) ...to here (18) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 19-21
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (19) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (20) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (21) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 22-23
|
|  401 |         if ((sendCommand("AT+CGPS=1,1\r") && sendCommand("AT+CGPSINFO=1\r")) || sendCommand("AT+CGPS?\r", 100, "+CGPS: 1")) {
|      |              ~~~~~~~~~~~^~~~~~~~~~~~~~~~~    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                         |                               |
|      |                         |                               (23) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::setGPS'
|      |                         (22) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 24-26
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (24) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (25) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (26) ...to here
|
<------+
|
'virtual bool CellSIMCOM::setGPS(bool)': events 27-31
|
|  401 |         if ((sendCommand("AT+CGPS=1,1\r") && sendCommand("AT+CGPSINFO=1\r")) || sendCommand("AT+CGPS?\r", 100, "+CGPS: 1")) {
|      |                                              ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~
|      |                                                         |
|      |                                                         (27) returning to 'CellSIMCOM::setGPS' from 'CellSIMCOM::sendCommand'
|  402 |           if (!m_gps) {
|      |           ~~
|      |           |
|      |           (28) following 'true' branch...
|  403 |             m_gps = new GPS_DATA;
|      |             ~~~~~       ~~~~~~~~
|      |             |           |
|      |             |           (30) this call could return NULL
|      |             (29) ...to here
|  404 |             memset(m_gps, 0, sizeof(GPS_DATA));
|      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (31) argument 1 ('operator new(36)') from (30) could be NULL where non-null expected
|
c:\users\florian\.platformio\packages\toolchain-xtensa-esp32\xtensa-esp32-elf\sys-include\string.h:33:10: note: argument 1 of 'void* memset(void*, int, size_t)' must be non-null
33 | void *   memset (void *, int, size_t);
|          ^~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp: In member function 'virtual String CellSIMCOM::getIP()':
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 449)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:449](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L449)
- **Column:** 20
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
449 |             return ip;
|                    ^~
'virtual String CellSIMCOM::getIP()': events 1-5
|
|  436 | String CellSIMCOM::getIP()
|      |        ^~~~~~~~~~        ~
|      |        |                 |
|      |        |                 (2) region created on stack here
|      |        (1) entry to 'CellSIMCOM::getIP'
|  437 | {
|  438 |   if (m_type == CELL_SIM7070) {
|      |   ~~
|      |   |
|      |   (3) following 'true' branch...
|  439 |     sendCommand("AT+CNACT=0,1\r");
|      |     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |     |          |
|      |     |          (5) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getIP'
|      |     (4) ...to here
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 6-8
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (6) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (7) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (8) ...to here
|
<------+
|
'virtual String CellSIMCOM::getIP()': events 9-12
|
|  439 |     sendCommand("AT+CNACT=0,1\r");
|      |     ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~
|      |                |
|      |                (9) returning to 'CellSIMCOM::getIP' from 'CellSIMCOM::sendCommand'
|  440 |     for (int i = 0; i < 30; i++) {
|      |                     ~~~~~~
|      |                       |
|      |                       (10) following 'true' branch (when 'i != 30')...
|  441 |       delay(500);
|      |       ~~~~~
|      |       |
|      |       (11) ...to here
|  442 |       if (sendCommand("AT+CNACT?\r", 1000)) {
|      |           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (12) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getIP'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 13-15
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (13) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (14) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (15) ...to here
|
<------+
|
'virtual String CellSIMCOM::getIP()': events 16-17
|
|  442 |       if (sendCommand("AT+CNACT?\r", 1000)) {
|      |           ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (16) returning to 'CellSIMCOM::getIP' from 'CellSIMCOM::sendCommand'
|......
|  449 |             return ip;
|      |                    ~~
|      |                    |
|      |                    (17) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 464)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:464](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L464)
- **Column:** 20
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
464 |             return ip;
|                    ^~
'virtual String CellSIMCOM::getIP()': events 1-5
|
|  436 | String CellSIMCOM::getIP()
|      |        ^~~~~~~~~~        ~
|      |        |                 |
|      |        |                 (2) region created on stack here
|      |        (1) entry to 'CellSIMCOM::getIP'
|  437 | {
|  438 |   if (m_type == CELL_SIM7070) {
|      |   ~~
|      |   |
|      |   (3) following 'false' branch...
|......
|  455 |     uint32_t t = millis();
|      |     ~~~~~~~~
|      |     |
|      |     (4) ...to here
|  456 |     do {
|  457 |       if (sendCommand("AT+IPADDR\r", 3000, "\r\nOK\r\n")) {
|      |           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (5) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getIP'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 6-8
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (6) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (7) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (8) ...to here
|
<------+
|
'virtual String CellSIMCOM::getIP()': events 9-10
|
|  457 |       if (sendCommand("AT+IPADDR\r", 3000, "\r\nOK\r\n")) {
|      |           ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (9) returning to 'CellSIMCOM::getIP' from 'CellSIMCOM::sendCommand'
|......
|  464 |             return ip;
|      |                    ~~
|      |                    |
|      |                    (10) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 472)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:472](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L472)
- **Column:** 10
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
472 |   return "";
|          ^~
'virtual String CellSIMCOM::getIP()': events 1-3
|
|  436 | String CellSIMCOM::getIP()
|      |        ^~~~~~~~~~        ~
|      |        |                 |
|      |        |                 (2) region created on stack here
|      |        (1) entry to 'CellSIMCOM::getIP'
|......
|  457 |       if (sendCommand("AT+IPADDR\r", 3000, "\r\nOK\r\n")) {
|      |           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (3) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getIP'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 4-6
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (4) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (5) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (6) ...to here
|
<------+
|
'virtual String CellSIMCOM::getIP()': events 7-8
|
|  457 |       if (sendCommand("AT+IPADDR\r", 3000, "\r\nOK\r\n")) {
|      |           ~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                      |
|      |                      (7) returning to 'CellSIMCOM::getIP' from 'CellSIMCOM::sendCommand'
|......
|  472 |   return "";
|      |          ~~
|      |          |
|      |          (8) use of uninitialized value '<unknown>' here
|
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp: In member function 'String CellSIMCOM::getOperatorName()':
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 497)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:497](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L497)
- **Column:** 18
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
497 |           return p;
|                  ^
'String CellSIMCOM::getOperatorName()': events 1-3
|
|  489 | String CellSIMCOM::getOperatorName()
|      |        ^~~~~~~~~~                  ~
|      |        |                           |
|      |        |                           (2) region created on stack here
|      |        (1) entry to 'CellSIMCOM::getOperatorName'
|  490 | {
|  491 |   if (sendCommand("AT+COPS?\r")) {
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (3) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getOperatorName'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 4-6
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (4) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (5) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (6) ...to here
|
<------+
|
'String CellSIMCOM::getOperatorName()': events 7-12
|
|  491 |   if (sendCommand("AT+COPS?\r")) {
|      |   ~~  ~~~~~~~~~~~^~~~~~~~~~~~~~
|      |   |              |
|      |   |              (7) returning to 'CellSIMCOM::getOperatorName' from 'CellSIMCOM::sendCommand'
|      |   (8) following 'true' branch...
|  492 |       char *p = strstr(m_buffer, ",\"");
|      |       ~~~~
|      |       |
|      |       (9) ...to here
|  493 |       if (p) {
|      |       ~~
|      |       |
|      |       (10) following 'true' branch...
|  494 |           p += 2;
|      |           ~
|      |           |
|      |           (11) ...to here
|......
|  497 |           return p;
|      |                  ~
|      |                  |
|      |                  (12) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 500)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:500](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L500)
- **Column:** 10
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
500 |   return "";
|          ^~
'String CellSIMCOM::getOperatorName()': events 1-3
|
|  489 | String CellSIMCOM::getOperatorName()
|      |        ^~~~~~~~~~                  ~
|      |        |                           |
|      |        |                           (2) region created on stack here
|      |        (1) entry to 'CellSIMCOM::getOperatorName'
|  490 | {
|  491 |   if (sendCommand("AT+COPS?\r")) {
|      |       ~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                  |
|      |                  (3) calling 'CellSIMCOM::sendCommand' from 'CellSIMCOM::getOperatorName'
|
+--> 'bool CellSIMCOM::sendCommand(const char*, unsigned int, const char*)': events 4-6
|
|  562 | bool CellSIMCOM::sendCommand(const char* cmd, unsigned int timeout, const char* expected)
|      |      ^~~~~~~~~~
|      |      |
|      |      (4) entry to 'CellSIMCOM::sendCommand'
|  563 | {
|  564 |   if (cmd) {
|      |   ~~
|      |   |
|      |   (5) following 'true' branch (when 'cmd' is non-NULL)...
|  565 |     m_device->xbWrite(cmd);
|      |     ~~~~~~~~
|      |     |
|      |     (6) ...to here
|
<------+
|
'String CellSIMCOM::getOperatorName()': events 7-8
|
|  491 |   if (sendCommand("AT+COPS?\r")) {
|      |       ~~~~~~~~~~~^~~~~~~~~~~~~~
|      |                  |
|      |                  (7) returning to 'CellSIMCOM::getOperatorName' from 'CellSIMCOM::sendCommand'
|......
|  500 |   return "";
|      |          ~~
|      |          |
|      |          (8) use of uninitialized value '<unknown>' here
|
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp: In member function 'virtual String CellSIMCOM::queryIP(const char*)':
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 540)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:540](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L540)
- **Column:** 18
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
540 |           return ip;
|                  ^~
'virtual String CellSIMCOM::queryIP(const char*)': events 1-10
|
|  528 | String CellSIMCOM::queryIP(const char* host)
|      |                                            ^
|      |                                            |
|      |                                            (1) region created on stack here
|  529 | {
|  530 |   if (m_type == CELL_SIM7070) {
|      |   ~~
|      |   |
|      |   (2) following 'true' branch...
|  531 |     sprintf(m_buffer, "AT+CDNSGIP=\"%s\",1,3000\r", host);
|      |     ~~~~~~~
|      |     |
|      |     (3) ...to here
|  532 |     if (sendCommand(m_buffer, 10000, "+CDNSGIP:")) {
|      |     ~~
|      |     |
|      |     (4) following 'true' branch...
|  533 |       char *p = strstr(m_buffer, host);
|      |       ~~~~
|      |       |
|      |       (5) ...to here
|  534 |       if (p) {
|      |       ~~
|      |       |
|      |       (6) following 'true' branch (when 'p' is non-NULL)...
|  535 |         p = strstr(p, "\",\"");
|      |         ~
|      |         |
|      |         (7) ...to here
|  536 |         if (p) {
|      |         ~~
|      |         |
|      |         (8) following 'true' branch (when 'p' is non-NULL)...
|  537 |           char *ip = p + 3;
|      |           ~~~~
|      |           |
|      |           (9) ...to here
|......
|  540 |           return ip;
|      |                  ~~
|      |                  |
|      |                  (10) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 554)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:554](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L554)
- **Column:** 18
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
554 |           return ip;
|                  ^~
'virtual String CellSIMCOM::queryIP(const char*)': events 1-10
|
|  528 | String CellSIMCOM::queryIP(const char* host)
|      |                                            ^
|      |                                            |
|      |                                            (1) region created on stack here
|  529 | {
|  530 |   if (m_type == CELL_SIM7070) {
|      |   ~~
|      |   |
|      |   (2) following 'false' branch...
|......
|  545 |     sprintf(m_buffer, "AT+CDNSGIP=\"%s\"\r", host);
|      |     ~~~~~~~
|      |     |
|      |     (3) ...to here
|  546 |     if (sendCommand(m_buffer, 10000)) {
|      |     ~~
|      |     |
|      |     (4) following 'true' branch...
|  547 |       char *p = strstr(m_buffer, host);
|      |       ~~~~
|      |       |
|      |       (5) ...to here
|  548 |       if (p) {
|      |       ~~
|      |       |
|      |       (6) following 'true' branch (when 'p' is non-NULL)...
|  549 |         p = strstr(p, ",\"");
|      |         ~
|      |         |
|      |         (7) ...to here
|  550 |         if (p) {
|      |         ~~
|      |         |
|      |         (8) following 'true' branch (when 'p' is non-NULL)...
|  551 |           char *ip = p + 2;
|      |           ~~~~
|      |           |
|      |           (9) ...to here
|......
|  554 |           return ip;
|      |                  ~~
|      |                  |
|      |                  (10) use of uninitialized value '<unknown>' here
|
```

---

#### ⚠️ use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 559)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp:559](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsNetwork.cpp#L559)
- **Column:** 10
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
559 |   return "";
|          ^~
'virtual String CellSIMCOM::queryIP(const char*)': events 1-2
|
|  528 | String CellSIMCOM::queryIP(const char* host)
|      |                                            ^
|      |                                            |
|      |                                            (1) region created on stack here
|......
|  559 |   return "";
|      |          ~~
|      |          |
|      |          (2) use of uninitialized value '<unknown>' here
|
In member function 'String fs::File::getNextFileName()':
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsOBD.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp)

#### ⚠️ format '%X' expects argument of type 'unsigned int', but argument 3 has type 'long unsigned int' [-Wformat=] (Line 476)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsOBD.cpp:476](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp#L476)
- **Column:** 37
- **Analysis Context & Path:**
```text
476 |                 sprintf(buf, "ATSH %X\r", num & 0xffffff);
|                                    ~^     ~~~~~~~~~~~~~~
|                                     |         |
|                                     |         long unsigned int
|                                     unsigned int
|                                    %lX
```

---

#### ⚠️ format '%X' expects argument of type 'unsigned int', but argument 3 has type 'long unsigned int' [-Wformat=] (Line 478)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsOBD.cpp:478](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp#L478)
- **Column:** 37
- **Analysis Context & Path:**
```text
478 |                 sprintf(buf, "ATCP %X\r", num & 0x1f);
|                                    ~^     ~~~~~~~~~~
|                                     |         |
|                                     |         long unsigned int
|                                     unsigned int
|                                    %lX
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp: In member function 'void COBD::setHeaderFilter(uint32_t)':
```

---

#### ⚠️ format '%X' expects argument of type 'unsigned int', but argument 3 has type 'uint32_t' {aka 'long unsigned int'} [-Wformat=] (Line 495)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsOBD.cpp:495](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp#L495)
- **Column:** 37
- **Analysis Context & Path:**
```text
495 |                 sprintf(buf, "ATCF %X\r", num);
|                                    ~^     ~~~
|                                     |     |
|                                     |     uint32_t {aka long unsigned int}
|                                     unsigned int
|                                    %lX
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp: In member function 'void COBD::setHeaderMask(uint32_t)':
```

---

#### ⚠️ format '%X' expects argument of type 'unsigned int', but argument 3 has type 'uint32_t' {aka 'long unsigned int'} [-Wformat=] (Line 504)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsOBD.cpp:504](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.cpp#L504)
- **Column:** 37
- **Analysis Context & Path:**
```text
504 |                 sprintf(buf, "ATCM %X\r", bitmask);
|                                    ~^     ~~~~~~~
|                                     |     |
|                                     |     uint32_t {aka long unsigned int}
|                                     unsigned int
|                                    %lX
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsOBD.h](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.h)

#### ⚠️ declaration of 'link' shadows a member of 'COBD' [-Wshadow] (Line 23)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsOBD.h:23](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.h#L23)
- **Column:** 27
- **Analysis Context & Path:**
```text
23 |         void begin(CLink* link) { this->link = link; }
|                    ~~~~~~~^~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsOBD.h:73:16: note: shadowed declaration is here
73 |         CLink* link = 0;
|                ^~~~
In file included from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/portable.h:51,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/FreeRTOS.h:63,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h:33,
from C:\Users\Florian\AppData\Local\Temp\tmp02xoxya9:1:
```

---

### File: [esp32/libraries/FreematicsPlus/FreematicsPlus.cpp](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp)

#### ⚠️ declaration of 'i' shadows a previous local [-Wshadow] (Line 572)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsPlus.cpp:572](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp#L572)
- **Column:** 26
- **Analysis Context & Path:**
```text
572 |                 for (int i = 0; i < sizeof(gpsSettings); i++) softSerialTx(GPS_SOFT_BAUDRATE, gpsSettings[i]);
|                          ^
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp:565:14: note: shadowed declaration is here
565 |     for (int i = 0; i < 11; i++) {
|              ^
In file included from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/portable.h:51,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/FreeRTOS.h:63,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/utility/ble_spp_server.c:10:
```

---

#### ⚠️ use of possibly-NULL 'operator new(4)' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument] (Line 919)

- **File Location:** [esp32/libraries/FreematicsPlus/FreematicsPlus.cpp:919](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp#L919)
- **Column:** 28
- **Analyzer Rule:** `-Wanalyzer-possible-null-argument`
- **Analysis Context & Path:**
```text
919 |         if (linkUART->begin(115200)) {
|             ~~~~~~~~~~~~~~~^~~~~~~~
'bool FreematicsESP32::begin(bool, bool)': events 1-6
|
|  904 |     if (useCoProc) do {
|      |     ^~             ~~
|      |     |              |
|      |     |              (2) ...to here
|      |     (1) following 'true' branch (when 'useCoProc != false')...
|  905 |         if (link) return false;
|      |         ~~
|      |         |
|      |         (3) following 'false' branch...
|  906 | #ifdef PIN_LINK_RESET
|  907 |         pinMode(PIN_LINK_RESET, OUTPUT);
|      |         ~~~~~~~
|      |         |
|      |         (4) ...to here
|......
|  910 |         CLink_UART *linkUART = new CLink_UART;
|      |                                    ~~~~~~~~~~
|      |                                    |
|      |                                    (5) this call could return NULL
|......
|  919 |         if (linkUART->begin(115200)) {
|      |             ~~~~~~~~~~~~~~~~~~~~~~~
|      |                            |
|      |                            (6) argument 'this' ('operator new(4)') from (5) could be NULL where non-null expected
|
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/FreematicsPlus.cpp:234:6: note: argument 'this' of 'virtual bool CLink_UART::begin(unsigned int, int, int)' must be non-null
234 | bool CLink_UART::begin(unsigned int baudrate, int rxPin, int txPin)
|      ^~~~~~~~~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httpd.c: In function 'mwGetHttpDateTime':
```

---

### File: [esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c)

#### ⚠️ use of uninitialized value 'acfg.ACCEL_FS_SEL' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 546)

- **File Location:** [esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c:546](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c#L546)
- **Column:** 28
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
546 |         pagmt->fss.a = acfg.ACCEL_FS_SEL;       // Worth noting that without explicitly setting the FS range of the accelerometer it was showing the register value for +/- 2g but the reported values were actually scaled to the +/- 16g range
|                        ~~~~^~~~~~~~~~~~~
'ICM_20948_get_agmt': events 1-5
|
|  515 | ICM_20948_Status_e  ICM_20948_get_agmt          ( ICM_20948_Device_t* pdev, ICM_20948_AGMT_t* pagmt ){
|      |                     ^~~~~~~~~~~~~~~~~~
|      |                     |
|      |                     (1) entry to 'ICM_20948_get_agmt'
|  516 |         if( pagmt == NULL ){ return ICM_20948_Stat_ParamErr; }
|      |           ~
|      |           |
|      |           (3) following 'false' branch (when 'pagmt' is non-NULL)...
|  517 |
|  518 |         ICM_20948_Status_e retval = ICM_20948_Stat_Ok;
|      |         ~~~~~~~~~~~~~~~~~~
|      |         |
|      |         (4) ...to here
|......
|  523 |         retval |= ICM_20948_set_bank( pdev, 0 );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (5) calling 'ICM_20948_set_bank' from 'ICM_20948_get_agmt'
|......
|  544 |         ICM_20948_ACCEL_CONFIG_t acfg;
|      |                                  ~~~~
|      |                                  |
|      |                                  (2) region created on stack here
|
+--> 'ICM_20948_set_bank': events 6-8
|
|  117 | ICM_20948_Status_e      ICM_20948_set_bank( ICM_20948_Device_t* pdev, uint8_t bank ){
|      |                         ^~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (6) entry to 'ICM_20948_set_bank'
|  118 |         if( bank > 3 ){ return ICM_20948_Stat_ParamErr; } // Only 4 possible banks
|      |           ~
|      |           |
|      |           (7) following 'false' branch...
|  119 |         bank = (bank << 4) & 0x30; // bits 5:4 of REG_BANK_SEL
|      |         ~~~~
|      |         |
|      |         (8) ...to here
|
<------+
|
'ICM_20948_get_agmt': events 9-10
|
|  523 |         retval |= ICM_20948_set_bank( pdev, 0 );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (9) returning to 'ICM_20948_get_agmt' from 'ICM_20948_set_bank'
|......
|  543 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (10) calling 'ICM_20948_set_bank' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_set_bank': events 11-14
|
|  117 | ICM_20948_Status_e      ICM_20948_set_bank( ICM_20948_Device_t* pdev, uint8_t bank ){
|      |                         ^~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (11) entry to 'ICM_20948_set_bank'
|  118 |         if( bank > 3 ){ return ICM_20948_Stat_ParamErr; } // Only 4 possible banks
|      |           ~
|      |           |
|      |           (12) following 'false' branch...
|  119 |         bank = (bank << 4) & 0x30; // bits 5:4 of REG_BANK_SEL
|      |         ~~~~
|      |         |
|      |         (13) ...to here
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (14) calling 'ICM_20948_execute_w' from 'ICM_20948_set_bank'
|
+--> 'ICM_20948_execute_w': events 15-16
|
|   28 | ICM_20948_Status_e      ICM_20948_execute_w( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (15) entry to 'ICM_20948_execute_w'
|   29 |         if( pdev->_serif->write == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (16) following 'true' branch...
|
'ICM_20948_execute_w': event 17
|
|cc1.exe:
| (17): ...to here
|
<------+
|
'ICM_20948_set_bank': event 18
|
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (18) returning to 'ICM_20948_set_bank' from 'ICM_20948_execute_w'
|
<------+
|
'ICM_20948_get_agmt': events 19-20
|
|  543 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (19) returning to 'ICM_20948_get_agmt' from 'ICM_20948_set_bank'
|  544 |         ICM_20948_ACCEL_CONFIG_t acfg;
|  545 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_ACCEL_CONFIG, (uint8_t*)&acfg, 1*sizeof(acfg) );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (20) calling 'ICM_20948_execute_r' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_execute_r': events 21-22
|
|   33 | ICM_20948_Status_e      ICM_20948_execute_r( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (21) entry to 'ICM_20948_execute_r'
|   34 |         if( pdev->_serif->read == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (22) following 'true' branch...
|
'ICM_20948_execute_r': event 23
|
|cc1.exe:
| (23): ...to here
|
<------+
|
'ICM_20948_get_agmt': events 24-25
|
|  545 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_ACCEL_CONFIG, (uint8_t*)&acfg, 1*sizeof(acfg) );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (24) returning to 'ICM_20948_get_agmt' from 'ICM_20948_execute_r'
|  546 |         pagmt->fss.a = acfg.ACCEL_FS_SEL;       // Worth noting that without explicitly setting the FS range of the accelerometer it was showing the register value for +/- 2g but the reported values were actually scaled to the +/- 16g range
|      |                        ~~~~~~~~~~~~~~~~~
|      |                            |
|      |                            (25) use of uninitialized value 'acfg.ACCEL_FS_SEL' here
|
```

---

#### ⚠️ use of uninitialized value 'gcfg1.GYRO_FS_SEL' [CWE-457] [-Wanalyzer-use-of-uninitialized-value] (Line 551)

- **File Location:** [esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c:551](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/FreematicsPlus/utility/ICM_20948_C.c#L551)
- **Column:** 29
- **Analyzer Rule:** `-Wanalyzer-use-of-uninitialized-value`
- **Analysis Context & Path:**
```text
551 |         pagmt->fss.g = gcfg1.GYRO_FS_SEL;
|                        ~~~~~^~~~~~~~~~~~
'ICM_20948_get_agmt': events 1-5
|
|  515 | ICM_20948_Status_e  ICM_20948_get_agmt          ( ICM_20948_Device_t* pdev, ICM_20948_AGMT_t* pagmt ){
|      |                     ^~~~~~~~~~~~~~~~~~
|      |                     |
|      |                     (1) entry to 'ICM_20948_get_agmt'
|  516 |         if( pagmt == NULL ){ return ICM_20948_Stat_ParamErr; }
|      |           ~
|      |           |
|      |           (3) following 'false' branch (when 'pagmt' is non-NULL)...
|  517 |
|  518 |         ICM_20948_Status_e retval = ICM_20948_Stat_Ok;
|      |         ~~~~~~~~~~~~~~~~~~
|      |         |
|      |         (4) ...to here
|......
|  523 |         retval |= ICM_20948_set_bank( pdev, 0 );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (5) calling 'ICM_20948_set_bank' from 'ICM_20948_get_agmt'
|......
|  549 |         ICM_20948_GYRO_CONFIG_1_t gcfg1;
|      |                                   ~~~~~
|      |                                   |
|      |                                   (2) region created on stack here
|
+--> 'ICM_20948_set_bank': events 6-8
|
|  117 | ICM_20948_Status_e      ICM_20948_set_bank( ICM_20948_Device_t* pdev, uint8_t bank ){
|      |                         ^~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (6) entry to 'ICM_20948_set_bank'
|  118 |         if( bank > 3 ){ return ICM_20948_Stat_ParamErr; } // Only 4 possible banks
|      |           ~
|      |           |
|      |           (7) following 'false' branch...
|  119 |         bank = (bank << 4) & 0x30; // bits 5:4 of REG_BANK_SEL
|      |         ~~~~
|      |         |
|      |         (8) ...to here
|
<------+
|
'ICM_20948_get_agmt': events 9-10
|
|  523 |         retval |= ICM_20948_set_bank( pdev, 0 );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (9) returning to 'ICM_20948_get_agmt' from 'ICM_20948_set_bank'
|......
|  543 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (10) calling 'ICM_20948_set_bank' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_set_bank': events 11-14
|
|  117 | ICM_20948_Status_e      ICM_20948_set_bank( ICM_20948_Device_t* pdev, uint8_t bank ){
|      |                         ^~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (11) entry to 'ICM_20948_set_bank'
|  118 |         if( bank > 3 ){ return ICM_20948_Stat_ParamErr; } // Only 4 possible banks
|      |           ~
|      |           |
|      |           (12) following 'false' branch...
|  119 |         bank = (bank << 4) & 0x30; // bits 5:4 of REG_BANK_SEL
|      |         ~~~~
|      |         |
|      |         (13) ...to here
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (14) calling 'ICM_20948_execute_w' from 'ICM_20948_set_bank'
|
+--> 'ICM_20948_execute_w': events 15-16
|
|   28 | ICM_20948_Status_e      ICM_20948_execute_w( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (15) entry to 'ICM_20948_execute_w'
|   29 |         if( pdev->_serif->write == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (16) following 'true' branch...
|
'ICM_20948_execute_w': event 17
|
|cc1.exe:
| (17): ...to here
|
<------+
|
'ICM_20948_set_bank': event 18
|
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (18) returning to 'ICM_20948_set_bank' from 'ICM_20948_execute_w'
|
<------+
|
'ICM_20948_get_agmt': events 19-20
|
|  543 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (19) returning to 'ICM_20948_get_agmt' from 'ICM_20948_set_bank'
|  544 |         ICM_20948_ACCEL_CONFIG_t acfg;
|  545 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_ACCEL_CONFIG, (uint8_t*)&acfg, 1*sizeof(acfg) );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (20) calling 'ICM_20948_execute_r' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_execute_r': events 21-22
|
|   33 | ICM_20948_Status_e      ICM_20948_execute_r( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (21) entry to 'ICM_20948_execute_r'
|   34 |         if( pdev->_serif->read == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (22) following 'true' branch...
|
'ICM_20948_execute_r': event 23
|
|cc1.exe:
| (23): ...to here
|
<------+
|
'ICM_20948_get_agmt': events 24-25
|
|  545 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_ACCEL_CONFIG, (uint8_t*)&acfg, 1*sizeof(acfg) );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (24) returning to 'ICM_20948_get_agmt' from 'ICM_20948_execute_r'
|......
|  548 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (25) calling 'ICM_20948_set_bank' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_set_bank': events 26-29
|
|  117 | ICM_20948_Status_e      ICM_20948_set_bank( ICM_20948_Device_t* pdev, uint8_t bank ){
|      |                         ^~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (26) entry to 'ICM_20948_set_bank'
|  118 |         if( bank > 3 ){ return ICM_20948_Stat_ParamErr; } // Only 4 possible banks
|      |           ~
|      |           |
|      |           (27) following 'false' branch...
|  119 |         bank = (bank << 4) & 0x30; // bits 5:4 of REG_BANK_SEL
|      |         ~~~~
|      |         |
|      |         (28) ...to here
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (29) calling 'ICM_20948_execute_w' from 'ICM_20948_set_bank'
|
+--> 'ICM_20948_execute_w': events 30-31
|
|   28 | ICM_20948_Status_e      ICM_20948_execute_w( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (30) entry to 'ICM_20948_execute_w'
|   29 |         if( pdev->_serif->write == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (31) following 'true' branch...
|
'ICM_20948_execute_w': event 32
|
|cc1.exe:
| (32): ...to here
|
<------+
|
'ICM_20948_set_bank': event 33
|
|  120 |         return ICM_20948_execute_w( pdev, REG_BANK_SEL, &bank, 1 );
|      |                ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                |
|      |                (33) returning to 'ICM_20948_set_bank' from 'ICM_20948_execute_w'
|
<------+
|
'ICM_20948_get_agmt': events 34-35
|
|  548 |         retval |= ICM_20948_set_bank( pdev, 2 );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (34) returning to 'ICM_20948_get_agmt' from 'ICM_20948_set_bank'
|  549 |         ICM_20948_GYRO_CONFIG_1_t gcfg1;
|  550 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_GYRO_CONFIG_1, (uint8_t*)&gcfg1, 1*sizeof(gcfg1) );
|      |                   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (35) calling 'ICM_20948_execute_r' from 'ICM_20948_get_agmt'
|
+--> 'ICM_20948_execute_r': events 36-37
|
|   33 | ICM_20948_Status_e      ICM_20948_execute_r( ICM_20948_Device_t* pdev, uint8_t regaddr, uint8_t* pdata, uint32_t len ){
|      |                         ^~~~~~~~~~~~~~~~~~~
|      |                         |
|      |                         (36) entry to 'ICM_20948_execute_r'
|   34 |         if( pdev->_serif->read == NULL ){ return ICM_20948_Stat_NotImpl; }
|      |           ~
|      |           |
|      |           (37) following 'true' branch...
|
'ICM_20948_execute_r': event 38
|
|cc1.exe:
| (38): ...to here
|
<------+
|
'ICM_20948_get_agmt': events 39-40
|
|  550 |         retval |= ICM_20948_execute_r( pdev, (uint8_t)AGB2_REG_GYRO_CONFIG_1, (uint8_t*)&gcfg1, 1*sizeof(gcfg1) );
|      |                   ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|      |                   |
|      |                   (39) returning to 'ICM_20948_get_agmt' from 'ICM_20948_execute_r'
|  551 |         pagmt->fss.g = gcfg1.GYRO_FS_SEL;
|      |                        ~~~~~~~~~~~~~~~~~
|      |                             |
|      |                             (40) use of uninitialized value 'gcfg1.GYRO_FS_SEL' here
|
In file included from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/portable.h:51,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/include/freertos/include/freertos/FreeRTOS.h:63,
from C:/Users/Florian/.platformio/packages/framework-arduinoespressif32/cores/esp32/Arduino.h:33,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httppil.h:14,
from C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/libraries/httpd/httppil.c:13:
```

---

### File: [esp32/telelogger/telelogger.ino](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino)

#### ⚠️ implicit conversion from 'float' to 'double' to match other operand of binary expression [-Wdouble-promotion] (Line 339)

- **File Location:** [esp32/telelogger/telelogger.ino:339](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L339)
- **Column:** 64
- **Analysis Context & Path:**
```text
339 |   if ((lastGPSLat || lastGPSLng) && (abs(gd->lat - lastGPSLat) > 0.001 || abs(gd->lng - lastGPSLng) > 0.001)) {
|                                      ~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~
```

---

#### ⚠️ declaration of 'acc' shadows a global declaration [-Wshadow] (Line 462)

- **File Location:** [esp32/telelogger/telelogger.ino:462](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L462)
- **Column:** 13
- **Analysis Context & Path:**
```text
462 |       float acc[3];
|             ^~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:78:7: note: shadowed declaration is here
78 | float acc[3] = {0};
|       ^~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino: In function 'void showStats()':
```

---

#### ⚠️ format '%u' expects argument of type 'unsigned int', but argument 3 has type 'long unsigned int' [-Wformat=] (Line 597)

- **File Location:** [esp32/telelogger/telelogger.ino:597](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L597)
- **Column:** 16
- **Analysis Context & Path:**
```text
597 |   sprintf(buf, "%02u:%02u.%c ", t / 60000, (t % 60000) / 1000, (t % 1000) / 100 + '0');
|                ^~~~~~~~~~~~~~~  ~~~~~~~~~
|                                   |
|                                   long unsigned int
```

---

#### ⚠️ format '%u' expects argument of type 'unsigned int', but argument 4 has type 'long unsigned int' [-Wformat=] (Line 597)

- **File Location:** [esp32/telelogger/telelogger.ino:597](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L597)
- **Column:** 16
- **Analysis Context & Path:**
```text
597 |   sprintf(buf, "%02u:%02u.%c ", t / 60000, (t % 60000) / 1000, (t % 1000) / 100 + '0');
|                ^~~~~~~~~~~~~~~             ~~~~~~~~~~~~~~~~~~
|                                                        |
|                                                        long unsigned int
```

---

#### ⚠️ format '%c' expects argument of type 'int', but argument 5 has type 'long unsigned int' [-Wformat=] (Line 597)

- **File Location:** [esp32/telelogger/telelogger.ino:597](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L597)
- **Column:** 16
- **Analysis Context & Path:**
```text
597 |   sprintf(buf, "%02u:%02u.%c ", t / 60000, (t % 60000) / 1000, (t % 1000) / 100 + '0');
|                ^~~~~~~~~~~~~~~                                 ~~~~~~~~~~~~~~~~~~~~~~
|                                                                                 |
|                                                                                 long unsigned int
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino: In function 'bool waitMotion(long int)':
```

---

#### ⚠️ declaration of 'acc' shadows a global declaration [-Wshadow] (Line 629)

- **File Location:** [esp32/telelogger/telelogger.ino:629](file:///c:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino#L629)
- **Column:** 13
- **Analysis Context & Path:**
```text
629 |       float acc[3];
|             ^~~
C:/Users/Florian/OneDrive/Documents/Dev/freematics-traccar-encrypted/esp32/telelogger/telelogger.ino:78:7: note: shadowed declaration is here
78 | float acc[3] = {0};
|       ^~~
```

---

