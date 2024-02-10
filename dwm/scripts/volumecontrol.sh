#!/bin/sh


ex() {
  kill -42 $(pidof dwmblocks)
  exit
}

mute() {
  pamixer --toggle-mute

  if [ "$(pamixer --get-mute)" = true ]; then 
    notify-send -i " " -h string:x-canonical-private-synchronous:volume "Volume:" "Muted" -t 4000
  else 
    notify-send -i " " -h string:x-canonical-private-synchronous:volume "Volume:" "Unmuted" -t 4000
  fi

  ex
}

case $1 in 
  i) pamixer -i 5 ;; 
  d) pamixer -d 5 ;;
  m) mute ;; 
  *) echo "Invalid Option" ;;
esac

notify-send -i " " -h string:x-canonical-private-synchronous:volume "Volume:" "$(pamixer --get-volume)" -t 4000
ex
