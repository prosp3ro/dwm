#!/usr/bin/env bash

sudo make install
# kill -HUP "$(pgrep -u "$USER" "\bdwm$")"

Xephyr :5& sleep 1 ; DISPLAY=:5 ssh-agent dwm
