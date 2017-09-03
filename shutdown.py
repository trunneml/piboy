#!/usr/bin/env python

"""
This script is a workaround until the dtoverlay gpio-shutdown is included in
the retropie kernel.
"""

import os
import RPi.GPIO as GPIO

DEFAULT_GPIO_PIN = 21
SHUTDOWN_COMMAND = "/sbin/shutdown -h now"


def watch_gpio_pin(gpio_pin):
    """
    Waits (Blocking) for a falling edge on the given gpio pin
    """
    GPIO.setup(gpio_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.wait_for_edge(gpio_pin, GPIO.FALLING)
    os.system(SHUTDOWN_COMMAND)


if __name__ == "__main__":
    try:
        print("Waitung for shutdown signal")
        GPIO.setmode(GPIO.BCM)
        watch_gpio_pin(DEFAULT_GPIO_PIN)
    finally:
        print("Clean up and good bye!")
        GPIO.cleanup()

