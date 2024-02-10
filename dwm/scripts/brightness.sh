#!/bin/sh

case $1 in 
  i) brillo -q -A 10 ;; # Increase brightness
  d) brillo -q -U 10 ;; # Decrease brightness
  *) echo "Invalid Option" ;;
esac

notify-send -i " " -h string:x-canonical-private-synchronous:brightness "Brightness:" "$(brillo)" -t 4000
