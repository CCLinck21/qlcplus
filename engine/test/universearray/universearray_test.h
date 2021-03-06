/*
  Q Light Controller - Unit test
  universearray_test.h

  Copyright (c) Heikki Junnila

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef UNIVERSEARRAY_TEST_H
#define UNIVERSEARRAY_TEST_H

#include <QObject>

class UniverseArray_Test : public QObject
{
    Q_OBJECT

private slots:
    void initial();
    void gMChannelMode();
    void gMValueMode();
    void gMValue();
    void applyGM();
    void setGMValue();
    void write();
    void writeRelative();
    void reset();
    void setGMValueEfficiency();
    void writeEfficiency();
};

#endif
