/*
  Q Light Controller
  playbackslider.cpp

  Copyright (C) Heikki Junnila

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  Version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details. The license is
  in the file "COPYING".

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <QIntValidator>
#include <QApplication>
#include <QToolButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QSlider>
#include <QLabel>
#include <QDebug>
#include <QSize>
#include <QIcon>

#include "playbackslider.h"
#include "apputil.h"

PlaybackSlider::PlaybackSlider(QWidget* parent)
    : QWidget(parent)
    , m_select(NULL)
    , m_value(NULL)
    , m_slider(NULL)
    , m_label(NULL)
    , m_flash(NULL)
    , m_previousValue(-1)
{
    new QVBoxLayout(this);
    layout()->setSpacing(1);
    layout()->setContentsMargins(1, 1, 1, 1);

    /* Select button */
    m_select = new QToolButton(this);
    m_select->setIcon(QIcon(":/check.png"));
    m_select->setIconSize(QSize(32, 32));
    m_select->setToolTip(tr("Select"));
    layout()->addWidget(m_select);
    layout()->setAlignment(m_select, Qt::AlignHCenter);
    connect(m_select, SIGNAL(clicked()), this, SIGNAL(selected()));

    /* Value label */
    m_value = new QLabel(this);
    m_value->setAlignment(Qt::AlignHCenter);
    layout()->addWidget(m_value);
    layout()->setAlignment(m_value, Qt::AlignHCenter);

    /* Value slider */
    m_slider = new QSlider(this);
    m_slider->setRange(0, UCHAR_MAX);
    m_slider->setTickInterval(16);
    m_slider->setTickPosition(QSlider::TicksBothSides);
    m_slider->setStyle(AppUtil::saneStyle());
    layout()->addWidget(m_slider);
    layout()->setAlignment(m_slider, Qt::AlignHCenter);
    connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(slotSliderChanged(int)));

    /* Label */
    m_label = new QLabel(this);
    m_label->setWordWrap(true);
    layout()->addWidget(m_label);
    layout()->setAlignment(m_label, Qt::AlignHCenter);

    /* Flash button */
    m_flash = new QToolButton(this);
    m_flash->setIcon(QIcon(":/flash.png"));
    m_flash->setIconSize(QSize(32, 32));
    m_flash->setToolTip(tr("Flash"));
    layout()->addWidget(m_flash);
    layout()->setAlignment(m_flash, Qt::AlignHCenter);
    connect(m_flash, SIGNAL(pressed()), this, SLOT(slotFlashPressed()));
    connect(m_flash, SIGNAL(released()), this, SLOT(slotFlashReleased()));

    slotSliderChanged(0);
}

PlaybackSlider::~PlaybackSlider()
{
}

void PlaybackSlider::setValue(uchar value)
{
    m_slider->setValue(value);
}

uchar PlaybackSlider::value() const
{
    return m_slider->value();
}

void PlaybackSlider::setLabel(const QString& text)
{
    m_label->setText(text);
}

QString PlaybackSlider::label() const
{
    return m_label->text();
}

void PlaybackSlider::setSelected(bool sel)
{
    if (sel == true)
    {
        QPalette pal(QApplication::palette());
        pal.setColor(QPalette::Window, pal.color(QPalette::Highlight));
        setPalette(pal);
        setAutoFillBackground(true);
        m_slider->setFocus(Qt::MouseFocusReason);
    }
    else
    {
        setPalette(QApplication::palette());
        setAutoFillBackground(false);
    }
}

void PlaybackSlider::slotSliderChanged(int value)
{
    if (value == m_previousValue)
        return;

    m_value->setText(QString::number(value));

    if (value == 0)
        emit stopped();
    else if (value > 0 && m_previousValue == 0)
        emit started();

    m_previousValue = value;
    emit valueChanged(value);
}

void PlaybackSlider::slotFlashPressed()
{
    emit flashing(true);
}

void PlaybackSlider::slotFlashReleased()
{
    emit flashing(false);
}