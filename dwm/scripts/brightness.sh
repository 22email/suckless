#!/usr/bin/env sh

case $1 in 
  i) brillo -q -A 10 ;; # Increase brightness
  d) brillo -q -U 10 ;; # Decrease brightness
  *) echo "Invalid Option" ;;
esac

notify-send -h string:x-canonical-private-synchronous:sys-notify "Brightness:" "$(brillo)"

